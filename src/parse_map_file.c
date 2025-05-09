/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:45:39 by igcastil          #+#    #+#             */
/*   Updated: 2024/11/12 12:55:49 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	wrt_ln_2_map(char **line, int row, t_map_file *map_file)
{
	char	*aux;
	int		col;

	aux = *line;
	col = 0;
	while (*aux && *aux != '\n')
	{
		if (*aux == ' ' || *aux == '0' || *aux == '1')
			map_file->map_grid[row][col++] = *aux++;
		else if (*aux == 'N' || *aux == 'S' || *aux == 'E' || *aux == 'W')
		{
			if (map_file->is_player_starting_pos_set)
				free_map_file_and_exit("Error: 2 player's starting positions",
					*line, map_file);
			map_file->map_grid[row][col] = *aux++;
			map_file->is_player_starting_pos_set = 1;
			map_file->player_starting_pos[0] = row;
			map_file->player_starting_pos[1] = col++;
		}
		else
			free_map_file_and_exit("Error: invalid char in map grid",
				*line, map_file);
	}
	free(*line);
	*line = get_next_line(map_file->cub_file_fd);
}

static void	parse_map_grid(t_map_file *map_file)
{
	char			*ln;
	unsigned int	row;

	row = 0;
	while (row < map_file->map_file_header_rows)
	{
		ln = get_next_line(map_file->cub_file_fd);
		free(ln);
		row++;
	}
	ln = get_next_line(map_file->cub_file_fd);
	if (!ln)
		free_map_file_and_exit("Error: empty line in .cub file", ln, map_file);
	row = -1;
	while (ln)
	{
		if (*ln == '\n')
		{
			free(ln);
			ln = get_next_line(map_file->cub_file_fd);
			continue ;
		}
		row++;
		wrt_ln_2_map(&ln, row, map_file);
	}
}

static void	map_malloc_mem(unsigned int row, t_map_file *map_file)
{
	map_file->map_num_rows = row;
	map_file->map_grid = (char **)malloc(sizeof(char *) * (row + 1));
	map_file->aux_map_grid = (char **)malloc(sizeof(char *) * (row + 1));
	row = 0;
	while (row < map_file->map_num_rows)
	{
		map_file->map_grid[row] = (char *)malloc(sizeof(char)
				* (map_file->map_num_cols + 1));
		ft_bzero(map_file->map_grid[row], map_file->map_num_cols + 1);
		map_file->aux_map_grid[row] = (char *)malloc(sizeof(char)
				* (map_file->map_num_cols + 1));
		ft_bzero(map_file->aux_map_grid[row], map_file->map_num_cols + 1);
		row++;
	}
	map_file->map_grid[row] = NULL;
	map_file->aux_map_grid[row] = NULL;
	close(map_file->cub_file_fd);
}

static void	count_map_rows_and_malloc_mem(t_map_file *map_file)
{
	char			*ln;
	unsigned int	row;

	ln = get_next_line(map_file->cub_file_fd);
	if (!ln)
		free_map_file_and_exit("Error: empty line in .cub file", ln, map_file);
	row = 0;
	map_file->map_num_cols = 0;
	while (ln)
	{
		if (*ln == '\n')
		{
			free(ln);
			ln = get_next_line(map_file->cub_file_fd);
			map_file->map_file_header_rows++;
			continue ;
		}
		if (ft_strlen(ln) > map_file->map_num_cols)
			map_file->map_num_cols = ft_strlen(ln);
		free(ln);
		ln = get_next_line(map_file->cub_file_fd);
		row++;
	}
	map_malloc_mem(row, map_file);
}

void	parse_map_file(char *filename, t_map_file *map_file)
{
	ft_bzero(map_file, sizeof(t_map_file));
	map_file->cub_file_fd = open(filename, O_RDONLY);
	if (map_file->cub_file_fd == -1)
	{
		perror("Error: file could not be opened");
		exit(1);
	}
	map_file->map_file_header_rows = 0;
	while (map_file->els_count < NUM_MAP_ELEMENTS)
		parse_map_file_element(map_file);
	count_map_rows_and_malloc_mem(map_file);
	map_file->cub_file_fd = open(filename, O_RDONLY);
	parse_map_grid(map_file);
	if (!map_file->is_player_starting_pos_set)
		free_map_file_and_exit("Error: no player's starting position",
			NULL, map_file);
	populate_aux_map_grid(map_file);
	check_surroundings(map_file);
}
