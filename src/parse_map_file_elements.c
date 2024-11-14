/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file_elements.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:53:27 by igcastil          #+#    #+#             */
/*   Updated: 2024/11/12 12:55:34 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	parse_texture_floor_or_ceiling(char *line, t_map_file *map_fl)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (parse_no_texture(line, map_fl));
	if (!ft_strncmp(line, "SO ", 3))
		return (parse_so_texture(line, map_fl));
	if (!ft_strncmp(line, "WE ", 3))
		return (parse_we_texture(line, map_fl));
	if (!ft_strncmp(line, "EA ", 3))
		return (parse_ea_texture(line, map_fl));
	if (!ft_strncmp(line, "F ", 2))
		return (parse_floor(line, map_fl));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_ceiling(line, map_fl));
	return (0);
}

static int	is_texture_floor_or_ceiling(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (1);
	if (!ft_strncmp(line, "SO ", 3))
		return (1);
	if (!ft_strncmp(line, "WE ", 3))
		return (1);
	if (!ft_strncmp(line, "EA ", 3))
		return (1);
	if (!ft_strncmp(line, "F ", 2))
		return (1);
	if (!ft_strncmp(line, "C ", 2))
		return (1);
	return (0);
}

static int	already_parsed_element(char *line, t_map_file *map_fl)
{
	if (!ft_strncmp(line, "NO ", 3) && map_fl->is_el_parsed[NO_TEXTUR])
		return (ft_putstr_fd("Error: more than one NO element\n", 2), 1);
	if (!ft_strncmp(line, "SO ", 3) && map_fl->is_el_parsed[SO_TEXTUR])
		return (ft_putstr_fd("Error: more than one SO element\n", 2), 1);
	if (!ft_strncmp(line, "WE ", 3) && map_fl->is_el_parsed[WE_TEXTUR])
		return (ft_putstr_fd("Error: more than one WE element\n", 2), 1);
	if (!ft_strncmp(line, "EA ", 3) && map_fl->is_el_parsed[EA_TEXTUR])
		return (ft_putstr_fd("Error: more than one EA element\n", 2), 1);
	if (!ft_strncmp(line, "F ", 2) && map_fl->is_el_parsed[FLOOR_COLOR])
		return (ft_putstr_fd("Error: more than one F element\n", 2), 1);
	if (!ft_strncmp(line, "C ", 2) && map_fl->is_el_parsed[CEILING_COLR])
		return (ft_putstr_fd("Error: more than one C element\n", 2), 1);
	return (0);
}

static int	get_map_file_element(char *line, t_map_file *map_fl)
{
	if (is_texture_floor_or_ceiling(line))
	{
		if (already_parsed_element(line, map_fl))
			return (0);
		if (parse_texture_floor_or_ceiling(line, map_fl))
		{
			map_fl->els_count++;
			return (1);
		}
		return (0);
	}
	ft_putstr_fd("Error: elements in .cub file must be NO,SO,WE,EA,F and C\n",
		2);
	return (0);
}

void	parse_map_file_element(t_map_file *map_file)
{
	char	*ln;

	ln = get_next_line(map_file->cub_file_fd);
	if (!ln)
		free_map_file_and_exit("Error: empty line in .cub file", ln, map_file);
	while (ln)
	{
		if (*ln == '\n')
		{
			free(ln);
			ln = get_next_line(map_file->cub_file_fd);
			map_file->map_file_header_rows++;
			continue ;
		}
		while (*ln && *ln == ' ')
			ln++;
		if (!get_map_file_element(ln, map_file))
			free_map_file_and_exit("", ln, map_file);
		map_file->map_file_header_rows++;
		free(ln);
		ln = NULL;
	}
}
