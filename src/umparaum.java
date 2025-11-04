import java.util.concurrent.TimeUnit; //converter o tempo em milissegundos

public class umparaum {
    static long contador = 0L; //variavel global pra acumular o resultado total

    // classe que define o que cada thread vai fazer
    // cada thread faz uma soma independente
    static class Soma implements Runnable {
        private final int range; // até onde vai somar

        // construtor que recebe o limite do range
        Soma(int range) {
            this.range = range;
        }

        @Override
        public void run() {
            long acc = 0L; // variavel local pra somar os numeros
            // faz a soma de 0 até range - 1
            for (int i = 0; i < range; i++) acc += i;
            // adiciona o resultado da soma no contador global
            contador += acc;
        }
    }

    // função que cria e executa as threads
    static long run(int tasks, int range) throws InterruptedException {
        Thread[] threads = new Thread[tasks]; // vetor que guarda as threads
        contador = 0L; // zera o contador antes de começar

        long t0 = System.nanoTime(); // marca o tempo inicial
        // cria e inicia todas as threads
        for (int i = 0; i < tasks; i++) {
            threads[i] = new Thread(new Soma(range)); // cria uma nova thread com a tarefa Soma
            threads[i].start(); // inicia a thread
        }

        // espera todas as threads terminarem (join = aguarda finalizar)
        for (Thread t : threads) t.join();

        long t1 = System.nanoTime(); // marca o tempo final depois de todas acabarem
        return TimeUnit.NANOSECONDS.toMillis(t1 - t0); // retorna o tempo total em milissegundos
    }

    public static void main(String[] args) throws Exception {
        int range = 200; // até onde cada thread vai somar
        int[] tasks = {1, 10, 100, 500, 1000}; // quantidades de threads que vai testar

        // mostra o cabeçalho da tabela
        System.out.printf("%-10s | %-12s%n", "Tasks", "Tempo (ms)");
        System.out.println("-------------------------------------------------");

        // executa os testes e mostra os tempos
        for (int t : tasks) {
            long tempo = run(t, range);
            System.out.printf("%-10d | %-12d%n", t, tempo);
        }
    }
}