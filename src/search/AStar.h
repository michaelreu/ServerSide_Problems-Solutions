#ifndef PROJECTPARTB_ASTAR_H
#define PROJECTPARTB_ASTAR_H

#include "ISearcher.h"

template <class T, class Comp>
class AStar : public SearcherPriorityQueue<T, vector<Node<T>*>, Comp> {
private:
    //gets
    HeuristicFunctor<T> *heuristicFunc;
    //Class of interface heuristic function;
public:
    /*
     * Ctor using strategy pattern - user can decide which heuristic function it will use
     */
    AStar(HeuristicFunctor<T> *hFunc) {
        this->heuristicFunc = hFunc;
    }
    /*
     * implementation of A* Algorithm
     */
    virtual vector<Node<T>*> search(ISearchable<T> *searchable) {
        Node<T>* initNode = searchable->getInitNode();
        double initCost = initNode->getCost();
        Node<T>* goalNode = searchable->getGoalNode();
        double heuristicDistance = this->heuristicFunc->calculate(initNode,goalNode);
        //initNode->setDistanceFromStart(initNode->getCost() + heuristicDistance);
        initNode->setDistanceFromStart(0);
        initNode->setFScore(initNode->getDistanceFromStart() + heuristicDistance);
        this->addToOpen(initNode);
        //map of the treated nodes
        unordered_set< Node<T>* > closedMap;
        while (this->openListSize() > 0) {
            Node<T> *currentNode = this->popFromOpenList();
            if (currentNode == goalNode) {
                currentNode->setDistanceFromStart(currentNode->getDistanceFromStart() + initCost);
                return this->backTrace(currentNode);
            }
            closedMap.insert(currentNode);
            vector<Node<T>*> successors = searchable->getAllPossibleStates(currentNode);
            for (Node<T>* successor : successors) {
                double tentativeGscore = currentNode->getDistanceFromStart() + successor->getCost();
                //double pureDistance = currentNode->getDistanceFromStart() + successor->getCost(); // tentativeGscore
                if ( (closedMap.find(successor) != closedMap.end()) || tentativeGscore >= successor->getDistanceFromStart()) {
                    continue;
                }
                if ( !(this->openList.contain(successor)) || tentativeGscore < successor->getDistanceFromStart())  {
                    successor->setCameFrom(currentNode);
                    //successor->setDistanceFromStart(pureDistance);
                    successor->setDistanceFromStart(tentativeGscore);
                    heuristicDistance = this->heuristicFunc->calculate(successor,goalNode);
                    successor->setFScore(tentativeGscore + heuristicDistance);
                    if(!(this->openList.contain(successor))) {
                        this->addToOpen(successor);
                    }
                }
            }
        }
        vector<Node<T>*> emptyVec;
        return emptyVec;
    }

    virtual ~AStar(){
        if(heuristicFunc != nullptr){
            delete(heuristicFunc);
            heuristicFunc = nullptr;
        }
    }
};
#endif //PROJECTPARTB_ASTAR_H
