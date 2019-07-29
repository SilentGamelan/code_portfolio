//   Use the every Method to Check that Every Element in an Array Meets a Criteria.js


/*
The every method works with arrays to check if every element passes a particular test. 
It returns a Boolean value - true if all values meet the criteria, false if not.

-------
Use the every method inside the checkPositive function to check if every element in arr is positive. 
The function should return a Boolean value.

*/

function checkPositive(arr) {
    // Add your code below this line
    return arr.every(item => {return item > 0});
    
    // Add your code above this line
  }

  result = checkPositive([1, 2, 3, -4, 5]);
  console.log(result);
