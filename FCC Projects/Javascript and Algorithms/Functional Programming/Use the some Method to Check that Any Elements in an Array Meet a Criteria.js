//   Use the some Method to Check that Any Elements in an Array Meet a Criteria.js


/*
The some method works with arrays to check if any element passes a particular test. 
It returns a Boolean value - true if any of the values meet the criteria, false if not.

Use the some method inside the checkPositive function to check if any element in arr is positive. 
The function should return a Boolean value.

*/

function checkPositive(arr) {
    // Add your code below this line
    return arr.some(item => {return item > 0});    
    // Add your code above this line
  }
  
  result = checkPositive([1, 2, 3, -4, 5]);
  
  //
  console.log(result)