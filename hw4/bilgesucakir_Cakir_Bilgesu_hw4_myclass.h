#ifndef _DYNAMICSTACKCLASS
#define _DYNAMICSTACKCLASS

#include <iostream>
using namespace std;

/* Begin: code taken and updated from DynIntStack.h */

struct NodeStack{
	int row, column;
	NodeStack *next;
	NodeStack::NodeStack(){};
	NodeStack::NodeStack(const int & r, const int & c, NodeStack * n): row(r), column(c), next(n){}
};

class dynamicStackClass
{
public:
	/* Begin: code taken from and updated from 4.1-advanced-classes.pdf*/
	dynamicStackClass(void);
	~dynamicStackClass(void);
	dynamicStackClass(dynamicStackClass & copy);
	void Push(int r, int c, bool & allocFail);
	void Pop(int & r, int & c);
	bool isEmpty(void);

private:
	NodeStack * theTop;
	NodeStack * createTheClone(void) const; 
	/* End: code taken from and updated from 4.1-advanced-classes.pdf*/
};  

/* End: code taken and updated from DynIntStack.h */

#endif