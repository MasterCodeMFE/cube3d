/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_surroundings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:29:30 by igcastil          #+#    #+#             */
/*   Updated: 2024/11/12 12:54:15 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	depth_first_search(t_map_file *map_file, int row, int col)
{
	if (map_file->aux_map_grid[row][col] == ' '
		|| map_file->aux_map_grid[row][col] == 0)
		free_map_file_and_exit("Error: invalid map", NULL, map_file);
	if ((row == 0 || col == 0) && map_file->aux_map_grid[row][col] == '0')
		free_map_file_and_exit("Error: invalid map", NULL, map_file);
	if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
		return ;
	if (map_file->aux_map_grid[row][col] == '1'
		|| map_file->aux_map_grid[row][col] == 'V')
		return ;
	if (map_file->aux_map_grid[row][col] == '0')
		map_file->aux_map_grid[row][col] = 'V';
	depth_first_search(map_file, row - 1, col);
	depth_first_search(map_file, row + 1, col);
	depth_first_search(map_file, row, col - 1);
	depth_first_search(map_file, row, col + 1);
}

void	check_surroundings(t_map_file *map_file)
{
	depth_first_search(map_file, map_file->player_starting_pos[0],
		map_file->player_starting_pos[1]);
	ft_putstr_fd("Map is OK\n", 1);
}
