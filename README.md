# Atividade Prática: Comparação de Desempenho entre Modelos de Threads N:M e 1:1

## Objetivo:
Desenvolver dois programas em Java que simulem os modelos de execução de threads N:M e 1:1, e comparar o desempenho entre eles com base no tempo total de execução. O objetivo é compreender como o modelo de mapeamento de threads influencia a eficiência da execução concorrente.

## Entregáveis

### Código-fonte dos dois programas (N:M e 1:1)
#### Modelo N:M
```C
#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include <stdint.h>

LARGE_INTEGER frequencia;
int         N = 100;
int         M = 4;
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

int main() {
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

    return 0;
}
```

#### Modelo 1:1
```C
#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include <stdint.h>

LARGE_INTEGER frequencia;
int         N = 100;
long long   carga = 2147483647;

void* processo_somar_thread(void* carga) {
    long long range = *(long long*)carga;
    volatile long long total = 0;
    for (int i = 0; i < range; ++i) {
        total += i;
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
    QueryPerformanceFrequency(&frequencia);
    LARGE_INTEGER inicio11;
    LARGE_INTEGER fim11;
    pthread_t* threads11 = (pthread_t*)malloc(sizeof(pthread_t) * N);
    int* indices = (int*)malloc(sizeof(int) * N);

    QueryPerformanceCounter(&inicio11);

    for (int i = 0; i < N; ++i) {
        indices[i] = i;
        pthread_create(&threads11[i], NULL, fila_processos11, &indices[i]);
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(threads11[i], NULL);
    }

    QueryPerformanceCounter(&fim11);

    double resultado11 = (double)(fim11.QuadPart - inicio11.QuadPart) / (double)frequencia.QuadPart;
    printf("\nmodelo 1:1 (1:%d, 1:%d) - Tempo Total: %.6f", N, N, resultado11);

    free(threads11);
    free(indices);

    return 0;
}
```
### Tabela com os tempos de execução para diferentes quantidades de threads
| Threads | Configuração (1, 1) | Tempo Total (s) |
| ------: |:-------------------:| --------------: |
|      10 |    (1:10, 1:10)     |        2.920836 |
|     100 |   (1:100, 1:100)    |       24.469351 |
|     500 |   (1:500, 1:500)    |      125.567725 |
|    1000 |  (1:1000, 1:1000)   |      242.282212 |

| M (threads SO) | Configuração (N, M) | Tempo Total (s) |
| -------------: | :-----------------: | --------------: |
|             10 |    (N:1000, M:10)   |      252.665331 |
|            100 |   (N:1000, M:100)   |      238.800051 |
|            500 |   (N:1000, M:500)   |      238.241453 |
|           1000 |   (N:1000, M:1000)  |      236.148017 |

### Gráfico comparativo (opcional, mas recomendado)
![Gráfico comparativo dos modelos](https://pucpredu-my.sharepoint.com/:i:/r/personal/s_rodrigo5_pucpr_edu_br/Documents/2025.2/04-Performance/tde3-graficos/output.png?csf=1&web=1&e=UcReDl?raw=true
)

### Relatório com análise crítica dos resultados
- Logo de cara achamos estranho os tempos do modelo N:M terem se mantido altos, quase sem nenhuma diferença, nem ganho de desempenho.
- Mas entendemos que o tipo de tarefa que escolhemos, soma dos valores de 2147483647, é uma tarefa que depende 100% do CPU.
- Então apesar de em teoria lançarmos 10, 100, 500 ou 1000 threads, na prática ficamos limitados as threads fisicas do ‘hardware’.
- Esses testes foram executados em um 11th Intel Core i5-11400 com 2.60GHz.
- Outro tipo de processo como o sleep() teria dado resultados bem diferentes.
- Também imaginamos que o fato de estarmos usando: printf("Thread: %p executando tarefa: %d\n", (void*)pthread_self(), meu_indice); também amarrou o lançamento das threads e a execução dos processos, à sincronização de tela do sistema.
- Por último, mas não menos importante, nem de longe, temos conhecimento suficiente em C para saber se o algoritmo criado, tem um bom desempenho.
