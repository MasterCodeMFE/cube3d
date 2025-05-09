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
	int	d;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		d = (y << 8) - (con->wdw_hgth << 7) + (ray->line_height << 7);
		ray->tex_y = ((d * ray->texture->height) >> 8) / ray->line_height;
		ray->color = get_texture_color(ray->texture, ray->tex_x, ray->tex_y);
		my_mlx_pixel_put(&con->img, ray->x, y, ray->color);
		y++;
	}
}
