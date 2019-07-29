//   DNA Pairing.js

/*
The DNA strand is missing the pairing element. Take each character, get its pair, and return the results as a 2d array.

Base pairs are a pair of AT and CG. Match the missing element to the provided character.

Return the provided character as the first element in each array.

For example, for the input GCG, return [["G", "C"], ["C","G"],["G", "C"]]

The character and its pair are paired up in an array, and all the arrays are grouped into one encapsulating array.


*/

// Quick and easy solution.
// LOL. I forgot that JS had a case statement - was thinking of python.
// Also, probably would have been more correct to use .map() instead of foreach()
/* see pairElem2
*/

function pairElement(str) {
    let strArr = [...str];
    let basePairs = [];
    let dnaDic = {
        "G": "C",
        "C": "G",
        "T": "A",
        "A": "T"
    };

    strArr.forEach(element => {
        basePairs.push([element, dnaDic[element]]);    
    });
    return basePairs;
  }

  function pairElement2(str) {
    let strArr = [...str];
    let dnaDic = {
        "G": "C",
        "C": "G",
        "T": "A",
        "A": "T"
    };

    return strArr.map(elem => [elem, dnaDic[elem]]);
  }
  

  result = pairElement2("GCG");




//-------------------
console.log(result);

