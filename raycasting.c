/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:56:19 by injah             #+#    #+#             */
/*   Updated: 2025/06/26 15:29:30 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	init_raycasting_info(int x, t_data *data, t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * x / (double)data->screen_width - 1;								//Conversion de la coordonnée x de l'écran en coordonnée caméra dans l'espace de vision, entre -1 (gauche) et 1 (droite).
	ray->dir_x = player->direction.x + player->plane.x * ray->camera_x;					//Calcule la direction du rayon dans le monde 2D, à partir de la direction du joueur et du "plan" de projection.
	ray->dir_y = player->direction.y + player->plane.y * ray->camera_x;
	ray->map_x = (int)player->position.x;												//Position du joueur dans la carte (grille), tronquée en coordonnées d’int case.
	ray->map_y = (int)player->position.y;
	if (ray->dir_x != 0)
		ray->deltadist_x = fabs(1.0 / ray->dir_x);										//Distance à parcourir pour passer d’une ligne verticale à la suivante (x) ou horizontale (y), en unité de rayon.
	else
		ray->deltadist_x = 1e30;
	if (ray->dir_y != 0)
		ray->deltadist_y = fabs(1.0 / ray->dir_y);
	else
		ray->deltadist_y = 1e30;
	if (ray->dir_x < 0)																	//Détermine la direction du pas horizontal, et la distance initiale au premier bord vertical.
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->position.x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->position.x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)																	//Idem pour les pas verticaux.
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->position.y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->position.y) * ray->deltadist_y;
	}
}

static void	calculate_line_height(t_data *data, t_ray *ray, t_player *player)
{
	if (ray->side == 0)
	{
		ray->wall_dist = ray->sidedist_x - ray->deltadist_x;
		if (ray->dir_x < 0)
			ray->wall_card = WEST;
		else
			ray->wall_card = EAST;
	}
	else
	{
		ray->wall_dist = ray->sidedist_y - ray->deltadist_y;
		if (ray->dir_y > 0)
			ray->wall_card = SOUTH;
		else
			ray->wall_card = NORTH;
	}
	if (ray->wall_dist <= 0.0001)
		ray->wall_dist = 0.0001;
	
	ray->line_base_height = data->screen_height / ray->wall_dist;
	ray->line_height = ray->line_base_height * ray->wall_height;

	// draw_end = position du sol en perspective + moitié de la hauteur du mur
	ray->draw_end = data->screen_height / 2 + player->pitch + (player->view_z / ray->wall_dist) + ray->line_base_height / 2;
	ray->draw_start = ray->draw_end - ray->line_height;
	
	ray->draw_end = ft_iclamp(ray->draw_end, 0, data->screen_height - 1);
	ray->draw_start = ft_iclamp(ray->draw_start, 0, data->screen_height - 1);
	
}

static void	calculate_wall_texture(t_data *data, t_ray *ray, double u, double v)
{
	if (ray->side == 0)
		ray->wall_x = data->player.position.y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = data->player.position.x + ray->wall_dist * ray->dir_x;
	ray->wall_x *= u;
	ray->wall_x -= floor(ray->wall_x);
	ray->texture_x = (int)(ray->wall_x * data->wall.width);			//Coordonnée horizontale du pixel dans la texture (inversion si nécessaire selon la direction).
	if (ray->wall_card == WEST || ray->wall_card == SOUTH)
		ray->texture_x =  data->wall.width - ray->texture_x - 1;
	ray->texture_step = v * data->wall.height / ray->line_base_height;	//Préparation de l’échantillonnage vertical : combien de pixels sauter à chaque ligne pour parcourir la texture.
	float offset = ray->draw_start - data->player.pitch - (data->player.view_z / ray->wall_dist);
	float center_offset = offset - data->screen_height / 2 + ray->line_base_height / 2;
	ray->texture_pos = center_offset * ray->texture_step;
}

static void	calculate_plateform(t_data *data, t_ray *ray)
{
	t_ray	clone = *ray;

	if (clone.sidedist_x < clone.sidedist_y)
	{
		clone.sidedist_x += clone.deltadist_x;
		clone.map_x += clone.step_x;
		clone.side = 0;
	}
	else
	{
		clone.sidedist_y += clone.deltadist_y;
		clone.map_y += clone.step_y;
		clone.side = 1;
	}
	calculate_line_height(data, &clone, &data->player);
	ray->platform_start = clone.draw_start;
}

void	draw_floor(t_data *data, t_ray *ray, int x, float u, float v)
{
	int				y;
	int				index;
	unsigned int	color;

	const int 		horizon = data->screen_half_height + data->player.pitch;
	const float 	rayDirX = ray->dir_x;
	const float 	rayDirY = ray->dir_y;
	const float		camZ = (0.5f - ray->wall_height) * data->screen_height + data->player.view_z;

	float			rowDistance;
	float			floorX, floorY;
	int				cellX, cellY;
	int				tx, ty;

	y = ray->platform_start;
	int p = y - horizon;
	while (++y < ray->draw_start + 1)
	{
		p++;
		index = y * data->screen_width + x;
		if (p == 0)
			continue;
		rowDistance = fabs(camZ / p);
		if (data->distance_buffer[index] != 0 && data->distance_buffer[index] < rowDistance)
			continue;

		floorX = data->player.position.x + rowDistance * rayDirX;
		floorY = data->player.position.y + rowDistance * rayDirY;

		floorX *= u;
		floorY *= v;

		cellX = (int)floorX;
		cellY = (int)floorY;

		tx = (int)(data->floor.width * (floorX - cellX)) & (data->floor.width - 1);
		ty = (int)(data->floor.height * (floorY - cellY)) & (data->floor.height - 1);

		color = data->floor.addr[data->floor.width * ty + tx];


		data->color_buffer[index] = color;
		data->distance_buffer[index] = rowDistance;
	}
}


static void	draw_wall(t_data *data, t_img *wall, t_ray *ray, int x, double u, double v)
{
	int					y;
	unsigned int		color;
	const int 			screen_width = data->screen_width;
	int	index;

	if (ray->draw_start >= ray->draw_end)
		return ;

	y = ray->draw_start - 1;
	calculate_wall_texture(data, ray, u, v);
	while (++y < ray->draw_end)
	{
		index = y * screen_width + x;
		if (data->distance_buffer[index] != 0 && data->distance_buffer[index] - 0.1 < ray->wall_dist)
			continue ;
		ray->texture_y = (int)ray->texture_pos & (wall->height - 1);		//& (texture_size - 1) est une bonne optimisation (équivaut à mod texture_size si texture_size est une puissance de 2).
		ray->texture_pos += ray->texture_step;
		color = wall->addr[wall->height * ray->texture_y + ray->texture_x];
		if(ray->side == 1)
			color = (color >> 1) & 8355711;
		data->color_buffer[index] = color;
		data->distance_buffer[index] = ray->wall_dist;
	}
}

static void	draw_one_vertical_line(t_data *data, t_ray *ray, int x)
{
	draw_floor(data, ray, x, 1.2f, 1.5f);
	draw_wall(data, &data->wall, ray, x, 1.0, 1.0);
}

static void	perform_dda(t_data *data, t_ray *ray, t_map *map, int x)
{
	if (ray->sidedist_x < ray->sidedist_y)
		ray->side = 0;
	else
		ray->side = 1;
	while (1)
	{
		ray->wall_height = get_wall_height(map, ray->map_x, ray->map_y);
		calculate_line_height(data, ray, &data->player);
		calculate_plateform(data, ray);
		draw_one_vertical_line(data, ray, x);
		if (is_out_of_map(map, ray->map_x, ray->map_y))
			return ;
		if (ray->platform_start < 1)
			break ;
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		
	}
		
}

void	raycasting(t_data *data)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < data->screen_width)
	{
		init_raycasting_info(x, data, &ray, &data->player);
		perform_dda(data, &ray, &data->map_infos, x);
	}
}