//Territory
//KingRmz

#include <stdio.h>
#include <stdlib.h>

//Global Variables
struct problems{
	char problem[200];
	char decision1[200];
	int effect1[3];
	char decision2[200];
	int effect2[3];
	int possibility; 
};
struct node{
	struct problems data;
	struct node *next;
};
struct node* head = NULL;
struct satisfaction
{
	int people;
	int court;
	int treasury;
};
char King[30];


//functions
struct node *create_node(struct problems info)    // creating new node of list
{
	struct node *nn;
	nn = (struct node *)malloc(sizeof(struct node));
	nn -> data = info;
	nn -> next = NULL;
	return nn;
} 
void readproblems()  //read all problems from the files that given(CHOICES.txt and "c*.txt")
{

	int i = 0;
	FILE *address,*choice;
	char choice_address[50];
	struct node *current = head;
	struct problems info;
	char test[200];
	address = fopen("CHOICES.txt","r+");
	if (address == NULL)
	{
		printf("cannot open file\n");
		return;
	} 
	while(!feof(address))
	{
		fscanf(address,"%s",choice_address);
		choice = fopen(choice_address,"r+");
		i++;
		fgets(info.problem,200,choice);
		fgets(info.decision1,200,choice);
		fscanf(choice,"%d%d%d",&info.effect1[0],&info.effect1[1],&info.effect1[2]);
		fgets(info.decision2,200,choice);
		fscanf(choice,"%d%d%d",&info.effect2[0],&info.effect2[1],&info.effect2[2]);
		info.possibility = 3;
		current = create_node(info);
		current = current -> next;
	}
	return;
}

int main()
{
	int menu;
	int numb;
	struct satisfaction city;
	printf("Enter your name:\n");
	scanf("%s",King);
	printf("1.New Game\n2.Load Save\n");
	scanf("%d",&menu);
	switch(menu)
	case 1:
	city.people = 50;
	city.court = 50;
	city.treasury = 50;
	readproblems();
//	printf("%s",head->data.problem);




}
