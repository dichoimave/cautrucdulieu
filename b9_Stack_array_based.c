#include <stdio.h>
#include <stdlib.h>

#define EMPTY_POS -1
#define MIN_SIZE 5
#define EMPTY_VALUE -1000000

struct elementType {
    int value;    
};

struct stackRecord {
    unsigned int capacity;    
    int tos;                
    struct elementType *stack_array; 
};

typedef struct stackRecord *stack;

int is_empty(stack s) {        
    return s->tos == EMPTY_POS;
}

int is_full(stack s) {
    return s->tos == s->capacity - 1;
}

void make_null(stack s) {
    s->tos = EMPTY_POS;
}

void dispose(stack s) {    
    if (s != NULL) {
        free(s->stack_array);
        free(s);
    }
}

stack create_stack(unsigned int capacity) {
    if (capacity < MIN_SIZE) {
        printf("Dung lượng ngăn xếp ít nhất là %d\n", MIN_SIZE);
    }
    stack s = malloc(sizeof(struct stackRecord));
    if (s == NULL) {
        printf("Không đủ bộ nhớ\n");
        return NULL;
    } 
    s->stack_array = malloc(sizeof(struct elementType) * capacity);
    if (s->stack_array == NULL) {
        printf("Không đủ bộ nhớ\n");
        free(s);
        return NULL;
    } 
    s->capacity = capacity;
    s->tos = EMPTY_POS;
    return s;
}

void push(stack s, struct elementType e) {    
    if (is_full(s)) {
        printf("Ngăn xếp đã đầy\n");
        return;
    }
    s->stack_array[++s->tos] = e;
}

struct elementType pop(stack s) {    
    if (is_empty(s)) {        
        printf("Ngăn xếp rỗng\n");
        struct elementType e;
        e.value = EMPTY_VALUE;
        return e;
    }
    return s->stack_array[s->tos--];
}

struct elementType top(stack s) {    
    if (is_empty(s)) {    
        printf("Ngăn xếp rỗng\n");
        struct elementType e;
        e.value = EMPTY_VALUE;
        return e;
    }
    return s->stack_array[s->tos];
}

void show_stack(stack s) {
    if (is_empty(s)) {
        printf("Ngan xep rong\n");
        return;
    }
    for (int i = s->tos; i > EMPTY_POS; i--) {
        printf("%d ", s->stack_array[i].value);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);
    struct elementType *arr = malloc(sizeof(struct elementType) * n);
    printf("Nhap cac gia tri: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i].value);
    }
    stack s = create_stack(n + 1);
    for (int i = 0; i < n; i++) {
        push(s, arr[i]);
    }
    printf("Mang sau nhap la: ");
    show_stack(s);

    int m;
    printf("Nhap so luong phan tu can xoa: ");
    scanf("%d", &m);
    struct elementType *b = malloc(sizeof(struct elementType) * m);
    printf("Nhap cac gia tri can xoa: ");
    for (int j = 0; j < m; j++) {
        scanf("%d", &b[j].value);
    }
    for (int i = 0; i < m; i++) {
        int found = 0;
        for (int j = 0; j < n; j++) {
            if (b[i].value == arr[j].value) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("So %d khong co trong day so!\n", b[i]);
        } else {
            struct elementType e;
            do {
                e = pop(s);
            } while (e.value == b[i].value && e.value != EMPTY_VALUE);
        }
    }

    printf("Mang sau xoa la: ");
    show_stack(s);
//	struct elementType e,e1,e2,e3,e4;
//	e1.value = 5; e2.value = 7; e3.value = -19; e4.value = 17;
//	stack s = create_stack(100);
//	push(s,e1);	push(s,e2);	push(s,e3); push(s,e4);
//	show_stack(s);
//	e=pop(s); e=pop(s);e=pop(s);
//	printf("e = %d\n",e.value);
//	show_stack(s);
    free(arr);
    free(b);
    dispose(s);

    return 0;    
}
