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

// FPS tracking function
void	update_fps_counter(t_connection *data)
{
	long current_time = get_current_time_in_milliseconds();
	
	data->fps_frame_count++;
	
	// Print FPS every second
	if (current_time - data->fps_last_time >= 1000)
	{
		printf("FPS: %d\n", data->fps_frame_count);
		data->fps_frame_count = 0;
		data->fps_last_time = current_time;
	}
}

// Initialize player movement system
void	init_player_movement(t_connection *data)
{
	int i;
	
	data->player.vel_x = 0.0;
	data->player.vel_y = 0.0;
	data->player.accel = ACCELERATION;
	data->player.friction = FRICTION;
	i = 0;
	while (i < 256)
	{
		data->player.keys_pressed[i] = 0;
		i++;
	}
}

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

// Enhanced movement with wall sliding
void	move_with_collision(t_connection *data, double move_x, double move_y)
{
	double new_x = data->player.pos_x + move_x;
	double new_y = data->player.pos_y + move_y;
	
	// Try moving in both directions
	if (!check_collision(data, new_x, new_y))
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	else
	{
		// Try sliding along walls
		if (!check_collision(data, new_x, data->player.pos_y))
			data->player.pos_x = new_x;
		else if (!check_collision(data, data->player.pos_x, new_y))
			data->player.pos_y = new_y;
	}
}

// Apply movement input based on pressed keys
void	apply_movement_input(t_connection *data, double delta_time)
{
	double target_vel_x = 0.0;
	double target_vel_y = 0.0;
	double max_vel = MAX_VELOCITY;
	
	// Calculate target velocity based on input
	if (data->player.keys_pressed[XK_w] || data->player.keys_pressed[XK_W])
	{
		target_vel_x += data->player.dir_x * max_vel;
		target_vel_y += data->player.dir_y * max_vel;
	}
	if (data->player.keys_pressed[XK_s] || data->player.keys_pressed[XK_S])
	{
		target_vel_x -= data->player.dir_x * max_vel;
		target_vel_y -= data->player.dir_y * max_vel;
	}
	if (data->player.keys_pressed[XK_a] || data->player.keys_pressed[XK_A])
	{
		target_vel_x += data->player.dir_y * max_vel;
		target_vel_y -= data->player.dir_x * max_vel;
	}
	if (data->player.keys_pressed[XK_d] || data->player.keys_pressed[XK_D])
	{
		target_vel_x -= data->player.dir_y * max_vel;
		target_vel_y += data->player.dir_x * max_vel;
	}
	
	// Apply acceleration/deceleration
	double accel_factor = data->player.accel * delta_time;
	data->player.vel_x += (target_vel_x - data->player.vel_x) * accel_factor;
	data->player.vel_y += (target_vel_y - data->player.vel_y) * accel_factor;
	
	// Apply friction when no input
	if (target_vel_x == 0.0 && target_vel_y == 0.0)
	{
		data->player.vel_x *= data->player.friction;
		data->player.vel_y *= data->player.friction;
	}
	
	// Clamp velocity to max
	double vel_magnitude = sqrt(data->player.vel_x * data->player.vel_x + 
								data->player.vel_y * data->player.vel_y);
	if (vel_magnitude > max_vel)
	{
		data->player.vel_x = (data->player.vel_x / vel_magnitude) * max_vel;
		data->player.vel_y = (data->player.vel_y / vel_magnitude) * max_vel;
	}
}

// Update player movement with time-based calculations
void	update_player_movement(t_connection *data, double delta_time)
{
	apply_movement_input(data, delta_time);
	
	// Apply movement with collision detection
	move_with_collision(data, data->player.vel_x * delta_time * 60.0, 
						data->player.vel_y * delta_time * 60.0);
	
	// Handle rotation
	if (data->player.keys_pressed[XK_Left])
	{
		double old_dir_x = data->player.dir_x;
		double rot_speed = SPEED_ROTATE * delta_time * 60.0;
		data->player.dir_x = data->player.dir_x * cos(-rot_speed) - data->player.dir_y * sin(-rot_speed);
		data->player.dir_y = old_dir_x * sin(-rot_speed) + data->player.dir_y * cos(-rot_speed);
		double old_plane_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(-rot_speed) - data->player.plane_y * sin(-rot_speed);
		data->player.plane_y = old_plane_x * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
	}
	if (data->player.keys_pressed[XK_Right])
	{
		double old_dir_x = data->player.dir_x;
		double rot_speed = SPEED_ROTATE * delta_time * 60.0;
		data->player.dir_x = data->player.dir_x * cos(rot_speed) - data->player.dir_y * sin(rot_speed);
		data->player.dir_y = old_dir_x * sin(rot_speed) + data->player.dir_y * cos(rot_speed);
		double old_plane_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(rot_speed) - data->player.plane_y * sin(rot_speed);
		data->player.plane_y = old_plane_x * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
	}
}

void	update_movement(t_connection *data)
{
	long current_time = get_current_time_in_milliseconds();
	double dt = (current_time - data->time) / 1000.0;
	
	// Cap delta time to prevent large jumps
	if (dt > 0.05)
		dt = 0.05;
	if (dt < 0.0)
		dt = 0.016; // Fallback to ~60fps timing
	
	// Paint scene to buffer
	clear_screen(data);
	paint_view(data);
	
	// Single call to mlx_put_image_to_window per frame
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	
	// Update timing at the end
	data->time = current_time;
}

// Legacy movement functions for compatibility - now using delta time
void	move_up(t_connection *data)
{
	long current_time = get_current_time_in_milliseconds();
	double dt = (current_time - data->time) / 1000.0;
	
	// Cap delta time to prevent large jumps
	if (dt > 0.05)
		dt = 0.05;
	if (dt < 0.0)
		dt = 0.016; // Fallback to ~60fps timing
		
	move_with_collision(data, data->player.dir_x * SPEED_WALK * dt * 60.0, 
						data->player.dir_y * SPEED_WALK * dt * 60.0);
}

void	move_down(t_connection *data)
{
	long current_time = get_current_time_in_milliseconds();
	double dt = (current_time - data->time) / 1000.0;
	
	// Cap delta time to prevent large jumps
	if (dt > 0.05)
		dt = 0.05;
	if (dt < 0.0)
		dt = 0.016; // Fallback to ~60fps timing
		
	move_with_collision(data, -data->player.dir_x * SPEED_WALK * dt * 60.0, 
						-data->player.dir_y * SPEED_WALK * dt * 60.0);
}

void	move_left(t_connection *data)
{
	long current_time = get_current_time_in_milliseconds();
	double dt = (current_time - data->time) / 1000.0;
	
	// Cap delta time to prevent large jumps
	if (dt > 0.05)
		dt = 0.05;
	if (dt < 0.0)
		dt = 0.016; // Fallback to ~60fps timing
		
	move_with_collision(data, data->player.dir_y * SPEED_STRAFE * dt * 60.0, 
						-data->player.dir_x * SPEED_STRAFE * dt * 60.0);
}

void	move_right(t_connection *data)
{
	long current_time = get_current_time_in_milliseconds();
	double dt = (current_time - data->time) / 1000.0;
	
	// Cap delta time to prevent large jumps
	if (dt > 0.05)
		dt = 0.05;
	if (dt < 0.0)
		dt = 0.016; // Fallback to ~60fps timing
		
	move_with_collision(data, -data->player.dir_y * SPEED_STRAFE * dt * 60.0, 
						data->player.dir_x * SPEED_STRAFE * dt * 60.0);
}
