#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<conio.h>
#include<ctype.h>
#include<time.h>

struct date{
	int day;
	int month;
	int year;
};

struct notes{
	char user[50];
	char title[50];
	char content[5000];
	struct date created;
};

struct tasks{
	char user[50];
	char title[50];
	char content[5000];
	char status;
	char completed;
	struct date created;
	struct date date;
};


//creating new users
//returns number of user
int Adduser(int user){  
	char x[50];
	char y[50];
	char z[50];
	int i, j, check;
	FILE * fp;
	fp = fopen("users.txt", "r");
	do{
		check = 0;
		system("cls");
		printf("Welcome to SIRPAD\n\n\n");
		printf("Creating new user\n\n");
		printf("\tEnter new user name: ");
		gets(x);
		printf("\n");
		printf("\tConfirm user name: ");
		gets(y);
		
		if(strcmp(x,y) != 0){
			system("cls");
			printf("ERROR\n");
			printf("\nThe usernames entered don't match\nPlease enter the usernames again");
			getch();
			check = 1;
			continue;
		}
		
		if(tolower(x[0])<'a' || tolower(x[0])>'z' || strlen(x) == 0){
			system("cls");
			printf("ERROR\n");
			printf("\nThe username should start with an alphabet\nPlease enter the usernames again");
			getch();
			check = 1;
			continue;
		}
		
		fp = fopen("users.txt", "r");
		while(fgets(z, 49, fp) != NULL){
			strcat(y,"\n");
			if(strcmp(z,y) == 0){
				system("cls");
				printf("ERROR\n");
				printf("\nThe username already exist's\nPlease enter the usernames again");
				getch();
				check = 1;
				continue;
			}
		}	
		fclose(fp);
	}
	while(check == 1);
	fp = fopen("users.txt", "a");
	fputs(x,fp);
	fputs("\n",fp);
	fclose(fp);
	user++;
	fp = fopen("user count.txt", "r+");
	rewind(fp);
	fprintf(fp, "%d",user);
	fclose(fp);
	return user;
}

//changes x to 1 if user if present in users.txt
//changes x to 0 if user if not present in users.txt
//returns user name entered
char* checkUser(int *x){
	char *name = (char*)calloc(50,sizeof(char));
	char name1[50];
	char user[50];
	
	system("cls");
	printf("Welcome to SIRPAD\n\n\n\n");
	printf("Signing In");
	printf("\n\n\n");
	printf("\tUser name: ");
	gets(name);
	int i;
	strcpy(name1, name);
	strcat(name1, "\n");
	
	FILE *fp;
	fp = fopen("users.txt", "r");
	while(fgets(user, 49, fp) != NULL){
		if(user == " "){
			continue;
		}
		if(strcmp(user,name1) == 0){
			*x = 1;
			break;
		}
		else{
			*x = 0;
		}
	}
	fclose(fp);
	return name;
}

//deletes user from users.txt
//returns number of users
int DelUser(int usercount, char* user){
	char name[50], name1[50];
	char file1[] = "users.txt";
	char file2[] = "temp.txt";
	FILE *fp, *ft;
	
	fp = fopen(file2, "w+");
	ft = fopen(file1, "r+");
	
	strcpy(name1, user);
	strcat(name1, "\n");
	rewind(fp);
	rewind(ft);
	
	while(fgets(name, 50, ft) != NULL){
		if(strcmp(name, name1) != 0){
			fputs(name, fp);
			fputs("\n", fp);
		}
		if(strcmp(name, name1) == 0){
			continue;
		}
	}
	
	fclose(fp);
	fclose(ft);
	_fcloseall();
	remove(file1);
	rename(file2, file1);
	
	usercount = usercount - 1;
	fp = fopen("user count.txt", "r+");
	rewind(fp);
	fprintf(fp, "%d",usercount);
	fclose(fp);
	return usercount;
}

void Addnote(char *user){
	struct notes *Ptr;
	char str[100];
	int size = sizeof(*Ptr);
	Ptr = (struct notes *)calloc(1, size);
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	Ptr->created.day = tm.tm_mday;
	Ptr->created.month = tm.tm_mon + 1;
	Ptr->created.year = tm.tm_year + 1900;
	
	strcpy(Ptr->user, user);
	
	while(1){
		system("cls");
		printf("Creating note\n\n\n");
		printf("Enter the title: ");
		gets(Ptr->title);
		if(strlen(Ptr->title) != 0)
			break;
	}
	printf("\n\n");
	while(strlen(gets(str)) != 0){
		strcat(Ptr->content, str);
		strcat(Ptr->content, "\n");
	}
	
	FILE *fp;
	fp = fopen("notes.txt", "a");
	fwrite(Ptr, size, 1, fp);
	fclose(fp);
	free(Ptr);
}

void Delnote(char* title, char* user){
	struct notes x;
	int size = sizeof(x);
	char ntitle[50], name[50];
	FILE *fp, *ft;
	
	fp = fopen("notes.txt", "r+");
	ft = fopen("note temp.txt", "w");
	
	while(fread(&x, size, 1, fp) != 0){
		if(strcmp(x.user, user) == 0){
			if(strcmp(x.title, title) == 0){
				continue;
			}
			fwrite(&x, size, 1, ft);
		}
		else
			fwrite(&x, size, 1, ft);
	}
	
	fclose(fp);
	fclose(ft);
	_fcloseall();
	remove("notes.txt");
	rename("note temp.txt", "notes.txt");
}

