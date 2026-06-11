# Slime Dungeon

A simple top-down 2D dungeon crawler built in C++ with SFML, inspired by *The Binding of Isaac*. Battle through procedurally structured rooms, collect weapons, and defeat the boss as fast as possible.

---

## Table of Contents

- [About the Game](#about-the-game)
- [Gameplay](#gameplay)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Level File Format](#level-file-format)
- [Authors](#authors)

---

## About the Game

Aqua Dungeon is a 2D top-down dungeon crawler.

The player navigates through a series of rooms, eliminating all enemies before doors unlock and progression is possible. The final room of each level contains a boss. Defeat the boss to advance — the goal is to complete all levels in the shortest time possible.

---

## Gameplay

- Move through rooms and eliminate all enemies to unlock doors
- Pick up weapons to increase your firepower
- Collect hearts dropped by enemies to restore health
- Defeat the boss to complete the level
- Difficulty increases with each level — enemies deal more damage and spawn in greater numbers
- The game ends when all levels are cleared or the player's HP reaches zero

### Enemy Types

| Type | Name | Behavior |
|------|------|----------|
| Type 1 | Slife (Knife-slime) | Charges directly at the player; deals 1 damage on contact |
| Type 2 | Spime (Spit-slime) | Keeps distance and fires projectiles at the player |
| Type 3 | Boss | Moves slowly toward the player and fires projectiles in multiple directions; has increased HP |

### Weapons

| Weapon | Description |
|--------|-------------|
| LEKIA Vattenpistol | Starting weapon; slowest fire rate |
| SuperSoaker | Found in a room; faster fire rate than the starting weapon |
| Högtryckstvätt | Found in a room; fastest fire rate of all weapons |

---

## Controls

| Key / Button | Action |
|---|---|
| `W` | Move up |
| `A` | Move left |
| `S` | Move down |
| `D` | Move right |
| `Mouse` | Aim (player rotates toward cursor) |
| `Left Mouse Button` | Shoot |

---

## Project Structure

```
.
├── src/
│   ├── main.cpp
│   ├── states/         # State machine (MenuState, GameState, PauseState, GameOverState)
│   ├── entities/       # Player, Enemy types, Projectile, Heart
│   ├── objects/        # Base Object and Entity classes
│   ├── weapons/        # Weapon class
│   ├── level/          # Level and Room loading
│   └── resources/      # ResourceManager (textures, sprites)
├── assets/
│   └── textures/
├── levels/
│   ├── level1.txt
│   └── level2.txt
├── CMakeLists.txt
└── README.md
```

---

## Getting Started

### Prerequisites

- C++17 or later
- [SFML 2.x](https://www.sfml-dev.org/)
- CMake 3.x

### Build & Run

```bash
# Clone the repository
git clone <repository-url>
cd slime-dungeon
# Build
mkdir build && cd build
cmake ..
make

# Run
./slime-dungeon
```

---

## Level File Format

Levels are defined in plain `.txt` files located in the `levels/` directory. Each room is described by two lines, and rooms within a level are separated by `___`.

```
___
<door connections>
<enemies and items>
___
```

**Door connections** — four comma-separated values representing connections in each direction (0 = no door, N = room ID to connect to):

```
0,0,0,2     →  No door north/west/south, door east leading to room 2
```

**Enemies and items** — four comma-separated values:

```
1,2,2,3     →  1× Type-1 enemy, 2× Type-2 enemies, 2× Type-3 enemies, 1× Weapon type 3
```

**Example (`level1.txt`):**

```
___
0,0,0,2
1,2,2,3
___
0,0,0,4
2,1,0,1
___
```

Levels can be freely created or modified by editing these files — no recompilation required.

---

## Authors

Developed by Torgav
