/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:53:59 by igcastil          #+#    #+#             */
/*   Updated: 2025/05/07 12:08:45 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_file_extension(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (len < 5 || ft_strncmp(&file_name[len - 4], ".cub", 4))
	{
		ft_putstr_fd("Error: file extension must be .cub\n", 2);
		exit(1);
	}
}

int	texture_is_ok(t_connection *con)
{
	if (con->img_array[0].height < PX_TEXTURE && con->img_array[0].width
		< PX_TEXTURE && con->img_array[1].height < PX_TEXTURE
		&& con->img_array[1].width < PX_TEXTURE && con->img_array[2].height
		< PX_TEXTURE && con->img_array[2].width < PX_TEXTURE
		&& con->img_array[3].height < PX_TEXTURE && con->img_array[3].width
		< PX_TEXTURE)
		return (1);
	else
		return (0);
}

void init_xserv_windw(t_connection *con) {
    con->mlx_ptr = mlx_init();
    con->wdw_wdth = 1280;
    con->wdw_hgth = 720;
    con->win_ptr = mlx_new_window(con->mlx_ptr, con->wdw_wdth, con->wdw_hgth, "cub3d");
    con->img.img_ptr = mlx_new_image(con->mlx_ptr, con->wdw_wdth, con->wdw_hgth);
    con->img.img_px_ptr = mlx_get_data_addr(con->img.img_ptr, &con->img.bpp, &con->img.line_len, &con->img.endian);
    con->time = get_current_time_in_milliseconds();
    con->old_time = con->time;
    init_textures(con);
    
    // Initialize enhanced movement system
    init_player_movement(con);

    // Asegurarse de que las teclas no se acumulen

    if (texture_is_ok(con)) {
        mlx_hook(con->win_ptr, KeyPress, KeyPressMask, handle_key_press, con);
        mlx_hook(con->win_ptr, KeyRelease, KeyReleaseMask, handle_key_release, con);
        mlx_hook(con->win_ptr, DestroyNotify, NoEventMask, terminate_program, con);
        mlx_loop_hook(con->mlx_ptr, update_game_loop, con);
        clear_screen(con);
        paint_first_view(con);
        mlx_put_image_to_window(con->mlx_ptr, con->win_ptr, con->img.img_ptr, 0, 0);
        mlx_loop(con->mlx_ptr);
    } else {
        write(1, "Texture too big\n", 16);
    }
}

int	main(int argc, char	**argv)
{
	t_connection	con;

	if (argc != 2)
		return (ft_putstr_fd("Error: exec is cub3d map_file_name.cub\n", 2), 0);
	check_file_extension(argv[1]);
	parse_map_file(argv[1], &con.map_file);
	init_xserv_windw(&con);
	return (0);
}
