/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:35:46 by manufern          #+#    #+#             */
/*   Updated: 2024/11/11 12:38:23 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_up(t_connection *data)
{
	double	move_speed;
	double	new_pos_x;
	double	new_pos_y;
	int		x;
	int		y;

	move_speed = SPEED_WALK;
	new_pos_x = data->player.pos_x + data->player.dir_x * (move_speed + 0.5);
	new_pos_y = data->player.pos_y + data->player.dir_y * (move_speed + 0.5);
	x = (int)new_pos_x;
	y = (int)new_pos_y;
	if (data->map_file.map_grid[y][x] == '1')
		return ;
	data->player.pos_x += data->player.dir_x * move_speed;
	data->player.pos_y += data->player.dir_y * move_speed;
	data->old_time = data->time;
	data->time = get_current_time_in_milliseconds();
	if (data->time - data->old_time >= 3)
	{
		clear_screen(data);
		paint_view(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.img_ptr, 0, 0);
		data->time = get_current_time_in_milliseconds();
	}
}

void	move_down(t_connection *data)
{
	double	move_speed;
	int		x;
	int		y;
	double	new_pos_x;
	double	new_pos_y;

	move_speed = SPEED_WALK;
	new_pos_x = data->player.pos_x - data->player.dir_x * (move_speed + 0.5);
	new_pos_y = data->player.pos_y - data->player.dir_y * (move_speed + 0.5);
	x = (int)new_pos_x;
	y = (int)new_pos_y;
	if (data->map_file.map_grid[y][x] == '1')
		return ;
	data->player.pos_x -= data->player.dir_x * move_speed;
	data->player.pos_y -= data->player.dir_y * move_speed;
	data->old_time = data->time;
	data->time = get_current_time_in_milliseconds();
	if (data->time - data->old_time >= 3)
	{
		clear_screen(data);
		paint_view(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.img_ptr, 0, 0);
		data->time = get_current_time_in_milliseconds();
	}
}

void	move_left(t_connection *data)
{
	double	move_speed;
	int		x;
	int		y;
	double	new_pos_x;
	double	new_pos_y;

	move_speed = SPEED_WALK;
	new_pos_x = data->player.pos_x + data->player.dir_y * move_speed;
	new_pos_y = data->player.pos_y - data->player.dir_x * move_speed;
	x = (int)new_pos_x;
	y = (int)new_pos_y;
	if (data->map_file.map_grid[y][x] == '1')
		return ;
	data->player.pos_x = new_pos_x;
	data->player.pos_y = new_pos_y;
	data->old_time = data->time;
	data->time = get_current_time_in_milliseconds();
	if (data->time - data->old_time >= 3)
	{
		clear_screen(data);
		paint_view(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.img_ptr, 0, 0);
		data->time = get_current_time_in_milliseconds();
	}
}

void	move_right(t_connection *data)
{
	double	move_speed;
	int		x;
	int		y;
	double	new_pos_x;
	double	new_pos_y;

	move_speed = SPEED_WALK;
	new_pos_x = data->player.pos_x - data->player.dir_y * move_speed;
	new_pos_y = data->player.pos_y + data->player.dir_x * move_speed;
	x = (int)new_pos_x;
	y = (int)new_pos_y;
	if (data->map_file.map_grid[y][x] == '1')
		return ;
	data->player.pos_x = new_pos_x;
	data->player.pos_y = new_pos_y;
	data->old_time = data->time;
	data->time = get_current_time_in_milliseconds();
	if (data->time - data->old_time >= 3)
	{
		clear_screen(data);
		paint_view(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.img_ptr, 0, 0);
		data->time = get_current_time_in_milliseconds();
	}
}
