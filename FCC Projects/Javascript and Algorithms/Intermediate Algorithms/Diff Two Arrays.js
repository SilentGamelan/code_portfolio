//  Diff Two Arrays.js


/*
Compare two arrays and return a new array with any items only found in one of the two given arrays, but not both. 
In other words, return the symmetric difference of the two arrays.

You can return the array with its elements in any order.
*/

// !! Rewrite - this this isn't very elegant.


  function diffArray(arr1, arr2) {
    var newArr = arr1.filter(item => arr2.indexOf(item) === -1);
    newArr = newArr.concat(arr2.filter(item => arr1.indexOf(item) === -1));
    return newArr;
    
    }

 result = diffArray(["andesite", "grass", "dirt", "pink wool", "dead shrub"], ["diorite", "andesite", "grass", "dirt", "dead shrub"] );

//
console.log(result)



