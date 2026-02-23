///////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- program541.cpp
//    Description  :- Write a program to understand return value of scanf().
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//    Day and Date :- WEDNESDAY  |  14/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

int main()
{
    char str[80] = "India is my country";
    char Command[4][20];
    int iRet = 0;

    iRet = sscanf(str, "%s %s %s %s", Command[0], Command[1], Command[2], Command[3]);

    printf("Return value : %d\n", iRet);

    printf("%s\n", Command[0]);
    printf("%s\n", Command[1]);
    printf("%s\n", Command[2]);
    printf("%s\n", Command[3]);

    return 0;
}