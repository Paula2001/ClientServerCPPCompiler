#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void createANewFileAndAppendToIt(char* buffer){
    FILE* f = fopen("./testing/aTest2.cpp", "w");
    // Write some text to the file
    fprintf(f, buffer);// Close the file
    fclose(f);
}

void compile(){
    system("g++ ./testing/aTest2.cpp -o test3");
}

void readAndSendCompiledFile(int sock){
    char* buffer[1024];
    FILE* file = fopen("./test", "rb");
    while (!feof(file)) {
        int bytesRead = fread(buffer, 1, 1024, file);
        // buffer[strlen(buffer) - 1] = '\0';
        if (bytesRead > 0) {
            send(sock, buffer, bytesRead, 0);
        }
    }
}

void readFromClient(int new_socket){
    char buffer[1024] = {0};
    const char *message = "Hello from server";
    pid_t x = fork();
    if(x < 0){
        printf("process failed to bond");
        exit(EXIT_FAILURE);
    }
    if(x == 0){
        
        while(1){
            memset(buffer, 0, sizeof(buffer));  // Clear the buffer
            int read_val = recv(new_socket, buffer, 1024, 0);  // Read message from client
            if(read_val <= 0) break;  // Exit loop if read error or client disconnects
            createANewFileAndAppendToIt(buffer);
            compile();
            printf("%s", buffer);
            send(new_socket, message, strlen(message), 0);  // Send message to client
        }
    }
}