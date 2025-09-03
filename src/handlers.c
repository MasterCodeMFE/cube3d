/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:50:58 by igcastil          #+#    #+#             */
/*   Updated: 2025/09/01 by Copilot                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_resources(t_connection *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(data->mlx_ptr, data->img_array[i].img_ptr);
		i++;
	}
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data->img_array);
	free_map_file_and_exit("freeing map resources", NULL, &data->map_file);
}

void	handle_movement(int keysym, t_connection *data)
{
	if (keysym == XK_Left)
	{
		rotate_left(data);
		update_movement(data);
	}
	else if (keysym == XK_Right)
	{
		rotate_right(data);
		update_movement(data);
	}
	else if (keysym == XK_w)
	{
		move_up(data);
		update_movement(data);
	}
	else if (keysym == XK_s)
	{
		move_down(data);
		update_movement(data);
	}
	else if (keysym == XK_d)
	{
		move_right(data);
		update_movement(data);
	}
	else if (keysym == XK_a)
	{
		move_left(data);
		update_movement(data);
	}
}

int	handle_key_input(int keysym, t_connection *data)
{
	if (keysym == XK_Escape)
		free_resources(data);
	else
		handle_movement(keysym, data);
	return (0);
}

// New key press handler for enhanced movement with arrow-key flags
int	handle_key_press(int keysym, t_connection *data)
{
	if (keysym == XK_Escape)
		free_resources(data);
	// Set rotation flags for arrow keys (these keysyms are large; use flags)
	else if (keysym == XK_Left)
		data->left_key_pressed = 1;
	else if (keysym == XK_Right)
		data->right_key_pressed = 1;
	// Keep using keys_pressed[] for ASCII-like keys (WASD)
	else if (KEY_INDEX_VALID(keysym))
		data->player.keys_pressed[keysym] = 1;
	return (0);
}

// New key release handler for enhanced movement with arrow-key flags
int	handle_key_release(int keysym, t_connection *data)
{
	if (keysym == XK_Left)
		data->left_key_pressed = 0;
	else if (keysym == XK_Right)
		data->right_key_pressed = 0;
	else if (KEY_INDEX_VALID(keysym))
		data->player.keys_pressed[keysym] = 0;
	return (0);
}

int	terminate_program(t_connection *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_map_file_and_exit("freeing map file resources", NULL, &data->map_file);
	exit(1);
}

// Game loop for smooth movement
int	update_game_loop(t_connection *data)
{
	long current_time = get_current_time_in_milliseconds();
	double delta_time = (current_time - data->old_time) / 1000.0; // Convert to seconds

	// Cap delta time to prevent large jumps
	if (delta_time > 0.05)
		delta_time = 0.05;

	// Update movement
	update_player_movement(data, delta_time);

	// Update screen
	clear_screen(data);
	paint_view(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);

	// Update and draw FPS counter
	update_fps_counter(data);
	draw_fps_counter(data);

	// Update timing
	data->old_time = data->time;
	data->time = current_time;

	return (0);
}