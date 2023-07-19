#include <iostream>
#include <string>
#include "Set.h"
#include <stack>
#include <cctype>
#include <cassert>

using namespace std;

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result);
bool precedence_check(char operator1, char operator2);
bool two_char_not_compatible(char ch1, char ch2);

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {

	string infix_without_space = "";
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] != ' ')
			infix_without_space += infix[i];
	}
	// Syntax checking
	// open paranthesis counts, they should match
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < infix_without_space.size(); i++) {
		char ch = infix_without_space[i];

		if (!((isalpha(ch) && islower(ch)) || ch == '!' || ch == '(' || ch == ')' || ch == '|' || ch == '&'))
			return 1; // unknown character

		// mistmatch check
		if (ch == '(')
			count1++;
		else if (ch == ')')
			count2++;

		//end and beginning check
		if (i == infix_without_space.size() - 1) {
			if (ch == '!' || ch == '&' || ch == '(' || ch == '|')
				return 1;
		}
		else if (i == 0)
		{
			if ( ch == '&' || ch == ')' || ch == '|')
				return 1;
		}

		// set check
		if (isalpha(ch))
		{
			if (!trueValues.contains(ch) && !falseValues.contains(ch))
				return 2;
			else if (trueValues.contains(ch) && falseValues.contains(ch))
				return 3;
		}

		if (i > 0)
		{
			char prev = infix_without_space[i - 1];
			if(two_char_not_compatible(prev, ch))
				return 1;
		}
	}
	if (count1 != count2)
	{
		return 1; // unmatching paranthesis
	}

	postfix = ""; // initialize postfix to empty
	stack<char> operatorStack; // initialize operator stack to empty
	for (int i = 0; i < infix_without_space.size(); i++)
	{
		char ch = infix_without_space[i];
		if (isalpha(ch)) // ch is filtered and can be only lower case set values.
			postfix += ch;
		else if( ch == '(' || ch == '!')
			operatorStack.push(ch);
		else if (ch == ')')
		{
			while (operatorStack.top() != '(')
			{
				if (operatorStack.empty())
					return 1;
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			if (operatorStack.empty())
				return 1;
			operatorStack.pop();
		}
		else if (ch == '&' || ch == '|')
		{
			while (!operatorStack.empty() && operatorStack.top() != '(' && precedence_check(ch, operatorStack.top()))
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(ch);
		}
		else
			return 1; // ERROR

	}
	while (!operatorStack.empty())
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}
	cerr << "POSTFIX: " << postfix << endl;
	//evaluation of postfix
	stack<bool> operandStack;
	for (int i = 0; i < postfix.size(); i++)
	{
		char ch = postfix[i];
		if (isalpha(ch)) // filtered at the first part
		{
			if (trueValues.contains(ch)) 
				operandStack.push(true);
			else if (falseValues.contains(ch))
				operandStack.push(false);
			else
				return 1;
		}
		else if (ch == '!')
		{
			if (operandStack.empty()) 
				return 1; // syntatically invalid infix boolean expression
			bool operand1 = operandStack.top();
			operandStack.pop();
			operandStack.push(!operand1);
		}
		else if (ch == '|')
		{
			if (operandStack.size() <= 1)
				return 1; // syntatically invalid infix boolean expression
			bool operand1 = operandStack.top();
			operandStack.pop();
			bool operand2 = operandStack.top();
			operandStack.pop();
			operandStack.push((operand1 || operand2));
		}
		else if (ch == '&')
		{
			if (operandStack.size() <= 1)
				return 1; // syntatically invalid infix boolean expression
			bool operand1 = operandStack.top();
			operandStack.pop();
			bool operand2 = operandStack.top();
			operandStack.pop();
			operandStack.push((operand1 && operand2));
		}
		else
			return 1;
	}

	if (operandStack.size() != 1) // returns 1 if empty "" passed
		return 1; // syntatically invalid infix boolean expression
	result = operandStack.top();
	operandStack.pop();

	return 0;
}

// ! has higher precedence than &, which has higher precedence than | ,
// and the operators & and | associate left to right
bool precedence_check(char operator1, char operator2)
// returns precedence of operator1 <= precedence of operator2
{
	if (operator1 == '!') {
		if (operator2 == '!')
			return true;
		else if (operator2 == '&')
			return false;
		else if (operator2 == '|')
			return false;
	}
	else if (operator1 == '&')
	{
		if (operator2 == '!')
			return true;
		else if (operator2 == '&')
			return true;
		else if (operator2 == '|')
			return false;

	}
	else if (operator1 == '|')
	{
		if (operator2 == '!')
			return true;
		else if (operator2 == '&')
			return true;
		else if (operator2 == '|')
			return true;
	}
	return false; // ERROR
	
}

