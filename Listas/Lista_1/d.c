#include <pthread.h>

int work(int id);

int count = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

struct thread_arg {
    int vezes;
};

void *thread_func(void *arg) {
    struct thread_arg *targ = (struct thread_arg *)arg;

    for (int i = 0; i < targ->vezes; i++) {
        int id;

        pthread_mutex_lock(&mut);
        id = count++;
        pthread_mutex_unlock(&mut);

        work(id);
    }

    pthread_exit(NULL);
}
