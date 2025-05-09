/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:26:49 by manufern          #+#    #+#             */
/*   Updated: 2025/04/03 18:53:51 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calculate_camera_and_direction(t_connection *con, t_ray *ray)
{
	ray->camera_x = 2 * ray->x / (double)(con->wdw_wdth) - 1;
	ray->ray_dirx = con->player.dir_x + con->player.plane_x * ray->camera_x;
	ray->ray_diry = con->player.dir_y + con->player.plane_y * ray->camera_x;
}

void	calculate_delta_dist(t_ray *ray)
{
	if (ray->ray_dirx == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dirx);
	if (ray->ray_diry == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_diry);
}

void	calculate_ray_direction(t_connection *con, t_ray *ray)
{
	calculate_camera_and_direction(con, ray);
	calculate_delta_dist(ray);
}

void	calculate_perpendicular_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

void	calculate_line_height(t_connection *con, t_ray *ray)
{
	ray->line_height = (int)(con->wdw_hgth / ray->perp_wall_dist);
}
