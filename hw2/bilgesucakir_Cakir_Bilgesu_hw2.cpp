#include <iostream>
#include <string>
#include <sstream>
#include "bilgesucakir_Cakir_Bilgesu_hw2_strutils.h"
using namespace std;
//Bilgesu Cakir 27889 CS204 HW2  
//This program takes a series of integers and adds them in a linked list according to given input about this series is ascending or descending.
//Numbers that violates the ascendance or descendance are deleted from the link list and at the end, final list is displayed.

/* Begin: code taken and updated from ptrfunc.cpp */
struct node{
	int value;
	node* next;
	node::node(){
	}
	node::node(const int & s, node * link):value(s), next(link){
	}
};
/* End: code taken and updated from ptrfunc.cpp */

/* Begin: code taken and updated from ptrfunc.cpp */
node * Add2End(node * tail, int id){            //This function adds a node to the end of the linked list.
	node *nn = new node(id, NULL);
	tail->next = nn;
	return nn;
}
/* End: code taken and updated from ptrfunc.cpp */

bool isInList(int number, node * headNode){   //This function checks that the current number is in linked list or not. 
	node * ptr = headNode;
	while(ptr != NULL){
		if(ptr->value == number){
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

/* Begin: code taken and updated from ptrfunc.cpp */
void DisplayList(node * head){   //This function takes a pointer (head) and displays the numbers in nodes of the link list that pointed by the 
	                             //head in necessary form.
	int loopCount = 0;
	node * ptr = head;
    while (ptr != NULL){
		if(loopCount != 0){
			cout << " ";
		}
		loopCount++;
		cout << ptr->value;
		ptr = ptr->next;
	}
}
/* End: code taken and updated from ptrfunc.cpp */

/* Begin: code taken and updated from ptrfunc.cpp */
void DeleteOneNode(node * toBeDeleted, node * & head, node * & tail, node * & tempInFunc){
	node * thePointer;
		                                //This function deletes a node from the linked list, also deals with the situations that the node
	if(toBeDeleted == head){            //to be deleted is the first node, last node, or a node that is neither. If necessary, head and tail
		head = head->next;              //pointers are updated.
		tempInFunc = head;
		delete toBeDeleted;
		toBeDeleted = NULL;
	}
	else{
		thePointer = head;
		while (thePointer->next != toBeDeleted){
			thePointer = thePointer->next;
		}
		thePointer->next = toBeDeleted->next;
		tempInFunc = toBeDeleted->next;
		delete toBeDeleted;
		toBeDeleted = NULL;

		if(thePointer->next == NULL){
			tail = thePointer;
		}
	}
}
/* End: code taken and updated from ptrfunc.cpp */

int NoOfNodesInList(node * head){           //This function returns the number of nodes in the given linked list.
	int count = 0;
	node * nd = head;

	while(nd != NULL){
		count++;
		nd = nd->next;
	}
	return count;
}

bool isEmpty(node * listHead){  //This function returns true if the linked list that given pointer points is empty.
	if(listHead == NULL){
		return true;
	}
	return false;
}

void lookForNodesToBeDeletedAndDelete(node * & theHead, int theNumber, node * & tailNode, bool ascending, int & nodeNo){
	int valueToBeD, deletedNodeCount = 0;

	/* Begin: code taken and updated from ptrfunc.cpp */
	node *temp = theHead, *pointToDeletingNode = NULL;       //This function finds and deletes the nodes containing integers that violates 
	                                                         //ascendance or descendance of the list. Deleted nodes are displayed in this function.
	nodeNo = NoOfNodesInList(theHead);                       

	while(temp != NULL){
		if((temp->value > theNumber && ascending)||(temp->value < theNumber && ! ascending)){
			pointToDeletingNode = temp;
			valueToBeD = pointToDeletingNode->value;

			if(deletedNodeCount != 0){
				cout << " ";
			}
			cout << valueToBeD;

			DeleteOneNode(pointToDeletingNode, theHead, tailNode, temp);
			deletedNodeCount++;
			nodeNo = nodeNo - 1;
		}
		else{
			temp = temp->next;
		}
	/* End: code taken and updated from ptrfunc.cpp */
	}
	if(deletedNodeCount == 0){
		cout << "None"; //If no nodes are deleted, then this is displayed.
	}
	cout << endl;

	temp = NULL;
}

/*Begin: code taken and updated from 2.2-pointers-linkedlists.pdf*/ 
void DeleteList(node * headOfList){          //This function deletes a linked list pointed by given pointer.
	node *temporary;
	while (headOfList != NULL){
		temporary = headOfList->next;
		delete headOfList;
		headOfList = temporary;
	}
}
/*End: code taken and updated from 2.2-pointers-linkedlists.pdf*/ 

int main(){
	string orderModeInput, numbers, orderModeLine;
	int number;
	bool error = true;

	cout << "Please enter the order mode (A/D): ";

	while(error){  //This part asks for input until an acceptable one is entered.
		getline(cin, orderModeLine);
		
		if(orderModeLine.length() > 0){
			istringstream orderModeStream(orderModeLine);
			orderModeStream >> orderModeInput;

			if(orderModeInput == "A" || orderModeInput == "D"){
				error = false;
			}
			else{
				cout << "Please enter the order mode again (A/D): ";
			}
		}
		else{
			cout << "Please enter the order mode again (A/D): ";
		}
	}
	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers);
	istringstream lineStream(numbers);

	node *head = NULL, *theTail = NULL;

	int numberCount = 0;
	while(lineStream >> number){  //In this while loop, for every current number lookForNodesToBeDeletedAndDelete function is called and 
		cout << endl;             //some numbers that violate the ascending or the descending list are deleted, after that current number 
		numberCount++;            //is added to the main linked list. Also necessary infos are displayed within this loop (next number, deleted nodes,
		bool isAscending = false; //appended and list content).
		int nodeNumber = -1;

		cout << "Next number: " << number << endl;
		                                                          
		if(orderModeInput == "A"){                                
			isAscending = true;
		}
		if(numberCount == 1){                 //If the number is the first one to be added to the linked list, there is no need to delete anything,
			head = new node(number, NULL);    //so the number is directly added to the linked list.
			theTail = head;

			cout << "Deleted nodes: None" << endl;
			cout << "Appended: " << number << endl;
		}
		else{ //If the number won't be the first number in the linked list, then a function is called for the necessary checks and deletions.
			if(! isInList(number, head)){

				cout << "Deleted nodes: ";
				lookForNodesToBeDeletedAndDelete(head, number, theTail, isAscending, nodeNumber);
				if(nodeNumber == 0){
					head = new node(number, NULL);
					theTail = head;
				}
				else{
					theTail = Add2End(theTail, number);   //Tail is updated if the current number is not the first node (because number is
				}                                         //added to the end of the linked list).
				
				cout << "Appended: " << number << endl;
			}
			else{
				cout << number << " is already in the list!" << endl;
			}
		}
		cout << "List content: ";
		DisplayList(head);
		cout << endl;
	}     

	cout << endl;
	if(isEmpty(head)){
		cout << "The list is empty at the end of the program and nothing is deleted" << endl; //If the list is empty at the end of the program, this is printed
	}
	else{
		cout << "All the nodes are deleted at the end of the program: "; 
		DisplayList(head);  //Final version of the main linked list is displayed here.
		cout << endl;
	}

	DeleteList(head);    //Main linked list is deleted here also pointers that point to it are pointed to NULL to avoid problems.
	head = NULL, theTail = NULL;

	return 0;
}