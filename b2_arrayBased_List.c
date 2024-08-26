	/*XỬ LÝ DANH SÁCH SINH VIÊN*/
#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE = 100;

//khai báo cấu trúc của một sinh viên gồm tên và ID
struct _ElementType { 
	char *name;
	unsigned long ID;
};

typedef struct _ElementType *Student; //khai báo cấu trúc sinh viên cho Student
typedef int Position; //vị trí

//thông tin về danh sách: gồm số lượng phần tử, kích thước tối đa và một mảng các sinh viên
struct _ListInfo { 
	unsigned long count;
	unsigned long max_size;
	Student list;
};

//danh sách học sinh
typedef struct _ListInfo *StudentList; 

//chèn học sinh e vào danh sách L tại vị trí p
void Insert(StudentList L, Student e, Position p) { 
	Position current;
	if (p > L->count || L->count == MAX_SIZE) exit(1); //xem vị trí p có hợp lệ hay không (không vượt quá số lượng phần tử hiện tại hoặc vượt quá kích thước tối đa)
		current = L->count;
	while (current != p) { //trong khi vị trí hiện tại khác p thì 
		L->list[current] = L->list[current-1]; //dịch các phần tử sang phải bắt đầu từ cuối danh sách cho đến khi đạt được vị trí p
		current--;
	}
	L->list[current] = *e; //chèn sinh viên vào vị trí p và tăng số lượng phần tử
	L->count++;
}

//xuất ra sinh viên cùng ID
void Show(StudentList L) { 
	for (Position i=0;i<L->count;i++)
	{
		printf("*** %d ID=%d    Name:%s \n",i+1,L->list[i].ID,L->list[i].name);
	}
}

int main () {
	StudentList stdList;
	stdList = malloc(sizeof(struct _ListInfo));
	stdList->max_size = MAX_SIZE;
	stdList->count = 0;
	
	stdList->list = malloc(stdList->max_size*sizeof(struct _ElementType));
	
	Student std1 = malloc(sizeof(struct _ElementType));
	std1->name = "Nguyen Van A";
	std1->ID = 202301;
	
	Student std2 = malloc(sizeof(struct _ElementType));
	std2->name = "Do B";
	std2->ID = 202302;
	
	Insert(stdList, std1, 0);
	Insert(stdList, std2, 0);	
		
	Show(stdList);
	return 0;
}
