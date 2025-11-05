import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: (script) (csv file with STR information) (sequence text file)")
        return sys.exit(1)

    # TODO: Read database file into a variable
    database = []
    subsequence = []

    file = open(sys.argv[1], "r")
    reader = csv.DictReader(file)
    number_of_columns = len(next(reader))
    file.seek(0)

    # populate subsequence list which will be the keys of dicts used
    for row in reader:
        for key in row.keys():
            if key not in subsequence:
                subsequence.append(key)

    file.seek(0)
    counter = 0

    # populate database list w/dictionaries from rows of csv file
    for row in reader:
        temporary_dict = {}

        if counter != 0:
            for element in subsequence:
                temporary_dict[element] = row[element]

            database.append(temporary_dict)

        counter += 1

    file.close()

    # TODO: Read DNA sequence file into a variable
    file2 = open(sys.argv[2], "r")
    sequence = file2.readline()
    file2.close()

    # TODO: Find longest match of each STR in DNA sequence
    dna_repeats = {}

    for i in range(len(subsequence)):
        dna_repeats[subsequence[i]] = longest_match(sequence, subsequence[i])

    # TODO: Check database for matching profiles
    dna_match = "No match"

    # delete "name" from list
    subsequence.pop(0)

    for i in range(len(database)):
        check = 0
        for j in range(len(subsequence)):
            if int(database[i][subsequence[j]]) == int(dna_repeats[subsequence[j]]):
                check += 1

            if check == (number_of_columns - 1):
                dna_match = database[i]["name"]

    print(dna_match)

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
