/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:33:54 by manufern          #+#    #+#             */
/*   Updated: 2025/05/07 12:10:12 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	rotate_player(t_connection *data)
{
	double	rotate_speed;
	double	new_dir_x;
	double	new_dir_y;
	double	new_plane_x;
	double	new_plane_y;

	rotate_speed = -SPEED_ROTATE;
	new_dir_x = data->player.dir_x * cos(rotate_speed)
		- data->player.dir_y * sin(rotate_speed);
	new_dir_y = data->player.dir_x * sin(rotate_speed)
		+ data->player.dir_y * cos(rotate_speed);
	data->player.dir_x = new_dir_x;
	data->player.dir_y = new_dir_y;
	new_plane_x = data->player.plane_x * cos(rotate_speed)
		- data->player.plane_y * sin(rotate_speed);
	new_plane_y = data->player.plane_x * sin(rotate_speed)
		+ data->player.plane_y * cos(rotate_speed);
	data->player.plane_x = new_plane_x;
	data->player.plane_y = new_plane_y;
}

void	rotate_left(t_connection *data)
{
	double	rotate_speed;
	double	new_dir_x;
	double	new_dir_y;
	double	new_plane_x;
	double	new_plane_y;

	rotate_speed = -SPEED_ROTATE;
	new_dir_x = data->player.dir_x * cos(rotate_speed)
		- data->player.dir_y * sin(rotate_speed);
	new_dir_y = data->player.dir_x * sin(rotate_speed)
		+ data->player.dir_y * cos(rotate_speed);
	data->player.dir_x = new_dir_x;
	data->player.dir_y = new_dir_y;
	new_plane_x = data->player.plane_x * cos(rotate_speed)
		- data->player.plane_y * sin(rotate_speed);
	new_plane_y = data->player.plane_x * sin(rotate_speed)
		+ data->player.plane_y * cos(rotate_speed);
	data->player.plane_x = new_plane_x;
	data->player.plane_y = new_plane_y;
	update_screen(data);
}

void	update_screen(t_connection *data)
{
	// Only update timing - rendering is handled by main game loop
	data->time = get_current_time_in_milliseconds();
}

void	rotate_right(t_connection *data)
{
	double	rotate_speed;
	double	new_dir_x;
	double	new_dir_y;
	double	new_plane_x;
	double	new_plane_y;

	rotate_speed = SPEED_ROTATE;
	new_dir_x = data->player.dir_x * cos(rotate_speed)
		- data->player.dir_y * sin(rotate_speed);
	new_dir_y = data->player.dir_x * sin(rotate_speed)
		+ data->player.dir_y * cos(rotate_speed);
	data->player.dir_x = new_dir_x;
	data->player.dir_y = new_dir_y;
	new_plane_x = data->player.plane_x * cos(rotate_speed)
		- data->player.plane_y * sin(rotate_speed);
	new_plane_y = data->player.plane_x * sin(rotate_speed)
		+ data->player.plane_y * cos(rotate_speed);
	data->player.plane_x = new_plane_x;
	data->player.plane_y = new_plane_y;
	update_screen(data);
}
