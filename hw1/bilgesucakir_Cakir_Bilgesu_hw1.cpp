#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "bilgesucakir_Cakir_Bilgesu_hw1_strutils.h"
using namespace std;

//Bilgesu Cakir 27889 CS204 HW1

//This program takes a filename, uses that, reads that file and places every word on the lines (starting from the 2nd line) in the matrix if possible,
//sizes of the matrix given in the first row. This program displays the result of the placing, successfull or not to the console, with the given
//informations and the matrix. Strutils is used in this program.

struct RowCol{ //Struct containing cooridantes of a point (row, column)
	int row, column;
};

struct Word{                               //Struct containing informations on one line of the txt files. 
	string word, direction, orientation;   //RowCol struct has been put in as coordinates for easing the implementations.
	RowCol coordinates;
};

void MatrixPrinter(vector<vector<char>> & theMtrx){ //This function prints a given matrix in the wanted form.
	int rows = theMtrx.size(), cols = theMtrx[0].size();
	for(int i=0; i < rows; i++){
		for(int j=0; j < cols; j++){
			cout << theMtrx[i][j];
			if(j != cols - 1){
				cout << "\t";
			}
		}
		cout << endl;
	}
}

void GivePlacingError(vector<vector<char>> & TheMatrix, Word & wordInfos){ //If a word's placing process to the matrix fails, this function
	cout << "\"" << wordInfos.word << "\""                                 //is called and prints necessary warning messages, also the matrix before
		<< " could not be put into the matrix with given starting point: " //this failed word.
		<< wordInfos.coordinates.row << "," << wordInfos.coordinates.column << endl;
	cout << "direction: " << wordInfos.direction <<  "   " << "orientation: " << wordInfos.orientation << endl;
	MatrixPrinter(TheMatrix);
}

void GivePlacingResult(vector<vector<char>> & TheMatrix2, Word & wordInfos2){ //If current word is succesfully placed into the matrix, this
	cout << "\"" << wordInfos2.word << "\""                                   //function is called and prints necessary infos and the resulting matrix.
		<< " was put into the matrix with given starting point: " << wordInfos2.coordinates.row 
		<< "," << wordInfos2.coordinates.column << endl;
	cout << "direction: " << wordInfos2.direction <<  "   " << "orientation: " << wordInfos2.orientation << endl;
	MatrixPrinter(TheMatrix2);
}

bool isMatrixDimensionsPossible(int & theRow, int & theCol){ //This function checks given row and column numbers for the matrix are
	bool possible = true;                                    //useable or not. Since a matrix can't have 0 or -1, -2 etc. rows/columns,
	if(theRow <= 0){                                         //only integers bigger than zero are accepted.
		possible = false;                                     
	}
	else{
		if(theCol <= 0){
			possible = false;
		}
	}
	return possible;
}

bool isClockWise(Word & datas){ //This function checks whether the given orientation is clockwise or counter clockwise.
	bool cw = false;
	if(datas.orientation == "CW"){                 
		cw = true;
	}
	return cw;
}

bool isEmpty(vector<vector<char>> & Mtrx, int & rowCoord, int & colCoord){  //This function checks whether a given point from 
	bool empty = true;                                                      //the matrix is emtpty or not.
	if(Mtrx[rowCoord][colCoord] != '-'){ 
		empty = false;
	}
	return empty;
}

