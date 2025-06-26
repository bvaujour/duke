/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:44:11 by injah             #+#    #+#             */
/*   Updated: 2025/06/26 13:20:09 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_line_in_file(char *path)
{
	int		fd;
	int		line;
	char	*str;
	
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = 0;
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		line++;
	}
	close(fd);
	return (line);
}

char	**ft_stock_file(char *path)
{
	char	**text;
	int		fd;
	int		line;

	line = ft_count_line_in_file(path);
	if (line == -1)
		return (NULL);
	text = malloc(sizeof(char *) * (line + 1));
	if (!text)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = 0;
	text[line] = get_next_line(fd);
	text[line] = ft_strtrim(text[line], "\n", 1);
	while (text[line])
	{
		line++;
		text[line] = get_next_line(fd);
		text[line] = ft_strtrim(text[line], "\n", 1);
	}
	close(fd);
	return (text);
}
