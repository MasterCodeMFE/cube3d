/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:25:03 by manufern          #+#    #+#             */
/*   Updated: 2024/11/11 11:58:19 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_textures(t_connection *con)
{
	int	i;

	con->img_array = malloc(sizeof(t_image) * 4);
	if (!con->img_array)
		return ;
	i = 0;
	while (i < 4)
	{
		init_texture_image(con, i);
		if (!con->img_array[i].img_ptr)
		{
			free_textures_and_exit(con, i);
			return ;
		}
		init_texture_data(con, i);
		i++;
	}
}

void	init_texture_image(t_connection *con, int i)
{
	con->img_array[i].img_ptr = mlx_xpm_file_to_image(con->mlx_ptr,
			con->map_file.el_texture_path[i], &con->img_array[i].width,
			&con->img_array[i].height);
	if (!con->img_array[i].img_ptr)
	{
		ft_putstr_fd(con->map_file.el_texture_path[i], 2);
		ft_putstr_fd(" texture not found\n", 2);
	}
}

void	init_texture_data(t_connection *con, int i)
{
	con->img_array[i].img_px_ptr = mlx_get_data_addr(con->img_array[i].img_ptr,
			&con->img_array[i].bpp, &con->img_array[i].line_len,
			&con->img_array[i].endian);
}

void	free_textures_and_exit(t_connection *con, int i)
{
	while (i > 0)
		mlx_destroy_image(con->mlx_ptr, con->img_array[--i].img_ptr);
	free(con->img_array);
	mlx_destroy_image(con->mlx_ptr, con->img.img_ptr);
	mlx_destroy_window(con->mlx_ptr, con->win_ptr);
	mlx_destroy_display(con->mlx_ptr);
	free(con->mlx_ptr);
	free_map_file_and_exit(NULL, NULL, &con->map_file);
}

int	get_texture_color(t_image *texture, int texX, int texY)
{
	int	offset;

	offset = (texY * texture->line_len) + (texX * (texture->bpp >> 3));
	return (*(int *)(texture->img_px_ptr + offset));
}
