/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:29:18 by manufern          #+#    #+#             */
/*   Updated: 2024/11/11 11:30:40 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	perform_dda(t_connection *con, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->steps_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->steps_y;
			ray->side = 1;
		}
		if (con->map_file.map_grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_draw_start_end(t_connection *con, t_ray *ray)
{
	if (-ray->line_height / 2 + con->wdw_hgth / 2 < 0)
		ray->draw_start = 0;
	else
		ray->draw_start = -ray->line_height / 2 + con->wdw_hgth / 2;
	if (ray->line_height / 2 + con->wdw_hgth / 2 >= con->wdw_hgth)
		ray->draw_end = con->wdw_hgth - 1;
	else
		ray->draw_end = ray->line_height / 2 + con->wdw_hgth / 2;
}

void	calculate_wall_x(t_connection *con, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = con->player.pos_y + ray->perp_wall_dist * ray->ray_diry;
	else
		ray->wall_x = con->player.pos_x + ray->perp_wall_dist * ray->ray_dirx;
	ray->wall_x -= floor(ray->wall_x);
}

void	calculate_wall_parameters(t_connection *con, t_ray *ray)
{
	calculate_perpendicular_distance(ray);
	calculate_line_height(con, ray);
	calculate_draw_start_end(con, ray);
	calculate_wall_x(con, ray);
}