bool ErrorCheck(Word & word, RowCol & matrixSizes){
	bool hasError = false;                                                                                       
	cout << endl;                                                                                                
	if(((word.coordinates.row < 0)||(word.coordinates.row >= matrixSizes.row))||((word.coordinates.column < 0)||(word.coordinates.column >= matrixSizes.column))){                    
		cout << "Starting point is out of range! Point: " << word.coordinates.row << "," << word.coordinates.column << endl;            
		hasError = true;                                                                                         
	}                                                                                                            
	else{                                                                                                                                                                                                                                                                                    
		if((word.direction == "r")||(word.direction == "l")||(word.direction == "u")||(word.direction == "d")){
			if(!((word.orientation == "CW")||(word.orientation == "CCW"))){
				cout << "Invalid input for orientation! Orientation: " << word.orientation << endl;
				hasError = true;
			}                                                                                 //This function checks starting point, direction(r, l, 
		}                                                                                     //u, d otherwise error), orinentation (CW or CCW otherwise 
		else{                                                                                 //error). Starting point's components should be smaller or
			cout << "Invalid input for direction! Direction: " << word.direction << endl;     //equal than given matrix sizes also should be bigger or
			hasError = true;                                                                  //equal than 0.
		}
	}
	return hasError;
}

void PlaceLetter(vector<vector<char>> & givenMatrix, int rowNum, int colNum, char currentLetter){ //This function replaces an empty cell of the matrix
	givenMatrix[rowNum][colNum] = currentLetter;                                                  //('-') with the given letter of the current word.  
}

void DetermineNewDirection(Word & info){ //By using orientation information, this function decides for a new direction when a letter cannot be placed 
	if(info.direction == "r"){           //by using the current direction.
		if(isClockWise(info)){           
			info.direction = "d";
		}
		else{
			info.direction = "u";
		}
	}
	else if(info.direction == "d"){
		if(isClockWise(info)){
			info.direction = "l";
		}
		else{
			info.direction = "r";
		}
	} 
	else if(info.direction == "l"){
		if(isClockWise(info)){
			info.direction = "u";
		}
		else{
			info.direction = "d";
		}
	}
	else{
		if(isClockWise(info)){
			info.direction = "r";
		}
		else{
			info.direction = "l";
		}
	}
}

void PlaceWord_R(Word & currentWord1, vector<vector<char>> & copyMatrix1, bool & isplaced1, int index1, char l1, bool & noPossibility){
	bool goBack = false;
	if(index1 != 0){
		if(currentWord1.coordinates.column != copyMatrix1[0].size() - 1){  //Ths function deals with placement of the direction r. Since the given
			currentWord1.coordinates.column++;                             //row and col info belongs to previous point (i, j), if the new point
		}                                                                  //won't be out of range, new point is chosen as (i, j+1), moving one cell
		else{                                                              //to the right. If the letter is the first letter of that word, we use the
			DetermineNewDirection(currentWord1);                           //same point (i,j). If intitial point is at the last col of the matrix
			goBack = true;                                                 //placement fails and a new direction is chosen.
		}                                                                  //If the chosen point is empty, then letter is placed. If not, a new
	}                                                                      //direction is chosen and the point is reversed to its first condition (i,j).
	if(!goBack){           //goBack is to stop an out of range point to be placed.                                          
		if(isEmpty(copyMatrix1, currentWord1.coordinates.row, currentWord1.coordinates.column)){
			PlaceLetter(copyMatrix1, currentWord1.coordinates.row, currentWord1.coordinates.column, l1);
			isplaced1 = true;
		}
		else{
			if(index1 == 0){     
				noPossibility = true;   //this part means starting point is occupied, meaning this word cannot be placed, noPossibility is returned
			}                           //to the PlaceTheWord function, stopping everything for that word.
			else{
				currentWord1.coordinates.column--; 
				DetermineNewDirection(currentWord1);
			}
		}
	}

}

void PlaceWord_D(Word & currentWord2, vector<vector<char>> & copyMatrix2, bool & isplaced2, int index2, char l2, bool & noPossibility2){
	bool goBack2 = false;
	if(index2 != 0){
		if(currentWord2.coordinates.row != copyMatrix2.size() -1){  //This function deals with the placement of the direction d. It has the 
			currentWord2.coordinates.row++;                         //same implementations with PlaceWord_R. Only difference is the point is chosen as  
		}                                                           //(i+1, j) and if previous point is t the last row, new point is out of range.
		else{                                                       
			DetermineNewDirection(currentWord2);                    
			goBack2 = true;                                         
		}                                                           
	}
	if(! goBack2){  
		if(isEmpty(copyMatrix2, currentWord2.coordinates.row, currentWord2.coordinates.column)){
			PlaceLetter(copyMatrix2, currentWord2.coordinates.row, currentWord2.coordinates.column, l2);
			isplaced2 = true;
		}
		else{
			if(index2 == 0){
				noPossibility2 = true;
			}
			else{
				currentWord2.coordinates.row--;
				DetermineNewDirection(currentWord2);
			}
		}
	}
}

