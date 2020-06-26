#include "ExpressionManagerInterface.h"
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

class ExpressionManager : public ExpressionManagerInterface {
private:
	string expression = "";
	vector<string> inFix;
	vector<string> postFix;
	vector<string> preFix;

public:
	ExpressionManager() { }
	ExpressionManager(string exp) :
		expression(exp) { }
	~ExpressionManager() { }

	void setExpression(string fromMain) {
		expression = fromMain;
	}

	int getPriority(char C) {
		if (C == '-' || C == '+') {
			return 1;
		}
		else if (C == '*' || C == '/' || C == '%') {
			return 2;
		}
		else{
			return 0;
		}
	}

	bool isOperator(char C) {
		if (C == '%' || C == '/' || C == '*' || C == '+' || C == '-'){
			return true;
		}
		else {
			return false;
		}
	}
	bool isOperand(char C) {
		if (C == '1'|| C == '2'|| C == '3'|| C == '4'|| C == '5'|| C == '6'|| C == '7'|| C == '8'|| C == '9'|| C == '0') {
			return true;
		}
		else {
			return false;
		}
	}
	bool isBracket(char C) {
		if (C == '(' || C == ')' || C == '{' || C == '}' || C == '[' || C == ']') {
			return true;
		}
		else {
			return false;
		}
	}
	bool areParanthesisBalanced(string expr){
		stack<char> s;
		char x;
		// Traversing the Expression 
		for (int i = 0; i < expr.length(); i++)
		{
			if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')
			{
				// Push the element in the stack 
				s.push(expr[i]);
				continue;
			}

			// IF current current character is not opening 
			// bracket, then it must be closing. So stack 
			// cannot be empty at this point. 
			if (s.empty())
				return true;

			switch (expr[i]){
			case ')':

				// Store the top element in a 
				x = s.top();
				s.pop();
				if (x == '{' || x == '[')
					return false;
				break;

			case '}':

				// Store the top element in b 
				x = s.top();
				s.pop();
				if (x == '(' || x == '[')
					return false;
				break;

			case ']':

				// Store the top element in c 
				x = s.top();
				s.pop();
				if (x == '(' || x == '{')
					return false;
				break;
			}

		}

		// Check Empty Stack 
		return true;
	}


	string infix(void) {
		int operands1 = 0;
		int operators1 = 0;
		bool illegal;

		//First we double check that all the ({[ are being closed
		if (areParanthesisBalanced(expression) == false) {
			return "Unbalanced";
		}
		
		for (int i = 0; i < expression.size(); i++) {
			if (expression.at(i) == ' ') {
				continue;
			}
			//Second we check if all the items in the vector are legal terms
			if (isOperator(expression.at(i)) == false && isOperand(expression.at(i)) == false && isBracket(expression.at(i)) == false) {
				return "Illegal Operator";
			}
			// We check that we have no adjacent operators
			if (isOperator(expression.at(i)) == true) {
				if (i == 0) {
					return "Missing Operand";
				}
				if (i >= expression.size()) {
					return "Missing Operand";
				}
				if (i+1 <= expression.size()) {
					return "Missing Operand";
				}
			}
		}
		for (int i = 0; i < expression.size(); i++) {
			if (expression.at(i == ' ')) {
				continue;
			}
			if (isdigit(expression.at(i)) == true) {
				operands1++;
			}
			else if (isOperator(expression.at(i)) == true) {
				operators1++;
			}
		}
		if (operators1 == operands1 + 1) {
			return "Missing operator";
		}
		return expression;
	}

