#include <iostream>
#include <sstream>
#include <stack>
#include "Bigint.h"

using namespace std;

int main() {
    //A stack is made to store any values and retrieve them again when needed. A string is made for the line because the
    //entire line needs to be calculated for the accurate result, different from the previous method of just inputting
    //n1 then n2 then the operation (which would not work after the first three inputs on the line).
    stack<Bigint> stack;
    string line;

    //Gets the entire line, then when that line is finished it gets the next, until there are no lines left.
    while (getline(cin, line)){
        //Variables made for each expression within the line, whether it's a value or operation.
        stringstream expression(line);
        Bigint action;

        //Expression inputted into the action variable to be able to pushed into the stack as a Bigint if it is a value.
        //This while loop continues until every expression in the line is computed.
        while (expression >> action){
            //Checks the first character of the string, testing if it is a digit. If it is then it pushes it into the
            //stack. If it is not a digit, then it continues to the next if statements.
            if (isdigit(action.num[0])){
                stack.push(action);
            }

            //Checks for each type of operation that would occur. Assuming there are no typos in the input, one of these
            //would always work if the previous if statement was not true. For all of these, it returns the top value to
            //an initialisation of a new Bigint, then pops the value (deletes the top value). It does this again for the
            //second value that will be used for the calculation. Then it pushes the calculation to the stack, so that
            //result can be used again later on if needed. Otherwise, it will just return the top value (the result) if
            //there are no expressions/actions left on the line.
            else if (action.num == "+"){
                Bigint n2 = stack.top();
                stack.pop();
                Bigint n1 = stack.top();
                stack.pop();
                stack.push(n1 + n2);
            }
            else if (action.num == "-"){
                Bigint n2 = stack.top();
                stack.pop();
                Bigint n1 = stack.top();
                stack.pop();
                stack.push(n1 - n2);
            }
            else if (action.num == "*"){
                Bigint n2 = stack.top();
                stack.pop();
                Bigint n1 = stack.top();
                stack.pop();
                stack.push(n1 * n2);
            }
            else if (action.num == "/"){
                Bigint n2 = stack.top();
                stack.pop();
                Bigint n1 = stack.top();
                stack.pop();
                stack.push(n1 / n2);
            }
        }
        cout << stack.top() << endl;
    }

    /*Bigint n1, n2;
    char op;
    while (cin >> n1 >> n2 >> op) {
        switch (op) {
            case '+' :
                cout << n1 + n2 << endl;
                break;
            case '-' :
                cout << n1 - n2 << endl;
                break;
            case '*' :
                cout << n1 * n2 << endl;
                break;
            case '/' :
                cout << n1 / n2 << endl;
                break;
        }
    }*/
    return 0;

}
