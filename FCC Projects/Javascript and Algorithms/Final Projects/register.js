// cash register.js

/*
Design a cash register drawer function checkCashRegister() that accepts purchase price as the first argument (price), 
payment as the second argument (cash), and cash-in-drawer (cid) as the third argument.

cid is a 2D array listing available currency.

The checkCashRegister() function should always return an object with a status key and a change key.

Return {status: "INSUFFICIENT_FUNDS", change: []} if cash-in-drawer is less than the change due, or if you cannot return the exact change.

Return {status: "CLOSED", change: [...]} with cash-in-drawer as the value for the key change if it is equal to the change due.

Otherwise, return {status: "OPEN", change: [...]}, with the change due in coins and bills, sorted in highest to lowest order, as the value of the change key.

Remember to use Read-Search-Ask if you get stuck. Try to pair program. Write your own code.

Currency Unit	Amount
Penny	$0.01 (PENNY)
Nickel	$0.05 (NICKEL)
Dime	$0.1 (DIME)
Quarter	$0.25 (QUARTER)
Dollar	$1 (DOLLAR)
Five Dollars	$5 (FIVE)
Ten Dollars	$10 (TEN)
Twenty Dollars	$20 (TWENTY)
One-hundred Dollars	$100 (ONE HUNDRED)
*/


function checkCashRegister(price, cash, cid) {
    // used for dollar/cent conversion
    let values = [100, 20, 10, 5, 1, 0.25, 0.1, 0.05, 0.01]
    let centValues = values.map(x => x * 100);
    
    let registerTotalCents = 0;

    // total contents of till in cent value and convert each till drawer to number of each denomination, rather than dollar value
    // avoids need for float calculations with its related rounding errors
    // reverse change to simplify sorting return object by highest value
    // NB: not possible to clone a multi-dimension array with built-in methods
    let change = arrayDeepCopy(cid);
    change.reverse();
    change.forEach((elem, i) => {
        registerTotalCents += elem[1] * 100;
        elem[1] = Math.round(elem[1] /= values[i]);
    });

    // will use difference between till state at beginning and end to calculate what change to return
    let balance = arrayDeepCopy(change);


    let changeOwedInCents = (cash - price) * 100;
   
    if(changeOwedInCents == registerTotalCents) {
        return {status: "CLOSED", change: cid};
    }
    
    // Take change out of till to try and reduce changed owed to 0. elem[1] holds how much of a denomination is in drawer[i]
    // check that till contains given denom, that change is still owed, and that its possible to deduct the current denomination from change owned on each loop
    change.forEach((elem, i) => {
        while(elem[1] && changeOwedInCents > 0 && changeOwedInCents - centValues[i] >= 0) {
            elem[1]--;
            changeOwedInCents -= centValues[i];
        }
    });

    // generate change return object
    // x[0] = denomination name
    // determine change to return by finding the difference between denominations at beginning (balance) and end (change) of calculation
    // then convert it back into dollar value (values[i] *...) as required for return object.
    // 
    // finally, filter out any till drawers whose contents haven't changed
    change = change.map((x, i) => [x[0], values[i] *= balance[i][1] - x[1]]).filter(x => x[1] > 0);
    
    
    if(changeOwedInCents > 0) {
        return {status: "INSUFFICIENT_FUNDS", change: []};
    } else {
        return {status: "OPEN", change: change};
    }

  }
  
  // this will only work for a 2-d array
  function arrayDeepCopy(source) {
    let destination = [];
    for(let i = 0; i < source.length; i++) {
        destination[i] = source[i].slice(0);
    }
    return destination;
}
 
  // Example cash-in-drawer array:
  // [["PENNY", 1.01],
  // ["NICKEL", 2.05],
  // ["DIME", 3.1],
  // ["QUARTER", 4.25],
  // ["ONE", 90],
  // ["FIVE", 55],
  // ["TEN", 20],
  // ["TWENTY", 60],
  // ["ONE HUNDRED", 100]]
  
  result = checkCashRegister(3.26, 100, [["PENNY", 1.01], ["NICKEL", 2.05], ["DIME", 3.1], ["QUARTER", 4.25], ["ONE", 90], ["FIVE", 55], ["TEN", 20], ["TWENTY", 60], ["ONE HUNDRED", 100]]);
  console.log(result);