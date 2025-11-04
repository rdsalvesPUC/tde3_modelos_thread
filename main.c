#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include <stdint.h>

LARGE_INTEGER frequencia;
int         N = 1000;
int         M = 1000;
long long   carga = 2147483647;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int proxima_tarefa = 0;

void* processo_somar_thread(void* carga) {
    long long range = *(long long*)carga;
    volatile long long total = 0;
    for (int i = 0; i < range; ++i) {
        total += i;
    }
    return NULL;
}

void* fila_processosNM(void* arg) {
    (void)arg;
    while (1) {
        int meu_indice;

        pthread_mutex_lock(&mutex);
        if (proxima_tarefa >= N) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        meu_indice = proxima_tarefa++;
        pthread_mutex_unlock(&mutex);

        printf("Thread: %p executando tarefa: %d\n", (void*)pthread_self(), meu_indice);
        processo_somar_thread(&carga);

        fflush(stdout);
    }
    return NULL;
}

void* fila_processos11(void* arg) {
    int meu_indice = *(int*)arg;

    printf("Thread: %p executando tarefa: %d\n", (void*)pthread_self(), meu_indice);
    processo_somar_thread(&carga);

    fflush(stdout);
    return NULL;
}


int main() {
// =============== MODELO N:M ================================ //
    QueryPerformanceFrequency(&frequencia);
    LARGE_INTEGER inicioNM;
    LARGE_INTEGER fimNM;
    pthread_t threadsNM[M];

    QueryPerformanceCounter(&inicioNM);

    for (int i = 0; i < M; ++i) {
        pthread_create(&threadsNM[i], NULL, fila_processosNM, NULL);
    }

    for (int i = 0; i < M; ++i) {
        pthread_join(threadsNM[i], NULL);
    }

    QueryPerformanceCounter(&fimNM);

    double resultadoNM = (double)(fimNM.QuadPart - inicioNM.QuadPart) / (double)frequencia.QuadPart;
    printf("\nmodelo N:M (N:%d, M:%d) - Tempo Total: %.6f", N, M, resultadoNM);

// =============== MODELO 1:1 ================================ //

    // QueryPerformanceFrequency(&frequencia);
    // LARGE_INTEGER inicio11;
    // LARGE_INTEGER fim11;
    // pthread_t* threads11 = (pthread_t*)malloc(sizeof(pthread_t) * N);
    // int* indices = (int*)malloc(sizeof(int) * N);
    //
    // QueryPerformanceCounter(&inicio11);
    //
    // for (int i = 0; i < N; ++i) {
    //     indices[i] = i;
    //     pthread_create(&threads11[i], NULL, fila_processos11, &indices[i]);
    // }
    //
    // for (int i = 0; i < N; ++i) {
    //     pthread_join(threads11[i], NULL);
    // }
    //
    // QueryPerformanceCounter(&fim11);
    //
    // double resultado11 = (double)(fim11.QuadPart - inicio11.QuadPart) / (double)frequencia.QuadPart;
    // printf("\nmodelo 1:1 (1:%d, 1:%d) - Tempo Total: %.6f", N, N, resultado11);
    //
    // free(threads11);
    // free(indices);

    return 0;
}
