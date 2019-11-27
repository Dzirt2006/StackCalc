//
// Created by dzirt on 11/26/2019.
//

#include "Calc.h"


//fill up the stack
void Calc::FillUpStack(char *StringPtr, const int *DIMM, stack<float> *Numbers, stack<char> *Operattors) {
    cout << " Enter your expression:(if u want to enter decimal-type it  without point ex. 0.2-> 02) :  ";
    cin.getline(StringPtr, *DIMM);
    string x = "";
    for (int i = 0; i < strlen(StringPtr); i++) {
        if (isdigit(*(StringPtr + i))) {
            x += *(StringPtr + i);
            if (!isdigit(*(StringPtr + (i + 1)))) {//check next element of CString array for writing the numbers  greater than 9 -two digits numbers
                Numbers->push(stoi(x));
                x = "";
            } else continue;
        } else {
            Operattors->push(*(StringPtr + i));
        }
    }
}

void Calc::Calculation(stack<float> *num, stack<char> *op) {
    float n1, n2;
    stack<char> opTemp;
    stack<float> numTemp;
    char o;
    do {
        //taking data from 2 stacks
        n2 = NumPop(num);
        o = OpPop(op);//operator
        n1 = NumPop(num);
        if (o == '/' || o == '*') { //if operator is * or / make multiply or division
            cout << n1 << " " << o << " " << n2 << " = ";
            n2 = HightOp(n1, n2, o);//call multiply or division method
            cout << n2 << endl;
            if (num->empty()) { //end of program if number stack is empty and output result
                cout << "Result is: " << n2;
            } else {
                num->push(n2);//push result to num stack if not end
            }
        } else if (!op->empty() &&
                   (op->top() == '*' || op->top() == '/')) {// "!op->empty()" check for final iteration case
            cout << " make this first " << endl;
            //in this case we already have operator and numbers in variable and we have to move them temporary to another stack
            cout << "let put operator '" << o << "' and second number '" << n2 << "' to the temporary stacks" << endl;
            opTemp.push(o);
            numTemp.push(n2);
            //poping new data from stack
            n2 = n1;
            n1 = NumPop(num);
            o = OpPop(op);
            cout << "now calculate the expression " << n1 << " " << o << " " << n2 << " = ";
            n2 = HightOp(n1, n2, o);
            cout << n2 << endl;
            if (op->top() == '-') {
                cout << " as well as operator before '" << n1
                     << "' is '-' lets convert result to negative and change operator before to '+'" << endl;
                n2 *= -1;
                op->pop();
                op->push('+');
            } else continue;
            //return value from temporary stack
            n1 = NumPop(&numTemp);
            o = OpPop(&opTemp);
            //push back to original stack
            num->push(n2);
            op->push(o);
            num->push(n1);
        } else { // if operator + or - lets do summation or substitution
            cout << n1 << " " << o << " " << n2 << " = ";
            n2 = LowOp(n1, n2, o);
            cout << n2 << endl;
            if (num->empty()) {
                cout << "Result is: " << n2;
            } else
                num->push(n2);
        }
    } while (!num->empty());
}

char Calc::OpPop(stack<char> *o) {
    char from_op_stack;
    from_op_stack = (*o).top();
    (*o).pop();
    return from_op_stack;
}

float Calc::NumPop(stack<float> *n) {
    float from_num_stack;
    from_num_stack = (*n).top();
    (*n).pop();
    return from_num_stack;
}


float Calc::HightOp(float a, float b, char c) {
    float res = 0;
    switch (c) {
        case '*':
            res = a * b;
            break;
        case '/':
            res = a / b;
            break;
    }
    return res;
}


float Calc::LowOp(float a, float b, char c) {
    float res = 0;
    switch (c) {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
    }

    return res;
}
