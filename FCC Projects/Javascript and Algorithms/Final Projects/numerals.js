// Roman Numeral Converter.js

/*
Convert the given number into a roman numeral.

All roman numerals answers should be provided in upper-case.
*/

let STRICT_MODE = false;
let MAXVAL = 3999;

function convertToRoman(number) {
    // I have used the apostrophus symbols in a non-standard way to enable handling of numbers greater than
    // can be represented using the Roman Numerals alone (>3999)
    // Set STRICT_MODE to true to reject numbers > MAXVAL
    
    if(STRICT_MODE) {
        if(number > MAXVAL) {return "BOOTOOBIG"}
    }
    
    let numerals = {
        1: "I",
        5: "V",
        10: "X",
        50: "L",
        100: "C",
        500: "D",
        1000: "M",
        5000: "ↁ",
        10000: "ↂ"
    }

    // x=>x*1 is a kludge to force conversion of array items from string to number
    // reverse array to allow easier mapping of loop iteration count and unit modifier
    number = number.toString().split("").map(x=>x*1).reverse();

    let result = []

    for(let i = 0; i < number.length; i++) {
        // taking advantage of the fact that raising to the power 0 gives 1
        // which allows the correct unit modifier to be selected on the 0th index
        let unit = numerals[1 * Math.pow(10, i)];
        let penta = numerals[5 * Math.pow(10, i) ];
        let deca = numerals[10 * Math.pow(10, i)];
        let x = number[i];    
        switch(x) {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
                result.unshift.apply(result, Array(x).fill(unit));
                break;
            case 4:
                result.unshift.apply(result, [unit, penta]);
                break;
            case 5:
            case 6:
            case 7:
            case 8:
                result.unshift.apply(result, Array(x-5).fill(unit));
                result.unshift(penta);
                break;
            case 9:
                result.unshift.apply(result, [unit, deca]);
                break;
            default:
                result.unshift("!");
                break;
        }
    }
        
    return result.join("");
}

let result = convertToRoman(68);
console.log(result);

//convertToRoman(68) should return "LXVIII"