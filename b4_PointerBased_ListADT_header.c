/*
HOÀN THIỆN HƠN BÀI TRƯỚC
	HIỂN THỊ VÀ TÌM KIẾM PHẦN TỬ TRONG DANH SÁCH LIÊN KẾT 
*/
#include <stdio.h>

//đại diện cho một phần tử trong danh sách, bao gồm mọt ID và một con trỏ tới chuỗi tên
struct ElementType {
	unsigned long ID;
	char *name;
};

//định nghĩa một nút trong danh sách liên kết, mỗi nút chứa một phần tử ElementType và một con trỏ tới nút tiếp theo
struct Node {
	struct ElementType value;
	struct Node *next;
};

typedef struct Node *List;//định danh cho danh sách là một con trỏ tới nút đầu tiên của danh sách
typedef struct Node *Position;//phần định danh cho một vị trí trong danh sách

//chèn phần tử 'e' vào vị trí 'p' 
Position insert(struct ElementType e, Position p){	
	Position newItem;
	newItem = malloc(sizeof(struct Node)); //cấp phát bộ nhớ cho nút mới
	newItem->value = e; //gán giá trị của 'e' cho nút mới

	newItem->next = p->next;
	p->next = newItem;

	return newItem; //trả về giá trị của nút vừa chèn
}

//in ra tất cả các phần tử trong danh sách, bắt đầu từ phần tử sau nút đầu tiên của danh sách
void display(List pL)
{
	int count = 1; //duyệt qua phần tử từ phần tử thứ hai trở đi và in ra ID và tên của mỗi phần tử
	pL = pL->next;
	while (pL!=NULL)
	{
		printf("*** %d | %ld       | %s\n",count,pL->value.ID, pL->value.name);
		pL = pL->next;
		count++;
	}
}

//tìm kiếm một phần tử trong danh sách dựa trên ID
Position find(List pL, unsigned long ID) {
	pL=pL->next;
	while (pL!=NULL && pL->value.ID!=ID) //duyệt qua danh sách và so sánh ID của mỗi phần tử với ID được cung cấp
		pL = pL->next;
	return pL; //nếu tìm thấy phần tử có ID khớp thì hàm trả về con trỏ tới phần tử đó
	//Nếu không tìm thấy thì hàm trả về NULL
}

//tạo một danh sách mới và trả về con trỏ tới nút đầu tiên của danh sách đó
//nút đầu tiên này không chứa dữ liệu thực tế, chỉ được sử dụng làm nút đầu danh sách
List createList() {
	List headerNode = malloc(sizeof(struct Node));
	headerNode->next = NULL;
	return headerNode;
}

int main()
{
	List pL = createList();
	struct ElementType e1,e2,e3;
	
	e1.ID = 123; e1.name = "Nguyen Van A";
	e2.ID = 124; e2.name = "Dang Thi B";
	e3.ID = 125; e3.name = "Do Van C";
	
	Position p = NULL;
	
	p = insert(e1,pL);
	p = insert(e2,p);
	p = insert(e3,p);
	
	display(pL);
		
	p = find(pL,124);
	
	if (p!=NULL) 
		printf("Found!!!  ID: %ld         Name:%s\n",p->value.ID,p->value.name);
	else
		printf("Not Found!!!");
	return 0;
}
