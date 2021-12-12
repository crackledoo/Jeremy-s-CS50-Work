# Jeremy-s-CS50-Work
A collection of the labs and problem sets from the free 'introduction to computer science' course offered by Harvard/Yale, CS50 2020.


I completed this course in 2021, and later decided to upload my completed projects to Github for posterity.

This collection is ordered into a series of 9 folders, named after each week of course content that I chose to include.


While CS50 2020 includes 11 weeks in total, I chose not to include weeks 0 and 10. Week 0 only contained a brief project for Scratch, and week 10 contained only a quiz and a Final Project. The Final Project will be a separate repository under this Github account, and will be included at a later time (my final project is a professional portfolio, but I want to continue exploring different backend services before commiting the portfolio to its own repository here, where it will live a long and fulfilling life).


I can't take credit for the entirety of the code in these folders: many of CS50's labs and problem sets contain initial codebases, intended to either reduce redundancy in the course's overall work or to facilitate learning by simply avoiding certain arduous subjects. If you want to know more about the initial code, and the exact coding that each of these projects had actually required, I recommend clicking on the links for each project below.


The course also used its own [web-based IDE](https://ide.cs50.io/), with libraries and software pre-installed. I can't promise that this repository includes all the necessary libraries for certain projects, but I'm fairly certain that any programs will work if they're executed through the CS50 IDE.


If you want to know more about the projects, I've described a bit about them below:

<br>

<br>

## PROGRAMMING IN C


### Week 1: C

Week 1's **lab** consisted of two projects: [Hello](https://cs50.harvard.edu/x/2021/labs/1/hello/) (a basic 'Hello World' and introduction to the course's IDE) and [Population](https://cs50.harvard.edu/x/2021/labs/1/population/) (a basic mathematical program that can predict a population's size based off of a constant rate of growth and variable population/timeframe.

Week 1's **problem set** consisted of two pairs of easier/harder projects: [Mario (easier)](https://cs50.harvard.edu/x/2021/psets/1/mario/less/) / [Mario (harder)](https://cs50.harvard.edu/x/2021/psets/1/mario/more/), and [Cash](https://cs50.harvard.edu/x/2021/psets/1/cash/) / [Credit](https://cs50.harvard.edu/x/2021/psets/1/credit/).

I completed **Mario (harder)** and **Cash** (after a failed attempt at **Credit**).

- **Mario (harder)** prints a pyramid, consisting of a diagonal series of #'s, and its inverse, separated by a middle column two spaces wide. The pyramid depended on a variable input for its height.

- **Cash** finds the most coin-efficient distribution of change for any given floating integer input.

- **Credit** asked the student to use Luhn's algorithm to verify and differentiate simplified versions of card numbers for American Express, MasterCard, and Visa cards. In hindsight, my attempt at the program had failed to correctly identify (and then sum) every other digit. It was incredibly easy to notice this later, during the problem set in week 6. This later problem set presents the same project options for week 1 - but instead through Python and with several additional weeks of coding experience.



### Week 2: Arrays

Week 2's **lab** consisted of one project: [Scrabble](https://cs50.harvard.edu/x/2021/labs/2/). The program takes a string as input from two players. It then compares the string against a pre-established score-card, and then either names the player with the highest-scoring string as the winner or declares a tie.

Week 2's **problem set** consisted of one project and one pair of easier/harder projects: [Readability](https://cs50.harvard.edu/x/2021/psets/2/readability/) and [Ceasar](https://cs50.harvard.edu/x/2021/psets/2/caesar/) / [Substitution](https://cs50.harvard.edu/x/2021/psets/2/substitution/).

I completed **Readability** and **Caesar** (after, again, a failed attempt at **Substitution**).

- **Readability** computes the [Coleman-Liau index](https://en.wikipedia.org/wiki/Coleman%E2%80%93Liau_index) of any given string of text, returning a reading level ranging from "Before Grade 1" to "Grade 16+". Since it was still a simple program, I was allowed to ignore cases of non-sentence punctuation (e.g. 'Mr.' and 'e.g.').

- **Caesar** imitates the popular (and very beginner-friendly) encription style of simply substituting every letter in a string with the letter n spaces adjacent.

- **Substitution** asked the student to encrypt a given input string using a second input key of exactly 26 characters. The nth letter of the alphabet, for each occurence in the message, would then be replaced with the nth letter of the key, while retaining original capitalization. I can't, for the life of me, remember where I failed at **Substitution**. I think I might have just gotten too confused by the process to continue?



### Week 3: Algorithms

Week 3's **lab** was a simple quiz, asking the student to identify the sorting method (selection sort, bubble sort, or merge sort) of unknown programs by only the speed with which each program was able to sort sets of ordered and randomized numbers.

Week 3's **problem set** consisted of one project and one pair of easier/harder projects: [Plurality](https://cs50.harvard.edu/x/2021/psets/3/plurality/) and [Runoff](https://cs50.harvard.edu/x/2021/psets/3/runoff/) / [Tideman](https://cs50.harvard.edu/x/2021/psets/3/tideman/).

I completed **Plurality** and **Runoff** (after, once AGAIN, a failed attempt at **Tideman**).

- **Plurality** runs a plurality election, which takes as input a series of candidates (no more than 9), a number of voters, and strings representing each voter's desired candidate, and then prints the winner(s) of the election.

- **Runoff** uses a ranked-choice voting system to, in the case of a plurality tie, calculate the most-desired candidate. It takes as input the same candidates and voters, but then allows each voter 3 strings as input, where the first string is the most-desired candidate and the third is the third-most-desired candidate. The program systematically eliminates candidates with the lowest desirability until it prints the final winning candidate(s).

- **Tideman** asked the student to use the Tideman (or 'ranked pairs') voting method to calculate the most-desired candidate using an adjacency matrix. With the same inputs as Plurality, the program would find the most-desired candidate by generating an adjacency matrix of each pair of candidates, where the more-preferred of the two is selected as winning over the other. The program would also be able to identify if any pairing would create a loop, and skip that pairing if so. At the time, I didn't have a sufficient understanding of recursive functions to identify any loops in the matrix and resigned to writing the easier program. This was by far the most difficult project in the entire course for me, so I'm not too disappointed to have failed.



### Week 4: Memory
  
Week 4's **lab** consisted of one project: [Volume](https://cs50.harvard.edu/x/2021/labs/4/). The program takes a floating-point number and WAV file as input, and adjusts the audio volume of the selected file by that number.

Week 4's **problem set** consisted, again, of one project and one pair of easier/harder projects: [Recover](https://cs50.harvard.edu/x/2021/psets/4/recover/) and [Filter (easy)](https://cs50.harvard.edu/x/2021/psets/4/filter/less/) / [Filter (hard)](https://cs50.harvard.edu/x/2021/psets/4/filter/more/).

I completed **Recover** and **Filter (hard)**.

- **Recover** recovers deleted JPEGs from a given memory card by scanning the card's contiguous blocks and searching for a JPEG's signature bytes. The program assumes that all of the deleted JPEGs are perfectly adjacent to each other.

- **Filter** takes as arguments an image, the desired filter operation to use on the image, and the desired name of the outputted image. Both versions of Filter require student to implement a Grayscale, Reflection, and Box Blur function. The hard version also implements a [Sobel edge detection](https://en.wikipedia.org/wiki/Sobel_operator) function.



### Week 5: Data Structures

Week 5's **lab** consisted of one project: [Inheritance](https://cs50.harvard.edu/x/2021/labs/5/). The program takes as input a number of n generations, and then creates a series of two parents for each person, ending with a single youngest person to generate a total of (2^n)+1 people. The program then gives the oldest generation a random assignment of two blood type alleles ('A', 'B', or 'O'), and randomly decided the allele inheritence of that generations children. This assignment ends with the youngest person.

Week 5's **problem set** consisted of only one project: [Speller](https://cs50.harvard.edu/x/2021/psets/5/speller/).

- **Speller** marks the only problem set that I failed to complete in CS50. The project asked students to perform a spell-check of entire books by storing a given dictionary in memory and then comparing every word of the book against the dictionary. I was too absorbed in designing the optimal hash function for the dictionary, became overwhelmed, and resigned.

<br>

<br>

## PYTHON

### Week 6: 

Week 6's **lab** consisted of one project: [World Cup](https://cs50.harvard.edu/x/2021/labs/6/). The program runs simulations of the FIFA World Cup. It generates 1000 randomized tournaments, whose brackets were randomized and whose matches were slightly randomized (with weight granted to the team's 2018 Men's and 2019 Women's FIFA ratings). It then prints a list of each team's simulated odds of tournament victory.

Week 6's **problem set** of **three projects** and **two** pairs of easier/harder projects: [Hello](https://cs50.harvard.edu/x/2021/psets/6/hello/), [Readability](https://cs50.harvard.edu/x/2021/psets/6/readability/) and [DNA](https://cs50.harvard.edu/x/2021/psets/6/dna/), and [Mario (easy)](https://cs50.harvard.edu/x/2021/psets/6/mario/less/) / [Mario (hard)](https://cs50.harvard.edu/x/2021/psets/6/mario/more/) and [Cash](https://cs50.harvard.edu/x/2021/psets/6/cash/) / [Credit](https://cs50.harvard.edu/x/2021/psets/6/credit/).
- **Hello** prompts the user for their name, and then returns "hello, {name}". Very simple.
- **Readability** once again performs the Coleman-Liau index on any provided string of text.
- **DNA** reads a txt file containing a sample of DNA nucleotide bases belonging to an unknown person, and a txt file contianing several peoples' DNA nucleotide bases. The program then enumerates any Short Tandem Repeats within the sample, and identifies any available person with matching STRs.
- **Mario (hard)** once again generates a pyramid of #'s based on the user's inputted height.
- **Credit** once again verifies and identifies card numbers with Luhn's algorithm.

<br>

<br>

## SQLITE

### Week 7: SQL

Week 7's **lab** was simply a series of prompts named [Songs](https://cs50.harvard.edu/x/2021/labs/7/), asking the student to write the cortrect SQL queries to acquire information from a Spotify database.

Week 7's **problem set** consisted of two prompts as well: [Movies](https://cs50.harvard.edu/x/2021/psets/7/movies/) and [Fiftyville](https://cs50.harvard.edu/x/2021/psets/7/fiftyville/). 
- **Movies** asked for a similar set of SQL queries to acquire information from an IMDB database.
- **Fiftyville** was an incredibly entertaining 'SQL mystery', where the student had to follow a series of hints to query for the exact information to identify a criminal and their accomplice.

<br>

<br>

## HTML, CSS, JAVASCRIPT

### Week 8: HTML, CSS, JavaScript

Week 8's **lab** consisted of a single project: [Trivia](https://cs50.harvard.edu/x/2021/labs/8/). The webpage presents a multiple choice question and a free response question, both of which will turn red/green depending upon the user's answer.

Week 8's **problem set** consisted also of a single project: [Homepage](https://cs50.harvard.edu/x/2021/psets/8/homepage/). The webpage is simply a personalized homepage, which marked the beginnings of my professional portfolio.

<br>

<br>

## FLASK

### Week 9: Flask

Finally, week 9's **lab** consisted of a single project: Birthdays. The webpage both presents a table of every entrant's name and birthday -- and also allows the user to enter their own name and birthday to the database.

Week 9's **problem set** consisted of a single project: [Finance](https://cs50.harvard.edu/x/2021/psets/9/finance/). Certainly the largest endeavor of the course, this website features a host of dynamic webpages that quotes stocks via IEX's API, and allows a user to create an account, log in for a session, and buy/sell stocks in real time. As the culmination of Python, HTML5, and Flask, and entire fullstack web development tends to be, this project took me the longest time to complete.

<br>

<br>

###And that's it!
I hope you enjoyed reading to the end.
