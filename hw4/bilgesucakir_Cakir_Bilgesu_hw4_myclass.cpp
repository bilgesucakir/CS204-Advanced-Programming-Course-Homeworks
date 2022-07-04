#include "bilgesucakir_Cakir_Bilgesu_hw4_myclass.h"

dynamicStackClass::dynamicStackClass(void){   //constructor
	/* Begin: code taken from and updated from DynIntStack.cpp*/
	theTop = NULL;
	/* End: code taken from and updated from DynIntStack.cpp*/
}

dynamicStackClass::~dynamicStackClass(void){   //destructor
	/* Begin: code taken from and updated from 4.1-advanced-classes.pdf*/
	NodeStack * ptr = theTop;
	while(theTop != NULL){
		theTop = theTop->next;
		delete ptr;
		ptr = theTop;
	}
	/* End: code taken from and updated from 4.1-advanced-classes.pdf*/
}

dynamicStackClass::dynamicStackClass(dynamicStackClass & copy){   //copy constructor since it is needed in the program.
	/* Begin: code taken from and updated from 4.1-advanced-classes.pdf*/

	theTop = copy.createTheClone();

	/* End: code taken from and updated from 4.1-advanced-classes.pdf*/
}

void dynamicStackClass::Push(int r, int c, bool & allocFail){    //This function pushes a new node to the top of the stack.
	/* Begin: code taken from and updated from DynIntStack.cpp*/
	NodeStack * newNode;
	if(isEmpty()){
		newNode = new NodeStack(r, c, NULL);
	}
	else{
		newNode = new NodeStack(r, c, theTop);
	}

	if(newNode != NULL){
		theTop = newNode;
	}
	else{
		allocFail = true;
	}
	/* End: code taken from and updated from DynIntStack.cpp*/
}

void dynamicStackClass::Pop(int & r, int & c){        //This function deletes the node on the top and retuns its contained infos.
	/* Begin: code taken from and updated from DynIntStack.cpp*/
	if(! isEmpty()){

		NodeStack * nodeToBeDeleted = theTop;

		r = nodeToBeDeleted->row;
		c = nodeToBeDeleted->column;

		theTop = theTop->next;
		delete nodeToBeDeleted;

		nodeToBeDeleted = NULL;
	}
	/* End: code taken from and updated from DynIntStack.cpp*/
}
 
bool dynamicStackClass::isEmpty(void){    //Returns true if there is no node in the stack.
	/* Begin: code taken from and updated from DynIntStack.cpp*/
	if(theTop == NULL){
		return true;
	}
	return false;
	/* End: code taken from and updated from DynIntStack.cpp*/
}

NodeStack * dynamicStackClass::createTheClone(void) const{     //This function creates a deep copy of the given stack.
	/* Begin: code taken from and updated from 4.1-advanced-classes.pdf*/
	if(theTop == NULL){
		return NULL;
	}

	NodeStack * topClone = new NodeStack (theTop->row, theTop->column, NULL);
	NodeStack * ptr = theTop->next;
	NodeStack * ptrClone = topClone; 

	while (ptr != NULL){
		ptrClone->next = new NodeStack (ptr->row, ptr->column, NULL);
		ptr = ptr->next;
		ptrClone = ptrClone->next;
	}
	return topClone;
	/* End: code taken from and updated from 4.1-advanced-classes.pdf*/
}