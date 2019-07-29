/** vigenere.c : program to take a single commandline argument [keytext], prompt for [plaintext], and then encrypt 
 *               it according to vigenere's cypher
 */
 
 #include <stdio.h>
 #include <cs50.h>
 #include <string.h>
 
 // defines the upper and lower bound values for chars (LOWER and UPPER cases - note upper case has lower value)
 #define LOWER_START    97
 #define LOWER_END      122
 
 #define UPPER_START    65
 #define UPPER_END      90
 
 // offset between upper and lower case character ranges in ASCII
 #define CASE_OFFSET    32
 
 // argc [argument count] always >=1, calling program name is the first argument, and will hence always be val of argv[0]
int main(int argc, char *argv[])
{
    
    if(argc == 1 || argc > 2) {
        printf("Sorry %s requires precisely 1 argument (alphabetic characters only)\n", argv[0]);
        return(1);
    } 
    
    int key_length = strlen(argv[1]);

    // couldn't initalize string type with this syntax, so forced to make char array and key_length+1 to give space for \0
    char key_text[key_length + 1];
    strcpy(key_text, argv[1]);
    
    for(int x = 0; x < key_length; x++){
        
        // error catching for non-alphabetic characters within key_text
        if(key_text[x] < UPPER_START || ( key_text[x] > UPPER_END && key_text[x] < LOWER_START) || key_text[x] > LOWER_END){
            printf("ERROR: Input must contain only alphabetic characters\n");
            return 1;
        }
        else if(key_text[x] >= LOWER_START && key_text[x]<= LOWER_END){
            // convert lower case to upper case - makes processing ciphertext easier
            key_text[x] = key_text[x] - 32;
        }
    }
    

    printf("plaintext:  ");
    string plain_text = get_string();
        
    int plain_text_length = strlen(plain_text);
    
    // strlen DOESNT include the NULL terminator!
    char cipher_text[plain_text_length + 1];
    
    // will allow us to cycle through the characters of the keytext without creating another string filled with repeated key.
    int cipher_counter = 0;
    
    // design spec states non-alpha chars in plain_text are not encrypted - when hit, the current key_text char to be 
    // applied to next alpha instead. This is controlled by cipher_counter var and step_counter flag
    bool step_counter = true; 
        
    for(int x = 0; x < plain_text_length; x++){
        
        step_counter = true;
        
        // add plain to cipher, apply negative offset to bring to 0 (based on ASCII alphabet placement)
        // apply mod %26 as per algorithm - manages rollover from end of alphabet to beginning where necessary
        // reapply UPPER or LOWER case ASCII offset to give desired value in cipher_text[x]
        if(plain_text[x] >= UPPER_START && plain_text[x] <= UPPER_END){
            
            cipher_text[x] = ( ( ( (plain_text[x] + key_text[cipher_counter]) % UPPER_START) % 26) + UPPER_START); 
            
        } 
        else if( (plain_text[x] >= LOWER_START) &&  plain_text[x] <= LOWER_END){
            // CASE_OFFSET applied to match cases of cipher_text[] and plain_text[] (treats cipher_text[] as lower case)
            cipher_text[x] = ((((plain_text[x] + key_text[cipher_counter] + CASE_OFFSET)  % LOWER_START) % 26) + LOWER_START); 
            
        }
        else{
        // if not an alpha char, then transcribe without encrypting, and don't progress the cipher_counter so that
        // the current key_text[] char will be used to encrypt the next alpha char in plain_text[] instead
            cipher_text[x] = plain_text[x];
            step_counter = false;
        }
        
        if(step_counter == true){
            // this was the cause of 90% of the problem - needed to add -1 to key_length due to 0 indexing!
            if(cipher_counter + 1 > key_length - 1 ){
                cipher_counter = 0;
                
            }
            else{
                cipher_counter++;
            }
        }
    }
 
   // need to manually add in the null terminator, as cipher_text has been handled as a char array NOT a string
   cipher_text[plain_text_length] = '\0';
    
    printf("ciphertext: %s", cipher_text);
    printf("\n");
    
    return 0;
}
