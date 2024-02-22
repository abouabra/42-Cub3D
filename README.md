# Cub3D

## Description

Cub3D is a project that aims to create a 3D game using the raycasting technique. The project was developed using the C language and the Codam 42MLX library.
The Game is inspired by the world-famous game Wolfenstein 3D, which was developed by id Software in 1992.
The Game is a maze game where the player has to find the exit while avoiding the enemies.
you can fight the enemies using the gun that you have, but be careful, you have limited ammo.

### **Note:**
**The project was developed and tested on a macOS system, and it may not work on other operating systems.**

## Installation

**Pre-requirement**
if you are in a macOS you need to have `gltw` you can install it using brew:
```bash
brew install glew
```

1. Clone the repository
```bash
git clone https://github.com/abouabra/Cub3D.git
```
2. Navigate to the project folder
```bash
cd Cub3D
```
3. Run the make command
```bash
make
```
4. Run the game
```bash
./cub3D maps/bonus.cub
```

## Usage

The game has a few maps that you can play, you can find them in the `maps` folder.
You can also create your own map and play it using the game.

The game can be closed by pressing the 'esc' key or by clicking the red cross on the window.

## Map
The map is a simple text file with the following characters:
- `1` for the wall
- `0` for the empty space
- `N`, `S`, `E`, `W` for the player's starting position and direction
- ` ` (space) for the empty space

## Controls
The player can move using the WASD keys.
shooting is done by pressing the space key.
you can move the camera using the arrow keys or the mouse.

## Screenshots

![Screenshot 1](ScreenShots/level_2-min.png)

![Screenshot 2](ScreenShots/level_5-min.png)

![Screenshot 3](ScreenShots/level_8-min.png)


## Final Note
If you have any suggestions or improvements, feel free to open an issue or submit a pull request.
