///////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- program538.cpp
//    Description  :- Write a program to understand return value of scanf().
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//    Day and Date :- WEDNESDAY  |  14/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

int main()
{
    char str[80];
    char Command[4][20];

    int iRet = 0;
    int No1 = 0, No2 = 0;

    printf("Enter two numbers : \n");

    iRet = scanf("%d%d", &No1, &No2);

    printf("First number : %d\n", No1);
    printf("Second number : %d\n", No2);

    printf("Return value of scanf is : %d\n", iRet);

    return 0;
}