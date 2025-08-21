#!/bin/bash

echo "🎮 CUB3D - RAYCASTING ENGINE DEMO 🎮"
echo "====================================="
echo ""
echo "Este es un motor de raycasting completo inspirado en Wolfenstein 3D"
echo "desarrollado para el proyecto cub3D de 42."
echo ""
echo "🚀 CARACTERÍSTICAS IMPLEMENTADAS:"
echo ""
echo "✅ PARTE OBLIGATORIA:"
echo "  - Raycasting en tiempo real con algoritmo DDA"
echo "  - Texturas diferentes para cada orientación de pared"
echo "  - Colores personalizables para suelo y techo"
echo "  - Controles fluidos (WASD + flechas)"
echo "  - Parser robusto de archivos .cub"
echo "  - Detección de colisiones"
echo "  - Validación completa de mapas"
echo ""
echo "⭐ BONUS IMPLEMENTADOS:"
echo "  - Sistema de colisiones mejorado"
echo "  - Minimapa giratorio en tiempo real"
echo "  - Control de ratón para cámara"
echo "  - Elementos interactivos del juego:"
echo "    🪙 Coleccionables (C) - +10 puntos"
echo "    🗝️ Llaves (K) - necesarias para ganar"
echo "    🏥 Packs de salud (H) - +25 HP"
echo "    👹 Enemigos (X) - -20 HP al tocar"
echo "    🚪 Puerta de salida (D)"
echo "    🌊 Agua (~) - ralentiza movimiento"
echo "    🔥 Lava (L) - daña continuamente"
echo "    🧱 Paredes secretas (2)"
echo ""
echo "🎮 CONTROLES:"
echo "  WASD - Movimiento"
echo "  Shift + WASD - Correr"
echo "  Flechas - Rotar cámara / Mirar arriba-abajo"
echo "  C - Activar/Desactivar control de ratón"
echo "  ESC - Salir"
echo ""
echo "🗺️ MAPAS DISPONIBLES:"
echo ""
echo "1. maps/simple.cub - Mapa básico de demostración"
echo "2. maps/new/level1_tutorial.cub - Tutorial fácil"
echo "3. maps/new/level2_enemies.cub - Con enemigos"
echo "4. maps/new/level3_secrets.cub - Laberinto con secretos"
echo "5. maps/new/extended_map.cub - Todos los elementos"
echo ""
echo "¿Qué mapa quieres probar?"
echo "Ingresa el número (1-5) o 'q' para salir:"

read choice

case $choice in
    1)
        echo "🎯 Ejecutando mapa básico..."
        ./cub3d maps/simple.cub
        ;;
    2)
        echo "🎓 Ejecutando tutorial..."
        ./cub3d maps/new/level1_tutorial.cub
        ;;
    3)
        echo "⚔️ Ejecutando nivel con enemigos..."
        ./cub3d maps/new/level2_enemies.cub
        ;;
    4)
        echo "🗝️ Ejecutando laberinto con secretos..."
        ./cub3d maps/new/level3_secrets.cub
        ;;
    5)
        echo "🌟 Ejecutando mapa completo con todos los elementos..."
        ./cub3d maps/new/extended_map.cub
        ;;
    q|Q)
        echo "¡Hasta luego! 👋"
        exit 0
        ;;
    *)
        echo "❌ Opción inválida. Ejecutando mapa básico por defecto..."
        ./cub3d maps/simple.cub
        ;;
esac

echo ""
echo "🎊 ¡Gracias por probar CUB3D!"
echo "Este proyecto demuestra:"
echo "  - Programación en C siguiendo la Norma de 42"
echo "  - Algoritmos de raycasting y DDA"
echo "  - Gestión de gráficos con MiniLibX"
echo "  - Parseo y validación de archivos"
echo "  - Gestión de eventos y memoria"
echo "  - Matemáticas aplicadas a gráficos"
