#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(char *s){
    int n;

    scanf("%d", &n);

    s[n-1] = 1;
}

void remove(char *s){
    int n;

    scanf("%d", &n);

    s[n-1] = 0;
}

void check(char *s){
    int n;

    scanf("%d", &n);

    printf("%hhd \n", s[n-1]);
}

void toggle(char *s){
    int n;

    scanf("%d", &n);

    s[n-1] = !s[n-1];
}

void all(char *s){
    for (int i=0; i<20; ++i) s[i] = 1;
}

void empty(char *s){
    for (int i=0; i<20; ++i) s[i] = 0;
}

void solution(char *s){
    char cmd[7];

    scanf("%s", cmd);

    if (!strcmp(cmd, "add")) add(s);
    else if (!strcmp(cmd, "remove")) remove(s);
    else if (!strcmp(cmd, "check")) check(s);
    else if (!strcmp(cmd, "toggle")) toggle(s);
    else if (!strcmp(cmd, "all")) all(s);
    else if (!strcmp(cmd, "empty")) empty(s);
}

int main(){
    int m;
    char *s;

    scanf("%d", &m);

    s = (char*)calloc(20, sizeof(char));

    for (int i=0; i<m; ++i){
        solution(s);
    }

    free(s);

    return 0;
}