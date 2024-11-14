/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 09:42:54 by igcastil          #+#    #+#             */
/*   Updated: 2024/11/11 12:30:14 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <sys/time.h>

# define NUM_MAP_ELEMENTS 6
# define MAP_ROWS 100
# define MAP_COLS 100
# define DARK_COLOR  0x00330066
# define LIGHT_COLOR 0x00FFCC99
# define NORTH_COLOR 0x00FF00
# define SOUTH_COLOR 0xFF0000
# define EAST_COLOR 0x0000FF
# define WEST_COLOR 0xFFFF00
# define SPEED_ROTATE 0.06
# define SPEED_WALK   0.2
# define MAX_VIEW_ANGLE 30.0
# define PX_TEXTURE 300

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
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	double	anglo;
	double	view_angle;
}	t_player;

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
	t_map_file	map_file;
	t_image		img;
	t_player	player;
	t_image		*img_array;
}	t_connection;

typedef struct s_ray
{
	double	camera_x;
	int		x;
	double	ray_dirx;
	double	ray_diry;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		steps_x;
	int		steps_y;
	int		hit;
	int		map_x;
	int		map_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		tex_y;
	double	wall_x;
	int		color;
	t_image	*texture;
}	t_ray;

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
int			rgb_to_int(int *rgb);
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

#endif