#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "bilgesucakir_Cakir_Bilgesu_hw4_myclass.h"
using namespace std;

//Bilgesu Cakir 27889 CS204 HW4

/*This program takes a file containing a matrix made of 1's and 0's as input and a bit string, and then searchs that given 
  matrix if it contains that bit string or not, according to some limitations. This program contains a backtracking algorithm, 
  to do so, it uses a class called dynamicStackClass and by stacks provided by that class, backtracking is done. If the given
  bit string is found, then matrix cells are displayed in order which contain that string. If not found, then appoprite
  message is returned. Also checks for dynamically allocating memory issues is done both in this program and in dynamicStackClass
  too. If that happens, program ends whithput further progress.*/

struct cellStruct{
	char ch;
	bool boolFlag;
	cellStruct::cellStruct(){}
	cellStruct::cellStruct(const char & theChar, bool theBool):ch(theChar), boolFlag(theBool){}
};

void CreateMatrixAndPlaceBitStrsInIt(cellStruct ** & h, ifstream & theStream, int rows, int cols, bool & allocFail){
	/* Begin: code taken from and updated from 2.2-pointers-linkedlists.pdf*/
	string theLine;

	h = new cellStruct * [rows];
	if(h != NULL){                                        //This function creates a dynamically allocated 2D matrix using cellStruct
		                                                  //struct and places bit strings read from given file and boolean flags.
		for(int i=0; i<rows; i++){                        //Dynamically memory allocating problem checks are done in this function.
			if(! allocFail){
				getline(theStream, theLine);
				istringstream theStrStream(theLine);
		
				h[i] = new cellStruct [cols];
				if(h[i] != NULL){

					for(int j=0; j<cols; j++){
						char ch;
						theStrStream >> ch;

						cellStruct cS(ch, false);
						h[i][j] = cS;
					}
				}
				else{
					allocFail = true;
				}
			}
		}
	}
	else{
		allocFail = true;
	}
	/* End: code taken from and updated from 2.2-pointers-linkedlists.pdf*/
}

bool isOnlyMadeFrom0and1(string & input){          //This function retýrns true if given bit string is only made from '0's and '1's.
	for(int i=0; i<input.length(); i++){           //This function prevents unnecessary checks if it returns false since we know that
		if(input[i] != '0' && input[i] != '1'){    //matrix only contains '0's and '1's.
			return false;
		}
	}
	return true;
}

bool isFittingToTheMatrix(string & bitStr, int & rowNum, int & colNum){   //This function returns true if given bit string's length is smaller
	int allCellNumber = rowNum * colNum;                                  //than or equal to the number of cells the matrix contains. 
	if(bitStr.length() > allCellNumber){                                  //This function prevents unnecessary searchs if bitstr does not fit in
		return false;                                                     //the matrix, meaning it can't be found in that matrix anyway.
	}
	else{
		return true;
	}
}

bool isBorderCell(string & direction, int theValue, int & matRow, int & matCol){  //Border cell means if that cell is on the last row (preventing
	if(direction == "right"){                                                     //move to down) or last column (preventing move to right) or both
		if(theValue == matCol - 1){                                               //(preventing going down and right). We need that info since in the
			return true;                                                          //search, matrix dimensions shouldn't be exceeded.
		}                                                                         //This function returns true if given cell is a border cell.
		else{
			return false;
		}
	}
	else{
		if(theValue == matRow - 1){
			return true;
		}
		else{
			return false;
		}
	}
}

bool isRightBlocked(int & matrixR, int & matrixC, int & cellR, int & cellC, cellStruct ** & mat){  //This function returns true if right hand side
	string direciton = "right";                                                                    //of that matrix is blocked. (if rhs boolean is true
	                                                                                               //or the given cell is in the last dolumn)
	if(isBorderCell(direciton, cellC, matrixR, matrixC)){
		return true;
	}
	else{
		if(mat[cellR][cellC + 1].boolFlag == true){
			return true;
		}
		else{
			return false;
		}
	}
}

bool isDownBlocked(int & matrixR, int & matrixC, int & cellR, int & cellC, cellStruct ** & mat){   //This function returns true if left hand side
	string direciton = "down";                                                                     //of that matrix is blocked. (meaning if lhs       
	                                                                                               //boolean is true or given cell is in the last row)
	if(isBorderCell(direciton, cellR, matrixR, matrixC)){
		return true;
	}
	else{
		if(mat[cellR + 1][cellC].boolFlag == true){
			return true;
		}
		else{
			return false;
		}
	}
}

bool isBitStringAllFound(dynamicStackClass & theStack, string & bitStr){      //This fucntion checks if the bit string is all found or not by using
	dynamicStackClass copyStack(theStack);                                    //the info in given stack. To not to alter the given stack, a copy stack
	int count = 0, rowPopped = 0, colPopped = 0;                              //is used (deep copy).

	while(! copyStack.isEmpty()){
		copyStack.Pop(rowPopped, colPopped);
		count++;
	}

	if(count == bitStr.length()){
		return true;
	}
	else{
		return false;
	}
}

