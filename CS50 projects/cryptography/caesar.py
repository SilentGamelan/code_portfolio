import sys

def main(rotval):
    try:
        rotval = int(rotval) % 26
    except ValueError:
        print("ERROR: argument not an integer")
        return 1

    if rotval < 0:
        print("ERROR: Please enter a non-negative integer")
        return 1

    plaintext = input("plaintext: ")
    ciphertext = []
    for x in plaintext:
        if x >= 'A' and x <= 'Z':
            ciphertext.append(chr((((ord(x) - ord('A')) + rotval) % 25) + ord('A')))
        elif x >= 'a' and x <= 'z':
            ciphertext.append(chr((((ord(x) - ord('a')) + rotval) % 25) + ord('a')))
        else:
            ciphertext.append(x)

    print("ciphertext: {}\n".format(''.join(ciphertext)))
    return 0

if __name__ == "__main__":
    argc = len(sys.argv)
    if argc != 2:
        print("ERROR: Please enter precisely one argument")
        sys.exit(1)
    main(sys.argv[1])