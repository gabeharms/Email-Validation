//main.cpp - Email Validation Program main entry point
//Written by Gabe Harms

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Validates email and retruns true if the email is valdi, returns zero otherwise

bool IsValid( string email);


void main() {


	// 1. Open input and output files
	ifstream input("Email.txt");
	ofstream output("Result.txt");

	// 2. While not at the end of the input file
	while ( !input.eof() )
	{

		string email;


	// 3. Read an email address from the input file
		input >> email;
		

	// 4. Validate the email address
		bool isValid = IsValid(email);
	
			
	// 5. If the email address is valid write 1 to the output file else write zero
		output << isValid << endl;

	
		// 6. Repeat


	system("pause");

}