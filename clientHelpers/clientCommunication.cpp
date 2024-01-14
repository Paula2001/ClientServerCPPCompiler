#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>  // Include for close function
#include <iostream>
#include <string>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>

#define SHM_NAME "SHARED"

using namespace std;


void sendMessage(int sock){
    char message[1024] ;
    char buffer[1024];
    FILE *file;
    memset(message, 0, sizeof(message));  // Clear the buffer
    memset(buffer, 0, sizeof(buffer));  // Clear the buffer
    

    if(fgets(message, 1024, stdin) != NULL){
        size_t length = strlen(message);
        message[length - 1] = '\0'; // INF: terminate the bytes
        
        file = fopen(message, "rb"); // TODO : add this to a new function
        if (file == NULL) {
            perror("File not found");
            exit(1);
        }

        while (!feof(file)) {
            int bytesRead = fread(buffer, 1, 1024, file);
            // buffer[strlen(buffer) - 1] = '\0';
            if (bytesRead > 0) {
                send(sock, buffer, bytesRead, 0);
            }
        }
    };
}

void readCompiledFileOut(char* path){
    const char* type = "r";
    char command[strlen(path)+2];
    sprintf(command, "./%s", path);
    char s[1024];
    FILE* f = popen(command, type);
    auto x = 1;
    char* zz = fgets(s, 1024,f);
    printf("This is a test ==== %s %s\n",s, path);
    pclose(f);
}

void clientCommunication(int sock){
    char message[1024] ;
    char buffer[1024] = {0};
   
    while(true) {
        memset(buffer, 0, sizeof(buffer));  // Clear the buffer
        sendMessage(sock);
        
        printf("Message sent\n");
        int read_val = read(sock, buffer, 1024);  // Read response from server
        if(read_val <= 0) break;  // Exit loop if read error or server disconnects
        readCompiledFileOut(buffer);
    }
}