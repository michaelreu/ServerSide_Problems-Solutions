
#ifndef PROJECTPARTB_PROBLEMCREATOR_H
#define PROJECTPARTB_PROBLEMCREATOR_H

#define TWO 2

#include "search/Node.h"
#include "search/ISearchable.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::pair;
using std::string;
using std::getline;

/*
 * class to create problems, to separate the problem creation .
 */
template <class Problem>
class ProblemCreator {
    virtual Problem getProblem(string str) = 0;
};

/*
 * this class has all the members that matrix needs
 */
class MatrixCreator : public ProblemCreator<ISearchable<Point>*> {
private:
    map<Point,Node<Point>*> mapOfNodes;
    Node<Point>* startPoint;
    Node<Point>* endPoint;

public:
    virtual ISearchable<Point>* getProblem(string str);

};




#endif //PROJECTPARTB_PROBLEMCREATOR_H
