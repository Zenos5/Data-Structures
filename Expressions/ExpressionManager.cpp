#include <sstream>
#include <cctype>

#include "ExpressionManager.h" 

using std::string;
using std::istringstream;
/*
* Checks whether an expression is balanced on its parentheses
*
* - The given expression will have a space between every number or operator
*
* @return true if expression is balanced
* @return false otherwise
*/
// The set of opening parentheses.
const string OPEN = "([{";

// The corresponding set of closing parentheses.
const string CLOSE = ")]}";

bool is_open(char ch) {
    return OPEN.find(ch) != string::npos;
}

bool is_close(char ch) {
    return CLOSE.find(ch) != string::npos;
}

bool ExpressionManager::isBalanced(string expression)
{
    cout << "In isBalanced expression " << expression << endl;

    stack<char> s;
    bool balanced = true;
    for (string::const_iterator iter = expression.begin();
        balanced && (iter != expression.end());
        iter++) {
        char next_ch = *iter;
        if (is_open(next_ch)) {
            s.push(next_ch);
        }
        else if (is_close(next_ch)) {
            if (s.empty()) {
                balanced = false;
            }
            else {
                char top_ch = s.top();
                s.pop();
                balanced =
                    OPEN.find(top_ch) == CLOSE.find(next_ch);
            }
        }
    }
    return balanced && s.empty();
}

/**
* Converts a postfix expression into an infix expression
* and returns the infix expression.
*
* - The given postfix expression will have a space between every number or operator.
* - The returned infix expression must have a space between every number or operator.
* - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if postfixExpression is not a valid postfix expression.
* otherwise, return the correct infix expression as a string.
*/
string ExpressionManager::postfixToInfix(string postfixExpression)
{
    cout << "In postfixToInfix" << endl;

    string infixExpression = "";
    stack<string> operands;

    // Be sure the stack is empty
    while (!operands.empty())
        operands.pop();

    // Process each token
    istringstream elements(postfixExpression);
    char next_char;
    while (elements >> next_char) {
        if (isdigit(next_char)) {
            elements.putback(next_char);
            string value;
            elements >> value;
            for (int i = 0; i < value.size(); i++)
            {
                if (!isdigit(value[i]))
                {
                    return("invalid");
                }
            }
            operands.push(value);
        }
        else if (is_operator(next_char)) {
            if (operands.size() < 2)
            {
                return("invalid");
            }
            else
            {
                string operation, operand1, operand2;
                operand2 = operands.top();
                operands.pop();
                operand1 = operands.top();
                operands.pop();
                operation = "( " + operand1 + " " + next_char + " " + operand2 + " )";
                operands.push(operation);
            }   
            if (operands.size() == 1)
            {
                infixExpression = operands.top();
            }
            else if (operands.size() > 1)
            {
                cout << "More values in the stack" << endl;
                //return "invalid";
            }
        }
        else {
            cout << "not digit or operand";
            return("invalid");
        }
    }
    if (infixExpression == "")
    {
        return("invalid");
    }
    return infixExpression;
}

/*
* Evaluates a postfix expression returns the result as a string
*
* - The given postfix expression will have a space between every number or operator.
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if postfixExpression is not a valid postfix Expression
* otherwise, return the correct evaluation as a string
*/
string ExpressionManager::postfixEvaluate(string postfixExpression)
{
    cout << "In postfixEvaluate " << postfixExpression << endl;
    // Be sure the stack is empty
    while (!operand_stack.empty())
        operand_stack.pop();

    // Process each token
    istringstream tokens(postfixExpression);
    char next_char;
    while (tokens >> next_char) {
        if (isdigit(next_char)) {
            tokens.putback(next_char);
            int value;
            tokens >> value;
            operand_stack.push(value);
        }
        else if (is_operator(next_char)) {
            int result;
            try {
                result = eval_op(next_char);
            }
            catch (int which) {
                cout << "not enough operands";
                return("invalid");
            }
            operand_stack.push(result);
        }
        else {
            cout << "not digit or operand";
            return("invalid");
        }
    }
    if (!operand_stack.empty()) {
        string answer = to_string(operand_stack.top());
        operand_stack.pop();
        if (operand_stack.empty()) {
            return answer;
        }
        else {
            cout << "at end stack not empty";
            return("invalid");
        }
    }
    else {
        cout << "at end answer not on stack";
        return("invalid");
    }
}

