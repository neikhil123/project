/*****************************************************************************
 * Copyright (C) Nikhil Waghmare. waghmaren13.comp@coep.ac.in
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include<stdio.h>                    //HEADER FILES
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct student {                      //STRUCTURE DEFINITION
	long int rollno;
	char name[40];
	char branch[10];
}stud1,stud2;

FILE *ptr1,*ptr2;                    //GLOBAL FILE POINTERS

int menu(void);                        //FUNCTION PROTOTYPES
int submenu(int);
void target(int,int,long int *,char []);
void copy(void);
void write(FILE *,struct student);
void found(struct student);
int getit(int,int *,long int,char[]);
void add(void);
void delete(void);
void modify(void);
void search(void);
void display(void);

main() {                            //MAIN() STARTS
	int i,j,k,choice;
	do
	{
		choice = menu();                //CALLING menu()
		switch(choice) {
			case 1 : add();            //CALLING add()
			break;
			case 2 : delete();        //CALLING delete()
			break;
			case 3 : modify();        //CALLING modify()
			break;
			case 4 : search();        //CALLING search()
			break;
			case 5 : display();        //CALLING display()
			break;
			case 6 : exit(0);
			break;
		}
	}while(choice != 6);
}

int menu() {                           //FUNCTION TO PRINT MAIN MENU AND RETURN THE CHOICE
	char choice;
	while(1) {
		printf("\n\n\n                 STUDENTS' RECORD FILE");
		printf("\n                       MAIN MENU");
		printf("\n                ADD RECORD          :: 1");
		printf("\n                DELETE RECORD       :: 2");
		printf("\n                MODIFY RECORD       :: 3");
		printf("\n                SEARCH RECORD       :: 4");
		printf("\n                DISPLAY ALL RECORDS :: 5");
		printf("\n                EXIT                :: 6");
		printf("\n                ENTER YOUR CHOICE   :: ");
		scanf("%c",&choice);
		if((isdigit(choice))&&((choice>=49)&&(choice<=54)))
		return(choice-48);
	}
}

int submenu(int type) {              			   //FUNCTION TO PRINT SUBMENUS ACCORDING TO THE TYPE
	 char ask[][10] = {"DELETE","MODIFY","SEARCH"};
	 int choice;
	 do {
		 printf("\n\t\t %s MENU", ask[type-1]);
		 printf("\n\t %s BY ROLL NO. :: 1", ask[type-1]);
		 printf("\n\t %s BY NAME :: 2",ask[type-1]);
		 printf("\n\t RETURN TO MAIN MENU :: 3");
		 printf("\n\t ENTER YOUR CHOICE :: ");
		 scanf("%d", &choice);
	 }while((choice != 1)&&(choice != 2)&&(choice != 3));
	 return choice;
 }

void target(int choice, int type, long int *roll, char name[]) {    //FUNCTION TO GET THE RECORD TO BE SEARCHED FOR
	char ch,opt[][10] = {"ROLL NO","NAME"};
	char ask[][10] = {"DELETED","MODIFIED","SEARCHED"};
	int j;
	printf("\n ENTER THE %s OF STUDENT WHOSE RECORD IS TO BE %s :: ",opt[choice-1], ask[type-1]);
	if(choice==1)
		scanf("%ld",roll);
	else {
		ch=getchar();
		j=0;
		ch=getchar();
		while(ch!='\n') {
			name[j++]=ch;
			ch=getchar();
		}
		name[j]='\0';
	}
}

void copy(void) {                       //FUNCTION TO COPY FILE (*ptr1) TO FILE (*ptr2)
	int j;
	char ch;
	fscanf(ptr1,"%ld",&stud1.rollno);
	ch=getc(ptr1);
	j=0;
	do {
		stud1.name[j]=getc(ptr1);
	}while(stud1.name[j++]!='\0');
	
	ch=getc(ptr1);
	fscanf(ptr1,"%s",stud1.branch);
	fprintf(ptr2,"%ld\n",stud1.rollno);
	fprintf(ptr2,"%s",stud1.name);
	putc('\0',ptr2);
	putc('\n',ptr2);
	fprintf(ptr2,"%s",stud1.branch);
	putc('\0',ptr2);
	putc('\n',ptr2);
}

void write(FILE *p,struct student stud) {            //FUNCTION TO WRITE CONTENTS OF OBJECT stud IN FILE *p
	fprintf(p,"%ld\n",stud.rollno);
	fprintf(p,"%s",stud.name);
	putc('\0',p);
	putc('\n',p);
	fprintf(p,"%s",stud.branch);
	putc('\0',p);
	putc('\n',p);
}

void found(struct student stud) {                //FUNCTION TO PRINT A RECORD IF IT IS IN THE FILE
	printf("\n ROLL NO. :: %ld",stud.rollno);
	printf("\n NAME :: %s",stud.name);
	printf("\n BRANCH :: %s\n",stud.branch);
}

int getit(int choice,int *flag,long int roll,char nam[]) {   //FUNCTION TO READ ONE RECORD FROM FILE AND TO...
                               				//...CHECK WHETHER IT IS THE TARGET RECORD...
	int find=0,j;                    			    //...IT RETURNS 1 IF MATCH IS FOUND, 0 OTHERWISE
	char ch;
	fscanf(ptr1,"%ld",&stud1.rollno);
	ch=getc(ptr1);
	j=0;
	do {
		stud1.name[j]=getc(ptr1);
	}while(stud1.name[j++]!='\0');
	
	ch=getc(ptr1);
	fscanf(ptr1,"%s",stud1.branch);
	if((choice==1)&&(stud1.rollno==roll))
		find=1;
	else if((choice==2)&&(!strcmp(stud1.name,nam)))
		find=1;
	if(find) {
		*flag=1;
		printf("\n RECORD FOUND::");
		found(stud1);                    //CALLING FUNCTION found()
		ch=getchar();
	}
	return (find);
}

void add(void) {                       //FUNCTION TO PERFORM ADD OPERATION IN FILE
	 int i,j,k,rec,num,no;
	 char cho,ch;
	 struct student *stud;                //STRUCTURE POINTER FOR DYNAMIC MEMORY ALLOCATION
	 ptr1=fopen("records.txt","r");            //OPENING THE RECORD FILE

	 if(ptr1==NULL) {
	 	printf("CANNOT OPEN THE RECORD FILE\n");
	 	exit(0);
	 }
	 fscanf(ptr1,"%d",&num);                //READING THE NO. OF RECORDS IN FILE
	 ptr2=fopen("temp.txt","w");            //OPENING A TEMPORARY FILE
	 fprintf(ptr2,"%d\n",num);
	 for(i=0;i<num;i++)
	 	copy();
	 	no=0;
	 do {
		 printf("\n ENTER THE NO. OF RECORDS TO BE ADDED ::");
		 scanf("%d",&rec);
		 stud=(struct student *)(calloc(rec,sizeof(struct student)));    //DYNAMIC ALLOCATION
		 for(k=0;k<rec;k++) {
			 printf("\n\n ENTER ROLL NO. OF STUDENT %d :: ",k+1);
			 scanf("%ld",&stud[k].rollno);
			 ch=getchar();
			 printf("\n ENTER STUDENT'S NAME :: ");
			 j=0;
			 ch=getchar();

			 while(ch!='\n') {
				 stud[k].name[j++]=ch;
				 ch=getchar();
			 }
			 stud[k].name[j]='\0';
			 printf("\n ENTER STUDENT'S BRANCH :: ");
			 scanf("%s",stud[k].branch);
		  }
		  ch=getchar();
		  printf("\n DO U WANT TO SAVE THESE %d RECORDS (Y/N)??",rec);
		  cho=getchar();
		  if((cho=='n')||(cho=='N'))
	 	  goto label;
	 	  no+=rec;

	 	  for(k=0;k<rec;k++)
	 		write(ptr2,stud[k]);
	 	  printf("\n %d RECORD SUCCESSFULLY ADDED",rec);
		  label:
		  ch=getchar();
		  printf("\n WANT TO ENTER MORE RECORDS (Y/N) ::");
		  cho=getchar();
	 }while((cho=='y')||(cho=='Y'));

	 free(stud);                                //FREE THE ALLOCATED MEMORY
	 fclose(ptr1);
	 fclose(ptr2);
	 printf("\n TOTAL %d RECORD SUCCESSFULLY ADDED",no);

	 ptr1=fopen("temp.txt","r");
	 if(ptr1==NULL) {
	 	printf("CANNOT OPEN THE RECORD FILE\n");
	 	exit(0);
	 }
	 fscanf(ptr1,"%d",&num);
	 ptr2=fopen("records.txt","w");
	 fprintf(ptr2,"%d\n",num+no);

	 for(i=0;i<num+no;i++)                        //COPY TEMP TO RECORDS
	 	copy();
	 fclose(ptr1);
	 fclose(ptr2);
}

void delete(void) {                   //FUNCTION TO PERFORM DELETE OPERATION
	 int i,j,flag,find,choice,num,rec;
	 long int roll;
	 char cho,ch,opt[][10]={"ROLL NO","NAME"},nam[40],dept[10];
	 do {
		ptr1=fopen("records.txt","r");
		fscanf(ptr1,"%d",&num);
	 	if(num==0) {
			printf("\n NO MORE RECORDS IN FILE!!!!!");
			printf("\n RETURNING TO MAIN MENU");
		break;
	 	}
	 	choice=submenu(1);
		if(choice==3)
		return;

		target(choice,1,&roll,nam);
		flag=rec=0;
		ptr2=fopen("temp.txt","w");
		fprintf(ptr2,"%d\n",num);
		for(i=0;i<num;i++) {
			cho='n';
			find=getit(choice,&flag,roll,nam);
			if(find) {
				printf("\n DO U WANT TO DELETE THIS RECORD (Y/N)??");
				cho=getchar();
	 		}
	 		if((cho=='y')||(cho=='Y')) {
	 			rec++;
			continue;
	 		}
			write(ptr2,stud1);
		 }
		 fclose(ptr1);
		 fclose(ptr2);
		 ptr2=fopen("records.txt","w");
		 ptr1=fopen("temp.txt","r");
		 fscanf(ptr1,"%d",&num);
		 fprintf(ptr2,"%d\n",num-rec);
		 for(i=0;i<num-rec;i++)
		 	copy();
		 fclose(ptr1);
		 fclose(ptr2);
		 if((!find)&&(!flag))
		 	printf("\n RECORD NOT FOUND");
		 if(rec)
			 printf("\n %d RECORD SUCCESSFULLY DELETED",rec);
		 ch=getchar();
		 printf("\n WANT TO DELETE SOME OTHER RECORDS (Y/N) ::");
		 cho=getchar();
		 }while((cho=='y')||(cho=='Y'));
}

void modify(void) {                   //FUNCTION TO MODIFY RECORDS
	 int i,j,flag,find,choice,num,rec;
	 long int roll;
	 char cho,ch,nam[40],dept[10];
	 do {
	 	ptr1=fopen("records.txt","r");
	 	fscanf(ptr1,"%d",&num);
	 	if(num==0) {
			 printf("\n NO RECORDS IN FILE!!!!!");
			 printf("\n RETURNING TO MAIN MENU");
		break;
	 	}
	 	choice=submenu(2);
	 	if(choice==3)
	 	return;
	 	target(choice,2,&roll,nam);
	 	flag=rec=0;
	 	ptr2=fopen("temp.txt","w");
	 	fprintf(ptr2,"%d\n",num);
	 	for(i=0;i<num;i++) {
	 		cho='n';
	 		find=getit(choice,&flag,roll,nam);
	 		if(find) {
	 			printf("\n DO U WANT TO MODIFY THIS RECORD (Y/N)??");
	 			cho=getchar();
	 		}
	 		if((cho=='y')||(cho=='Y')) {
	 			rec++;
	 			printf("\n ENTER THE NEW ROLL NO. STUDENT :: ");
	 			scanf("%ld",&stud2.rollno);
	 			ch=getchar();
	 			printf("\n ENTER STUDENT'S NAME :: ");
	 			j=0;
	 			ch=getchar();
					 while(ch!='\n') {
					 stud2.name[j++]=ch;
					 ch=getchar();
					 }
				stud2.name[j]='\0';
				printf("\n ENTER STUDENT'S BRANCH :: ");
				scanf("%s",stud2.branch);
				write(ptr2,stud2);
				continue;
			 }
	 		 write(ptr2,stud1);
	 	}
	 	fclose(ptr1);
	 	fclose(ptr2);
	 	ptr2=fopen("records.txt","w");
	 	ptr1=fopen("temp.txt","r");
	 	fscanf(ptr1,"%d",&num);
	 	fprintf(ptr2,"%d\n",num);
	 	for(i=0;i<num;i++)
	 		copy();
	 	fclose(ptr1);
	 	fclose(ptr2);
	 	if((!find)&&(!flag))
	 		printf("\n RECORD NOT FOUND");
	 	if(rec)
	 		printf("\n %d RECORD SUCCESSFULLY MODIFIED",rec);
	 	ch=getchar();
	 	printf("\n WANT TO MODIFY SOME OTHER RECORDS (Y/N) ::");
	 	cho=getchar();
	 	}while((cho=='y')||(cho=='Y'));
}

void search(void) {                //FUNCTION TO SEARCH FOR A RECORD
	 int i,j,flag,find,choice,num,rec;
	 long int roll;
	 char cho,ch,nam[40],dept[10];
	 do {
	 	ptr1=fopen("records.txt","r");
	 	fscanf(ptr1,"%d",&num);
	 		if(num==0) {
	 			printf("\n NO RECORDS IN FILE!!!!!");
	 			printf("\n RETURNING TO MAIN MENU");
	 		break;
	 		}
	 	choice=submenu(3);
	 	if(choice==3)
	 	return;
	 	target(choice,3,&roll,nam);
	 	flag=rec=0;
	 	for(i=0;i<num;i++) {
	 		cho='n';
	 		find=getit(choice,&flag,roll,nam);
	 	}
	 	fclose(ptr1);
	 	if((!find)&&(!flag))
	 		printf("\n RECORD NOT FOUND");
	 	if(rec)
	 		printf("\n %d RECORDS FOUND",rec);
	 	ch=getchar();
	 	printf("\n WANT TO SEARCH SOME OTHER RECORDS (Y/N) ::");
	 	cho=getchar();
	 	}while((cho=='y')||(cho=='Y'));
}

void display(void) {                   //FUNCTION TO DISPLAY ALL RECORDS
	 int i,j,num;
	 long int roll;
	 char ch,cho;
	 i=1;
	 ptr1=fopen("records.txt","r");
	 fscanf(ptr1,"%d",&num);
	 if(num==0) {
	 	printf("\n NO RECORDS IN FILE!!!!!");
	 	printf("\n RETURNING TO MAIN MENU");
	 return;
	 }
	 for(i=0;i<num;i++) {
	 	fscanf(ptr1,"%ld",&stud1.rollno);
	 	ch=getc(ptr1);
	 	j=0;
	 		do {
	 			stud1.name[j]=getc(ptr1);
	 		}while(stud1.name[j++]!='\0');
	 	ch=getc(ptr1);
	 	fscanf(ptr1,"%s",stud1.branch);
	 	printf("\n SR. NO.  %d",i+1);
	 	found(stud1);
	 	if(!((i+1)%5)) {
	 	cho=getchar();
	 	printf("\n PRESS ENTER TO CONTINUE");
	 	cho=getchar();
	 	}
	 }
	 printf("\n TOTAL NO. OF RECORDS = %d",num);
	 fclose(ptr1);
}
