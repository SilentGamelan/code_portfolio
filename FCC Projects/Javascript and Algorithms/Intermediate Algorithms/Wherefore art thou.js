//   Wherefore art thou.js


/*
Make a function that looks through an array of objects (first argument) and returns an array of all objects that have matching name and value pairs (second argument). 
Each name and value pair of the source object has to be present in the object from the collection if it is to be included in the returned array.

*/


function whatIsInAName(collection, source) {
    // What's in a name?
    var arr = [];
    // Only change code below this line

    // Object.keys(object) will return an array containing all of the properties of an object.
    // Didn't end up needing this.
    //var srcKeys = Object.keys(source);

    arr = collection.filter(colObj => {
        for(var prop in source){
            if(!(colObj.hasOwnProperty(prop) && colObj[prop] === source[prop])) {
                return false
            }
        }
        return true;
    });
        
    
    // Only change code above this line
    return arr;
  }
  
 result = whatIsInAName([{ first: "Romeo", last: "Montague" }, { first: "Mercutio", last: null }, { first: "Tybalt", last: "Capulet" }], { last: "Capulet" });

//
console.log(result)



