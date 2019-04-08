#ifndef PROJECTPARTB_CLIENTHANDLER_H
#define PROJECTPARTB_CLIENTHANDLER_H

#include "../Solver.h"
#include "../CacheManager.h"
#include "../StreamManager.h"
#include <string>
#define ENDLINE1 "end"
#define ENDLINE2 "end\n"
#define MATRIX_FILE "matrix.txt"

using namespace std;
/*
 * pure abstract class
 * Server and ClientHandler implemented by using bridge design.
 * MyClientHandler implements this class
 */
class ClientHandler {
public:
    //parameter string should be a socket
    virtual void handleClient(StreamManager* streamManager, pthread_mutex_t* mutex) = 0;
    virtual ~ClientHandler() = default;
};

#endif //PROJECTPARTB_CLIENTHANDLER_H
