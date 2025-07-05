#include "../include/Car.h"

Car::Car(const std::string &name, const Coordinate &coordinate) :
    name_(name), coordinate_(coordinate), driver_(nullptr) {}
bool Car::assignDriver(Player *player) {
    if (!driver_) {
        driver_ = player;
        return true;
    }
    return false;
}
bool Car::addPassenger(Player *player) {
    if (passengers_.size() < MAX_PASSENGERS) {
        passengers_.push_back(player);
        return true;
    }
    return false;
}
std::vector<Player *> Car::getAllPlayers() const {
    std::vector<Player *> allPlayers = {driver_};
    allPlayers.insert(allPlayers.end(), passengers_.begin(), passengers_.end());
    return allPlayers;
}
std::string Car::getName() const { return name_; }
Coordinate Car::getCoordinate() const { return coordinate_; }
Player *Car::getDriver() const { return driver_; }
const std::vector<Player *> &Car::getPassengers() const { return passengers_; }
bool Car::isFull() const { return passengers_.size() + 1 > MAX_PASSENGERS; }
size_t Car::getAvailableSeats() const { return (driver_ ? 1 : 0) + (passengers_.size() - MAX_PASSENGERS); }
