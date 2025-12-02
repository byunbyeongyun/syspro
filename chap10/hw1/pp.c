#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};
void push(struct node **top, int data)
{
	struct node *p;
	p = (struct node *) malloc(sizeof(struct node));
	if(p == NULL)
	{
		perror("malloc");
		exit(1);
	}
	p -> data = data;
	p->next = *top;
	*top = p;
}
int pop(struct node **top)
{
	struct node *p =top;
	int popped_data = p->data;
	*top = p->next;
	printf("%d\n", popped_data);
	free(p);
	return popped_data;
}
int main() {
	int data;
	struct node *head = NULL;
	while(1)
	{
		int scan_result = scanf("%d",&data);
		if(scan_result != 1) {
			while(getchar() != '\n');
			break;
		}
		if(data<=0) break;

		push(&head,data);
	}
	printf("print stack\n");
	
	while(head !=NULL)
	{
		pop(&head);
	}
	exit(0);
}
