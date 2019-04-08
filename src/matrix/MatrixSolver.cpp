#include "../Solver.h"
#define NO_SOLUTION_MSG "no solution for that matrix"
#define RIGHT "Right,"
#define LEFT "Left,"
#define DOWN "Down,"
#define UP "Up,"

/*
 * Ctor gets a unique searcher with it's templates for matrix (graph) solving
 */
MatrixSolver::MatrixSolver(ISearcher<Point, vecOfNodes, cmpMin<Point>>* searcher){
    this->searcherAlgorithm = searcher;
}

vecOfNodes MatrixSolver::solve(iSearchable* problem){
    vecOfNodes solution;
    this->searcherAlgorithm->initNumOfEvalNodes();
    solution = this->searcherAlgorithm->search(problem);
    return solution;
}


string MatrixSolver::toString(vecOfNodes solution){
    if (solution.empty()) {
        return NO_SOLUTION_MSG;
    }
    string directions = "";
    vecOfNodes vecToPrint = solution;
    std::reverse(vecToPrint.begin(),vecToPrint.end());
    for (vecOfNodes::iterator it=vecToPrint.begin(); it!=vecToPrint.end();) {
        Point* curr = (*it++)->getNodeSerial();
        if ((it)==vecToPrint.end()) {
            break;
        }
        Point* next = (*it)->getNodeSerial();
        if(curr->getX() == next->getX()) {
            ((curr->getY() < next->getY()) ?  directions+= RIGHT : directions+= LEFT);
        } else {
            ((curr->getX() < next->getX()) ?  directions+= DOWN : directions+= UP);
        }

    }
    //erasing last "," in the string of directions = solution
    directions = directions.substr(0,directions.size()-1);
    return directions;
}

MatrixSolver::~MatrixSolver(){
    if(this->searcherAlgorithm != nullptr) {
        delete(this->searcherAlgorithm);
        this->searcherAlgorithm = nullptr;
    }
}
