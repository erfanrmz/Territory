//Territory
//KingRmz

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
void create_node(struct problems info)    // creating new node of list
{
	struct node *temp;
	temp = (struct node *)malloc(sizeof(struct node));
	temp -> data = info;
	temp -> next = NULL;
	if (head == NULL)
	{
		head = temp;
	}
	else 
	{
		struct node *current = head;
		while (current->next != NULL)
			current = current -> next;
		current -> next = temp;
	}
	
	
} 
int random_problem() // find the problem that want to show
{
	int total = 0;
	int random,r = 0,numb = 0;
	struct node *current = head;
	while (current -> next != NULL)
	{
		total += current -> data.possibility;
		current = current -> next;
	}
	time_t t = time(NULL);
	srand(t);
	random = rand();
	random %= total;
	random += 1;
	current = head;
	while ((r) < random)
	{
		numb++;
		r += current -> data.possibility;
		current = current -> next;
	}
	return numb;

}
void readproblems()  //read all problems from the files that given(CHOICES.txt and "c*.txt")
{

	int i = 0;
	FILE *address,*choice;
	char choice_address[50];
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
		fgets(info.decision2,200,choice);
//		printf("%s",info.decision2);
		fscanf(choice,"%d%d%d",&info.effect2[0],&info.effect2[1],&info.effect2[2]);
		info.possibility = 3;
		create_node(info);
		fclose(choice);
	}
	fclose(address);

	return;
}
void showproblem (int numb)
{
	struct node *current = head;
	while (numb > 0)
	{
		current = current->next;
		numb--;
	}
	printf("%s\n",current -> data.problem);
	printf("1-%s",current -> data.decision1);
	printf("2-%s",current -> data.decision2);

}
void answer_decision1 (int numb , int *people , int *court , int *treasury)
{
	struct node *current = head;
	while (numb > 0)
	{
		current = current->next;
		numb--;
	}
	*people += (current -> data.effect1[0]);
	*court += (current -> data.effect1[1]);
	*treasury += (current -> data.effect1[2]);
	current -> data.possibility--;
}
void answer_decision2 (int numb , int *people , int *court , int *treasury)
{
	struct node *current = head;
	while (numb > 0)
	{
		current = current->next;
		numb--;
	}
	*people += (current -> data.effect2[0]);
	*court += (current -> data.effect2[1]);
	*treasury += (current -> data.effect2[2]);
	current -> data.possibility--;
}

int main()
{
	int menu,answer,numb;
	char save_choice;
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
	numb = 0;
	while (1)
	{	
		printf("People : %d Court : %d Treasury : %d\n",city.people,city.court,city.treasury);
		numb = random_problem() - 1;
		showproblem(numb);
		scanf("%d",&answer);
		switch(answer)
		{
		case 0:
			printf("Do you want to save your game ?[Y/N]\n");
			scanf(" %c",&save_choice);
			if (save_choice == 'y' || save_choice == 'Y')
			{
//				savegame();
				printf("Your game has been saved,B-Bye\n");

			}
			else if (save_choice == 'n' || save_choice == 'N')
				printf("OK , GoodBye\n");
			return 0;
			break;
		case 1:
			answer_decision1(numb,&city.people,&city.court,&city.treasury);
			break;
		case 2:
			answer_decision2(numb,&city.people,&city.court,&city.treasury);
			break;
		}	
	}
	
	




}
