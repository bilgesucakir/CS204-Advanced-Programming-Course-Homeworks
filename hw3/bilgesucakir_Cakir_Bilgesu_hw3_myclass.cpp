#include "bilgesucakir_Cakir_Bilgesu_hw3_myclass.h"

//Public functions start here
SubSeqsList::SubSeqsList(){
	hHead = NULL;
}

void SubSeqsList::DisplayAll(){ //This function displays the list (every line is a subsequence) in the wanted form.
	/* Begin: code taken and updated from ptrfunc.cpp */ 
	SubSeqHeadNode * ptr = hHead;
	while(ptr != NULL){

		cout << ptr->size << " | ";
		SubSeqNode * subPtr = ptr->sHead;
		int nodeCount = 0;
		while(subPtr != NULL){

			if(nodeCount != 0){
				cout << " --> ";
			}
			cout << subPtr->value;
			nodeCount++;
			subPtr = subPtr->next;
		}
		cout << endl;
		ptr = ptr->next;
	}
	/* End: code taken and updated from ptrfunc.cpp */ 
}

void SubSeqsList::DeleteAll(){ //This function deletes all SUbSeqHeadNodes (so all the list actually).
	SubSeqHeadNode * headN = hHead;
	SubSeqHeadNode * headN2 = hHead;
	while(headN2 != NULL){
		DeleteSubSeqHead(headN, hHead);
		headN2 = hHead;
		headN = headN2;
	}
}

void SubSeqsList::NegCase(int num){          //This function is called if the number is negative. If absolute value of that number exists in
	SubSeqHeadNode * headptr = hHead;        //a subsequence of the list, then that subsequence is deleted.
	SubSeqHeadNode * headptr2 = headptr;
	while(headptr2 != NULL){
		headptr2 = headptr2->next;
		if(ValueExistInSubSeq(num, headptr->sHead)){
			DeleteSubSeqHead(headptr, hHead);
		}
		headptr = headptr2;
	}
}

void SubSeqsList::NonNegCase(int num, bool & error){  //If the number is non-negative, this function places necessary subsequences in the list
	                                                  //to the necessary places. Also dynamically memory allocating checks are done by bool error
	SubSeqNode * newseq = new SubSeqNode(num, NULL);  //(if null is returned, then program ends when this function is finished without making 
	if(newseq != NULL){                               //any further implementations).
		SubSeqHeadNode * newhseq = new SubSeqHeadNode(1, newseq, NULL);
		if(newhseq != NULL){
			InsertSubSeqToThePlace(newhseq); //This part adds newly created subsequence which consists only the num itself to the list.

			SubSeqHeadNode * temp = hHead;
			while(temp != NULL){  //In this while loop other subsequences are checked (if there are any) to copy them and add the num and add this new
				                  //subsequence to the list.
				if(! ValueExistInSubSeq(num, temp->sHead)){
					if(isBiggerNumVsSubSeqNumbers(num, temp->sHead)){
						SubSeqNode * newSequence = CopySubSeq(temp->sHead, error);
						if(! error){
							AddNodeToSubSeq(newSequence, num, error);
							if(! error){
								SubSeqHeadNode * newSeqHead = new SubSeqHeadNode(lenSubSeq(newSequence), newSequence, NULL);
								if(newSeqHead != NULL){

									InsertSubSeqToThePlace(newSeqHead); //Newly created subsequence is added to the list here.
								}
								else{
									error = true;
								}
							}
						}
					}
				}
				temp = temp->next;
			}
		}
		else{
			error = true;
		}
	}
	else{
		error = true;
	}
}

bool SubSeqsList::IsListEmpty(){ //This function returns true if the list is empty.
	if(hHead == NULL){
		return true;
	}
	return false;
}

bool SubSeqsList::ValueExists(int val){ //This function returns true if an integer val exists in one of the subsequences that the current list has.
	bool exist = false;
	if(! IsListEmpty()){
		SubSeqHeadNode * hh = hHead;
		while(hh != NULL){
			SubSeqNode * sh = hh->sHead;
			while(sh != NULL){
				if(sh->value == val){
					exist = true;
				}
				sh = sh->next;
			}
			hh= hh->next;
		}
	}
	return exist;
}

//Private functions start here
int SubSeqsList::lenSubSeq(SubSeqNode * nde){ //This function returns length of a given subsequence. This is needed 
	SubSeqNode * ptr = nde;                   //for determining the sizes of the subsequences.
	int count = 0;
	while(ptr != NULL){
		count++;
		ptr = ptr->next;
	}
	return count;
}

void SubSeqsList::DeleteSubSeqHead(SubSeqHeadNode * subSeqDelete, SubSeqHeadNode *  & head){ //This function deletes one SubSeqHeadNode. It deals
	/* Begin: code taken and updated from ptrfunc.cpp */                                     //with cases such as whether the SubSeqHeadNode is
	if (subSeqDelete == head){                                                               //the first node or not.
		DeleteNodes(subSeqDelete);
		head = head->next;
		delete subSeqDelete;
	}
	else{
		SubSeqHeadNode * subPtr;
		subPtr = head;
		while (subPtr->next != subSeqDelete){
			subPtr = subPtr->next;
		}
		subPtr->next = subSeqDelete->next;
		delete subSeqDelete;
	}
	subSeqDelete = NULL;
	/* End: code taken and updated from ptrfunc.cpp */
}

