#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <mutex>
#include <random>
#include <atomic>
#include "Player.h"
#include "Car.h"

class Game {
private:
    std::vector<Player> players_;
    std::vector<Car> cars_;
    std::mutex playersMutex_;
    std::mutex carsMutex_;
    std::random_device rd_;
    std::mt19937 gen_;
    std::atomic<bool> isFillingCars_;

public:
    Game();
    void generatePlayers(size_t count);
    void generateCars(size_t count);
    void fillCars();
    void displayRandomCars(size_t count);
    void displayPlayersInRadius(const Car& car, double radius);
    void displayCarInfo(const Car& car) const;
    std::vector<Player>& getPlayers();
    std::vector<Car>& getCars();
    bool isFillingInProgress() const;
    void setFillingStatus(bool status);
};

#endif // GAME_H