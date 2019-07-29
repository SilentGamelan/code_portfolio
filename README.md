Example Code Portfolio - D Cooper
=================================

Included within are some completed exercises and projects from FCC, CS50, and personal code I wrote to explore data structures and sorting algorithms.

The examples include code written in C, python, Javascript, SQL, and utilising HTML/CSS, Node and other technologies.

I have exported them from the CS50 cloud platform which was my previous development environment, and collected them in a single repository for ease of viewing.

---

&nbsp;

The projects I am particularly proud of include: 

* **crack** - *a brute-force password cracker*
    - Fulfilled a life-long dream of being able to say that I have cracked a password! 

* **finance** - *a working simulated stock trading website, with mutiple user accounts and live price scraping* 
    - Independently designing and creating a fully functional website bolstered my confidence that I have the ability to persue programming as a full-time career

* **resize** - *reads in a bitmap image, and resizes it according to command-line argument*
    - Working with memory allocation and independently study the BMP file structure specification was challenging, but satisfying
    
* **FCC-APIs-HeaderParser** - *displays user agent information pulled from page requests*
    - Although the specification only required using express for simplicity, I was inspired to rewrite my code in vanilla node to learn more about webservers and requests

* **Functional Programming** - *various exercises which required a solution written in functional code style*
    - Learning a different programming approach stretched my abilities, and gave me a good grasp of `filter()`, `reduce()` and `map()`

---

&nbsp;

## Folder map and brief description of contents.



### Exercises and projects completed during HarvardX's CS50 course

```
/cs50 Projects/

    cc checker/         Verifies if a given number is a valid credit card number, and returns the name of the card issuer (works with real cc numbers)
    
    collatz/            Implementation of the collatz conjecture
    
    cryptography/
        /caesar.py      Implements a simple caesar cypher - takes a rotation value and plaintext, and outputs cyphertext
        /crack.c        Brute force DEC password cracker for password lengths of up to 4 characters plus 2 salt characters
        /vigenere.c     Implements encryption using a vigenere cypher - takes keytext and plaintext, then outputs cyphertext 
          
    fifteen/            Console-based sliding tile puzzle
    
    finance/            Multi-user stock trading simulator implemented in HTML, python and SQL. Scrapes live stock prices from the internet.
    
    mashup/             Search map by name/postcode with autocomplete functionality, generates map pins with list of local news headlines (python/flask/Gmaps API)
    
    recover/            Reads in a file representing a corrupted SD card - scans for deleted jpg files and outputs recovered image files to disk
    
    resize/             Reads in a BMP image file from disk, resizes and writes new file to disk 
    
    sentiments/         Simple sentiment analysis of tweets - takes twitter handle, scrapes most recent 200 tweets and classifies as positive/negative/neutral
    
    speller/            Implements a dictionary based spellchecker - takes a text and dictionary file, outputs list of misspelled words and performance info
    
    whodunit/           Reads in a BMP file and parses it using its header. Writes out a new BMP image containing steganographically hidden message
    
```

---

&nbsp;

### Exercises and projects completed during FreeCodeCamp course


```
/FCC Projects
    /Apis and MicroServices
        /FCC-APIs-HeaderParser  Sets up a nodeserver and returns a JSON containing useragent information of web requests. Has Express versions and my own     
                                manually written vanilla node server code
        
        /FCC-APIs-TimeStamp     Sets up a node server and validates timecodes supplied via route naming
    
    /Javascript and Algorithms

        /Functional Programming     solutions to exercises requiring functional code techniques
        /Intermediate Algorithms    solutions to varied exercise problems
        /Final Projects
            /caesar.js              JS implementation of caesar cypher
            /register.js            Calculates change required from payment in dollar denomonations
            /palindrome.js          Checks if a word is a palindrome
            /numerals.js            Converts a decimal number into roman numerals
            /telvalidator.js        Validates a phone number, based on US telephone format, uses regular expressions
```

---

&nbsp;

### Personal experiments exploring algorithms and data structures

```
/self study                     
    /algorithms
        /searches
        /sorts

    /data_structures
```



