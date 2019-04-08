
#ifndef PROJECTPARTB_ISEARCHABLE_H
#define PROJECTPARTB_ISEARCHABLE_H
#define BLOCK -1
#include "Point.h"
#include "Node.h"
#include <algorithm>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::pair;

/*
 * Isearchable has the funcunality of searchable object
 */
template <class T>
class ISearchable {
public:
    virtual Node<T>* getInitNode() = 0;
    virtual Node<T>* getGoalNode() = 0;
    virtual vector<Node<T>*> getAllPossibleStates(Node<T>* state) = 0;
    virtual ~ISearchable()= default;
};

class Matrix : public ISearchable<Point> {
private:
    Node<Point> *initialNode;
    Node<Point> *goalNode;
    map<Point,Node<Point>*> nodesMap;

public:
    Matrix(Node<Point>* &initNode,  Node<Point>* &goalNode, map<Point,Node<Point>*> mapOfNodes) {
        this->nodesMap = mapOfNodes;
        this->initialNode = initNode;
        this->goalNode = goalNode;
    }

    virtual Node<Point> *getInitNode() {
        return this->initialNode;
    }

    virtual Node<Point> *getGoalNode() {
        return this->goalNode;
    }
    /*
     * successors can be on the right/left side or up and down
     */
    virtual vector<Node<Point>*> getAllPossibleStates(Node<Point> *currNode) {
        vector<Node<Point>* > vecOfSuccessors;
        int i = currNode->getIndexPoint().getX();
        int j = currNode->getIndexPoint().getY();
        Point p1 = Point(i+1,j);
        Point p2 = Point(i,j+1);
        Point p3 = Point(i-1,j);
        Point p4 =Point(i,j-1);
        vector<Point> potentialNeighbours = { p1 , p2, p3 , p4};
        for (Point pNeigh : potentialNeighbours) {
            if (this->nodesMap.count(pNeigh) == 1) {
                Node<Point>* node = this->nodesMap[pNeigh];
                if (node->getCost() != BLOCK) {
                    vecOfSuccessors.push_back(node);
                }
            }
        }
        return vecOfSuccessors;
    }

    virtual ~Matrix() {
        Node<Point>* node;
        map <Point, Node<Point>* >::iterator itOfMap;
        for(itOfMap = this->nodesMap.begin(); itOfMap != this->nodesMap.end(); itOfMap++){
            node = itOfMap->second;
            if (node != nullptr) {
                delete(node);
                node = nullptr;
            }
        }
    }
};
#endif //PROJECTPARTB_ISEARCHABLE_H
