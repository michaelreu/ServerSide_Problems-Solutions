#include "Server.h"

void* runServer(void *arg) {
    //MySerialServer mySerialServer = MySerialServer();
    struct serverParameters* serverPar = (struct serverParameters*) arg;
    StreamManager *streamManager = new StreamManager(serverPar->newsockfd);
    if (serverPar->newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    //call to function handleClient
    serverPar->clientHandler->handleClient(streamManager, serverPar->mutex);
    if(serverPar!= nullptr) {
        delete(serverPar);
        serverPar = nullptr;
    }
    if(streamManager!= nullptr) {
        delete(streamManager);
        streamManager = nullptr;
    }
    return nullptr;
}

void MySerialServer::open(int port, ClientHandler* &clientHandler) {
    pthread_t serverThread;
    pthread_mutex_t mutex;
    if (pthread_mutex_init(&mutex,NULL)) {
        cout<<MUTEX_INIT_ERROR<<endl;
    }
    int   clilen, sockfd ,newsockfd;
    string tempStr;
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
    newsockfd = accept(sockfd, (struct sockaddr*) &clientAddress, (socklen_t*) &clilen);
    fcntl(sockfd,F_SETFL,O_NONBLOCK);
    short times = 0;
    while (true) {
        if (!(newsockfd < 0)) {
            //cout << "accept success" << endl;
            // need to add  timeout condition
            //StreamManager *streamManager = new StreamManager(newsockfd);
            struct serverParameters *params = new serverParameters();
            params->clientHandler = clientHandler;
            params->newsockfd = newsockfd;
            pthread_create(&serverThread, nullptr, runServer, params);
            pthread_join(serverThread, nullptr);
        }
        ++times;
        if (times> SEC_TIME_OUT) {
            break;
        }
        sleep(1);
        newsockfd = accept(sockfd, (struct sockaddr*) &clientAddress, (socklen_t*) &clilen);
    }
    close(sockfd);
}

void MySerialServer::close(int socket) {
    shutdown(socket, SHUT_RDWR);
    ::close(socket);
}