
#ifndef PROJECTPARTB_STREAMMANAGER_H
#define PROJECTPARTB_STREAMMANAGER_H

#define BUFF_SIZE 1024

#include <string.h>
#include <unistd.h>
#include <string>
/*
 * class that responsibles for reading and writing lines to user through socket number
 */
using std::string;
class StreamManager {
private:
    int socketNumber;
public:
    StreamManager(int socketNum);
    string readLineFromClient();
    void sendSolutionToClient(string &str);
    ~StreamManager() = default;
};
#endif //PROJECTPARTB_STREAMMANAGER_H
