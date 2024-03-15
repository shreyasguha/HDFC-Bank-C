#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void displaydatabase();
void databaseaccess();
void start();
int isStringOnlyIntegers(const char *str);
int isValidPassword(const char *password);


//--------------------------------------------RETURNS 1 IF THE STRING HAS NO INTEGERS, 0 OTHERWISE-------------------------------------------
int isStringOnlyIntegers(const char *str)
{
   for (int i = 0; str[i] != '\0'; i++)
   {
      if (!isdigit(str[i]))
         return 0;
   }
   return 1;
}


//-----------------RETURNS 0 IF PASSWORD EITHER HAS NO SPECIAL CHARACTERS OR HAS NO NUMBERS, RETURNS NON-ZERO VALUE OTHERWISE----------------
int isValidPassword(const char *password)
{
   int length = strlen(password);

   if (length < 8)
      return 0; // Password length is less than 8 characters

   int hasInteger = 0;
   int hasSymbol = 0;

   for (int i = 0; i < length; i++)
   {
      if (isdigit(password[i]))
         hasInteger = 1;
      else if (!isalnum(password[i]))
         hasSymbol = 1;
   }

   return (hasInteger * hasSymbol);
}



//----------------------------------------------------DEFINING THE STRUCTURE OF A BANK USER--------------------------------------------------
typedef struct
{
   char username[50];
   int age;
   char gender[50];
   char passcode[30];
   char phone[15];
   char mail[50];
   int balance;
} account;



//-------------------------------------------------------DECLARING SOME GLOBAL VARIABLES-----------------------------------------------------
int b1 = 0, nou = 0, b2 = 0;
char a1, a2, a3;
char *s1, *masterkey;
account user[100];


//------------------DEFAULT USERNAME OF A USER IS SET TO "NEXT", FUNCTION DISPLAYS THE USER DETAILS OF ALL THE CURRENT USERS-----------------
void displaydatabase()
{
   for (int i = 0; i < 100; i++)
   {
      if (strcmp(user[i].username, "NEXT") != 0)
         printf("Account %i: username: %s, age: %i, gender: %s, passcode: %s, phone number: %s, mail id: %s, account balance: ₹%i\n", i + 1, user[i].username, user[i].age, user[i].gender, user[i].passcode, user[i].phone, user[i].mail, user[i].balance);
      else
         break;
   }
}



//-----KEEPS IN CHECK THE MECHANISM OF AN EMPLOYEE ACCESSING THE DATABASE, IF INCORRECT MASTERKEY IS ENTERED 3 TIMES, THE FUNCTION EXITS-----
void databaseaccess()
{
   if (b1 < 3)
   {
      printf("Enter masterkey: ");
      s1 = malloc(sizeof(char) * 20);
      scanf("%s", s1);
      if (strcmp(s1, masterkey) == 0)
      {
         printf("Unlocked\n");
         displaydatabase();
         printf("Enter 'm' to go to main page\n");
         char h;
         scanf(" %c", &h);
         if (h == 'm')
            start();
      }
      else
      {
         printf("Wrong password\n");
         b1++;
         databaseaccess();
      }
   }
   else if (b1 == 3)
   {
      printf("Too many incorrect attempts\n");
      exit(0);
   }
}



