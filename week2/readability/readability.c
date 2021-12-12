#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int l = 0, el = 0, s=0;
    double w = 0;

//Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
//where L=letters per 100 words
//and S=average number of sentences per 100 words

    string text = get_string("Text: ");

    //The Coleman-Liau index = (0.0588 * L) - (0.296 * S) - 15.7
    for (int i = 0, n = strlen(text); i < n; i++)
        {
            int letter = text[i];
            //convert islower : toupper
            if (islower(letter))
            {
                letter = toupper(letter);
            }
            if (letter >= 'A' && letter <= 'Z')
            {
                el++;
                l++;
            }
            //Begin new word after finding an SP
            if (letter == 32 && el > 0)
            {
                w++;
                el = 0;
            }
            //Begin new sentence after finding  a . or ! or ?
            if (letter == '.' || letter == '!' || letter == '?')
            {
                if (el > 0)
                {
                    s++;
                    w++;
                    el = 0;
                }
            }



        }
    w /= 100;
    double L = l / w;
    double S = s / w;
    L *= 0.0588;
    S *=0.296;
    double grade = L - S;
    grade -= 15.8;
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf ("Grade 16+\n");
    }
    else
    {
    int final = round(grade);

//THE PROBLEM IS IN M BIG L AND BIG S SOMEWHERE


//Father
//Grade 7, 214 letters, 56 words, 4 sentences

//Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
//where L=letters per 100 words
//and S=average number of sentences per 100 words

    printf("Grade %i\n", final);
    }
    //printf("big L is %f and big S is %f and grade is %f\n", L, S, grade);
    //printf("Letters = %i\nWords = %0lf\nSentences = %i\n", l, w, s);
}