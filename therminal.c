#include "library.h"
#include "assembler.h"
#include <windows.h>
#include "therminal.h"

static int argc;

int accessdirectory = 1; // no use just preventing compile error for extern definition
int flag__ = 0;

char currentdirectory[MAXLEN];

typedef struct {
    char label[MAXLEN];
    int line;
} Label;

typedef struct {
    char y;
    char x;
} Input;

static int buffer_index = 0;
static int end = 0;
static int echoflag = 1;

void runTherminal() {
    
    FILE *therminalfile = fopen("therminal.os", "r");
    if (!therminalfile) {
        printf("\n\tCould not open therminal.os\n\n");
        return;
    }
    int linecount = 0;
    while (fgetline(therminalprogram[linecount], therminalfile, MAXLEN) != EOF && (linecount < MAXARG))
        linecount++;
    fclose(therminalfile);

    Label therminal_labels[50];
    int labelCount = 0;

    for (int i = 0; i < MAXARG && therminalprogram[i] != NULL; i++) {
        cleararray(token, MAXARG);
        clearstr(line);
        int semicolonPos = findindex(therminalprogram[i], ";");
        if (semicolonPos >= 0) // removing comments
            copyto(therminalprogram[i], line, 0, semicolonPos - 1, MAXLEN);
        else
            copy(therminalprogram[i], line, MAXLEN);
        gettoken(token, line, MAXLEN, MAXARG);

        int toklen = len(token[0]);
        if (toklen > 0 && token[0][toklen - 1] == ':') { // finding lables and storing them
            token[0][toklen - 1] = '\0';
            copy(token[0], therminal_labels[labelCount].label, MAXLEN);
            therminal_labels[labelCount].line = i;
            labelCount++;
        }
    }
    //============================================================

    char rootdir[2]; // just to make runcmd() function working
    // getcurrentdirectory(rootdir);
    // getcurrentdirectory(currentdirectory);

    // if (echoflag) printf("MYOS %s > ",currentdirectory);
    // else printf("MYOS > ");

    Input input;
    int i = 0;
    // char **buffersplit = malloc_2d(MAXARG, MAXLEN);
    // if (!buffersplit) {
    //     printf("Boot Process Failed\nShutting Down...");
    //     free_2d(buffersplit, MAXARG);
    //     return;
    // }
    // cleararray(buffersplit, MAXARG);
    while (i < MAXARG && therminalprogram[i] != NULL) {

        cleararray(token, MAXARG);
        clearstr(line);

        // comments removing
        int semicolonPos = findindex(therminalprogram[i], ";");
        if (semicolonPos >= 0)
            copyto(therminalprogram[i], line, 0, semicolonPos - 1, MAXLEN);
        else
            copy(therminalprogram[i], line, MAXLEN);
        gettoken(token, line, MAXLEN, MAXARG);

        if (len(token[0]) == 0) { // skipping empty line
            i++;
            continue;
        }

        if (checkword(token[0], "set")) {
            if (checkword(token[1], "getchar")) 
                input.x = getchar();
            else if (checkword(token[2], "y"))
                input.y = '\n';
            else if (checkword(token[2], "buffer"))
                buffer[buffer_index++] = input.x;
        } else if (checkword(token[0], "cmp")) {
            if (checkword(token[1], "x")) {
                char str1[2] = { input.x, '\0' };  // convert x & y to string
                char str2[2] = { input.y, '\0' };
                R[199] = ((checkword(str1, str2)) == 1) ? 1 : -1;
            }
            // else {
            //     gettoken(buffersplit, buffer, MAXLEN, MAXARG);
            //     R[199] = ((checkword(buffersplit[0], token[2])) == 1) ? 1 : -1;
            // }
        } else if (checkword(token[0], "runcmd")) {
            buffer[buffer_index] = '\0';
            runcmd(buffer, rootdir);
            if (end) {
                // free_2d(buffersplit, MAXARG);
                return;  
            } 
            // getcurrentdirectory(currentdirectory);
            // if (echoflag) printf("MYOS %s > ",currentdirectory);
            // else printf("MYOS > ");
            clearstr(buffer);
            buffer_index = 0;
            // cleararray(buffersplit, MAXARG);
        } 
        // else if (checkword(token[0], "getchar")) input.x = getchar();


        else if (checkword(token[0], "goto")) {
            int jump = 0;
            if (len(token[2]) > 0 && checkword(token[2], "if")) {
                if (checkword(token[3], "==") && R[199] == 1) jump = 1;
            } else jump = 1;

            if (jump) {
                for (int j = 0; j < labelCount; j++) {
                    if (checkword(therminal_labels[j].label, token[1])) { // Goes to the token label and continues line from there
                        i = therminal_labels[j].line+1;
                        goto MOVE_ON;
                    }
                }
            }
        }
        i++;
        MOVE_ON:;
    }
}

