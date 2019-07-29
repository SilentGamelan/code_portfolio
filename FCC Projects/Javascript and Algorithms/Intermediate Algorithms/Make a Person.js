// Make a Person.js
/*
Fill in the object constructor with the following methods below:

getFirstName() getLastName() getFullName() setFirstName(first) setLastName(last) setFullName(firstAndLast)
Run the tests to see the expected output for each method.

The methods that take an argument must accept only one argument and it has to be a string.

These methods must be the only available means of interacting with the object.

*/

// Finally realised that they want you to use CLOSURES to encapsulate the private variables
// if use this.varName, then they are globally accessible.

// ES6 solution, as uses [a,b] destructuring assisngment syntax
 var Person = function(firstAndLast) {
  // Complete the method below and implement the others similarly
  let firstName;
  let lastName;

  function validate(args) {
    return (args.length !== 1 || !(typeof args[0] === "string")) ? false : true;
  }
  
  this.getFullName = () => {
    return firstName + " " + lastName;
  };
  
  this.getFirstName = () => {
    return firstName;
  };

  this.getLastName = () => {
    return lastName;
  };
  
  this.setFirstName = (first) => {
    let retVal = true;
    validate(arguments) ? firstName = first : retVal = false;
    return retVal
  }

  this.setLastName = (last) => {
    let retVal = true;
    validate(arguments) ? lastName = last : retVal = false;
    return retVal
  }

  this.setFullName = (firstAndLast) => {
    let retVal = true;
    if(validate(arguments)) {
      [firstName, lastName] = firstAndLast.split(" ");
    } else {
      retVal = false;
    }
    return retVal
  }

  // Initialises name on construction
  this.setFullName(firstAndLast);  

};
  
let bob = new Person('Bob Ross');
let result = bob.getFirstName();
console.log(bob.firstName);
//-------------------
console.log(result);






