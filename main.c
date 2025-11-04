#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>

LARGE_INTEGER frequencia;
int         N = 100;
int         M = 4;
long long   carga = 2147483647;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int proxima_tarefa = 0;

// long long processo_somar(int range) {
//     long long total = 0;
//     for (int i = 0; i < range; ++i) {
//         total += i;
//     }
//     return total;
// }

// double temporizador_cpu_tick(int range) {
//     clock_t clock_inicio = clock();
//     long long resultado = processo_somar(range);
//     clock_t clock_fim = clock();
//
//     double tempo = (double)(clock_fim - clock_inicio) / CLOCKS_PER_SEC;
//
//     return tempo;
// }

// double temporizador_relogio_humano(long long range, LARGE_INTEGER frequencia) {
//     LARGE_INTEGER inicio;
//     LARGE_INTEGER fim;
//
//     QueryPerformanceCounter(&inicio);
//     long long resultado = processo_somar(range);
//     QueryPerformanceCounter(&fim);
//
//     long long diferenca = fim.QuadPart - inicio.QuadPart;
//     double tempo = (double)diferenca / (double)frequencia.QuadPart;
//
//     return tempo;
// }

void* processo_somar_thread(void* carga) {
    long long range = *(long long*)carga;
    volatile long long total = 0;
    for (int i = 0; i < range; ++i) {
        total += i;
    }
    return NULL;
}

void* fila_processos(void* arg) {
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


int main() {
    QueryPerformanceFrequency(&frequencia);
    LARGE_INTEGER inicio;
    LARGE_INTEGER fim;
    pthread_t threads[M];

    QueryPerformanceCounter(&inicio);

    for (int i = 0; i < M; ++i) {
        pthread_create(&threads[i], NULL, fila_processos, NULL);
    }

    for (int i = 0; i < M; ++i) {
        pthread_join(threads[i], NULL);
    }

    QueryPerformanceCounter(&fim);

    double resultado = (double)(fim.QuadPart - inicio.QuadPart) / (double)frequencia.QuadPart;
    printf("\n%.6f", resultado);
    return 0;
}
