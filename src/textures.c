/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:25:03 by manufern          #+#    #+#             */
/*   Updated: 2025/05/05 18:06:06 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void init_weapon_texture(t_connection *con)
{
	con->weapon.img_ptr = mlx_xpm_file_to_image(con->mlx_ptr,
			"./arma/arma3.xpm", &con->weapon.width, &con->weapon.height);
	if (!con->weapon.img_ptr)
	{
		ft_putstr_fd("Error: ./arma/arma.xpm not found\n", 2);
		exit(EXIT_FAILURE);
	}
	con->weapon.img_px_ptr = mlx_get_data_addr(con->weapon.img_ptr,
			&con->weapon.bpp, &con->weapon.line_len, &con->weapon.endian);
}

void init_textures(t_connection *con)
{
	int i;

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
	init_weapon_texture(con); // <-- Inicializa el arma después de las texturas normales
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
	
	// Bounds checking to prevent segmentation faults
	if (!texture || !texture->img_px_ptr)
		return (0x000000); // Return black if texture is invalid
		
	if (texX < 0)
		texX = 0;
	if (texY < 0)
		texY = 0;
	if (texX >= texture->width)
		texX = texture->width - 1;
	if (texY >= texture->height)
		texY = texture->height - 1;

	offset = (texY * texture->line_len) + (texX * (texture->bpp >> 3));
	
	// Additional bounds check for the offset
	int max_offset = texture->height * texture->line_len;
	if (offset < 0 || offset >= max_offset - 4) // -4 for int size
		return (0x000000);
		
	return (*(int *)(texture->img_px_ptr + offset));
}
