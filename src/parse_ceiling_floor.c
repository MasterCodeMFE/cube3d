/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ceiling_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:15:27 by igcastil          #+#    #+#             */
/*   Updated: 2024/11/12 12:55:17 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	parse_ceiling_rgb(char **line, t_map_file *map_fl)
{
	int	rgb;

	rgb = 0;
	while (rgb < 2)
	{
		map_fl->ceiling_rgb[rgb] = ft_atoi(*line);
		if (map_fl->ceiling_rgb[rgb] < 0 || map_fl->ceiling_rgb[rgb] > 255)
			return (ft_putstr_fd("Error: invalid RGB value for element C\n", 2),
				0);
		*line = ft_strchr(*line, ',');
		if (!(*line))
			return (ft_putstr_fd(
					"Error: missing ',' after RGB val for element C\n", 2), 0);
		(*line)++;
		rgb++;
	}
	map_fl->ceiling_rgb[rgb] = ft_atoi(*line);
	if (map_fl->ceiling_rgb[rgb] < 0 || map_fl->ceiling_rgb[rgb] > 255)
		return (ft_putstr_fd("Error: invalid RGB value for element C\n", 2),
			0);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	return (1);
}

int	parse_ceiling(char *line, t_map_file *map_fl)
{
	map_fl->is_el_parsed[CEILING_COLR] = 1;
	line += 2;
	while (*line && *line == ' ')
		line++;
	if (!(*line) || *line == '\n')
		return (ft_putstr_fd("Error: no RGB for element C\n", 2), 0);
	if (!parse_ceiling_rgb(&line, map_fl))
		return (0);
	if (*line == 0)
		return (ft_putstr_fd("Error: incomplete .cub file after C element\n",
				2), 0);
	if (*line == '\n')
		return (1);
	ft_putstr_fd("Error: file .cub line must end after rgb code for C elem.\n",
		2);
	return (0);
}

static int	parse_floor_rgb(char **line, t_map_file *map_fl)
{
	int	rgb;

	rgb = 0;
	while (rgb < 2)
	{
		map_fl->floor_rgb[rgb] = ft_atoi(*line);
		if (map_fl->floor_rgb[rgb] < 0 || map_fl->floor_rgb[rgb] > 255)
			return (ft_putstr_fd("Error: invalid RGB value for element F\n", 2),
				0);
		*line = ft_strchr(*line, ',');
		if (!(*line))
			return (ft_putstr_fd(
					"Error: missing ',' after RGB val for element F\n", 2), 0);
		(*line)++;
		rgb++;
	}
	map_fl->floor_rgb[rgb] = ft_atoi(*line);
	if (map_fl->floor_rgb[rgb] < 0 || map_fl->floor_rgb[rgb] > 255)
		return (ft_putstr_fd("Error: invalid RGB value for element F\n", 2),
			0);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	return (1);
}

int	parse_floor(char *line, t_map_file *map_fl)
{
	map_fl->is_el_parsed[FLOOR_COLOR] = 1;
	line += 2;
	while (*line && *line == ' ')
		line++;
	if (!(*line) || *line == '\n')
		return (ft_putstr_fd("Error: no RGB for element F\n", 2), 0);
	if (!parse_floor_rgb(&line, map_fl))
		return (0);
	if (*line == 0)
		return (ft_putstr_fd("Error: incomplete .cub file after F element\n",
				2), 0);
	if (*line == '\n')
		return (1);
	ft_putstr_fd("Error: file .cub line must end after rgb code for F elem.\n",
		2);
	return (0);
}
