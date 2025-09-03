/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:35:46 by manufern          #+#    #+#             */
/*   Updated: 2025/09/01 by Copilot                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Initialize player movement system
void init_player_movement(t_connection *data)
{
    int i;
    
    // Initialize velocity and physics parameters
    data->player.vel_x = 0.0;
    data->player.vel_y = 0.0;
    data->player.accel = ACCELERATION;
    data->player.friction = FRICTION;
    
    // Initialize movement speeds
    data->player.move_speed = SPEED_WALK;
    data->player.rot_speed = SPEED_ROTATE;
    
    // Initialize view angle
    data->player.view_angle = 0.0;
    
    // Clear all key states
    i = 0;
    while (i < 256)
    {
        data->player.keys_pressed[i] = 0;
        i++;
    }
    
    // Initialize connection-level key flags for arrow keys
    data->left_key_pressed = 0;
    data->right_key_pressed = 0;
}

int check_collision(t_connection *data, double new_x, double new_y)
{
    // Check multiple points around the player for better collision detection
    double margin = COLLISION_RADIUS;
    int min_x, max_x, min_y, max_y;
    
    // Check bounds first
    if (new_x - margin < 0 || new_y - margin < 0 || 
        new_x + margin >= data->map_file.map_num_cols || 
        new_y + margin >= data->map_file.map_num_rows)
        return (1);
    
    // Calculate grid indices with proper bounds validation
    min_x = (int)(new_x - margin);
    max_x = (int)(new_x + margin);
    min_y = (int)(new_y - margin);
    max_y = (int)(new_y + margin);
    
    // Additional safety checks for array bounds (cast to avoid sign comparison warnings)
    if (min_x < 0 || min_y < 0 || 
        (unsigned int)max_x >= data->map_file.map_num_cols || 
        (unsigned int)max_y >= data->map_file.map_num_rows)
        return (1);
    
    // Check four corners around the player position with margin
    if (data->map_file.map_grid[min_y][min_x] == '1' ||
        data->map_file.map_grid[min_y][max_x] == '1' ||
        data->map_file.map_grid[max_y][min_x] == '1' ||
        data->map_file.map_grid[max_y][max_x] == '1')
        return (1);
    
    return (0);
}

// Enhanced movement with wall sliding
void move_with_collision(t_connection *data, double move_x, double move_y)
{
    double new_x = data->player.pos_x + move_x;
    double new_y = data->player.pos_y + move_y;
    
    // Try moving in both directions
    if (!check_collision(data, new_x, new_y))
    {
        data->player.pos_x = new_x;
        data->player.pos_y = new_y;
    }
    else
    {
        // Try sliding along walls
        if (!check_collision(data, new_x, data->player.pos_y))
            data->player.pos_x = new_x;
        else if (!check_collision(data, data->player.pos_x, new_y))
            data->player.pos_y = new_y;
    }
}

// Apply movement input based on pressed keys
void apply_movement_input(t_connection *data, double delta_time)
{
    double target_vel_x = 0.0;
    double target_vel_y = 0.0;
    double max_vel = MAX_VELOCITY;
    
    // Calculate target velocity based on input (using safe key index checks)
    if ((KEY_INDEX_VALID(XK_w) && data->player.keys_pressed[XK_w]) || 
        (KEY_INDEX_VALID(XK_W) && data->player.keys_pressed[XK_W]))
    {
        target_vel_x += data->player.dir_x * max_vel;
        target_vel_y += data->player.dir_y * max_vel;
    }
    if ((KEY_INDEX_VALID(XK_s) && data->player.keys_pressed[XK_s]) || 
        (KEY_INDEX_VALID(XK_S) && data->player.keys_pressed[XK_S]))
    {
        target_vel_x -= data->player.dir_x * max_vel;
        target_vel_y -= data->player.dir_y * max_vel;
    }
    if ((KEY_INDEX_VALID(XK_a) && data->player.keys_pressed[XK_a]) || 
        (KEY_INDEX_VALID(XK_A) && data->player.keys_pressed[XK_A]))
    {
        target_vel_x += data->player.dir_y * max_vel;
        target_vel_y -= data->player.dir_x * max_vel;
    }
    if ((KEY_INDEX_VALID(XK_d) && data->player.keys_pressed[XK_d]) || 
        (KEY_INDEX_VALID(XK_D) && data->player.keys_pressed[XK_D]))
    {
        target_vel_x -= data->player.dir_y * max_vel;
        target_vel_y += data->player.dir_x * max_vel;
    }
    
    // Normalize diagonal movement (DOOM-style)
    double target_magnitude = sqrt(target_vel_x * target_vel_x + target_vel_y * target_vel_y);
    if (target_magnitude > max_vel)
    {
        target_vel_x = (target_vel_x / target_magnitude) * max_vel;
        target_vel_y = (target_vel_y / target_magnitude) * max_vel;
    }
    
    // Apply acceleration/deceleration with enhanced responsiveness
    double accel_factor = data->player.accel * delta_time;
    data->player.vel_x += (target_vel_x - data->player.vel_x) * accel_factor;
    data->player.vel_y += (target_vel_y - data->player.vel_y) * accel_factor;
    
    // Apply friction when no input
    if (target_vel_x == 0.0 && target_vel_y == 0.0)
    {
        data->player.vel_x *= data->player.friction;
        data->player.vel_y *= data->player.friction;
    }
    
    // Final velocity clamp (safety check)
    double vel_magnitude = sqrt(data->player.vel_x * data->player.vel_x + 
                        data->player.vel_y * data->player.vel_y);
    if (vel_magnitude > max_vel)
    {
        data->player.vel_x = (data->player.vel_x / vel_magnitude) * max_vel;
        data->player.vel_y = (data->player.vel_y / vel_magnitude) * max_vel;
    }
}

// Update player movement with time-based calculations
void update_player_movement(t_connection *data, double delta_time)
{
    apply_movement_input(data, delta_time);
    
    // Apply movement with collision detection
    move_with_collision(data, data->player.vel_x * delta_time * 60.0, 
                    data->player.vel_y * delta_time * 60.0);
    
    // Handle rotation
    /* Use connection-level flags for arrow keys to avoid indexing keysyms directly
       (XK_Left/XK_Right are large values and cause out-of-bounds accesses). */
    if (data->left_key_pressed)
    {
        double old_dir_x = data->player.dir_x;
        double rot_speed = SPEED_ROTATE * delta_time * 60.0;
        data->player.dir_x = data->player.dir_x * cos(-rot_speed) - data->player.dir_y * sin(-rot_speed);
        data->player.dir_y = old_dir_x * sin(-rot_speed) + data->player.dir_y * cos(-rot_speed);
        double old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(-rot_speed) - data->player.plane_y * sin(-rot_speed);
        data->player.plane_y = old_plane_x * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
    }
    if (data->right_key_pressed)
    {
        double old_dir_x = data->player.dir_x;
        double rot_speed = SPEED_ROTATE * delta_time * 60.0;
        data->player.dir_x = data->player.dir_x * cos(rot_speed) - data->player.dir_y * sin(rot_speed);
        data->player.dir_y = old_dir_x * sin(rot_speed) + data->player.dir_y * cos(rot_speed);
        double old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(rot_speed) - data->player.plane_y * sin(rot_speed);
        data->player.plane_y = old_plane_x * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
    }
}

void update_movement(t_connection *data)
{
    clear_screen(data);
    paint_view(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
    data->time = get_current_time_in_milliseconds();
}

// Legacy movement functions for compatibility
void move_up(t_connection *data)
{
    move_with_collision(data, data->player.dir_x * SPEED_WALK, data->player.dir_y * SPEED_WALK);
}

void move_down(t_connection *data)
{
    move_with_collision(data, -data->player.dir_x * SPEED_WALK, -data->player.dir_y * SPEED_WALK);
}

void move_left(t_connection *data)
{
    move_with_collision(data, data->player.dir_y * SPEED_STRAFE, -data->player.dir_x * SPEED_STRAFE);
}

void move_right(t_connection *data)
{
    move_with_collision(data, -data->player.dir_y * SPEED_STRAFE, data->player.dir_x * SPEED_STRAFE);
}