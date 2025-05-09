/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:38:01 by igcastil          #+#    #+#             */
/*   Updated: 2024/11/12 12:54:21 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map(t_map_file *map_fl)
{
	unsigned int	i;

	i = 0;
	while (i < map_fl->map_num_rows)
	{
		free(map_fl->map_grid[i]);
		free(map_fl->aux_map_grid[i]);
		i++;
	}
	free(map_fl->map_grid);
	free(map_fl->aux_map_grid);
}

void	free_map_file_and_exit(char *msg_2_print, char *ln, t_map_file *map_fl)
{
	int	i;

	i = 0;
	ft_putstr_fd(msg_2_print, 2);
	ft_putstr_fd("\n", 2);
	while (i < (NUM_MAP_ELEMENTS - 2))
	{
		if (map_fl->el_texture_path[i])
			free(map_fl->el_texture_path[i]);
		i++;
	}
	while (ln)
	{
		free(ln);
		ln = get_next_line(map_fl->cub_file_fd);
	}
	free_map(map_fl);
	close(map_fl->cub_file_fd);
	exit(1);
}
