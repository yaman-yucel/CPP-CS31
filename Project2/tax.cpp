#include <iostream>
#include <string>
using namespace std;

int main() 
{
	const double LOW_TAX_RATE = 0.04;
	const double MEDIUM_TAX_RATE = 0.05;
	const double HIGH_TAX_RATE = 0.07;
	const double VERY_HIGH_TAX_RATE = 0.093;

	const double TAX_REDUCTION_PER_CHILD = 200;

	const double FIRST_INCOME_BRACKET = 55000;
	const double SECOND_INCOME_BRACKET = 125000;

	string name = "none";
	double income = 0;
	string occupation = "none";
	int numberOfChildren = 0;
	
	double taxPay = 0;
	
	// Input reading and checking
	cout << "Name: ";
	getline(cin,name);

	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "Taxable income: ";
	cin >> income;
	cin.ignore(10000, '\n');

	cout << "Occupation: ";
	getline(cin, occupation);

	cout << "Number of children: ";
	cin >> numberOfChildren;
	cin.ignore(10000, '\n');

	cout << "---" << endl;

	// Handling empty name
	if (name == "") {
		cout << "You must enter a name" << endl;
		return 1;
	}
	// Handling negative income
	if (income < 0) {
		cout << "The taxable income must not be negative" << endl;
		return 1;
	}
	// Handling empy occupation
	if (occupation == "") {
		cout << "You must enter an occupation" << endl;
		return 1;
	}
	// Handling negative numberOfChildren
	if (numberOfChildren < 0) {
		cout << "The number of children must not be negative" << endl;
		return 1;
	}

	// Code Part
	
	// I have created 3 categories for a taxpayer according to their income. Each if handles one category.

	if (income >= 0 && income <= FIRST_INCOME_BRACKET){
		taxPay = income * LOW_TAX_RATE;
	}
	else if (income > FIRST_INCOME_BRACKET && income <= SECOND_INCOME_BRACKET){ 
		taxPay = FIRST_INCOME_BRACKET * LOW_TAX_RATE;
		if (occupation == "nurse" || occupation == "teacher")
			taxPay += (income - FIRST_INCOME_BRACKET) * MEDIUM_TAX_RATE;
		else
			taxPay += (income - FIRST_INCOME_BRACKET) * HIGH_TAX_RATE;
	}	
	else{
		taxPay = FIRST_INCOME_BRACKET * LOW_TAX_RATE;
		if (occupation == "nurse" || occupation == "teacher")
			taxPay += (SECOND_INCOME_BRACKET - FIRST_INCOME_BRACKET) * MEDIUM_TAX_RATE;
		else
			taxPay += (SECOND_INCOME_BRACKET - FIRST_INCOME_BRACKET) * HIGH_TAX_RATE;
		taxPay += (income - SECOND_INCOME_BRACKET) * VERY_HIGH_TAX_RATE;
	}
	
	if (income >= 0 && income < SECOND_INCOME_BRACKET)
		taxPay = taxPay - (TAX_REDUCTION_PER_CHILD * numberOfChildren);

	if (taxPay < 0)
		taxPay = 0;

	cout << name << " would pay $" << taxPay << endl;

	return 0;

}