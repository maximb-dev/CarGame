# CarGame Simulation
A C++ application simulating a game where players are assigned to cars as drivers or passengers. The simulation runs in multiple threads to generate data and assign players to cars concurrently.

## Usage
The application generates 1000 players and 200 cars with random coordinates. It assigns players to cars as drivers and passengers in a separate thread. After completion, it displays information about 5 random cars and players within a 15-unit radius of a selected car.

## Overview
This project implements a simulation with the following features:
- **Coordinate System**: Manages 2D coordinates and calculates distances.
- **Player Management**: Tracks player nicknames, coordinates, and assignment status.
- **Car Management**: Assigns drivers and up to 3 passengers to cars, ensuring coordinates match.
- **Multithreading**: Uses separate threads for data generation and car filling.
- **Output**: Displays information about random cars and nearby players within a specified radius.
