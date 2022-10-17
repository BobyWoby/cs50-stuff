#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float algorithm(int letters, int words, int sentences);

int main(void)
{
    string sentence;
    do{
        sentence = get_string("Text: ");
    }while(strlen(sentence) < 1);
    int index = algorithm(count_letters(sentence), count_words(sentence), count_sentences(sentence));
    index = round(index);

    if(index <= 1){
        printf("Before Grade 1\n");
    }
    else if(index > 1 && index <= 15){
        printf("Grade %i\n", index);
    }
    else{
        printf("Grade 16+\n");
    }

}


int count_letters(string text){
    int count = 0;
    for(int i = 0, n = strlen(text); i < n; i++){
        if(isalpha(text[i])){
            count++;
        }
    }
    return count;
}

int count_words(string text){
    int count = 1;
    	for(int i =0, n = strlen(text); i < n; i++){
            if(isspace(text[i])){
                count++;
            }
        }
    return count;
}

int count_sentences(string text){
    int count = 0;
        for(int i =0, n = strlen(text); i < n; i++){
            if((text[i] == '.' || text[i] == '!'| text[i] == '?')){
                count++;
            }
        }
    return count;
}

float algorithm(int letters, int words, int sentences){
    int index = 0.0588 * (letters/words * 100) - 0.296 * (sentences/words * 100) - 15.8;
    float L = ((float)letters/words) * 100;
    //printf("%f\n",L);
    float S = ((float)sentences/words) * 100;
    //printf("%f\n",S);
    index = round(0.0588 * L - 0.296 * S - 15.8);


    return index;
}