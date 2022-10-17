#include <stdio.h>
#include <cs50.h>
#include <math.h>

//4003600000000014

int main(void)
{
    //get card info
    unsigned long int card;
    do
    {
        card = get_long("Card number: ");
    }
    while (card < 1);

    //prepare card info to be spliced into array
    const int CARD_LENGTH = (int) log10((double) card);

    //splice card info
    int digits[CARD_LENGTH];
    for (int i = 0; card > 0; i++)
    {
        digits[i] = card % 10;
        card /= 10;
    }


    //implement Luhn's algorithm

    //multiply every second number by 2
    int evenDigits[(int) (CARD_LENGTH / 2)];
    for (int i = 0; i <= (int) (CARD_LENGTH / 2); i ++)
    {
        evenDigits[i] = 0;
        evenDigits[i] = digits[(2 * i) + 1] * 2;
        printf("%i\n", evenDigits[i]);
    }

    //add individual digits together
    int total = 0;
    printf("num1 : %i\n", digits[CARD_LENGTH]);
    for (int i = 0; i < ((int) (CARD_LENGTH / 2) + CARD_LENGTH % 2) ; i++)
    {
        //printf("even added : %i\n", evenDigits[i]);
        //adds 1 if over 10
        if (evenDigits[i] > 9)
        {
            total ++;
        }
    printf("num2 : %i\n", digits[CARD_LENGTH]);
        //adds ones place of evenDigits[i]
        total += evenDigits[i] % 10;

    }

    //cycle through odd digits
    for (int i = 0; i <= CARD_LENGTH; i += 2)
    {
        total += digits[i];
        //printf("odd total : %i\n", digits[CARD_LENGTH]);
    }
    printf("total : %i\n", total);
    if (total % 10 == 0)
    {
        if (digits[CARD_LENGTH] == 3 && (digits[CARD_LENGTH - 1] == 4 || digits[CARD_LENGTH - 1] == 7))
        {
            printf("AMEX\n");
        }
        else if (digits[CARD_LENGTH] == 5 && digits[CARD_LENGTH - 1] >= 1 && digits[CARD_LENGTH - 1] <= 5)
        {
            printf("MASTERCARD\n");
        }
        else if (digits[CARD_LENGTH] == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;


}