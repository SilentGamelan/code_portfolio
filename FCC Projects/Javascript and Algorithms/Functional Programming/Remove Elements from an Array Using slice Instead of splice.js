//  Remove Elements from an Array Using slice Instead of splice.js

/*
the splice method takes arguments for the index of where to start removing items, then the number of items to remove. 
If the second argument is not provided, the default is to remove items through the end. 
However, the splice method mutates the original array it is called on.

---
Rewrite the function nonMutatingSplice by using slice instead of splice. 
It should limit the provided cities array to a length of 3, and return a new array with only the first three items.

Do not mutate the original array provided to the function.

*/

function nonMutatingSplice(cities) {
    // Add your code below this line
    return cities.slice(0, 3);
    
    // Add your code above this line
  }
  var inputCities = ["Chicago", "Delhi", "Islamabad", "London", "Berlin"];
  nonMutatingSplice(inputCities);
