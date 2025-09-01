# Delta Time Movement and FPS Implementation

This document describes the implementation of delta time-based movement, FPS counter, and texture bounds checking in the cube3d project.

## Overview

The implementation addresses four main objectives:
1. **Frame-rate independent movement**: Movement and rotation depend on delta time rather than frame rate
2. **Centralized rendering**: Single `mlx_put_image_to_window` call per frame to prevent flickering
3. **FPS monitoring**: Real-time FPS counter that prints to terminal every second
4. **Crash prevention**: Texture bounds checking to prevent segmentation faults

## Implementation Details

### 1. Delta Time System

All movement and rotation functions now calculate delta time using:
```c
long current_time = get_current_time_in_milliseconds();
double dt = (current_time - data->time) / 1000.0;

// Cap delta time to prevent large jumps
if (dt > 0.05)
    dt = 0.05;
if (dt < 0.0)
    dt = 0.016; // Fallback to ~60fps timing
```

**Benefits:**
- Smooth movement regardless of frame rate
- Prevents jerky movement during frame drops
- Consistent gameplay experience across different hardware

### 2. Enhanced Movement Functions

Legacy movement functions (`move_up`, `move_down`, `move_left`, `move_right`) now use delta time:
```c
move_with_collision(data, data->player.dir_x * SPEED_WALK * dt * 60.0, 
                    data->player.dir_y * SPEED_WALK * dt * 60.0);
```

Rotation functions (`rotate_left`, `rotate_right`) also use delta time:
```c
rotate_speed = SPEED_ROTATE * dt * 60.0;
```

### 3. FPS Counter

Added to `t_connection` structure:
```c
long fps_last_time;
int  fps_frame_count;
```

FPS counter function:
```c
void update_fps_counter(t_connection *data)
{
    long current_time = get_current_time_in_milliseconds();
    data->fps_frame_count++;
    
    // Print FPS every second
    if (current_time - data->fps_last_time >= 1000)
    {
        printf("FPS: %d\n", data->fps_frame_count);
        data->fps_frame_count = 0;
        data->fps_last_time = current_time;
    }
}
```

### 4. Centralized Rendering

The `update_movement` function ensures single rendering call:
```c
// Paint scene to buffer
clear_screen(data);
paint_view(data);

// Single call to mlx_put_image_to_window per frame
mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
```

### 5. Texture Bounds Checking

Enhanced `get_texture_color` function:
```c
int get_texture_color(t_image *texture, int texX, int texY)
{
    // Null pointer checks
    if (!texture || !texture->img_px_ptr)
        return (0x000000);
        
    // Bounds checking
    if (texX < 0) texX = 0;
    if (texY < 0) texY = 0;
    if (texX >= texture->width) texX = texture->width - 1;
    if (texY >= texture->height) texY = texture->height - 1;

    // Offset validation
    offset = (texY * texture->line_len) + (texX * (texture->bpp >> 3));
    int max_offset = texture->height * texture->line_len;
    if (offset < 0 || offset >= max_offset - 4)
        return (0x000000);
        
    return (*(int *)(texture->img_px_ptr + offset));
}
```

## Files Modified

1. **`inc/cub3d.h`**: Added FPS tracking fields and function declaration
2. **`src/move.c`**: Delta time movement functions and FPS counter
3. **`src/rotate.c`**: Delta time rotation functions  
4. **`src/handlers.c`**: FPS counter integration in main loop
5. **`src/main.c`**: FPS tracking initialization
6. **`src/textures.c`**: Enhanced texture bounds checking

## Testing

The implementation:
- ✅ Compiles without warnings or errors
- ✅ Maintains existing functionality
- ✅ Passes map parsing validation
- ✅ Provides frame-rate independent movement
- ✅ Includes comprehensive error checking

## Usage

Run the program normally:
```bash
./cub3d maps/simple.cub
```

The FPS counter will automatically print to the terminal every second during gameplay.

## Benefits

1. **Smooth gameplay**: Movement is now frame-rate independent
2. **Performance monitoring**: Real-time FPS feedback
3. **Stability**: Texture bounds checking prevents crashes
4. **Optimized rendering**: Single draw call per frame reduces flickering
5. **Consistent experience**: Same movement speed regardless of hardware performance