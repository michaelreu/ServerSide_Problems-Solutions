#ifndef PROJECT_PART_B_SERVER_H
#define PROJECT_PART_B_SERVER_H


#define SEC_TIME_OUT 2
#define BACKLOG 5
#define FIRST_ARG 1
#define MUTEX_INIT_ERROR "mutex initialization error"

#include <pthread.h>
#include <stack>
#include <unistd.h>
#include "../Utils.h"
#include "../search/AStar.h"
#include "../client/MyClientHandler.h"
#include "../Solver.h"


namespace boot {
    class Main;
};


/*
 * this class is a pure abstract class that responsible for listenting and solving problems of clients.
 * Server and ClientHandler implemented by using bridge design
 */
class Server {
    /*
     * open a server using dependency inversion with a given ClientHandler
     */
public:
    virtual void open (int port, ClientHandler* &clientHandler) = 0;
    virtual void close(int socket) = 0;
    virtual ~Server() = default;
};

struct threadData {
    pthread_t serverThread;
    bool serverThreadIsRun;
};
typedef struct threadData threadData;

struct serverParameters {
    ClientHandler* clientHandler;
    pthread_mutex_t* mutex;
    threadData* threadData1;
    int newsockfd;
};

/*
 * handling clients one by one
 */
class MySerialServer : public Server {

public:
    MySerialServer() = default;
    virtual void open (int port, ClientHandler* &clientHandler);
    virtual void close(int socket);
    virtual ~MySerialServer() = default;
};

class MyParallelServer : public Server {

public:
    MyParallelServer() = default;
    virtual void open (int port, ClientHandler* &clientHandler);
    virtual void close(int socket);
    virtual ~MyParallelServer() = default;
};


class boot::Main {

public:
    int main(int argc, char *argv[]) {
            int port = atoi(argv[FIRST_ARG]);
            ClientHandler *clientHandler = new MyClientHandler<iSearchable*, vecOfNodes>();
            Server *server = new MyParallelServer();
            server->open(port, clientHandler);
            delete (clientHandler);
            delete (server);
            return 0;
    }
};



#endif //PROJECT_PART_B_SERVER_H