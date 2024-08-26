/*
TRIỂN KHAI CẤU TRÚC DỮ LIÊU NGĂN XẾP BẰNG CÁCH SỬ DỤNG DANH SÁCH LIÊN KẾT ĐƠN
*/

#include <stdio.h>

//Định nghĩa một cấu trúc cho phần tử trong stack, chứa một giá trị kiểu "unsigned long"
struct ElementType {
	unsigned long v;	
};

//Định nghĩa một nút trong danh sách liên kết, chứa một phần tử và một con trỏ tới nút kết tiếp
struct Node {
	struct ElementType value;
	struct Node *next;
};

typedef struct Node *Stack;
typedef struct Node *StackNode;

//Kiểm tra xem stack có rỗng không bằng cách kiểm tra xem con trỏ "next" của stack có trỏ tới "NULL" không
int is_empty(Stack S){
	return S->next == NULL;
}

//Tạo một stack mới bằng cách cấp phát bộ nhớ cho một nút và gán con trỏ "next" của nút này thành "NULL"
Stack create_stack(){
	Stack S = malloc(sizeof(struct Node));
	S->next = NULL;
	return S; //Trả về con trỏ tới nút đầu tiên -> stack mới được tạo
}

//Đặt con trỏ "next" của stack thành "NULL", loại bỏ các phần tử ra khỏi stack
void make_null(Stack S){
	if (S!=NULL)
		S->next = NULL;
	else 
		printf("You must use create_stack first!\n");
}

//Thêm một phần tử vào đỉnh của stack bằng cách tạo một nút mới, gán giá trị của phần từ cho nút này và liên kết nút mới vào stack
void push(Stack S, struct ElementType e){
	StackNode node = malloc(sizeof(struct Node));
	node->value = e;
	node->next = S->next;
	S->next = node;
}

//Trả về phần tử ở đỉnh của stack, mà là phần tử kế tiếp của nút đầu tiên trong danh sách
StackNode top(Stack S){
	if (is_empty(S)){
		printf("The stack is empty!\n");
		return NULL;
	} else {
		return S->next;
	}
}

//Loại bỏ phần tử ở đỉnh của stack bằng cách giải phóng nút đầu tiên và cập nhật con trỏ "next" của stack
void pop(Stack S){
	if (is_empty(S)){
		printf("The stack is empty!\n");
		return NULL;
	} else {
		StackNode firstNode = S->next;
		struct ElementType returnValue = S->next->value;
		S->next = S->next->next;
		free(firstNode);
	}
}

//In ra trạng thái hiện tại của stack, bao gồm tất cả các phần tử từ đỉnh tới đáy
void show_stack(Stack S){
	printf("Current state of the stack is: ");
	if (is_empty(S))
		printf("Empty!!!");
	S = S->next;		
	while (S!=NULL)	{
		printf("%ld ", S->value.v);
		S = S->next;
	}
	printf("\n");
}

int main() {
	Stack S = create_stack();
	struct ElementType v1, v2, v3, v4;
	v1.v = 10; v2.v = -4; v3.v = 6; v4.v = 20;
	push(S,v1);push(S,v2);push(S,v3);push(S,v4);
	show_stack(S);
	pop(S);pop(S);
	
	StackNode node = top(S);
	printf("Value of the top node is:%ld",node->value.v);
	return 0;
}
