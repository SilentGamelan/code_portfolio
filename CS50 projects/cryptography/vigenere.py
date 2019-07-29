''' vigenere.py
    -----------

    port of my original vigenere.c into python

    Implemented to be importable if required.

    Ran as standalone, vigenere.py will require precisely 1 command-line argument as a cipher-keyword.
    As a module, main() will expect a cipher-keyword "keyword" to be passed from the caller.

'''

import sys

def main(keyword):
    if not isinstance(keyword, str):
        print("argument must be a string")
        return 1

    plaintext = input("plaintext: ")
    ciphertext = []
    key_index = 0
    key_len = len(keyword)

    for x in plaintext:
        if x.isalpha():
            ciphertext.append(caesar(x, keyword[key_index % key_len]))
            key_index += 1
        else:
            ciphertext.append(x)
    print("".join(ciphertext))
    return 0

def caesar(plain_char, key_char):
    if plain_char.isupper():
        case = 'A'
    else:
        case = 'a'

    return chr((ord(plain_char) - ord(case) + (ord(key_char.upper()) - ord('A')) % 25 + ord(case)))



if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("vigenere.py requires exactly 1 command line argument\n")
        sys.exit(0)

    main(sys.argv[1])