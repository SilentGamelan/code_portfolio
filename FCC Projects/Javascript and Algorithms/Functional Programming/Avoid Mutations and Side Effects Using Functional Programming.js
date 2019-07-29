//  Avoid Mutations and Side Effects Using Functional Programming.js

/*
One of the core principle of functional programming is to not change things. Changes lead to bugs.
It's easier to prevent bugs knowing that your functions don't change anything, including the function arguments or any global variable.

Recall that in functional programming,
    - changing or altering things is called mutation
    - the outcome is mutation is called a side effect.
 
    A function, ideally, should be a pure function, meaning that it does not cause any side effects.
----
Fill in the code for the function incrementer so it returns the value of the global variable fixedValue increased by one.

*/


// the global variable
var fixedValue = 4;

function incrementer () {
  // Add your code below this line
  return fixedValue + 1
  
  // Add your code above this line
}

var newValue = incrementer(); // Should equal 5
console.log(fixedValue); // Should print 4

