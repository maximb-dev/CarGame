#include "../include/Player.h"

Player::Player(const std::string &nickname, const Coordinate &coordinate) :
    nickname_(nickname), coordinate_(coordinate), isAssigned_(false) {}
std::string Player::getNickname() const { return nickname_; }
Coordinate Player::getCoordinate() const { return coordinate_; }
void Player::setCoordinate(const Coordinate &newCoordinate) { coordinate_ = newCoordinate; }
bool Player::getIsAssigned() const { return isAssigned_; }
void Player::setAssigned(bool assigned) { isAssigned_ = assigned; }
