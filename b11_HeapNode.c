#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct HeapNode {
    int value;
};

struct HeapRecord {
    int length;
    int heap_size;
    struct HeapNode *heap_array;
};

typedef struct HeapRecord *Heap;

Heap create_heap(int length) {
    Heap H = malloc(sizeof(struct HeapRecord));
    if (H == NULL) {
        printf("Not enough memory!\n");
        return NULL;
    }
    H->heap_array = malloc(sizeof(struct HeapNode) * (length + 1));
    if (H->heap_array == NULL) {
        printf("Not enough memory!\n");
        free(H);
        return NULL;
    }
    H->length = length;
    H->heap_size = 0;
    return H;
}

/*
 Duy trì tính chất của một heap tối đa tại một nút nhất định trong cây.
 Nếu một nút vi phạm tính chất heap tối đa (nút cha lớn hơn hoặc bằng các nút con), 
thì hàm sẽ đổi vị trí của nút đó với nút con lớn hơn và tiếp tục kiểm tra ở cấp độ con để đảm bảo tính chất heap tối đa được duy trì
*/
void max_heapify(Heap H, int i) {
	int left, right ,largest;
	//left là nút con bên trái, right là nút con bên phải, largest là vị trí của nút lớn nhất trong ba nút hiện tại
	left = 2*i;
	right = 2*i + 1;
	largest = i;
	/*tìm nút có giá trị lớn nhất*/
	//so sánh giá trị của nút 'i' với giá trị của nút con bên trái
	if (left<= H->heap_size && H->heap_array[left].value>H->heap_array[largest].value)
		largest = left;
	//so sánh giá trị của nút 'i' với giá trị của nút con bên phải
	if (right<= H->heap_size && H->heap_array[right].value>H->heap_array[largest].value)
		largest = right;
	/*Hoán đổi đệ quy*/
	if (largest != i) { //nếu largest khác 'i' tức là giá trị của nút 'i' không phải là lớn nhất, hoán đổi vị trí hai nút
		struct HeapNode tmp;
		tmp = H->heap_array[i];
		H->heap_array[i] = H->heap_array[largest];
		H->heap_array[largest] = tmp;
		max_heapify(H,largest); //Gọi đệ quy trên nút largest để duy trì tính chất heap tối đa
	}
}

void show_heap(Heap H, int size) {
	if (H->heap_size == 0) {
		printf("The heap is empty!\n");
		return;
	}
	printf("The heap: ");
	for (int i = 1; i<= size;i++)
		printf("%d ",H->heap_array[i].value);
	printf("\n");
}


/*
Hàm này có nhiệm vụ chuyển đôi một mảng thành một heap tối đa (max heap)
Tính chất của max heap: giá trị của mỗi nút lớn hơn hoặc bằng giá trị của các nút con của nó.
Sử dụng hàm 'max_heapify' để đảm bảo tính chất này tại từng nút trong heap.
*/
void build_max_heap(Heap H) {   
	H->heap_size = H->length; //khởi tạo kích thước của heap
	for (int i=H->length/2;i>0;i--) //duyệt từ giữa về đầu mảng
	//bắt đầu từ nút cha cuối cùng và di chuyển ngược lên đầu mảng. Nút cha cuối cùng nằm ở vị trí H->length/2 vì các nút sau vị trí này đều là nút lá và không cần phải heapify
		max_heapify(H,i); //gọi hàm này để duy trì tính chất heap tối đa từ nút 'i' trở xuống
}


/*
Đoạn mã này thực hiện thuật toán sắp xếp bằng cách sử dụng cấu trúc heap max
Hai bước: 
	1. Xây dựng một heap tối đa từ mảng đầu vào.
	2. Hoán đổi phần tử lớn nhất (gốc của heap) với phần tử cuối cùng và giảm kích thước heap đi 1
	   Sau đó gọi max_heapify để duy trì tính chất heap max. Lặp lại cho đến khi heap trống
*/
void heap_sort(Heap H) { 
	build_max_heap(H); //Chuyển đổi mảng đầu vào thành một heap max. Khi hoàn thành phần tử lớn nhất của mảng sẽ ở gốc của heap
	//Hoán đổi và heapify
	for (int i=H->length;i>1;i--) { //Bắt đầu từ phần tử cuối cùng của và di chuyển ngược về đầu mảng
	//Hoán đổi: Phần tử gốc (lớn nhất) được hoán đổi với phần tử ở vị trí 'i'. Đưa phần tử lớn nhất về cuối mảng, nằm đúng vị trí cuối cùng sau khi sắp xếp
		struct HeapNode tmp = H->heap_array[1];
		H->heap_array[1] = H->heap_array[i];
		H->heap_array[i] = tmp;
		H->heap_size--; //Giảm kích thước heap: Giảm kích thước heap đi 1 để loại bỏ phần tử đã được sắp xếp ra khỏi phạm vi của heap
		max_heapify(H,1); //duy trì tính chất heap max
	}
}


/*
Hàm này trả về giá trị lớn nhất trong heap
Trong một heap tối đa, giá trị lớn nhất luôn nằm ở gốc của heap, tức là phần tử đầu tiên của mảng (ở chỉ số 1 nếu mảng bắt đầu từ chỉ số 1)
*/
struct HeapNode* heap_maximum(Heap H) {
	if (H->heap_size < 1) //Kiểm tra kích thước của heap
		return NULL;
	return &H->heap_array[1]; //Trả về giá trị lớn nhất
}


