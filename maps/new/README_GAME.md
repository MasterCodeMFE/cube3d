# CUB3D - SISTEMA DE JUEGO EXTENDIDO

## Elementos del Mapa

### Símbolos del Mapa:
- `0` - Espacio vacío
- `1` - Pared normal
- `2` - Pared secreta (se puede abrir con interruptor)
- `N/S/E/W` - Posición inicial del jugador

### Elementos Interactivos:
- `C` - Objetos coleccionables (monedas/gemas) - **10 puntos**
- `K` - Llaves (necesarias para abrir la puerta de salida)
- `D` - Puerta de salida (requiere todas las llaves)
- `H` - Packs de salud (+25 HP)
- `A` - Munición/Poder especial
- `X` - Enemigos (te quitan 20 HP si los tocas)
- `S` - Interruptores (abren paredes secretas)
- `T` - Teletransportadores
- `~` - Agua (ralentiza movimiento)
- `L` - Lava (daña 10 HP por segundo)

## Objetivo del Juego

1. **Recolectar** todos los objetos coleccionables (C) para obtener puntos
2. **Encontrar** todas las llaves (K) - necesitas al menos 1 para ganar
3. **Evitar** los enemigos (X) o eliminarlos tocándolos cuando tengas munición
4. **Usar** los packs de salud (H) para mantener tu vida
5. **Activar** interruptores (S) para abrir paredes secretas
6. **Llegar** a la puerta de salida (D) con las llaves necesarias

## Controles

### Movimiento:
- **W** - Adelante
- **S** - Atrás  
- **A** - Strafe izquierda
- **D** - Strafe derecha
- **Shift + WASD** - Correr

### Cámara:
- **Flechas ←/→** - Rotar cámara
- **Flechas ↑/↓** - Mirar arriba/abajo
- **C** - Activar/Desactivar control de ratón
- **Ratón** - Control de cámara (cuando esté activado)

### Interacción:
- **E** - Interactuar con objetos (recoger, abrir puertas, etc.)
- **Espacio** - Usar munición/atacar enemigos

### Otras:
- **ESC** - Salir del juego
- **Tab** - Mostrar/Ocultar estadísticas

## Sistema de Puntuación

- **Coleccionables**: 10 puntos cada uno
- **Enemigo eliminado**: 50 puntos
- **Completar nivel**: 100 puntos bonus
- **Tiempo bonus**: Puntos extra por completar rápido

## Estadísticas HUD

- **Salud**: 0-100 HP (empiezas con 100)
- **Puntuación**: Puntos acumulados
- **Llaves**: Llaves recolectadas / Total necesarias
- **Coleccionables**: Objetos restantes por recoger

## Consejos

1. **Explora** todo el mapa para encontrar secretos
2. **Conserva** tu salud - los packs son limitados
3. **Planifica** tu ruta para ser eficiente
4. **Usa** los interruptores para acceso a áreas secretas
5. **Ten cuidado** con la lava y los enemigos

¡Buena suerte, explorador!
