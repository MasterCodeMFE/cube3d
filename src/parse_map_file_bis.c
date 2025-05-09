/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:10:16 by igcastil          #+#    #+#             */
/*   Updated: 2024/11/12 12:55:21 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	populate_aux_map_grid(t_map_file *map_file)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < map_file->map_num_rows)
	{
		j = 0;
		while (j < map_file->map_num_cols)
		{
			map_file->aux_map_grid[i][j] = map_file->map_grid[i][j];
			j++;
		}
		i++;
	}
}
