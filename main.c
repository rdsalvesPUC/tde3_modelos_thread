#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <profileapi.h>
#include <stdint.h>

LARGE_INTEGER frequencia;

long long processo_somar(int range) {
    long long total = 0;
    for (int i = 0; i < range; ++i) {
        total += i;
    }
    return total;
}

double temporizador_cpu_tick(int range) {
    clock_t clock_inicio = clock();
    long long resultado = processo_somar(range);
    clock_t clock_fim = clock();

    double tempo = (double)(clock_fim - clock_inicio) / CLOCKS_PER_SEC;

    return tempo;
}

double temporizador_relogio_humano(int range, LARGE_INTEGER frequencia) {
    LARGE_INTEGER inicio;
    LARGE_INTEGER fim;

    QueryPerformanceCounter(&inicio);
    long long resultado = processo_somar(range);
    QueryPerformanceCounter(&fim);

    long long diferenca = fim.QuadPart - inicio.QuadPart;
    double tempo = (double)diferenca / (double)frequencia.QuadPart;

    return tempo;
}


int main() {
    QueryPerformanceFrequency(&frequencia);

    // double resultado = temporizador_cpu_tick(2147483647);
    double resultado2 = temporizador_relogio_humano(2147483647, frequencia);
    // printf("%.6f", resultado);
    printf("\n%.6f", resultado2);
    return 0;
}
