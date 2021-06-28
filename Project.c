#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<time.h>
#include "myfunctions.h"


int main(){
	int check, x, userCount;
	char *user, a, *ntitles;
	struct notes note;
	struct tasks task;
	struct date today;
	int tsize = sizeof(task);
	int nsize = sizeof(note);
	int i, j, d, c, a_count, d_count, c_count;
	char menu = 'u';
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	today.day = tm.tm_mday;
	today.month = tm.tm_mon + 1;
	today.year = tm.tm_year + 1900;
	
	FILE *fp, *ft;
	
	if(fopen("users.txt", "r") == NULL){
		fp = fopen("users.txt", "w");
		fclose(fp);
	}
	
	if(fopen("user count.txt", "r") == NULL){
		fp = fopen("user count.txt", "w");
		fprintf(fp,"0");
		fclose(fp);
	}
	
	if(fopen("notes.txt", "r") == NULL){
		fp = fopen("notes.txt", "w");
		fclose(fp);
	}
	
	if(fopen("tasks.txt", "r") == NULL){
		fp = fopen("tasks.txt", "w");
		fclose(fp);
	}

	fp = fopen("user count.txt", "r");
	userCount = fgetc(fp) - 48;
	fclose(fp);
	
	printf( "\n\n\n\n\n\n\n\n\n\n    WW   WW   WW  EEEEEEE   LL       CCCCCCC   OOOOOOO  MMMMMMMMMMMM  EEEEEEE  \n");
	sleep(1);
	printf( "    WW   WW   WW  EE        LL       CC        OO   OO  MM   MM   MM  EE       \n");
	sleep(1);
	printf("    WW   WW   WW  EEEEEEE   LL       CC        OO   OO  MM   MM   MM  EEEEEEE  \n");
	sleep(1);
	printf("    WW   WW   WW  EE        LL       CC        OO   OO  MM   MM   MM  EE       \n");
	sleep(1);
	printf("    WW   WW   WW  EE        LL       CC        00   00  MM   MM   MM  EE       \n");
	sleep(1);
	printf("    WWWWWWWWWWWW  EEEEEEE   LLLLLLL  CCCCCCC   OOOOIOO  MM   MM   MM  EEEEEEE  \n");
	sleep(1);
	
	while(1){ 
	
		do{
			if(menu == 'u'){
				
				switch(userCount){
					
					case 0:
						do{
							system("cls");
							printf("Welcome to SIRPAD\n\n\n");
							printf("\t1) Create new user\n");
							printf("\t2) Exit\n");
							printf("\n");
							printf("\nEnter your selection: ");
							scanf(" %d",&x);
							fflush(stdin);
							if(x == 1)
								userCount = Adduser(userCount);
								
							if(x == 2)
								exit(0);
								
							if(x < 1 || x > 2){
								system("cls");
								printf("ERROR\n");
								printf("Please enter the correct option\n");
								printf("(PRESS ANY KEY)");
								getch();
							}	
						}
						while(x < 1 || x > 2);
						
					case 1:
					case 2:
					case 3:
					case 4:
						
						do{
							system("cls");
							printf("Welcome to SIRPAD\n");
							printf("\n\n");
							printf("\t1) Create new user\n");
							printf("\t2) Log in\n");
							printf("\t3) Exit\n");
							printf("\n");
							
							printf("\nEnter your selection: ");
							scanf(" %d",&x);
							
							fflush(stdin);
							
							if(x == 3)
								exit(0);
							
							if(x < 1 || x > 3){
								system("cls");
								printf("ERROR\n");
								printf("Please enter the correct option\n");
								printf("(PRESS ANY KEY)");
								getch();
							}
							
						}
						while(x < 1 || x > 3);
						
						switch(x){
							case 1:
								userCount = Adduser(userCount);
							case 2:
								system("cls");
								user = checkUser(&check);
								menu = 'm';
								break;
						}
						
						break;
					case 5:
						
						do{
							system("cls");
							printf("Welcome to SIRPAD\n\n\n");
							printf("\t1) Log in\n");
							printf("\t2) Exit\n");
							printf("\n");
							printf("\nEnter your selection: ");
							scanf("%d",&x);
							fflush(stdin);
							if(x == 1){
								user = checkUser(&check);
								menu = 'm';
							}
							
							if(x == 2)
								exit(0);
								
							if(x < 1 || x > 2){
								system("cls");
								printf("ERROR\n");
								printf("Please enter the correct option\n");
								printf("(PRESS ANY KEY)");
								getch();
							}	
						}while(x < 1 || x > 2);
						
						break;
				}
				
				
				while(check != 1){
					system("cls");
					printf("ERROR\n\n");
					printf("Invalid User name entered\n");
					if(userCount < 5)
						printf("Please press Y to return or N to create new user\n");
					if(userCount == 5)
						printf("Please press Y to return \n");
					a = getch();
					
					if(a == 'y'){
						user = checkUser(&check);
					}
					
					if(userCount < 5){
						if(a == 'n'){
							userCount = Adduser(userCount);
							user = checkUser(&check);
						}
					}		
				}
			}
			
			
			if(menu == 'm'){
				do{
					system("cls");
					printf("Hi %s this is the Main Menu\nPlease select any option\n\n\n",user);
					printf("\t1) Notepad\n\t2) Tasks\n\t3) Change user\n\t4) Delete user\n\t5) Exit");
					printf("\n\n\nEnter your selection: ");
					scanf(" %d",&x);
					fflush(stdin);
					
					if(x == 5){
						free(user);
						exit(0);
					}
					
					if(x<1 || x>4){
						system("cls");
						printf("ERROR\n");
						printf("Please enter the correct option\n");
						printf("(PRESS ANY KEY)");
						getch();
					}
					
					if(x == 4){
						system("cls");
						printf("Warning\n\n");
						printf("Press Y to continue or press any key to return");
						a = getch();
						if(tolower(a) != 'y'){
							x = 100;
						}
					}
					
				}
				while( x<1 || x>4 );
				
				if(x==4){
					userCount = DelUser(userCount, user);
					
					fp = fopen("notes.txt", "r+");
					ft = fopen("note temp.txt", "w");
					while(fread(&note, nsize, 1, fp) != 0){
						if(strcmp(note.user, user) != 0){
							fwrite(&note, nsize, 1, ft);
						}
					}
					fclose(fp);
					fclose(ft);
					_fcloseall();
					remove("notes.txt");
					rename("note temp.txt", "notes.txt");
					
					fp = fopen("tasks.txt", "r");
					ft = fopen("task temp.txt", "w");
					while(fread(&task, tsize, 1, fp) != 0){
						if(strcmp(task.user, user) != 0){
							fwrite(&task, tsize, 1, ft);
						}
					}
					fclose(fp);
					fclose(ft);
					_fcloseall();
					remove("tasks.txt");
					rename("task temp.txt", "tasks.txt");
					
					menu = 'u';
				}	
				
				if(x==3){
					menu = 'u';
				}
			}
			
			
		}while(x == 3 || x == 4);
				
		if(x==1){
			do{
				do{
					i = 0;
					fp = fopen("notes.txt", "r");
					system("cls");
					printf("Welome to Notepad\n\n\n");
					printf("Please select any option\n\n\n");
					
					printf("\t0) Create note\n");
					
					while(fread(&note, nsize, 1, fp) != 0){
						if(strcmp(user, note.user) == 0){
							i++;
							printf("\t%d) %s\n", i,note.title);	
						}
					}
					
					printf("\t%d) Main menu\n",i+1);
					printf("\n\nEnter selection: ");
					scanf("%d",&x);
					
					fclose(fp);
					
					if(x == i+1){
						menu = 'm';
						break;
					}
					
					fflush(stdin);
					
					if(x > i){
						system("cls");
						printf("ERROR");
						printf("\nEnter correct selection\n\nPlease enter the selection again");
						getch();
					}
					
					if(x == 0){
						Addnote(user);
					}
				}
				while(x>i || x<=0);
				
				if(x == i+1){
					menu = 'm';
					break;
				}
				
				fp = fopen("notes.txt", "r");
				i=0;
				while(fread(&note, nsize, 1, fp) != 0){
					if(strcmp(note.user, user) == 0){
						i++;
						if(i==x){
							break;
						}
					}
				}
				
				fclose(fp);
				
				do{
					check = 0;
					system("cls");
					printf("Welome to Notepad\n\n\n");
					printf("Title: %s\n\n",note.title);
					printf("Date Created: %d-%d-%d\n\n", note.created.day, note.created.month, note.created.year);
					printf("%s\n\n\n",note.content);
					printf("(PRESS R TO RETURN OR D TO DELETE)");
					a = getch();
					
					if(tolower(a)=='d'){
						
						system("cls");
						printf("Warning\n\n");
						printf("If you want to confirm press Y or press any key");
						a = getch();
						
						if(tolower(a) == 'y'){
							Delnote(note.title, user);
							check = 1;
						}
						
						else
							check = 0;
							
					}
						
					if(tolower(a)=='r'){
						check = 1;
					}
					
				}
				while(check==0);	
			}
			while(1);
			x = 0;
		}
		
		if(x==2){
			do{
				do{
					i = 0;
					c = 0;
					d = 0;
					_fcloseall();
					fp = fopen("tasks.txt", "r+");
					system("cls");
					printf("Welome to Tasks\n\n\n");
					printf("Please select any option\n\n\n");
					printf("\t%d) Create task", i);
					
					while(fread(&task, tsize, 1, fp) != 0){
						if(strcmp(user, task.user) == 0){
							if(task.completed == 'y'){
								c++;
								continue;
							}
							
							if(task.date.year<today.year || (task.date.year==today.year && task.date.month<today.month) || (task.date.year==today.year && task.date.month==today.month && task.date.day<today.day)){
								if(task.status == 'd'){
									d++;
								}
								else{
									d++;
									fclose(fp);
									taskstatus(task.title, user, 'd');
									fp = fopen("tasks.txt", "r+");
									fseek(fp, i * sizeof(struct tasks), SEEK_SET);	
								}
								continue;
							}
							
							if(task.date.day == today.day && task.date.month == today.month && task.date.year == today.year){
								if(i == 0){
									printf("\n\n\tActive Tasks,\n");
								}
								i++;
								printf("\t%d) %s  DUE  Today\n", i,task.title);
								continue;
							}
							
							if(i == 0){
								printf("\n\n\tActive Tasks,\n");
							}
							
							if(task.status == 'a'){
								i++;
							}
							else{
								i++;
								fclose(fp);
								taskstatus(task.title, user, 'a');
								fp = fopen("tasks.txt", "r+");
								fseek(fp, i * sizeof(struct tasks), SEEK_SET);	
							}
							printf("\t%d) %s  DUE  %d-%d-%d\n", i,task.title, task.date.day, task.date.month, task.date.year);	
						}
					}
					a_count = i;
					close(fp);
					fp = fopen("tasks.txt", "r+");
					if(d != 0){
						printf("\n\n\tDelayed Tasks,\n");
						
						while(fread(&task, tsize, 1, fp) != 0){
							if(strcmp(task.user, user) == 0){
								if(task.status == 'd' && task.completed == 'n'){
									i++;
									printf("\t%d) %s  DUE  %d-%d-%d\n", i, task.title, task.date.day, task.date.month, task.date.year);
								}
							}
						}
					}
					d_count = i;
					close(fp);
					fp = fopen("tasks.txt", "r+");
					if(c != 0){
						printf("\n\n\tCompleted Tasks,\n");
						
						while(fread(&task, tsize, 1, fp) != 0){
							if(strcmp(task.user, user) == 0){
								if(task.completed == 'y'){
									i++;
									printf("\t%d) %s  DUE  %d-%d-%d\n", i, task.title, task.date.day, task.date.month, task.date.year);
								}
							}
						}
					}
					c_count = i;
					fclose(fp);	
														
					printf("\n\t%d) Main menu\n", 1 + i);
					printf("\n\nEnter selection: ");
					scanf("%d",&x);

					
					if(x == i+1){
						menu = 'm';
						break;
					}
					
					fflush(stdin);
					
					if(x > i){
						system("cls");
						printf("ERROR");
						printf("\nEnter correct selection\n\nPlease enter the selection again");
						getch();
					}
					
					if(x == 0){
						Addtask(user);
					}
				}
				while(x>i || x<1);
				
				if(x == i+1){
					menu = 'm';
					break;
				}
				
				fp = fopen("tasks.txt", "r");
				if(x > 0 && x <= a_count){
					i=0;
					while(fread(&task, tsize, 1, fp) != 0){
						if(strcmp(task.user, user) == 0){
							if(task.status == 'a' && task.completed == 'n'){
								i++;
								if(i==x){
									break;
								}
							}
						}
					}
				}

				else if(x > a_count && x <= d_count){
					i=0;
					x = x - a_count;
					while(fread(&task, tsize, 1, fp) != 0){
						if(strcmp(task.user, user) == 0){
							if(task.status == 'd' && task.completed == 'n'){
								i++;
								if(i==x){
									break;
								}	
							}							
						}
					}
				}

				else if(x > d_count && x <= c_count){
					i=0;
					x = x - d_count;
					while(fread(&task, tsize, 1, fp) != 0){
						if(strcmp(task.user, user) == 0){
							if(task.completed == 'y'){
								i++;
								if(i==x){
									break;
								}	
								continue;
							}
						}
					}
				}
				fclose(fp);
				
				do{
					check = 0;
					system("cls");
					printf("Welome to Tasks\n\n\n");
					printf("Title: %s\n\n",task.title);
					printf("Date Created: %d-%d-%d\n\n", task.created.day, task.created.month, task.created.year);
					printf("Due Date: %d-%d-%d\n\n", task.date.day, task.date.month, task.date.year);
					if(task.completed == 'y'){
						if(task.status == 'd'){
							printf("Status: Delayed\n\n");
						}
						else{
							printf("Status: Not Delayed\n\n");
						}
					}
					printf("%s\n\n",task.content);
					if(task.completed == 'n'){
						printf("(PRESS R TO RETURN OR C TO COMPLETE TASK OR D TO DELETE)");
						a = getch();
					}
					
					else{
						printf("(PRESS R TO RETURN OR D TO DELETE)");
						a = getch();
					}
					
					if(tolower(a)=='d'){
						
						system("cls");
						printf("Warning\n\n\n");
						printf("If you want to confirm press Y or press any key");
						a = getch();
						
						if(tolower(a) == 'y'){
							Deltask(task.title, user);
							check = 1;
						}
						
						else
							check = 0;
							
					}
						
					if(tolower(a)=='r'){
						check = 1;
					}
					
					if(task.completed != 'y'){
						if(tolower(a) == 'c'){
							system("cls");
							printf("Warning\n\n\n");
							printf("If you want to confirm press Y or press any key");
							a = getch();
							
							if(tolower(a) == 'y'){
								taskcomplete(task.title, user);
								check = 1;
							}
							else
								check = 0;
						}	
					}					
				}
				while(check==0);	
			}
			while(1);
			x = 0;
		}
	}
}
