
#ifndef PROJECT_PART_B_MYCLIENTHENDLER_H
#define PROJECT_PART_B_MYCLIENTHENDLER_H

#define INVALID_INPUT "invalid input"
#define LINE_SEPARATOR '|'

#include "ClientHandler.h"
#include "../ProblemCreator.h"
#include "../Solver.h"
#include "../search/BestFirstSearch.h"
#include "../search/BreadthFirstSearch.h"
#include "../search/AStar.h"
#include "../search/DepthFirstSearch.h"

typedef ISearchable<Point>* searchableWithIndexes;
template <class Problem, class Solution>
/*
 * handle input of a matrix represented with lines of numbers, seperated by "," and has starting and ending point
 * which represented by their matrix indexes
 * converting the lines into one string.
 */
class MyClientHandler: public  ClientHandler {
private:
    Solver<Problem, Solution> *solver;
    CacheManager *cacheManager;
    vector<searchableWithIndexes> vecOfProblemsToFree;
public:
    MyClientHandler(){
        this->solver = new MatrixSolver(new AStar<Point,cmpMin<Point> >(new ManhatenDisHeuristic<Point>()));
        this->cacheManager = new FileCacheManager(MATRIX_FILE);
    }

    virtual void handleClient(StreamManager* streamManager, pthread_mutex_t* mutex) {
        string problemStr = "", solutionStr = "";
        Solution solution;
        problemStr = "";
        solutionStr = "";
        string line = streamManager->readLineFromClient();
            while ((line != ENDLINE1) && (line != ENDLINE2)) {
                problemStr += line;
                problemStr += LINE_SEPARATOR;
                line = streamManager->readLineFromClient();
            }
            MatrixCreator createProblem;
            ISearchable<Point> *problem;
            //pthread_mutex_lock(mutex);
            bool solutionExist = this->cacheManager->isSolutionExist(problemStr);
            //pthread_mutex_unlock(mutex);
            if (solutionExist) {
                // take from cache
                pthread_mutex_lock(mutex);
                solutionStr = this->cacheManager->getSolution(problemStr);
                pthread_mutex_unlock(mutex);
            }
            else {
                try {
                    problem = createProblem.getProblem(problemStr);
                } catch (exception e) {
                    string wrong = INVALID_INPUT;
                    streamManager->sendSolutionToClient(wrong);
                    return;
                }
                vecOfProblemsToFree.push_back(problem);
                solution = solver->solve(problem);
                solutionStr = solver->toString(solution);
                pthread_mutex_lock(mutex);
                this->cacheManager->saveSolution(problemStr, solutionStr);
                pthread_mutex_unlock(mutex);
                //cout << solutionStr << endl;
            }
            streamManager->sendSolutionToClient(solutionStr);
    }

    /*
     * DTOR
     */
    virtual ~MyClientHandler() {
        if (this->solver != nullptr) {
            delete(this->solver);
            this->solver = nullptr;
        }
        if (this->cacheManager != nullptr) {
            delete(this->cacheManager);
            this->cacheManager = nullptr;
        }
        for(searchableWithIndexes searchableToFree : this->vecOfProblemsToFree) {
            if(searchableToFree != nullptr) {
                delete(searchableToFree);
                searchableToFree = nullptr;
            }
        }
    }
};



#endif //PROJECT_PART_B_MYCLIENTHENDLER_H
