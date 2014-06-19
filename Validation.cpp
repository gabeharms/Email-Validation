//main.cpp - Email Validation Program main entry point
//Written by Gabe Harms

#include "Validation.h"

#include <iostream>
#include <istream>
#include <fstream>
#include <string>

using namespace std;

//Validates email and retruns true if the email is valdi, returns zero otherwise


int main() {

	MyClass main;

	// 1. Open input and output files
	ifstream input("Email.txt");
	ofstream output("Result.txt");

	//make sure the file exists
	cout << "Making Sure Both Files Exist...\n\n";
	if(input.fail())
		cout << "Error: Could Not Find The Input File\n";
	if(output.fail())
		cout << "Error Could Not Find the Output File\n";

	// 2. While not at the end of the input file
	string email;
	while ( getline(input, email) )
	{
		
		
	// 4. Validate the email address
		cout <<"Validating the following email address: " << email <<"...\n";
		bool IsValid = main.IsValid(email);
	
		
	// 5. If the email address is valid write 1 to the output file else write zero
		cout << email << " is a " << IsValid <<", writing to Result.txt...\n\n";
		output << IsValid << endl;

	
		// 6. Repeat

	}
		cout << "Completed Email Validation\n";
		system("pause");
		return 0;

}