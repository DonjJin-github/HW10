#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

#define MAX_STACK_SIZE	20 //MAX_STACK_SIZE=20
Node* stack[MAX_STACK_SIZE]; //Node ������ ����ü stack[20]����
int top = -1; //top���� ������ -1 ����

Node* pop(); //Node ������ �Լ� pop����
void push(Node* aNode); //push�Լ� ����

#define MAX_QUEUE_SIZE	20 //MAX_QUEUE_SIZE=20
Node* queue[MAX_QUEUE_SIZE]; //Node ������ ����ü queue[20]����
int front = -1; //front ���� �� -1����
int rear = -1; //rear ���� �� -1 ����

Node* deQueue(); //Node ������ �Լ� deQueue����
void enQueue(Node* aNode); //enQueue�Լ� ����


int initializeBST(Node** h); //��带 �����Ҵ��Ͽ� �ʱ�ȭ �ϴ� �Լ�

void recursiveInorder(Node* ptr);//����� ������ȸ �Լ�
void iterativeInorder(Node* ptr);//�ݺ��� ������ȸ �Լ�
void levelOrder(Node* ptr);	//level order ������ȸ �Լ�
int insert(Node* head, int key);//��带 �����ϴ� �Լ�
int deleteNode(Node* head, int key);//��带 �����ϴ� �Լ�
int freeBST(Node* head); //�޸𸮸� �����ϴ� �Լ�

void printStack(); //printStack�Լ� ����



int main()
{
	printf("[----- [�ֵ���]  [2019038016] -----]\n"); 
	char command; //����ڿ��� �޴��� �Է¹��� ����
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); 

		switch(command) {//commad�� ���� ���� ����
		case 'z': case 'Z': //command�� z  or Z�϶�
			initializeBST(&head); //initailizeBST �Լ� ȣ��
			break;
		case 'q': case 'Q': //command�� q  or Q�϶�
			freeBST(head); //freeBST �Լ� ȣ��
			break;
		case 'i': case 'I': //command�� i or I�϶�
			printf("Your Key = "); 
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			insert(head, key); //key�� �����ϴ� insert�Լ� ȣ��
			break;
		case 'd': case 'D': //command�� d  or D�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key�� �Է¹޴´�
			deleteNode(head, key); //deleyeNode�� �����Ͽ� key�� ����
			break;

		case 'r': case 'R': //command�� r  or R�϶�
			recursiveInorder(head->left); //recursiveInorder�Լ��� ȣ���Ͽ� ����� ������ȸ 
			break;
		case 't': case 'T': //command�� t  or T�϶�
			iterativeInorder(head->left); //iterativeInorder�Լ��� ȣ���Ͽ� �ݺ��� ���ּ�ȸ
			break;

		case 'l': case 'L': //command�� t  or T�϶�
			levelOrder(head->left); //levelOrder�Լ��� ȣ���Ͽ� level order ������ȸ
			break;

		case 'p': case 'P': //command�� p  or P�϶�
			printStack(); //printStack�Լ� ȣ��
			break;

		default: //command�� ���� ����� �ٸ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q or Q�϶� �ݺ��� ����

	return 1; //�Լ� ����
}

int initializeBST(Node** h) {
	if(*h != NULL)//*h�� NULL�� �ƴϸ� �޸� ����
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //*h�� �����Ҵ��Ѵ�
	(*h)->left = NULL;	//h�� ��� ����ü left�� NULL����
	(*h)->right = *h; //h�� ��� ����ü right�� *h ����
	(*h)->key = -9999; //h�� ������� key�� -9999����

	top = -1; //top�� -1����

	front = rear = -1; //front,rear�� -1����

	return 1; //�Լ�����
}



