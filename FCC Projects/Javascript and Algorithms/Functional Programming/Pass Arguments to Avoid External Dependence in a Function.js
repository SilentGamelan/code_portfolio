//   Pass Arguments to Avoid External Dependence in a Function.js

/*
Another principle of functional programming is to always declare your dependencies explicitly.
This means if a function depends on a variable or object being present, then pass that variable or object directly into the function as an argument.

There are several good consequences from this principle. 
The function is easier to test, you know exactly what input it takes, and it won't depend on anything else in your program.

---

Let's update the incrementer function to clearly declare its dependencies.

Write the incrementer function so it takes an argument, and then increases the value by one.

*/


// the global variable
var fixedValue = 4;

// Add your code below this line
function incrementer (value) {
  return value + 1
  
  // Add your code above this line
}

var newValue = incrementer(fixedValue); // Should equal 5
console.log(fixedValue); // Should print 4

