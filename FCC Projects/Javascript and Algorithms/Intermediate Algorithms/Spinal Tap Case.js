//   Spinal Tap Case.js


/*
Convert a string to spinal case. Spinal case is all-lowercase-words-joined-by-dashes.

!! From the test cases, it wants you to split on word boundaries, spaces, and <wrb> tags
spinalCase("This Is Spinal Tap") should return "this-is-spinal-tap".
spinalCase("thisIsSpinalTap") should return "this-is-spinal-tap".
spinalCase("The_Andy_Griffith_Show") should return "the-andy-griffith-show".
spinalCase("Teletubbies say Eh-oh") should return "teletubbies-say-eh-oh".
spinalCase("AllThe-small Things") should return "all-the-small-things".

*/



// regex using match will extract words by looking for something that starts with lower or uppercase and stopping before it hits another uppercase letter, which
// indicates the start of another word. <wbr> needs to taken out first, as the regex will match the inside of the angle brackets. 
// Surely its possible to do it in one pass though.

function spinalCase(str){
    let re = /([A-Za-z][a-z]+)/g;
    return str.replace("<wbr>"," ").match(re).join("-").toLowerCase();
    
}


//
result = spinalCase("thisIsSpinal<wbr>Tap");
console.log(result);
