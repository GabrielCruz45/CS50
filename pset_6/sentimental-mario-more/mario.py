# TODO
from cs50 import get_int


def main():

    # prompt user input
    userMainInput = get_height()

    # start printinng by row
    for row in range(userMainInput):

        # print first spaces according to number of row
        for space in range(userMainInput - (1 + row)):
            print(' ', end="")

        # print blocks by row
        for block in range(row + 1):
            print('#', end="")

        # space between half-pyramids
        print('  ', end="")

        # second round of blocks byy row
        for block in range(row + 1):
            print('#', end="")

        # new line
        print("")


# function to rpompt user for integer input; filter if out of 1-8 range
def get_height():
    while True:
        userGet_HeightInput = get_int('Height of half_pyramids (integer from 1-8): ')
        if userGet_HeightInput > 0 and userGet_HeightInput < 9:
            return userGet_HeightInput


# call main function
main()
