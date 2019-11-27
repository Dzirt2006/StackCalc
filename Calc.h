//
// Created by dzirt on 11/26/2019.
//

#ifndef UNTITLED3_CALC_H
#define UNTITLED3_CALC_H

#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Calc {

    //constructor
public:
    Calc() {
        FillUpStack(ptr, &SIZE, &Numers, &Opers);
        Calculation(&Numers, &Opers);
    }


private:

    //prototypes
    float HightOp(float, float, char);

    float LowOp(float, float, char);

    void FillUpStack(char *, const int *, stack<float> *, stack<char> *);

    void Calculation(stack<float> *, stack<char> *);

    char OpPop(stack<char> *);

    float NumPop(stack<float> *);

    //list of variables
    const int SIZE = 99;
    char *ptr = new char[SIZE];
    stack<float> Numers;
    stack<char> Opers;
};


#endif //UNTITLED3_CALC_H
