//   Convert HTML Entities.js

/*

Convert the characters &, <, >, " (double quote), and ' (apostrophe), in a string to their corresponding HTML entities.
*/

// Feels a bit hacky
function convertHTML(str) {
    const entityDic = {
        "&": "&amp",
        "<": "&lt",
        ">": "&gt",
        "\"": "&quot",
        "\'": "&apos"
    };

    for(const key in entityDic) {
        str = str.split(key).join(entityDic[key]+';');    
    }

    return str;
  }



result = convertHTML("Dolce & Gabbana");

//-------------------
console.log(result);

