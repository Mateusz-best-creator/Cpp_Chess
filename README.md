# Chess Game in C++ (OOP)

## Overview

This is a C++ chess game, meticulously crafted using Object-Oriented Programming (OOP) principles. The implementation includes a variety of features such as every possible chess move, castling on both sides and En Passant. You also have sound effects for different moves. One for moving piece into empty square and one for pieces that go to non empty square.

## Interface

Choose from three options to interact with the chess game:

1. **Quick Start:** Initiate a chess game with currently logged players. If a player is not logged in, their name will be displayed as "Unknown".

2. **Player Authentication:** Authenticate in the player database by providing pieces color you want to play with and your name. If your name is new, you will be added to the database. If your name already exists, you can specify whether you want to play as white or black.

3. **Hall of Fame:** Explore the Hall of Fame to view metrics of the top 6 players. Compete with your friends to climb the rankings and establish yourself among the chess elite!

## Features

- **Modular Design:** The game utilizes classes to organize code in a modular fashion, enhancing readability and maintainability.

- **Abstract Classes:** Abstract classes and virtual abstract classes are employed to define common behaviors shared among chess pieces, promoting extensibility.

- **Multiple Inheritance:** The Queen class showcases the use of multiple inheritance, inheriting characteristics from both the Rook and Bishop classes.

- **Smart Pointers:** Standard Template Library (STL) smart pointers are utilized to manage resources efficiently, ensuring memory safety and avoiding leaks.

## Chess Moves

- **Comprehensive Moves:** Every standard chess move is implemented, allowing players to enjoy a complete and authentic gaming experience.

- **Castling:** Castling is supported on both sides, adhering to the rules of the game.

- **En Passant:** The game features the En Passant move, enhancing realism and strategic gameplay.

This chess game project utilizes SDL2, SDL2_image, SDL2_mixer libraries. The required SDL2 libraries are included in the source files, but if you encounter issues starting the project, follow these steps:

## Prerequisites

If you are unable to start the project, download SDL2, SDL_image, SDL_mixer from the following links:
- [SDL2 Releases](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5)
- [SDL_image Releases](https://github.com/libsdl-org/SDL_image/releases)
- [SDL_mixer Releases](https://github.com/libsdl-org/SDL_mixer/releases)

Of course download the latest versions of the liblaries. Ensure you download the versions compatible with your Visual Studio setup. If you are using VS Code, download the VS Code versions of the libraries.

## Configuration Steps

1. **Configure Include Directories:**
   - Go to the properties of your project.
   - In the C/C++ section, click on General.
   - Navigate to Additional Include Directories and provide the path to your SDL include folder.

2. **Configure Linker Directories:**
   - Still in the properties of your project, go to the Linker section.
   - Click on General.
   - Go to Additional Library Directories and select `lib\x86` from your SDL folder.

3. **Configure Linker Input:**
   - In the Linker section, go to Input.
   - Navigate to Additional Dependencies.
   - Add the following entries: `SDL2.lib;SDL2main.lib;SDL2_image.lib;SDL2_mixer`.

4. **Optional Recommendation:**
   - Place the files from SDL_image into your SDL2 folder to ensure automatic linking.
   - If you get an error that SDL2_some_package.dll cannot be found, try to copy some_package.dll and paste it in the same directory where your main.cpp is.

Now, you should be able to build and run the chess game smoothly.

## Build and Run in Microsoft Visual Studio

To build and run the chess game using Microsoft Visual Studio, follow these simple steps:

1. **Open the Project:**
   - Launch Microsoft Visual Studio.
   - Open the chess game project in Visual Studio.

2. **Build and Run:**
   - Press `F5` to build and run the chess game.

That's it! You should now be able to enjoy playing chess. Feel free to explore the features and functionalities of the game. The code is available here: https://github.com/Mateusz-best-creator/Chess/tree/master.

Happy gaming!