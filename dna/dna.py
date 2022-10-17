import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("wrong usage fool")
        sys.exit(1)

    # TODO: Read database file into a variable
    rows = []
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        header = next(reader)
        header.pop(0)
        dictReader = csv.DictReader(file)
        for row in reader:
            rows.append(row)
        #print(rows)
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        reader = csv.reader(file)
        sequence = str(next(reader))
        #print(sequence)
        # TODO: Find longest match of each STR in DNA sequence
        length = []
        for i in range(len(header)):
            length.append(longest_match(sequence, header[i]))
        # TODO: Check database for matching profiles

    for i in range(len(length)):
        length[i] = str(length[i])
    #print(rows)
    names = []
    for i in range(len(rows)):
        names.append(rows[i].pop(0))
    isMatch = False
    for i in range(len(rows)):
        if rows[i] == length:
            isMatch = True
            print(f"{names[i]}")
    if not isMatch:
        print("No match")
    #print(length)
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
