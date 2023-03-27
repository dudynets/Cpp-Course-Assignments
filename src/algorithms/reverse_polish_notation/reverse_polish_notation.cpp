#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include <stack>
#include <cmath>
#include "doctest/doctest.h"

using namespace std;

// Precedences of operators
const int HIGHEST_PRECEDENCE = 3;
const int HIGH_PRECEDENCE = 2;
const int LOW_PRECEDENCE = 1;
const int NO_PRECEDENCE = 0;

// Operators
const char ADDITION = '+';
const char SUBTRACTION = '-';
const char MULTIPLICATION = '*';
const char DIVISION = '/';
const char POWER = '^';
const char MODULUS = '%';

// Parentheses
const char LEFT_PARENTHESIS = '(';
const char RIGHT_PARENTHESIS = ')';

// Space
const char SPACE = ' ';

// Function that returns true if the character is a digit
bool isDigit(char _digit) {
  return _digit >= '0' && _digit <= '9';
}

// Function that returns true if the character is an operator
bool isOperator(char _operator) {
  return _operator == ADDITION || _operator == SUBTRACTION || _operator == MULTIPLICATION || _operator == DIVISION
      || _operator == POWER || _operator == MODULUS;
}

// Function that returns true if the character is a unary operator
bool isUnaryOperator(int _index, string _infixNotation) {
  return (_infixNotation[_index] == ADDITION || _infixNotation[_index] == SUBTRACTION)
      && isDigit(_infixNotation[_index + 1]);
}

// Function that returns precedence of the operator
int getPrecedence(char _operator) {
  switch (_operator) {
    case ADDITION:
    case SUBTRACTION:return LOW_PRECEDENCE;
    case MULTIPLICATION:
    case DIVISION:
    case MODULUS:return HIGH_PRECEDENCE;
    case POWER:return HIGHEST_PRECEDENCE;
    default:return NO_PRECEDENCE;
  }
}

// Function that applies the operator to the operands
int applyOperator(char _operator, int _operand1, int _operand2) {
  switch (_operator) {
    case ADDITION:return _operand1 + _operand2;
    case SUBTRACTION:return _operand1 - _operand2;
    case MULTIPLICATION:return _operand1 * _operand2;
    case DIVISION:return _operand1 / _operand2;
    case POWER:return int(pow(_operand1, _operand2));
    case MODULUS:return _operand1 % _operand2;
    default:return 0;
  }
}

// Function that converts infix expression to postfix expression (Reverse Polish Notation) and returns the string.
string convertToRPN(string _infixNotation) {
  // Define a stack to store operators
  stack<char> operators;

  // Define a string to store the final postfix notation
  string postfixNotation;

  // Loop through each character in the infix notation
  int i = 0;
  while (i < _infixNotation.length()) {
    if (_infixNotation[i] == SPACE) {
      // If the current character is a space, skip it
      i++;
      continue;
    } else if (isDigit(_infixNotation[i]) || isUnaryOperator(i, _infixNotation)) {
      // If the current character is a digit or a unary operator, check if it is a number with multiple digits and add it to the output string

      // Define a string to store the number
      string number;

      // While the next character is a digit or the unary operator, add it to the number string
      while (i < _infixNotation.length()
          && (isDigit(_infixNotation[i]) || isUnaryOperator(i, _infixNotation))) {
        number += _infixNotation[i];
        i++;
      }

      // Add a space to the end of the number string
      postfixNotation += number + SPACE;

      // Decrement i to make sure the next character is not skipped
      i--;
    } else if (_infixNotation[i] == LEFT_PARENTHESIS) {
      // If the current character is a left parenthesis, push it to the operators stack
      operators.push(LEFT_PARENTHESIS);
    } else if (_infixNotation[i] == RIGHT_PARENTHESIS) {
      // If the current character is a right parenthesis, pop operators from the stack and add them to the output string
      while (!operators.empty() && operators.top() != LEFT_PARENTHESIS) {
        // Add each operator to the output string
        postfixNotation += operators.top();

        // Add a space to the end of the operator
        postfixNotation += SPACE;

        // Pop the operator from the stack
        operators.pop();
      }

      // If the stack is not empty and the top of the stack is a left parenthesis, pop it from the stack.
      // That means the right parenthesis is matched with the left parenthesis.
      if (!operators.empty() && operators.top() == LEFT_PARENTHESIS) {
        // Pop the left parenthesis from the stack
        operators.pop();
      }
    } else if (isOperator(_infixNotation[i])) {
      // If the current character is an operator, pop operators from the stack and add them to the output string
      // until an operator with lower precedence is found
      while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(_infixNotation[i])) {
        // Add each operator to the output string
        postfixNotation += operators.top();

        // Add a space to the end of the operator
        postfixNotation += SPACE;

        // Pop the operator from the stack
        operators.pop();
      }

      // Push the current operator to the stack
      operators.push(_infixNotation[i]);
    } else {
      // If the current character is not a digit, an operator, a left parenthesis or a right parenthesis, throw an error
      throw invalid_argument("Invalid character in the infix notation");
    }

    // Increment i to move to the next character
    i++;
  }

  // If there are any operators left in the stack, pop them and add them to the output string
  while (!operators.empty()) {
    // Add each operator to the output string
    postfixNotation += operators.top();

    // Add a space to the end of the operator
    postfixNotation += SPACE;

    // Pop the operator from the stack
    operators.pop();
  }

  // If the last character in the output string is a space, remove it
  if (!postfixNotation.empty() && postfixNotation[postfixNotation.length() - 1] == SPACE) {
    postfixNotation.erase(postfixNotation.length() - 1, 1);
  }

  // Return the output string
  return postfixNotation;
}

