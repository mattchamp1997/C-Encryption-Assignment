/* Assignment 2 - Security Authorisation
Matthew Champion
02/03/17
Borland
Windows 10 x64
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 4

//Declare Prototypes
int displaymenu(void);
int entercode(int[]);
int encrypt(int[]);
void verify(int[], int[]);
int decrypt(int[]);
void codeattempts(int*,int*);
int exitprogram(int*);

int main()
{
    int access_code[SIZE]={4,5,2,3};
    int usercode[SIZE];
    int menu;
    int encryptcount=0;
    int correct,incorrect=0;
    int i;

    menu = displaymenu();
    
    while (menu != 6)
    {
        if (menu==1)
        {
            usercode[SIZE] = entercode(usercode);    //Call prototype for enter code
            printf("Code has been entered successfully\n\n");
            menu = displaymenu();
        }//end option 1
        
        if (menu==2)
        {
            if (encryptcount!=0) //If code has already been encrypted
            {
                printf("Error: Code has already been encrypted\n\n");
                menu = displaymenu();
            }
            else    //If code has not yet been encrypted
            {
                usercode[SIZE] = encrypt(usercode);
                printf("Code has been successfully encrypted\n\n");
                menu = displaymenu();
                encryptcount++;
            }
            
        }//end option 2
        
        if (menu==3)
        {
            if (encryptcount!=1)
            {
                printf("Only encrypted codes can be verified. Please enter a code and encrypt it.\n\n");
                menu = displaymenu();
            }
            else
            {
                verify(access_code, usercode);
                menu = displaymenu();
            }
            
        }//end option 3
        
        if (menu==4)
        {
            if (encryptcount==1)
            {
                usercode[SIZE] = decrypt(usercode);
                printf("Code has been successfully decrypted\n\n");
                menu = displaymenu();
            }
            
            else
            {
                printf("Error: Code has not been encrypted\n\n");
                menu = displaymenu();
            }
            
            encryptcount=0;
            
        }//end option 4
        
        if (menu==5)
        {
            codeattempts(&correct,&incorrect);
            menu = displaymenu();
        }//end option 5
        
    }//end while
    
    if (menu == 6)
    {
        printf("Press ENTER again to EXIT\n");
    }
    
    getchar();
    return(0);
}//End main

//Implement display menu
int displaymenu()
{
    int option;
    
    do
    {
        printf("Welcome. Please select a menu option.\n\n \
        1. Enter code\n \
        2. Encrypt code\n \
        3. Verify if correct\n \
        4. Decrypt code\n \
        5. Display number of times the code was entered correctly and incorrectly\n \
        6. Exit program\n ");
        scanf("%d", &option); //read in selected menu option
        flushall();
    }
    while ((option<1) || (option>6));   //Show menu while an option between 1 and 6 is not selected
        
    return(option); //Return menu option chosen by user
}

// 1. Implement function entercode
int entercode(int usercode[])
{
    int i;
    
    printf("Enter 4 separate integers as a security code\n");
    
    for(i=0; i<SIZE; i=i+1)
    {
        scanf("%d", usercode[i]);
        flushall();
        
        //If digit of code is negative int or greater than 9, ask again for the incorrectly entered element, not the whole code
        if ((usercode[i]<0) || (usercode[i]>9))
        {
            printf("Error: Please choose an integer 0-9 \n");
            scanf("%d", &usercode[i]);
            flushall();
        }//end if
    }//end for
    
    return(usercode[SIZE]);
}   //end entercode

// 2. Function to encrypt user entered code
int encrypt(int codeuser[])
{
    int i,tmp1;
    
    //Encryption algorithm
    for (i=0; i<SIZE; i++);
    {
        codeuser[i] = codeuser[i]+1;
        
        if (codeuser[i] == 10)
        {
            codeuser[i] = 0;
        }
    }
    
    //Swap 1st number and 3rd number
    tmp1 = codeuser[0];
    codeuser[0] = codeuser[2];
    codeuser[2] = tmp1;
    
    //Swap 2nd number and 4th number
    tmp1 = codeuser[1];
    codeuser[1] = codeuser[3];
    codeuser[3] = tmp1;
    
    for(i=0; i<SIZE; i++)
    {
        printf("%d ", codeuser[i]);
    }
    
    return (codeuser[SIZE]);
    
}

// 3. Implement whether codes are the same or not - VERIFY
void verify (int access[], int user[])
{
    //If all elements are equal, print correct code, else print ERROR
    if ((access[0]==user[0]) && (access[1]==user[1]) && (access[2]==user[2]) && (access[3]==user[3]))
    {
        printf("CORRECT CODE\n");
    }
    else
    {
        printf("ERROR CODE\n");
    }
    
}

// 4. Decrypt previously encrypted code
int decrypt (int codeuser[])
{
    int i;
    int tmp1;
    
    //Algorithm to decrypt
    for (i=0; i<SIZE; i++);
    {
        codeuser[i] = codeuser[i]-1;
        
        if (codeuser[i] == -1)
        {
            codeuser[i] = 9;
        }
    }
    
    //Swap 1st number and 3rd number
    tmp1 = codeuser[0];
    codeuser[0] = codeuser[2];
    codeuser[2] = tmp1;
    
    
    //Swap 2nd number and 4th number
    tmp1 = codeuser[1];
    codeuser[1] = codeuser[3];
    codeuser[3] = tmp1;


    return (codeuser[SIZE]);    //Return decrypted array
    
}

// 5. Print correct and incorrect code attempts
void codeattempts(int *cor,int *incor)
{
    printf("Correct attempts: %d\n", *cor);
    printf("Incorrect attempts: %d\n\n", *incor);
}



