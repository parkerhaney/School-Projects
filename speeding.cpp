/* Program Name: Speeding Ticket Calculator
 * Student Name: Parker Haney
 * Net ID: phaney
 * Student ID: 000-54-2681
 * Program Description: This program reads an input file of speeding citations.
 *	For each ticket inside the given date range, it calculates the monetary fine 
 *	along with its date and its citation number and is then printed to an output file. */	

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

int main() {
	// These are what the input and output file names are stored as, 
	// as well as constant variables for the fine multiplier.
	string inputfilename;
	string outputfilename;
	const double iMult = 5.2243;
	const double hMult = 9.4312;
	const double rMult = 17.2537;
	const double otherMult = 12.916;

	//This is where it prompts the user for the input file and it reads it with fin.
	//It then error checks the file to see if it was able to be opened.
	cout << "Enter a ticket file: ";
	cin >> inputfilename;
	ifstream fin;
	fin.open(inputfilename);
	if (fin.fail()) {
		cerr << "Unable to open " << inputfilename << "." << endl;
		return 1;
	} 

	//Here the program prompts the user for an output file.
	//We create the ofstream object "fout" and error check that the output file was opened.
	cout << "Enter a report file: ";
	cin >> outputfilename;
	ofstream fout;
	fout.open(outputfilename);
	if (fout.fail()) {
		cerr << "Unable to open " << outputfilename << "." << endl;
		return 1;
	}

	//This is where the user is prompted for the start and end dates of the report.
	//We use this information to compare dates with the citations on the input file,
	// and we're able to filter out dates that are outside the range.
	//Variables for the year, month, and date for the start and end were created to store.
	int smon, sday, syr;
	cout << "Enter report start date (mm dd yyyy): ";
	cin >> smon >> sday >> syr;
	int emon, eday, eyr;
	cout << "Enter report end date   (mm dd yyyy): ";
	cin >> emon >> eday >> eyr;	

	//These are more variables that are being declared so that we 
	//are able to use them to store data in the while loop.
	string citNum;
	int month, day, year, clockedSpeed, speedLimit;
	char roadType;
	string omonth;
	double fine;

	//This means that until fin runs out of lines to read from the file, the loop will execute.
	while (fin >> citNum >> month >> day >> year >> clockedSpeed >> speedLimit >> roadType) {	

		//This array holds the months in 3-char strings, we use this to convert the months entered in numbers to be out put as a 3-char string.
		const string MONTHS[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		string omonth = MONTHS[month - 1];

		//This if statement takes care of when a year is entered in as 2 digits instead of 4.
		if (year <= 99) {
			year = 2000 + year;
		}

		//These if statements and continue statements are what filter out dates outside of our wanted range.
		//All the if statements apply to dates that are out of range, and when they are applicable to the if statement
		// and hold true, then the "continue" will skip the current interation of the while loop and move on to the next,
		// essentially meaning that once it detects and out of date range, it skips to the next line of text in the input file.
		if (year < syr) {
			continue;
		}	
		if (year > eyr) {
			continue;
		}
		if (month < smon && year == syr) {
			continue;
		}
		if (month > emon && year == eyr) {
			continue;
		}
		if (day < sday && month == smon) {
			continue;
		}
		if (day > eday && month == emon) {
			continue;
		}

		//Here, the fine is calculated by using a switch statement for the roadType chars. 
		//The cases account for upper and lowercase letters, and then uses the constant variable from 
		// earlier in the code that holds its fine multiplier to calculate the fine for that specific citation.
		switch (roadType) {
			case 'I':
			case 'i':
				fine = (clockedSpeed - speedLimit) * iMult;
				break;
			case 'R':
			case 'r':
				fine = (clockedSpeed - speedLimit) * rMult;
				break;
			case 'H':
			case 'h':
				fine = (clockedSpeed - speedLimit) * hMult;
				break;
			default:
				fine = (clockedSpeed - speedLimit) * otherMult;
				break;
		}

		//This if statement takes care of negative fines and rounds them to zero.
		if (fine < 0) {
			fine = 0;
		}

		//This is the format of what is printed into the output file.
		//We have 0's for single digit dates, left and right justification for the citation number and the fine, as well as the '$'.
		fout << fixed << setfill('0') << setw(2) << day << "-" << setw(2) << omonth << "-" << year << " ";
		fout << left << setfill(' ') << setw(10) << citNum << " " << "$" << right << setprecision(2) << setfill(' ') << setw(9) << fine << endl;
	}

	//Here we close out the ifstream object fin and the ofstream object fout.
	fin.close();
	fout.close();

}
