#include "ExpressionManagerInterface.h"
class ExpressionManager : public ExpressionManagerInterface
{
public:
	ExpressionManager() {}
	~ExpressionManager() {}

	/*
	* Checks whether an expression is balanced on its parentheses
	*
	* - The given expression will have a space between every number or operator
	*
	* @return true if expression is balanced
	* @return false otherwise
	*/

	bool isBalanced(string expression);

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
	string postfixToInfix(string postfixExpression);

	/*
	* Evaluates a postfix expression returns the result as a string
	*
	* - The given postfix expression will have a space between every number or operator.
	* - Check lab requirements for what will be considered invalid.
	*
	* return the string "invalid" if postfixExpression is not a valid postfix Expression
	* otherwise, return the correct evaluation as a string
	*/
	string postfixEvaluate(string postfixExpression);

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
	string infixToPostfix(string infixExpression);
private:
	/** Evaluates the current operator.
		This function pops the two operands off the operand
		stack and applies the operator.
		@param op A character representing the operator
		@throws Syntax_Error if top is attempted on an empty stack
	*/
	int eval_op(char op);

	/** Determines whether a character is an operator.
		@param ch The character to be tested
		@return true if the character is an operator
	*/
	bool is_operator(char ch) const 
	{
		return OPERATORS.find(ch) != std::string::npos;
	}

	bool process_operator(char ch);

	int precedence(char op) const
	{
		return PRECEDENCE[OPERATORS.find(op)];
	}

	// Data fields
	static const std::string OPERATORS;
	static const int PRECEDENCE[];
	std::stack<int> operand_stack;
	std::stack<char> operator_stack;
	std::string postfixExpression;
};