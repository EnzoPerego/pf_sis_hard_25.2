#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
/* primeiros RDV (N = 3) */
pthread_mutex_t mutex1;
sem_t sem1;
int count1;
/* segundo RDV (N = 4) */
pthread_mutex_t mutex2;
sem_t sem2;
int count2;
void barrier1_init(void) {
    pthread_mutex_init(&mutex1, NULL);
    sem_init(&sem1, 0, 0);
    count1 = 0;
}
void barrier2_init(void) {
    pthread_mutex_init(&mutex2, NULL);
    sem_init(&sem2, 0, 0);
    count2 = 0;
}
/* espera na barrier1 (N=3) */
void barrier1_wait(void) {
    pthread_mutex_lock(&mutex1);
    count1++;
    if (count1 == 4) {
         /* último libera os outros (N-1 posts) */
        for (int i = 0; i < 3; i++) sem_post(&sem1);
        count1 = 0; /* opcional: reset para reuso */
        pthread_mutex_unlock(&mutex1);
    } else {
        pthread_mutex_unlock(&mutex1);
        sem_wait(&sem1);
} }
/* espera na barrier2 (N=4) */
void barrier2_wait(void) {
    pthread_mutex_lock(&mutex2);
    count2++;
    if (count2 == 4) {
        for (int i = 0; i < 3; i++) sem_post(&sem2);
        count2 = 0;
        pthread_mutex_unlock(&mutex2);
    } else {
        pthread_mutex_unlock(&mutex2);
        sem_wait(&sem2);
} }
void barrier1_destroy(void) {
    pthread_mutex_destroy(&mutex1);
    sem_destroy(&sem1);
}
void barrier2_destroy(void) {
    pthread_mutex_destroy(&mutex2);
    sem_destroy(&sem2);
}
/* Threads conforme a figura */
void *thread1(void *arg) {
    barrier1_wait();
    printf("C\n");
    barrier2_wait();
    printf("E\n");
 
     return NULL;
}
void *thread2(void *arg) {
    barrier1_wait();
    printf("D\n");
    barrier2_wait();
    return NULL;
}
void *thread3(void *arg) {
    /* chega no 1o RDV sem trabalho anterior */
    printf("A\n");
    barrier1_wait();
    barrier2_wait();
    printf("F\n");
    return NULL;
}
void *thread4(void *arg) {
    /* chega no 2o RDV sem trabalho anterior */
    printf("B\n");
    barrier1_wait();
    barrier2_wait();
    printf("G\n");
    return NULL;
}
int main(void) {
    barrier1_init();
    barrier2_init();
    pthread_t t1, t2, t3, t4;
    if (pthread_create(&t1, NULL, thread1, NULL) != 0) {
        perror("pthread_create"); exit(1); }
    if (pthread_create(&t2, NULL, thread2, NULL) != 0) {
        perror("pthread_create"); exit(1); }
    if (pthread_create(&t3, NULL, thread3, NULL) != 0) {
        perror("pthread_create"); exit(1); }
 
if (pthread_create(&t4, NULL, thread4, NULL) != 0) {
        perror("pthread_create"); exit(1); }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    barrier1_destroy();
    barrier2_destroy();
return 0; }