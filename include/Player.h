#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Coordinate.h"

class Player {
private:
    std::string nickname_;
    Coordinate coordinate_;
    bool isAssigned_;

public:
    Player(const std::string& nickname, const Coordinate& coordinate);
    std::string getNickname() const;
    Coordinate getCoordinate() const;
    void setCoordinate(const Coordinate& newCoordinate);
    bool getIsAssigned() const;
    void setAssigned(bool assigned);
};

#endif // PLAYER_H