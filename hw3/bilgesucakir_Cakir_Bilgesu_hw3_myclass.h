#ifndef _SUBSEQNODE
#define _SUBSEQNODE

#include <iostream>
using namespace std;

/* Begin: code taken and updated from CS204_Homework3_Spring2021.pdf */
struct SubSeqNode{
	int value;
	SubSeqNode * next;
	SubSeqNode::SubSeqNode(){}
	SubSeqNode::SubSeqNode(const int & v, SubSeqNode * n):value(v), next(n){
	}
};

struct SubSeqHeadNode{
	int size; 
	SubSeqNode * sHead; 
	SubSeqHeadNode * next;
	SubSeqHeadNode::SubSeqHeadNode(){}
	SubSeqHeadNode::SubSeqHeadNode(const int & s, SubSeqNode * sH, SubSeqHeadNode * n):size(s), sHead(sH), next(n){
	}
};
/* End: code taken and updated from CS204_Homework3_Spring2021.pdf */

class SubSeqsList
{
public:
	SubSeqsList();

	void DisplayAll();

	void DeleteAll();

	void NegCase(int num);

	void NonNegCase(int num, bool & error);

	bool IsListEmpty();

	bool ValueExists(int val);

private:
	SubSeqHeadNode * hHead;

	int lenSubSeq(SubSeqNode * nde);

	void DeleteSubSeqHead(SubSeqHeadNode * subSeqDelete, SubSeqHeadNode *  & head);

	void DeleteNodes(SubSeqHeadNode * headOfNodes);

	bool isSmaller(SubSeqNode * theseq, SubSeqNode * seq2);

	bool isBiggerNumVsSubSeqNumbers(int theNum, SubSeqNode * sequence);

	bool ValueExistInSubSeq(int theVal, SubSeqNode * seqH);

	void InsertSubSeqToThePlace(SubSeqHeadNode * headS);

	void AddNodeToSubSeq(SubSeqNode * head, int val, bool & error);

	SubSeqNode * CopySubSeq(SubSeqNode * ptr, bool & node);
};

#endif