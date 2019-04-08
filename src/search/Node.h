
#ifndef PROJECTPARTB_STATE_H
#define PROJECTPARTB_STATE_H


#include "Point.h"
/*
 * node is a State/Vertex in a graph (for example) can have any template of serialNum for using
 * in other application including graph searching.
 */
template <class T>
class Node {
protected:
    T* serialNum;
    double distanceFromStart;
    double fScore;
    double cost;
    bool visited;
    Node<T> *cameFrom;
    Point indexIJ;

public:
    Node(T* node) {
        this->serialNum = node;
        this->cost = 0;
        this->fScore = 0;
        this->cameFrom = nullptr;
        this->visited = false;
        this->distanceFromStart = INFINITY;
    }
    T* getNodeSerial() const {
        return this->serialNum;
    }
    const double getCost() const {
        return this->cost;
    }
    const double getFscore() const {
        return this->fScore;
    }
    const bool isVisited() const {
        return this->visited;
    }
    const double getDistanceFromStart() const {
        return this->distanceFromStart;
    }
    Point getIndexPoint() {
        return this->indexIJ;
    }
    Node<T>* getCameFrom() const {
        return this->cameFrom;
    }
    void setCost(double cost) {
        this->cost = cost;
    }
    void setFScore(double f) {
        this->fScore = f;
    }
    void setPoint(Point p) {
        this->indexIJ = p;
    }
    void setToVisit() {
        this->visited = true;
    }
    void setCameFrom(Node<T>* &father) {
        this->cameFrom = father;
    }
    void setDistanceFromStart(double distance) {
        this->distanceFromStart = distance;
    }
    bool operator == (const Node<T>* &right)  {
        return (this->getNodeSerial() == right->getNodeSerial());
    }

    bool operator > (const Node<T>* &right)  {
        return (this->getCost() > right->getCost());
    }

    bool operator < (const Node<T>* &right)  {
        return (this->getCost() < right->getCost());
    }

    ~Node() {
        if (serialNum != nullptr) {
            delete(serialNum);
            serialNum = nullptr;
        }
    }
};

#endif //PROJECTPARTB_STATE_H
