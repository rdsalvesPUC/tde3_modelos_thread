import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.LongAdder;

public class NtoM {
    static class Soma implements Runnable {
        private final int range;
        private final LongAdder sink;

        Soma(int range, LongAdder sink) {
            this.range = range;
            this.sink = sink;
        }

        @Override
        public void run() {
            long acc = 0L;
            for (int i = 0; i < range; i++) acc += i;
            sink.add(acc);
        }
    }

    static long runVirtual(int tasks, int range) throws InterruptedException {
        LongAdder sink = new LongAdder();
        List<Thread> threads = new ArrayList<>(tasks);

        long t0 = System.nanoTime();
        for (int i = 0; i < tasks; i++) {
            threads.add(Thread.startVirtualThread(new Soma(range, sink)));
        }
        for (Thread t : threads) t.join();
        long t1 = System.nanoTime();

        return TimeUnit.NANOSECONDS.toMillis(t1 - t0);
    }

    public static void main(String[] args) throws Exception {
        int range = 200;
        int[] tasks = {1, 10, 100, 500, 1000};

        System.out.println("range = " + range);
        System.out.printf("%-10s | %-15s%n", "Tasks", "Tempo (ms)");
        System.out.println("-------------------------------");

        for (int t : tasks) {
            long tempo = runVirtual(t, range);
            System.out.printf("%-10d | %-15d%n", t, tempo);
        }
        System.out.println();
    }
}