void PlaceWord_L(Word & currentWord3, vector<vector<char>> & copyMatrix3, bool & isplaced3, int index3, char l3, bool & noPossibility3){
	bool goBack3 = false;
	if(index3 !=0){
		if(currentWord3.coordinates.column != 0){  //This function deals with the placement of the direction left. This function is very similar to
			currentWord3.coordinates.column--;     //the one which deals with the right. Only difference is point is chosen as (i, j-1), not (i, j+1)
		}                                          //and a point is out of range when the previous point is in the first column. The rest is the same.
		else{
			DetermineNewDirection(currentWord3);
			goBack3 = true;
		}
	}
	if(! goBack3){
		if(isEmpty(copyMatrix3, currentWord3.coordinates.row, currentWord3.coordinates.column)){
			PlaceLetter(copyMatrix3, currentWord3.coordinates.row, currentWord3.coordinates.column, l3);
			isplaced3 = true;
		}
		else{
			if(index3 == 0){
				noPossibility3 = true;
			}
			else{
				currentWord3.coordinates.column++;
				DetermineNewDirection(currentWord3);
			}
		}
	}
}

void PlaceWord_U(Word & currentWord4, vector<vector<char>> & copyMatrix4, bool & isplaced4, int index4, char l4, bool & noPossibility4){
	bool goBack4 = false;
	if(index4 !=0){
		if(currentWord4.coordinates.row != 0){    //This function deals with placement of the direction up. This is very similar to the function 
			currentWord4.coordinates.row--;       //which deals with the direction right. Only difference is in this function choses the point as
		}                                         //(i-1, j), not (i, j+1) and a point is out of range when the previous one is at the first row.
		else{                                     //The rest is same.
			DetermineNewDirection(currentWord4);
			goBack4 = true;
		}
	}

	if(! goBack4){
		if(isEmpty(copyMatrix4, currentWord4.coordinates.row, currentWord4.coordinates.column)){
			PlaceLetter(copyMatrix4, currentWord4.coordinates.row, currentWord4.coordinates.column, l4);
			isplaced4 = true;
		}
		else{
			if(index4 == 0){
				noPossibility4 = true;
			}
			else{
				currentWord4.coordinates.row++;
				DetermineNewDirection(currentWord4);
			}
		}
	}
}

