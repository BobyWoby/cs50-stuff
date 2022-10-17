#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{

    if(argc != 2){
        printf("ur dumb\n");
        return 1;
    }
    string cypher = argv[1];
    if(strlen(cypher) != 26){
        printf("u just had to try and be special didn't u\n");
        return 1;
    }

    for(int i = 0; i < strlen(cypher); i++){
        if (!(isalpha(cypher[i])))
            {
                printf("Key must contain only letters.\n");
                return 1;
            }
    }
  int matches = 0;

    for (int i = 0; i<26; i++)
    {
        for (int j = 0; argv[1][j] != '\0'; j++)
        {

            if (argv[1][j] == argv[1][i])
            {
                matches++;
            }
        }
    }
if (matches!= 26)
    {
        printf("do not repeat letters in key\n");
        return 1;
    }





    string plaintext = get_string("plaintext: ");
    string result = plaintext;

    for(int i = 0; i < strlen(plaintext); i++){
        if(isalpha(plaintext[i])){
            if(islower(plaintext[i])){
                result[i] = tolower(cypher[plaintext[i]-97]);
            }
            else if(isupper(plaintext[i])){
                result[i] = toupper(cypher[plaintext[i]-65]);
            }
        }
        else{
            result[i] = plaintext[i];
        }
    }
    printf("ciphertext: %s\n", result);
    return 0;
}