/*
Hàm này có nhiệm vụ loại bỏ và trả về phần tử lớn nhất trong một heap tối đa.
Các bước:
	1.Lấy giá trị của phần tử gốc.
	2.Di chuyển phần tử cuối cùng lên gốc.
	3.Giảm kích thước của heap.
	4.Gọi hàm max_heapify để duy trì tính chất của heap max.
*/
struct HeapNode* heap_extract_max(Heap H) {
	if (H->heap_size < 1)
		return NULL;
	/*Lưu giá trị lớn nhất*/
	struct HeapNode *max = malloc(sizeof(struct HeapNode)); //Cấp phát bộ nhớ cho nút mới và lưu trữ giá trị của phần tử gốc trong nút này.
	max->value = H->heap_array[1].value;
	/*Di chuyển giá trị của phần tử cuối cùng lên vị trí gốc và giảm kích thước của heap đi 1*/
	struct HeapNode tmp = H->heap_array[1];
	H->heap_array[1] = H->heap_array[H->heap_size];
	H->heap_array[H->heap_size] = tmp;
	H->heap_size--;
	max_heapify(H,1);
	return max; //Trả về con trỏ đến nút chứa giá trị lớn nhất đã được trích xuất
}


/*
Hàm này có nhiệm vụ tăng giá trị của một nút trong heap tối đa và sau đó điều chỉnh heap để duy trì tính chất của heap tối đa
Khi tăng giá trị của một nút, có thể cần phải đẩy giá trị này lên cây để đảm bảo rằng heap vẫn duy trì tính chất tối đa
*/
void heap_increase_key(Heap H, int i, int key) {
	/*Kiểm tra giá trị mới*/
	if (key < H->heap_array[i].value) { //Nếu giá trị mới 'key' nhỏ hơn giá trị hiện tại của nút, hàm in ra thông báo lỗi và thoát
		printf("The new value must be equal or greater than the node's current value!\n");
		return;
	}
	H->heap_array[i].value = key; // cập nhật giá trị của nút, gán giá trị cho nút tại vị trí 'i'
	/*Điều chỉnh heap để duy trì tính chất tối đa*/
	while (i>1 && H->heap_array[i].value > H->heap_array[i/2].value) { //duyệt từ nút vừa mới được cập nhật giá trị ('i') lên gốc của heap
		struct HeapNode tmp = H->heap_array[i]; //Nếu giá trị của nút hiện tại lớn hơn giá trị của nút cha thì hoán đổi hai nút này
		H->heap_array[i] =  H->heap_array[i/2];
		H->heap_array[i/2] = tmp;
		i = i/2; //Cập nhật 'i' để tiếp tục kiểm tra nút cha của nút hiện tại
	}
}


/*
Hàm này có nhiệm vụ thêm một phần tử mới vào heap max 
Sau đó điều chỉnh heap để duy trì tính chất của heap tối đa
Các bước:
	1.Tăng kích thước của heap
	2.Gán giá trị cực tiểu cho nút mới được thêm vào
	3.Gọi hàm 'heap_increase_key' để đặt giá trị đúng và duy trì tính chất heap max
*/
void heap_insert(Heap H, int key) {
	if (H->heap_size < H->length) { //Nếu kích thước hiện tại của heap nhỏ hơn chiều dài của mảng
		H->heap_size++; //Tăng kích thước của heap
		H->heap_array[H->heap_size].value = INT_MIN; //Đặt giá trị của phần tử mới thêm vào vị trí cuối cùng của heap là INT_MIN để đảm bảo nó nhỏ hơn mọi giá trị hợp lệ khác
		heap_increase_key(H,H->heap_size,key); //Gọi hàm này để tăng giá trị của nút mới lên giá trị 'key' va điều chỉnh heap
	} else { //Ngược lại
//		struct HeapNode newNode;
//		newNode.value = INT_MIN; //Tạo một nút mới với giá trị 'INT_MIN'
		H->heap_size++; //Tăng kích thước của heap
		H->length++; //Tăng chiều dài của mảng
		H->heap_array[H->heap_size].value = INT_MIN; //Thêm nút mới vào vị trí cuối cùng của heap
		heap_increase_key(H,H->heap_size,key); //Tăng giá trị của nút mới thêm lên giá trị 'key' và điều chỉnh heap
	}
}

int main() {
    int n;
    printf("Nhap chieu dai cua cay: ");
    scanf("%d", &n);
    
    Heap H = create_heap(n);
    if (H == NULL) {
        return 1; // Không thể tạo heap, thoát chương trình
    }
    
    printf("Nhap cac gia tri cua cay: ");
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        H->heap_array[i + 1].value = value;
        H->heap_size++;
    }

    build_max_heap(H);
    printf("Cay sau khi duoc xay dung la: ");
    show_heap(H, H->heap_size);

    int m;
    printf("Nhap so luong phan tu can them vao cay: ");
    scanf("%d", &m);
    for (int j = 0; j < m; j++) {
        int value;
        printf("Nhap gia tri can them: ");
        scanf("%d", &value);
        heap_insert(H, value);
    }

    printf("Cay sau khi duoc them vao la: ");
    show_heap(H, H->heap_size);

    free(H->heap_array);
    free(H);

//	Heap H = create_heap(10);
//	int data[] = {23,18,12,14,9,7,10,6,5,8};
//	for (int i = 0; i<10; i++) 
//		H->heap_array[i+1].value = data[i];
//	show_heap(H,H->heap_size);
//	heap_insert(H,20);
//	show_heap(H,H->length);
//	heap_insert(H,13);
//	show_heap(H,H->length);


	return 0;
}
