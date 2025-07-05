#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
private:
    int x_;
    int y_;

public:
    Coordinate(int x = 0, int y = 0);
    double distanceTo(const Coordinate& other) const;
    int getX() const;
    int getY() const;
    void setX(int newX);
    void setY(int newY);
};

#endif // COORDINATE_H