//--------------------------------THE START FUNCTION WHICH IS RESPONSIBLE FOR THE FUNCTIONING OF THE WHOLE SYSTEM----------------------------
void start()
{
   masterkey = "AbcdEfg";
   printf("\nHI! WELCOME TO HDFC BANK\nPress 'e' if you're an employee or 'c' if you're a customer. Press 't' at any time to exit  ");
   scanf(" %c", &a1);

   //--------------------------------------------------------------------EMPLOYEE LOOP
   if (a1 == 'e') 
   {
      printf("\nEnter 'a' to access database\nEnter 'b' to go back\n\n");
      scanf(" %c", &a2);
      if (a2 == 'b')
         start();
      if (a2 == 'a')
         databaseaccess();
   }

   //--------------------------------------------------------------------EXIT------
   else if (a1 == 't') // EXIT
   {
      printf("\nThank you for visiting HDFC bank, have a lovely day\n");
      exit(0);
   }

   //--------------------------------------------------------------------CUSTOMER LOOP
   else if (a1 == 'c') 
   {
      printf("\nWELCOME\n");
      printf("Enter 'o' to open a bank account\nEnter 'a' to access the existing account\nEnter 'b' to go back\n\n");
      scanf(" %c", &a3);
      //-----------------------------------OPENING AN ACCOUNT
      if (a3 == 'o')
      {
         user[nou].balance = 0;
         char confirmation;
         printf("\nEnter username: ");
         scanf(" %[^\n]", user[nou].username);

         //----------CHECK VALID USERNAME
         for (int i = 0; i < 100; i++)
         {
            int x = 0;
            for (int i = 0; i < nou; i++)
            {
               if (strcmp(user[i].username, user[nou].username) == 0)
               {
                  x++;
               }
            }
            if (x != 0)
            {
               printf("\nAccount with this username already exists.");
               printf("\nEnter a different username: ");
               scanf(" %[^\n]", user[nou].username);
            }
            else
               break;
         }
         printf("Enter age: ");
         scanf("%d", &user[nou].age);
         printf("Enter gender\nPress 'm' for male\nPress 'f' for female\n");
         scanf("%s", user[nou].gender);
         for (int i = 0; i < 100; i++)
         {
            if (strcmp(user[nou].gender, "m") != 0 && strcmp(user[nou].gender, "f") != 0)
            {
               printf("Enter a valid gender: ");
               scanf("%s", user[nou].gender);
            }
            else
               break;
         }

         //-------------------------------TAKE IN PASSWORD AND CHECK VALID PASSWORD
         printf("Enter passcode for the account (It must have at least 1 integer, 1 symbol and must be at least 8 characters long): ");
         scanf(" %s", user[nou].passcode);
         char pas_conf[50];
         for (int i = 0; i < 100; i++)
         {
            if (isValidPassword(user[nou].passcode) == 0)
            {
               printf("Enter a valid password: ");
               scanf(" %s", user[nou].passcode);
            }
            else
            {
               printf("Please confirm your password: ");
               scanf(" %s", pas_conf);
               if (strcmp(pas_conf, user[nou].passcode) == 0)
               {
                  break;
               }
               else
               {
                  printf("Confirmation password and original password do not match");
                  printf("\nEnter passcode for the account (It must have at least 1 integer, 1 symbol and must be at least 8 characters long): ");
                  scanf(" %s", user[nou].passcode);
               }
               
            }
         }

         printf("Link your phone number to your account number: ");
         scanf(" %s", user[nou].phone);

         //-----------------------------------ENSURE THE PHONE NUMBER ENTERED IS VALID
         for (int i = 0; i < 100; i++)
         {
            if (strlen(user[nou].phone) == 10 && isStringOnlyIntegers(user[nou].phone) != 0)
               break;
            else
               printf("Enter a valid phone number: ");
            scanf("%s", user[nou].phone);
         }

         printf("Link your email to your account: ");
         scanf(" %s", user[nou].mail);

         printf("Would you like to deposit some money? y/n\n");
         scanf(" %c", &confirmation);


         //-----------------------------------DEPOSIT MONEY WHILE CREATING ACCOUNT
         for (int i = 0; i < 100; i++)
         {
            if (confirmation != 'y' && confirmation != 'n')
            {
               printf("Type y or n: ");
               scanf(" %c", &confirmation);
            }
            else if (confirmation == 'y')
            {
               printf("Enter amount to be deposited: ₹");
               scanf("%i", &user[nou].balance);
               break;
            }
            else
               break;
         }

         nou++;
         strcpy(user[nou].username, "NEXT");
         printf("\nYour bank account has been opened. Thank you for choosing HDFC bank!\n");
         start();
      }


      //-------------------------------------GO BACK
      else if (a3 == 'b')
         start();

      //-------------------------------------ACCESS YOUR ACCOUNT AS A CUSTOMER
      else if (a3 == 'a')
      {
         char name[100], pass[100];
         int index, b3 = 0;
         printf("Enter username: ");
         scanf(" %[^\n]", name);
         for (int i = 0; i < 100; i++)
         {
            if (strcmp(user[i].username, name) == 0)
            {
               index = i;
               b3++;
               break;
            }
         }


         //---------------------------------CHECK IF ACCOUNT EXISTS
         if (b3 != 0)
         {

            printf("Enter passcode: ");
            scanf("%s", pass);

            //-----------------ACCESS TO ACCOUNT IF PASSWORD IS VALID
            if (strcmp(user[index].passcode, pass) == 0)
            {
               char v;
               printf("\n\nUnlocked\n");
               printf("username: %s\nage: %i\ngender: %s\npasscode: %s\nphone number: %s\nmail id: %s\naccount balance: ₹%i\n", user[index].username, user[index].age, user[index].gender, user[index].passcode, user[index].phone, user[index].mail, user[index].balance);
               printf("Enter 'w' to withdraw money, 'd' to deposit money, 'e' to edit account details, 'b' to go to start\n");
               scanf(" %c", &v);
               if (v == 'b')
                  start();
               
               //---------DEPOSIT MORE MONEY
               else if (v == 'd')
               {
                  int v1;
                  printf("Enter amount: ₹");
                  scanf("%i", &v1);
                  user[index].balance += v1;
                  printf("Available balance: ₹%d", user[index].balance);
                  start();
               }

               //---------WITHDRAW MONEY
               else if (v == 'w')
               {
                  int v2;
                  printf("Enter amount: ₹");
                  scanf("%d", &v2);
                  if (v2 > user[index].balance)
                  {
                     printf("\nInsufficient balance\n");
                     start();
                  }

                  else
                  {
                     user[index].balance = user[index].balance - v2;
                     printf("\nAvailable balance: ₹%d\n", user[index].balance);
                     start();
                  }
               }

               //----------EDIT DETAILS
               else if (v == 'e')
               {
                  char y;
                  printf("Enter 'u' to edit username.\nEnter 'p' to edit passcode.\nEnter 'n' to change linked phone number.\nEnter 'e' to edit linked e-mail.\nEnter 'b' to return to main menu.\n");
                  scanf(" %c", &y);
                  for (int i = 0; i < 100; i++)
                  {
                     if (y == 'u')
                     {
                        char p1;
                        char z[100];
                        char new[100];
                        printf("Enter new username: ");
                        scanf(" %[^\n]", z);
                        for (int i = 0; i < 100; i++)
                        {
                           if (strcmp(z, user[index].username) == 0)
                           {
                              printf("Same username.\nEnter new username: ");
                              scanf(" %[^\n]", z);
                           }
                           else
                           {

                              for (int i = 0; i < 100; i++)
                              {
                                 int x = 0;
                                 for (int i = 0; i < nou; i++)
                                 {
                                    if (strcmp(user[i].username, z) == 0)
                                    {
                                       x++;
                                    }
                                 }
                                 if (x != 0)
                                 {
                                    printf("\nAccount with this username already exists.");
                                    printf("\nEnter a different username: ");
                                    scanf(" %[^\n]", z);
                                 }
                                 else
                                    break;
                              }

                              printf("Press 'c' to Confirm username.\nPress 'b' to go to start.\n ");
                              scanf(" %c", &p1);
                              for (int i = 0; i < 100; i++)
                              {
                                 if (p1 == 'c')
                                 {
                                    printf("confirm username: ");
                                    scanf(" %[^\n]", new);
                                    for (int i = 0; i < 100; i++)
                                    {
                                       if (strcmp(new, z) == 0)
                                       {
                                          strcpy(user[index].username, new);
                                          printf("Your username has been changed\n");
                                          start();
                                          break;
                                       }
                                       else
                                       {
                                          printf("Username mismatch.\n");
                                          printf("confirm username: ");
                                          scanf(" %[^\n]", new);
                                       }
                                    }
                                 }
                                 else if (p1 == 'b')
                                 {
                                    start();
                                    break;
                                 }
                                 else
                                 {
                                    printf("Invalid key");
                                    printf("Press 'c' to Confirm username.\nPress 'b' to go to start.\n ");
                                    scanf("%c", &p1);
                                 }
                              }
                           }
                        }
                     }
                     else if (y == 'p')
                     {
                        char p2;
                        char z2[100];
                        char new2[100];
                        printf("Enter new passcode: ");
                        scanf(" %[^\n]", z2);
                        for (int i = 0; i < 100; i++)
                        {
                           if (strcmp(z2, user[index].passcode) == 0)
                           {
                              printf("Same passcode.\nEnter new passcode: ");
                              scanf(" %[^\n]", z2);
                           }
                           else
                           {
                              for (int i = 0; i < 100; i++)
                              {
                                 if (isValidPassword(z2) == 0)
                                 {
                                    printf("Enter a valid password: ");
                                    scanf(" %s", z2);
                                 }
                                 else
                                    break;
                              }
                              printf("Press 'c' to Confirm passcode.\nPress 'b' to go to start.\n ");
                              scanf(" %c", &p2);
                              for (int i = 0; i < 100; i++)
                              {
                                 if (p2 == 'c')
                                 {
                                    printf("confirm passcode: ");
                                    scanf(" %[^\n]", new2);
                                    for (int i = 0; i < 100; i++)
                                    {
                                       if (strcmp(new2, z2) == 0)
                                       {
                                          strcpy(user[index].passcode, new2);
                                          printf("Your passcode has been changed.");
                                          start();
                                          break;
                                       }
                                       else
                                       {
                                          printf("passcode mismatch.\n");
                                          printf("confirm passcode: ");
                                          scanf(" %[^\n]", new2);
                                       }
                                    }
                                 }
                                 else if (p2 == 'b')
                                 {
                                    start();
                                    break;
                                 }
                                 else
                                 {
                                    printf("Invalid key");
                                    printf("Press 'c' to Confirm passcode.\nPress 'b' to go to start.\n ");
                                    scanf("%c", &p2);
                                 }
                              }
                           }
                        }
                     }
                     else if (y == 'n')
                     {
                        char p3;
                        char z3[100];
                        char new3[100];
                        printf("Enter new phone number: ");
                        scanf(" %[^\n]", z3);
                        for (int i = 0; i < 100; i++)
                        {
                           if (strcmp(z3, user[index].phone) == 0)
                           {
                              printf("Same phone number.\nEnter new phone number: ");
                              scanf(" %[^\n]", z3);
                           }
                           else
                           {
                              for (int i = 0; i < 100; i++)
                              {
                                 if (strlen(z3) == 10 && isStringOnlyIntegers(z3) != 0)
                                    break;
                                 else
                                    printf("Enter a valid phone number: ");
                                 scanf("%s", z3);
                              }
                              printf("Press 'c' to Confirm phone number.\nPress 'b' to go to start.\n ");
                              scanf(" %c", &p3);
                              for (int i = 0; i < 100; i++)
                              {
                                 if (p3 == 'c')
                                 {
                                    printf("confirm phone number: ");
                                    scanf(" %[^\n]", new3);
                                    for (int i = 0; i < 100; i++)
                                    {
                                       if (strcmp(new3, z3) == 0)
                                       {
                                          strcpy(user[index].phone, new3);
                                          printf("Your phone number has been changed.");
                                          start();
                                          break;
                                       }
                                       else
                                       {
                                          printf("phone number mismatch.\n");
                                          printf("confirm phone number: ");
                                          scanf(" %[^\n]", new3);
                                       }
                                    }
                                 }
                                 else if (p3 == 'b')
                                 {
                                    start();
                                    break;
                                 }
                                 else
                                 {
                                    printf("Invalid key");
                                    printf("Press 'c' to Confirm phone number.\nPress 'b' to go to start.\n ");
                                    scanf("%c", &p3);
                                 }
                              }
                           }
                        }
                     }
                     else if (y == 'e')
                     {
                        char p4;
                        char z4[100];
                        char new4[100];
                        printf("Enter new e-mail id: ");
                        scanf(" %[^\n]", z4);
                        for (int i = 0; i < 100; i++)
                        {
                           if (strcmp(z4, user[index].mail) == 0)
                           {
                              printf("Same e-mail id.\nEnter new e-mail id: ");
                              scanf(" %[^\n]", z4);
                           }
                           else
                           {

                              printf("Press 'c' to Confirm e-mail id.\nPress 'b' to go to start.\n ");
                              scanf(" %c", &p4);
                              for (int i = 0; i < 100; i++)
                              {
                                 if (p4 == 'c')
                                 {
                                    printf("confirm e-mail id");
                                    scanf(" %[^\n]", new4);
                                    for (int i = 0; i < 100; i++)
                                    {
                                       if (strcmp(new4, z4) == 0)
                                       {
                                          strcpy(user[index].mail, new4);
                                          printf("Your e-mail id has been changed.");
                                          start();
                                          break;
                                       }
                                       else
                                       {
                                          printf("e-mail id mismatch.\n");
                                          printf("confirm e-mail id: ");
                                          scanf(" %[^\n]", new4);
                                       }
                                    }
                                 }
                                 else if (p4 == 'b')
                                 {
                                    start();
                                    break;
                                 }
                                 else
                                 {
                                    printf("Invalid key");
                                    printf("Press 'c' to e-mail id.\nPress 'b' to go to start.\n ");
                                    scanf("%c", &p4);
                                 }
                              }
                           }
                        }
                     }
                     else if (y == 'b')
                        start();
                     else
                     {
                        printf("Invalid key\nEnter a valid key\n");
                        scanf("%c", &y);
                     }
                  }
               }
            }

            else
            {
               printf("Incorrect password\n");
               start();
            }
         }

         else
         {
            printf("User not found\n");
            start();
         }
      }

      else
      {
         printf("Invalid key\n");
         start();
      }
   }
   else
   {
      printf("Invalid key\n");
      start();
   }
}


//----------------------------------------------------------------MAIN FUNCTION--------------------------------------------------------------
int main()
{
   start();
   return 0;
}