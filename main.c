/*	ENGG1003 Assignment 1
	James Cochrane
	C3206223	
	Due: 29/04/19 
	This program requires the user to manually type input when asked by program.	*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Prototypes */
int line_skip();                                                            // Reads the standard input to the end of the line.
int line_copy();                                                            // Reads the standard input to the end of the line and copy to the standard output.
int pause();                                                                // Ask user to press Enter to continue.
int read_line(char line[], int len);                                        // Read at most len characters from the standard input and ignore the rest of the line.
int find_index(char code[],char char_to_find);                              // Pairs the code alphabet with the normal alphabet
void Ceasarencrypt();                                                       // Encrypts using ceasar cipher
void Ceasardecrypt();                                                       // Decrypts using ceasar cipher
void CeasarbruteForce();                                                    // Displays all possible decyptions
void Subdecrypt();                                                          // Encrypts using substitution cipher
void Subencrypt();                                                          // Decrypts using substitution cipher


int main() {
  int option;

  for (;;) {                                                                // Infinite loop open
    printf("\n-- ENGG1003 Assesment 1 --\n");
    printf("     James Cochrane\n");
    printf("        C3206223\n");
    printf("1: Encrypt with Ceasar cipher\n");
    printf("2: Decrypt with Ceasar cipher\n");
    printf("3: Brute Force a Ceasar cipher text\n");
    printf("4: Encrypt with Substitution cipher\n");
    printf("5: Decrypt with Substitution cipher\n");
    printf("0: Exit\n");
    printf("\n");

    printf("Enter an option: ");                                            // Asks user for menu option
    if ( scanf("%d", &option) != 1 ) {                                      // Conditions for if the user
      if ( feof(stdin) ) break;                                             // inputs letters or symbols
      printf("Invalid option: "); line_copy(); pause();                     // it will print invalid option
      continue;
    }

    line_skip();                                                            // Reads the rest of the line after option number. Usually, it is just one new-line character.

    if (option == 0) break;                                                 // Conditions for main menu, if 0 is sellected the program ends loop and ends program.

    switch(option) {
    case 1: Ceasarencrypt();                               break;           // If 1 is selcted the encrypt prototype runs.
    case 2: Ceasardecrypt();                               break;           // If 2 is selcted the decrypt prototype runs.
    case 3: CeasarbruteForce();                            break;           // If 3 is selcted the bruteForce prototype runs.
    case 4: Subencrypt();                                  break;
    case 5: Subdecrypt();                                  break;
    default:
      printf("Incorrect option: %d\n", option); pause();
    }
  }
  printf("Thankyou!\n");
  return 0;                                                                 // Ends main program.
}

/*Encrypts using ceasar cipher*/
void Ceasarencrypt() {
for (;;) {                                                                  // Infinite loop open.
  int key;                                                                  // Rotation key.
  char stringToEncrpt[256];                                                 // String for user input.
  printf("Enter your string(255 char max): ");
  read_line(stringToEncrpt,256);                                            // Reads what user has written and stores in the string
  printf("Collected String: '%s'\n",stringToEncrpt);
  printf("Enter your rotation key[0-25]: ");                                // Ask user for rotation key.
  if ( scanf("%d", &key) != 1 || key > 25 || key < 0) {                     // Conditions for the rotation key so that the user
    if ( feof(stdin) ) break;                                               // has to select a number between 0 and 25. If not
    printf("Invalid option: "); line_copy(); pause();                       // the loop will print invalid option and what the
    continue;                                                               // user inputed,then runs the puase prototype
  }                                                                         // and then re-starts the infinite loop again.

  int i=0;int k=0;

  while (stringToEncrpt[i] != '\0') {                                       // Condition allows all letters in string to undergo rotation from start to finish once.
    if (stringToEncrpt[i]!=32)                                              // Condition for if sting letter isnt a space
      stringToEncrpt[i] += key;                                             // Encrytption using: string letter = string letter + letter rotations
    i++;                                                                    // Next letter in string.
  }

  while (stringToEncrpt[k] != '\0') {                                       //
    if (stringToEncrpt[k] > 90)                                             // Cleaning up the
        stringToEncrpt[k] -=26;                                             // encrypted text
    k++;                                                                    //
  }

  printf("Encrypted String: %s \n", stringToEncrpt);

  return;
}                                                                           // Infinite loop closed
}

/*Decrypts using ceasar cipher*/
void Ceasardecrypt() {
for (;;) {                                                                  // Infinite loop open
  int key;                                                                  // Rotation key.
  char stringToDecrpt[256];                                                 // String for user input.
  printf("Enter your string(255 char max): ");
  read_line(stringToDecrpt,256);                                            // Reads what user has written and stores in the string
  printf("Collected String: '%s'\n",stringToDecrpt);
  printf("Enter your key[1-25]: ");
  if ( scanf("%d", &key) != 1 || key > 25 || key < 1) {                     // Conditions for the rotation key so that the user
    if ( feof(stdin) ) break;                                               // has to select a number between 0 and 25. If not
    printf("Invalid option: "); line_copy(); pause();                       // the loop will print invalid option and what the
    continue;                                                               // user inputed,then runs the puase prototype
  }                                                                         // and then re-starts the infinite loop again.

  int i=0;int k=0;

  while (stringToDecrpt[i] != '\0') {                                       // Condition allows all letters in string to undergo rotation from start to finish once.
     if ( stringToDecrpt[i]!=32)                                            // Condition for if sting letter isnt a space.
        stringToDecrpt[i] -= key; i++;                                      // Encrytption using: string letter = string letter - letter rotations
  }                                                                         // Next letter in string.

  while (stringToDecrpt[k] != '\0') {                                       //
    if (stringToDecrpt[k] < 65 && stringToDecrpt[k]!=32)                    // Cleaning up the
        stringToDecrpt[k] +=26; k++;                                        // Decrypted text
  }                                                                         //

  printf("Decrypted String: %s", stringToDecrpt);

  return;
}                                                                           // infinite loop closed
}

