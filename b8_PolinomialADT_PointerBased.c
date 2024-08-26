#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int coeff;
    int expo;
    struct Node *next;
};

typedef struct Node *Polynomial;
typedef struct Node *Position;

Polynomial create_poly() {
    Polynomial poly = malloc(sizeof(struct Node));
    poly->next = NULL;
    poly->expo = INT_MAX;
    return poly;
}

void insert_poly(Polynomial poly, int coeff, int expo) {
    while (poly->next != NULL && poly->next->expo >= expo)
        poly = poly->next;
    if (poly->expo == expo) {
        poly->coeff += coeff;
    } else {
        Position newItem = malloc(sizeof(struct Node));
        newItem->coeff = coeff;
        newItem->expo = expo;
        newItem->next = poly->next;
        poly->next = newItem;
    }
}

void display(Polynomial poly) {
    poly = poly->next;
    while (poly != NULL) {
        printf(" %dx^%d ", poly->coeff, poly->expo);
        poly = poly->next;
    }
    printf("\n");
}

void input_poly(Polynomial poly) {
    int degree;
    printf("Enter the degree of the polynomial: ");
    scanf("%d", &degree);
    int *coefficients = (int *)malloc((degree + 1) * sizeof(int));
    printf("Enter coefficient: ");
    for (int i = degree; i >= 0; i--) {
        
        scanf("%d", &coefficients[i]);
    }
    for (int i = degree; i >= 0; i--) {
        if (coefficients[i] != 0) {
            insert_poly(poly, coefficients[i], i);
        }
    }
    free(coefficients);
}

void sum_poly(Polynomial poly1, Polynomial poly2, Polynomial poly_sum) {
    poly1 = poly1->next;
    poly2 = poly2->next;
    while (poly1 != NULL) {
        insert_poly(poly_sum, poly1->coeff, poly1->expo);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insert_poly(poly_sum, poly2->coeff, poly2->expo);
        poly2 = poly2->next;
    }
}

void multi_poly(Polynomial poly1, Polynomial poly2, Polynomial poly_prod) {
    poly1 = poly1->next;
    poly2 = poly2->next;
    Polynomial temp = poly2;
    while (poly1 != NULL) {
        while (poly2 != NULL) {
            insert_poly(poly_prod, poly1->coeff * poly2->coeff, poly1->expo + poly2->expo);
            poly2 = poly2->next;
        }
        poly1 = poly1->next;
        poly2 = temp;
    }
}

int main() {
    Polynomial poly1 = create_poly();
    Polynomial poly2 = create_poly();
    Polynomial poly_sum = create_poly();
    Polynomial poly_prod = create_poly();

    printf("Polynomial 1:\n");
    input_poly(poly1);
    printf("Polynomial 2:\n");
    input_poly(poly2);

    printf("Polynomial 1: ");
    display(poly1);
    printf("Polynomial 2: ");
    display(poly2);

    sum_poly(poly1, poly2, poly_sum);
    multi_poly(poly1, poly2, poly_prod);

    printf("SUM: ");
    display(poly_sum);
    printf("MULTIPLY: ");
    display(poly_prod);

    return 0;
}
