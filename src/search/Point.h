#ifndef PROJECTPARTB_POINT_H
#define PROJECTPARTB_POINT_H

#include <math.h>
class Point {
private:
    int x;
    int y;
public:
    Point() {this->x = 0, this->y = 0;}
    Point(int x, int y){this->x = x; this->y = y;}
    int getX() const{return this->x;}
    int getY() const{return this->y;}
    void setX (int x){this->x = x;}
    void setY (int y){this->y = y;}
    bool operator ==(const Point other) const {
        return ((this->getX() == other.getX())&& this->getY() == other.getY());
    }
    void operator =(Point other){
        this->setX(other.getX());
        this->setY(other.getY());
    }

    bool operator<(const Point &rhs) const {
        if (x < rhs.x) {
            return true;
        } if (rhs.x < x) {
            return false;
        }
        return (y < rhs.y);
    }

    bool operator>(const Point &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Point &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Point &rhs) const {
        return !(*this < rhs);
    }

    double euclidDistance(Point other) {
        double disX = pow((this->x - other.getX()),2);
        double disY = pow((this->y - other.getY()),2);
        double dis = sqrt(disX+disY);
        return dis;
    }
    virtual ~Point() = default;
};


#endif //PROJECTPARTB_POINT_H
