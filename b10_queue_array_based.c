#include <stdio.h>

/*Khai báo cấu trúc cây*/
struct TreeNodeRecord {
	int key;
	struct TreeNodeRecord *left;
	struct TreeNodeRecord *right;
	struct TreeNodeRecord *parent;
};

typedef struct TreeNodeRecord *TreeNode;
typedef struct TreeNodeRecord *BST;

/*Duyệt cây theo thứ tự trước*/
void preorder_traversal(BST T) {
	if (T!=NULL) {
		printf("%d ",T->key);
		preorder_traversal(T->left);
		preorder_traversal(T->right);
	}
}

/*Duyệt cây theo thứ tự giữa*/
void inorder_traversal(BST T) {
	if (T!=NULL) {		
		inorder_traversal(T->left);
		printf("%d ",T->key);
		inorder_traversal(T->right);
	}
}

/*Duyệt cây theo thứ tự sau*/
void postorder_traversal(BST T) {
	if (T!=NULL) {		
		postorder_traversal(T->left);		
		postorder_traversal(T->right);
		printf("%d ",T->key);
	}
}

/*Tìm kiếm một giá trị trong cây*/
TreeNode tree_search(BST T,int key) {
	if (T == NULL || T->key == key)
		return T;
	else {
		if (key<T->key)
			return tree_search(T->left,key);
		else
			return tree_search(T->right,key);
	}
}

/*Tìm kiếm phần tử nhỏ nhất trong cây*/
TreeNode tree_minimum(BST T) {
	if (T == NULL) {
		printf("The tree is empty!\n");
		return NULL;
	}
	while (T->left!=NULL)
		T = T->left;
	return T;
}

/*Tìm kiếm phần tử lớn nhất trong cây*/
TreeNode tree_maximum(BST T) {
	if (T == NULL) {
		printf("The tree is empty!\n");
		return NULL;
	}
	while (T->right!=NULL)
		T = T->right;
	return T;
}

/*Tìm kiếm phần tử kế tiếp của một nút trong cây*/
TreeNode tree_successor(TreeNode x){
	if (x->right != NULL)
		return tree_minimum(x->right);
	TreeNode y = x->parent;
	while (y!=NULL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;		
}

/*Chèn một giá trị mới vào cây*/
void tree_insert(BST *T, int key) {
	TreeNode newNode = malloc(sizeof(struct TreeNodeRecord));
	newNode->key = key; 
	newNode->left = NULL; 
	newNode->right = NULL;
	
	TreeNode y = NULL;
	TreeNode x = *T;
	while (x!=NULL) {
		y = x;
		if (newNode->key < x->key)
			x = x->left;
		else 
			x = x->right;
	}
	newNode->parent = y;
	if (y == NULL)
	{
		*T = newNode;
	} else {
		if (newNode->key>y->key)
			y->right = newNode;
		else
			y->left = newNode;	
	}
}

int main() {	
	int n;
	printf("Nhap so luong phan tu cua cay: ");
	scanf("%d", &n);
	BST T = NULL;
	int tree_data[n];
	printf("Nhap cac gia tri cua cay: ");
	for (int i=0;i<n;i++)
		scanf("%d ", &tree_data[i]);
	for (int i=0;i<n;i++)
		tree_insert(&T,tree_data[i]);
	
	printf("Preorder travesal: ");
	preorder_traversal(T);
	printf("\nInorder travesal: ");
	inorder_traversal(T);
	printf("\nPostorder travesal: ");
	postorder_traversal(T);
	TreeNode result;
	result = tree_search(T,4);
	if (result != NULL) 
		printf("\n%d found!",result->key);
	else
		printf("\nNot found!");
	result = tree_minimum(T);
	printf("\nTree min: %d",result->key);
	result = tree_maximum(T);
	printf("\nTree max: %d",result->key);
	TreeNode t_node = tree_search(T,4);
	result  = tree_successor(t_node);
	if (result!=NULL)
		printf("\nSuccessor of %d is %d",t_node->key,result->key);
	else
		printf("\nNode %d does not have a successor!",t_node->key);

	return 0;
}
