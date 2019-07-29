//  Sum All Numbers in a Range.js


/*

We'll pass you an array of two numbers. Return the sum of those two numbers plus the sum of all the numbers between them.

The lowest number will not always come first.
*/

function sumAll(arr) {
    let tempArr = arr.sort((a,b)=> a-b);
    let sum = arr[0] + arr[1];

    for(let i=arr[0]+1; i < arr[1]; i++) {
        sum += i;
    }

    return sum;
}

result =  sumAll([1, 4]);

//
console.log(result)