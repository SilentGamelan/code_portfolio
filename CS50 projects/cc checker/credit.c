/* credit.c:    takes a credit card number and checks its valdity by comparing against known credit card number formats, and 
                performs a checksum validation using luhn's algorithm. Outputs the type of card if valid, else invalid; 
*/
#include <stdio.h>
#include <cs50.h>
#include <math.h>


// using defines as constants, rather than declaring them as variables - used for logic purposes and indicating  card type/validity
#define INVALID -1
#define NOTVALIDATED 0 
#define AMEX 1
#define MASTER 2
#define VISA 3
#define LUHN_OK 4

int validate (long long ccnum);

int main(void)
{
    /*
    American Express numbers all start with 34 or 37;
    MasterCard numbers all start with 51, 52, 53, 54, or 55; 
    Visa numbers all start with 4. 
    
     American Express uses 15-digit numbers
     MasterCard uses 16-digit numbers
     Visa uses 13- and 16-digit numbers
    */
    
    long long card_num;
    
    // used to collect the return value from function validate()
    int card_type = NOTVALIDATED;
    
    long long amex_code_1[2], amex_code_2[2];
    long long master_code[2];
    long long visa_code_16[2], visa_code_13[2];
    
    // lists the upper and lower bounds for valid CC numbers for each credit card type
    amex_code_1[0] = 340000000000000;
    amex_code_1[1] = 349999999999999;
    amex_code_2[0] = 370000000000000;
    amex_code_2[1] = 379999999999999;
    
    master_code[0] = 5100000000000000;
    master_code[1] = 5599999999999999;
    
    visa_code_16[0] = 4000000000000000;
    visa_code_16[1] = 4999999999999999;
    visa_code_13[0] = 4000000000000;
    visa_code_13[1] = 4999999999999;
    
    // repeats until user input is non-negative
    printf("Please enter your credit card number: ");
    do{
        card_num = get_long_long();
    } while (card_num < 0);
    

    // nested ifs in turn check card_num against known upper and lower bounds of each type of credit card
    //  if card_num within a valid range, it is sent to validate() to check valid checksum.
    //  if valid, we update the card_type with appropriate type
    
    if(card_num >= master_code[0] && card_num <= master_code[1]){
        card_type = validate(card_num);    

         
        if(card_type == LUHN_OK){
            card_type = MASTER;
        }
    }
    else if((card_num >= amex_code_1[0] && card_num < amex_code_1[1]) || (card_num >= amex_code_2[0] && card_num <= amex_code_2[1])){
            card_type = validate(card_num);
            if(card_type == LUHN_OK){
                card_type = AMEX;
        }
    }
    else if( (card_num >= visa_code_16[0] && card_num < visa_code_16[1]) || (card_num >= visa_code_13[0] && card_num <= visa_code_13[1])){
           card_type = validate(card_num);
            if(card_type == LUHN_OK){
                card_type = VISA;
            }
    }
    else{
        // anything outside of the above ranges is invalid for our purposes
        card_type = INVALID;
    }


    switch (card_type){
        case AMEX:
        printf("AMEX\n");
        break;
        
        case MASTER:
        printf("MASTERCARD\n");
        break;
        
        case VISA:
        printf("VISA\n");
        break;
        
        default:
        printf("INVALID\n");  
    } 
    
    return (0);
}



/***************************************/

int validate (long long ccnum){
    // applies luhns algorithm to ccnum

/*    Luhn’s algorithm:
A:    Multiply every other digit by 2, starting with second-to-LEAST-significant digit   
B:    add those products' digits together.
C:    Add the sum to the sum of the digits that weren’t multiplied by 2.
D:    If the total’s last digit is 0 [or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
*/


    
    int numlen = 0;
    
    // used to do calculations on value of ccnum; retain ccnum so we can reset the value as needed
    long long temp = ccnum;
    
    // used when adding digits together as part of luhns 
    int luhn = 0;
    
    
    /* finds the length of int ccnum by right rotation truncation - dividing by ten effectively shifts a number one to the right
     *  and as temp is an int, anything after the decimal place is removed. By increasing the nunlen counter, we can calc the number
     * of digits of temp/cc num
     */
    
    while(temp != 0){
        temp=temp/10;
        numlen++;
    }
    
    // STEP A -
    // starting with second-to-LEAST-significant digit, then looping to every *other* digit in turn (x=x+2)
    // shift chosen digit to be the least significant digit by pow(10,x) [saves creating a loop to do multiple /10's]
    
    for(int x = 1; x <= numlen-1; x = x + 2){
        temp = ccnum;
        temp = temp / pow(10,x);

    // remove all digits to the left of the new "ones column", leaving only the digit to be processed, multiply this by 2
        temp = temp % 10;
        temp = temp * 2;

    // STEP B - multiply the digits of the product; 
    // if temp>9, it has more than 1 digit so: %10 gives the LSD and (temp/10) % 10 gives the MSD
    
        if(temp > 9){
            temp = (temp % 10) + ((temp/10) % 10);
            luhn = luhn + temp;
        }
        else{
            luhn = luhn + temp;
        }
    }
    
    // STEP C - add the sum of non-multiplied digits to luhn, using similar process as above
    for (int x = 0; x <= numlen; x = x + 2) {
        temp = ccnum;
        temp = temp / pow(10,x);
        temp = temp % 10;
        luhn = luhn + temp;
    }
    
    // STEP D - check if last digit of luhn is 0 (ie; valid checksum)
    if(luhn % 10 == 0){
        return(LUHN_OK);
    }
    else{
        return(INVALID);
    }
}