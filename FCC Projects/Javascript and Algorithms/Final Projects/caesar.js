// Caesar Cypher.js
// Implements a function to decode a 13 character rotated caesar cypher

function rot13(str) {
    let result = str.split("").map(c => {
        if(/[A-Z]/.test(c)) { 
            let x = c.charCodeAt();
            let rangeStart = "A".charCodeAt();
            let rangeEnd = "Z".charCodeAt();
            let offset = mod(x - rangeStart + 13, rangeEnd - rangeStart + 1);
            return String.fromCharCode(offset + rangeStart);
        } else {
            return c;
        }
    }).join("");
    
    return result;
}

function mod(x, y) {
    let r = x % y;
    return r < 0 ? y + r : r; 
}

  // Change the inputs below to test
  result = rot13("SERR PBQR PNZC");
  console.log(result);