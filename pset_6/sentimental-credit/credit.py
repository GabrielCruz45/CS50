# TODO
from cs50 import get_int


def main():

    # Prompt user for input
    card = user_prompt()

    # Check decimal places
    decimal_places = how_many_decimal_places(card)

    # Checksum algorithm
    validity = checksum(card, decimal_places)

    # Check card length and digits
    card_type = check_card_type(card, decimal_places)

    # Print AMEX, VISA, MASTERCARD or INVALID according to checksum and card type
    validation_print(card_type, validity)


def user_prompt():
    # get user card number
    userInput = get_int("Number: ")
    return userInput


def checksum(card, decimal):

    # sum of even numbers for checksum
    suma_pares = 0
    # sum of odd numbers for cheksum
    suma_impares = 0
    # prepare variable to run for loop according to length of card
    length = decimal - 1
    counter = 1

    # iterate over card numbers
    for i in range(length, -1, -1):
        # par
        temporary = str(card)

        # discern if even or odd
        if (counter % 2 == 0):
            temporary_even_variable = int(temporary[i])

            # if even, check if multiplicaton of number by 2 creates 2 digits ('10' or more)
            if (temporary_even_variable * 2 > 9):

                # if 2 digits, treate each digit as a separate number
                temporary_even_variable *= 2
                first_digit = str(temporary_even_variable)[0]
                second_digit = str(temporary_even_variable)[1]

                # add separate numbers to sum of even numbers for checksum
                suma_pares = int(first_digit) + int(second_digit) + suma_pares

            else:
                # if not add to sum of pairs for checksum
                temporary_even_variable *= 2
                suma_pares = temporary_even_variable + suma_pares

        # impar
        else:
            # if odd, add to sum of odd numbers for checksum
            temporary_odd_variable = int(temporary[i])
            suma_impares += temporary_odd_variable

        counter += 1

    # add even and odd numbers to get checksum
    checksum = suma_pares + suma_impares

    # return if last digit of checksum is a 0
    if (checksum % 10 == 0):
        return 1
    else:
        return 0


def check_card_type(card, decimal_places):

    # VISA
    if (decimal_places == 13):

        # get first digit of card
        first_digit = str(card)[0]
        first_digit = int(first_digit)

        # check if first digit of card is 4
        if (first_digit == 4):
            return "VISA"

        else:
            return "INVALID"

    # AMEX
    elif (decimal_places == 15):

        first_digit = str(card)[0]
        second_digit = str(card)[1]
        check_digits = int(first_digit + second_digit)

        # check if first numbers of card are 34 or 37
        if (check_digits == 34 or check_digits == 37):
            return "AMEX"
        else:
            return "INVALID"

    # MASTERCARD OR VISA
    elif (decimal_places == 16):

        check_digits = card / 10 ** 14

        # check if first numbers of card are numbers 50 - 56 for mastercard
        if (check_digits > 50 and check_digits < 56):
            return "MASTERCARD"

        # check if first numbers of card are numbers 39 - 50 for visa
        elif (check_digits > 39 and check_digits < 50):
            return "VISA"

        else:
            return "INVALID"

    # INVALID
    else:
        return "INVALID"


def validation_print(card_type, validity):

    # print if valid, the card's type, else invalid
    if (validity == 1):
        print(f"{card_type}")

    else:
        print("INVALID")


def how_many_decimal_places(number):
    decimal_places = len(str(number))

    return decimal_places


main()
