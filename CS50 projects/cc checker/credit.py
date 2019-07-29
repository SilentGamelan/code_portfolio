''' credit.py takes a credit card number as a string, tests it for validity using Luhn's algorithm and prints whether the number
    is invalid or, if valid, is a Amex/Mastercard/Visa card number. It will always return 0.

    It first checks that the passed string is numeric only, then determines the type of card by the intial digit(s).
    It then reverses the string to perform Luhn's Algorithm - using odd/evenness of index x to apply approprate operation.
    It lastly uses checksum to confirm (in)validity.`

'''

def main(cc_num):
    cc_len = len(cc_num)
    if cc_num.isdecimal and cc_len in (13, 15, 16):
        sum1 = 0
        sum2 = 0
        if cc_num[0:1] in ('4') and cc_len in (13, 16):
            cc_type = "VISA\n"
        elif cc_num[0:2] in ('34', '37') and cc_len == 15:
            cc_type = "AMEX\n"
        elif cc_num[0:2] in ('51', '52', '53', '54', '55') and cc_len == 16:
            cc_type = "MASTERCARD\n"
        else:
            cc_type = "INVALID\n"

        if cc_type != "INVALID\n":
            cc_num = cc_num[::-1]
            for x in range(cc_len):
                if x % 2 == 0:
                    sum1 += int(cc_num[x])
                else:
                    product = int(cc_num[x]) * 2
                    sum2 += product % 10
                    sum2 += product // 10

            sum1 += sum2

            if sum1 % 10 != 0:
                cc_type = "INVALID\n"
    else:
        cc_type = "INVALID\n"


    print(cc_type)
    return 0

if __name__ == "__main__":
    while True:
        cc_num = input("Enter Credit Card number: ")

        if cc_num.isdecimal():
            break
        else:
            print("Please enter numeric values only.\n")

    main(cc_num)