/*Displays all possible decyptions*/
void CeasarbruteForce() {
  for (;;) {                                                                // Infinite loop open
    char stringToDecrpt[256];                                               // String for user input.
    char workingCopyToDecrpt[256];                                          // String for working decrypt.
    printf("Enter your string(255 char max): ");
    read_line(stringToDecrpt,256);                                          // Reads what user has written and stores in the string
    printf("Collected String: '%s'\n",stringToDecrpt);

    int key=0;
    while (key<26) {                                                        // Creates a while loop so that the prototype can decrypt and print the string with every key possible from 0 to 25.
      int i=0;int k=0;
      strcpy(workingCopyToDecrpt, stringToDecrpt);                          // Uses the same decryption method as the decryption prototype except inside a loop.
      while (workingCopyToDecrpt[i] != '\0') {
        if (workingCopyToDecrpt[i] != 32)
          workingCopyToDecrpt[i] -= key;
        i++;
      }

      while (workingCopyToDecrpt[k] != '\0') {                              // Uses the same cleaning method as the decryption prototype except inside a loop.
        if (workingCopyToDecrpt[k] < 65 && workingCopyToDecrpt[k] != 32)
            workingCopyToDecrpt[k] +=26;
        k++;
      }
    printf("Decrypted String #%d: %s\n", key, workingCopyToDecrpt);
    key++;
    }

    return;
}                                                                           // Infinite loop Closed
}

/*Encrypts using substitution cipher*/
void Subencrypt() {
  for(;;) {
    char message[256];
    char code[26];

    printf("Enter your string(255 char max): ");
    read_line(message, 256);
    printf("Collected String: '%s'\n",message);
    printf("Enter your Sub string(26 char max): ");
    read_line(code,26);
    printf("Collected String: '%s'\n",code);


        int length = strlen(message);                                       // Length of message amd and how much im going to itterate, in this case character buy character.
	    char *encrypted_message = (char *) malloc(sizeof(char)*length);     // Allocate space

            for(int i = 0; i < length; i++){
            int encryption_index = toupper(message[i]) - 'A';               // Makes each letter upper case, checks to see if
            if(encryption_index >= 0 && encryption_index < 26){             // each letter is between A and Z and if so swaps
             encrypted_message[i] = code[encryption_index];                 // each letter with the paired letter from the code alphabet.
            }else{
             encrypted_message[i] = message[i];
	    }
	  }

	  printf("Original Message: %s\nEncrypted Message: %s\n",message,encrypted_message);
    return;
}
}

/*Decrypts using substitution cipher*/
void Subdecrypt() {
  for(;;){
    char message[256];
    char code[26];

    printf("Enter your string(255 char max): ");
    read_line(message, 256);
    printf("Collected String: '%s'\n",message);
    printf("Enter your Sub string(26 char max): ");
    read_line(code,26);
    printf("Collected String: '%s'\n",code);

        int length = strlen(message);                                       // Length of message amd and how much im going to itterate, in this case character buy character
        char *decrypted_message = (char *) malloc(sizeof(char)*length);     // Allocate space

            for(int i = 0; i <length; i++){
            int decryption_index = toupper(message[i]) - 'A';
            if(decryption_index >= 0 && decryption_index < 26){
            int code_index = find_index(code,toupper(message[i]));
             decrypted_message[i] = 'A' + code_index;
            }else {
             decrypted_message[i] = message[i];
                }
            }

    printf("Decrypted Message: %s\n",decrypted_message);
    return;
}
}

/* Reads at most len characters from the standard input and ignore the rest of the line.*/
int read_line(char line[], int len) {
  int ch, i = 0;

  while ((ch = getchar()) != '\n' && ch != EOF)
    if (i < len)
      line[i++] = toupper(ch);

  line[i] = '\0';
  return i;
}

/* Reads the standard input to the end of the line and copy to the standard output.*/
int line_copy() {
  int ch;
  while ( (ch=getchar()) != '\n' && ch != EOF )
    putchar(ch);

  putchar('\n');
  return ch != EOF;
}

/* Reads the standard input to the end of the line.*/
int line_skip() {
  int ch;
  while ( (ch=getchar()) != '\n' && ch != EOF )
    ;
  return ch != EOF;
}

/* Ask user to press Enter to continue. */
int pause() {
  printf("\nPress Enter to continue...");
  return line_skip();
}

/* Pairs the code alphabet with the normal alphabet */
int find_index(char code[],char char_to_find){
  for(int i = 0 ; i < 26; i ++){
    if(code[i] == char_to_find){
      return i;
    }
  }
  return -1;
}