void PlaceTheWord(Word & infos, vector<vector<char>> & mainMatrix){  //This function deals with the placement of the every letter of the current word.
	                                                                 //If a letter cannot be placed at the first try, a count is hold since when all 4
	vector<vector<char>> copy_matrix;                                //directions are occupied, then the placement of the word fails and an error
	copy_matrix = mainMatrix;                                        //message and the current matrix is displayed. A copy matrix is created if the 
	bool notPossible = false;                                        //word cannot be placed, initial matrix is displayed, not the incomplete copy
	string copyDirection = infos.direction;                          //matrix. There are copies of the coordinates and the direction since during the 
	RowCol copyCoordinates = infos.coordinates;                      //process, these values change and the initial ones are displayed (copy ones are
	int LenWord = infos.word.length(), errorOutputCount = 0;         //not altered during the process). If the placement fails, a boolen variable
	                                                                 //prevents the function trying to go the next letter. While loop controls the
	for(int i=0; i < LenWord; i++){                                  //number of directions and prevents the same placed letter to be tried again.
		char letter = infos.word[i];                                 //If placement is successfully done, final matrix and infos are displayed.
		bool placed = false;                                         
		int directionCount = 0;
		infos.direction = copyDirection;

		if(!notPossible){

			while((directionCount < 4)&&(! placed)&&(! notPossible)){

				if((infos.direction == "r")&&(! placed)){
					PlaceWord_R(infos, copy_matrix, placed, i, letter, notPossible);
					if(! placed){
						directionCount++;
					}
				}
				else if((infos.direction == "l")&&(! placed)){
					PlaceWord_L(infos, copy_matrix, placed, i, letter, notPossible);
					if(! placed){
						directionCount++;
					}
				} 
				else if((infos.direction == "u")&&(! placed)){
					PlaceWord_U(infos, copy_matrix, placed, i, letter, notPossible);
					if(! placed){
						directionCount++;
					}
				}
				else if((infos.direction == "d")&&(! placed)){
					PlaceWord_D(infos, copy_matrix, placed, i, letter, notPossible);
					if(! placed){
						directionCount++;
					}
				}
			}
			if((! placed)||(directionCount == 4)){
				notPossible = true;
			}
		}
		else{
			if(errorOutputCount == 0){
				infos.direction = copyDirection;
				infos.coordinates = copyCoordinates;
				GivePlacingError(mainMatrix, infos);
				errorOutputCount++;
			}
		}
	}

	infos.direction = copyDirection;
	infos.coordinates = copyCoordinates;
	if(! notPossible){
		mainMatrix = copy_matrix;
		GivePlacingResult(mainMatrix, infos);
	}
	else{
		if(errorOutputCount == 0){
			GivePlacingError(mainMatrix, infos);
		}
	}
}

int main(){
	string fileName, currentLine, firstLine, strFromLine, rowNumberStr, columnNumberStr;
	bool errorExists = false;

	cout << "Please enter the name of the file: ";  
	cin >> fileName;

	ifstream fileInput;
	fileInput.open(fileName.c_str());

	while(fileInput.fail()){
		cout << "File name is incorrect, please enter again: ";    
		cin >> fileName;
		fileInput.open(fileName.c_str());
	}

	getline(fileInput, firstLine);
	istringstream firstLineStream(firstLine);
	firstLineStream >> rowNumberStr >> columnNumberStr;
	RowCol matSize;

	matSize.row = atoi(rowNumberStr);           //int row and column numbers are put into RowCol struct to ease the implementation.
	matSize.column = atoi(columnNumberStr);

	if(isMatrixDimensionsPossible(matSize.row, matSize.column)){   //If the given sizes for the matrix are valid, next lines are read, else stopped.
		vector<vector<char>> theMatrix(matSize.row, vector<char>(matSize.column, '-'));

		while(getline(fileInput, currentLine)){

			Word wordStruct;
			vector<string> wordInfoOfStr;  

			istringstream currentLineStream(currentLine);
			while(currentLineStream >> strFromLine){
				wordInfoOfStr.push_back(strFromLine);
			}

			if(wordInfoOfStr.size() != 5){                           //If number of the inputs is correct, then it is continued, else stopped.
				cout <<endl <<  "Invalid line! Number of values is different than 5." << endl;
				errorExists = true;
			}
			else{
				wordStruct.word = wordInfoOfStr[0];      
				wordStruct.coordinates.row = atoi(wordInfoOfStr[1]);
				wordStruct.coordinates.column = atoi(wordInfoOfStr[2]);
				wordStruct.direction = wordInfoOfStr[3];
				wordStruct.orientation = wordInfoOfStr[4];

				errorExists = ErrorCheck(wordStruct, matSize); //if there are no errors in starting point, direction and orientation,
				if(! errorExists){                             //then word placing function is called, otherwise an error message is displayed 
					                                           //and the next line is read. 
					PlaceTheWord(wordStruct, theMatrix);   
				}
			}
		}
	}
	else{
		cout << endl << "Invalid number for row and/or column!" << endl;
	}

	fileInput.close();
	return 0;
}