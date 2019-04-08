//
// Created by cs on 1/11/19.
//

#ifndef PROJECTPARTB_BREADTHFIRSTSEARCH_H
#define PROJECTPARTB_BREADTHFIRSTSEARCH_H
#include "ISearcher.h"

template <class T, class Comp>
class BreadthFirstSearch : public SearcherPriorityQueue<T,vector<Node<T>*>, Comp> {
public:
    /*
     * BreadthFirstSearch implementation
     */
    virtual vector<Node<T> *> search(ISearchable<T> *searchable) {
        Node<T> *initNode = searchable->getInitNode();
        Node<T> *goalNode = searchable->getGoalNode();
        initNode->setDistanceFromStart(initNode->getCost());
        //initializing the list of the untreated nodes with the initial node the algo start from
        this->addToOpen(initNode);
        //map of the treated nodes
        unordered_set<Node<T> *> closedMap;
        while (this->openListSize() > 0) {
            Node<T> *currentNode = this->popFromOpenList();
            // We found the node we wanted so stop and emit a path.
            if (currentNode == goalNode) {
                return this->backTrace(currentNode);
            }
            vector<Node<T> *> successors = searchable->getAllPossibleStates(currentNode);
            //iterating the succesors
            for (Node<T> *successor : successors) {
                //The node has already been processed, so skip over it
                if (closedMap.count(successor)){
                    continue;
                }
                if (!(this->contain(successor))) {
                    double distance = currentNode->getDistanceFromStart() + successor->getCost();
                    successor->setDistanceFromStart(distance);
                    successor->setCameFrom(currentNode);
                    this->addToOpen(successor);
                }
            }
            closedMap.insert(currentNode);
        }
        vector<Node<T>*> emptyVec;
        return emptyVec;
    }
};
#endif //PROJECTPARTB_BREADTHFIRSTSEARCH_H
