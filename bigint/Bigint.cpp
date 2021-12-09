//
// Created by Will on 20-Sep-21.
//

#include "Bigint.h"
#include <iostream>
#include <utility>

using namespace std;

istream &operator>>(istream &in, Bigint &n) {
    in >> n.num;

    //Resets the digit array when a new n is entered by setting them all to 0 again.
    for (int i = 0; i < 256; i++){
        n.digit[i] = 0;
    }

    //Converts the string from the input.txt and converts each character into an integer digit using ASCII encoding
    //hence the subtraction of the '0' character. It also  aligns the digits on the array such that the rightmost digits
    //start at index 1 to make it easier to make the arithmetic operations, especially multiplication since if it
    //started at 0, it would make a calculation within an index and get the value of -1 which would crash the program.
    int numberOfDigits = n.num.length();
    for (int i = numberOfDigits-1, j = 1; i >= 0; i--){
        n.digit[j] = n.num[i] - '0';
        j++;
    }

    return in;
}

ostream &operator<<(ostream &out, const Bigint &n) {
    out << n.num;

    return out;
}


Bigint operator+(const Bigint &n1, const Bigint &n2) {
    //A new Bigint is made so that it is able to return the result using the output operator. Uses the values of the n1
    //class to make writing code less tedious, such that there is no need to local arrays to store the resulting values.
    Bigint result(n1);

    //Adds each digit in the array from rightmost to leftmost so that it can deal better with if a result digit is more
    //than 10. Such that if it were more than 10, it subtracts 10 from the element then adds one onto the next, then
    //that one is added onto the next result digit. 10 is subtracted because I made the assumption that it is impossible
    //for single digit additions to exceed or equal to 20.
    for (int i = 1; i <= result.num.length(); i++){
        result.digit[i] += n2.digit[i];
        if (result.digit[i] >= 10){
            result.digit[i] -= 10;
            result.digit[i+1] += 1;
        }
    }

    bool zeroCheck = true;
    string finalResult;

    //Ensure that it only converts the relevant digits into an array of characters, by only doing so when the series of
    //zeros end and the first digit appears in the array from the loop
    for (int i = 255; i > 0; i--){
        if (result.digit[i] == 0 && zeroCheck){
            continue;
        } else {
            zeroCheck = false;
            finalResult += to_string(result.digit[i]);
        }
    }

    //Assigns the finalResult to the result class, so it can be displayed
    result.num = finalResult;
    return result;
}

Bigint operator-(const Bigint &n1, const Bigint &n2) {
    //A new Bigint is made so that it is able to return the result using the output operator. Uses the values of the n1
    //class to make writing code less tedious, such that there is no need to local arrays to store the resulting values.
    Bigint result(n1);

    bool zeroCheck = true;

    //Subtraction when done on paper is much easier when none of the results are negative numbers. So if the result is
    //going to be negative, then it will subtract from each digit then add ten to the next up until the digit at the
    //index i is positive. Then the subtraction of n2 digit from result digit will produce a positive value for easier
    //working. zeroCheck is implemented here to avoid subtractions and additions on the zeroes that appear before the
    //beginning of the number in the array.
    //Idea from: https://www.dummies.com/education/math/basic-math/how-to-borrow-when-subtracting/
    for (int i = 1; i < 256; i++){
        if (result.digit[i] < n2.digit[i]){
            for (int j = 255; j > i; j--){
                if (result.digit[j] == 0 && zeroCheck){
                    continue;
                } else {
                    zeroCheck = false;
                    result.digit[j] -= 1;
                    result.digit[j-1] += 10;
                }
            }
        }
        result.digit[i] -= n2.digit[i];
    }

    string finalResult;
    zeroCheck = true;

    //Ensure that it only converts the relevant digits into an array of characters, by only doing so when the series of
    //zeros end and the first digit appears in the array from the loop.
    for (int i = 255; i > 0; i--){
        if (result.digit[i] == 0 && zeroCheck){
            continue;
        } else {
            zeroCheck = false;
            finalResult += to_string(result.digit[i]);
        }
    }

    //For if the result of a subtraction is zero by seeing if the zeroCheck is still true, it displays the result of
    //zero.
    if (zeroCheck == true){
        finalResult = '0';
    }

    //Assigns the finalResult to the result class, so it can be displayed
    result.num = finalResult;
    return result;
}

