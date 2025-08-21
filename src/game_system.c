/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:00:00 by manufern          #+#    #+#             */
/*   Updated: 2025/07/29 10:00:00 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Inicializar el estado del juego
void	init_game_state(t_connection *data)
{
	data->game.health = 100;
	data->game.score = 0;
	data->game.keys_collected = 0;
	data->game.collectibles = 0;
	data->game.enemies_killed = 0;
	data->game.level_complete = 0;
	data->game.game_over = 0;
	data->game.objects = NULL;
	
	// Parsear objetos del mapa
	parse_game_objects(data);
	
	printf("\n=== JUEGO INICIADO ===\n");
	printf("Salud: %d/100\n", data->game.health);
	printf("Coleccionables en mapa: %d\n", data->game.collectibles);
	printf("========================\n\n");
}

// Crear un nuevo objeto del juego
t_game_object	*create_game_object(int x, int y, char type, int value)
{
	t_game_object	*obj;

	obj = malloc(sizeof(t_game_object));
	if (!obj)
		return (NULL);
	obj->x = x;
	obj->y = y;
	obj->type = type;
	obj->collected = 0;
	obj->value = value;
	obj->next = NULL;
	return (obj);
}

// Agregar objeto a la lista
void	add_game_object(t_connection *data, t_game_object *obj)
{
	t_game_object	*current;

	if (!data->game.objects)
	{
		data->game.objects = obj;
		return;
	}
	current = data->game.objects;
	while (current->next)
		current = current->next;
	current->next = obj;
}

// Parsear objetos del mapa
void	parse_game_objects(t_connection *data)
{
	int				x, y;
	char			tile;
	t_game_object	*obj;

	y = 0;
	while (y < (int)data->map_file.map_num_rows)
	{
		x = 0;
		while (x < (int)data->map_file.map_num_cols)
		{
			tile = data->map_file.map_grid[y][x];
			if (is_special_tile(tile))
			{
				if (tile == COLLECTIBLE)
				{
					obj = create_game_object(x, y, tile, 10);
					add_game_object(data, obj);
					data->game.collectibles++;
				}
				else if (tile == KEY_ITEM)
				{
					obj = create_game_object(x, y, tile, 1);
					add_game_object(data, obj);
				}
				else if (tile == ENEMY)
				{
					obj = create_game_object(x, y, tile, 50);
					add_game_object(data, obj);
				}
				else if (tile == HEALTH_PACK)
				{
					obj = create_game_object(x, y, tile, 25);
					add_game_object(data, obj);
				}
				else if (tile == EXIT_DOOR || tile == SWITCH || tile == AMMO_PACK)
				{
					obj = create_game_object(x, y, tile, 0);
					add_game_object(data, obj);
				}
			}
			x++;
		}
		y++;
	}
}

// Verificar si es un tile especial
int	is_special_tile(char c)
{
	return (c == COLLECTIBLE || c == ENEMY || c == EXIT_DOOR || 
			c == KEY_ITEM || c == HEALTH_PACK || c == AMMO_PACK || 
			c == WATER || c == LAVA || c == '2' || c == 'P' || c == 'T');
}

// Obtener color del objeto para el minimapa
int	get_object_color(char type)
{
	if (type == COLLECTIBLE)
		return (COLLECTIBLE_COLOR);
	else if (type == ENEMY)
		return (ENEMY_COLOR);
	else if (type == EXIT_DOOR)
		return (EXIT_COLOR);
	else if (type == KEY_ITEM)
		return (KEY_COLOR);
	else if (type == HEALTH_PACK)
		return (HEALTH_COLOR);
	else if (type == AMMO_PACK)
		return (AMMO_COLOR);
	else if (type == WATER)
		return (WATER_COLOR);
	else if (type == LAVA)
		return (LAVA_COLOR);
	return (0xFFFFFF);
}

// Recolectar objeto
void	collect_object(t_connection *data, int x, int y)
{
	t_game_object	*obj;

	obj = data->game.objects;
	while (obj)
	{
		if (obj->x == x && obj->y == y && !obj->collected)
		{
			obj->collected = 1;
			if (obj->type == COLLECTIBLE)
			{
				data->game.score += obj->value;
				data->game.collectibles--;
				printf("¡Coleccionable! +%d puntos (Total: %d)\n", 
					obj->value, data->game.score);
			}
			else if (obj->type == KEY_ITEM)
			{
				data->game.keys_collected++;
				printf("¡Llave encontrada! (%d/1)\n", data->game.keys_collected);
			}
			else if (obj->type == HEALTH_PACK)
			{
				data->game.health += obj->value;
				if (data->game.health > 100)
					data->game.health = 100;
				printf("¡Salud restaurada! +%d HP (Total: %d/100)\n", 
					obj->value, data->game.health);
			}
			// Quitar el objeto del mapa
			data->map_file.map_grid[y][x] = '0';
			break;
		}
		obj = obj->next;
	}
}

// Manejar tiles especiales (lava, agua, enemigos)
void	handle_special_tiles(t_connection *data)
{
	int	player_x, player_y;
	char tile;
	static long last_damage_time = 0;
	long current_time;

	player_x = (int)data->player.pos_x;
	player_y = (int)data->player.pos_y;
	
	if (player_x < 0 || player_y < 0 || 
		player_x >= (int)data->map_file.map_num_cols || 
		player_y >= (int)data->map_file.map_num_rows)
		return;
		
	tile = data->map_file.map_grid[player_y][player_x];
	current_time = get_current_time_in_milliseconds();
	
	if (tile == LAVA)
	{
		if (current_time - last_damage_time > 1000) // Daño cada segundo
		{
			data->game.health -= 10;
			printf("¡LAVA! -10 HP (Salud: %d/100)\n", data->game.health);
			last_damage_time = current_time;
			if (data->game.health <= 0)
			{
				data->game.game_over = 1;
				printf("¡HAS MUERTO EN LA LAVA!\n");
			}
		}
	}
	else if (tile == ENEMY)
	{
		if (current_time - last_damage_time > 2000) // Daño cada 2 segundos
		{
			data->game.health -= 20;
			printf("¡ENEMIGO! -20 HP (Salud: %d/100)\n", data->game.health);
			last_damage_time = current_time;
			if (data->game.health <= 0)
			{
				data->game.game_over = 1;
				printf("¡HAS SIDO DERROTADO!\n");
			}
		}
	}
}

// Verificar interacciones del jugador
void	check_player_interactions(t_connection *data)
{
	int	player_x, player_y;
	char tile;

	player_x = (int)(data->player.pos_x + 0.5);
	player_y = (int)(data->player.pos_y + 0.5);
	
	if (player_x < 0 || player_y < 0 || 
		player_x >= (int)data->map_file.map_num_cols || 
		player_y >= (int)data->map_file.map_num_rows)
		return;
		
	tile = data->map_file.map_grid[player_y][player_x];
	
	// Auto-recolectar objetos al pasar por encima
	if (tile == COLLECTIBLE || tile == KEY_ITEM || tile == HEALTH_PACK)
	{
		collect_object(data, player_x, player_y);
	}
	
	// Manejar tiles especiales
	handle_special_tiles(data);
}

// Verificar condición de victoria
void	check_win_condition(t_connection *data)
{
	int	player_x, player_y;
	char tile;

	if (data->game.level_complete || data->game.game_over)
		return;
		
	player_x = (int)(data->player.pos_x + 0.5);
	player_y = (int)(data->player.pos_y + 0.5);
	
	if (player_x < 0 || player_y < 0 || 
		player_x >= (int)data->map_file.map_num_cols || 
		player_y >= (int)data->map_file.map_num_rows)
		return;
		
	tile = data->map_file.map_grid[player_y][player_x];
	
	if (tile == EXIT_DOOR)
	{
		// Verificar si el jugador ha recogido todos los objetos necesarios
		int all_collectibles = (data->game.collectibles == 0); // No quedan coleccionables
		int all_keys = (data->game.keys_collected > 0);
		
		if (all_collectibles && all_keys)
		{
			data->game.level_complete = 1;
			data->game.score += 100; // Bonus por completar
			printf("\n=== ¡NIVEL COMPLETADO! ===\n");
			printf("Puntuación final: %d\n", data->game.score);
			printf("Salud final: %d\n", data->game.health);
			printf("¡Felicidades! Has escapado exitosamente.\n");
			printf("======================\n\n");
			
			// Salir del juego limpiamente
			cleanup_and_exit(data);
		}
		else
		{
			// Mostrar qué falta por recoger
			printf("No puedes salir aún. Te faltan:\n");
			if (!all_collectibles)
				printf("- Coleccionables restantes: %d\n", data->game.collectibles);
			if (!all_keys)
				printf("- Necesitas una llave para abrir la puerta\n");
		}
	}
}

// Verificar game over
void	check_game_over(t_connection *data)
{
	if (data->game.health <= 0)
	{
		data->game.game_over = 1;
		printf("\n=== GAME OVER ===\n");
		printf("Puntuación final: %d\n", data->game.score);
		printf("Presiona ESC para salir\n");
	}
}

// Actualizar lógica del juego
void	update_game_logic(t_connection *data)
{
	check_player_interactions(data);
	check_win_condition(data);
	check_game_over(data);
}

// Liberar objetos del juego
void	free_game_objects(t_connection *data)
{
	t_game_object	*current;
	t_game_object	*next;

	current = data->game.objects;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	data->game.objects = NULL;
}

// Función para limpiar recursos y salir del juego
void	cleanup_and_exit(t_connection *con)
{
	// Liberar texturas de sprites
	if (con->sprite_collectible.img_ptr)
		mlx_destroy_image(con->mlx_ptr, con->sprite_collectible.img_ptr);
	if (con->sprite_key.img_ptr)
		mlx_destroy_image(con->mlx_ptr, con->sprite_key.img_ptr);
	if (con->sprite_health.img_ptr)
		mlx_destroy_image(con->mlx_ptr, con->sprite_health.img_ptr);
	if (con->sprite_enemy.img_ptr)
		mlx_destroy_image(con->mlx_ptr, con->sprite_enemy.img_ptr);
	if (con->sprite_exit.img_ptr)
		mlx_destroy_image(con->mlx_ptr, con->sprite_exit.img_ptr);
	
	// Liberar Z-buffer
	if (con->zbuffer)
		free(con->zbuffer);
	
	// Liberar objetos del juego
	free_game_objects(con);
	
	// Aquí puedes añadir más limpieza de recursos si es necesario
	// Como liberar texturas de paredes, sonidos, etc.
	
	// Salir del programa
	exit(0);
}
