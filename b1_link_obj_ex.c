#include <stdio.h>
#include <stdlib.h>

//khởi tạo biểu tượng gồm tên và giá trị
struct Symbol {
  char *name;
  unsigned long val;
};

//khởi tạo nốt chứa con trỏ tới node tiếp theo và con trỏ tới phần tử của node
struct Node {
	struct Node *next;
	struct Symbol *element;
};

int main()
{
	//Khởi tạo các biến thuộc biểu tượng
	struct Symbol oneSym; 
	struct Symbol twoSym;
	struct Symbol threeSym;
	
	//khởi tạo các con trỏ đến các node A, B, C, P
	struct Node *nodeA;
	struct Node *nodeB;
	struct Node *nodeC;
	struct Node *nodeP;
	
	//Gán giá trị của các biến với các tên và giá trị tương ứng
	oneSym.name = "one";  	 oneSym.val = 1;	
	twoSym.name = "two";	 twoSym.val = 2;
	threeSym.name = "three"; threeSym.val = 3;
	
	//cấp phát bộ nhớ cho các node
	nodeA = malloc(sizeof(struct Node));
	nodeB = malloc(sizeof(struct Node));
	nodeC = malloc(sizeof(struct Node));
	
	
	nodeA->next = nodeB; nodeA->element = &oneSym;
	nodeB->next = nodeC; nodeB->element = &twoSym;
	nodeC->next = NULL; nodeC->element = &threeSym;
	
	nodeP = nodeA;
	
	while (nodeP!=NULL)
	{
		printf("%p (%s) points to %p\n", nodeP,nodeP->element->name,nodeP->next);
		nodeP = nodeP->next;
	}
		
	return 0;
}
