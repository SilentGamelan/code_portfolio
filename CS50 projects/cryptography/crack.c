/* crack.c - program to crack DES encrypted passwords of up to 4 characters, plus 2 character salt
*
* Uses brute force method by recursively generating all combinations of letters contained in alphabet[]
* hashing the generated password with the suffixed salt, and returning a match value of 1 if a collision is detected
* ie; there is a match between the given hash and generated hash
*
* Have updated code to eliminate all global variables, instead passing variables into functions where required
* Memory overheads still acceptable as recursion depth is low, and arrays are passed by reference not value
*/

#define HASH_LEN    13
#define SALT_LEN    2
#define PWORD_LEN   4

#define LOWER_START    'a'
#define LOWER_END      'z'
#define UPPER_START    'A'
#define UPPER_END      'Z'

// the length of the "alphabet" of expected characters in password to crack (0-25 AZ 0-25 az), +1 to account for 0-indexing
#define ITERATIONS (LOWER_END - LOWER_START) + (UPPER_END - UPPER_START) + 1

#define _XOPEN_SOURCE

#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


int precrypt(int p_index, int a_index, char password[], char alphabet[], char salt[], char hash[]);
int iterator(int iterator_count, int iterator_depth, char password[], char alphabet[], char salt[], char hash[]);
void fill_alphabet(char alphabet[]);

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("ERROR: %s requires exactly 1 argument\n(usage: %s hash [%d chars])\n", argv[0], argv[0], HASH_LEN);
        return 1;
    }
    else if(strlen(argv[1]) != HASH_LEN){
        printf("ERROR: hash must be %d characters long\n", HASH_LEN);
        return 1;
    }

    char hash[strlen(argv[1])];
    strcpy(hash, argv[1]);

    char alphabet[52];
    fill_alphabet(alphabet);

    // +1 to leave space for \0
    char password[PWORD_LEN + 1];
    char salt[SALT_LEN+1];

    // extract salt from hash
    for(int x = 0; x < SALT_LEN; x++){
        salt[x] = hash[x];
    }
    salt[SALT_LEN] = '\0';

    int match = iterator(0, PWORD_LEN, password, alphabet, salt, hash);

    if( match == 1){
        printf("password is %s\n", password);
    } else{
        printf("No match found.\n");
    }

    return 0;
}



void fill_alphabet(char alphabet[]){
    //use of i removes need to use magic numbers on count to transform count to appropriate letter of alphabet
    int i = 0;
    for(int count = UPPER_START; count <= UPPER_END; count++){
        alphabet[i++] = count;
    }

    for(int count = LOWER_START; count <= LOWER_END; count++){
        alphabet[i++] = count;
    }
}

// recursively works through all letters of alphabet[] (determined by ITERATIONS)
// to a password length determined by iterator depth. iterator count keeps track of current letter of password(ie;current iteration loop)
// two return statements required to handle recursive calls, otherwise will fail to exit when password match reached after first instance
// on both statements, if match found, return 1 otherwise return 0
int iterator(int iterator_count, int iterator_depth, char password[], char alphabet[], char salt[], char hash[]){

    for(int a = 0; a <= ITERATIONS; a++){

        if(precrypt(iterator_count, a, password, alphabet, salt, hash) == 1){
            return 1;
        }

        if(iterator_depth > 1){
          if(iterator(iterator_count+1, iterator_depth-1, password, alphabet, salt, hash) == 1){;
                return 1;
            }
        }
    }

    return 0;
}


// prepares password for hashing by prefixing with salt, and passed to crypt to hash
int precrypt(int p_index, int a_index, char password[], char alphabet[], char salt[], char hash[]){

//    printf("%s\n", password);
//    char c = fgetc(stdin);
//   c = (char)c;
    password[p_index] = alphabet[a_index];
    password[p_index+1] = '\0';

    char *result = crypt(password, salt);
    // if hash and result match, return 1 - indicating password found
   if(strcmp(hash, result) == 0){
            return 1;
    }

    return 0;
 }

