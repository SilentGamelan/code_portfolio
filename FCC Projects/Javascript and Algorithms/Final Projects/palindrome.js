// palindrome.js

/*
Return true if the given string is a palindrome. Otherwise, return false.

A palindrome is a word or sentence that's spelled the same way both forward and backward, ignoring punctuation, case, and spacing.

Note
You'll need to remove all non-alphanumeric characters (punctuation, spaces and symbols) and turn everything into the same case (lower or upper case) in order to check for palindromes.

We'll pass strings with varying formats, such as "racecar", "RaceCar", and "race CAR" among others.

We'll also pass strings with special symbols, such as "2A3*3a2", "2A3 3a2", and "2_A3*3#A2".
*/

// Most compact code I could come up with, but probably not the most efficient method 
function palindrome(str) {
    str = str.split(/[^a-zA-Z0-9]/).join("").toLowerCase();
    let rev = str.split("").reverse().join("");
    return str == rev ? true : false;
}
  
// Alternate version which doesn't rely on regular expressions
function palindrome2(str){
    let z = str.length -1;
    let x = 0;
    let validChars = "abcdefghijklmnopqrstuvwxyz";
    str = str.toLowerCase();
    
    function match(i) {
        return validChars.indexOf(str.charAt(i));
    }

    while(x < str.length && z > x) { 
         
        while(match(x) == -1) {
            x++;
        }

        while(match(z) == -1) {
            z--;
        }

        if(str.charAt(x) !== str.charAt(z)) {
            return false;
        } else {
            x++;
            z--;
        }
    }

    return true;
}


  
  result = palindrome2("1 eye for of 1 eye.");   

  console.log(result);