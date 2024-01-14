#include "./serverHelpers/socket.h"
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include <sys/mman.h>
#define SHM_NAME "/my_shm"   
#include <cstddef>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>

struct Shm {
    sem_t m_file_sent;
    int x = 111;
};
Shm* shm;
int main() {
    shm_unlink(SHM_NAME);

    int l_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0660);
    if (l_fd == -1) {
        perror("shm_open");
    }

    if (ftruncate(l_fd, sizeof(struct Shm)) == -1) {
        perror("ftruncate");
    }

    // Memory map the shared memory object
    shm = (struct Shm *) mmap(NULL, sizeof(struct Shm), PROT_READ | PROT_WRITE, MAP_SHARED, l_fd, 0);
    if (shm == MAP_FAILED) {
        perror("mmap");
    }
    if (sem_init(&shm->m_file_sent, 1, 1) == -1) {
        perror("sem_init");
    }
    // int sem_value;
    // sem_getvalue(&shm->m_file_sent, &sem_value);  
    // printf("Semaphore value before sem_wait: %d\n", sem_value);
    // sem_wait(&shm->m_file_sent);
    // sem_getvalue(&shm->m_file_sent, &sem_value);
    // printf("Semaphore value after sem_wait: %d\n", sem_value);
    // sem_post(&shm->m_file_sent);
    
    while (true)
    {

        createSocket();
    }    
    return 0;
}