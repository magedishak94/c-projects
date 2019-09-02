#include <stdio.h>
#include <stdlib.h>
#include "StdTypes.h"
#include <string.h>
#define PASSWORD 1234
typedef struct node*nodep;
struct node{
	char name[20];
	u8 age;
	u8 gender;
	u8 id;
	nodep next;
};
struct slot{
	char time[14];
	nodep patient;
};
nodep head=NULL;
void addnode(void);
void editrec(void);
void printll(void);//not used
void getdata(nodep);
void reserveslot(struct slot*p);
void cancelres(struct slot*p);
void viewrec(void);
void viewreservation(struct slot*p);
void main(void){
	struct slot slots[5]={{"2pm to 2:30pm",NULL},{"2:30pm to 3pm",NULL},{"3pm to 3:30pm",NULL},{"4pm to 4:30pm",NULL}
		,{"4:30pm to 5pm",NULL}
	};
	u8 main=0,admin=0,user=0,i;
	u16 pass;
	
	printf("Welcome to your clinic\n\n");
	while(main!=3)
	{
		printf("====>for ADMIN press :1\n");
		printf("====>for USER press : 2\n");
		printf("====>to exit press :  3\n");
		scanf("%d",&main);
		switch(main){
			case 1:printf("enter password :");
	               scanf("%d",&pass);
				   for(i=0;i<2;i++)
				   {
					   if(pass==PASSWORD)break;
					   else{
						   printf("wrong password try again:");
						   scanf("%d",&pass);
					   }
				   }
				   if(pass!=PASSWORD){
					   main=3;
					   break;
				   }
				   else{
					   printf("*******WElcome ADMIN********\n\n");
					   while(admin!=5)
					   {
						   printf("-->add new patient press : 1\n");
					       printf("-->edit patient data press:2\n");
						   printf("-->reserve slot press :    3\n");
						   printf("-->cancel reservation press:4\n");
						   printf("-->return to main menu press:5\n");
						   scanf("%d",&admin);
						   switch(admin){
						   case 1:addnode(); break;
						   case 2:editrec();break;
						   case 3:reserveslot(slots);break;
						   case 4:cancelres(slots);break;
						   case 5:break;
						   default:printf("unvalid command try again\n");
						   }
					   }
					   admin=0;
				   }
				   break;
			case 2:	printf("********Welcome USER********\n\n");
                    while(user!=3){
						printf("-->View record press:1\n");
						printf("-->View today's reservations press :2\n");
						printf("-->return to main menu press:3\n");
                        scanf("%d",&user);
                     	switch(user){
							case 1:viewrec();break;
							case 2:viewreservation(slots);break;
							case 3:break;
							default:printf("unvalid command try again\n");
							
						}
                    						
					}
					user=0;
                    break;
			case 3:break;
            default:printf("unvalid command try again\n");			
		}
		
	}
	printf("\nProgrammed by Maged Ishak @2019\n"); 
}
void editrec(void)
{
	nodep ptr;
	
	u8 id;
	printf("enter patient id to edit record :");
	scanf("%d",&id);
	ptr=head;
	
	while(ptr!=NULL)
	{
		if(id==ptr->id)
		{
			printf("id found\n");
			printf("old record : patient name : %s ||gender : %c||age:%d||\n",ptr->name,ptr->gender,ptr->age);
			printf("enter new data :\n");
			getdata(ptr);
			printf("record edit succesful\n");
			printf("new record : patient name : %s ||gender : %c||age:%d||\n",ptr->name,ptr->gender,ptr->age);
			return ;
		}
		ptr=ptr->next;
	}
	printf("id not found\n");
}
void addnode(void)
{
	nodep ptr=head,new;
	u8 id;
	printf("enter id value :");
	scanf("%d",&id);
	while(ptr!=NULL)
	{
		if(id==ptr->id)
		{
			printf("id already used\n");
			return ;
		}
		ptr=ptr->next;
	}
	new=(nodep)malloc(sizeof(struct node));
	new->next=NULL;
	new->id=id;
	getdata(new);
	ptr=head;
	if(head==NULL)
	head=new;

	else{while(ptr->next!=NULL)
		{
			ptr=ptr->next;
		}
	ptr->next=new;	
	}
	printf("\t\t\t===>patient added successfeully\n");
}
void printll(void)
{
	nodep ptr=head;
	
	
	if(head==NULL)printf("\t\t\t===>list is empty\n");
	else{
	while(ptr!=NULL)
	{
		printf("\npatient id %d||",ptr->id);
		printf("patient name : %s ||gender : %c||age:%d||\n",ptr->name,ptr->gender,ptr->age);
		
		ptr=ptr->next;
	}
	
	
	}
}
void getdata(nodep new)
{
	char nname[20];
	u8 nage;
	u8 ngender;
	printf("enter patient name:");
	scanf("%s",nname);
	strcpy(new->name,nname);
	printf("enter patient gender:");
	scanf(" %c",&ngender);
	new->gender=ngender;
	printf("enter patient age:");
	scanf("%d",&nage);
	new->age=nage;
}
void reserveslot(struct slot*p)
{//one patient can reserve more than one slot
//user can enter any number to reserve slot
	nodep ptr;
	s8 arr[5]={-1,-1,-1,-1,-1};
	u8 id,s,f=0,i;
	printf("enter patient id to reserve slot :");
	scanf("%d",&id);
	ptr=head;
	
	while(ptr!=NULL)
	{
		if(id==ptr->id)
		{
			do{
			printf("avaliable slots :\n");
			for( i=0;i<5;i++)
			{
				if(p[i].patient==NULL)
				{//printf("slot number:%d ||Time : %s\n",i,p[i].time);
			     printf("slot number:%d ||",i);
				 puts(p[i].time);
				 arr[i]=i;
                 f=1;		
				}
			}
			if(f==0){
				printf("\t\t\t===>no avaliable slots\n");
				return;
			}
			printf("enter slot number:");
			scanf("%d",&s);
			for(i=0;i<5;i++)
			{
				if(s==arr[i])f=2;
				
			}
			
			}while(f!=2);
			p[s].patient=ptr;
			printf("\t\t\t===>slot reserved successfully\n");
			return ;
		}
		ptr=ptr->next;
	}
	printf("\t\t\t===>id not found\n");
	
}
void cancelres(struct slot*p)
{
	nodep ptr;
	
	u8 id,i;
	printf("enter patient id to cancel reservation :");
	scanf("%d",&id);
	ptr=head;
	
	while(ptr!=NULL)
	{
		if(id==ptr->id)
		{
			for( i=0;i<5;i++)
			{
				if(p[i].patient==ptr)
				{printf("patient slot was %s->",p[i].time);
				p[i].patient=NULL;
                 printf("===>reservation cancelled\n");
                 return;				 
				}
			}
			printf("\t\t\t===>patient has no slot reserved\n");
			return ;
		}
		ptr=ptr->next;
	}
	printf("\t\t\t===>id not found\n");
	
}
void viewrec(void)
{
	nodep ptr;
	
	u8 id;;
	printf("enter patient id to view record :");
	scanf("%d",&id);
	ptr=head;
	
	while(ptr!=NULL)
	{
		if(id==ptr->id)
		{
			printf("patient name : %s ||gender : %c||age:%d||\n",ptr->name,ptr->gender,ptr->age);
			return ;
		}
		ptr=ptr->next;
	}
	printf("\t\t\t===>id not found\n");
}
void viewreservation(struct slot*p)
{
	int i=0;
	printf("slot\tTime\t\tpatient\n");
	for(i=0;i<5;i++)
	{
		printf("%d\t%s\t",i,p[i].time);
		if(p[i].patient==NULL)printf("Empty\n");
		else printf("%s\n",p[i].patient);
	}
}