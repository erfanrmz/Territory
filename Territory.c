//Territory
//KingRmz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Global Variables
struct problems{
	char problem[200];
	char decision1[200];
	char decision2[200];
	int effect1[3];
	int effect2[3];
	int possibility; 
	int code;
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
struct saveinfo{
	char king_name[30];
	int condition_save;
	int people_save;
	int court_save;
	int treasury_save;
	int problems_number_save;
	int problems_possibility_save[100];

};
char King[30];
int condition = 1;
int problems_possibility[100];
int problems_number = 0;
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
void delete_node(int numb) //deleting a node from list
{
	if(numb == 0)
	{
		struct node *temp = head;
		temp = head;
		head = temp -> next;
		temp -> next = NULL;
		free(temp);
	}
	else
	{
		struct node *p = head , *q;
		int i = 1;
		while (i < numb)
		{
			p = p -> next;
			i++;
		}
		q = p -> next;
		p -> next = q -> next;
		q -> next = NULL;
		free(q);

	}

}
void delete_node_load() //deleting the problems with zero possibility
{
	int i = 0;
	struct node *current = head;
	while (current != NULL)
	{
		if (current -> data.possibility == 0)
		{
			delete_node(i);
			return;
		}
		current = current -> next;
		i++;
	}
}
int random_problem() // find the problem that want to show
{
	int total = 0 , random , r = 0 , numb = 0;
	struct node *current = head;
	while (current != NULL)
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

	FILE *address,*choice;
	char choice_address[200];
	char choice_address1[200];
	struct problems info;
	address = fopen("problems/CHOICES.txt","r+");
	if (address == NULL)
	{
		printf("cannot open file\n");
		return;
	} 
	while(!feof(address))
	{
		strcpy(choice_address,"problems/");
		fscanf(address,"%s",choice_address1);
		strcat(choice_address,choice_address1);
		choice = fopen(choice_address,"r+");
		problems_number++;
		fgets(info.problem,200,choice);
		fgets(info.decision1,200,choice);
		fscanf(choice,"%d%d%d",&info.effect1[0],&info.effect1[1],&info.effect1[2]);
		fgets(info.decision2,200,choice);
		fgets(info.decision2,200,choice);
		fscanf(choice,"%d%d%d",&info.effect2[0],&info.effect2[1],&info.effect2[2]);
		info.possibility = 3;
		info.code = problems_number-1;
		problems_possibility[info.code] = 3;
		create_node(info);
		fclose(choice);
	}
	fclose(address);

	return;
}
void showproblem (int numb) // show the problem
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
void answer_decision1 (int numb , int *people , int *court , int *treasury) //if answer is decision one 
{
	int i = numb;
	struct node *current = head;
	while (i > 0)
	{
		current = current->next;
		i--;
	}
	*people += (current -> data.effect1[0]);
	*court += (current -> data.effect1[1]);
	*treasury += (current -> data.effect1[2]);
	if (*people < 0)
		*people = 0;
	if (*court < 0)
		*court = 0;
	if (*treasury < 0)
		*treasury = 0;
	if (*people > 100)
		*people = 100;
	if (*court > 100)
		*court = 100;
	if (*treasury > 100)
		*treasury = 100;
	current -> data.possibility--;
	problems_possibility[current -> data.code]--;
	if (current -> data.possibility == 0)
		delete_node(numb);
}
void answer_decision2 (int numb , int *people , int *court , int *treasury) //if answer is decision second
{
	int i = numb;
	struct node *current = head;
	while (i > 0)
	{
		current = current->next;
		i--;
	}
	*people += (current -> data.effect2[0]);
	*court += (current -> data.effect2[1]);
	*treasury += (current -> data.effect2[2]);
	if (*people < 0)
		*people = 0;
	if (*court < 0)
		*court = 0;
	if (*treasury < 0)
		*treasury = 0;
	if (*people > 100)
		*people = 100;
	if (*court > 100)
		*court = 100;
	if (*treasury > 100)
		*treasury = 100;
	current -> data.possibility--;
	problems_possibility[current -> data.code]--;
	if (current -> data.possibility == 0)
		delete_node(numb);
}
int check_condition(int *people , int *court , int *treasury) //check failing
{
	int avrg = (*people + *court + *treasury)/3;
	if (*people == 0 || *court < 0 || *treasury == 0 || avrg < 10)
		return 0;
	return 1;
}
void savegame(int *people , int *court , int *treasury) // save the game in a binary file
{
	struct saveinfo save;
	char saveinfo_adress[200];
	FILE *saves , *info;
	saves = fopen("saves/saves_name.txt","a+");
	fprintf(saves,"%s\n",King);
	fclose(saves);
	save.condition_save = condition;
	save.people_save = *people;
	save.court_save = *court;
	save.treasury_save = *treasury;
	save.problems_number_save = problems_number;
	for (int i = 0 ; i < problems_number ; i++)
		save.problems_possibility_save[i] = problems_possibility[i];
	strcpy(save.king_name,King);
	strcpy(saveinfo_adress,"saves/");
	strcat(saveinfo_adress,save.king_name);
	strcat(saveinfo_adress,".bin");
	info = fopen(saveinfo_adress,"w");
	if (info == NULL)
	{
		printf("cant save. name is unavailbe\n");
		return;
	}
	fwrite(&save, sizeof(struct saveinfo), 1, info);
	fclose(info);
}
void showsaves() // show saves list
{
	int number = 1;
	FILE *saves;
	saves = fopen("saves/saves_name.txt","r+");
	if (saves == NULL)
	{
		printf("no saves available\nrestart for new game");
		return;
	}
	while(!feof(saves))
	{
	char save_nameshow[200];
	fscanf(saves,"%s ",save_nameshow);
	printf("%d.%s\n",number,save_nameshow);
	number++;
	}
}
void loadgame(int choose , int *people , int *court , int *treasury) // read information from the saved file
{
	int i = choose;
	FILE *load;
	char load_address[200],load_address1[200];
	struct saveinfo loadinfo;
	struct node *current = head;
	load = fopen("saves/saves_name.txt","r+");
	while (i > 0)
	{
		fscanf(load,"%s ",load_address1);
		i--;
	}
	fclose(load);
	strcpy(load_address,"saves/");
	strcat(load_address,load_address1);
	strcat(load_address,".bin");
	load = fopen(load_address,"r+");
	fread(&loadinfo,sizeof(struct saveinfo),1,load);
	fclose(load);
	*people = loadinfo.people_save;
	*court = loadinfo.court_save;
	*treasury = loadinfo.treasury_save;
	strcpy(King,loadinfo.king_name);
	condition = loadinfo.condition_save;
	problems_number = loadinfo.problems_number_save;
	for (int i = 0 ; i < loadinfo.problems_number_save ; i++)
	{
		problems_possibility[i] = loadinfo.problems_possibility_save[i];
		current -> data.possibility = problems_possibility[i]; 
		current = current -> next;
	}

}
void shownode() //showing list for testing code
{
	struct node *current = head;
	while(current != NULL)
	{
		printf("%s %d \n",current->data.problem,current -> data.possibility);
		current = current -> next;
	}
}
int main()
{
	int menu,answer,numb,choose_load;
	char save_choice;
	struct satisfaction city;
	
	printf("1.New Game\n2.Load Save\n");
	scanf("%d",&menu);
	switch(menu)
	{
	case 1:
		printf("Enter your name:\n");
		scanf("%s",King);
		city.people = 50;
		city.court = 50;
		city.treasury = 50;
		readproblems();
		numb = 0;
		while (1)
		{
			condition = check_condition(&city.people,&city.court,&city.treasury);
			if (head == NULL)
			{
				readproblems();	
			}
			printf("People : %d Court : %d Treasury : %d\n",city.people,city.court,city.treasury);
			if (condition == 0)
			{
				printf("You Lost.\nDo you want to save your game ?[Y/N]\n");
				scanf(" %c",&save_choice);
				if (save_choice == 'y' || save_choice == 'Y')
				{
					savegame(&city.people,&city.court,&city.treasury);
					printf("Your game has been saved,B-Bye\n");
				}
				else if (save_choice == 'n' || save_choice == 'N')
				{
					printf("OK , GoodBye\n");
					
				}
				return 0;
			}
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
					savegame(&city.people,&city.court,&city.treasury);
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
		break;
	case 2:
		readproblems();
		showsaves();
		printf("choose your save\n");
		scanf("%d",&choose_load);
		loadgame(choose_load,&city.people,&city.court,&city.treasury);
		numb = 0;
		if (condition == 0)
		{
			city.people = 50;
			city.court = 50;
			city.treasury = 50;
			readproblems();
			while (1)
			{
				condition = check_condition(&city.people,&city.court,&city.treasury);
				if (head == NULL)
				{
					readproblems();	
				}
				printf("People : %d Court : %d Treasury : %d\n",city.people,city.court,city.treasury);
				if (condition == 0)
				{
					printf("You Lost.\nDo you want to save your game ?[Y/N]\n");
					scanf(" %c",&save_choice);
					if (save_choice == 'y' || save_choice == 'Y')
					{
						savegame(&city.people,&city.court,&city.treasury);
						printf("Your game has been saved,B-Bye\n");
					}
					else if (save_choice == 'n' || save_choice == 'N')
					{
						printf("OK , GoodBye\n");
						
					}
					return 0;
				}
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
						savegame(&city.people,&city.court,&city.treasury);
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
		else if (condition == 1)
		{

			for (int i = 0 ; i < problems_number ; i++)
					delete_node_load();
			while (1)
			{
				condition = check_condition(&city.people,&city.court,&city.treasury);
				if (head == NULL)
				{
					readproblems();	
				}
				printf("People : %d Court : %d Treasury : %d\n",city.people,city.court,city.treasury);
				if (condition == 0)
				{
					printf("You Lost.\nDo you want to save your game ?[Y/N]\n");
					scanf(" %c",&save_choice);
					if (save_choice == 'y' || save_choice == 'Y')
					{
						savegame(&city.people,&city.court,&city.treasury);
						printf("Your game has been saved,B-Bye\n");
					}
					else if (save_choice == 'n' || save_choice == 'N')
					{
						printf("OK , GoodBye\n");
						
					}
					return 0;
				}
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
						savegame(&city.people,&city.court,&city.treasury);
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
		break;	
	}
	
}
