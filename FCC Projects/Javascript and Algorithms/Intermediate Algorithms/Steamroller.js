// Steamroller.js
/*
Flatten a nested array. You must account for varying levels of nesting.

*/

/** Alternative methods of checking is variable is array: https://stackoverflow.com/questions/767486/
    variable.constructor === Array;
    
    variable.prop && variable.prop.constructor === Array // for checking if property of an object is an array

    variable instanceof Array

    Array.isArray(variable) // ES5

NB: as usual, some argument about which is most performant and appropriate
    -   NOTE: 'variable.constructor === Array' will throw EXCEPTION if variable is null but 'variable instanceof Array' will not

    -   variable.constructor is faster only for checking actual arrays. 
        When checking random objects (and in real world this will be the case as this is why you use this function) it's faster to use instanceof

    -   .isArray() will break on older browsers without polyfills
*/

function steamrollArray(arr) {
    // I'm a steamroller, baby
    arr = unrollArray(arr);    
    return arr;
  }

// used recursive approach 
// .apply() allows for passing multiple arguments to another method
// .push.apply() enables me to append each item of an array to a target array
function unrollArray(rolled) {
    let unrolled = [];
    for(let i = 0; i < rolled.length; i++) {
        if(rolled[i].constructor === Array) {
            unrolled.push.apply(unrolled, unrollArray(rolled[i]));
        } else {
            unrolled.push(rolled[i]);
        }
    }
    return unrolled;
} 

result = steamrollArray([1, [2], [3, [[4]]]]);
//-------------------
console.log(result);






