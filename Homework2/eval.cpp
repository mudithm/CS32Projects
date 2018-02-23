#include "Map.h"
#include <cctype>
#include <string>
#include <stack>
#include <iostream>
#include <cassert>

using namespace std;

// function to check the validity of strings
bool isValid(string infix);

int evaluate(string infix, const Map& values, string& postfix, int& result){
    // check if infix has valid syntax
    if (! isValid(infix))
        return 1;

    bool return2 = false;
        
    string output = "";
    stack<char> operators;

    int size = infix.size();
    int val;

    // convert from infix to postfix
    for (int i = 0; i < size; i++){
        char t = infix[i];
       //cerr << t << endl;
        switch (t){
            case '(':
                operators.push(t);
                break;
            case ')':
                while(operators.top() != '('){
                    output += operators.top();
                    operators.pop();
                }
                operators.pop();
                break;
            case '+':
            case '-':
                while( ! operators.empty() && operators.top() != '(' ){
                    output += operators.top();
                    operators.pop();
                }
                operators.push(t);
                break;
            case '*':
            case '/':
                while( ! operators.empty() && operators.top() != '(' && operators.top() != '+' 
                        && operators.top() != '-'){
                    output += operators.top();
                    operators.pop();
                }
                operators.push(t);
                break;
            default:
                if (t == ' '){
                    //cerr << "we out here" << endl;
                    break;
                }
                // if operand not in map
                if (! values.get(t, val))
                    return2 = true;

                output += t;
                break;
        }



    }
    // appends remaining operators to postfix
    while ( ! operators.empty()){
        output += operators.top();
        operators.pop();
    }

    postfix = output;

    if (return2)
        return 2;
    // evaluate postfix
    stack<int> operands;
    char curr;
    int c;

    int operand1;
    int operand2;

    size = postfix.size();
    for (int i = 0; i < size; i++){
        curr = postfix[i];    
        if (values.get(curr, c))
            operands.push(c);
        else{
            operand2 = operands.top();
            operands.pop();
            operand1 = operands.top();
            operands.pop();
            switch (curr){
                case '+':
                    operands.push(operand1 + operand2);
                    break;
                case '-':
                    operands.push(operand1 - operand2);
                    break;
                case '*':
                    operands.push(operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0)
                        return 3;
                    operands.push(operand1 / operand2);
                    break;
                default:
                    cerr << "Something went very wrong." << endl;
                    break;

            }
                     
        }
    }
    
    result = operands.top();
    operands.pop();



    return 0;

}

bool isValid(string infix){
    if (infix == "")
        return false;
    
    string temp = "";
    
    // removes spaces
    for (int m = 0; m < infix.size(); m++)
       if (infix[m] != ' ')
          temp += infix[m] ;
    
    //checks proper parenthesis balance
    stack<char> paren;
    for (int j = 0; j < temp.size(); j++){
        if (temp[j] == '(') 
            paren.push('(');
        if (temp[j] == ')' && ! paren.empty()) 
            paren.pop();  
        else if (temp[j] == ')' && paren.empty()){
            //cerr << "Got herer" << endl;
           return false; 
        }
    }
    if (! paren.empty()){
        cerr << "Unbalanced Parenthesis" << endl;
        return false;
    }

    // checks for valid operators/operands
    for (int i = 0; i < temp.size(); i++){
        switch (temp[i]){
            //Operators
            case '+':
            case '-':
            case '/':
            case '*':
              //cerr << "operators" << endl;
                if (i == 0)
                    return false;
                if (temp[i-1] != '(' && temp[i-1] != ')' && !islower(temp[i - 1]))
                    return false;
                if (i == temp.size() - 1)
                    return false;
                if (temp [i+1] != ')' && temp [i+1] != '(' && !islower(temp[i+1]))
                    return false;
                break;
            // Open paren
            case '(':
                //cerr << "open paren" << endl;
                if (i == temp.size() - 1)
                    return false;
                if (temp[i+1] != '(' && ! islower(temp[i+1]))
                    return false;
                if (i != 0)
                    if (islower(temp[i - 1]))
                       return false; 
                break;
            // close paren
            case ')':
                //cerr << "close paren" << endl;
                if (i == 0)
                    return false;
                //cerr << "   got here" << endl;
                if (temp[i-1] != ')' && ! islower(temp[i-1]))
                    return false;
                if (i != temp.size() - 1)
                    if (islower(temp[i + 1]))
                        return false;
                break;
            // letters    
            default:
                //cerr << "default case" << endl;
                if (! islower(temp[i]))
                       return false;
                if (i == 0){
                    if (islower(temp[i+1]))
                        return false;
                }else if (i == temp.size() - 1){
                    if (islower(temp[i-1]))
                        return false;
                }else{
                    if (islower(temp[i-1]))
                        return false;
                    if (islower(temp[i+1]))
                        return false;
                }

                break;
        }
    }

    return true;
}


int main(){
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);

    string meme = "iii";
    while (meme != "s"){
       getline(cin, meme);
        cerr << isValid(meme) << endl;
    }
    
    cerr << "----------------------" << endl;       
    string output;
    int result = 999999;
    cerr << "Function returns " << evaluate("a+eEEE" , m, output, result) << endl;
    cerr << "Postfix: " << output << endl;
    cerr << "Result: " << result << endl;
    cerr << "---" << endl;
    
    cerr << "Function returns " << evaluate("" , m, output, result) << endl;
    cerr << "Postfix: " << output << endl;
    cerr << "Result: " << result << endl;
    cerr << "---" << endl;
    
    cerr << "Function returns " << evaluate("abcdefgh++(())" , m, output, result) << endl;
    cerr << "Postfix: " << output << endl;
    cerr << "Result: " << result << endl;
    cerr << "---" << endl;
    
    cerr << "Function returns " << evaluate("a * e + i / o" , m, output, result) << endl;
    cerr << "Postfix: " << output << endl;
    cerr << "Result: " << result << endl;

    meme = "iii";
    while (meme != "s"){
         getline(cin, meme);
         cerr << "Function returns " << evaluate(meme , m, output, result) << endl;
         cerr << "Postfix: " << output << endl;
         cerr << "Result: " << result << endl;
         cerr << "" << endl;
    }

    cerr << "-------------------------" << endl;

    string pf;
            int answer;
            assert(evaluate("a+ e", m, pf, answer) == 0  &&
                                    pf == "ae+"  &&  answer == -6);
            answer = 999;
            assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
              // unary operators not allowed:
            assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
            
            assert(evaluate("a*b", m, pf, answer) == 2  &&
                                    pf == "ab*"  &&  answer == 999);
            assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
                                    pf == "yoau-*+"  &&  answer == -1);
            answer = 999;
            assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                                    pf == "oyy-/"  &&  answer == 999);
            assert(evaluate(" a  ", m, pf, answer) == 0  &&
                                    pf == "a"  &&  answer == 3);
            assert(evaluate("((a))", m, pf, answer) == 0  &&
                                    pf == "a"  &&  answer == 3);
            cout << "Passed all tests" << endl;


}
