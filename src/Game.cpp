#include "../include/Game.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_set>

namespace {
    constexpr int COORD_MIN = 0;
    constexpr int COORD_MAX = 100;

    std::string generateName(const std::string &prefix, size_t index) {
        std::ostringstream oss;
        oss << prefix << std::setw(4) << std::setfill('0') << index;
        return oss.str();
    }
} // namespace

Game::Game() : rd_(), gen_(rd_()), isFillingCars_(false) {}

void Game::generatePlayers(size_t count) {
    std::lock_guard<std::mutex> lock(playersMutex_);

    players_.clear();
    players_.reserve(count);

    std::uniform_int_distribution<int> coordDist(COORD_MIN, COORD_MAX);

    for (size_t i = 0; i < count; ++i) {
        players_.emplace_back(generateName("Player", i + 1), Coordinate(coordDist(gen_), coordDist(gen_)));
    }
}

void Game::generateCars(size_t count) {
    std::lock_guard<std::mutex> lock(carsMutex_);

    cars_.clear();
    cars_.reserve(count);

    std::uniform_int_distribution<int> coordDist(COORD_MIN, COORD_MAX);

    for (size_t i = 0; i < count; ++i) {
        cars_.emplace_back(generateName("Car", i + 1), Coordinate(coordDist(gen_), coordDist(gen_)));
    }
}

void Game::fillCars() {
    if (players_.empty() || cars_.empty()) {
        return;
    }

    setFillingStatus(true);

    try {
        std::lock_guard<std::mutex> playersLock(playersMutex_);
        std::lock_guard<std::mutex> carsLock(carsMutex_);

        // Создаём очередь доступных игроков
        std::queue<Player *> availablePlayers;
        for (auto &player: players_) {
            player.setAssigned(false);
            availablePlayers.push(&player);
        }

        for (auto &car: cars_) {
            if (availablePlayers.empty())
                break;

            auto *driver = availablePlayers.front();
            availablePlayers.pop();

            if (car.assignDriver(driver)) {
                driver->setAssigned(true);
                driver->setCoordinate(car.getCoordinate());

                while (!availablePlayers.empty() && !car.isFull()) {
                    auto *passenger = availablePlayers.front();
                    availablePlayers.pop();

                    if (car.addPassenger(passenger)) {
                        passenger->setAssigned(true);
                        passenger->setCoordinate(car.getCoordinate());
                    }
                }
            }
        }
    } catch (...) {
        setFillingStatus(false);
        throw;
    }

    setFillingStatus(false);
}

void Game::displayRandomCars(size_t count) {
    std::lock_guard<std::mutex> lock(carsMutex_);

    if (cars_.empty() || count == 0) {
        std::cout << "No cars to display.\n";
        return;
    }

    count = std::min(count, cars_.size());
    std::vector<size_t> indices(cars_.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), gen_);

    for (size_t i = 0; i < count; ++i) {
        const auto &car = cars_[indices[i]];
        displayCarInfo(car);
    }
}

void Game::displayPlayersInRadius(const Car &car, double radius) {
    if (radius <= 0) {
        std::cout << "Invalid radius value.\n";
        return;
    }

    std::lock_guard<std::mutex> lock(playersMutex_);

    const double radiusSquared = radius * radius;
    std::vector<std::pair<const Player *, double>> nearbyPlayers;
    nearbyPlayers.reserve(players_.size() / 4);

    const auto &carCoord = car.getCoordinate();

    for (const auto &player: players_) {
        const auto &playerCoord = player.getCoordinate();
        double dx = carCoord.getX() - playerCoord.getX();
        double dy = carCoord.getY() - playerCoord.getY();
        double distSquared = dx * dx + dy * dy;

        if (distSquared <= radiusSquared) {
            nearbyPlayers.emplace_back(&player, std::sqrt(distSquared));
        }
    }

    if (nearbyPlayers.empty()) {
        std::cout << "No players found within radius " << radius << " of " << car.getName() << ".\n";
        return;
    }

    std::sort(nearbyPlayers.begin(), nearbyPlayers.end(),
              [](const auto &a, const auto &b) { return a.second < b.second; });

    std::cout << "Players within radius " << radius << " of " << car.getName() << ":\n";
    for (const auto &[player, dist]: nearbyPlayers) {
        std::cout << std::fixed << std::setprecision(2) << player->getNickname() << " (distance: " << dist << ")\n";
    }
}

void Game::displayCarInfo(const Car &car) const {
    std::cout << "\n=== " << car.getName() << " ===\n"
              << "Position: (" << car.getCoordinate().getX() << ", " << car.getCoordinate().getY() << ")\n";

    if (const auto *driver = car.getDriver()) {
        std::cout << "Driver: " << driver->getNickname() << "\n";
    } else {
        std::cout << "No driver assigned\n";
    }

    const auto &passengers = car.getPassengers();
    if (!passengers.empty()) {
        std::cout << "Passengers (" << passengers.size() << "):\n";
        for (const auto *passenger: passengers) {
            std::cout << "  - " << passenger->getNickname() << "\n";
        }
    } else {
        std::cout << "No passengers\n";
    }
}

std::vector<Player> &Game::getPlayers() {
    std::lock_guard<std::mutex> lock(playersMutex_);
    return players_;
}

std::vector<Car> &Game::getCars() {
    std::lock_guard<std::mutex> lock(carsMutex_);
    return cars_;
}

bool Game::isFillingInProgress() const { return isFillingCars_.load(std::memory_order_acquire); }

void Game::setFillingStatus(bool status) { isFillingCars_.store(status, std::memory_order_release); }
