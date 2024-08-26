/*
CÁC HOẠT ĐỘNG CƠ BẢN LIÊN QUAN ĐẾN ĐA THỨC: KHỞI TẠO; TÍNH TỔNG, TÍCH VÀ HIỂN THỊ ĐA THỨC
*/

#include <stdio.h>

#define MAX_DEGREE 100

//Định nghĩa một đa thức bao gồm hệ số mảng và một chỉ số cao nhất
struct polynomial {
	unsigned int high_power;
	int coeff_array[MAX_DEGREE+1];
};

typedef struct polynomial *POLYNOMIAL;

//Đặt tất cả các hệ số thành 0 và chỉ cập nhật chỉ số cao nhất
void zero_polynomial(POLYNOMIAL poly){
	poly->high_power = 0;
	for (int i = 0;i<=MAX_DEGREE;i++)
		poly->coeff_array[i] = 0;
}

//Trả về giá trị lớn nhất giữa hai số
unsigned int max(unsigned int a, unsigned int b){
	return a>b?a:b;
}

//Tính tổng của hai đa thức và lưu kết quả vào một đa thức mới ("poly_sum")
//Đa thức tổng có chỉ số cao nhất bằng chỉ số cao nhất của hai đa thức gốc
void sum_polynomial(POLYNOMIAL poly1, POLYNOMIAL poly2, POLYNOMIAL poly_sum){
	zero_polynomial(poly_sum);
	poly_sum->high_power = max(poly1->high_power,poly2->high_power); 
	for (int i=0;i<=poly_sum->high_power;i++)
		poly_sum->coeff_array[i] = poly1->coeff_array[i]+poly2->coeff_array[i];
}

//Tính tích của hai đa thức và lưu kết quả vào một đa thức mới ("poly_prod")
//Đa thức có chỉ số cao nhất là tổng của chỉ số cao nhất của hai đa thức gốc
void mult_polynomial(POLYNOMIAL poly1, POLYNOMIAL poly2, POLYNOMIAL poly_prod){
	zero_polynomial(poly_prod);
	poly_prod->high_power = poly1->high_power+poly2->high_power;
	for (int i=0;i<=poly1->high_power;i++)
		for (int j=0;j<=poly2->high_power;j++)
			poly_prod->coeff_array[i+j] += poly1->coeff_array[i]*poly2->coeff_array[j];
}

//Hiển thị đa thức ra màn hình dưới dạng chuỗi
//Duyệt qua các hệ số của đa thức từ cao xuống thấp và hiển thị chúng kèm với biến x và mũ tương ứng
void display_polynomial(POLYNOMIAL poly){
	for (int i=poly->high_power;i>=0;i--){		
		if (poly->coeff_array[i]==0)
			continue;
		if (poly->coeff_array[i]<0){
			if (i!=poly->high_power)
				printf(" - ");
			else
				printf("-");
		} else {
			if (i!=poly->high_power)
				printf(" + ");
		}
		
		if (abs(poly->coeff_array[i])!=1)
			printf("%d",abs(poly->coeff_array[i]));
		if (i!=0)
			printf("x");
		if (i>1)
			printf("^%d",i);
	}
	printf("\n");
}

int main(){
	POLYNOMIAL poly1 = malloc(sizeof(struct polynomial));
	POLYNOMIAL poly2 = malloc(sizeof(struct polynomial));	
	POLYNOMIAL poly_sum = malloc(sizeof(struct polynomial));
	POLYNOMIAL poly_prod = malloc(sizeof(struct polynomial));
	
	zero_polynomial(poly1);
	zero_polynomial(poly2);
	
	poly1->high_power = 3;
	poly1->coeff_array[0] = 7; poly1->coeff_array[1] = 0;
	poly1->coeff_array[2] = 4; poly1->coeff_array[3] = 10;
	
	poly2->high_power = 2;
	poly2->coeff_array[0] = 5; poly2->coeff_array[1] = -6;
	poly2->coeff_array[2] = -1;
	
	display_polynomial(poly1);
	display_polynomial(poly2);
	
	sum_polynomial(poly1,poly2,poly_sum);
	mult_polynomial(poly1,poly2,poly_prod);
	
	printf("SUM:");
	display_polynomial(poly_sum);
	printf("MULTIPLY:");
	display_polynomial(poly_prod);
	
	return 0;
}