void SubSeqsList::DeleteNodes(SubSeqHeadNode * headOfNodes){ //This function deletes all nodes in a given subsequence's head pointer (SubSeqHeadNode).
	/* Begin: code taken and updated from ptrfunc.cpp */
	SubSeqNode * ptr = headOfNodes->sHead;
	while(ptr != NULL){
		headOfNodes->sHead = headOfNodes->sHead->next;
		delete ptr;
		ptr = headOfNodes->sHead;
	}
	/* End: code taken and updated from ptrfunc.cpp */
}

bool SubSeqsList::isSmaller(SubSeqNode * theseq, SubSeqNode * seq2){ //This function compares 2 subsequences' nodes. Returns true if theseq is
	if(lenSubSeq(theseq) < lenSubSeq(seq2)){                         //smaller than seq2.
		return true;                                                 //(As an example sequence 1,4 is considered smaller than 1,2,3 so number of nodes
	}                                                                //is important too. Another example: 1,2 is considered smaller than 2,3 and 1,3 etc.)
	else if(lenSubSeq(theseq) > lenSubSeq(seq2)){                    //This is needed for placing the newly created subsequence in the right order.
		return false;
	}
	else{
		SubSeqNode * theTemp = theseq;
		SubSeqNode * temp2 = seq2;
		while(temp2 != NULL){
			if(theTemp->value < temp2->value){
				return true;
			}
			else if(theTemp->value > temp2->value){
				return false;
			}
			else{
				theTemp = theTemp->next;
				temp2 = temp2->next;
			}
		}
	}
	return false;
}

bool SubSeqsList::isBiggerNumVsSubSeqNumbers(int theNum, SubSeqNode * sequence){ //This function is used to decide whether should a new subsequence
	SubSeqNode * sequenceCopy = sequence;                                        //be created as this subsequence's another version that has also
	while(sequenceCopy != NULL){                                                 //the num. (Example: given subseq 1-->2 and num=3 num>1 and num>2
		if(theNum < sequenceCopy->value){                                        //so a new sequence 1-->2-->3 should be added to the list
			return false;
		}
		sequenceCopy = sequenceCopy->next;
	}
	return true;
}

bool SubSeqsList::ValueExistInSubSeq(int theVal, SubSeqNode * seqH){ //This function returns true if a given number is in one of the nodes
	SubSeqNode * subPtr = seqH;                                      //of the given subsequence.
	while(subPtr != NULL){
		if(subPtr->value == theVal){
			return true;
		}
		subPtr = subPtr->next;
	}
	return false;
}

void SubSeqsList::InsertSubSeqToThePlace(SubSeqHeadNode * headNew){  //This function inserts the newly created subsequence in the right order. It
	/* Begin: code taken and updated from ptrfunc.cpp */             //has different cases for the first node, last node and a node that is neither.
	int count=0;
	bool placed = false;
	if(hHead == NULL){
		hHead = headNew;
	}
	else{
		SubSeqHeadNode * temp = hHead;
		while(temp != NULL && !placed){
			count++;
			if(count == 1){
				if(isSmaller(headNew->sHead, temp->sHead)){
					headNew->next = temp;
					hHead = headNew;
					placed = true;
				}
			}
			if(!placed){
				if(temp->next != NULL){
					if(isSmaller(headNew->sHead, temp->next->sHead)){
						headNew->next = temp->next;
						temp->next = headNew;
						placed = true;
					}
				}
				else{
					headNew->next = temp->next;
					temp->next = headNew;
					placed = true;
				}
			}
			temp = temp->next;
		}
	}
	/* End: code taken and updated from ptrfunc.cpp */
}

void SubSeqsList::AddNodeToSubSeq(SubSeqNode * head, int val, bool & error){ //This function adds the val at the end of the newly copied 
	/* Begin: code taken and updated from ptrfunc.cpp */                     //subsequence. By this function a new sequence is made in the right
	SubSeqNode * headOfSeq = head;                                           //form. Also necessary checks for memory allocating problems are
	while(headOfSeq->next != NULL){                                          //done in this function.
		headOfSeq = headOfSeq->next;
	}
	SubSeqNode * nn = new SubSeqNode(val, NULL);
	headOfSeq->next = nn;

	if(nn == NULL){
		error = true;
	}
	/* End: code taken and updated from ptrfunc.cpp */
}

SubSeqNode * SubSeqsList::CopySubSeq(SubSeqNode * ptr, bool & error){ //This function copies a subsequence and returns its head.
	/* Begin: code taken and updated from copyLinkedList.cpp */       //Also checks for memory allocating problems are done in this function.
	if (ptr == NULL){
		return NULL;
	}
	SubSeqNode * res = new SubSeqNode(ptr->value, NULL); //This is the head of the copy subsequence.
	if(res != NULL){
		SubSeqNode * temp = res;
		SubSeqNode * ptrcopy = ptr;

		while(ptrcopy->next != NULL && temp != NULL){ 
			temp->next = new SubSeqNode(ptrcopy->next->value, NULL); 
			ptrcopy = ptrcopy->next;
			temp = temp->next;
		}
		if(temp != NULL){
			return res;
		}
		else{
			error = true;
			return NULL;
		}
	}
	else{
		error = true;
		return NULL;
	}
	/* End: code taken and updated from copyLinkedList.cpp */
}