/*QUẢN LÝ DANH SÁCH LIÊN KẾT*/
#include <stdio.h>
#include <stdlib.h>

//đại diện cho một phần tử trong danh sách, bao gồm một ID và một con trỏ tới chuỗi tên
struct ElementType { 
	unsigned long ID;
	char *name;
};

//định nghĩa một nút trong danh sách liên kết, mỗi nút chứa một phần tử ElementType và một con trỏ tới nút tiếp theo
struct Node {//
	struct ElementType value;
	struct Node *next;
};

typedef struct Node *List;//định danh cho danh sách là một con trỏ tới nút đầu tiên của danh sách
typedef struct Node *Position;//phần định danh cho một vị trí trong danh sách

//chèn phần tử 'e' vào vị trí 'p' của danh sách 'pL' 
Position insert(List *pL, struct ElementType e, Position p){	
	Position newItem;
	newItem = malloc(sizeof(struct Node)); //cấp phát bộ nhớ cho nút mới
	newItem->value = e; //gán giá trị của 'e' cho nút mới
	if (*pL==NULL || p==NULL){ //nếu danh sách đang trống hoặc vị trí "p" là "NULL", nút mới sẽ được chèn vào danh sách
		newItem->next = *pL;
		*pL = newItem;
	} else { //ngược lại, nút mới sẽ được chèn vào sau vị trí "p"
		newItem->next = p->next;
		p->next = newItem;
	}
	return newItem; //trả về giá trị của nút vừa chèn
}

//in ra tất cả các phần tử trong danh sách, bao gồm ID và tên của mỗi phần tử
void display(List pL)
{
	int count = 1;
	while (pL!=NULL)
	{
		printf("*** %d | %ld       | %s\n",count,pL->value.ID, pL->value.name);
		pL = pL->next;
		count++;
	}
}

int main()
{
	List pL = NULL;
	struct ElementType e1,e2,e3;
	
	e1.ID = 123; e1.name = "Nguyen Van A";
	e2.ID = 124; e2.name = "Dang Thi B";
	e3.ID = 125; e3.name = "Do Van C";
	
	Position p;
	
	p = insert(&pL,e1,p);
	p = insert(&pL,e2,p);
	p = insert(&pL,e3,p);
	
	display(pL);	
	return 0;
}
