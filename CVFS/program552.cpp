///////////////////////////////////////////////////////////////////////////////////
//
//    Program Name :- program552.cpp
//    Description  :- Write a program to understand :-
//                 1.) CreateFile()
//                 2.) USER-DEFINED MACROS FOR ERROR_HANDLING
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
//    USER-DEFINED MACROS FOR ERROR_HANDLING
//
////////////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1

#define ERR_NO_INODES -2

#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_PERMISSION_DENIED -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

#define ERR_MAX_FILES_OPEN -8

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
    else if (strcmp("creat", Name) == 0)
    {
        printf("About : It is used to create a file.\n");
        printf("Usage : create\n");
    }
    else
    {
        printf("No manual entry for %s\n", Name);
    }
}

////////////////////////////////////////////////////////////////
//
//   Function Name :- IsFileExist()
//   Description   :- It is used to check whether file already exist or not.
//   INPUT         :- It accepts file.
//   OUTPUT        :- It returns the true or false.
//   Author Name   :- Aryan Pardeshi
//   Date          :- 16/01/2026
//
////////////////////////////////////////////////////////////////

bool IsFileExist(
    char *name // File Name
)
{
    PINODE temp = head;
    bool bFlag = false;

    while (temp != NULL)
    {
        if ((strcmp(name, temp->FileName) == 0) && (temp->FileType == REGULARFILE))
        {
            bFlag = true;
            break;
        }

        temp = temp->next;
    }

    return bFlag;
}

////////////////////////////////////////////////////////////////
//
//   Function Name :- CreateFile()
//   Description   :- It is used to create a new regular file.
//   INPUT         :- It accepts file name and description.
//   OUTPUT        :- It returns the file descriptor.
//   Author Name   :- Aryan Pardeshi
//   Date          :- 16/01/2026
//
////////////////////////////////////////////////////////////////

int CreateFile(
    char *name,    // name of new file
    int permission // permission for that file
)
{
    PINODE temp = head;
    int i = 0;

    printf("Total number of Inodes remaining : %d\n", superobj.FreeInodes);

    // if name is missing
    if (name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If the permission value is wrong
    // permission -> 1 -> READ
    // permission -> 2 -> WRITE
    // permission -> 3 -> READ + WRITE
    if (permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // If the inodes are full
    if (superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    // If file is already present
    if (IsFileExist(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Search empty Inode
    while (temp != NULL)
    {
        if (temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("There is no Inode.\n");
        return ERR_NO_INODES;
    }

    // Search for empty UFDT Entry
    // Note :- 0,1,2 are reserved.
    for (i = 3; i < MAXOPENFILES; i++)
    {
        if (uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    // UFDT is full
    if (i == MAXOPENFILES)
    {
        return ERR_MAX_FILES_OPEN;
    }

    // Allocate memory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FileTable));

    // Initialize FileTable
    uareaobj.UFDT[i]->ReadOffset = 0;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Mode = permission;

    // Connect File Table with Inode
    uareaobj.UFDT[i]->ptrinode = temp;

    // Initialize elements of Inode
    strcpy(uareaobj.UFDT[i]->ptrinode->FileName, name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;

    // Allocate memory for files data
    uareaobj.UFDT[i]->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);

    superobj.FreeInodes--;

    return i; // File Descriptor
}

////////////////////////////////////////////////////////////////
//
//   Function Name :- LsFile()
//   Description   :- It is used to list all file.
//   INPUT         :- Nothing.
//   OUTPUT        :- Nothing.
//   Author Name   :- Aryan Pardeshi
//   Date          :- 16/01/2026
//
////////////////////////////////////////////////////////////////

void LsFile()
{
    PINODE temp = head;

    printf("---------------------------------------------------\n");
    printf("-------- Marvellous CVFS Files Information --------\n");
    printf("---------------------------------------------------\n");

    while (temp != NULL)
    {
        if (temp->FileType != 0)
        {
            printf("%d\t%s\t%d\n", temp->InodeNumber, temp->FileName, temp->ActualFileSize);
        }

        temp = temp->next;
    }

    printf("---------------------------------------------------\n");
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
    int iRet = 0;

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
            // Marvellous CVFS : > exit
            if (strcmp("exit", Command[0]) == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            // Marvellous CVFS : > ls
            else if (strcmp("ls", Command[0]) == 0)
            {
                LsFile();
            }
            // Marvellous CVFS : > help
            else if (strcmp("help", Command[0]) == 0)
            {
                DisplayHelp();
            }
            // Marvellous CVFS : > clear
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
            // Marvellous CVFS : > man ls
            if (strcmp("man", Command[0]) == 0)
            {
                ManPageDisplay(Command[1]);
            }
        } // End of else if 2

        else if (iCount == 3)
        {
            // Marvellous CVFS : > creat Ganesh.txt 3
            if (strcmp("creat", Command[0]) == 0)
            {
                iRet = CreateFile(Command[1], atoi(Command[2])); // atoi :- ascii to integer

                if (iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Unable to create the files as parameters are invalid.\n");
                    printf("Please refer man page.\n");
                }

                if (iRet == ERR_NO_INODES)
                {
                    printf("Error : Unable to create the file as there is no Inodes.\n");
                }
                if (iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("Error : Unable to create file because the file is already present.\n");
                }
                if (iRet == ERR_MAX_FILES_OPEN)
                {
                    printf("Error : Unable to create file.\n");
                    printf("Max opened files limit reached.\n");
                }

                printf("File gets successfully created with FD %d\n", iRet);
            }
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
// Task :- write() and read() function.