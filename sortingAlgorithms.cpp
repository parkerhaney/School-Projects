/* Program Name: Sorting Algorithms
 * Student Name: Parker Haney
 * Net ID: phaney
 * Student ID: 000-54-2681
 * Program Description: This program takes two arguments, the executible and an input file containing integers. The user 
 *	is prompted to choose between insertion sort or selection sort. The integers in the file are then sorted in the way
 *	entered by the user. */
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void printVector(vector <int> &vec) {
	/* This function uses a forloop to cycle through the vector of integers and print them with specific spacing. */
	unsigned int size = vec.size();
	for (int i = 0; i < size; ++i) {
		cout << " " << vec.at(i);
		if (i != size - 1) {
			cout << " ";
		}
	}
	cout << "\n";
}

void swapValues(vector <int> &vec, const int lIndex, const int rIndex) {
	/* The following three lines uses a temporary variable to store the int at 
	 * vec.at(lIndex) and then sets vec.at(lIndex) to vec.at(rIndex) and vec.at(rIndex) to 
	 * the temporary value, or the old value of vec.at(lIndex). */ 
	int tempVal = vec.at(lIndex);
	vec.at(lIndex) = vec.at(rIndex);
	vec.at(rIndex) = tempVal;
}

void insertionSort(vector <int> &vec) {
	int inPos;
	int inVal;
	unsigned int size = vec.size();

	for (int i = 1; i < size; i++) {
		/* One iteration of this forloop means that the value at index i has been
		 * correctly sorted to a new index in respect to the other already sorted
		 * integers, however this can still change until its final iteration. */
		inPos = i;
		inVal = vec.at(i);
		cout << "  Finding placement for this value: " << inVal << endl; 

		while (inPos > 0 && inVal < vec.at(inPos - 1)) {
			vec.at(inPos) = vec.at(inPos - 1);
			inPos = inPos - 1;
			//This loop means "While my number is less then the number below it, keep moving it down in the vector"
		}
		
		//Once your number has reached its correct spot, set it to that index and print the vectort
		cout << "    " << inVal << " needs to be placed at index " << inPos << endl; 
		vec.at(inPos) = inVal;
		cout << "  Current state of vector:" << endl;
		cout << " ";
		printVector(vec);
	}	
}
 
void selectionSort(vector <int> &vec) {
	int min;
	unsigned int size = vec.size();

	//Each iteration of this forloop sorts the current number to its perminent sorted index
	for (int i = 0; i < size - 1; i++) {
		cout << "Step " << i + 1 << ":" << endl;
		cout << "  Selected index: vec[" << i << "] = " << vec.at(i) << endl;
		min = i;
		
		/* This forloop compares the number at index i to the numbers at the indexes
		 * above i, finding the smallest number left in the "unsorted part" of the list
		 * each time. */ 
		for ( int j = i + 1; j < size; j++) {
			if (vec.at(j) < vec.at(min)) {
				min = j;
			}
		}

		//States the minimum value and its index, then sets that minimum value to the current index
		//It sets it to the current index using the swapValues function
		cout << "    vec[" << min << "] = " << vec.at(min) << " is the minimum." << endl;
		if (min != i) {
			swapValues(vec, i, min);
			cout << "    SWAP." << endl;
		}
		
		//This is for when the current index is also the minimum value in the unsorted list
		else if (min == i) {
			cout << "    No swap. The selected index is the minimum." << endl;
		}
		cout << "  Vector after Step " << (i + 1) << ":" << endl;
		cout << " ";
		printVector(vec);
	}
}

int main(int argc, char **argv) {
	if (argc != 2) {
		//Error checking for the right number of arguments
		cerr << "usage: ./sortingAlgorithms datafile" << endl;
		return 1;
	}
	
	const string fileName = argv[1];
	ifstream fin(fileName);
	if (fin.fail()) {
		//Error checking in reading/opening the file
		cerr << "Error opening input file." << endl;
		return 1;
	}

	vector <int> vec;
	int data;
	
	//This reads the file and creates the vector we will be sorting
	while (fin >> data)	{
		vec.push_back(data);
	}
	fin.close();

	char letter;

	//Checking that the user entered a valid option
	while (letter != 'i' && letter != 's') {
		cout << "Type \"i\" for insertion sort, or \"s\" for selection sort: ";
		cin >> letter;
	}

	//This is the code for insertion sort (option "i")
	//The functions printVector() and insertionSort() are used, along with beginning/end print for the program  
	if (letter == 'i') {
		cout << "Beginning Vector:" << endl;
		cout << " ";
		printVector(vec);
		insertionSort(vec);
		cout << "Sorted Array in Ascending Order:" << endl;
		cout << " ";
		printVector(vec);
	}

	//This is selection sort (option "s")
	//It uses the functions printVector() and selectionSort to sort the 'vec' vector, and beginning/end print
	else if (letter == 's') {
		cout << "Beginning Vector:" << endl;
		cout << " ";
		printVector(vec);
		selectionSort(vec);
		cout << "Sorted Array in Ascending Order:" << endl;
		cout << " ";
		printVector(vec);
	}

	return 0;
}
