'''
crack.py takes a DES hashed password as list, either via a module call or via command line argument
and will attempt to brute-force crack it. It uses a recursive password generation method.

PW_LEN and ALPHABET are global constants which can be altered to change the target password
length and key-space.


'''
import crypt, sys

PW_LEN = 4
ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

def main(full_hash):

    curr_pw = [None] * PW_LEN

    if brute_force(0, 1, full_hash, curr_pw):
        return 0
    else:
        return 1

def brute_force(curr_column, current_len, full_hash, curr_pw):


    for letter in ALPHABET:
        curr_pw[curr_column] = letter

        if check_password(curr_column+1, full_hash, curr_pw):
            return True

        if current_len < PW_LEN:
            if brute_force(curr_column+1, current_len+1, full_hash, curr_pw):
                return True

    return 0



def check_password(pw_index, full_hash, curr_pw):

    if crypt.crypt("".join(curr_pw[:pw_index]), "".join(full_hash[:2])) == full_hash:
        print("{}\n".format("".join(curr_pw)))
        return True
    else:
        return False

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Error: crack.py requires (precisely) one argument only")
        sys.exit(1)
    else:
        main(sys.argv[1])

