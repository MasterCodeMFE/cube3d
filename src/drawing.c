/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:31:36 by manufern          #+#    #+#             */
/*   Updated: 2025/04/03 18:54:05 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*pixel;
	int		bytes_per_pixel;

	bytes_per_pixel = img->bpp / 8;
	pixel = img->img_px_ptr + (y * img->line_len + x * bytes_per_pixel);
	*(unsigned int *) pixel = color;
}

void	draw_vertical_line(t_connection *con, t_ray *ray)
{
	int	y;
	double	tex_step;
	double	tex_pos;

	y = ray->draw_start;
	// Pre-calculate texture stepping to avoid division in the loop
	tex_step = (double)ray->texture->height / ray->line_height;
	tex_pos = (ray->draw_start - con->wdw_hgth / 2 + ray->line_height / 2) * tex_step;
	
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)tex_pos;
		ray->color = get_texture_color(ray->texture, ray->tex_x, ray->tex_y);
		my_mlx_pixel_put(&con->img, ray->x, y, ray->color);
		tex_pos += tex_step;
		y++;
	}
}
