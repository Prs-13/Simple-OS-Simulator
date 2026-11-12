#include "library.h"
#include "therminal.h"
#include <windows.h>

char **boot;
char **therminalprogram;
char **program;
char **token;
char *line;
char *buffer;
long long int *R;


int main() {
   FILE *file_boot = fopen("myosBOOTfile.txt", "r");
   if (file_boot == NULL) {
       printf("Boot Process Failed\nShutting Down...");
       Sleep(2000);
       return 1;
    }
    boot = (char**)malloc_2d(MAXARG, MAXLEN);
    int linecount = 0;
    while (fgetline(boot[linecount], file_boot, MAXLEN) != EOF && (linecount < MAXARG))
        linecount++;
    fclose(file_boot);
    
    therminalprogram = malloc_2d(MAXARG, MAXLEN);
    program = malloc_2d(MAXARG, MAXLEN);
    token   = malloc_2d(MAXARG, MAXLEN);
    
    line = (char*)malloc(MAXLEN * sizeof(char));
    buffer = (char*)malloc(MAXLEN * sizeof(char));
    R = (long long int*)malloc(MAX_REGISTER * sizeof(long long int));

    for (int i = 0; i < MAX_REGISTER; i++) R[i] = 0;

    if (!R || !buffer || !line || !program || !token || !therminalprogram) {
        printf("Boot Process Failed\nShutting Down...");
        Sleep(2000);
        return 1;
    }

    printf("Booted Successfully\n\n"); // Global arrays initialized
    Sleep(1000);
    printf("\t\t\t\t\t=========== Welcome To OS ===========\n\n\n");
    // printf("\tType 'help' for available commands\n\n");

    runTherminal();
    
    free_2d(therminalprogram, MAXARG);
    free_2d(program, MAXARG);
    free_2d(token, MAXARG);
    
    free(R);
    free(line);
    free(buffer);

    free_2d(boot, MAXARG);

    printf("\nShutting Down...");
    Sleep(2000);

    return 0;
}