//   Sorted Union.js

/*

Write a function that takes two or more arrays and returns a new array of unique values in the order of the original provided arrays.

In other words, all values present from all arrays should be included in their original order, but with no duplicates in the final array.

The unique numbers should be sorted by their original order, but the final array should not be sorted in numerical order.
*/


function uniteUnique(arr) {
    const args = Array.prototype.slice.call(arguments);
    let newArr = []

    args.forEach(subArr => {
        subArr.forEach(elem => {
            if(!newArr.includes(elem)) {
                newArr.push(elem);
            }
        });
    });

    return newArr;
}

    /* Why doesn't this work??
    Think because its returning all enumerable properties?
    for(var subArr in args){
        for(var elem in subArr){
            if(!newArr.includes(elem)){
                newArr.push(elem);
            }
        }
    }
    return newArr;
  }
  */
result = uniteUnique([1, 3, 2], [5, 2, 1, 4], [2, 1]);

//-------------------
console.log(result);

