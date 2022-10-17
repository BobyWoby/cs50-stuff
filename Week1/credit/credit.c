#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long num, temp, startDig;
    int counter = 0;
    int sum = 0;
    num = get_long("Number: ");
    temp = num;
    startDig = num;
    temp /= 10;
//finds every other digit starting from the second to last and multiplies it by two, then adds it to sum
    while(temp){
        int tmp = 2 * (temp % 10);
        while(tmp){
            sum += tmp % 10;
            tmp /=10;
        }
        temp /= 100;
    }
//adds the remaining digit
    while(num){
        sum += num % 10;
        num /= 100;
    }
    if(sum % 10 == 0 ){
        //finds the starting digits
        while(startDig > 99){
            startDig/=10;
            //finds how many digits there are
            counter++;
        }
        //adds two to digit count cuz startDig stops at 2 digits
        counter += 2;
        if(counter == 15 || counter == 16 || counter == 13){
            if(startDig > 39 && startDig < 50){
                printf("VISA\n");
            }
            else if(startDig == 51 || startDig == 52 || startDig == 53 || startDig == 54 || startDig == 55){
                printf("MASTERCARD\n");
            }
            else if(startDig == 34 || startDig == 37){
                printf("AMEX\n");
            }
            else{
                printf("INVALID\n");
            }
        }
        else{
            printf("INVALID\n");
        }

    }
    else{
        printf("INVALID\n");
    }

}