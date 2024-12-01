def is_number(num):
    return num.isdigit()

def validation(num):
    first_checksum = 0
    second_checksum = 0
    
    for i in range(len(num)-1, -1, -1):
        tmp_digit = int(num[i])
        if i & 1:
            first_checksum += tmp_digit
            tmp_digit *= 2
            second_checksum += (tmp_digit // 10 + tmp_digit % 10)
        else:
            second_checksum += tmp_digit
            tmp_digit *= 2
            first_checksum += (tmp_digit // 10 + tmp_digit % 10)
            
    return (first_checksum % 10 == 0 or second_checksum % 10 == 0) and len(num) >= 13

def print_card_brand(num):
    if num[0] == '3' and num[1] in ['4', '7'] and len(num) == 15:
        print("AMEX")
    elif num[0] == '5' and int(num[1]) <= 5 and len(num) == 16:
        print("MASTERCARD")
    elif (num[0] == '4' and len(num) == 13) or (num[0] == '4' and int(num[1]) <= 6 and len(num) == 16):
        print("VISA")
    else:
        print("INVALID")

def main():
    while True:
        num = input("Number: ")
        if is_number(num):
            if validation(num):
                print_card_brand(num)
                break
            else:
                print("INVALID")
                break

if __name__ == "__main__":
    main()
