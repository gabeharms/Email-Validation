//Validation.h - File that contains the IsValid function
//Written by Gabe Harms
#include <string>
#include<iostream>
#include<fstream>
using namespace std;

class MyClass 
{
	
private:
	#define MIN_EMAIL_SIZE 1
	#define MAX_EMAIL_SIZE 254

	#define MIN_LOCAL_PART_SIZE 1
	#define MAX_LOCAL_PART_SIZE 64

	#define MIN_DOMAIN_SIZE 1
	#define MAX_DOMAIN_SIZE 255

	#define VALID_LOCAL_PARTS_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.-0123456789!#$%^&*+=_-/?{}~'"
	#define VALID_DOMAIN_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.-"

	#define TDL_ARRAY_SIZE 280

public:
	bool IsValid(string);

	bool IsLocalPartValid(string);
	bool IsDomainValid(string);

	bool CheckRule(string);
	bool IsTdlValid(string);
}; 

bool MyClass::IsValid(string email){

	//1. Check sizwe: has to be >= 7 and <= 254	
	int emailLength = email.length();
	if ( (emailLength < MIN_EMAIL_SIZE) || (emailLength > MAX_EMAIL_SIZE) ) {
		cout << "\nERROR: Invalid Email Address:\nInvalid Overall Size of Address\n"; 
		return false;
	}

	//2. Find '@', if not found email is invalid
	int atIndex = email.find('@');
	if ( atIndex == string::npos ) {
		cout << "\nERROR: Invalid Email Address:\nNo @ was Found in the Address\n"; 
		return false;
	}

	//3. Seperate email into local part and domain
	string localPart = email.substr(0, atIndex);
	string domainPart = email.substr(atIndex + 1);

	//4. Validate localPart and domain
	return
		( IsLocalPartValid(localPart) && IsDomainValid(domainPart) );

}

bool MyClass::IsLocalPartValid(string localPart) {
		
	//1. Check size
	int localPartLength= localPart.length(); {
	if (localPartLength < MIN_LOCAL_PART_SIZE || localPartLength > MAX_LOCAL_PART_SIZE) {
		cout << "\nERROR: Invalid Email Address:\nLocal Part has an Invalid Size\n\n"; 
		return false;
	}
	}
	
	//2. Check for valid characters
	if (localPart.find_first_not_of(VALID_LOCAL_PARTS_CHARS) != string::npos) {
		cout << "\nERROR: Invalid Email Address:\nLocal Part Contains Invalid Characters\n\n"; 
		return false;
	}

	//3. Check dash rule and dot rule
	return
		CheckRule(localPart);
}
bool MyClass::IsDomainValid(string domainPart) {

	//1. Check size
	int domainPartLength= domainPart.length();
	if (domainPartLength < MIN_DOMAIN_SIZE || domainPartLength > MAX_DOMAIN_SIZE) {
		cout << "\nERROR: Invalid Email Address:\nDomain Part has an Invalid Size\n\n"; 
		return false;
	}

	//2. Check for valid characters
	if (domainPart.find_first_not_of(VALID_DOMAIN_CHARS) != string::npos) {
		cout << "\nERROR: Invalid Email Address:\nDomain Part Contains Invalid Characters\n\n"; 
		return false;
	}

	//3. Check dash rule and dot rule
	return
		CheckRule(domainPart) && IsTdlValid(domainPart);
	}

bool MyClass::CheckRule(string word) {
	
	//Check if . or - appears twice in a row
	int wordLength = word.length();
	char previous;
	char next; 
	for (int i = 0; i < wordLength - 1; i++) {
		previous = word[i];
		next = word[i+1];
		
		if ( (next =='.' || next == '-')  &&  (previous == '.' || previous == '-') ) { 
			cout << "\nERROR: Invalid Email Address:\nDid Not Pass the Hyphen/Dot Rule\n\n"; 
			return false;
		}

		if ( i == 0 ) {
			if ( previous == '.' || previous == '-' ) {
				cout << "\nERROR: Invalid Email Address:\nDid Not Pass the Hyphen/Dot Rule\n\n";
				return false;
			}
		}

		if ( i == wordLength-2 ) {
			if ( next == '.' || next == '-') {
				cout << "\nERROR: Invalid Email Address:\nDid Not Pass the Hyphen/Dot Rule\n\n";
				return false;
			}
	
		}

	}	



	return true;

}
bool MyClass::IsTdlValid(string domainPart) {
	//read in list of valid tdl's and put into an array
	ifstream input("ValidTDLs.txt");
	string validTDLs[TDL_ARRAY_SIZE];
	int arrayCount = 0;
	while ( input >> validTDLs[arrayCount]) {
		arrayCount++;
	}


	//identify where the tdl starts
	int tdlStart;
	int domainPartLength = domainPart.length();
	for (int i = domainPartLength-1; i >= 0; i--) {
		if (domainPart[i] == '.') {
			tdlStart = i+1;
			break;
		}
		if (i==0) {
			cout << "\nERROR: Invalid Email Address:\nDomain Part does not contain a dot\n\n";
			return false;
		}
	}

	if(tdlStart == domainPartLength) {
		cout << "\nERROR: Invalid Email Address:\nInvalid TDL\n\n";
		return false;
	}



	//construct the tdl into a string
	string tdl;
	int count = 0;
	for (int j = tdlStart; j < domainPartLength; j++) {
		tdl += domainPart[j];
		count++;
	}

	//convert string to all uppercase
	for (int l = 0; l < tdl.length(); l++) {
		if (tdl[l] >= 'a' && tdl[l] <= 'z') 
			tdl[l] = tdl[l ]-32;
	}

	//reference this string with the list of valid tdl's
	for (int k = 0; k < TDL_ARRAY_SIZE; k++) {
		if (tdl == validTDLs[k]) 
			return true;
	}

	cout << "\nERROR: Invalid Email Address:\nInvalid TDL\n\n";
	return false; 

}