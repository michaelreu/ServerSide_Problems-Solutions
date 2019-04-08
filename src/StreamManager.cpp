
#include "StreamManager.h"

#include <cstring>
StreamManager::StreamManager(int socketNum) {
    this->socketNumber = socketNum;
}

string StreamManager::readLineFromClient() {
    char buffer[BUFF_SIZE];
    int n = 0;
    bzero(buffer, BUFF_SIZE);
    n = read(this->socketNumber, buffer, BUFF_SIZE - 1);
    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
    return string(buffer);
}


void StreamManager::sendSolutionToClient(string &str) {
    int n = 0;
    const char* buffer = str.c_str();
    n = write(this->socketNumber, buffer, strlen(buffer));
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
    std::memset((char*)buffer, 0, sizeof(buffer));
}