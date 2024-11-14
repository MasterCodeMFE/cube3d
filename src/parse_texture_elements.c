/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_elements.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:59:39 by igcastil          #+#    #+#             */
/*   Updated: 2024/11/12 12:55:59 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parse_no_texture(char *line, t_map_file *map_fl)
{
	int	i;

	map_fl->is_el_parsed[NO_TEXTUR] = 1;
	line += 3;
	while (*line && *line == ' ')
		line++;
	if (!(*line) || *line == '\n')
		return (ft_putstr_fd("Error: no path to texture for element NO\n", 2),
			0);
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		i++;
	map_fl->el_texture_path[NO_TEXTUR] = ft_substr(line, 0, i);
	line += i;
	while (*line && *line == ' ')
		line++;
	if (*line == 0)
		return (ft_putstr_fd("Error: incomplete .cub file after NO element\n",
				2), 0);
	if (*line == '\n')
		return (1);
	ft_putstr_fd("Error: file .cub line must end after path to NO texture\n",
		2);
	return (0);
}

int	parse_so_texture(char *line, t_map_file *map_fl)
{
	int	i;

	map_fl->is_el_parsed[SO_TEXTUR] = 1;
	line += 3;
	while (*line && *line == ' ')
		line++;
	if (!(*line) || *line == '\n')
		return (ft_putstr_fd("Error: no path to texture for element SO\n", 2),
			0);
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		i++;
	map_fl->el_texture_path[SO_TEXTUR] = ft_substr(line, 0, i);
	line += i;
	while (*line && *line == ' ')
		line++;
	if (*line == 0)
		return (ft_putstr_fd("Error: incomplete .cub file after SO element\n",
				2), 0);
	if (*line == '\n')
		return (1);
	ft_putstr_fd("Error: file .cub line must end after path to SO texture\n",
		2);
	return (0);
}

int	parse_we_texture(char *line, t_map_file *map_fl)
{
	int	i;

	map_fl->is_el_parsed[WE_TEXTUR] = 1;
	line += 3;
	while (*line && *line == ' ')
		line++;
	if (!(*line) || *line == '\n')
		return (ft_putstr_fd("Error: no path to texture for element WE\n", 2),
			0);
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		i++;
	map_fl->el_texture_path[WE_TEXTUR] = ft_substr(line, 0, i);
	line += i;
	while (*line && *line == ' ')
		line++;
	if (*line == 0)
		return (ft_putstr_fd("Error: incomplete .cub file after WE element\n",
				2), 0);
	if (*line == '\n')
		return (1);
	ft_putstr_fd("Error: file .cub line must end after path to WE texture\n",
		2);
	return (0);
}

int	parse_ea_texture(char *line, t_map_file *map_fl)
{
	int	i;

	map_fl->is_el_parsed[EA_TEXTUR] = 1;
	line += 3;
	while (*line && *line == ' ')
		line++;
	if (!(*line) || *line == '\n')
		return (ft_putstr_fd("Error: no path to texture for element EA\n", 2),
			0);
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		i++;
	map_fl->el_texture_path[EA_TEXTUR] = ft_substr(line, 0, i);
	line += i;
	while (*line && *line == ' ')
		line++;
	if (*line == 0)
		return (ft_putstr_fd("Error: incomplete .cub file after EA element\n",
				2), 0);
	if (*line == '\n')
		return (1);
	ft_putstr_fd("Error: file .cub line must end after path to EA texture\n",
		2);
	return (0);
}
