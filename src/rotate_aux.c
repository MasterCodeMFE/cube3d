/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:37:27 by manufern          #+#    #+#             */
/*   Updated: 2025/05/07 12:00:22 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

// Implementación de la función para dibujar un píxel
// Asegúrate de que esta implementación coincida con la que uses en otras partes si ya existe.
void    draw_pixel(t_connection *con, int x, int y, int color)
{
    if (x >= 0 && x < con->wdw_wdth && y >= 0 && y < con->wdw_hgth)
    {
        *(int *)(con->img.img_px_ptr + (y * con->img.line_len + x * (con->img.bpp / 8))) = color;
    }
}

void draw_weapon(t_connection *con)
{
    int x, y;

    // Movimiento tipo DOOM: offset vertical simulado con sinusoide
    double time = (double)(get_time_ms() % 1000) / 1000.0; // tiempo normalizado [0,1]
    int bob_offset_y = (int)(sin(time * 2 * M_PI * 2) * 5); // frecuencia y amplitud
    int bob_offset_x = (int)(cos(time * 2 * M_PI * 1.5) * 3); // opcional: un poco de X

    // Ajustar la posición vertical del arma para dibujarla más abajo
    int weapon_x = (con->wdw_wdth - con->weapon.width) / 2 + bob_offset_x;
    int weapon_y = con->wdw_hgth - con->weapon.height + bob_offset_y + 20; // Mover 20 píxeles más abajo

    for (y = 0; y < con->weapon.height; y++)
    {
        for (x = 0; x < con->weapon.width; x++)
        {
            int src_offset = y * con->weapon.line_len + x * (con->weapon.bpp / 8);
            int dst_x = weapon_x + x;
            int dst_y = weapon_y + y;

            if (dst_x >= 0 && dst_x < con->wdw_wdth && dst_y >= 0 && dst_y < con->wdw_hgth)
            {
                unsigned int color = *(unsigned int *)(con->weapon.img_px_ptr + src_offset);
                if (color != TRANSPARENT_COLOR)
                    draw_pixel(con, dst_x, dst_y, color);
            }
        }
    }
}



// Implementación de la función para dibujar el minimapa redondo
void    draw_minimap(t_connection *con)
{
    int minimap_radius_pixels = MINIMAP_PIXEL_RADIUS;
    int minimap_center_x = minimap_radius_pixels + MINIMAP_PADDING; // Esquina superior izquierda
    int minimap_center_y = minimap_radius_pixels + MINIMAP_PADDING; // Esquina superior izquierda
    int px, py;
    double map_x_double, map_y_double;
    int map_x_int, map_y_int;
    int color;
    double dist_sq;
    double radius_sq = (double)minimap_radius_pixels * minimap_radius_pixels;
    double border_thickness_sq = (double)MINIMAP_BORDER_THICKNESS * MINIMAP_BORDER_THICKNESS;

    // Dibuja el fondo del minimapa, los elementos del mapa y el borde
    // Itera sobre la caja delimitadora cuadrada del círculo
    for (py = minimap_center_y - minimap_radius_pixels; py < minimap_center_y + minimap_radius_pixels; py++)
    {
        for (px = minimap_center_x - minimap_radius_pixels; px < minimap_center_x + minimap_radius_pixels; px++)
        {
            // Verifica si el píxel actual está dentro del círculo del minimapa
            dist_sq = (double)(px - minimap_center_x) * (px - minimap_center_x) + (double)(py - minimap_center_y) * (py - minimap_center_y);

            if (dist_sq <= radius_sq)
            {
                // Por defecto, el color será el del espacio vacío
                color = MINIMAP_EMPTY_COLOR;

                // Calcula las coordenadas correspondientes del mapa (punto flotante)
                // Posición relativa al centro del minimapa en píxeles, escalada a unidades del mapa por el factor de zoom
                map_x_double = con->player.pos_x + (double)(px - minimap_center_x) / MINIMAP_ZOOM_FACTOR;
                map_y_double = con->player.pos_y + (double)(py - minimap_center_y) / MINIMAP_ZOOM_FACTOR;

                map_x_int = (int)map_x_double;
                map_y_int = (int)map_y_double;

                // Verifica si las coordenadas del mapa están dentro de los límites y determina el color
                // Usamos map_grid, map_num_rows, map_num_cols de tu struct t_map_file
                if (map_x_int >= 0 && map_x_int < (int)con->map_file.map_num_cols && map_y_int >= 0 && map_y_int < (int)con->map_file.map_num_rows)
                {
                    if (con->map_file.map_grid[map_y_int][map_x_int] == '1')
                        color = MINIMAP_WALL_COLOR; // Color de pared
                    // Puedes añadir más condiciones aquí para otros elementos del mapa
                    // else if (con->map_file.map_grid[map_y_int][map_x_int] == 'C')
                    //     color = 0xFFFF00; // Ejemplo: Color de coleccionable (Amarillo)
                }

                // Verifica si el píxel está cerca del borde del círculo para dibujar el borde
                if (radius_sq - dist_sq < border_thickness_sq)
                {
                    color = MINIMAP_BORDER_COLOR; // Dibuja el color del borde por encima
                }

                 draw_pixel(con, px, py, color);
            }
        }
    }

    // --- Dibuja el punto del jugador ---
    // El jugador se dibuja en el centro del minimapa, ya que la vista está centrada en él.
    int player_dot_half_size = PLAYER_MINIMAP_SIZE / 2;
     for (py = minimap_center_y - player_dot_half_size; py <= minimap_center_y + player_dot_half_size; py++)
    {
        for (px = minimap_center_x - player_dot_half_size; px <= minimap_center_x + player_dot_half_size; px++)
        {
             // Asegura que el punto del jugador esté dentro de los límites del círculo del minimapa
             dist_sq = (double)(px - minimap_center_x) * (px - minimap_center_x) + (double)(py - minimap_center_y) * (py - minimap_center_y);
             if (dist_sq <= radius_sq)
             {
                draw_pixel(con, px, py, MINIMAP_PLAYER_COLOR); // Color del jugador
             }
        }
    }

    // --- Dibuja los marcadores de brújula (N, S, E, O) ---
    int marker_half_size = COMPASS_MARKER_SIZE / 2;

    // Norte
    for (py = minimap_center_y - minimap_radius_pixels - marker_half_size; py <= minimap_center_y - minimap_radius_pixels + marker_half_size; py++)
    {
        for (px = minimap_center_x - marker_half_size; px <= minimap_center_x + marker_half_size; px++)
        {
             // Dibuja el píxel si está dentro de la ventana
             draw_pixel(con, px, py, COMPASS_NORTH_COLOR);
        }
    }

    // Sur
     for (py = minimap_center_y + minimap_radius_pixels - marker_half_size; py <= minimap_center_y + minimap_radius_pixels + marker_half_size; py++)
    {
        for (px = minimap_center_x - marker_half_size; px <= minimap_center_x + marker_half_size; px++)
        {
             draw_pixel(con, px, py, COMPASS_SOUTH_COLOR);
        }
    }

    // Este
    for (py = minimap_center_y - marker_half_size; py <= minimap_center_y + marker_half_size; py++)
    {
        for (px = minimap_center_x + minimap_radius_pixels - marker_half_size; px <= minimap_center_x + minimap_radius_pixels + marker_half_size; px++)
        {
             draw_pixel(con, px, py, COMPASS_EAST_COLOR);
        }
    }

    // Oeste
    for (py = minimap_center_y - marker_half_size; py <= minimap_center_y + marker_half_size; py++)
    {
        for (px = minimap_center_x - minimap_radius_pixels - marker_half_size; px <= minimap_center_x - minimap_radius_pixels + marker_half_size; px++)
        {
             draw_pixel(con, px, py, COMPASS_WEST_COLOR);
        }
    }

    // Nota sobre el "efecto 3D": Un minimapa top-down como este, basado en una cuadrícula 2D,
    // inherentemente no tiene perspectiva 3D. Las mejoras visuales (colores, borde,
    // marcadores) dan un aspecto más agradable y funcional similar a una brújula en un
    // entorno 3D, pero no renderizan la geometría del mapa con altura o perspectiva.
    // Lograr un renderizado 3D real dentro del minimapa requeriría un enfoque mucho más complejo.
    
    // --- Draw FOV rays ---
    draw_fov_rays(con, minimap_center_x, minimap_center_y);
    
	draw_weapon(con);
}

// Blend two colors with alpha
int	blend_colors(int base_color, int overlay_color, double alpha)
{
	int base_r = (base_color >> 16) & 0xFF;
	int base_g = (base_color >> 8) & 0xFF;
	int base_b = base_color & 0xFF;
	
	int overlay_r = (overlay_color >> 16) & 0xFF;
	int overlay_g = (overlay_color >> 8) & 0xFF;
	int overlay_b = overlay_color & 0xFF;
	
	int result_r = (int)(base_r * (1.0 - alpha) + overlay_r * alpha);
	int result_g = (int)(base_g * (1.0 - alpha) + overlay_g * alpha);
	int result_b = (int)(base_b * (1.0 - alpha) + overlay_b * alpha);
	
	return ((result_r << 16) | (result_g << 8) | result_b);
}

// Draw a single ray from center to hit point
void	draw_single_ray(t_connection *con, int center_x, int center_y, double ray_angle, double max_dist)
{
	double ray_x = con->player.pos_x;
	double ray_y = con->player.pos_y;
	double ray_dx = cos(ray_angle);
	double ray_dy = sin(ray_angle);
	double step = 0.1;
	double distance = 0.0;
	int hit = 0;
	
	// Cast the ray
	while (distance < max_dist && !hit)
	{
		ray_x += ray_dx * step;
		ray_y += ray_dy * step;
		distance += step;
		
		// Check bounds
		if (ray_x < 0 || ray_y < 0 || 
			ray_x >= con->map_file.map_num_cols || 
			ray_y >= con->map_file.map_num_rows)
			break;
			
		// Check for wall
		if (con->map_file.map_grid[(int)ray_y][(int)ray_x] == '1')
			hit = 1;
	}
	
	// Draw the ray on minimap
	double rel_x = (ray_x - con->player.pos_x) * MINIMAP_ZOOM_FACTOR;
	double rel_y = (ray_y - con->player.pos_y) * MINIMAP_ZOOM_FACTOR;
	
	int end_x = center_x + (int)rel_x;
	int end_y = center_y + (int)rel_y;
	
	// Choose color based on distance and hit
	int color;
	if (hit)
	{
		if (distance < max_dist * 0.3)
			color = RAY_COLOR_CLOSE;
		else
			color = RAY_COLOR_FAR;
	}
	else
		color = RAY_COLOR_MISS;
	
	// Draw line from center to end point
	int dx = abs(end_x - center_x);
	int dy = abs(end_y - center_y);
	int sx = center_x < end_x ? 1 : -1;
	int sy = center_y < end_y ? 1 : -1;
	int err = dx - dy;
	int x = center_x;
	int y = center_y;
	
	while (1)
	{
		// Check if point is within minimap circle
		double dist_sq = (x - center_x) * (x - center_x) + (y - center_y) * (y - center_y);
		if (dist_sq <= MINIMAP_PIXEL_RADIUS * MINIMAP_PIXEL_RADIUS)
			draw_pixel(con, x, y, color);
		
		if (x == end_x && y == end_y)
			break;
			
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

// Draw FOV rays on minimap
void	draw_fov_rays(t_connection *con, int center_x, int center_y)
{
	double player_angle = atan2(con->player.dir_y, con->player.dir_x);
	double fov = M_PI / 3.0; // 60 degrees FOV
	double ray_step = fov / (FOV_RAYS_COUNT - 1);
	double start_angle = player_angle - fov / 2.0;
	double max_ray_distance = 10.0; // Maximum ray distance
	int i;
	
	// Draw each ray
	i = 0;
	while (i < FOV_RAYS_COUNT)
	{
		double ray_angle = start_angle + i * ray_step;
		draw_single_ray(con, center_x, center_y, ray_angle, max_ray_distance);
		i++;
	}
}

// Enhanced minimap with raycasting visualization
void	draw_minimap_with_rays(t_connection *con)
{
	// First draw the regular minimap
	draw_minimap(con);
	
	// Then add the ray visualization (already called in draw_minimap)
}

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
	int		y;
	int		*pixel_ptr;
	int		pixels_per_line;
	int		ceiling_height;
	
	pixels_per_line = con->img.line_len / (con->img.bpp / 8);
	ceiling_height = con->wdw_hgth / 2;
	pixel_ptr = (int *)con->img.img_px_ptr;
	
	// Fast fill ceiling (top half)
	y = 0;
	while (y < ceiling_height)
	{
		int x = 0;
		// Unroll loop slightly for better performance
		while (x < con->wdw_wdth - 3)
		{
			pixel_ptr[y * pixels_per_line + x] = con->cached_ceiling_color;
			pixel_ptr[y * pixels_per_line + x + 1] = con->cached_ceiling_color;
			pixel_ptr[y * pixels_per_line + x + 2] = con->cached_ceiling_color;
			pixel_ptr[y * pixels_per_line + x + 3] = con->cached_ceiling_color;
			x += 4;
		}
		// Handle remaining pixels
		while (x < con->wdw_wdth)
		{
			pixel_ptr[y * pixels_per_line + x] = con->cached_ceiling_color;
			x++;
		}
		y++;
	}
	
	// Fast fill floor (bottom half)
	while (y < con->wdw_hgth)
	{
		int x = 0;
		// Unroll loop slightly for better performance
		while (x < con->wdw_wdth - 3)
		{
			pixel_ptr[y * pixels_per_line + x] = con->cached_floor_color;
			pixel_ptr[y * pixels_per_line + x + 1] = con->cached_floor_color;
			pixel_ptr[y * pixels_per_line + x + 2] = con->cached_floor_color;
			pixel_ptr[y * pixels_per_line + x + 3] = con->cached_floor_color;
			x += 4;
		}
		// Handle remaining pixels
		while (x < con->wdw_wdth)
		{
			pixel_ptr[y * pixels_per_line + x] = con->cached_floor_color;
			x++;
		}
		y++;
	}
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
	draw_minimap_optimized(con);
}
