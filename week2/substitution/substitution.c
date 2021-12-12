#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char encrypt (char, string);

int main (int argc, string argv[])
{
    string key = argv[1];
    //ENFORCING PARAMETERS
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (26 != strlen(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, n = strlen(key); i < n; i++)
        {
           if (isalpha(key[i]) == false)
           {
                printf ("All characters must be alphabetical\n");
                return 1;
           }
           for (int j = i + 1; j < n; j++)
           {
               if (key[i] == key[j])
               {
                   printf ("Key must not contain duplicate characters\n");
                   return 1;
               }
           }
        }
        //PROMPT MESSAGE AND BEGIN ENCRYPTION
        string message = get_string("plaintext: ");
        printf ("ciphertext: ");
        for (int i = 0, n = strlen(message); i < n; i++)
        {
            char l = message[i];
            if (isalpha(l))
            {
                if (l < 'a')
                {
                l = tolower(l);
                //printf("%c", l);
                l = encrypt (l, key);
                l = toupper(l);
                printf("%c", l);
                }
                else
                {
                l = encrypt (l, key);
                l = tolower(l);
                printf("%c", l);
                }
            }
            else
            {
                printf("%c", l);
            }
        }
        printf("\n");

return 0;
}

char encrypt(char l, string key)
{
    int k = l - 'a';
    //printf ("\nk is %i, l is %c\n", k, l);
    //printf ("%s\n", key);
    l = key[k];
    return l;
}