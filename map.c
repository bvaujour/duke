/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:32:00 by injah             #+#    #+#             */
/*   Updated: 2025/06/26 15:35:05 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/doom_nukem.h"


// static int	get_longest_string(char **map)
// {
// 	int	i;
// 	int	longest_line_len;
// 	int	current_line_len;

// 	i = 0;
// 	longest_line_len = 0;
// 	current_line_len = 0;
// 	while (map[i])
// 	{
// 		current_line_len = ft_strlen(map[i]);
// 		if (current_line_len > longest_line_len)
// 			longest_line_len = current_line_len;
// 		i++;
// 	}
// 	return (longest_line_len);
// }


int		get_tab_size(char **tab)
{
	int	i;
	
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// void	get_map(t_data *data, t_map *map, char *path)
// {
// 	ft_free_tab(map->grid);
// 	map->grid = NULL;
// 	map->grid = ft_stock_file(path);
// 	if (!map->grid)
// 		duke_error(data, "Nukem: get_Map: Failed to stock_file\n");
// 	data->map.col = get_longest_string(map->grid);
// 	int		i;
// 	char	*str;
// 	i = 0;
// 	while (map->grid[i])
// 	{
// 		str = calloc((data->map.col + 1), sizeof(char));
// 		if (!str)
// 			duke_error(data, "Nukem: get_Map: Failed to stock_file\n");
// 		ft_strlcpy(str, map->grid[i], ft_strlen(map->grid[i]));
// 		free(map->grid[i]);
// 		map->grid[i] = str;
// 		i++;
// 	}
// 	data->map.row = i;
// }

int		count_file_lines(char *path)
{
	int		fd;
	char	*str;
	int		count;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	count = 0;
	str = get_next_line(fd);
	while (str)
	{
		count++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int		max_col(char *path)
{
	int		fd;
	char	*str;
	char	**split_str;
	int		count;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	count = 0;
	str = get_next_line(fd);
	while (str)
	{
		split_str = ft_split(str, ' ');
		if (get_tab_size(split_str) > count)
			count = get_tab_size(split_str);
		ft_free_tab(split_str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void	get_height_map(t_map *map, char *path)
{
	int	i;
	int	j;
	int	fd;
	char *str;
	char **split_str;

	i = 0;
	j = 0;
	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		split_str = ft_split(str, ' ');
		map->height_map[i] = calloc(sizeof(int), (map->col));
		j = 0;
		while (split_str[j])
		{
			map->height_map[i][j] = ft_atoi(split_str[j]);
			j++;
		}
		ft_free_tab(split_str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	map->height_map[i] = NULL;
	close(fd);
}

void	get_map2(t_data *data, t_map *map, char *path)
{
	(void)data;
	(void)map;
	(void)path;
	map->row = count_file_lines(path);
	if (map->row == -1)
		return ;
	map->col = max_col(path);
	map->height_map = malloc(sizeof(int *) * (map->row + 1));
	get_height_map(map, path);
}