const std::string ExpressionManager::OPERATORS = "+-*/%()";
const int ExpressionManager::PRECEDENCE[] = {1, 1, 2, 2, 2, -1, -1};
/** Evaluates the current operator.
    This function pops the two operands off the operand
    stack and applies the operator.
    @param op A character representing the operator
    @throws Syntax_Error if top is attempted on an empty stack
*/
int ExpressionManager::eval_op(char op) {
    if (operand_stack.empty())
        throw 1;
    int rhs = operand_stack.top();
    operand_stack.pop();
    if (operand_stack.empty())
        throw 2;
    int lhs = operand_stack.top();
    operand_stack.pop();
    if (rhs == 0 && op == '/')
    {
        cout << "Dividing by Zero" << endl;
        throw 3;
    }
    int result = 0;
    switch (op) {
    case '+': result = lhs + rhs;
        break;
    case '-': result = lhs - rhs;
        break;
    case '*': result = lhs * rhs;
        break;
    case '/': result = lhs / rhs;
        break;
    case '%': result = lhs % rhs;
        break;
    }
    return result;
}



/*
* Converts an infix expression into a postfix expression
* and returns the postfix expression
*
* - The given infix expression will have a space between every number or operator.
* - The returned postfix expression must have a space between every number or operator.
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if infixExpression is not a valid infix expression.
* otherwise, return the correct postfix expression as a string.
*/
string ExpressionManager::infixToPostfix(string infixExpression)
{
    postfixExpression = "";
    while (!operator_stack.empty())
        operator_stack.pop();

    if (!isBalanced(infixExpression))
    {
        return("invalid");
    }

    // Process each token
    istringstream tokens(infixExpression);
    string next_token;
    while (tokens >> next_token)
    {
        if (isdigit(next_token[0]))
        {
            for (int i = 0; i < next_token.size(); i++)
            {
                if (!isdigit(next_token[i]))
                {
                    return("invalid");
                }
            }
            postfixExpression += next_token;
            postfixExpression += " ";
        }
        else if (is_operator(next_token[0]))
        {        
            bool no_error = process_operator(next_token[0]);
            if (!no_error)
            {
                return("invalid");
            }
        }
        else
        {
            cout << "Invalid Character" << endl;
            return "invalid";
        }
    }

    //pop any remaining operators and append them to expression
    while (!operator_stack.empty())
    {
        char op = operator_stack.top();
        operator_stack.pop();
        if (op == '(')
        {
            cout << "Unmatched Parenthesis" << endl;
            return "invalid";
        }
        postfixExpression += op;
        postfixExpression += " ";
    }
    if (postfixEvaluate(postfixExpression) == "invalid")
    {
        return("invalid");
    }
    return postfixExpression;
}

bool ExpressionManager::process_operator(char op)
{
    if (operator_stack.empty() || (op == '('))
    {
        if (op == ')')
        {
            cout << "Unmatched Closed Parenthesis" << endl;
            return false;
        }
        operator_stack.push(op);
    }
    else
    {
        if (precedence(op) > precedence(operator_stack.top()))
        {
            operator_stack.push(op);
        }
        else
        {
            while (!operator_stack.empty() 
                && (operator_stack.top() != '(')
                && (precedence(op) <= precedence(operator_stack.top())))
            {
                postfixExpression += operator_stack.top();
                postfixExpression += " ";
                operator_stack.pop();
            }
            if (op == ')')
            {
                if (!operator_stack.empty()
                    && (operator_stack.top() == '('))
                {
                    operator_stack.pop();
                }
                else
                {
                    cout << "Unmatched Parenthesis" << endl;
                    return false;
                }
            }
            else
            {
                operator_stack.push(op);
            }
        }
    }
    return true;
}