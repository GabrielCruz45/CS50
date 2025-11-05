import csv
import requests
import sys


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv")

    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter (without writing) when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):

    new_cases = {}
    new_cases.setdefault(None, [])
    # cases = []

    # Populate new_cases dictionasry with name of states
    for row in reader:
        current_state = row['state']
        current_case = int(row['cases'])


        if current_state not in new_cases.keys():
            new_cases |= {current_state : current_case}

        elif current_state in new_cases.keys():

            if new_cases[current_state] == None:
                    new_cases[current_state].append(current_case)
                    print("Se supone que esto no pase ;(")

            elif len(str(new_cases[current_state])) < 14:
                current_list = new_cases[current_state]
                previous_case = current_list[-1]
                new_cases[current_state].append(current_case - previous_case)

            elif len(str(new_cases[current_state])) == 14:
                current_list = new_cases[current_state]
                previous_case = current_list[-1]
                new_cases[current_state].pop(0)
                new_cases[current_state].append(current_case - previous_case)

            else:
                print('Error adding to cases')
                sys.exit(1)

                previous_case = current_case
        else:
            print("Whatever bro")

        # new_cases[current_state] = cases
        # if len(cases) > 0:
        #     cases.pop()




    # # Iterate over each state looking for all the cases until end of document and
    # # adding last 14 days to list then adding said list
    # # as value to state : last 14 day cases dictionary

    # for key in dict(new_cases).keys():

    #     # print(key)
    #     current_state = new_cases[key]
    #     previous_case = 0

    #     for row in reader:
    #         print("hola")
    #         if current_state == row['state']:
    #             current_case = int(row['cases'])

    #             if new_cases[current_state] == None:
    #                 cases.append(current_case)
    #             elif len(cases) < 14:
    #                 cases.append(current_case - previous_case)
    #             elif len(cases) == 14:
    #                 cases.pop(0)
    #                 cases.append(current_case - previous_case)
    #             else:
    #                 print('Error adding to cases')
    #                 sys.exit(1)

    #             previous_case = current_case

    #         counter += 1

    #     new_cases[current_state] = cases
    #     if len(cases) > 0:
    #         cases.pop()

    # new_cases.popitem()
    print(new_cases)
    # print(cases)
    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):

    for state in states:
        print(state)

        if state in new_cases.keys():
            print(new_cases[state])





main()
