/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:37:27 by manufern          #+#    #+#             */
/*   Updated: 2024/11/11 12:38:21 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rgb_to_int(int *rgb)
{
	int	rgb_value;

	rgb_value = rgb[0] << 16;
	rgb_value |= rgb[1] << 8;
	rgb_value |= rgb[2];
	return (rgb_value);
}

void	clear_screen(t_connection *con)
{
	int	x;
	int	y;
	int	color_top;
	int	color_bottom;
	int	color;

	color_top = rgb_to_int(con->map_file.ceiling_rgb);
	color_bottom = rgb_to_int(con->map_file.floor_rgb);
	y = 0;
	while (y < con->wdw_hgth)
	{
		if (y < con->wdw_hgth / 2)
			color = color_top;
		else
			color = color_bottom;
		x = 0;
		while (x < con->wdw_wdth)
		{
			*(int *)(con->img.img_px_ptr + (y * con->img.line_len
						+ x * (con->img.bpp / 8))) = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(con->mlx_ptr, con->win_ptr, con->img.img_ptr, 0, 0);
}

void	paint_view(t_connection *con)
{
	t_ray	ray;

	ray.x = 0;
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
}
