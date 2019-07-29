// Arguments Optional.js
/*
Create a function that sums two arguments together. If only one argument is provided, then return a function that expects one argument and returns the sum.

For example, addTogether(2, 3) should return 5, and addTogether(2) should return a function.

Calling this returned function with a single argument will then return the sum:

var sumTwoAnd = addTogether(2);

sumTwoAnd(3) returns 5.

If either argument isn't a valid number, return undefined.

*/

function addTogether() {
    // shortened code by relying on retVal being undefined here, and removing repeated retVal = undefined clauses below
    let retVal;

    switch (arguments.length) {
        case 1:
            if(isNum(arguments[0])) {
                retVal = (value) =>  {
                    return isNum(value) ? value + arguments[0] : undefined;
                }
            }
            break;
        case 2:
            if(isNum(arguments[0]) && isNum(arguments[1])) {
                retVal = arguments[0] + arguments[1];
            }
            break;
    }
    return retVal;
  }

// suprisingly, there isn't a native method for testing if something is a number.
// Other alternatives are from stackoverflow.com/questions/18082
// !isNaN(x)                                                                        -not reliable,  will class a space (" ") as a number, also null and others
// !isNaN(parseFloat(n)) && isFinite(n);
// num > 0 || num === 0 || num === '0' || num < 0) && num !== true && isFinite(num) -
// typeof num !== 'number'                                                          - actually forgot about this one, probably the simplest too

// I think my method is the most succinct and should not fail edge cases
function isNum(num) {
    return num.constructor === Number;
}

result = addTogether(2)([3]) 
var sumTwoAnd = addTogether(2);
console.log(sumTwoAnd(3));
//-------------------
console.log(result);






