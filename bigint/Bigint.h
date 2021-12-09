//
// Created by Will on 20-Sep-21.
//

#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#include <iostream>
#include <utility>

using namespace std;

class Bigint {
public:
    //The two variables where the string version of the number and the individual digits will be assigned to. digit is
    //initialised as zero for all 256 values to make it easier to add in values and delete the zeroes that come before
    //the start of the number.
    string num;
    int digit[256] = {0};

    //Probably redundant, but exists just in case, so it is 100% certain that num strings are being assigned to the
    //class properly.
    Bigint(string number = ""){
       num = number;
    }

    //Friend operators for the class to work properly.
    //The arithmetic operators are needed to work around completing the operations when values are too big it needs to
    //be calculated from the array of digits, as opposed to the entire integer.
    friend Bigint operator+ (const Bigint& n1, const Bigint& n2);
    friend Bigint operator- (const Bigint& n1, const Bigint& n2);
    friend Bigint operator* (const Bigint& n1, const Bigint& n2);
    friend Bigint operator/ (const Bigint& n1, const Bigint& n2);

    //Needed to divide up the string of a number into the array of int digits, and then simply outputs the string since
    //the conversion from array of int digits into a string is completed within the arithmetic operations.
    friend ostream& operator<< (ostream& out, const Bigint& n);
    friend istream& operator>> (istream& in, Bigint& n);
};


#endif //BIGINT_BIGINT_H
