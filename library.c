#include "library.h"

int crashhandler = 0;

long long int getvalue(const char *value_str){
    char cleaned[MAXLEN];
    copy(value_str, cleaned, MAXLEN);

    // Removes semicolon
    int l = len(cleaned);
    if (cleaned[l - 1] == ';')
        cleaned[l - 1] = '\0';

    if (isinteger(cleaned))
        return strtoint(cleaned);

    printf("\tInvalid value: %s\n", value_str);
    crashhandler = 1;
    return 0;
}

void add(long long int *R, int r1, int r2, int r3){
    R[r3] = R[r1] + R[r2];
    return;
}

void sub(long long int *R, int r1, int r2, int r3){
    R[r3] = R[r1] - R[r2];
    return;
}

void mul(long long int *R, int r1, int r2, int r3){
    R[r3] = R[r1] * R[r2];
    return;
}

void divide(long long int *R, int r1, int r2, int r3){
    if (R[r2] == 0) {
        printf("Error: Division by zero\n");
        R[r3] = 0; // Stores 0 to the destination reg
    } else {
        R[r3] = R[r1] / R[r2];
    }
    return;
}

void mod(long long int *R, int r1, int r2, int r3){
    if (R[r2] == 0) {
        printf("Error: Modulo by zero\n");
        R[r3] = 0; // Stores 0 to the destination reg
    } else {
        R[r3] = R[r1] % R[r2];
    }
    return;    
}

void printreg(long long int *R, int r){
    printf("\n\t%lld\n\n", R[r]);
    return;
}

//===========================================================================
int iswhite(char c){
    return (c==' '||c=='\t'||c=='\n');
}

int digit(char c){
    return (c>='0'&&c<='9');
}

int isletter(char c){
    return ((c>='A'&&c<='Z')||(c>='a'&&c<='z'));
}

int isnumber(char *s){ // only digit integer
    int i = 0;
    for(i;s[i]!='\0';i++)
        if(!digit(s[i]))
            return 0;
    return 1;
}

int doesexist(const char *line,const char c){
    int i = 0;
    for(i;line[i]!='\0';i++)
        if(line[i]==c)
            return 1;
    return 0;
}

int howmanyexists(const char *line,char c){
    int count = 0,i = 0;
    for(i;line[i]!='\0';i++)
        if(line[i]==c)
            count++;
    return count;
}

void clearstr(char *s) {
    s[0] = '\0';
}

void cleararray(char **token,int maxarg){
    int i = 0;
    for(i;i<maxarg;i++)
        token[i][0] = '\0';
}

int gline(char *s,int maxlen){
    int i,c;
    s[0] = '\0';
    for(i=0;i<maxlen-1&&(c = getchar())!=EOF&&c!='\n';i++)
        s[i] = c;
    s[i] = '\0';
    return i;
}

void inputline(char *line,int maxlen){
    int i = 0,c;
    line[0] = '\0';
    while(1){
        c = getchar();
        if(c=='\n'||c==EOF){
            line[i] = '\0';
            break;
        }
        if(i<maxlen-1)
            line[i++] = c;
        else if(i==maxlen-1){
            printf("\tMaximum character reached!\n\n");
            line[i] = '\0';
            while((c = getchar())!='\n'&&c!=EOF);
            break;
        }
    }
}

int getnum(void){
    int c,n = 0;
    while((c = getchar())!='\n'&&c!=EOF)
        if(digit(c))
            n = 10*n + c - '0';
    return n;
}

void input(char token[MAXARG][MAXLEN],int maxlen,int maxarg){
    int i = 0,j = 0;
    for(int t=0;t<maxarg;t++) // clear first
        token[t][0] = '\0';
    int c = getchar();
    while(i<maxarg){
        while(iswhite(c)&&c!='\n'&&c!=EOF)
            c = getchar();
        if(c==EOF||c=='\n')
            break;
        while(!iswhite(c)&&c!='\n'&&c!=EOF&&j<maxlen-1){
            token[i][j++] = c;
            c = getchar();
        }
        token[i][j] = '\0';
        j = 0;
        i++;
    }
    token[i][0] = '\0';
}