void DisplayStackNodes(dynamicStackClass & stack, bool & allocFail){            //This function displays resulting cells infos from the given stack by
	/* Begin: code taken from and updated from 2.2-pointers-linkedlists.pdf*/   //popping the elements but first transferring the nodes to a reversed
	dynamicStackClass stack2;                                                   //stack in order to not to violate stack structure.
	int r1, c1, count = 0;

	while((! stack.isEmpty())&&(! allocFail)){
		stack.Pop(r1, c1);
		stack2.Push(r1, c1, allocFail);
	}

	if(! allocFail){
		while(! stack2.isEmpty()){
			int r2, c2;
			stack2.Pop(r2, c2);

			if(count != 0){
				cout << " ";
			}
			cout << "(" << r2 << "," << c2 << ")";
			count++;
		}
		cout << endl;
	}
	/* End: code taken from and updated from 2.2-pointers-linkedlists.pdf*/
}

void DisplayMessage(bool & searchCompleteOrNot, string & bitString, dynamicStackClass & theStack, bool & allocFail){    
	                                                                                             //This function displays messages according to if the
	if(searchCompleteOrNot){                                                                     //bit string is found or not. Also calls DisplayStackNodes.
		cout << "The bit string " << bitString << " is found following these cells:" << endl;
		DisplayStackNodes(theStack, allocFail);
	}
	else{
		cout << "The bit string " << bitString << " could not be found." << endl;
	}
}

void MatrixBoolFlagsNormalize(cellStruct ** & matrixHead, int & r, int & c){  //This function makes all the cells' boolFlags false again in order to
	for(int i=0; i < r; i++){                                                 //be able to search a new bit string in the same matrix.
		for(int j=0; j < c; j++){
			matrixHead[i][j].boolFlag = false;
		}
	}
}


void SearchBitStringInMatrixAndDisplayResult(bool & allocFail, cellStruct ** & matrix, string & str, int & matrixR, int & matrixC){ 
	//In this funciton, algorithm explained in CS204_Homework4_Spring2021.pdf is used.
	//This function makes the searching process by using backtracking and determines if the bit string exists in given matrix or not basically.
	//Also calls the message displaying function when the loop ends.

	bool searchComplete = false;
	int count = 0, currentRow = 0, currentCol = 0, currentIndexOfStr = 0;     
	dynamicStackClass stack;  //Stack is only created in this function since it is not needed in the main part.

	if(matrix[0][0].ch != str[0]){
		matrix[0][0].boolFlag = true;
	}

	while(matrix[0][0].boolFlag != true && searchComplete != true && (! allocFail)){  
		//matrix[0][0].BoolFlag == true means that bit string cannot be found in that matrix, so loop ends in taht case.
		if(matrix[currentRow][currentCol].boolFlag == false && matrix[currentRow][currentCol].ch == str[currentIndexOfStr]){
			stack.Push(currentRow, currentCol, allocFail);

			if(isBitStringAllFound(stack, str)){
				searchComplete = true;
			}
			else{
				if(! isRightBlocked(matrixR, matrixC, currentRow, currentCol, matrix)){
					currentCol++;
					currentIndexOfStr++;
				}
				else if (! isDownBlocked(matrixR, matrixC, currentRow, currentCol, matrix)){
					currentRow++;
					currentIndexOfStr++;
				}
				else{
					matrix[currentRow][currentCol].boolFlag = true;
					stack.Pop(currentRow, currentCol);
				}
			}
		}
		else{
			matrix[currentRow][currentCol].boolFlag = true;
			stack.Pop(currentRow,currentCol);
			currentIndexOfStr--;
		}
	}

	MatrixBoolFlagsNormalize(matrix, matrixR, matrixC);  //this is done in order to not cause a problem for the next bit string to be searched.
	DisplayMessage(searchComplete, str, stack, allocFail);
}

void DeleteMatrix(int row, cellStruct ** head){ //This function deletes dynamically created 2D array structure (which is the matrix).
	for(int i=0; i<row; i++){
		delete [] head[i];
	}
	delete head;
	head = NULL;
}

int main(){
	int row, column;
	string bitStr, fileName;
	bool allocationFail = false;

	cout << "Please enter the number of rows: ";
	cin >> row;
	cout << "Please enter the number of columns: ";
	cin >> column;
	cout << "Please enter the name of the input file that contains the matrix: ";
	cin >> fileName;

	ifstream fileStream;
	fileStream.open(fileName.c_str());
	while(fileStream.fail()){
		cout << "File cannot be opened." << endl;
		cout << "Please enter the name of the input file again: ";
		cin >> fileName;
		fileStream.open(fileName.c_str());
	}
	cout << endl;

	cellStruct ** theHead = NULL;
	CreateMatrixAndPlaceBitStrsInIt(theHead, fileStream, row, column, allocationFail); //Now matrix is created.

	if(! allocationFail){
		cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
		while((cin >> bitStr)&&(! allocationFail)){
			if(isOnlyMadeFrom0and1(bitStr) && isFittingToTheMatrix(bitStr, row, column)){
				SearchBitStringInMatrixAndDisplayResult(allocationFail, theHead, bitStr, row, column);
			}
			else{
				cout << "The bit string " << bitStr << " could not be found." << endl;  //If the given matrix is not only made of 0a and 1s,
			}                                                                           //then this message is displayed without making the search
			                                                                            //since it wouldn't be founded anyway in the matrix.
			cout << "---------------------------------------------------------" << endl;
			cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
		}

		cout << "Program ended successfully!" << endl << endl;
	}
	else{
		cout << "There has been a dynamically memory allocation fail in the program or in the class. Program now ends without furter progress." << endl;
	}

	DeleteMatrix(row, theHead);
	fileStream.close();
	return 0;
}