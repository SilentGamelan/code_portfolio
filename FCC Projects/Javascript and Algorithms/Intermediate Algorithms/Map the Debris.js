// Map the Debris.js

/*
Return a new array that transforms the elements' average altitude into their orbital periods (in seconds).

The array will contain objects in the format {name: 'name', avgAlt: avgAlt}.

You can read about orbital periods on Wikipedia.

The values should be rounded to the nearest whole number. The body being orbited is Earth.

The radius of the earth is 6367.4447 kilometers, and the GM value of earth is 398600.4418 km3s-2.

Remember to use Read-Search-Ask if you get stuck. Try to pair program. Write your own code.

*/

////

/* Keplers 3rd law:
T = 2π√a³/μ

T = orbital period in seconds
a = semi-major axis 
μ = Standard Gravitational Parameter (GM)
        G = Gravitational Constant
        M = Mass of the more massive body

*/

// Took me a while to realise that you have to add the altitude of the satellite to the earth's radius to get the semi-major axis 
// as the gravitation force acts from the center of the orbited body

function orbitalPeriod(arr) {
    const GM = 398600.4418;
    const earthRadius = 6367.4447;

    arr = arr.map(body => {
        let a = body.avgAlt + earthRadius
        let T = (2 * Math.PI) * Math.sqrt(Math.pow(a, 3) / GM)
        return {name: body.name, orbitalPeriod: Math.round(T)};
    });
    
    return arr;

}
 
//////
 result = orbitalPeriod([{name: "iss", avgAlt: 413.6}, {name: "hubble", avgAlt: 556.7}, {name: "moon", avgAlt: 378632.553}]);
 // should return [{name : "iss", orbitalPeriod: 5557}, {name: "hubble", orbitalPeriod: 5734}, {name: "moon", orbitalPeriod: 2377399}].
 
 console.log(result);