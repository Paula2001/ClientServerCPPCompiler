#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include <semaphore.h>
#define SHM_NAME "/my_shm"
struct Shm {
    sem_t m_file_sent;
    int x = 111;
};

void createANewFileAndAppendToIt(char* buffer){
    FILE* f = fopen("./testing/aTest2.cpp", "w");
    // Write some text to the file
    fprintf(f, buffer);// Close the file
    fclose(f);
}

void compile(char* nameOfFile, char* nameOfOut){
    char command[200];
    sprintf(command, "g++ %s -o %s", nameOfFile, nameOfOut);
    FILE*f = popen(command, "r");
    pclose(f);
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
   
    
    int l_fd = shm_open(SHM_NAME, O_RDWR, 0666);

    Shm *shm = (Shm *) mmap(nullptr, sizeof(Shm), PROT_READ | PROT_WRITE, MAP_SHARED , l_fd, 0);

    if (shm == MAP_FAILED) {
        printf("failed map\n");
        // return;
    }
    int sem_value;
    // sem_getvalue(&shm->m_file_sent, &sem_value);
    // printf("My Master333: %d\n", sem_value);

    while(true){
        sem_getvalue(&shm->m_file_sent, &sem_value);
        printf("My Master: %d\n", sem_value);
        sem_getvalue(&shm->m_file_sent, &sem_value);
        char message[100];
        memset(buffer, 0, sizeof(buffer));  // Clear the buffer
        int read_val = recv(new_socket, buffer, 1024, 0);  // Read message from client
        if(read_val <= 0) break;  // Exit loop if read error or client disconnects
        printf("Reached:\n");
        sem_wait(&shm->m_file_sent);
        createANewFileAndAppendToIt(buffer);
        compile("./testing/aTest2.cpp", "aijosdf");
        printf("%s", buffer);
        sprintf(message, "%s", "aijosdf");
        send(new_socket, message, strlen(message), 0);  // Send message to client
        sem_post(&shm->m_file_sent);
    }
    
}