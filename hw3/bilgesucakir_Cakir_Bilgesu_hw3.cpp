#include <iostream>
#include <string>
#include <sstream>
#include "bilgesucakir_Cakir_Bilgesu_hw3_myclass.h"
using namespace std;

//Bilgesu Cakir 27889 CS204 HW3

/*This program reads a line of integers and creates a list of possible subsequences containing these numbers but in an ascending way
(also according to some limitations). If a negative number is entered, subsequences containing the absolute value of that number are deleted.
At the end, the list of subsequences is displayed. Implemented class (SubSeqsList) and its functions deal with these processes.
In that class, more complex functions are made as private members so most of the implementations happen there.*/

int main(){

	string lineStr;
	int currentNumber;
	bool error = false;  //For checking possible dynamically memory allocating problems

	cout << "Please enter the numbers in a line: ";
	getline(cin, lineStr);
	istringstream lineStream(lineStr);

	SubSeqsList theList;

	cout << endl;
	while(lineStream >> currentNumber){

		if(currentNumber >= 0){ //Newly read number added to the necessary sequences if not already in the list.

			if(theList.ValueExists(currentNumber)){
				cout << currentNumber << " is already in the list!" << endl;
			}
			else{
				theList.NonNegCase(currentNumber, error); //Error is true implies in some part of the NonNegCase a memory couldn't be allocated
				if(! error){                              //so the program ends without adding anything to the current list.
					cout << "Subsequence(s) containing " << currentNumber << " has/have been added" << endl;
				}
			}
		}
		else{
			int numToDelete = currentNumber * -1; //If a number is nagetive, then the subsequences containing absolute value of that number
			if(theList.ValueExists(numToDelete)){ //will be deleted in NegCase (of course if that number has ever existed in the list).

				theList.NegCase(numToDelete);
				cout << "All subsequence(s) containing "<< numToDelete << " has/have been deleted" << endl;
			}
			else{
				cout << "There is no subsequence that contains "<< numToDelete << " to be deleted" << endl;
			}
		}
	}
	if(! error){
		cout << endl << "FINAL CONTENT" << endl;
		if(theList.IsListEmpty() == true){
			cout << "List is empty!" << endl; //If every number is deleted at the end or none is given as input, this is displayed.
		}
		else{
			theList.DisplayAll(); //The list is displayed here by this member function.
		}
	}

	theList.DeleteAll(); //Deletion of the final version of the list made by this member function of the class.
	return 0;
}