// check two consecutive chars to find error in syntax
bool two_char_not_compatible(char ch1, char ch2)
{
	if (ch1 == '!')
	{
		if (ch2 == '!')
			return false; // !! okey , !!a
		else if (ch2 == '&')
			return true; // !& not okey
		else if (ch2 == '(')
			return false; // !(  okey,  !(a)
		else if (ch2 == ')')
			return true; // !) not okey
		else if (ch2 == '|')
			return true; // !| not okey
		else if (isalpha(ch2))
			return false; // !a okey 
	}
	else if (ch1 == '&')
	{
		if (ch2 == '!')
			return false; // &! okey , a&!a
		else if (ch2 == '&')
			return true; // &&  not okey
		else if (ch2 == '(')
			return false; // &( okey , a&(a)
		else if (ch2 == ')')
			return true; // &)  not okey
		else if (ch2 == '|')
			return true; // &| not okey
		else if (isalpha(ch2))
			return false; // &a okey ex a&a
	}
	else if (ch1 == '(')
	{
		if (ch2 == '!')
			return false; // (! okey , ex : (!a)
		else if (ch2 == '&')
			return true; // (& not okey
		else if (ch2 == '(')
			return false; // (( okey , ((a)|a)
		else if (ch2 == ')')
			return true; // ()  not okey
		else if (ch2 == '|')
			return true; // (| not okey
		else if (isalpha(ch2))
			return false; // (a okey (a)
	}
	else if (ch1 == ')')
	{
		if (ch2 == '!')
			return true; // )! not okey 
		else if (ch2 == '&')
			return false; // )& okey (a)&a
		else if (ch2 == '(')
			return true; // )( not okey 
		else if (ch2 == ')')
			return false; // )) okey ((a|a)|a)
		else if (ch2 == '|')
			return false; // )| okey (a)|a
		else if (isalpha(ch2))
			return true; // )a  not okey
	}
	else if (ch1 == '|')
	{
		if (ch2 == '!')
			return false; // |! okey  a|!a
		else if (ch2 == '&')
			return true; // |& not okey
		else if (ch2 == '(')
			return false; // |( okey  ex a|(a)
		else if (ch2 == ')')
			return true; // |) not okey
		else if (ch2 == '|')
			return true; // || not okey
		else if (isalpha(ch2))
			return false; // |a okey, ex a|a
	}
	else if (isalpha(ch1))
	{
		if (ch2 == '!')
			return true; // a not okey
		else if (ch2 == '&')
			return false; // a& okey, ex : a&a
		else if (ch2 == '(')
			return true; // a( not okey
		else if (ch2 == ')')
			return false; // a) okey , ex:!(a)
		else if (ch2 == '|')
			return false; // a| okey, ex: a|b
		else if (isalpha(ch2))
			return true; // aa not okey
	}
	return true; // invalid char ch1 or ch2
}

int main()
{
	string trueSet = "aclu";
    string falseSet = "nsx";
    Set truesSet;
    Set falsesSet;
    for (int k = 0; k < trueSet.size(); k++)
		truesSet.insert(trueSet[k]);
    for (int k = 0; k < falseSet.size(); k++)
		falsesSet.insert(falseSet[k]);

	string infix = "!!!(s&u&n)";
	// !!!n&c
	string pf;
	bool answer;
	assert(evaluate("u", truesSet, falsesSet, pf, answer) == 0  && answer);
	answer = !answer;
	assert(evaluate("u&c&l&a & !(u&s&c)", truesSet, falsesSet, pf, answer) == 0 && answer);
	assert(evaluate("(n)", truesSet, falsesSet, pf, answer) == 0 && !answer);
	answer = !answer;
	assert(evaluate("a&(s)", truesSet, falsesSet, pf, answer) == 0 && !answer);
	assert(evaluate("a & !s", truesSet, falsesSet, pf, answer) == 0 && answer);
	assert(evaluate("!(n|u)", truesSet, falsesSet, pf, answer) == 0 && !answer);
	assert(evaluate("!n|u", truesSet, falsesSet, pf, answer) == 0 && answer);
	answer = !answer;
	assert(evaluate("a|n&n", truesSet, falsesSet, pf, answer) == 0 && answer);
	answer = !answer;
	assert(evaluate("a&!(s|u&c|n)|!!!(s&u&n)", truesSet, falsesSet, pf, answer) == 0 && answer);

	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (int k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (int k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && answer);
	assert(evaluate("y|", trues, falses, pf, answer) == 1);
	assert(evaluate("n t", trues, falses, pf, answer) == 1);
	assert(evaluate("nt", trues, falses, pf, answer) == 1);
	assert(evaluate("()", trues, falses, pf, answer) == 1);
	assert(evaluate("()z", trues, falses, pf, answer) == 1);
	assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
	assert(evaluate("(n&(t|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("n+y", trues, falses, pf, answer) == 1);
	assert(evaluate("", trues, falses, pf, answer) == 1);
	assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
		&& pf == "ff!tn&&|" && !answer);
	assert(evaluate(" x  ", trues, falses, pf, answer) == 0 && pf == "x" && !answer);
	trues.insert('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 3);
	falses.erase('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 0 && pf == "x" && answer);
	trues.erase('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 2);
	falses.insert('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && !answer);
	cerr << "Passed all tests" << endl;

}