import java.util.*;
import java.util.concurrent.TimeUnit; //converter o tempo em milissegundos
import java.util.concurrent.atomic.LongAdder;

public class umparaum {
    // classe o que cada thread vai fazer
    // cada soma é uma tarefa individual, no caso uma thread
    static class soma implements Runnable {
        private final int range; // ate onde vai somar
        private final LongAdder sink; // acumulador global pra armazenar resultados

        // Construtor: recebe o range e o acumulador
        soma(int range, LongAdder sink) {
            this.range = range;
            this.sink = sink;
        }

        @Override
        public void run() {
            long acc = 0L;// variavel local pra somar os numeros
            // faz a soma de 0 até range - 1
            for (int i = 0; i < range; i++) {
                acc += i;
            }
            // adiciona o resultado no acumulador global
            sink.add(acc);
        }
    }
    // função que cria e executa N threads
    static long runumparaum(int N, int range) throws InterruptedException {
        // lista para guardar threads criadas
        List<Thread> threads = new ArrayList<>(N);
        // onde as threads fica o resultado final
        LongAdder sink = new LongAdder();

        // cria threads um para um
        for (int i = 0; i < N; i++) {
            // cria uma nova thread com a tarefa soma
            // tipo =  t-0, t-1, t-2 e assim vai
            threads.add(new Thread(new soma(range, sink), "t-" + i));
        }

        long t0 = System.nanoTime(); // marca o tempo inicial antes de começar todas as threads
        for (Thread t : threads) t.start(); // inicia todas as threads (elas começam a somar ao mesmo tempo)
        for (Thread t : threads) t.join(); // espera todas terminarem o trabalho (join = "aguarda até acabar")
        long t1 = System.nanoTime(); // marca o tempo final (depois que todas terminaram)

        return TimeUnit.NANOSECONDS.toMillis(t1 - t0); // retorna o tempo total em milissegundos
    }

    public static void main(String[] args) throws Exception {
        // valores
        int[] threadsTestes = {1, 10, 100, 500, 1000};
        int range = 200;

        System.out.println("range = " + range);
        System.out.printf("%-10s | %-15s%n", "Threads", "Tempo (ms)");
        System.out.println("-------------------------------");

        // só pra mostra o resultado formatado em tabela
        for (int N : threadsTestes) {
            long tempo = runumparaum(N, range);
            System.out.printf("%-10d | %-15d%n", N, tempo);
        }
    }
}