#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>  // Include for close function
#include <iostream>
#include <string>
using namespace std;
void clientCommunication(int sock){
    char message[1024] ;
    char buffer[1024] = {0};
    
    while(true) {
        fgets(message, 1024, stdin);
        send(sock, message, strlen(message), 0);  // Send message to server
        printf("Message sent\n");
        int read_val = read(sock, buffer, 1024);  // Read response from server
        if(read_val <= 0) break;  // Exit loop if read error or server disconnects

        printf("Message from server: %s\n", buffer);
    }
}