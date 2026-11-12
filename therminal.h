#ifndef THERMINAL_H
#define THERMINAL_H

#include "library.h"

// Global Arrays
extern char **boot;
extern char **therminalprogram;
extern char **program;
extern char **token;
extern char *line;
extern char *buffer;
extern long long int *R;
extern int flag__;

void runcmd(const char *buffer, const char *rootdir);
void help();
void runTherminal();

#endif