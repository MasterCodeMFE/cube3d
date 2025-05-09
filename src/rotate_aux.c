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
	draw_weapon(con);
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
	draw_minimap(con);
}
