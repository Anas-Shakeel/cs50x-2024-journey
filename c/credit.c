// Program check if a credit card number
// is american express card, mastercard or visa.

/*
American express : 15 digits, starts with 34 or 37
Mastercard : 16 digits, starts with 51,52,53,54 or 55.
Visa : 13 or 16 digits, starts with 4

It follows a checksum function:

Checksum:
    multiply every other digit by 2, starting with second-to-last digit (2nd last)
    add those product's digits together
    add the sum to the sum of the digits that weren't multiplied by 2
    if total's last digit is 0, number is valid! otherwise it's not!

for example : credit number '4003600000000014'
- take every other digit (starting from 2ndlast)
    4003600000000014 > 40600001
- multiply each by 2
    40600001 > (4*2) (0*2) (6*2) (0*2) (0*2) (0*2) (0*2) (1*2)
    8 0 12 0 0 0 0 2 > 801200002
- add all these digits together
    801200002 > 8+0+1+2+0+0+0+0+2
    13
- add result '13' to all digits that we didn't multiply by 2
    13+0+3+0+0+0+0+0+4 > 20
- check last digit of the result '20'
    if last digit is 0, it's valid
    if it's not, it's not!
    result 20 > last digit 0 > hence validates the checksum!


Checksum Algorithm:
-------------------
for credit > '4003600000000014'
do{
    last_digit = last digit of credit
    remove last digit from credit
    / sum1 is the sum of the digits which didn't get multiplied by 2
    sum1 += last_digit  // add last_digit to sum1

    2nd_last_digit = last digit of credit (since previous last digit is removed above)
    remove last digit from credit

    2nd_last_digit *= 2  // multiply 2nd_last_digit by 2

    / Split 2nd_last_digit if greater than 9 (aka, with 2 digits)
    / e.g if 2nd_lat_digit is 14
    first = 1
    second = 4

    / sum2 is the sum of digits multiplied by 2
    sum2 += first + second  // add 1st & 2nd and then add to sum2
}
while (credit > 0)

/ final checksum total
checksum_total = sum1 + sum2


TODO:
Prompt user for input (credit card number)
Calculate checksum (to check if number is valid)
Check for length & starting digits (to figure out which card this number belongs to)
Print `AMEX`, `MASTERCARD`, `VISA` or `INVALID`

 */

#include <stdio.h>
#include <math.h>

long long get_long_long(const char *message);
int checksum(long long credit);
int length(long long credit);
int get_first_two_digits(long long credit);

int main(void)
{
    long long credit = get_long_long("Enter credit: ");

    // Calculate checksum
    int checksum_valid = checksum(credit);
    if (!checksum_valid)
    {
        // Invalid: checksum faild
        printf("INVALID\n");
        return 0;
    }

    // find credit length
    int credit_len = length(credit);
    // Get first two digits
    int first_digits = get_first_two_digits(credit);

    // Check which card this number belongs to?
    if (credit_len == 15 && (first_digits == 34 || first_digits == 37))
    {
        // american express :> 34 or 37 (15 digits)
        printf("AMERICAN EXPRESS\n");
    }
    else if (credit_len == 16 && (first_digits / 10 == 5 && (first_digits % 10 > 0 || first_digits % 10 < 6)))
    {
        // Mastercard :> 51 - 55 (16 digits)
        printf("MASTERCARD\n");
    }
    else if ((credit_len == 13 || credit_len == 16) && (first_digits / 10 == 4 && first_digits % 10 >= 0))
    {
        // VISA :> 4 (13 or 16 digits)
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

long long get_long_long(const char *message)
{
    // Supports upto 19 digits
    long long userinput;
    printf(message);
    scanf("%lld", &userinput);
    return userinput;
}

int checksum(long long credit)
{
    int last_digit, second_last_digit;
    int sum1 = 0;      // holds sum of (not-multiplied) digits
    int sum2 = 0;      // holds sum of (multiplied) digits
    int first, second; // will hold splitted values (temporarily)

    do
    {
        // store last-dig.
        last_digit = credit % 10;
        // remove last-dig from credit
        credit = credit / 10;
        // add to sum1
        sum1 += last_digit;

        // store 2nd_last_digit
        second_last_digit = credit % 10;
        credit = credit / 10;
        // multiply by 2
        second_last_digit *= 2;

        // Split if (2nd_l_dig) is  two digits
        first = second_last_digit % 10;  // store last digit
        second = second_last_digit / 10; // remove last digit (remaining stored)

        // Add them up and store in sum2 (sum of multiplied digits)
        sum2 += first + second;

    } while (credit > 0);

    int total = sum1 + sum2;
    // if last digit is 0, valid
    return (total % 10 == 0) ? 1 : 0;
}

int length(long long credit)
{
    // Find length of 'credit'
    int length = (int)log10(credit) + 1;
    return length;
}

int get_first_two_digits(long long credit)
{
    // Get the first two digits of credit
    do
    {
        // remove last digit
        credit = credit / 10;
    } while (credit > 100); // two digits will always be less than 100

    return (int)credit;
}