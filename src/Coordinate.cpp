#include "../include/Coordinate.h"
#include <cmath>


Coordinate::Coordinate(int x, int y) : x_(x), y_(y) {}

double Coordinate::distanceTo(const Coordinate &other) const {
    return sqrt((pow(x_ - other.x_, 2) + pow(y_ - other.y_, 2)));
}

int Coordinate::getX() const { return x_; }

int Coordinate::getY() const { return y_; }
void Coordinate::setX(int newX) { x_ = newX; }
void Coordinate::setY(int newY) { y_ = newY; }
