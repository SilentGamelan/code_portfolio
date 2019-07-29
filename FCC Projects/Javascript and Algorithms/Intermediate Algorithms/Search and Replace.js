//   Search and Replace.js

/*

Perform a search and replace on the sentence using the arguments provided and return the new sentence.

First argument is the sentence to perform the search and replace on.

Second argument is the word that you will be replacing (before).

Third argument is what you will be replacing the second argument with (after).

---
Preserve the case of the first character in the original word when you are replacing it. 
For example if you mean to replace the word "Book" with the word "dog", it should be replaced as "Dog"

*/
// Works but is ugly
// !! Also, be aware that this will malfunction if given numeric strings or some unicode strings.
// see 3rd option for a unicode-agnostic version

function myReplace(str, before, after) {
    // before[0] == before[0].toUpperCase() -> returns true if uppercase, false if not
    after = (before[0] == before[0].toUpperCase()) ? after[0].toUpperCase() + after.slice(1): after[0].toLowerCase() + after.slice(1);
    return str.replace(before, after);
 
  }

// Same as above, but more readable
function myReplace2(str, before, after) {
    if(before[0] == before[0].toUpperCase()) {
        after = after[0].toUpperCase() + after.slice(1);
    } else {
        after = after[0].toLowerCase() + after.slice(1);
    }

    return str.replace(before, after);
}

function myReplace3(str, before, after) {
    if(before[0] == before[0].toLocaleUpperCase()) {
        after = after[0].toLocaleUpperCase() + after.slice(1);
    } else {
        after = after[0].toLocaleLowerCase() + after.slice(1);
    }

    return str.replace(before, after);
}

result = myReplace("A quick brown fox jumped over the lazy dog", "Jumped", "leaped");

//-------------------
console.log(result);

