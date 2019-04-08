
#ifndef PROJECTPARTB_DEPTHFIRSTSEARCH_H
#define PROJECTPARTB_DEPTHFIRSTSEARCH_H
#include "ISearcher.h"


template <class T, class Comp>
class DepthFirstSearch : public ISearcher<T,vector<Node<T>*>, Comp> {
private:
    int numOfNodesEvaluated;
public:
    DepthFirstSearch(){
        this->numOfNodesEvaluated = 0;
    }
    /*
     * DFS implementation
     */
    virtual vector<Node<T> *> search(ISearchable<T> *searchable) {
        Node<T> *initNode = searchable->getInitNode();
        initNode->setDistanceFromStart(initNode->getCost());
        bool isReachGoalNode = false;
        recursiveDFS(searchable, initNode, &isReachGoalNode);
        if(searchable->getGoalNode()->getCameFrom() != nullptr){
            return this->backTrace(searchable->getGoalNode());
        }
        vector<Node<T>*> emptyVec;
        return emptyVec;
    }

    void recursiveDFS(ISearchable<T> *searchable, Node<T> *currentNode, bool* isReachGoalNode){
        this->numOfNodesEvaluated++;
        if(currentNode == searchable->getGoalNode()){
            *isReachGoalNode = true;
            return;
        }
        currentNode->setToVisit();
        vector<Node<T> *> successors = searchable->getAllPossibleStates(currentNode);
        //iterating the succesors
        for (Node<T> *successor : successors) {
            if (!successor->isVisited()){
                double distance = currentNode->getDistanceFromStart() + successor->getCost();
                successor->setDistanceFromStart(distance);
                successor->setCameFrom(currentNode);
                recursiveDFS(searchable, successor, isReachGoalNode);
                if (*isReachGoalNode == true){
                    return;
                }
            }

        }
    }
    virtual int getNumOfNodesEvaluated(){
        return this->numOfNodesEvaluated;
    }

    virtual void initNumOfEvalNodes(){
        this->numOfNodesEvaluated = 0;
    }

};
#endif //PROJECTPARTB_DEPTHFIRSTSEARCH_H
