///////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- program547.cpp
//    Description  :- Write a program to understand :-
//                 1.) clear
//    Author Name  :- Aryan Shailendrasingh Pardeshi
//    Day and Date :- FRIDAY  |  16/01/2026
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

// Type of file in project.
#define REGULARFILE 1
#define SPECIALFILE 2

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
    int FileType;       // File's Type
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
        newn->FileType = 0;
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
//   Function Name :- StartAuxillaryDataInitialization()
//   Description   :- It is used to call such functions which are used to initialize auxillary data.
//   Author Name   :- Aryan Pardeshi
//   Date          :- 13/01/2026
//
////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialization()
{
    strcpy(bootobj.Information, "Booting process Marvellous CVFS is done");

    printf("%s\n", bootobj.Information);

    InitializeSuperBlock();

    CreateDILB();

    InitializeUAREA();

    printf("Marvellous CVFS : Auxillary Data initialized successfully\n\n");
}

////////////////////////////////////////////////////////////////
//
//   Function Name :- DisplayHelp()
//   Description   :- It is used to display the help page.
//   Author Name   :- Aryan Pardeshi
//   Date          :- 14/01/2026
//
////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("---------------------------------------------------\n");
    printf("------------ Marvellous CVFS Help Page ------------\n");
    printf("---------------------------------------------------\n");

    printf("man    : It is used to display manual page.\n");
    printf("clear  : It is used to clear the terminal.\n");
    printf("creat  : It is used to create new file.\n");
    printf("write  : It is used to write the data into file.\n");
    printf("read   : It is used to read the data from the file.\n");
    printf("stat   : It is used to display statisical information.\n");
    printf("unlink : It is used to delete the file.\n");
    printf("exit   : It is used to terminate Marvellous CVFS.\n");

    printf("---------------------------------------------------\n");
}

////////////////////////////////////////////////////////////////
//
//   Function Name :- ManPageDisplay()
//   Description   :- It is used to display man page.
//   Author Name   :- Aryan Pardeshi
//   Date          :- 14/01/2026
//
////////////////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if (strcmp("ls", Name) == 0)
    {
        printf("About : It is used to list the names of all files.\n");
        printf("Usage : ls\n");
    }
    else if (strcmp("man", Name) == 0)
    {
        printf("About : It is used to display manual page.\n");
        printf("Usage : man command_name\n");
        printf("command_name : It is the name of command.\n");
    }
    else if (strcmp("exit", Name) == 0)
    {
        printf("About : It is used to terminate the shell.\n");
        printf("Usage : exit\n");
    }
    else if (strcmp("clear", Name) == 0)
    {
        printf("About : It is used to clear the shell.\n");
        printf("Usage : clear\n");
    }
    else
    {
        printf("No manual entry for %s\n", Name);
    }
}

////////////////////////////////////////////////////////////////
//
//    ENTRY-POINT FUNCTION OF THE PROJECT
//
////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    int iCount = 0;

    StartAuxillaryDataInitialization();

    printf("---------------------------------------------------\n");
    printf("------- Marvellous CVFS started successfully ------\n");
    printf("---------------------------------------------------\n");

    // Infinite Listening Shell
    while (1)
    {
        fflush(stdin);

        strcpy(str, "");

        printf("\nMarvellous CVFS : > ");
        fgets(str, sizeof(str), stdin); // scanf("%s",str);

        iCount = sscanf(str, "%s %s %s %s %s", Command[0], Command[1], Command[2], Command[3], Command[4]);

        fflush(stdin);

        if (iCount == 1)
        {
            if (strcmp("exit", Command[0]) == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            else if (strcmp("ls", Command[0]) == 0)
            {
                printf("Inside ls\n");
            }
            else if (strcmp("help", Command[0]) == 0)
            {
                DisplayHelp();
            }
            else if (strcmp("clear", Command[0]) == 0)
            {
// Conditional pre-processing
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
            }
        } // End of else if 1
        else if (iCount == 2)
        {
            if (strcmp("man", Command[0]) == 0)
            {
                ManPageDisplay(Command[1]);
            }
        } // End of else if 2
        else if (iCount == 3)
        {
        } // End of else if 3
        else if (iCount == 4)
        {
        } // End of else if 4
        else
        {
            printf("Command not found : ");
            printf("Please refer help option to get more information.");
        } // End of else
    } // End of while

    return 0;
} // End of main

// Improvement :- Wrie a Help.txt....all display-driven menu in it and call with help of DisplayHelp().