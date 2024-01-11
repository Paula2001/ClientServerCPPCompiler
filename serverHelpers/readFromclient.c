#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
void readFromClient(int new_socket){
    char buffer[1024] = {0};
    const char *message = "Hello from server";
   
    while(true){
        printf("test\n");
        memset(buffer, 0, sizeof(buffer));  // Clear the buffer
        int read_val = read(new_socket, buffer, 1024);  // Read message from client
        if(read_val <= 0) break;  // Exit loop if read error or client disconnects

        printf("Message from client: %s\n", buffer);
        send(new_socket, message, strlen(message), 0);  // Send message to client
    }
}