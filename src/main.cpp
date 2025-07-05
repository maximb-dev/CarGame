#include <iostream>
#include <thread>
#include "../include/Game.h"

int main() {
    std::cout << "Starting CarGame simulation...\n";

    Game game;

    std::cout << "Generating players and cars...\n";
    game.generatePlayers(1000);
    game.generateCars(200);


    std::cout << "Starting car filling process in a separate thread...\n";
    game.setFillingStatus(true);
    std::thread fillThread(&Game::fillCars, &game);


    fillThread.join();
    game.setFillingStatus(false);
    std::cout << "Car filling process completed.\n";


    std::cout << "\nDisplaying information about 5 random cars:\n";
    game.displayRandomCars(5);


    if (!game.getCars().empty()) {
        std::cout << "\nDisplaying players within 15 units of a random car:\n";
        const Car &randomCar = game.getCars()[0];
        game.displayPlayersInRadius(randomCar, 15.0);
    } else {
        std::cout << "No cars available to display players in radius.\n";
    }

    std::cout << "Simulation completed.\n";
    return 0;
}
