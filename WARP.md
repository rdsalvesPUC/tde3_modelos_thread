# WARP.md

This file provides guidance to WARP (warp.dev) when working with code in this repository.

## Project Overview

This is an academic project comparing performance between N:M and 1:1 thread models. The assignment requires implementing simulations in **Java** (not C), despite the current C placeholder code.

**Important Context:**
- The README.md describes a Java-based assignment
- The current `main.c` is a placeholder and should be replaced with Java implementations
- This is a group assignment (up to 4 people) requiring performance analysis and comparative results
- Results must be documented in README.md with execution times for different thread counts (10, 100, 500, 1000)

## Build and Run Commands

### Current C Build (placeholder):
```bash
# Configure with CMake
cmake -B cmake-build-debug -G Ninja

# Build
cmake --build cmake-build-debug

# Run
.\cmake-build-debug\tde3_modelos_thread.exe
```

### Expected Java Implementation:
The project requires two Java programs:
1. **N:M Model**: Use `ExecutorService` with fixed thread pool
2. **1:1 Model**: Direct thread creation with `Thread` or `Runnable`

Both should:
- Implement the same computational task (e.g., calculations with sleep)
- Measure execution time using `System.currentTimeMillis()` or `System.nanoTime()`
- Test with varying thread counts: 10, 100, 500, 1000

## Code Architecture

### Assignment Requirements

**Two separate Java programs needed:**

1. **N:M Thread Model Simulation**
   - Multiple user threads mapped to fewer OS threads
   - Use `ExecutorService.newFixedThreadPool(M)` where M < N
   - User threads (tasks) are multiplexed across M system threads
   - Simulates partial application-controlled scheduling

2. **1:1 Thread Model Simulation**
   - Each user thread maps directly to an OS thread
   - Create threads using `new Thread(Runnable)` or similar
   - Use `thread.join()` to wait for completion
   - True concurrent execution

**Each program must:**
- Accept number of threads as parameter
- Execute identical computational tasks per thread
- Measure and output total execution time
- Allow fair performance comparison

### Performance Testing Structure

Run both programs with thread counts: 10, 100, 500, 1000

Expected deliverables in README.md:
- Execution time table comparing both models
- Analysis identifying when 1:1 becomes more advantageous
- Discussion of OS thread availability impact on N:M model

## Project Notes

- **Language Mismatch**: Current code is C with CMake, but assignment explicitly requires Java
- **IDE**: CLion project structure present (`.idea/` directory)
- **Version Control**: Git repository initialized
- **Group Work**: All members must be able to explain the implementation
- **Deadline**: No late submissions accepted
- **Submission**: Via GitHub with results in README.md
