//   Pass Arguments to Avoid External Dependence in a Function.js

/*
1) Don't alter a variable or object - create new variables and objects and return them if need be from a function.

2) Declare function arguments - any computation inside a function depends only on the arguments, and not on any global object or variable.
---

Refactor (rewrite) the code so the global array bookList is not changed inside either function.
The add function should add the given bookName to the end of an array. The remove function should remove the given bookName from an array.
Both functions should return an array, and any new parameters should be added before the bookName one..

*/


// the global variable
var bookList = ["The Hound of the Baskervilles", "On The Electrodynamics of Moving Bodies", "Philosophiæ Naturalis Principia Mathematica", "Disquisitiones Arithmeticae"];

/* This function should add a book to the list and return the list */
// New parameters should come before the bookName one

// Add your code below this line
function add(aBookList, bookName) {
  let shallowCopy = aBookList.slice();
  // !! Be aware of what methods actually return - was having problems as I'd originally written the below as
  // shallowCopy = shallowCopy.push(bookName), which returned and assigned the LENGTH of the new array to shallowCopy.
  shallowCopy.push(bookName);
  return shallowCopy;
  
  // Add your code above this line
}

/* This function should remove a book from the list and return the list */
// New parameters should come before the bookName one

// Add your code below this line
function remove(aBookList, bookName) {
  const shallowCopy = aBookList.slice();
  if (shallowCopy.indexOf(bookName) >= 0) {
    shallowCopy.splice(shallowCopy.indexOf(bookName), 1);
    return shallowCopy;
    
    // Add your code above this line
    }
}

var newBookList = add(bookList, 'A Brief History of Time');
var newerBookList = remove(bookList, 'On The Electrodynamics of Moving Bodies');
var newestBookList = remove(add(bookList, 'A Brief History of Time'), 'On The Electrodynamics of Moving Bodies');

console.log(bookList);
