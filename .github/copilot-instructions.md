# Air Combat - AI Agent Guidelines

## Architecture

- **Procedural design**: No class hierarchies or polymorphism; use POD structs + free functions
- **Module structure**: Each folder ([core](../src/core), [game_object](../src/game_object), [input](../src/input), [util](../src/util)) exports C-style APIs
- **Game loop**: See [main.cpp](../src/main.cpp) for Init → Update → Render → Shutdown pattern
- **Entity system**: Lifecycle functions `Create/Update/Render/Destroy` per entity type ([player.cpp](../src/game_object/player.cpp), [enemy.cpp](../src/game_object/enemy.cpp), [bullet.cpp](../src/game_object/bullet.cpp))
- **State management**: Singletons via anonymous namespaces (`g_player`, `g_enemies`, `g_bullets`); access via getters

## Code Style

- **Types**: POD structs (`Vector2`, `Rect`, `Circle`) defined in [type.h](../src/util/type.h); prefer `double` for positions
- **Memory**: Stack allocation only; use `std::vector` for dynamic collections; no heap/smart pointers
- **Configuration**: `#define` macros in [config.h](../src/util/config.h) for game constants
- **Constants**: `constexpr` for compile-time values (colors, math constants)
- **Parameters**: Pass SDL_Renderer* explicitly; no global renderer
- **Naming**: `snake_case` for files/functions, `PascalCase` for structs

## Build & Run

```bash
# Configure
cmake -S . -B build

# Build (incremental-safe)
cmake --build build

# Run from workspace root
./build/AirCombat
```

**Dependencies**: SDL2, CMake 3.16+, C++17

## Project Conventions

- **Input handling**: Poll state via [input.cpp](../src/input/input.cpp) API (`IsKeyDown`, `GetMousePos`), not direct SDL events in game logic
- **Collision**: Use geometry helpers from [util.cpp](../src/util/util.cpp) (`RectCircleCollision`, `CircleCircleCollision`)
- **Delta time**: Core clamps `deltaTime` at 0.1s to prevent physics glitches ([core.cpp](../src/core/core.cpp))
- **Rendering**: Direct SDL primitives (SDL_RenderFillRect); custom circle drawing in util
- **Entity lifecycle**: Always balance Create with Destroy; clear vectors on reset

## Key Files

- [main.cpp](../src/main.cpp) - Game loop entry point
- [core.cpp](../src/core/core.cpp) - Game coordinator, collision logic
- [config.h](../src/util/config.h) - Tunable game parameters
- [type.h](../src/util/type.h) - Core data structures
