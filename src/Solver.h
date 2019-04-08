#ifndef PROJECTPARTB_SOLVER_H
#define PROJECTPARTB_SOLVER_H

#include <string>
#include <vector>

#include "search/ISearcher.h"
#include "search/Node.h"

using std::string;
template <class P, class S>
class Solver {
public:
    virtual S solve(P problem) = 0;
    virtual string toString(S solution) = 0;
    virtual ~Solver() = default;
};

typedef ISearchable<Point> iSearchable;
typedef vector<Node<Point>*> vecOfNodes;

/*
 * struct to define the comparing order (minimum heap order)
 */
template <class T>
struct cmpMin {
    bool operator() (Node<T>* left, Node<T>* right) {
        return (left->getDistanceFromStart() > right->getDistanceFromStart());
    }
};

class MatrixSolver : public Solver<iSearchable* ,vecOfNodes>{
private:
    ISearcher<Point, vecOfNodes, cmpMin<Point>>* searcherAlgorithm;
public:
    MatrixSolver(ISearcher<Point, vecOfNodes, cmpMin<Point>>* searcher);
    virtual vecOfNodes solve(iSearchable* problem);
    virtual string toString(vecOfNodes solution);
    virtual ~MatrixSolver();
};

#endif //PROJECTPARTB_SOLVER_H
