/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:50:58 by igcastil          #+#    #+#             */
/*   Updated: 2025/05/07 11:58:52 by manufern         ###   ########.fr       */
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
		rotate_left(data);
	else if (keysym == XK_Right)
		rotate_right(data);
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

int	terminate_program(t_connection *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_map_file_and_exit("freeing map file resources", NULL, &data->map_file);
	exit(1);
}