// Function that evaluates the postfix notation and returns the result
int evaluateRPN(string _postfixNotation) {
  // Define a stack to store operands
  stack<int> operands;

  // Loop through each character in the postfix notation
  int i = 0;
  while (i < _postfixNotation.length()) {
    if (_postfixNotation[i] == SPACE) {
      // If the current character is a space, skip it
      i++;
      continue;
    } else if (isDigit(_postfixNotation[i]) || isUnaryOperator(i, _postfixNotation)) {
      // If the current character is a digit or a unary operator, check if it is a number with multiple digits and push it to the operands stack

      // Define a string to store the number
      string number;

      // While the next character is a digit or a unary operator, add it to the number string
      while (i < _postfixNotation.length()
          && (isDigit(_postfixNotation[i]) || isUnaryOperator(i, _postfixNotation))) {
        number += _postfixNotation[i];
        i++;
      }

      // Convert the number string to an integer and push it to the operands stack
      operands.push(stoi(number));

      // Decrement i to make sure the next character is not skipped
      i--;
    } else if (isOperator(_postfixNotation[i])) {
      // If the current character is an operator, pop two operands from the stack, apply the operator and push the result to the stack

      // Pop the second operand from the stack
      int operand2 = operands.top();
      operands.pop();

      // Pop the first operand from the stack
      int operand1 = operands.top();
      operands.pop();

      // Apply the operator to the operands
      int result = applyOperator(_postfixNotation[i], operand1, operand2);

      // Push the result to the operands stack
      operands.push(result);
    } else {
      // If the current character is not a digit, an operator, a left parenthesis or a right parenthesis, throw an error
      throw invalid_argument("Invalid character in the postfix notation");
    }

    // Move to the next character in the postfix notation
    i++;
  }

  // The result of the expression is the only element left on the stack
  return operands.top();
}

int main() {
  // Run tests
  doctest::Context context;
  int res = context.run();
  return res;
}

TEST_CASE("Converting to RPN and evaluating") {
  string infixNotation = "2 + 3 * 4";
  string postfixNotation = convertToRPN(infixNotation);
  int result = evaluateRPN(postfixNotation);
  CHECK(postfixNotation == "2 3 4 * +");
  CHECK(result == 14);
}

TEST_CASE("Converting to RPN and evaluating with unary operators") {
  string infixNotation = "-2 + 3 * 4";
  string postfixNotation = convertToRPN(infixNotation);
  int result = evaluateRPN(postfixNotation);
  CHECK(postfixNotation == "-2 3 4 * +");
  CHECK(result == 10);
}

TEST_CASE("Converting to RPN and evaluating with parentheses") {
  string infixNotation = "2 + (3 * 4)";
  string postfixNotation = convertToRPN(infixNotation);
  int result = evaluateRPN(postfixNotation);
  CHECK(postfixNotation == "2 3 4 * +");
  CHECK(result == 14);
}

TEST_CASE("Converting to RPN and evaluating with multiple parentheses") {
  string infixNotation = "2 + (3 * 4) - (6 / 2)";
  string postfixNotation = convertToRPN(infixNotation);
  int result = evaluateRPN(postfixNotation);
  CHECK(postfixNotation == "2 3 4 * + 6 2 / -");
  CHECK(result == 11);
}

TEST_CASE("Converting to RPN and evaluating with multiple parentheses and unary operators") {
  string infixNotation = "-2 + (3 * 4) - (-6 / 2)";
  string postfixNotation = convertToRPN(infixNotation);
  int result = evaluateRPN(postfixNotation);
  CHECK(postfixNotation == "-2 3 4 * + -6 2 / -");
  CHECK(result == 13);
}

TEST_CASE("Converting to RPN and evaluating with multiple parentheses and unary operators and multiple digits") {
  string infixNotation = "-20 + (+30 * 40) - (-60 / 20)";
  string postfixNotation = convertToRPN(infixNotation);
  int result = evaluateRPN(postfixNotation);
  CHECK(postfixNotation == "-20 +30 40 * + -60 20 / -");
  CHECK(result == 1183);
}

TEST_CASE(
    "Converting to RPN and evaluating with multiple parentheses, unary operators, multiple digits, powers and modules") {
  string infixNotation = "-20 + (+30 * 40) - (-60 / 20) ^ 2 % 3";
  string postfixNotation = convertToRPN(infixNotation);
  int result = evaluateRPN(postfixNotation);
  CHECK(postfixNotation == "-20 +30 40 * + -60 20 / 2 ^ 3 % -");
  CHECK(result == 1180);
}

TEST_CASE("Converting to RPN and evaluating with invalid characters") {
  string infixNotation = "-20 + (+30 * 40a) - (-60 / 20) ^ 2 % 3";
  CHECK_THROWS(convertToRPN(infixNotation));
  string postfixNotation = "-20 +30 40a * + -60 20 / 2 ^ 3 % -";
  CHECK_THROWS(evaluateRPN(postfixNotation));
}
