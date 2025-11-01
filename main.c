#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <profileapi.h>
#include <stdint.h>

long processo_somar(int range) {
    long total = 0;
    for (int i = 0; i < range; ++i) {
        total += i;
    }
    return total;
}

double temporizador_cpu_tick(int range) {
    clock_t clock_inicio = clock();
    long resultado = processo_somar(range);
    clock_t clock_fim = clock();

    double tempo = (double)(clock_fim - clock_inicio) / CLOCKS_PER_SEC;

    return tempo;
}

int64_t temporizador_relogio_humano(int range) {
    LARGE_INTEGER ticks;
    long resultado = processo_somar(range);


    return tempo;
}

static inline int64_t GetTicks()
{
    LARGE_INTEGER ticks;
    if (!QueryPerformanceCounter(&ticks))
    {
        winrt::throw_last_error();
    }
    return ticks.QuadPart;
}

int main() {
    double resultado = temporizador_cpu_tick(2147483647);
    printf("%.6f", resultado);
    return 0;
}
