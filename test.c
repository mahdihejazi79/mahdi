#include<stdio.h>
#include<string.h>
#define N 1000

struct food
{
	char foodName[N];
	int foodPrice;
};

struct date
{
	int year;
	int month;
	int day;
};

struct order
{
	char foodName[N];
	struct date d;
};

void addFood()
{
	struct food f;
	
	printf("enter food name\n");
	scanf("%s",f.foodName);
	
	printf("enter food price\n");
	scanf("%d",&f.foodPrice);
	
	FILE *ptf;
	
	ptf=fopen("foods.txt","a");
	
	fprintf(ptf,"%s %d\n",f.foodName,f.foodPrice);
	
	fclose(ptf);
}

void sortFood()
{
	int i;
	struct food f[N];
	
	FILE *ptf;
	
	ptf=fopen("foods.txt","r");
	
	for(i=0;feof(ptf)==0;i++)
	fscanf(ptf,"%s %d",f[i].foodName,&f[i].foodPrice);
	
	fclose(ptf);
	
	for(int j=0;j<i-1;j++)
	for(int k=j+1;k<i;k++)
	{
		if(f[j].foodPrice>f[k].foodPrice)
		{
			struct food temp;
			temp=f[j];
			f[j]=f[k];
			f[k]=temp;
		}
	}
	
	ptf=fopen("foods.txt","w");
	
	for(int j=1;j<i;j++)
	fprintf(ptf,"%s %d\n",f[j].foodName,f[j].foodPrice);
	
	fclose(ptf);
}

void addOrder()
{
	int i,j;
	struct food f[N];
	static int income;
	struct order o;
	
	printf("enter customer name\n");
	scanf("%s",o.name);
	
	printf("enter food name\n");
	scanf("%s",o.foodName);
	
	printf("enter date:yyyy-mm-dd\n");
	scanf("%d-%d-%d",&o.d.year,&o.d.month,&o.d.day);

	FILE *ptf;
	
	ptf=fopen("foods.txt","r");
	
	for(i=0;feof(ptf)==0;i++)
	fscanf(ptf,"%s %d",f[i].foodName,&f[i].foodPrice);
	
	fclose(ptf);
	
	ptf=fopen("orders.txt","a");
	
	for(j=0;j<i;j++)
	if(strcmp(o.foodName,f[j].foodName)==0)
	{
		fprintf(ptf,"%s %s %d-%d-%d\n",o.name,o.foodName,o.d.year,o.d.month,o.d.day);
		income+=f[j].foodPrice;
		break;
	}
		
	fclose(ptf);
	
	if(j==i)
	printf("this food not found\n");
	
	printf("%d\n",income);	
}

int main()
{
	int choice;
	
	do
	{
		printf("1:addFood\n");
		printf("2:sortFood\n");
		printf("3:addOrder\n");
		printf("4:Exit\n\n");
		
		printf("enter your choice:");
		
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
			addFood();
			break;
			
			case 2:
			sortFood();
			break;
			
			case 3:
			addOrder();
			break;
			
			case 4:
			printf("\nExit\n");
		}
		printf("\n");
	}while (choice != 4);
}
