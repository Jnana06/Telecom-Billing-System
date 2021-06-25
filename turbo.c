#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

struct subscriber
{
char phonenumber[20];
char name[50];
float amount;
}s;

void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();
void telecombill();
void login();
char get;
int main()
{

	char choice;
    system("cls");
    system("color 0C");
	printf("\n\n\n\n\n\n\n\n\n\n\t\t********************************************************************************");
	printf("\n\t\t\t\t------WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM---");
	printf("\n\t\t********************************************************************************");
	Sleep(2000);

    system("cls");
    login();
	while (1)
	{
		system("cls");
		system("color 0F");
		printf("\n********************************************");
		printf("\n\n\n********************************************");
		printf("\n--------------------------------------------");

		printf("\n Enter\n A -------> for adding new records.\n\n\n L -------> for list of records");
		printf("\n\n\n M -------> for modifying records.\n\n\n P -------> for payment\n\n\n B-------> for bill generation");
		printf("\n\n\n S -------> for searching records.");
		printf("\n\n\n D -------> for deleting records.\n\n\n E -------> for exit\n");
		printf("----------------------------------------------");
		printf("\n\n\n********************************************");
		choice=getche();
		choice=toupper(choice);
		switch(choice)
		{
			case 'P':
				payment();break;
			case 'A':
				addrecords();break;
			case 'L':
				listrecords();break;
			case 'M':
				modifyrecords();break;
			case 'S':
				searchrecords();break;
			case 'D':
				deleterecords();break;
                        case 'B':
                                telecombill();break;
			case 'E':
				system("cls");
				printf("\n\n\t\t\t\tTHANK YOU");
				printf("\n\n\n\n\t\t\tFOR USING OUR SERVICE");
				Sleep(2000);
				exit(0);
				break;
			default:
				system("cls");
				printf("Incorrect Input");
				printf("\nAny key to continue");
				_getch();
		}
	}
}

void addrecords()
{
	FILE *f;
	char test;
	int calls;
	f=fopen("d:/god.txt","ab+");
	while(1)
	{
		system("cls");
		system("color 02");
		do{
        printf("\n\nENTER A PHONENUMBER\n");
        scanf("%s",s.phonenumber);
        if(strlen(s.phonenumber)!=10)
        {

            printf("INVALID PHONE NUMBER\n\n\n");
        }
	}while(strlen(s.phonenumber)!=10);
	    system("cls");
		printf("\n ENTER NAME IN BLOCK LETTERS ONLY:");
		fflush(stdin);
		scanf("%s",s.name);
		system("cls");
		printf("\nMINIMUM Rs 200 FOR UPTO 100 CALLS\n\n\nPLUS Rs 0.60 PER CALL FOE NEXT 50 STD CALLS\n\n\nPLUS Rs 0.50 PER CALL FOR NEXT 50 STD CALLS\n\n\nPLUS Rs 0.40 FOR BEYOND 200 STD CALLS \n");
		printf("\n ENTER THE NUMBER OF CALLS");
		scanf("%d",&calls);
		if(calls<=100)
            s.amount=200;

        else if(calls>100 && calls<=150)
        {
            calls=calls-100;
            s.amount=200+(0.60*calls);
        }
        else if(calls>150 && calls<=200)
        {
            calls=calls-150;
            s.amount=200+(0.60*50)+(0.50*calls);
        }
        else{
            calls=calls-200;
            s.amount=200+(0.60*50)+(0.50*50)+(0.40*calls);
        }
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		system("cls");
		printf("1 RECORD SUCCESSFULLY ADDED");
		printf("\n PRESS ESC KEY TO EXIT OR ANY OTHER KEY TO ADD ANOTHER RECORD:");
		test=getche();
		if(test==27)
			break;
	}
	fclose(f);
}

void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("d:/god.txt","rb"))==NULL)
		exit(0);
	system("cls");
	system("color 01");
	printf("Phone Number\t\tUser Name\t\t\tAmount\n");
	for(i=0;i<79;i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-",s.phonenumber,s.name,s.amount);
	}
	printf("\n");
	for(i=0;i<79;i++)
		printf("-");

