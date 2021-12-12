# Simulate a sports tournament

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
    counts = {}

    #Read teams into memory from file
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        next(reader)
        for row in reader:
            row[1] = int(row[1])
            teams.append(row)
    #print(teams)

    #Simulate N tournaments and keep track of win counts
    for i in range (N):
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    #print(counts)
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = (team1[1])
    rating2 = (team2[1])
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    #print("length of teams BEFORE loop is " + str(len(teams)))
    for i in range(0, len(teams), 2):
        #print("length of teams is " + str(len(teams)))
        #print("i is " + str(i))
        #print(teams[i])
        #print(teams[i+1])
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO: Simulate a series of rounds
    winners = simulate_round(teams)
    while(True):
        if len(winners) == 1:
            winner = str(winners[0][0])
            break
        winners = simulate_round(winners)
        #print("succesfully simulated a round")
        #print("winners length is " + str(len(winners)))
    return winner


if __name__ == "__main__":
    main()
