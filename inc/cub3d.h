/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 09:42:54 by igcastil          #+#    #+#             */
/*   Updated: 2025/05/07 11:43:00 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h> // Necesario para round() y pow() o sqrt()
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <sys/time.h>
# include <alsa/asoundlib.h>
# include <unistd.h>
# include <pthread.h>

# define NUM_MAP_ELEMENTS 6
# define MAP_ROWS 100
# define MAP_COLS 100
// Colores originales (puedes mantenerlos o eliminarlos si no los usas)
# define DARK_COLOR  0x00330066
# define LIGHT_COLOR 0x00FFCC99
# define NORTH_COLOR 0x00FF00
# define SOUTH_COLOR 0xFF0000
# define EAST_COLOR 0x0000FF
# define WEST_COLOR 0xFFFF00

# define SPEED_ROTATE 0.05
# define SPEED_WALK   0.08
# define SPEED_STRAFE 0.08
# define MAX_VIEW_ANGLE 30.0
# define COLLISION_RADIUS 0.2
# define PX_TEXTURE 300

// Enhanced movement constants
# define ACCELERATION 0.15
# define FRICTION 0.85
# define MAX_VELOCITY 0.12
# define MOUSE_SENSITIVITY 0.002

// Key index validation macro
# define KEY_INDEX_VALID(key) ((key) >= 0 && (key) < 256)

//musica
#define SAMPLE_RATE 44100
#define AMPLITUDE 0.6  // Reducido para evitar distorsión
#define NOTE_DURATION 0.15  // Notas más cortas
#define SOUND_BUFFER_SIZE ((int)(SAMPLE_RATE * NOTE_DURATION))

#ifndef M_PI // Asegura que M_PI esté definido
    #define M_PI 3.14159265358979323846
#endif

// --- Minimap Configuration ---
#define MINIMAP_PIXEL_RADIUS 80 // Radio del minimapa en píxeles (fijo)
#define MINIMAP_ZOOM_FACTOR 20.0 // Cuántos píxeles del minimapa equivalen a 1 unidad del mapa (mayor valor = más zoom)
#define MINIMAP_PADDING 20 // Espacio desde los bordes de la ventana en píxeles
#define PLAYER_MINIMAP_SIZE 6 // Tamaño (diámetro) del punto del jugador en el minimapa (aumentado para más visibilidad)
#define MINIMAP_BORDER_THICKNESS 3 // Grosor del borde del minimapa en píxeles
#define COMPASS_MARKER_SIZE 4 // Tamaño de los marcadores de brújula (N, S, E, O)

// --- Ray visualization in minimap ---
#define FOV_RAYS_COUNT 21 // Number of rays to show in minimap FOV (odd number for center ray)
#define RAY_LENGTH_FACTOR 0.5 // Factor to control ray length visualization (0.0 to 1.0)
#define RAY_ALPHA 128 // Alpha value for ray transparency (0-255)

// --- Colors (in ARGB format) - Paleta estilo "moderno" ---
#define MINIMAP_WALL_COLOR 0x00555555 // Dark Grey para paredes
#define MINIMAP_EMPTY_COLOR 0x00AAAAAA // Light Grey para espacio vacío (carretera/área)
#define MINIMAP_PLAYER_COLOR 0xFFFF0000 // Bright Red para el jugador
#define MINIMAP_BORDER_COLOR 0xFFFFFFFF // White border (modern feel)
#define COMPASS_NORTH_COLOR 0xFFFF0000 // Red para Norte
#define COMPASS_SOUTH_COLOR 0xFF0000FF // Blue para Sur
#define COMPASS_EAST_COLOR 0xFF00FF00 // Green para Este
#define COMPASS_WEST_COLOR 0xFFFFFF00 // Yellow para Oeste

// --- Ray visualization colors ---
#define RAY_COLOR_CLOSE 0x8000FF00 // Semi-transparent green for close hits
#define RAY_COLOR_FAR 0x40FFFF00 // Semi-transparent yellow for far hits
#define RAY_COLOR_MISS 0x20FF0000 // Very transparent red for misses
#define FOV_COLOR 0x3000FFFF // Semi-transparent cyan for FOV cone

// --- Weapon HUD Colors (Estilo DOOM) ---
#define DOOM_SHOTGUN_COLOR 0xA0A0A0 // Un gris más claro para el arma
#define DOOM_HAND_COLOR 0x8B4513 // Color de mano/guante (Saddle Brown)
#define DOOM_METAL_COLOR 0x606060 // Gris oscuro para partes metálicas

#define TRANSPARENT_COLOR 0xFF000000


typedef struct s_map_file
{
	int				els_count;
	int				is_el_parsed[NUM_MAP_ELEMENTS];
	char			*el_texture_path[NUM_MAP_ELEMENTS - 2];
	int				ceiling_rgb[3];
	int				floor_rgb[3];
	char			**map_grid;
	char			**aux_map_grid;
	unsigned int	map_file_header_rows;
	unsigned int	map_num_rows;
	unsigned int	map_num_cols;
	int				is_player_starting_pos_set;
	int				player_starting_pos[2];
	int				cub_file_fd;
}	t_map_file;

typedef struct s_image
{
	void	*img_ptr;
	char	*img_px_ptr;
	char	*arma;
	int		line_len;
	int		bpp;
	int		endian;
	int		width;
	int		height;
	int		px_color;
}	t_image;

typedef enum e_map_element
{
	NO_TEXTUR,
	SO_TEXTUR,
	WE_TEXTUR,
	EA_TEXTUR,
	FLOOR_COLOR,
	CEILING_COLR
}	t_map_element;

typedef struct s_player
{
	double pos_x;       // Posición en X
	double pos_y;       // Posición en Y
	double dir_x;       // Dirección en X
	double dir_y;       // Dirección en Y
	double plane_x;     // Vector de la cámara en X
	double plane_y;     // Vector de la cámara en Y
	double move_speed;  // Velocidad de movimiento
	double rot_speed;   // Velocidad de rotación
	double view_angle;  // Ángulo de vista (para mirar arriba y abajo)
	// Momentum-based movement
	double vel_x;       // Velocidad en X
	double vel_y;       // Velocidad en Y
	double accel;       // Aceleración
	double friction;    // Fricción/desaceleración
	int	   keys_pressed[256]; // Estado de teclas presionadas
} t_player;

typedef struct s_connection
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			wdw_wdth;
	int			wdw_hgth;
	int			left_key_pressed;
	int			right_key_pressed;
	long		time;
	long		old_time;
	// FPS tracking variables
	int			frame_count;
	long		fps_last_time;
	int			current_fps;
	// Minimap optimization variables
	double		last_minimap_pos_x;
	double		last_minimap_pos_y;
	int			minimap_update_counter;
	// Cached values for performance
	int			cached_ceiling_color;
	int			cached_floor_color;
	t_map_file	map_file;
	t_image		img;
	t_player	player;
	t_image		*img_array;
	t_image		*texture_floor; // Añadir textura del suelo
	t_image		*texture_ceiling; // Añadir textura del techo
	t_image		weapon;
}	t_connection;

typedef struct s_ray
{
    double camera_x;
    int x;
    double ray_dirx;
    double ray_diry;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int steps_x;
    int steps_y;
    int hit;
    int map_x;
    int map_y;
    int side;
    double perp_wall_dist;
    int line_height;
    int draw_start;
    int draw_end;
    int tex_x;
    int tex_y;
    double wall_x;
    int color;
    t_image *texture;

    // Añadir estas dos variables para el cálculo del suelo y techo
    double floor_x; // Coordenada X del suelo
    double floor_y; // Coordenada Y del suelo
} t_ray;

void		rotate_player(t_connection *data);
void		update_screen(t_connection *data);
void		populate_aux_map_grid(t_map_file *map_file);
int			parse_ceiling(char *line, t_map_file *map_fl);
int			parse_floor(char *line, t_map_file *map_fl);
void		draw_vertical_line(t_connection *con, t_ray *ray);
int			terminate_program(t_connection *data);
int			handle_key_input(int keysym, t_connection *data);
void		paint_first_view(t_connection *con);
long		get_current_time_in_milliseconds(void);
void		check_surroundings(t_map_file *map_file);
void		free_map(t_map_file *map_fl);
void		free_map_file_and_exit(char *msg_2_print,
				char *ln, t_map_file *map_fl);
size_t		ft_strlen_gnl(const char *s);
char		*ft_strjoin_gnl(char *s1, char *s2);
void		*ft_memcpy_gnl(void *dest, const void *src, size_t n);
char		*ft_strchr_gnl(char *s, int c);
char		*ft_strdup_gnl(char *s);
char		*get_last_line(char **new_line, char **remainder_addr);
char		*trim_remainder(char	**remainder_addr);
int			ft_read_fd(int fd, char **buffer, char **remainder,
				int *read_bytes_count);
char		*read_from_fd_to_remainder(int fd, char *remainder);
char		*get_next_line(int fd);
void		free_resources(t_connection *data);
void		init_xserv_windw(t_connection *con);
void		parse_map_file_element(t_map_file *map_file);
void		parse_map_file(char *filename, t_map_file *map_file);
void		validate_parsed_elements(t_map_file *map_file);
void		validate_map_integrity(t_map_file *map_file);
int			is_valid_map_character(char c);
int			parse_no_texture(char *line, t_map_file *map_fl);
int			parse_so_texture(char *line, t_map_file *map_fl);
int			parse_we_texture(char *line, t_map_file *map_fl);
int			parse_ea_texture(char *line, t_map_file *map_fl);
void		calculate_camera_and_direction(t_connection *con, t_ray *ray);
void		calculate_delta_dist(t_ray *ray);
void		calculate_ray_direction(t_connection *con, t_ray *ray);
void		calculate_perpendicular_distance(t_ray *ray);
void		calculate_line_height(t_connection *con, t_ray *ray);
void		initialize_steps(t_ray *ray);
void		initialize_side_dist_x(t_connection *con, t_ray *ray);
void		initialize_side_dist_y(t_connection *con, t_ray *ray);
void		initialize_side_distances(t_connection *con, t_ray *ray);
void		perform_dda(t_connection *con, t_ray *ray);
void		calculate_draw_start_end(t_connection *con, t_ray *ray);
void		calculate_wall_x(t_connection *con, t_ray *ray);
void		calculate_wall_parameters(t_connection *con, t_ray *ray);
int	rgb_to_int(int *rgb);
void		clear_screen(t_connection *con);
void		paint_view(t_connection *con);
void		rotate_left(t_connection *data);
void		rotate_right(t_connection *data);
void		move_up(t_connection *data);
void		move_down(t_connection *data);
void		move_left(t_connection *data);
void		move_right(t_connection *data);
void		rotate_up(t_connection *data, double angle);
void		select_vertical_texture(t_connection *con, t_ray *ray);
void		select_horizontal_texture(t_connection *con, t_ray *ray);
void		select_texture(t_connection *con, t_ray *ray);
void		init_textures(t_connection *con);
void		init_texture_image(t_connection *con, int i);
void		init_texture_data(t_connection *con, int i);
void		free_textures_and_exit(t_connection *con, int i);
int			get_texture_color(t_image *texture, int texX, int texY);
void *play_music(void *arg);
void    draw_minimap(t_connection *con);

// Funciones de colisión mejoradas estilo Doom
int			check_collision(t_connection *data, double new_x, double new_y);
void		move_with_collision(t_connection *data, double move_x, double move_y);
void		update_movement(t_connection *data);

// Enhanced movement functions
void		init_player_movement(t_connection *data);
void		update_player_movement(t_connection *data, double delta_time);
void		apply_movement_input(t_connection *data, double delta_time);
int			handle_key_press(int keysym, t_connection *data);
int			handle_key_release(int keysym, t_connection *data);
int			update_game_loop(t_connection *data);

// Enhanced minimap with raycasting visualization
void		draw_minimap_with_rays(t_connection *con);
void		draw_fov_rays(t_connection *con, int center_x, int center_y);
void		draw_single_ray(t_connection *con, int center_x, int center_y, double ray_angle, double max_dist);
int			blend_colors(int base_color, int overlay_color, double alpha);

long get_time_ms(void);

// FPS tracking and display functions
void		init_fps_tracking(t_connection *data);
void		update_fps_counter(t_connection *data);
void		draw_fps_counter(t_connection *data);
void		draw_minimap_optimized(t_connection *data);

#endif