void Addtask(char *user){
	struct tasks *Ptr;
	char str[100];
	int size = sizeof(*Ptr), check;
	Ptr = (struct tasks *)calloc(1, size);
	struct date d;
	
	Ptr->status = 'a';
	Ptr->completed = 'n';
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	Ptr->created.day = tm.tm_mday;
	Ptr->created.month = tm.tm_mon + 1;
	Ptr->created.year = tm.tm_year + 1900;
	
	strcpy(Ptr->user, user);
	
	while(1){
		system("cls");
		printf("Creating Task\n\n\n");
		printf("Enter the title: ");
		gets(Ptr->title);
		if(strlen(Ptr->title) != 0)
			break;
	}
	
	d.day = tm.tm_mday;
	d.month = tm.tm_mon + 1;
	d.year = tm.tm_year + 1900;
	
	do{
		check = 1;
		system("cls");
		printf("Creating task\n\n\n");
		printf("Enter the title: %s\n", Ptr->title);
		printf("\n(Enter date in dd-mm-yyyy format)\n");
		printf("\nDue Date: ");	
		scanf("%d%*c%d%*c%d", &Ptr->date.day, &Ptr->date.month, &Ptr->date.year);
		
		if(Ptr->date.day < 1 || Ptr->date.day > 31){
			system("cls");
			printf("Error\n\n");
			printf("Invalid date entered \nPlease enter day again");
			getch();
			check = 0;
			continue;
		}
		
		if(Ptr->date.month < 1 || Ptr->date.month>12){
			system("cls");
			printf("Error\n\n");
			printf("Invalid date entered \nPlease enter day again");
			getch();
			check = 0;
			continue;
		}
		
		if(Ptr->date.month==1 || Ptr->date.month==3 || Ptr->date.month==5 || Ptr->date.month==7 || Ptr->date.month==8 || Ptr->date.month==10 || Ptr->date.month==12){
			if(Ptr->date.day > 31){
			system("cls");
			printf("Error\n\n");
			printf("Invalid date entered \nPlease enter day again");
			getch();
			check = 0;
			continue;
			}
		}
		
		else if(Ptr->date.month==4 || Ptr->date.month==6 || Ptr->date.month==9 || Ptr->date.month==11){
			if(Ptr->date.day > 30){
			system("cls");
			printf("Error\n\n");
			printf("Invalid date entered \nPlease enter day again");
			getch();
			check = 0;
			continue;
			}
		}
		
		else{
			if(Ptr->date.day > 28){
				system("cls");
				printf("Error\n\n");
				printf("Invalid date entered \nPlease enter day again");
				getch();
				check = 0;
				continue;
			}
		}
		
		if(Ptr->date.year < d.year){
			system("cls");
			printf("Error\n\n");
			printf("Invalid date entered \nPlease enter day again");
			getch();
			check = 0;
			continue;
		}		
		
		if(Ptr->date.year == d.year){
			if(Ptr->date.month < d.month){
				system("cls");
				printf("Error\n\n");
				printf("Invalid date entered \nPlease enter day again");
				getch();
				check = 0;
				continue;
			}
			if(Ptr->date.month == d.month){
				if(Ptr->date.day < d.day){
					system("cls");
					printf("Error\n\n");
					printf("Invalid date entered \nPlease enter day again");
					getch();
					check = 0;
					continue;
				}
			}
		}
	}
	while(check == 0);		
	
	fflush(stdin);
	
	printf("\n\n");
	while(strlen(gets(str)) != 0){
		strcat(Ptr->content, str);
		strcat(Ptr->content, "\n");
	}
	
	FILE *fp;
	fp = fopen("tasks.txt", "a");
	fwrite(Ptr, size, 1, fp);
	fclose(fp);
	free(Ptr);
}

void Deltask(char* title, char* user){
	struct tasks x;
	int size = sizeof(x);
	FILE *fp, *ft;
	
	fp = fopen("tasks.txt", "r");
	ft = fopen("task temp.txt", "w");
	
	while(fread(&x, size, 1, fp) != 0){
		if(strcmp(x.user, user) == 0){
			if(strcmp(x.title, title) == 0){
				continue;
			}
			fwrite(&x, size, 1, ft);
		}
		else
			fwrite(&x, size, 1, ft);
	}
	
	fclose(fp);
	fclose(ft);
	_fcloseall();
	remove("tasks.txt");
	rename("task temp.txt", "tasks.txt");
}

void taskcomplete(char *title, char*user){
	struct tasks x;
	FILE *fp, *ft;
	fp = fopen("tasks.txt", "r");
	ft = fopen("task temp.txt", "w");
	
	while(fread(&x, sizeof(struct tasks), 1, fp) != 0){
		if(strcmp(x.user, user) == 0){
			if(strcmp(x.title, title) == 0){
				x.completed = 'y';
			}
		}
		fwrite(&x, sizeof(struct tasks), 1, ft);
	}
	
	fclose(fp);
	fclose(ft);
	_fcloseall();
	
	remove("tasks.txt");
	rename("task temp.txt", "tasks.txt");
}

void taskstatus(char *title, char*user, char status){
	struct tasks x;
	FILE *fp, *ft;
	fp = fopen("tasks.txt", "r");
	ft = fopen("task temp.txt", "w");
	
	while(fread(&x, sizeof(struct tasks), 1, fp) != 0){
		if(strcmp(x.user, user) == 0){
			if(strcmp(x.title, title) == 0){
				x.status = status;
			}
		}
		fwrite(&x, sizeof(struct tasks), 1, ft);
	}
	
	fclose(fp);
	fclose(ft);
	_fcloseall();
	
	remove("tasks.txt");
	rename("task temp.txt", "tasks.txt");
}
