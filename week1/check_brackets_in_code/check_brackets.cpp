#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    int output = -1;

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket entry(next, position + 1);
            opening_brackets_stack.push(entry);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.empty()) {
            	output = ++position;
            	break;
            }
            else if (opening_brackets_stack.top().Matchc(next)) {
            	opening_brackets_stack.pop();
            } else {
            	output = ++position;
            	break;
            }
        }
    }

    if (output >= 0) {
    	std::cout << output; 
    } else if (!opening_brackets_stack.empty()) {
    	std::cout << opening_brackets_stack.top().position;
    } else {
    	std::cout << "Success";
    }

    // Printing answer, write your code here

    return 0;
}
