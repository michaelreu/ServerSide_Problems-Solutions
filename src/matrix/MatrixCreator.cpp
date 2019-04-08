#include "../ProblemCreator.h"

/*
 * creates a matrix from an input of user, gets a string returns a matrix which is Isearchable Object
 */
ISearchable<Point>* MatrixCreator::getProblem(string str){
    std::stringstream streamData(str);
    int i = 0, j = 0;
    int pFirst[TWO], pEnd[TWO];
    string row = "", nodes = "", first = "", end = "";
    vector<string> lines;
    while (getline(streamData, row, LINE_SEPARATOR)) {
        lines.push_back(row);
        first = end;
        end = row;
    }
    for (vector<string>::const_iterator it = lines.begin(); it != lines.end(); ++it) {
        if (*it != first) {
            std::stringstream streamLine(*it);
            while (getline(streamLine, nodes, COMMA_CHAR)) {
                Point* indexIJ = new Point(i, j);
                //auto indexIJ = std::make_pair(i,j);
                auto *temp = new Node<Point>(indexIJ);
                //MatrixNode *temp  = new MatrixNode(indexIJ);
                temp->setCost(std::stod(nodes));
                //added to set the point index
                temp->setPoint(*indexIJ);
                this->mapOfNodes[*indexIJ] = temp;
                //this->vecOfNode.push_back(temp);
                j++;
            }
            j = 0;
            i++;
        } else {
            break;
        }
    }
    // get start point
    i = 0;
    std::stringstream streamFirst(first);
    while (getline(streamFirst,first, COMMA_CHAR))
    {
       pFirst[i] = stod(first);
       i++;
    }
    Point* startP = new Point(pFirst[0], pFirst[1]);
    map <Point, Node<Point>*>::iterator itMapOfNodes;
    map <Point, Node<Point>*> mapOfNodes = this->mapOfNodes;
    for(itMapOfNodes = mapOfNodes.begin(); itMapOfNodes != mapOfNodes.end(); itMapOfNodes++) {
        this->startPoint = mapOfNodes[*startP];
    }
    // get end point
    i = 0;
    std::stringstream streamEnd(end);
    while (getline(streamEnd,end, COMMA_CHAR))
    {
        pEnd[i] = stod(end);
        i++;
    }
    Point* endP = new Point(pEnd[0], pEnd[1]);
    for(itMapOfNodes = mapOfNodes.begin(); itMapOfNodes != mapOfNodes.end(); itMapOfNodes++) {
        this->endPoint = mapOfNodes[*endP];
    }

    ISearchable<Point>* problem = new Matrix(this->startPoint, this->endPoint, this->mapOfNodes);
    // allocated points should be destruct
    if(startP!= nullptr) {
        delete(startP);
        startP = nullptr;
    }
    if(endP!= nullptr) {
        delete(endP);
        endP = nullptr;
    }
    return problem;
}