int gettoken(char **token,const char *line,int maxlen,int maxarg){
    int i = 0,j = 0,k = 0;
    for(int t=0;t<maxarg;t++) // clear first
        token[t][0] = '\0';
    while(j<maxarg){
        while(iswhite(line[i]))
            i++;
        if(line[i]=='\0')
            break;
        while(!iswhite(line[i])&&line[i]!='\0'&&k<maxlen)
            token[j][k++] = line[i++];
        token[j][k] = '\0';
        k = 0;
        j++;
    }
    token[j][0] = '\0';
    return j;
}

void printstr(const char *s){
    int i;
    for(i=0;s[i]!='\0';i++)
        putchar(s[i]);
}

int len(const char *s){
    int i = 0;
    for(i;s[i]!='\0';i++);
    return i;
}

void reverse(char *s){
    int i,j;
    for(i=0,j=len(s)-1;i<j;i++,j--){
        char t;
        t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
}

void copy(const char *from,char *to,int maxlen){
    int i;
    to[0] = '\0';
    for(i = 0;i<maxlen-1&&from[i]!='\0';i++)
        to[i] = from[i];
    to[i] = '\0';
}

void copyto(const char *from,char *to,int start,int end,int maxlen){ // 0
    int i,j = 0;
    to[0] = '\0';
    if(start>=maxlen||end<start||end>=maxlen)
        return;
    for(i=start;i<=end&&j<maxlen-1&&from[i]!='\0';)
        to[j++] = from[i++];
    to[j] = '\0';
}

long long int strtoint(const char *s){
    int i = 0,n = 0;
    int sign = 1;
    while(iswhite(s[i]))
        i++;
    if(s[i]=='-'||s[i] == '+'){
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }
    for(;s[i]!='\0';i++)
        if(digit(s[i]))
            n = 10*n + s[i] - '0';
    return sign*n;
}

double strtofloat(const char *s){
    int i = 0;
    double n = 0.0;
    int sign = 1;
    while(iswhite(s[i]))
        i++;
    if(s[i]=='-'||s[i] == '+'){
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }
    for(i;s[i]!='.'&&s[i]!='\0';i++)
        n = 10*n + s[i] - '0';
    if(s[i]=='.')
        i++;
    double m = 1.0;
    for(i;s[i]!='\0';i++){
        m *= 0.1;
        n += (s[i] - '0')*m;
    }
    return sign*n;
}

void inttostr(int n,char *s){
    int i = 0;
    s[0] = '\0';
    if(n == 0){
        s[i++] = '0';
        s[i] = '\0';
        return ;
    }
    int sign = 0;
    if(n<0){
        n = -n;
        sign = -1;
    }
    while(n!=0){
        s[i++] = n % 10 + '0';
        n /= 10;
    }
    if(sign)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int findindex(const char *line,const char *pattern){
    int i,j = 0;
    int l1 = len(line);
    int l2 = len(pattern);
    if(l2>l1)
        return -1;
    int flag = 0;
    for(i = 0;i<=l1-l2&&line[i]!='\0';i++){
        if(pattern[j]==line[i]){
            flag = 1;
            for(j = 0;pattern[j]!='\0';j++){
                if(pattern[j]!=line[i+j]){
                    flag = 0;
                    break;
                }
            }
            if(flag) 
                return i;
        }
    }
    return -1;
}

int findlastindex(const char *line,const char *pattern){
    int i,j = 0;
    int l1 = len(line);
    int l2 = len(pattern);
    if(l2>l1)
        return -1;
    int flag = 0;
    for(i = l1-l2;i>=0&&line[i]!='\0';i--){
        if(pattern[j]==line[i]){
            flag = 1;
            for(j = 0;pattern[j]!='\0';j++){
                if(pattern[j]!=line[i+j]){
                    flag = 0;
                    break;
                }
            }
            if(flag) 
                return i;
        }
    }
    return -1;
}

int isinteger(const char *s){
    int i = 0;
    if(howmanyexists(s,'+')>1||howmanyexists(s,'-')>1)
        return 0;
    int plus = findindex(s,"+");
    int minus = findindex(s,"-");
    if(plus>0||minus>0)
        return 0;
    if(plus==0||minus==0){
        if(len(s)==1)
            return 0;
        i++;
    }
    for(i;s[i]!='\0';i++)
        if(!digit(s[i]))
            return 0;
    return 1;
}

int ispalindrom(const char *s){
    int i,j;
    for(i=0,j=len(s)-1;i<j;i++,j--)
        if (s[i] != s[j])
            return 0;
    return 1;
}

void Sortstr(char *s){ // bubble sort
    int i,j;
    int l = len(s);
    for(i=0;i<l;i++){
        for(j=0;j<l-1;j++){
            if(s[j]>s[j+1]){
                char t;
                t = s[j];
                s[j] = s[j+1];
                s[j+1] = t;
            }
        }
    }
}

void Sort(double *s,int len){
    int i,j;
    for(i=0;i<len;i++){
        for(j=0;j<len-1;j++){
            if(s[j]>s[j+1]){
                double t;
                t = s[j];
                s[j] = s[j+1];
                s[j+1] = t;
            }
        }
    }
}

int binarysearch(const double *sorted,int len,double n){
    int low = 0,high = len - 1;
    while (low <= high){
        int mid = low + (high-low)/2;
        if(sorted[mid]==n)
            return 1;
        else if(sorted[mid]<n)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0;
}

void removespaces(char *s,int maxlen){
    int i,j;
    for(i=0,j=0;j<maxlen-1&&s[i]!='\0';i++){
        if(s[i]!='\t'&&s[i]!=' '&&s[i]!='\n')
            s[j++] = s[i];
    }
    s[j] = '\0';
}

void cutstr(const char *s,char *to,int i1,int i2,int maxlen){ // copy from index i1 to index i2 of *s to *to
    int i = 0,j = 0;
    to[0] = '\0';
    if(i1>i2)
        return;
    for(i=i1;j<maxlen-1&&i<=i2&&s[i]!='\0';)
        to[j++] = s[i++];
    to[j] = '\0';
}

int lower(const char c){
    if(c>='A'&&c<='Z')
        return c + 'a' - 'A';
    return c;
}

int checkword(const char *s1,const char *s2){ // case insensitive
    if(len(s1)!=len(s2))
        return 0;
    int i;
    for(i=0;s1[i]!='\0';i++)
        if(lower(s1[i])!=lower(s2[i]))
            return 0;
    return 1;
}

int checkwordCS(const char *s1,const char *s2){ // case sensitive
    if(len(s1)!=len(s2))
        return 0;
    int i;
    for(i=0;s1[i]!='\0';i++)
        if(s1[i]!=s2[i])
            return 0;
    return 1;
}

void addstring(const char *s1,const char *s2,char *result,int maxlen){
    int i = 0;
    result[0] = '\0';
    for(int j = 0;i<maxlen-1&&s1[j]!='\0';j++)
        result[i++] = s1[j];
    for(int k = 0;i<maxlen-1&&s2[k]!='\0';k++)
        result[i++] = s2[k];
    result[i] = '\0';
}

/*======================================================NUMERIC FUNCTIONS======================================================*/

long long unsigned int power(long long unsigned int a,long long unsigned int b){
    long long unsigned int p = 1;
    while(b!=0){
        p *= a;
        b--;
    }
    return p;
}

int isprime(int n){
    if(n<=1)
        return 0;
    if(n == 2 || n == 3)
        return 1;
    int i,t = n % 6;
    if(t == 5 || t == 1){
        for(i=3;i*i<=n;i+=2){
            if(n%i==0)
                return 0;
        }
        return 1;
    }
    return 0;
}

int iseven(int n){
    return(n % 2 == 0);
}

double dround(double n,int r){
    int sign = 1;
    if(n<0){
        sign = -1;
        n = -n;
    }
    double p = 1;
    while(r!=0){
        p *= 10;
        r--;
    }
    n *= p;
    unsigned int m;
    m = n;
    if(n - m>=0.5)
        m++;
    return sign * (m / p);
}

/*========================================================FILE FUNCTIONS=======================================================*/

int fgetline(char *line,FILE *file,int maxlen){
    int cf,i = 0;
    line[0] = '\0';
    while (i<maxlen-1&&(cf = fgetc(file))!=EOF&&cf!='\n')
        line[i++] = cf;
    if (cf=='\n') {
        line[i++]=' ';
        line[i++]='\n';
    }
    line[i] = '\0';
    return cf;
}

int touchfile(const char *filename){ // touch (create a new file)
    FILE *file;
    file = fopen(filename,"a");
    if(file==NULL)
        return -1;
    fclose(file);
    return 1;
}

void mytouch(const char *filename) {
    if (touchfile(filename) == 1) 
        printf("\n\tFile '%s' created (or updated) successfully.\n\n", filename);
    else 
        printf("\n\tError: Could not create file '%s'.\n\n", filename);
    return;
    
}

int catfile(const char *filename){ // show files contents
    FILE *file;
    file = fopen(filename,"r"); // r for read mode
    if(file==NULL)
        return -1;
    int cf;
    while((cf = fgetc(file))!=EOF)
        putchar(cf);
    fclose(file);
    return 1;
}

void mycat(const char *filename) {
    if (catfile(filename) == 1) 
        putchar('\n');
    else 
        printf("\n\tError: Could not open file '%s'.\n\n", filename);
    return;
}

int grep(const char *filename,const char *pattern,int maxlen){ // search for pattern in a file  
    FILE *file = fopen(filename,"r");
    if(file == NULL)
        return -1;
    char line[maxlen];
    line[0] = '\0';

    while(fgets(line,maxlen,file)!=NULL)
        if(findindex(line,pattern)>=0)
            printf("%s\n",line);

    fclose(file);
    return 1;
}

/*=============================================================================================================================*/


void getcurrentdirectory(char *curdir){  // current directory
    char cwd[MAXLEN];
    cwd[0] = '\0';
    if (getcwd(cwd, sizeof(cwd)) != NULL) // getcwd gets current directory
        copy(cwd,curdir,MAXLEN);
    else
        copy("[directory error]",curdir,MAXLEN);
}

void pwd(void){ 
    char cwd[MAXLEN];
    cwd[0] = '\0';
    if(getcwd(cwd,sizeof(cwd))!=NULL)
        printf("\tCurrent directory: %s\n\n", cwd);
    else
        printf("\tError getting current directory\n\n");
}

int changedir(const char *path){ 
    if(chdir(path) != 0)
        return -1;
    return 0;
}

int conditionalchangedir(const char *path, const char *rootdir) {
    char newpath[MAXLEN];

    // tries to change
    if (chdir(path) != 0) {
        accessdirectory = 1;
        return -1;
    }
    // gets full path after dirchange
    getcurrentdirectory(newpath);

    // checks if newpath starts with rootdir
    if (findindex(newpath, rootdir) != 0) {  
        printf("\tcd: Access denied (cannot leave OS main running directory)\n\n");
        chdir(rootdir);  // restores to rootdir
        accessdirectory = 0; // denied
        return -1;
    }

    accessdirectory = 1; // allows to change
    return 0;  // success
}

void mycls() {
    printf("\033[2J\033[H"); // ANSI escape sequence (\033[2J,[[H,[31m,[0m)
    return;
}

void myshowtime() {
    time_t now = time(NULL); // the time_t stores time value starts from 01/01/1970
    // passing NULL means we just want the current time and not to store it anywhere
    struct tm *t = localtime(&now); // a structure in <time.h> which keeps date and time in a broken form
    if (t == NULL) {
        printf("\n\tError: Unable to get local time.\n\n");
        return;
    }
    printf("\nDate: %02d/%02d/%04d\n", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
    printf("Time: %02d:%02d:%02d\n\n", t->tm_hour, t->tm_min, t->tm_sec);
}

int makedir(const char *path){ // 0 or -1
    return _mkdir(path);
}


char **malloc_2d(int maxarg, int maxlen) {
    char **arr = (char**)malloc(maxarg * sizeof(char*));
    if (!arr) return NULL;

    for (int i = 0; i < maxarg; i++) {
        arr[i] = (char*)malloc(maxlen * sizeof(char));
        if (!arr[i]) {
            for (int j = 0; j < i; j++) free(arr[j]);
            free(arr);
            return NULL;
        }
    }
    return arr;
}

void free_2d(char **arr, int maxarg) {
    if (!arr) return;
    for (int i = 0; i < maxarg; i++) free(arr[i]);
    free(arr);
    return;
}





