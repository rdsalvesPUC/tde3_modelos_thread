Atividade Prática: Comparação de Desempenho entre Modelos de Threads N:M e 1:1

Objetivo:
Desenvolver dois programas em Java que simulem os modelos de execução de threads N:M e 1:1, e comparar o desempenho entre eles com base no tempo total de execução. O objetivo é compreender como o modelo de mapeamento de threads influencia a eficiência da execução concorrente.

Descrição da Tarefa
Você deverá implementar dois programas distintos:

Simulação do modelo N:M: múltiplas threads de usuário são mapeadas para um número menor de threads do sistema operacional, permitindo que múltiplas threads de usuário sejam gerenciadas simultaneamente, mas com controle parcial do escalonamento pela aplicação. Para simular esse modelo em Java, implemente um agrupamento de threads de usuário que são gerenciadas e executadas por um conjunto fixo de threads do sistema (por exemplo, utilizando um pool de threads que executa as tarefas de maneira multiplexada).

Simulação do modelo 1:1: múltiplas threads de usuário mapeadas diretamente para threads do sistema operacional, com execução concorrente real.

Ambos os programas devem realizar a mesma tarefa computacional (por exemplo, cálculos simples, simulação de carga ou espera com sleep) para permitir uma comparação justa.

Métrica de Avaliação

Tempo total de execução (em milissegundos), medido do início ao fim da execução de todas as threads.

A comparação deve ser feita com diferentes quantidades de threads (ex: 10, 100, 500, 1000) para observar o impacto da escalabilidade.

Passo a Passo de Implementação:

Parte 1: Preparação

Escolha uma tarefa simples que cada thread irá executar (ex: somar números, simular carga com SLEEP, etc.).

Defina um número fixo de iterações ou tempo de execução por thread.

Parte 2: Simulação do Modelo N:M
3. Crie um pool fixo de threads do sistema operacional (ex: usando ExecutorService com número limitado de threads).
4. Distribua a execução das múltiplas threads de usuário (tarefas) entre essas threads do sistema, simulando o multiplexamento de N threads de usuário em M threads do sistema.
5. Meça o tempo total de execução usando System.currentTimeMillis() ou System.nanoTime().

Parte 3: Simulação do Modelo 1:1
6. Crie múltiplas threads reais usando a API padrão do Java (Thread ou Runnable), onde cada thread de usuário corresponde a uma thread do sistema.
7. Inicie todas as threads quase simultaneamente e aguarde sua conclusão com join().
8. Meça o tempo total de execução da mesma forma que no modelo N:M.

Parte 4: Comparação e Análise
9. Execute ambos os programas com diferentes quantidades de threads (ex: 10, 100, 500, 1000).
10. Registre os tempos de execução em uma tabela.
11. Analise os resultados e identifique em que ponto o modelo 1:1 se torna mais vantajoso, considerando o impacto do número de threads do sistema disponível no modelo N:M.
12. Elabore um relatório com gráficos comparativos e conclusões sobre o desempenho de cada modelo.

Entregáveis

Código-fonte dos dois programas (N:M e 1:1)

Tabela com os tempos de execução para diferentes quantidades de threads

Gráfico comparativo (opcional, mas recomendado)

Relatório com análise crítica dos resultados

ENVIO: A atividade deve ser enviada via GitHub com os resultados dos comparativos no README e os códigos.
Não haverá entrega fora do prazo.
Observação: A atividade pode demandar autoria, então todos do grupo devem saber explicar.
Grupo de até 4 pessoas.
Pessoas que não estiverem em grupo podem realizar a atividade sozinhas.
Os grupos serão formados em sala de aula.