Bigint operator*(const Bigint &n1, const Bigint &n2) {
    //A new Bigint is made so that it is able to return the result using the output operator. This does not use the
    //values of n1, because combining the results and n1 digits can output the wrong answer in multiplication.
    Bigint result;

    //This method multiplies each digit at the index of j + i - 1 because it ensures the placement of the digits within
    //the array are correct. It is very closely similar to how you would do multiplication by hand. It takes the n2
    //then multiplies it by each n1 digit at each j + 1 - 1 index. After each individual multiplication and assuming
    //that multiplication of single digit numbers cannot equal to or exceed 100, if the result
    //is bigger than 10, the carry is equal to the result divided by 10 and the tens digit is removed from result with
    //modulo 10. The carry is then carried over to the next index when j is increased by one. After j is equal to the
    //number of digits of n1, whatever is left of the carry is added to i + the number of n1 digits.
    //Idea from: https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication
    for (int i = 1; i <= n2.num.length(); i++){
        int carry = 0;
        for (int j = 1; j <= n1.num.length(); j++){
            //Remember that the loops start at 1 so the result index does not become less than zero
            result.digit[j + i - 1] += carry + n1.digit[j] * n2.digit[i];
            carry = result.digit[j + i - 1] / 10;
            result.digit[j + i - 1] = result.digit[j + i - 1] % 10;
        }
        result.digit[i + n1.num.length()] = carry;
    }

    string finalResult;
    bool zeroCheck = true;

    //Ensure that it only converts the relevant digits into an array of characters, by only doing so when the series of
    //zeros end and the first digit appears in the array from the loop.
    for (int i = 255; i > 0; i--){
        if (result.digit[i] == 0 && zeroCheck){
            continue;
        } else {
            zeroCheck = false;
            finalResult += to_string(result.digit[i]);
        }
    }

    //Assigns the finalResult to the result class, so it can be displayed
    result.num = finalResult;
    return result;
}

Bigint operator/(const Bigint &n1, const Bigint &n2) {
    //A new Bigint is made so that it is able to return the result using the output operator. This does not use the
    //values of n1, because combining the results and n1 digits can output the wrong answer in division.
    Bigint result;

    //The length is used as an index to loop the division. And for this assignment, it is assumed that n2 is
    //small enough to fit into an int data type.
    int numberOfDigits1 = n1.num.length();
    int number2 = stoi(n2.num);

    //Only takes out the first set of digits of n1 (stored in shortenedN1) until it is bigger than n2. Any left over
    //from the numberOfDigits1 becomes the amount of digits that will appear in the result (and the amount of iterations
    //of the next while loop).
    //Idea from: https://www.geeksforgeeks.org/divide-large-number-represented-string/?fbclid=IwAR36zplMsKUglI9ZYBbqWbk
    // zo9TvWIqnAk0y4INkLTWQ47QFifCrFYmLaC8
    int shortenedN1 = n1.digit[numberOfDigits1];
    while (shortenedN1 <= number2){
        shortenedN1 = shortenedN1 * 10 + (n1.digit[--numberOfDigits1]);
    }

    //With the numberOfDigits1 being used as the index, the shortened n1 is divided by the denominator (number2). Then
    //next digit in the array is the modulo of shortenedN1 and number2 multiplied by 10 plus the next digit of n1,
    //because to find the next digit it needs the extra digit from n1. This loops up until the numberOfDigits1 is zero.
    //Idea from: https://www.geeksforgeeks.org/divide-large-number-represented-string/?fbclid=IwAR36zplMsKUglI9ZYBbqWbk
    // zo9TvWIqnAk0y4INkLTWQ47QFifCrFYmLaC8
    while (numberOfDigits1 > 0){
        result.digit[numberOfDigits1] += (shortenedN1 / number2);
        shortenedN1 = (shortenedN1 % number2) * 10 + n1.digit[--numberOfDigits1];
    }

    string finalResult;
    bool zeroCheck = true;

    //Ensure that it only converts the relevant digits into an array of characters, by only doing so when the series of
    //zeros end and the first digit appears in the array from the loop.
    for (int i = 255; i > 0; i--){
        if (result.digit[i] == 0 && zeroCheck){
            continue;
        } else {
            zeroCheck = false;
            finalResult += to_string(result.digit[i]);
        }
    }

    //Assigns the finalResult to the result class, so it can be displayed
    result.num = finalResult;
    return result;
}





