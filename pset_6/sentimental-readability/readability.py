# TODO

from cs50 import get_string


def main():

    # prompt user for text
    userText = get_string("Text: ")

    # determine readability for text
    grade = readability(userText)

    # output grade level
    print_grade_level(grade)


def readability(text):

    letters = 0
    words = 0
    sentences = 0

    # check for each letter in user text
    for letter in text:
        if (letter.isalpha()):
            letters += 1

        elif (letter.isspace()):
            words += 1

        elif (letter == '.' or letter == '!' or letter == '?'):
            sentences += 1

    words += 1

    # l is average number og letter per 100 words
    L = letters / words * 100

    # S is number of sentences per 100 words
    S = sentences / words * 100

    # Coleman-Lieau index
    index = (0.0588 * L) - (0.296 * S) - 15.8

    # round index
    grade = round(index)

    # output grade
    return grade


def print_grade_level(grade):

    # check input variable and print grade level
    if (grade > 0 and grade < 17):
        print(f'Grade {grade}')

    elif (grade > 16):
        print('Grade 16+')

    else:
        print('Before Grade 1')


main()
