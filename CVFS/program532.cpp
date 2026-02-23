///////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- program532.cpp
//    Description  :- Write a program to understand :-
//                 1.) CreateDILB()
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//    Day and Date :- TUESDAY  |  13/01/2026
//
///////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//
//    HEADER FILE INCLUSION
//
////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>

////////////////////////////////////////////////////////////////
//
//    USER-DEFINED MACROS
//
////////////////////////////////////////////////////////////////

// Maximum file size that we allow in the project.
#define MAXFILESIZE 500

// Maximum file we can open in the project.
#define MAXOPENFILES 20

// Maximum inodes in the project.
#define MAXINODE 5

// Tasks in the project.
#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

////////////////////////////////////////////////////////////////
//
//    USER-DEFINED STRUCTURES
//
////////////////////////////////////////////////////////////////
//
//    STRUCTURE NAME : BootBlocK
//    DESCRIPTION    : HOLDS THE INFORMATION TO BOOT THE O.S.
//
////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

////////////////////////////////////////////////////////////////
//
//    STRUCTURE NAME : SuperBlocK
//    DESCRIPTION    : HOLDS THE INFORMATION ABOUT FILE SYSTEM.
//
////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

////////////////////////////////////////////////////////////////
//
//    STRUCTURE NAME : Inode
//    DESCRIPTION    : HOLDS THE INFORMATION ABOUT FILE.
//
////////////////////////////////////////////////////////////////

struct Inode
{
    char FileName[20];  // File's name
    int InodeNumber;    // Inode's number
    int FileSize;       // file's size
    int ActualFileSize; // Actual file's size
    int ReferenceCount; // Reference count
    int Permission;     // Permission
    char *Buffer;       // Buffer
    struct Inode *next; // Pointer to travel to next
};

typedef struct Inode INODE;
typedef struct Inode *PINODE;
typedef struct Inode **PPINODE;

////////////////////////////////////////////////////////////////
//
//    STRUCTURE NAME : FileTable
//    DESCRIPTION    : HOLDS THE INFORMATION ABOUT OPENED FILE.
//
////////////////////////////////////////////////////////////////

struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable *PFILETABLE;

////////////////////////////////////////////////////////////////
//
//    STRUCTURE NAME : UAREA
//    DESCRIPTION    : HOLDS THE INFORMATION ABOUT PROCESS.
//
////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};

////////////////////////////////////////////////////////////////
//
//    Global Variables or objects used in the project
//
////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL;

////////////////////////////////////////////////////////////////
//
//   Function Name :- InitializeUAREA()
//   Description   :- It is used to initialize UAREA members.
//   Author Name   :- Aryan Pardeshi
//   Date          :- 13/01/2026
//
////////////////////////////////////////////////////////////////

void InitializeUAREA()
{
    strcpy(uareaobj.ProcessName, "Myexe");

    int i = 0;

    for (i = 0; i < MAXOPENFILES; i++)
    {
        uareaobj.UFDT[i] = NULL;
    }
    printf("Marvellous CVFS : UAREA gets initialized successfully\n");
}

////////////////////////////////////////////////////////////////
//
//   Function Name :- InitializeSuperBlock()
//   Description   :- It is used to initialize Super block members.
//   Author Name   :- Aryan Pardeshi
//   Date          :- 13/01/2026
//
////////////////////////////////////////////////////////////////

void InitializeSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Marvellous CVFS : Super Block gets initialized successfully\n");
}

////////////////////////////////////////////////////////////////
//
//   Function Name :- CreateDILB()
//   Description   :- It is used to create LinkedList of Inodes.
//   Author Name   :- Aryan Pardeshi
//   Date          :- 13/01/2026
//
////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for (i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(Inode));

        strcpy(newn->FileName, "\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0;
        newn->Buffer = 0;
        newn->next = NULL;

        if (temp == NULL) // LL is empty
        {
            head = newn;
            temp = head;
        }
        else // LL contains atleast 1 node
        {
            temp->next = newn;
            temp = temp->next;
        }
    }
    printf("Marvellous CVFS : DILB created successfully\n");
}

////////////////////////////////////////////////////////////////
//
//    ENTRY-POINT FUNCTION OF THE PROJECT
//
////////////////////////////////////////////////////////////////

int main()
{

    return 0;
}
