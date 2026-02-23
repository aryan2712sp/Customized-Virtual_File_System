///////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- program549.cpp
//    Description  :- Write a program to understand :-)
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//    Day and Date :- FRIDAY  |  16/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

int main()
{
// Conditional pre-processing
#ifdef _WIN32
    system("dir");
#else
    system("ls");
#endif

    return 0;
}