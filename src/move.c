/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:35:46 by manufern          #+#    #+#             */
/*   Updated: 2025/05/07 12:11:26 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_collision(t_connection *data, double new_x, double new_y)
{
	// Check multiple points around the player for better collision detection
	double margin = COLLISION_RADIUS;
	
	// Check bounds first
	if (new_x - margin < 0 || new_y - margin < 0 || 
		new_x + margin >= data->map_file.map_num_cols || 
		new_y + margin >= data->map_file.map_num_rows)
		return (1);
	
	// Check four corners around the player position with margin
	if (data->map_file.map_grid[(int)(new_y - margin)][(int)(new_x - margin)] == '1' ||
		data->map_file.map_grid[(int)(new_y - margin)][(int)(new_x + margin)] == '1' ||
		data->map_file.map_grid[(int)(new_y + margin)][(int)(new_x - margin)] == '1' ||
		data->map_file.map_grid[(int)(new_y + margin)][(int)(new_x + margin)] == '1')
		return (1);
	
	return (0);
}

void	move_with_collision(t_connection *data, double move_x, double move_y)
{
	double new_x = data->player.pos_x + move_x;
	double new_y = data->player.pos_y + move_y;
	
	if (!check_collision(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (!check_collision(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
}

void	update_movement(t_connection *data)
{
	clear_screen(data);
	paint_view(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	data->time = get_current_time_in_milliseconds();
}

void	move_up(t_connection *data)
{
	move_with_collision(data, data->player.dir_x * SPEED_WALK, data->player.dir_y * SPEED_WALK);
}

void	move_down(t_connection *data)
{
	move_with_collision(data, -data->player.dir_x * SPEED_WALK, -data->player.dir_y * SPEED_WALK);
}

void	move_left(t_connection *data)
{
	move_with_collision(data, data->player.dir_y * SPEED_STRAFE, -data->player.dir_x * SPEED_STRAFE);
}

void	move_right(t_connection *data)
{
	move_with_collision(data, -data->player.dir_y * SPEED_STRAFE, data->player.dir_x * SPEED_STRAFE);
}
