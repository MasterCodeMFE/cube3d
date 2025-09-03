/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:07:00 by copilot           #+#    #+#             */
/*   Updated: 2025/09/03 13:07:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Initialize FPS tracking variables
void	init_fps_tracking(t_connection *data)
{
	data->frame_count = 0;
	data->fps_last_time = get_current_time_in_milliseconds();
	data->current_fps = 0;
}

// Update FPS counter (should be called every frame)
void	update_fps_counter(t_connection *data)
{
	long	current_time;
	long	elapsed_time;

	data->frame_count++;
	current_time = get_current_time_in_milliseconds();
	elapsed_time = current_time - data->fps_last_time;
	
	// Update FPS every second (1000ms)
	if (elapsed_time >= 1000)
	{
		data->current_fps = (int)(data->frame_count * 1000.0 / elapsed_time);
		data->frame_count = 0;
		data->fps_last_time = current_time;
	}
}

// Draw FPS counter on screen (top-left corner)
void	draw_fps_counter(t_connection *data)
{
	char	fps_text[32];
	char	*fps_str;
	
	// Convert FPS to string
	fps_str = ft_itoa(data->current_fps);
	ft_strlcpy(fps_text, "FPS: ", sizeof(fps_text));
	ft_strlcat(fps_text, fps_str, sizeof(fps_text));
	free(fps_str);
	
	// Draw FPS text in top-left corner with white color
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 20, 0xFFFFFF, fps_text);
}