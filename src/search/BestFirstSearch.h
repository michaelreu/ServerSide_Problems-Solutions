
#ifndef PROJECTPARTB_BESTFIRSTSEARCH_H
#define PROJECTPARTB_BESTFIRSTSEARCH_H

#include "ISearcher.h"

template <class T, class Comp>
class BestFirstSearch : public SearcherPriorityQueue<T,vector<Node<T>*>, Comp> {
public:
    BestFirstSearch() = default;
    /*
     * BestFirstSearch implementation
     */
    virtual vector<Node<T>*> search(ISearchable<T> *searchable){
        Node<T>* initNode = searchable->getInitNode();
        Node<T>* goalNode = searchable->getGoalNode();
        initNode->setDistanceFromStart(initNode->getCost());
        //initializing the list of the untreated nodes with the initial node the algo start from
        this->addToOpen(initNode);
        //map of the treated nodes
        unordered_set< Node<T>* > closedMap;
        while (this->openListSize() > 0) {
            //Node<T> *currentNode = this->openList->top();
            Node<T> *currentNode = this->popFromOpenList();
            closedMap.insert(currentNode);
            if (currentNode == goalNode) {
                return this->backTrace(currentNode);
            }
            vector<Node<T>*> successors = searchable->getAllPossibleStates(currentNode);
            //iterating the succesors
            for (Node<T>* successor : successors) {
                double distance = currentNode->getDistanceFromStart() + successor->getCost();
                //if successor is not in the closedMap and not in the openList
                if ((closedMap.find(successor)==(closedMap.end())) && !(this->contain(successor))) {
                    successor->setDistanceFromStart(distance);
                    successor->setCameFrom(currentNode);
                    this->addToOpen(successor);
                }
                else if(distance <= successor->getDistanceFromStart()) {
                    if (!this->contain(successor)) {
                        this->addToOpen(successor);
                    } else {
                        successor->setDistanceFromStart(distance);
                        this->removeFromOpen(successor);
                        //when node enters to priority queue it updates the heap
                        this->addToOpen(successor);
                    }
                }
            }
        }
        vector<Node<T>*> emptyVec;
        return emptyVec;
    }
};

#endif //PROJECTPARTB_BESTFIRSTSEARCH_H
