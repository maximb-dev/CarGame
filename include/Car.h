#ifndef CAR_H
#define CAR_H

#include <string>
#include <vector>
#include "Player.h"
#include "Coordinate.h"

class Car {
private:
    std::string name_;
    Coordinate coordinate_;
    Player* driver_;
    std::vector<Player*> passengers_;
    const size_t MAX_PASSENGERS = 3;

public:
    Car(const std::string& name, const Coordinate& coordinate);
    bool assignDriver(Player* player);
    bool addPassenger(Player* player);
    std::vector<Player*> getAllPlayers() const;
    std::string getName() const;
    Coordinate getCoordinate() const;
    Player* getDriver() const;
    const std::vector<Player*>& getPassengers() const;
    bool isFull() const;
    size_t getAvailableSeats() const;
};

#endif // CAR_H