#include "Server.h"




void* runServers(void *arg) {
    //MySerialServer mySerialServer = MySerialServer();
    struct serverParameters* serverPar = (struct serverParameters*) arg;
    StreamManager *streamManager = new StreamManager(serverPar->newsockfd);
    if (serverPar->newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    //call to function handleClient
    serverPar->clientHandler->handleClient(streamManager, serverPar->mutex);
    serverPar->threadData1->serverThreadIsRun = false;
    shutdown(serverPar->newsockfd, SHUT_RDWR);
    close(serverPar->newsockfd);
    delete(serverPar);
    serverPar = nullptr;
    delete(streamManager);
    streamManager = nullptr;
    return nullptr;
}

void MyParallelServer::open(int port, ClientHandler* &clientHandler) {
    stack<threadData> stackOfThreads;
    pthread_mutex_t mutex;
    if (pthread_mutex_init(&mutex,NULL)) {
        cout<<MUTEX_INIT_ERROR<<endl;
    }
    int clilen, sockfd, newsockfd;
    struct sockaddr_in serverAddress, clientAddress;

    //setup starts here
    // First call to socket() function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    // Initialize socket structure
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);


    // Now bind the host address using bind() call.
    if (bind(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    // Now start listening for the clients, here process will
    //go in sleep mode and will wait for the incoming connection

    listen(sockfd, BACKLOG);
    //setup ends here
    clilen = sizeof(clientAddress);
    newsockfd = accept(sockfd, (struct sockaddr *) &clientAddress, (socklen_t *) &clilen);
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    short times = 0;
    while (true) {
        if (!(newsockfd < 0)) {
            stackOfThreads.push(threadData{pthread_t(), true});
            struct serverParameters *params = new serverParameters();
            params->clientHandler = clientHandler;
            params->mutex = &mutex;
            params->newsockfd = newsockfd;
            params->threadData1 = &stackOfThreads.top();
            pthread_create((&stackOfThreads.top().serverThread) , nullptr, runServers, params);
        } else {
            if (times > SEC_TIME_OUT) {
                break;
            }
            sleep(1);
            ++times;
        }
        newsockfd = accept(sockfd, (struct sockaddr *) &clientAddress, (socklen_t *) &clilen);
    }
    // close all threads
    while(!stackOfThreads.empty()){
        threadData* temp = &stackOfThreads.top();
        if (temp->serverThreadIsRun) {
            pthread_join(temp->serverThread, nullptr);
        }
        stackOfThreads.pop();
    }
    MyParallelServer::close(sockfd);
}

void MyParallelServer::close(int socketfd) {
    shutdown(socketfd, SHUT_RDWR);
    ::close(socketfd);
}