void runcmd(const char *buffer, const char *rootdir) {
    argc = gettoken(token, buffer, MAXARG, MAXLEN);
    // else if (checkword(token[0], "help") && argc == 1) {
    //     help();
    // }
    // else if (checkword(token[0], "showtime") && argc == 1) {
    //     myshowtime();
    // }
    // else if (checkword(token[0], "echo")) {
    //     if (argc > 1) {
    //         if (checkword(token[1], "on") && argc == 2)
    //             echoflag = 1;
    //         else if (checkword(token[1], "off") && argc == 2)
    //             echoflag = 0;
    //         else {
    //             printf("\n\tUsage:\n");
    //             printf("\techo on       - Shows working directory in prompt\n");
    //             printf("\techo off      - Hides working directory in prompt\n\n");
    //         }
    //     } else {
    //         printf("\n\tUsage:\n");
    //         printf("\techo on       - Shows working directory in prompt\n");
    //         printf("\techo off      - Hides working directory in prompt\n\n");
    //     }
    // }
    // else if (checkword(token[0], "ls") || checkword(token[0], "dir")) {
    //     if (argc == 1) {
    //         system("dir");
    //         putchar('\n');
    //     } else {
    //         printf("\n\tInvalid option: %s\n\n", token[1]);
    //     }
    // }
    // else if (checkword(token[0], "cd")) {
    //     if (argc == 1)
    //         printf("\n\tcd: missing directory argument\n\n");
    //     else if (conditionalchangedir(token[1], rootdir) != 0) {
    //         if (accessdirectory)
    //             printf("\n\tcd: %s: No such directory\n\n", token[1]);
    //     } else 
    //         printf("\n\tInvalid use of cd\n\n");

    // }
    if (checkword(token[0], "exit") && argc == 1) {
        end = 1;
        return;
    }
    else if (checkword(token[0], "help") && argc == 1) {
        FILE *file = fopen("help.os", "r");
        if (!file) {
            printf("\n\tCould not open help.os\n\n");
            return;
        }
        int linecount = 0;
        while (fgetline(program[linecount], file, MAXLEN) != EOF && (linecount < MAXARG))
            linecount++;
        fclose(file);
        exe();
    }
    else if ((checkword(token[0], "cls") || checkword(token[0], "clear")) && argc == 1) {
        // system("cls");
        FILE *file = fopen("cls.os", "r");
        if (!file) {
            printf("\n\tCould not open cls.os\n\n");
            return;
        }
        int linecount = 0;
        while (fgetline(program[linecount], file, MAXLEN) != EOF && (linecount < MAXARG))
            linecount++;
        fclose(file);
        exe();
        // if (argc > 1)
        //     printf("\n\t %s is not accepted \n\n", token[1]);
        // else
        //     // mycls();
        //     system("cls");
    }
    else if (checkword(token[0], "mkdir")) {
        flag__ = makedir(token[1]);
        FILE *file = fopen("output.os", "r");
        if (!file) {
            printf("\n\tCould not open output.os\n\n");
            return;
        }
        int linecount = 0;
        while (fgetline(program[linecount], file, MAXLEN) != EOF && (linecount < MAXARG))
            linecount++;
        fclose(file);
        exe();
        putchar('\n');
        // if (argc == 1) {
        //     printf("\n\tmkdir [directoryname]\n");
        //     printf("\tUsage : make a directory\n\n");
        // } else if (argc == 2) {
        //     makedir(token[1]);
        // } else {
        //     printf("\n\tNot accepted! : %s\n\n", token[2]);
        // }
    }
    else if (checkword(token[0],"write") && argc == 1) {
        RUN();
    }
    else if (checkword(token[0], "touch")) {
        flag__ = touchfile(token[1]);
        FILE *file = fopen("output.os", "r");
        if (!file) {
            printf("\n\tCould not open output.os\n\n");
            return;
        }
        int linecount = 0;
        while (fgetline(program[linecount], file, MAXLEN) != EOF && (linecount < MAXARG))
            linecount++;
        fclose(file);
        exe();
        putchar('\n');
    //     if (argc == 1) {
    //         printf("\n\ttouch [filename]\n\n");
    //         printf("\tUsage : create an empty file or update it\n\n");
    //     } else if (argc == 2) {
    //         mytouch(token[1]);
    //     } else {
    //         printf("\tNot accepted : %s\n\n", token[2]);
    //     }
    // }
    // else if (checkword(token[0], "cat")) {
    //     if (argc == 1) {
    //         printf("\n\tcat [filename]\n\n");
    //         printf("\tUsage : show contents of a file\n\n");
    //     } else if (argc == 2) {
    //         mycat(token[1]);
    //     } else {
    //         printf("\n\tNot accepted! : %s\n\n", token[2]);
    //     }
    }

    else if (checkword(token[0], "run") && argc == 2) {

            //=======================================||myosprogram.os||==============
        if (checkword(token[1], "myosprogram.os")) {
            FILE *file = fopen("myosprogram.os", "r");
            if (file == NULL){
                printf("\tError: Could not open myosprogram.os\n\n");
                return;;
            }
            // printf("\n\tSum Of First 20 Prime Numbers :\n\n\t");
            cleararray(program, MAXARG);

            int linecount = 0;
            while (fgetline(program[linecount], file, MAXLEN) != EOF && (linecount < MAXARG)) {
                linecount++;
            }
            fclose(file);
            exe();  // Run
            putchar('\n');

        }

            //=============================||evenoddcheck.os||=======================================
        else if (checkword(token[1], "evenoddcheck.os")) {
            FILE *file = fopen("evenoddcheck.os", "r");
            if (file == NULL){
                printf("\tError: Could not open evenoddcheck.os\n\n");
                return;
            }
            int linecount = 0;
            while (fgetline(program[linecount], file, MAXLEN) != EOF && (linecount < MAXARG)) {
                linecount++;
            }
            fclose(file);
            exe();  // exe replaced program
            putchar('\n');
        }


            //==================================||powerloop.os||=========================================
        else if (checkword(token[1], "powerloop.os")) {
            FILE *file = fopen("powerloop.os", "r");
            if (file == NULL){
                printf("\tError: Could not open powerloop.os\n\n");
                return;
            }
            int linecount = 0;
            while (fgetline(program[linecount], file, MAXLEN) != EOF && (linecount < MAXARG)) {
                linecount++;
            }
            fclose(file);

            printf("\nbase : ");
            exe();
            putchar('\n');
        }
        // else
        //     printf("\n\tInvalid program : %s\n\tUse one of the three programs that is shown by using 'help' command\n\n", buffer);
        
    }
    // else {
    //     printf("\n\tInvalid command : %s\n", buffer);
    //     printf("\tType 'help' for allowed commands...\n\n");
    // }

    return;
}

// void help() {
//     printf("\n\t==================Available Commands==================\n\n");
//     printf("\thelp\tls\tcls\n\techo\tmkdir\ttouch\tcat\n\tcd\tshowtime\trun\tWRITE\texit\n\n");
//     printf("\tuse 'write' to write your own program with OS language and execute it if possible\n\n");
//     printf("\tprograms to use :\n\n\tuse 'run' before to execute :\n\tmyosprogram.os\tevenoddcheck.os\tpowerloop.os\n\n");
//     printf("\tNOTE: in powerloop program first input is your BASE and second is your POWER\n\n");
// }