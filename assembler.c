#include "library.h"
#include <stdio.h>
#include "therminal.h"


// Label processing
typedef struct {
    char label[MAXLEN];
    int line;
} Label;

int is_valid_register(int reg) {
    return reg >= 0 && reg < MAX_REGISTER;
}

void exe() {

    Label labels[100];
    int labelCount = 0;

    for (int i = 0; i < MAXARG && program[i] != NULL; i++) {
        cleararray(token, MAXARG);
        clearstr(line);
        int semicolonPos = findindex(program[i], ";");
        if (semicolonPos >= 0) // removes semi colons if exists
            copyto(program[i], line, 0, semicolonPos - 1, MAXLEN);
        else
            copy(program[i], line, MAXLEN);
        gettoken(token, line, MAXLEN, MAXARG);

        int toklen = len(token[0]);
        if (toklen > 0 && token[0][toklen - 1] == ':') { // Label finding and storing them
            token[0][toklen - 1] = '\0';
            copy(token[0], labels[labelCount].label, MAXLEN);
            labels[labelCount].line = i;
            labelCount++;
        }
    }

    // Exe loop
    int i = 0;
    while (i < MAXARG && program[i] != NULL) {
        
        cleararray(token, MAXARG);
        clearstr(line);
        // char lineWithoutComment[MAXLEN];

        // Removes comments
        int semicolonPos = findindex(program[i], ";");
        if (semicolonPos >= 0)
            copyto(program[i], line, 0, semicolonPos - 1, MAXLEN);
        else
            copy(program[i], line, MAXLEN);
        gettoken(token, line, MAXLEN, MAXARG);

        if (len(token[0]) == 0) {
            i++;
            continue;
        }

        // Assigns varibales in the format 'r[integer number]'
        int toklen = len(token[0]);
        if (toklen > 0 && token[0][toklen - 1] == ':') {
            i++;
            continue;
        }

        if (checkword(token[0], "LOAD")) {
            int reg = strtoint(token[1] + 1);
            if (is_valid_register(reg) && !isletter(token[1][1])) {
                if (isletter(token[2][0])) {
                    if (checkword(token[2], "flag__")) 
                        R[reg] = flag__;
                    else if (checkword(token[2], "getint")) {
                        // printf("\tWaiting for user input : ");
                        char x;
                        char buffer[MAXLEN];
                        int buffer_index = 0;
                        while (((x = getchar()) != '\n')) 
                            buffer[buffer_index++] = x;
                        buffer[buffer_index] = '\0';
                        if (buffer_index != 0)
                            R[reg] = getvalue(buffer);
                        else {
                            printf("\tInvalid input: \\n\n");
                            crashhandler = 1;
                        }
                        if (crashhandler) {
                            printf("\tprogram crashed!!\n");
                            crashhandler = 0;
                            cleararray(token, MAXARG);
                            clearstr(line);
                            return;
                        }
                    } else {
                        int v = findindex(token[2], "R");
                        if (v == -1){
                            v = findindex(token[2], "r");
                        }
                        if (v == 0 && isinteger(token[2] + 1)) {
                            int src = strtoint(token[2] + 1);
                            if (is_valid_register(src))
                                R[reg] = R[src];
                            else
                                printf("Error: Invalid source register in LOAD\n");
                        }
                    }
                } else {
                    R[reg] = getvalue(token[2]);
                }
            } else {
                printf("Error: Invalid source register in LOAD\n");
            }
        }
        else if (checkword(token[0], "ADD")) {
            int r1 = strtoint(token[1] + 1);
            int r2 = strtoint(token[2] + 1);
            int r3 = strtoint(token[3] + 1);
            if (is_valid_register(r1) && is_valid_register(r2) && is_valid_register(r3) && !isletter(token[1][1]) && !isletter(token[2][1]) && !isletter(token[3][1])) {
                add(R, r1, r2, r3);
            } else {
                printf("Error: Invalid register in ADD\n");
            }
        }
        else if (checkword(token[0], "SUB")) {
            int r1 = strtoint(token[1] + 1);
            int r2 = strtoint(token[2] + 1);
            int r3 = strtoint(token[3] + 1);
            if (is_valid_register(r1) && is_valid_register(r2) && is_valid_register(r3) && !isletter(token[1][1]) && !isletter(token[2][1]) && !isletter(token[3][1])) {
                sub(R, r1, r2, r3);
            } else {
                printf("Error: Invalid register in SUB\n");
            }
        }
        else if (checkword(token[0], "MUL")) {
            int r1 = strtoint(token[1] + 1);
            int r2 = strtoint(token[2] + 1);
            int r3 = strtoint(token[3] + 1);
            if (is_valid_register(r1) && is_valid_register(r2) && is_valid_register(r3) && !isletter(token[1][1]) && !isletter(token[2][1]) && !isletter(token[3][1])) {
                mul(R, r1, r2, r3);
            } else {
                printf("Error: Invalid register in MUL\n");
            }
        }
        else if (checkword(token[0], "DIV")) {
            int r1 = strtoint(token[1] + 1);
            int r2 = strtoint(token[2] + 1);
            int r3 = strtoint(token[3] + 1);
            if (is_valid_register(r1) && is_valid_register(r2) && is_valid_register(r3) && !isletter(token[1][1]) && !isletter(token[2][1]) && !isletter(token[3][1])) {
                divide(R, r1, r2, r3);
            } else {
                printf("Error: Invalid register in DIV\n");
            }
        }
        else if (checkword(token[0], "MOD")) {
            int r1 = strtoint(token[1] + 1);
            int r2 = strtoint(token[2] + 1);
            int r3 = strtoint(token[3] + 1);
            if (is_valid_register(r1) && is_valid_register(r2) && is_valid_register(r3) && !isletter(token[1][1]) && !isletter(token[2][1]) && !isletter(token[3][1])) {
                mod(R, r1, r2, r3);
            } else {
                printf("Error: Invalid register in MOD\n");
            }
        }
        else if (checkword(token[0], "CMP")) {
            int r1 = strtoint(token[1] + 1);
            int r2 = strtoint(token[2] + 1);
            if (is_valid_register(r1) && is_valid_register(r2) && !isletter(token[1][1]) && !isletter(token[2][1])) {
                R[198] = (R[r1] == R[r2]) ? 0 : (R[r1] > R[r2]) ? 1 : -1;
            } else {
                printf("Error: Invalid register in CMP\n");
            }
        }
        else if (checkword(token[0], "goto")) {
            int jump = 0;
            if (len(token[2]) > 0 && checkword(token[2], "if")) {
                if (checkword(token[3], "==") && R[198] == 0) jump = 1;
                else if (checkword(token[3], ">") && R[198] > 0) jump = 1;
                else if (checkword(token[3], "<") && R[198] < 0) jump = 1;
                else if (checkword(token[3], ">=") && R[198] >= 0) jump = 1;
                else if (checkword(token[3], "<=") && R[198] <= 0) jump = 1;
            } else {
                jump = 1;
            }

            if (jump) {
                for (int j = 0; j < labelCount; j++) {
                    if (checkword(labels[j].label, token[1])) { // Goes to the token label and continues line from there
                        i = labels[j].line+1;
                        goto CONTINUE_EXE;
                    }
                }
            }
        }
        else if (checkword(token[0], "PRINT")) {
            int r = strtoint(token[1] + 1);
            if (is_valid_register(r) && !isletter(token[1][1])) {
                printreg(R, r);
            } else {
                printf("Error: Invalid register in PRINT\n");
            }
        }
        else if (checkword(token[0], "PUTCHAR")) {
            if (checkword(token[1], "\\n"))
                putchar('\n');
            else
                putchar(token[1][0]);
        }
        else if (checkword(token[0], "END")) {
            cleararray(token, MAXARG);
            clearstr(line);
            for (int R_index = 0; R_index < MAX_REGISTER; R_index++) R[R_index] = 0;
            putchar('\n');
            break;
        }
        i++;
        CONTINUE_EXE:;
    }
}

int RUN() { // for storing "write" program 
    cleararray(program, MAXARG);
    clearstr(line);
    int programline = 0;
    int endflag = 0;
    int linenumber = 1;

    while (1) {
        clearstr(line);
        cleararray(token, MAXARG);

        printf("%d : ", linenumber);
        gline(line, MAXLEN);
        gettoken(token, line, MAXLEN, MAXARG);

        // removes comments
        int comment_idx = findindex(line, ";");
        if (comment_idx != -1)
            copyto(line, program[programline], 0, comment_idx - 1, MAXLEN);
        else
            copy(line, program[programline], MAXLEN);

        if (checkword(token[0], "END")) {
            endflag = 1;
            break;
        }
        programline++;
        linenumber++;
    }

    if (endflag) {
        exe();
    }

    return 0;
}