/* Program Name: MPG
 * Student Name: Parker Haney
 * Net ID: phaney
 * Student ID: 000-54-2681
 * Program Description: This program takes an input of cars, trucks, and their miles and gallons for each.
 *	After the user has entered their desired amount cars and trucks, the average miles per gallon for each the
 *	cars and the trucks is printed to the screen */

#include <iostream>
#include <limits>
using namespace std;

int main() {
	int tCars = 0;
	double tcmiles = 0;
	double tcgallons = 0;

	int tTrucks = 0;
	double ttmiles = 0;
	double ttgallons = 0;
	string vehicle;

	while (true) {
		cout << "Enter command: ";
		cin >> vehicle;
		double cmiles;
		double cgallons;
		double tmiles;
		double tgallons;

		if (vehicle == "car") {
			tCars++;
			cout << "Enter car's miles: ";
			
			while (!(cin >> cmiles)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter car's miles: ";
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			tcmiles += cmiles;

			cout << "Enter car's gallons: ";
			
			while(!(cin >> cgallons)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter car's gallons: ";
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			tcgallons += cgallons;
		}

		else if (vehicle == "truck") {	
			tTrucks++;
			cout << "Enter truck's miles: ";
			while (!(cin >> tmiles)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter truck's miles: ";
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			ttmiles += tmiles;

			cout << "Enter truck's gallons: ";
			while (!(cin >> tgallons)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter truck's gallons: ";
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			ttgallons += tgallons;
		}

		else if (vehicle == "done") {
			break;
		}

		else {
			cout << "Unknown command." << endl;
		}
	}

	if (tCars == 0) {
		cout << "Fleet has no cars." << endl;
	}
	else {
		double avgCarMPG = (tcmiles / tcgallons);
		cout << "Average car MPG = " << avgCarMPG << endl;
	}

	if (tTrucks == 0) {
		cout << "Fleet has no trucks." << endl;
	}
	else {
		double avgTruckMPG = (ttmiles / ttgallons);
		cout << "Average truck MPG = " << avgTruckMPG << endl;
	}
}

