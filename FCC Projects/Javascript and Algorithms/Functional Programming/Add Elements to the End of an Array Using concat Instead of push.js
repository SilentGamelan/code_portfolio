// Add Elements to the End of an Array Using concat Instead of push.js


/*

Compare concat to the push method. Push adds an item to the end of the same array it is called on, which mutates that array.

---
Change the nonMutatingPush function so it uses concat to add newItem to the end of original instead of push.
The function should return an array.

*/

function nonMutatingPush(original, newItem) {
    // Add your code below this line
    return original.concat(newItem);
    
    // Add your code above this line
  }
  var first = [1, 2, 3];
  var second = [4, 5];
  nonMutatingPush(first, second);
