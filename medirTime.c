#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Uso: %s <programa> [argumentos...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num_executions = 15;
    double time_taken[num_executions];
    struct timespec start, end;
    pid_t pid;
    int status;

    for (int i = 0; i < num_executions; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        pid = fork();
        if (pid == -1) {
            perror("fork");
            return EXIT_FAILURE;
        } else if (pid == 0) {
            execvp(argv[1], &argv[1]);
            perror("No se pudo ejecutar el programa especificado");
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, &status, 0);
            clock_gettime(CLOCK_MONOTONIC, &end);
            time_taken[i] = end.tv_sec - start.tv_sec;
            time_taken[i] += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        }
    }
    for (int i = 0; i < num_executions; i++) {
        printf("Tiempo de ejecución %d: %.6f segundos\n", i+1, time_taken[i]);
    }

    return EXIT_SUCCESS;
}

