//   Missing letters.js

/*
Find the missing letter in the passed letter range and return it.

If all letters are present in the range, return undefined.

*/

// Convert letters to ascii equivilent and check to see if i's ascii code immediately follows i-1 in numerical sequence.
// hmm. Thinking about it, would probably have made more sense to start at 0 and check i + 1, but then would have to -1 to strLen in loop definition.
function fearNotLetter(str) {
    let strLen = str.length;
    
    for(let i = 1; i < strLen; i++) {
        if(str.charCodeAt(i) - 1 !== str.charCodeAt(i-1)) {
            return String.fromCharCode(str.charCodeAt(i)-1);
        }
    }
    return;
  }
  
result = fearNotLetter("abce");

//-------------------
console.log(result);

