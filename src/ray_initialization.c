/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:28:16 by manufern          #+#    #+#             */
/*   Updated: 2024/11/11 11:29:08 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	initialize_steps(t_ray *ray)
{
	if (ray->ray_dirx < 0)
		ray->steps_x = -1;
	else
		ray->steps_x = 1;
	if (ray->ray_diry < 0)
		ray->steps_y = -1;
	else
		ray->steps_y = 1;
}

void	initialize_side_dist_x(t_connection *con, t_ray *ray)
{
	if (ray->steps_x == -1)
		ray->side_dist_x = (con->player.pos_x - ray->map_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - con->player.pos_x)
			* ray->delta_dist_x;
}

void	initialize_side_dist_y(t_connection *con, t_ray *ray)
{
	if (ray->steps_y == -1)
		ray->side_dist_y = (con->player.pos_y - ray->map_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - con->player.pos_y)
			* ray->delta_dist_y;
}

void	initialize_side_distances(t_connection *con, t_ray *ray)
{
	initialize_steps(ray);
	initialize_side_dist_x(con, ray);
	initialize_side_dist_y(con, ray);
}