	string postfix(void) {
		stack<char> st;
		st.push('N');
		int l = expression.length();
		string ns;
		for (int i = 0; i < l; i++) {
			if (expression.at(i) == ' ') {
				ns += ' ';
			}
			if (expression.at(i) == '{' || expression.at(i) == '[') {
				expression.at(i) = '(';
			}
			if (expression.at(i) == '}' || expression.at(i) == ']') {
				expression.at(i) = ')';
			}
			// If the scanned character is an operand, add it to output string. 
			if (isOperand(expression.at(i)) == true) {
				ns += expression.at(i);
			}
			// If the scanned character is an ‘(‘, push it to the stack. 
			else if (expression.at(i) == '(') {
				st.push(expression.at(i));
			}
			// If the scanned character is an ‘)’, pop and to output string from the stack 
			// until an ‘(‘ is encountered. 
			else if (expression.at(i) == ')') {
				while (st.top() != 'N' && st.top() != '(') {
					char c = st.top();
					st.pop();
					ns += c;
				}
				if (st.top() == '(') {
					char c = st.top();
					st.pop();
				}
			}
			//If an operator is scanned 
			else if (isOperator(expression.at(i)) == true) {
				while (st.top() != 'N' && getPriority(expression.at(i)) <= getPriority(st.top())) {
					char c = st.top();
					st.pop();
					ns += c;
				}
				st.push(expression.at(i));
				
			}
		}
		//Pop all the remaining elements from the stack 
		while (st.top() != 'N'){
			char c = st.top();
			st.pop();
			ns += c;
		}
		return ns;

	}
	string prefix() {
		/* Reverse String
		 * Replace ( with ) and vice versa
		 * Get Postfix
		 * Reverse Postfix  *  */
		int l = expression.size();

		// Reverse infix 
		reverse(expression.begin(), expression.end());

		// Replace ( with ) and vice versa 
		for (int i = 0; i < l; i++) {

			if (expression.at(i) == '(') {
				expression.at(i) = ')';
				i++;
			}
			else if (expression.at(i) == ')') {
				expression.at(i) = '(';
				i++;
			}
		}

		string prefix = postfix();

		// Reverse postfix 
		reverse(prefix.begin(), prefix.end());

		return prefix;
	}

	// Function to perform arithmetic operations. 
	int applyOp(int a, int b, char op) {
		switch (op) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
		case '%': return a % b;
		}
	}

	// Function that returns value of 
	// expression after evaluation. 
	int value() {
		string tokens = expression;
		int i;

		// stack to store integer values. 
		stack <int> values;

		// stack to store operators. 
		stack <char> ops;

		for (i = 0; i < tokens.length(); i++) {

			// Current token is a whitespace, 
			// skip it. 
			if (tokens[i] == ' ')
				continue;
			//We then switch all the brackets to one kind to simplify the code

			if (tokens[i] == '{' || tokens[i] == '[') {
				tokens[i] = '(';
			}
			if (tokens[i] == '}' || tokens[i] == ']') {
				tokens[i] = ')';
			}

			// Current token is an opening  
			// brace, push it to 'ops' 
			if (tokens[i] == '(') {
				ops.push(tokens[i]);
			}

			// Current token is a number, push  
			// it to stack for numbers. 
			else if (isdigit(tokens[i])) {
				int val = 0;
				// There may be more than one 
				// digits in number. 
				while (i < tokens.length() && isdigit(tokens[i])){
					val = (val * 10) + (tokens[i] - '0');
					i++;
				}
				values.push(val);
			}
			// Closing brace encountered, solve  
			// entire brace. 
			else if (tokens[i] == ')'){
				while (!ops.empty() && ops.top() != '('){
					int val2 = values.top();
					values.pop();
					int val1 = values.top();
					values.pop();
					char op = ops.top();
					ops.pop();
					values.push(applyOp(val1, val2, op));
				}

				// pop opening brace. 
				if (!ops.empty())
					ops.pop();
			}

			// Current token is an operator. 
			else {
				// While top of 'ops' has same or greater  
				// precedence to current token, which 
				// is an operator. Apply operator on top  
				// of 'ops' to top two elements in values stack. 
				while (!ops.empty() && getPriority(ops.top())>= getPriority(tokens[i])) {
					int val2 = values.top();
					values.pop();

					int val1 = values.top();
					values.pop();

					char op = ops.top();
					ops.pop();

					values.push(applyOp(val1, val2, op));
				}
				// Push current token to 'ops'. 
				ops.push(tokens[i]);
			}
		}

		// Entire expression has been parsed at this 
		// point, apply remaining ops to remaining 
		// values. 

		while (!ops.empty()) {
			int val2 = values.top();
			values.pop();

			int val1 = values.top();
			values.pop();

			char op = ops.top();
			ops.pop();

			values.push(applyOp(val1, val2, op));
		}

		// Top of 'values' contains result, return it. 
		return values.top();
	}
	string toString(void) const {
		return expression;
	}
};

