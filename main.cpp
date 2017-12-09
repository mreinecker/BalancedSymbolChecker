#include <iostream>
#include <stack>

// Counter to hold data for tracking balance of symbols
struct Counter {
	int parenthesis = 0;
	int curly = 0;
	int brackets = 0;
	int slashstar = 0;
	// stack noMatch holds any non-paired chars
	std::stack<char> noMatch;

	bool symbolChecker(std::string checkString) {
		std::stack<char> symbols; // stores the balanced char symbols

		for (int i = 0; i < checkString.length(); i++) {
			// find a symbol and add it to the stack if found
			if (checkString[i] == '(' || checkString[i] == '{' || checkString[i] == '[') {
				symbols.push(checkString[i]);
			} else if (checkString[i] == '/' && checkString[i + 1] == '*'){
				symbols.push(checkString[i]);
				symbols.push(checkString[i + 1]);
			} else if ((symbols.top() == '(' && checkString[i] == ')') ||
			           (symbols.top() == '{' && checkString[i] == '}')
			           || (symbols.top() == '[' && checkString[i] == ']')) {
				if (symbols.top() == '(' && checkString[i] == ')') {
					this->parenthesis++;
				} else if (symbols.top() == '{' && checkString[i] == '}') {
					this->curly++;
				} else if (symbols.top() == '[' && checkString[i] == ']') {
					this->brackets++;
				}
				symbols.pop();
			} else if (symbols.top() == '*' && checkString[i - 1] == '*' && checkString[i] == '/'){
				symbols.pop(); // removes the *
				symbols.pop(); // removes the /
				this->slashstar++; // increment counter
			} else {
				if (checkString[i] != '*') {
					this->noMatch.push(
							checkString[i]); // adds the unbalanced symbol to a separate tracking container for viewing the errors
				}
			}
		}

		return this->noMatch.empty();
	}
};


int main() {
	Counter tracker;
	std::string expression;
	std::cout << "\nEnter a string of symbols to check for balance: " << std::endl;
	 // used to store expression input by user
	std::cin >> expression; // ingest expression
	std::cout << "\n" << expression << std::endl;
	// send expression to function to check for balanced symbols
	if (!tracker.symbolChecker(expression)){
		std::cout << "\nThe expression was not balanced. We found the following symbols with no pair: \n";
		for (int i = 0; i < tracker.noMatch.size(); ++i) {
			std::cout << "\n" << tracker.noMatch.top()
			          << "\n" << std::endl;
			tracker.noMatch.pop();
		}
	} else {
		std::cout << "\nThe expression's symbols were balanced."
		          << "\nWe found " << tracker.parenthesis << " parenthesis pairs"
		          << "\nand " << tracker.brackets << " bracket pairs"
		          << "\nand " << tracker.curly << " curly brace pairs"
		          << "\nand " << tracker.slashstar << " sets of comment markers" << std::endl;
	}

	return 0;
}
