//  Understand Functional Programming Terminology.js

/*

We can modify getTea to accept a function as a parameter to be able to change the type of tea it prepares.
This makes getTea more flexible, and gives the programmer more control when client requests change.

! First Class Functions: Functions that can be assigned to a variable, passed into another function, or returned from another function  like any other normal value
    - In JavaScript, all functions are first class functions.

! Higher Order Functions: functions that take a function as an argument, or return a function as a return value.

! lambda function: functions that are passed in to another function or returned from another function

---------
Prepare 27 cups of green tea and 13 cups of black tea and store them in tea4GreenTeamFCC and tea4BlackTeamFCC variables, respectively.
Note that the getTea function has been modified so it now takes a function as the first argument.

*/

/**
 * A long process to prepare green tea.
 * @return {string} A cup of green tea.
 **/
const prepareGreenTea = () => 'greenTea';

/**
 * A long process to prepare black tea.
 * @return {string} A cup of black tea.
 **/
const prepareBlackTea = () => 'blackTea';

/**
 * Get given number of cups of tea.
 * @param {function():string} prepareTea The type of tea preparing function.
 * @param {number} numOfCups Number of required cups of tea.
 * @return {Array<string>} Given amount of tea cups.
 **/
const getTea = (prepareTea, numOfCups) => {
  const teaCups = [];

  for(let cups = 1; cups <= numOfCups; cups += 1) {
    const teaCup = prepareTea();
    teaCups.push(teaCup);
  }

  return teaCups;
};

// Add your code below this line

const tea4GreenTeamFCC = getTea(prepareGreenTea, 27);// :)
const tea4BlackTeamFCC = getTea(prepareBlackTea, 13); // :)

// Add your code above this line

console.log(
  tea4GreenTeamFCC,
  tea4BlackTeamFCC
);


