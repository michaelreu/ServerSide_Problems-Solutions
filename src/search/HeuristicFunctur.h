#ifndef PROJECTPARTB_HEURISTICFUNCTUR_H
#define PROJECTPARTB_HEURISTICFUNCTUR_H


#include "Node.h"
/*
 * class of the heuristic function of the Astar algorithm
 */
template <class T>
class HeuristicFunctor {
public:
    virtual double calculate(Node<T>* aNode, Node<T>* bNode) = 0;
    virtual ~HeuristicFunctor() = default;
};

template <class T>
class EuclidDisHeuristic : public HeuristicFunctor<T> {
public:
    virtual double calculate(Node<T>* aNode, Node<T>* bNode) {
        return pow(aNode->getIndexPoint().euclidDistance(bNode->getIndexPoint()) , 2);
    }

    virtual ~EuclidDisHeuristic() = default;
};

template <class T>
class ManhatenDisHeuristic : public HeuristicFunctor<T> {
public:
    virtual double calculate(Node<T>* aNode, Node<T>* bNode) {
        double x = abs( aNode->getIndexPoint().getX()-bNode->getIndexPoint().getX() );
        double y = abs( aNode->getIndexPoint().getY()-bNode->getIndexPoint().getY() );
        return (x+y);
    }

    virtual ~ManhatenDisHeuristic() = default;
};

#endif //PROJECTPARTB_HEURISTICFUNCTUR_H
