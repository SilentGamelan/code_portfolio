//   Pig Latin.js

/*

Translate the provided string to pig latin.

Pig Latin takes the first consonant (or consonant cluster) of an English word, moves it to the end of the word and suffixes an "ay".

If a word begins with a vowel you just add "way" to the end.

Input strings are guaranteed to be English words in all lowercase.

*/



function translatePigLatin2(str) {
   
    let vowelRegex = /[AEIOUaeiou]+\w*/;
    let consRegex = /^[^AEIOUaeiou]+/;

    console.log(str.match(vowelRegex));
    console.log(str.match(consRegex));
    str[0].match(vowelRegex) ? str += "way":str = str.match(vowelRegex) + str.match(consRegex) + "ay";

    return str;
    
}

function translatePigLatin(str) {
    let noVowels = /^[^AEIOUaeiou]+$/;
    let vowelRegex = /[AEIOUaeiou]+\w*/;
    let consRegex = /^[^AEIOUaeiou]+/;

    if(str.match(noVowels)) {
        str = str + "ay";
    } else {
        str[0].match(vowelRegex) ?  str = str += "way" : str = str.match(vowelRegex) + str.match(consRegex) + "ay";
    }
    
    return str;
}

var result = translatePigLatin("sty");
console.log(result);

