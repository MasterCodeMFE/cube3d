/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:09:59 by igcastil          #+#    #+#             */
/*   Updated: 2025/05/05 16:59:09 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_1st_direction_vector(t_connection *con)
{
	if (con->map_file.map_grid[con->map_file.player_starting_pos[0]]
		[con->map_file.player_starting_pos[1]] == 'N')
	{
		con->player.dir_x = 0;
		con->player.dir_y = -1;
	}
	else if (con->map_file.map_grid[con->map_file.player_starting_pos[0]]
		[con->map_file.player_starting_pos[1]] == 'S')
	{
		con->player.dir_x = 0;
		con->player.dir_y = 1;
	}
	else if (con->map_file.map_grid[con->map_file.player_starting_pos[0]]
		[con->map_file.player_starting_pos[1]] == 'W')
	{
		con->player.dir_x = -1;
		con->player.dir_y = 0;
	}
	else if (con->map_file.map_grid[con->map_file.player_starting_pos[0]]
		[con->map_file.player_starting_pos[1]] == 'E')
	{
		con->player.dir_x = 1;
		con->player.dir_y = 0;
	}
}

void	set_1st_screen_plane_vector(t_connection *con)
{
	if (con->map_file.map_grid[con->map_file.player_starting_pos[0]]
		[con->map_file.player_starting_pos[1]] == 'N')
	{
		con->player.plane_x = 0.66;
		con->player.plane_y = 0;
	}
	else if (con->map_file.map_grid[con->map_file.player_starting_pos[0]]
		[con->map_file.player_starting_pos[1]] == 'S')
	{
		con->player.plane_x = -0.66;
		con->player.plane_y = 0;
	}
	else if (con->map_file.map_grid[con->map_file.player_starting_pos[0]]
		[con->map_file.player_starting_pos[1]] == 'W')
	{
		con->player.plane_x = 0;
		con->player.plane_y = -0.66;
	}
	else if (con->map_file.map_grid[con->map_file.player_starting_pos[0]]
		[con->map_file.player_starting_pos[1]] == 'E')
	{
		con->player.plane_x = 0;
		con->player.plane_y = 0.66;
	}
}

long	get_current_time_in_milliseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	paint_first_view(t_connection *con)
{
	t_ray	ray;

	ray.x = 0;
	con->player.pos_x = con->map_file.player_starting_pos[1] + 0.5;
	con->player.pos_y = con->map_file.player_starting_pos[0] + 0.5;
	set_1st_direction_vector(con);
	set_1st_screen_plane_vector(con);
	while (ray.x < con->wdw_wdth)
	{
		ray.hit = 0;
		ray.map_x = (int)con->player.pos_x;
		ray.map_y = (int)con->player.pos_y;
		calculate_ray_direction(con, &ray);
		initialize_side_distances(con, &ray);
		perform_dda(con, &ray);
		calculate_wall_parameters(con, &ray);
		select_texture(con, &ray);
		draw_vertical_line(con, &ray);
		ray.x++;
	}
	draw_minimap(con);
}
