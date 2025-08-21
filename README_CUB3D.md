# CUB3D - RAYCASTING ENGINE 🎮

Un motor de raycasting inspirado en Wolfenstein 3D desarrollado con MiniLibX.

## 🚀 Características

### Parte Obligatoria ✅
- **Raycasting en tiempo real** usando algoritmo DDA
- **Texturas en paredes** diferentes según orientación (N, S, E, W)
- **Colores personalizables** para suelo y techo
- **Controles fluidos** con WASD y flechas
- **Gestión de ventana** completa (redimensión, cerrar, etc.)
- **Parser robusto** de archivos .cub con validación de errores
- **Detección de colisiones** con las paredes
- **Mapas válidos** cerrados y bien formados

### Bonus Implementados ⭐
- **Colisiones con paredes** mejoradas
- **Sistema de minimapa** giratorio
- **Puertas que se abren/cierran** (D)
- **Control de ratón** para rotación de cámara
- **Elementos interactivos**:
  - 🪙 Coleccionables (C) - +10 puntos
  - 🗝️ Llaves (K) - necesarias para salir
  - 🏥 Packs de salud (H) - +25 HP
  - 👹 Enemigos (X) - -20 HP
  - 🚪 Puerta de salida (D)
  - 📦 Munición (A)
  - 🌊 Agua (~) - ralentiza movimiento
  - 🔥 Lava (L) - daña al jugador
  - 🧱 Paredes secretas (2)

## 🛠️ Compilación

```bash
make
```

## 🎯 Uso

```bash
./cub3d maps/simple.cub
```

### Mapas disponibles:
- `maps/simple.cub` - Mapa básico de demostración
- `maps/new/level1_tutorial.cub` - Tutorial fácil
- `maps/new/level2_enemies.cub` - Con enemigos
- `maps/new/level3_secrets.cub` - Laberinto con secretos
- `maps/new/extended_map.cub` - Todos los elementos

## 🎮 Controles

### Movimiento:
- **W/S** - Caminar adelante/atrás
- **A/D** - Strafe lateral
- **Shift + WASD** - Correr

### Cámara:
- **Flechas ←/→** - Rotar cámara
- **Flechas ↑/↓** - Mirar arriba/abajo
- **C** - Activar/Desactivar control de ratón
- **Ratón** - Control de cámara

### Otros:
- **ESC** - Salir del juego

## 📁 Estructura del Proyecto

```
cub3D/
├── src/                    # Código fuente
│   ├── main.c             # Punto de entrada
│   ├── game_system.c      # Sistema de juego extendido
│   ├── move.c             # Sistema de movimiento
│   ├── handlers.c         # Manejadores de eventos
│   ├── parse_*.c          # Sistema de parseo
│   ├── ray_*.c            # Motor de raycasting
│   └── ...
├── inc/                   # Headers
│   └── cub3d.h
├── maps/                  # Mapas del juego
│   ├── simple.cub
│   └── new/
├── textures/              # Texturas
│   ├── simonkraft/        # Texturas principales
│   └── bonus/             # Texturas de elementos bonus
├── libft/                 # Biblioteca personal
├── minilibx-linux/        # MiniLibX
└── Makefile
```

## 🗺️ Formato de Mapas

### Elementos básicos (obligatorios):
- `0` - Espacio vacío
- `1` - Pared
- `N/S/E/W` - Posición inicial del jugador

### Elementos de bonus:
- `C` - Coleccionable (10 puntos)
- `K` - Llave (necesaria para ganar)
- `D` - Puerta de salida
- `H` - Pack de salud (+25 HP)
- `X` - Enemigo (-20 HP)
- `A` - Munición
- `2` - Pared secreta
- `~` - Agua (ralentiza)
- `L` - Lava (daña)

### Ejemplo de archivo .cub:
```
NO ./textures/north_texture.xpm
SO ./textures/south_texture.xpm
WE ./textures/west_texture.xpm
EA ./textures/east_texture.xpm

F 220,100,0
C 225,30,0

111111
1C00K1
100001
1000D1
1N0001
111111
```

## 🎨 Sistema de Texturas

Las texturas deben estar en formato XPM y ser de 64x64 píxeles. El proyecto incluye:

- **Texturas principales**: En `textures/simonkraft/`
- **Texturas de bonus**: En `textures/bonus/`
  - `collectible.xpm` - Monedas doradas
  - `health_pack.xpm` - Botiquines rosa
  - `enemy.xpm` - Enemigos rojos
  - `key.xpm` - Llaves azules
  - `door.xpm` - Puertas verdes

## 🏆 Sistema de Puntuación

- **Coleccionables**: 10 puntos cada uno
- **Completar nivel**: 100 puntos bonus
- **Salud**: Empiezas con 100 HP
- **Victoria**: Recoger llave y llegar a la puerta

## 🚨 Validación de Errores

El parser detecta y reporta:
- Archivos inexistentes o inválidos
- Extensión incorrecta (.cub requerida)
- Texturas faltantes o inaccesibles
- Colores RGB fuera de rango [0-255]
- Mapas no cerrados o inválidos
- Múltiples jugadores
- Elementos requeridos faltantes

## 🔧 Características Técnicas

- **Algoritmo DDA** para raycasting eficiente
- **Gestión de memoria** sin leaks
- **60 FPS** con límite de frame rate
- **Colisiones precisas** con buffer ajustable
- **Movimiento suave** con sistema de momentum
- **Minimapa en tiempo real** con rotación

## 📝 Norma 42

Código escrito siguiendo la Norma de 42:
- Máximo 25 líneas por función
- Máximo 5 funciones por archivo
- Variables declaradas al inicio
- Sin for, do-while, switch, goto
- Gestión correcta de memoria

## 🎯 Objetivos de Aprendizaje

- **Matemáticas aplicadas**: Vectores, trigonometría, algoritmos geométricos
- **Gráficos 2D/3D**: Proyección, transformaciones, texturas
- **Gestión de eventos**: Teclado, ratón, ventana
- **Parseo de archivos**: Validación y procesamiento de datos
- **Optimización**: Algoritmos eficientes para tiempo real

---

**¡Disfruta explorando el mundo del raycasting!** 🎮✨
