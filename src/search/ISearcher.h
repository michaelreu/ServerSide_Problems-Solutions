
#ifndef PROJECTPARTB_ISEARCHER_H
#define PROJECTPARTB_ISEARCHER_H

#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <iostream>
#include "ISearchable.h"
#include "MyPriorQueue.h"
#include "HeuristicFunctur.h"

using std::priority_queue;
using std::unordered_map;
using std::unordered_set;

template <class T, class Solution, class Comp>
class ISearcher {
public:
    //not sure about search func
    virtual Solution search(ISearchable<T>* searchable) = 0;
    virtual int getNumOfNodesEvaluated() = 0;
    virtual void initNumOfEvalNodes() = 0;
    vector<Node<T>*> backTrace(Node<T>* last) {
        Node<T>* curr = last;
        vector<Node<T>*> pathVec;
        while (curr->getCameFrom() != nullptr) {
            pathVec.push_back(curr);
            curr = curr->getCameFrom();
        }
        pathVec.push_back(curr);
        return pathVec;
    }
    virtual ~ISearcher() = default;
};


/*
 * implememtation of priority queue - algorithms that use prioQue derived from this class
 */
template <class T, class Solution, class Comp>
class SearcherPriorityQueue : public ISearcher<T,Solution, Comp> {
protected:
    //initializes minHeap
    MyPriorQueue<T,Comp> openList;
    int evaluatedNodes = 0;

    unsigned long openListSize() {
        return openList.size();
    }

    Node<T>* popFromOpenList() {
        ++(this->evaluatedNodes);
        Node<T>* nodeToBePoped = (this->openList.top());
        this->openList.pop();
        return nodeToBePoped;
    }

    virtual void initNumOfEvalNodes(){
        this->evaluatedNodes = 0;
    }

    virtual void addToOpen(Node<T>* node) {
        this->openList.push(node);
    }

    virtual void removeFromOpen(Node<T>* node) {
        this->openList.remove(node);
    }

    bool contain(Node<T>* node) {
        return this->openList.contain(node);
    }

public:
    SearcherPriorityQueue() {
        this->evaluatedNodes = 0;
    }

    //not virtual so it cant be override
    int getNumOfNodesEvaluated() {
        return (this->evaluatedNodes);
    }

    virtual Solution search(ISearchable<T> *searchable) = 0;

    virtual ~SearcherPriorityQueue() {
        this->openList.empty();
    }
};




#endif //PROJECTPARTB_ISEARCHER_H
