/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:30:31 by manufern          #+#    #+#             */
/*   Updated: 2024/11/11 11:31:22 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	select_vertical_texture(t_connection *con, t_ray *ray)
{
	if (ray->ray_dirx < 0)
		ray->texture = &con->img_array[EA_TEXTUR];
	else
		ray->texture = &con->img_array[WE_TEXTUR];
}

void	select_horizontal_texture(t_connection *con, t_ray *ray)
{
	if (ray->ray_diry < 0)
		ray->texture = &con->img_array[SO_TEXTUR];
	else
		ray->texture = &con->img_array[NO_TEXTUR];
}

void	select_texture(t_connection *con, t_ray *ray)
{
	if (ray->side == 0)
		select_vertical_texture(con, ray);
	else
		select_horizontal_texture(con, ray);
	ray->tex_x = (int)(ray->wall_x * (double)(ray->texture->width));
	if ((ray->side == 0 && ray->ray_dirx < 0)
		|| (ray->side == 1 && ray->ray_diry > 0))
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
}
