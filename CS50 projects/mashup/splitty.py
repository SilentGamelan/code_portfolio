"""
    experimenting with different approaches to tokenizing/sanitizing input
    Trying both python methods and RegEx, after playing around with RegExOne site

     x in splitme:
        if x.isalnum() or x.isspace():
            tokenized.extend(x)
        else:
            tokenized.extend(" ")
"""

import sys
import re

def main(splitme):
    print(type(splitme))

    symbol_list = [',' , '!', '?', ';', ':', '.']
    tokenized = []

    print(' '.join(splitme.split()))
    print("".join([ c if c.isalnum() else " " for c in splitme ]))
    print( "".join([ c if c.isalnum() else " " for c in splitme ]).strip().split(" ") )

    s = re.sub('[^0-9a-zA-Z]+', ' ', splitme).split(" ")
    print(s, splitme)
    print(type(s))

if __name__ == "__main__":

    lenny = len(sys.argv)

    splitme = ""

    if lenny == 1:
        print("Splitty requires a string as parameter")
        sys.exit(0)
    elif lenny > 2:
        splitme = ' '.join(sys.argv[1:])
    else:
        splitme = sys.argv[1]

    main(splitme)

