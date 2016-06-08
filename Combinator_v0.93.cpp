#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define STRATE 645000									// Defines the string-generating rate for the machine (My machine, anyway; YMMV)

string convertinto(unsigned long int* P_i, char* denom, int* divisor);
void mergefiles(char* L1, char* L2, char* Lo);			// Function which permutates strings in one file with another file to make an output file
unsigned long int j;									// Will store word list 1 count for progress indicator

unsigned long int countstrings(char* filename)			// unsigned long integers
{
	ifstream file (filename);
	string str;
	unsigned long int i = 0;							// Start counting at zero like a good computer should, using integers
	cout<<"Counting strings in " <<filename <<"...";
	while (file.good())	{								// As long as we haven't hit the end of the file,
		file>>str;										// Advance another string forward
		i++;											// And add 1 to our counter
	}
	cout<<i <<endl;										// Report the number to the user
	return i;											// When everything is done, send the result back to the function call
}

string convtime(unsigned long int i) 					// The argument will be seconds (units divided by units per second).
{
	int divisor;
	if (i < 60) {										// Less than a minute
		divisor = 1; return (convertinto (&i,  " seconds", &divisor)); }
	if (i < 3600) {										// Less than an hour
		divisor = 60; return (convertinto(&i, " minutes", &divisor)); }
	if (i < 86400) {									// Less than a day
		divisor = 3600; return (convertinto(&i, " hours", &divisor)); }
	if (i < 2419200) {									// Less than 28 days
		divisor = 86400; return (convertinto(&i, " days", &divisor)); }
	if (i < 31449600) {									// Less than a year
		divisor = 604800; return (convertinto(&i, " weeks", &divisor)); }
	else {												// More than a year
		divisor = 31557600; return (convertinto(&i, " years", &divisor)); }
}

string convertinto(unsigned long int* P_i, char* denom, int* divisor) {
	string c_denom = denom;
	string c_result = (std::to_string((*P_i / *divisor) + 1) + c_denom);
	return c_result;									// Converts one unit into another unit using its conversion rate
}

int main (int argc, char* argv[])
{
	cout<<"Combinator v. 0.93 by Ricky Ratzlaff\n\n";
	if (argc < 4) {
		cout<<"You need at least three arguments.\n";
		cout<<"Usage: combinator [input file 1] [input file 2] [output file]\n";
		return 1;
	}
	cout<<"Retrieving files " <<argv[1] <<" and " <<argv[2] <<"...\n";
	ifstream list1 (argv[1]);							// Open file 1
	if (!list1.is_open())								// Make sure it is open
	{
		cout<<"File " <<argv[1] <<" not found\n";
		return 1;
		}
	else
	{
	ifstream list2 (argv[2]);							// Open file 2
	if (!list2.is_open())								// Make sure it is open
	{
		cout<<"File " <<argv[2] <<" not found\n";
		return 1;
		}
	}
	unsigned long int numstrings1, numstrings2;			// These will store the string count for our opened files
	numstrings1 = countstrings(argv[1]);
	numstrings2 = countstrings(argv[2]);
	cout<<"Loading " <<numstrings1 <<" strings from " <<argv[1] <<"\n";
	cout<<"Loading " <<numstrings2 <<" strings from " <<argv[2] <<"\n";
	cout<<"This will produce " <<(numstrings1 * numstrings2) <<" strings.\n";
	cout<<"This will take approximately " <<(convtime((numstrings1 * numstrings2) / STRATE)) <<"." <<endl;
	cout<<"Press Enter to continue." <<endl;
	cin.get();											// Making the user press Enter, in case of balking at large time requirements
	j = numstrings1;									// Set the global variable for use in other functions as a progress indicator
	mergefiles(argv[1], argv[2], argv[3]);				// Do the dirty work
	return 0;
}

void mergefiles(char* L1, char* L2, char* Lo)
{
	unsigned long int i = 0;							// Introducing the counter
	string str1, str2, ostr;							// The three string-holders
	ofstream outputfile (Lo, ios::trunc);				// Create (or clear) a file for writing results to
	if (outputfile.is_open())							// If there was no problem opening for writing,
	{
		cout<<"0 percent complete\r";					// Initialize the progress indicator
		ifstream file1 (L1);							// Open List 1
		while (file1.good())							// As long as we haven't hit the end of List 1,
		{
			file1>>str1;								// Copy the next eligible string from List 1
			ifstream file2 (L2);						// Open List 2 for reading
			while (file2.good())						// As long as we haven't hit the end of List 2,
			{
				file2>>str2;							// Copy the next eligible string from List 2
				ostr = str1 + str2;						// Concatenate the string we got from List 1 with the string we got from List 2
				outputfile<<ostr;						// And stick it in the write file
				outputfile<<endl;						// Making sure to move to the next line.
			}
			i++;										// Add 1 to our progress indicator counter
			cout<<(i*100 / j) <<" percent complete\r";	// Compare the counter with the string count of List 1, and show it as a percentage
		}
		cout<<"\n";
	} else {
		cout<<"Output file cannot be written.\n";		// Heaven forbid you didn't get write permission first...
	}
}