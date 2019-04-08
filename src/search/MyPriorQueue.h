#ifndef PROJECTPARTB_MYPRIORQUEUE_H
#define PROJECTPARTB_MYPRIORQUEUE_H

#include <queue>
#include <algorithm>
#include "Node.h"
using std::priority_queue;
using std::vector;

/*
 * additional functunality to priority queue: contain and remove added
 */
template <class T, class Comp>
class MyPriorQueue : public priority_queue<  Node<T>* ,vector<Node<T>*>, Comp > {
public:
    /*
     * check if a node is in the queue, since there is not implemented method of it in
     */
    bool contain(Node<T>* node) {
        auto it = std::find(this->c.begin(), this->c.end(), node);
        return (it != this->c.end());
    }
    /*
     * removing node in the queue and making heap without the node removed
     */
    void remove(Node<T>* nodeToRemove) {
        auto it = std::find(this->c.begin(), this->c.end(), nodeToRemove);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(),this->c.end(), this->comp);
        }
    }
};
#endif //PROJECTPARTB_MYPRIORQUEUE_H
