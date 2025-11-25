#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};
void push(struct node *top, int data)
{
	struct node *p;
	p = (struct node *) malloc(sizeof(struct node));
	if(p == NULL)
	{
		perror("malloc");
		exit(1);
	}
	p -> data = data;
	p->next = top;
	top = p;
}
int pop(struct node *top)
{
	struct node *p =top->next;
	printf("%d\n",p->data);
}
int main() {
	int data;
	struct node *p, *head = NULL;
	while(scanf("%d",&data)==1&& data>0 )
	{
		push(head,data);
	}
	printf("print stack\n");
	p=head;
	while(p!=NULL)
	{
		pop(head);
		p = head->next;
	}
	exit(0);
}
