import csv
import sys

def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py database.csv sample_sequence.txt")

    database = []
    allele_count = []
    #Read teams into memory from file
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)
    with open(sys.argv[2], "r") as file:
        reader = csv.reader(file)
        for str in reader:
            sample = str
        database_keys = list(database[0].keys())
        for i in range (1, len(database_keys), 1):
            allele_count.append(sequence_slicer(database_keys[i], sample))

    #print(f"database_keys is {database_keys}")
    #print(f"database is {database}")
    #print(f"sample is {sample}")
    #print(f"Entirety of allele_count is {allele_count}")
    match = find_match(allele_count, database_keys, database)
    print (match)


def sequence_slicer(allele,sample):
    allele_count = {}
    allele_count[allele] = 0
    allele_length = len(allele)
    for i in range (0, (len(sample[0]) - allele_length)):
        sample_sequence = sample[0][i:(i + allele_length)]
        if allele in sample_sequence:
            tmp_count = 0
            j = i
            loop = 0
            while(loop == 0):
                if sample[0][j:(j + allele_length)] != allele:
                    if tmp_count > allele_count[allele]:
                        allele_count[allele] = tmp_count
                    loop = 1
                tmp_count += 1
                j += len(allele)
    #print(f"allele_counts for {allele} is {allele_count}")
    #FIND MAXIMUM ALLELE COUNT NUMBER AND RETURN A LIST CONTAINING THAT HIGHEST SCORE
    return allele_count


def find_match(allele_count, database_keys, database):
    database_keys = list(database[0].keys())
    for i in range (0, len(database)):
        sameness = 0
        person_values = list(database[i].values())
        for j in range(0, len(allele_count)):
            #print(f"Person '{person_values[0]}' is comparing their value of {person_values[j+1]} to sample's {allele_count[j]}")
            desired_allele_count = list(allele_count[j].values())[0]
            #print(f"person_values[j+1] is {person_values[j+1]} and allele_count[j] is {desired_allele_count}")
            if int(person_values[j+1]) == desired_allele_count:
                #print(f"Sameness identified for {database[i]}")
                sameness += 1
                if sameness == len(allele_count):
                    #print(f"!!!!! PERSON FOUND !!!!!")
                    match = str(person_values[0])
                    return match
    match = "No match"
    return match


main()