//    Sum All Primes.js

/*
Sum all the prime numbers up to and including the provided number.

A prime number is defined as a number greater than one and having only two divisors, one and itself. 
For example, 2 is a prime number because it's only divisible by one and two.

The provided number may not be a prime.

*/
// Brute force calculation of primes
// Think there's probably a better way.
function sumPrimes(num) {
    // 2 is the lowest prime, start summing from there
    let sum = 2;
    let isPrime = true;
    if(num < 2){
        return 0;
    } else if (num == 2){
        return 2;
    } else {
        // All primes bar 2 are odd, so begin at 3 and skip even numbers
        for(let i = 3; i <= num; i+=2){
            for(let j = 2; j < i; j++){
                if(i % j == 0){
                    isPrime = false;
                    break;
                }
            }
            !isPrime ? isPrime = true : sum += i;
        }
    }
    return sum;   
}
  

function erasSieve(num) {
    let primes = [];
    for(var i = 2; i <= num; i++) {
        primes[i] = true;
    }

    let max = Math.sqrt(num);

    for(let i = 2; i < max; i++){
        if(primes[i]){
            for(let j = i * 2; j < num; j+= i){
                primes[j] = false;
            }
        }
    }
    
    primeArr = [];
    let primesum = 0;

    primes.forEach((item, index) => {
        if(item && index > 1) {
            primeArr.push(index);
        }
    });

    primeSum = primes.reduce((acc, item, index, array) => {
        if(item && index > 1 && index <= num) {
            return acc + index;
        } else {
            return acc;
        }
    }, 0);
    return [primeArr,primeSum];
}

result = erasSieve(11);
//-------------------
console.log(result);
