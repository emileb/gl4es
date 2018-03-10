#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "string_utils.h"

const char* AllSeparators = " \t\n\r.,;()[]{}-<>+*/%&\\\"'^$=!:?";

int CountString(char* pBuffer, const char* S);
char* ResizeIfNeeded(char* pBuffer, int *size, int addsize);

char* InplaceReplace(char* pBuffer, int* size, const char* S, const char* D)
{
    int lS = strlen(S), lD = strlen(D);
    pBuffer = ResizeIfNeeded(pBuffer, size, (lD-lS)*CountString(pBuffer, S));
    char* p = pBuffer;
    while((p = strstr(p, S)))
    {
        // found an occurence of S
        // check if good to replace, strchr also found '\0' :)
        if(strchr(AllSeparators, p[lS])!=NULL) {
            // move out rest of string
            memmove(p+lD, p+lS, strlen(p)-lS+1);
            // replace
            memcpy(p, D, strlen(D));
            // next
            p+=lD;
        } else p+=lS;
    }
    
    return pBuffer;
}

void InplaceInsert(char* pBuffer, const char* S)
{
    char* p = pBuffer;
    int lS = strlen(S), ll = strlen(pBuffer);
    memmove(p+lS, p, ll+1);
    memcpy(p, S, lS);
}

char* GetLine(char* pBuffer, int num)
{
    char *p = pBuffer;
    while(num-- && (p=strstr(p, "\n"))) p+=strlen("\n");
    return (p)?p:pBuffer;
}

int CountLine(const char* pBuffer)
{
    int n=0;
    const char* p = pBuffer;
    while(p=strstr(p, "\n")) {
        p+=strlen("\n");
        n++;
    }
    return n;
}

int CountString(char* pBuffer, const char* S)
{
    char* p = pBuffer;
    int lS = strlen(S);
    int n = 0;
    while((p = strstr(p, S)))
    {
        // found an occurence of S
        // check if good to count, strchr also found '\0' :)
        if(strchr(AllSeparators, p[lS])!=NULL)
            n++;
        p+=lS;
    }
    return n;
}

char* ResizeIfNeeded(char* pBuffer, int *size, int addsize) {
    char* p = pBuffer;
    int newsize = strlen(pBuffer)+addsize+1;
    if (newsize>*size) {
        newsize += 100;
        p = (char*)realloc(pBuffer, newsize);
        *size=newsize;
    }
    return p;
}

char* Append(char* pBuffer, int* size, const char* S) {
    char* p =pBuffer;
    p = ResizeIfNeeded(pBuffer, size, strlen(S));
    strcat(p, S);
    return p;
}