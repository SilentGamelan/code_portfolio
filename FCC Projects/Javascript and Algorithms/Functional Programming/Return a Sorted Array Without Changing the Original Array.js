//  Sort an Array Alphabetically using the sort Method.js


/*

--
Use the sort method in the nonMutatingSort function to sort the elements of an array in ascending order. 
The function should return a new array, and not mutate the globalArray variable.

*/


var globalArray = [5, 6, 3, 2, 9];
function nonMutatingSort(arr) {
  // Add your code below this line
  
  // concat returns a new array (doesn't alter in place/mutate) - concatting an empty array is just a hack to force a deep copy
  let newArr = arr.concat([]);
  return newArr.sort((a,b) => a > b);

  
  // Add your code above this line
}
nonMutatingSort(globalArray);
console.log(nonMutatingSort(globalArray));