void recursiveInorder(Node* ptr)
{
	if(ptr) { //���ȣ���� ���� ��带 ���ʳ��->�Ѹ�-> ������ ��� ������ ����Ѵ�
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

void iterativeInorder(Node* node)
{
	for(;;) //�ݺ����� ����Ͽ� node�� ���ʳ��->�Ѹ�->������ ��� ������ ���
	{
		for(; node; node = node->left)
			push(node);
		node = pop();

		if(!node) break;
		printf(" [%d] ", node->key);

		node = node->right;
	}
}

void levelOrder(Node* ptr)
{

	if(!ptr) return; //tree�� ��������� �Լ� ����

	enQueue(ptr); //enQueue�Լ��� ȣ���Ͽ� ptr �߰�

	for(;;)
	{
		ptr = deQueue(); //ptr�� deQueue()����
		if(ptr) { //��带 ������ ���� ���ʳ�� ������ ��� ������ ����Ѵ�
			printf(" [%d] ", ptr->key);

			if(ptr->left)
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break; 

	}

}


int insert(Node* head, int key) //��带 �����ϴ� �Լ�
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //Node����ü ������ newNode ������ �����Ҵ�
	newNode->key = key; //newNode�� key�� �Ű�����key�� ����
	newNode->left = NULL; //newNode�� left�� NULL����
	newNode->right = NULL; //newNode�� right�� NULL����

	if (head->left == NULL) { //head�� left�� NULL�̸�
		head->left = newNode; //head�� left�� newNode����
		return 1; //�Լ� ����
	}

	Node* ptr = head->left; //Node ����ü ������ ptr�� head�� left����

	Node* parentNode = NULL; //Node ����ü ������ parentNode�� NULL����
	while(ptr != NULL) { //ptr�� key�� �Ű����� key�� ������ �Լ� ����

		if(ptr->key == key) return 1; //ptr�� key�� �Ű����� key�� ������ �Լ� ����

		parentNode = ptr; //�θ��忡 ptr ����

		if(ptr->key < key) //ptr�� key���� �Ű����� key�� �� Ŭ��
			ptr = ptr->right; //ptr�� ptr�� right����
		else
			ptr = ptr->left; //ptr�� ptr�� left����
	}

	if(parentNode->key > key) //�θ����� key���� key���� Ŭ��
		parentNode->left = newNode; //�θ����� left�� newNode ����
	else
		parentNode->right = newNode; //�θ����� right�� newNode ����
	return 1;//�Լ�����
}


int deleteNode(Node* head, int key) //��带 �����ϴ� �Լ�
{
	if (head == NULL) { //head�� NULL�϶�
		printf("\n Nothing to delete!!\n"); //�����Ұ��� ����
		return -1; //�Լ�����
	}

	if (head->left == NULL) { //head�� left�� NULL�϶�
		printf("\n Nothing to delete!!\n"); // �����Ұ��� ����
		return -1;//�Լ�����
	}

	Node* root = head->left;//Node����ü ������ root ���� �� head�� left����



	Node* parent = NULL; //Node ����ü ������ parent�� NULL����
	Node* ptr = root; //Node ����ü ������ ptr�� root����

	while((ptr != NULL)&&(ptr->key != key)) { //ptr�� NULL�� �ƴϰų� key�� key�� �ƴҶ�
		if(ptr->key != key) { //ptr�� key���� key���� �ƴҶ�

			parent = ptr;	//parent�� ptr����

			if(ptr->key > key) //ptr�� key���� key������ Ŭ��
				ptr = ptr->left; //ptr�� ptr�� left����
			else
				ptr = ptr->right; //ptr�� ptr�� right����
		}
	}

	if(ptr == NULL) //ptr�� NULL�϶�
	{
		printf("No node for key [%d]\n ", key); //�����Ұ��� ����
		return -1;
	}

	if(ptr->left == NULL && ptr->right == NULL) //ptr��left�� NULL�� �ƴϰų� ptr��right�� NULL�� �ƴҶ�
	{
		if(parent != NULL) { //parent�� NULL�� �ƴϸ�
			if(parent->left == ptr) //parent�� left�� ptr�� ������
				parent->left = NULL; //parent�� left�� NULL����
			else
				parent->right = NULL; //parent�� right�� NULL����
		} else {
			head->left = NULL; //head�� left�� NULL����

		}

		free(ptr); //ptr�޸� ����
		return 1; //�Լ� ����
	}

	if ((ptr->left == NULL || ptr->right == NULL)) //ptr�� left�� NULL�̰� ptr�� right�� NULL�϶�
	{
		Node* child; //Node ������ ����ü child ����
		if (ptr->left != NULL) //ptr�� left�� NULL�� �ƴҶ�
			child = ptr->left; //child�� ptr�� left����
		else
			child = ptr->right; //child�� ptr�� right����

		if(parent != NULL) //parent�� NULL�� �ƴҶ�
		{
			if(parent->left == ptr) //parent�� left�� ptr�� ������
				parent->left = child; //parent�� left�� child ����
			else
				parent->right = child; //parent�� right�� child ����
		} else {
			root = child; //root�� child ����
		}

		free(ptr); //ptr�޸� ����
		return 1; //�Լ�����
	}

	Node* candidate; //Node ������ ����ü candidate ����
	parent = ptr; //parent�� ptr ����


	candidate = ptr->right; //candidate�� ptr�� right ����

	while(candidate->left != NULL) //candidate�� left�� NULL�϶� ���� �ݺ�
	{
		parent = candidate; //parent�� candidate����
		candidate = candidate->left;//candidate�� candidate�� left ����
	}


	if (parent->right == candidate) //parent�� right�� candidate�� ������
		parent->right = candidate->right; //parent�� right�� candidate�� right����
	else
		parent->left = candidate->right; //parent�� left�� candidate�� right����

	ptr->key = candidate->key;//ptr�� key�� candidate�� key ����

	free(candidate); //candidate�޸� ����
	return 1; //�Լ� ����
}


void freeNode(Node* ptr) 
{
	if(ptr) { //���ʳ��, �����ʳ�� �Ѹ��� �޸� �����ϴ� �Լ�
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head) 
{

	if(head->left == head) //head�� left�� head�� ������
	{
		free(head); //head �޸�����
		return 1; //�Լ�����
	}

	Node* p = head->left;  //Node ������ ����ü p���� �� head�� left�� ����

	freeNode(p); //p �޸�����

	free(head); //head �޸�����
	return 1; //�Լ�����
}



Node* pop()
{
	if (top < 0) return NULL; //top�� ������ NULL ����
	return stack[top--]; //stack[top--]����
}

void push(Node* aNode)
{
	stack[++top] = aNode; //stack[++top]�� aNode ����
}


void printStack()
{
	int i = 0; 
	printf("--- stack ---\n");
	while(i <= top) //�ݺ����� ����Ͽ� stack ���
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue() 
{
	if (front == rear) { //front�� rear�� ������
		return NULL; //NULL ����
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front�� (front + 1) % 20����
	return queue[front]; // queue[front]����

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear�� (rear + 1) % 20 ����
	if (front == rear) { //����������
		return; //�Լ� ����
	}

	queue[rear] = aNode; //queue[rear] �� aNode����
}





