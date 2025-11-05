import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            current_team = row['team']
            current_rating = row['rating']


            temporary_dict = {'team' : current_team, 'rating' : current_rating}
            teams.append(temporary_dict)

        print(teams)




main()