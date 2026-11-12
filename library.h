#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_REGISTER 200
#define MAXLEN 512
#define MAXARG 512
extern int accessdirectory; // for some functions in lib.c
extern int crashhandler;

#include <direct.h> // directory handling
#include <time.h>
#define chdir _chdir
#define getcwd _getcwd

long long int getvalue(const char *value_str);
void add(long long int *R, int r1, int r2, int r3);
void sub(long long int *R, int r1, int r2, int r3);
void mul(long long int *R, int r1, int r2, int r3);
void divide(long long int *R, int r1, int r2, int r3);
void mod(long long int *R, int r1, int r2, int r3);
void printreg(long long int *R, int r);


// I/O Functions
void addstring(const char *s1,const char *s2,char *result,int maxlen);  // Concatenate s1 and s2
int getnum(void);                                                       // Read integer from stdin
int gline(char *s, int maxlen);                                         // Read line from stdin (no overflow)
void input(char token[MAXARG][MAXLEN], int maxlen, int maxarg);         // Tokenize input from stdin
void inputline(char *line, int maxlen);                                 // Read line from stdin (with overflow warning)

// String Functions
int checkword(const char *s1, const char *s2);                          // Case-insensitive string comparison
int checkwordCS(const char *s1, const char *s2);                        // Case-sensitive string comparison

void clearstr(char *s);                                                 // Clear a string
void cleararray(char **token, int maxarg);                // Clear a 2D token array                                   
void copy(const char *from, char *to, int maxlen);                      // Copy substring [i1, i2] from 'from' to 'to'
void copyto(const char *from, char *to, int start, int end, int maxlen);// Copy substring with bounds
void cutstr(const char *s, char *to, int i1, int i2, int maxlen);       // Cut substring [i1, i2] to 'to'

int doesexist(const char *line, const char c);                          // Check if character exists in a string
int findindex(const char *line, const char *pattern);                   // Find first occurrence of pattern in line
int findlastindex(const char *line, const char *pattern);               // Find last occurrence of pattern in line
int gettoken(char **token, const char *line, int maxlen, int maxarg);   // Tokenize a string
int howmanyexists(const char *line, char c);                            // Count character occurrences in a string

int digit(char c);                                                      // Check if character is a digit (0-9)
int isletter(char c);                                                   // Check if character is a letter (A-Z, a-z)
int iswhite(char c);                                                    // Check if character is whitespace

int len(const char *s);                                                 // Get string length
int lower(const char c);                                                // Convert character to lowercase
void printstr(const char *s);                                           // Print string to stdout
void removespaces(char *s, int maxlen);                                 // Remove whitespace from string
void reverse(char *s);                                                  // Reverse a string
int ispalindrom(const char *s);                                         // Check if string is a palindrome

// Numeric Functions
int binarysearch(const double *sorted, int len, double n);              // Binary search in sorted array
double dround(double n, int r);                                         // Round 'n' to 'r' decimal places
int iseven(int n);                                                      // Check if integer is even
int isinteger(const char *s);                                           // Check if string is a valid integer
int isnumber(char *s);                                                  // Check if string contains only digits
int isprime(int n);                                                     // Check if integer is prime

void inttostr(int n, char *s);                                          // Convert integer to string
long long unsigned int power(long long unsigned int a,long long unsigned int b); // Calculate a^b
void Sort(double *s, int len);                                          // Bubble sort for double array
void Sortstr(char *s);                                                  // Bubble sort for string characters
double strtofloat(const char *s);                                       // Convert string to double
long long int strtoint(const char *s);                                  // Convert string to integer

// File Functions

int fgetline(char *line, FILE *file, int maxlen);                       // Read line from file
int catfile(const char *filename);                                      // Print file contents to stdout

int grep(const char *filename, const char *pattern, int maxlen);        // Search for pattern in file
int touchfile(const char *filename);                                    // Create empty file
void mytouch(const char *filename);
void mycat(const char *filename);
void getcurrentdirectory(char *curdir);
void pwd(void);
int changedir(const char *path);
int conditionalchangedir(const char *path, const char *rootdir);
int makedir(const char *path);
void mycls();
void myshowtime();

char **malloc_2d(int maxarg, int maxlen);
void free_2d(char **arr, int maxarg);

#endif