//   Seek and Destroy.js


/*
You will be provided with an initial array (the first argument in the destroyer function), followed by one or more arguments. 
Remove all elements from the initial array that are of the same value as these arguments.

!!! You have to use the ARGUMENTS object.

*/

// !! Rewrite - this this isn't very elegant.

// Didn't notice it mentioned the ARGUMENTS object for a while.
// Using the ...rest syntax is accepted on FCC
// ...argumentArrName will destructure the arguments object, and place its values into an array.

function destroyer(arr, ...params) {   
    // Basically, filter out anything that is found in the params array
    // Unless there are no params, and

    arr = arr.filter(item => params.indexOf(item) === -1);
    return arr;
  }
  
result = destroyer([1, 2, 3, 1, 2, 3], 2, 3);

//
console.log(result)