fclose(f);
_getch();
}
void deleterecords()
{
	FILE *f,*t;
	int g=0;
	char phonenumber[20];
	int ch=1;
	while(ch!=0)
    {
        system("cls");
        system("color 06");
        printf("\nENTER THE PHONE NUMBER TO BE DELETED");
        scanf("%s",phonenumber);
        f=fopen("d:/god.txt","rb+");rewind(f);
        while(fread(&s,sizeof(s),1,f)==1)
        {
            if(strcmp(s.phonenumber,phonenumber)==0)
            {
                g=1;
            }
        }
        if(g==1)
        {
            t=fopen("d:/temp.txt","wb+");
            rewind(f);
            while(fread(&s,sizeof(s),1,f)==1)
            {
                if(strcmp(s.phonenumber,phonenumber)!=0)
                {                    fseek(t,0,SEEK_CUR);
                    fwrite(&s,sizeof(s),1,t);
                }
            }
            fclose(t);
            fclose(f);
            remove("d:/god.txt");
            rename("d:/temp.txt","d:/god.txt");
            printf("\n Record deleted");
        }
        printf("\n Do you want to continue deletion of records? If no press 0 else press 1\n");
        scanf("%d",&ch);
    }
}

void searchrecords()
{
	FILE *f;
	char phonenumber[20],name[20];
	int op;
	f=fopen("d:/god.txt","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("cls");
	system("color 08");
	printf("\nENTER THE SEARCH METHOD OPTION:\n1 FOR PHONENUMBER \n2 FOR NAME");
	scanf("%d",&op);
	if(op==1)
    {
        system("cls");
        printf("\nENTER THE PHONENUMBER");
        scanf("%s",phonenumber);
    }
    else{
        system("cls");
        printf("\nENTER THE NAME");
      scanf("%s",name);

    }
	while(fread(&s,sizeof(s),1,f)==1)
	{

		if((strcmp(s.phonenumber,phonenumber)==0) || (strcmp(s.name,strupr(name))==0))
		{	system("cls");
		printf("\n----------------------------------");
			printf("\n\nRECORD FOUND ");
			printf("\n----------------------------------");

			printf("\n\nPHONENUMBER: %s\n\n\nNAME: %s\n\n\nAMOUNT: Rs.%0.2f\n\n\n",s.phonenumber,s.name,s.amount);
        printf("\n----------------------------------");
			break;
		}

	}

	_getch();
   fclose(f);
}
void modifyrecords()
{
    int calls;
	FILE *f;
	char phonenumber[20],phone[20];
	long int size=sizeof(s);
	if((f=fopen("d:/god.txt","rb+"))==NULL)
		exit(0);
	system("cls");
	system("color 0F");
	printf("ENTER THE PHONE NUMBER OF THE SUBSCRIBER TO MODIFY:\n");
	scanf("%s",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{

			system("cls");
	do{

        printf("ENTER A NEW PHONENUMBER\n");
        scanf("%s",s.phonenumber);
        if(strlen(s.phonenumber)!=10)
        {

            printf("INVALID PHONE NUMBER\n\n");
        }
	}while(strlen(s.phonenumber)!=10);
	        system("cls");
	        //printf("ENTER THE PHONE NUMBER AGAIN\n");
	        //scanf("%s",s.phonenumber);
			printf("\nENTER THE NAME IN BLOCK LETTERS ONLY: ");
			fflush(stdin);
			scanf("%s",s.name);
			system("cls");
		printf("\nMINIMUM Rs 200 FOR UPTO 100 CALLS\n\n\nPLUS Rs 0.60 PER CALL FOE NEXT 50 STD CALLS\n\n\nPLUS Rs 0.50 PER CALL FOR NEXT 50 STD CALLS\n\n\nPLUS Rs 0.40 FOR BEYOND 200 STD CALLS \n");
		printf("\nENTER THE NUMBER CALLS\n");
		scanf("%d",&calls);
		if(calls<=100)
            s.amount=200;
        else if(calls>100 && calls<=150)
        {
            calls=calls-100;
            s.amount=200+(0.60*calls);
        }
        else if(calls>150 && calls<=200)
        {
            calls=calls-150;
            s.amount=200+(0.60*50)+(0.50*calls);
        }
        else{
            calls=calls-200;
            s.amount=200+(0.60*50)+(0.50*50)+(0.40*calls);
        }
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
}

void payment()
{
	FILE *f;
	int op,gst;
	char phonenumber[20],name[20];
	long int size=sizeof(s);
	float amt;
	int i;
	time_t t;
	time(&t);
	if((f=fopen("d:/god.txt","rb+"))==NULL)
		exit(0);
	system("cls");
	system("color 06");
	printf("ENTER THE METHOD OF PAYMENT:\n1 THROUGH PHONENUMBER \n2 THROUGH NAME");
	scanf("%d",&op);
	if(op==1)
    {
        system("cls");
        printf("\nENTER THE PHONENUMBER");
        scanf("%s",phonenumber);
    }
    if(op==2)
    {
        system("cls");
        printf("\nENTER THE NAME\n");
       scanf("%s",name);
    }
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
	    if((strcmp(s.phonenumber,phonenumber)==0) || (strcmp(s.name,strupr(name))==0))
		{
			system("cls");
			for(i=0;i<79;i++)
			{
			printf("*");}
			printf("\n\n..............PAYMENT DETAILS....................   ");
			printf("\n\nDATE/TIME:%s",ctime(&t));
			printf("\n PHONE NO.     :%s",s.phonenumber);
			printf("\n NAME          :%s",s.name);
			printf("\n CURRENT AMOUNT:%f",s.amount);
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\nENTER THE AMOUNT FOR PAYMENT :");
			fflush(stdin);
			scanf(" %f",&amt);
			s.amount=s.amount-amt;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			printf("\n\n\nTHANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
			break;
		}


	}

	_getch();
	fclose(f);
}
void telecombill()
{
	FILE *f;
	int op;
	char phonenumber[20],name[20];
	long int size=sizeof(s);
	float amt;
	int i;
	time_t t;
	time(&t);
	if((f=fopen("d:/god.txt","rb+"))==NULL)
		exit(0);
	system("cls");
	system("color 06");
	printf("ENTER THE METHOD OF BILL GENERATION:\n\n1 THROUGH PHONENUMBER \n\n2 THROUGH NAME");
	scanf("%d",&op);
	if(op==1)
    {
        system("cls");
        printf("\nENTER THE PHONENUMBER");
        scanf("%s",phonenumber);
    }
    if(op==2)
    {
        system("cls");
        printf("\nENTER THE NAME\n");
        scanf("%s",name);
    }
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
	    if((strcmp(s.phonenumber,phonenumber)==0) || (strcmp(s.name,strupr(name))==0))
		{
			system("cls");
			for(i=0;i<79;i++)
			{
			printf("*");}
			printf("\n\n      GENERATING BILL     ");
			printf("\n\n\nDATE/TIME:%s",ctime(&t));
			printf("\n PHONE NO.     :%s",s.phonenumber);
			printf("\n NAME          :%s",s.name);
			printf("\n CURRENT AMOUNT:%f",s.amount);
			printf("\n\n********PLEASE PROVIDE THIS COPY DURING PAYMENT***************");
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\n\nTHANK YOU %s FOR USING OUR SERVICE",s.name);
			break;
		}


	}

	_getch();
	fclose(f);
}
void login()
{
	system("color 0F");
	int a=0,i=0;
    char uname[10],c=' ';
    char pword[10];
    char user[10]="user";
    char pass[10]="pass";
    do
{

    printf("\n  **************************  LOGIN FORM  **************************  ");
    printf(" \n                       ENTER USERNAME:-");
	scanf("%s",uname);
	printf(" \n                       ENTER PASSWORD:-");
	while(i<10)
	{
	    pword[i]=_getch();
	    c=pword[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';
		if(strcmp(uname,"user")==0 && strcmp(pword,"pass")==0)
	{
	printf("  \n\n\n       WELCOME TO OUR SYSTEM !!!! LOGIN IS SUCCESSFUL");
	printf("\n\n\n\t\t\t\tPress any key to continue...");
	_getch();//holds the screen
	break;
	}
	else
	{
		printf("\n        SORRY !!!!  LOGIN IS UNSUCESSFUL");
		a++;

		_getch();//holds the screen
		system("cls");

	}
}
	while(a<=3);
	if (a>3)
	{
		printf("\nSORRY YOU HAVE ENTERED THE WRONG USERNAME AND PASSWORD FOR 4 TIMES!!!!!");

		_getch();
		exit(0);

		}
		system("cls");
}

