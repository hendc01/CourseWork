/***********************************************************************
  Henrique Dias Camargo
  skeletonCode1.c
  This programm
  skeleton 1
 **********************************************************************/
#include <stdio.h>
#include <string.h>

int MAX = 126;
const int LENGTH = 35;
/*
Student Functions
*/
int studentsGenerator(char studentList[][LENGTH]);
void addStudent( char studentList[MAX][LENGTH] );
void changeName(char studentList[MAX][LENGTH]);
void displayNames(char studentList[MAX][LENGTH]);
/*
Marks functions
*/
void marksGenerator(int (*listCourseworks[])[1], 
					char student_list[][LENGTH], int coursework);
void marksCorrection(int (*listCourseworks[])[1],
					 char students_list[MAX][LENGTH], int cw);
void cwDisplay(int (*listCoursework)[1], char studentList[MAX][LENGTH], 
			   int studentNum );
void displayMarks(int (*listCourseworks[])[1], 
				  char students_list[MAX][LENGTH]); 
/*
Grades Functions
*/
void gradeGenerator(int(*listCourseworks[MAX])[1],
					char studentList[MAX][LENGTH], int grades[MAX][1]);
void displayGrades( int ( *listCourseworks[MAX])[1], 
				   char studentList[MAX][LENGTH], int grades[MAX][1]);
/*
Menus
*/
int menu(void);
int displayMenu1( void );
int displayMenu2( void );
int displayMenu3( void );
/*
Password
*/
void passwordChange(char passwordChecker[13], char password[13]);
/*
Helper Functions
*/
int listLengh(char list[][LENGTH]);
void flagMaker(int (*listCoursework[])[1]);
void screencleaner( void );
void enterPress( void );
void bufferCleaner(void);

int main(void)
{
	int coursework1[MAX][1];
	int coursework2[MAX][1];
	int coursework3[MAX][1];
	int (*listCourseworks[])[1] = {coursework1, coursework2,
		coursework3};
	
	int studentsNum = 0;
	char studentsList[MAX][LENGTH];
	
	int menuOption;
	int menu1, menu2, menu3;
	int modfCourse;
	
	char passwordChecker[13] = "123321Sussex";
	char password[13];
	
	int grades[MAX][1];
	
	flagMaker(listCourseworks);
	
	studentsNum = studentsGenerator(studentsList);
	screencleaner();
	while( studentsNum != 0 )
	{
		menuOption = menu();
		if( menuOption == 1 )
		{
			screencleaner();	
			menu1 = displayMenu1();
			if (menu1 == 0)
			{
				screencleaner();
				continue;
			}
			/*All students have a -1 flag as a value*/
			if( listCourseworks[menu1 -1][0][0] != - 1 )
			{
				printf( "CourseWork %d has already been locked.\n"
					   "Changes only possible in Supervisor Mode.\n\n",
					   menu1 );
				enterPress();
				screencleaner();
				continue;
			}
			else if( menu1 >= 1 && menu1 <= 3 )
			{
				screencleaner();
				printf( "ENTERING MARKS. \n" );
				printf( "COURSEWORK %d\n", menu1 );
				
				marksGenerator( listCourseworks, studentsList, menu1 );
				screencleaner();
				
				printf( "COURSEWORK %d\n", menu1 );
				cwDisplay( listCourseworks[menu1 -1], studentsList, 
						  studentsNum );
				
				marksCorrection( listCourseworks, studentsList, menu1 );
				gradeGenerator( listCourseworks, studentsList, grades );
			}
			bufferCleaner();
		}	
		else if(menuOption == 2)
		{
			screencleaner();
			do
			{
				menu2 = displayMenu2();
				if (menu2 == 0)
				{
					screencleaner();
					break;
				}
				else if( menu2 <= 3 && menu2 >= 1 )
				{
					if( listCourseworks[menu2 -1][0][0] != -1 )
					{
						cwDisplay( listCourseworks[menu2 -1],
								  studentsList, 
								  studentsNum ); 
						printf("Press ENTER to exit.");
					}
					else
					{
						printf( "The marks for coursework %d have not "
							   "been input yet. Please try again after " 
							   "entering the marks.\n", menu2 );
						enterPress();
						break;
					}
				}
				else if( menu2 == 4 &&
						listCourseworks[0][0][0] != -1 &&
						listCourseworks[1][0][0] != -1 &&
						listCourseworks[2][0][0] != -1 )
				{
					displayGrades( listCourseworks, studentsList,
								  grades);
					printf("Press ENTER to exit.");
				}
				else
				{
					printf( "Not all the marks have been entered.\n"
						   "Please try again after entering all " 
						   "the marks\n" );
					enterPress();
					break;
				}
				
			}while(getchar() != '\n');
			screencleaner();
		}
		else if(menuOption == 3)
		{
			screencleaner();
			printf("SUPERVISOR MODE.\n");
			printf("Insert your password: ");
			scanf("%12[^\n]", password);
			bufferCleaner();
			screencleaner();
			
			if(strcmp(password, passwordChecker) == 0)
			{
				menu3 = displayMenu3();
				if(menu3 == 1)
				{
					screencleaner();
					printf("CHANGING PASSWORD \n");
					passwordChange(passwordChecker, password);
					screencleaner();
				}
				else if( menu3 == 2 )
				{
					screencleaner();
					printf( "MODIFYING MARKS.\n") ;
					displayMarks( listCourseworks, studentsList );
					printf("Input the coursework (1,2 or 3): ");  
					scanf("%d", &modfCourse);
					bufferCleaner();
					if(modfCourse < 1 || modfCourse > 3)
					{
						printf( "ERROR: Invalid coursework number.\n" );
						continue; 
					}
					marksCorrection(listCourseworks, studentsList,
									modfCourse);
				}
				else if(menu3 == 3)
				{
					screencleaner();
					addStudent(studentsList);
					studentsNum = listLengh(studentsList);
					enterPress();
					screencleaner();
				}
				else if(menu3 == 4)
				{
					screencleaner();
					changeName(studentsList);
					enterPress();
					screencleaner();
				}
				else if( menu3 == 5 )
				{
					screencleaner();
				}
			}
			else
			{
				printf( "Wrong Password! Please try again.\n\n" );
				enterPress();
			}
		}	
		
	}
}

int studentsGenerator( char studentList[][LENGTH] )
{
	int studentsNum;
	/*127 to prevent scanf bugs when scanf returns 0, because of a 
	char input in a denary scanf*/
	int studentLimiter = 127; 
	char studentName[LENGTH];
	int limiter = 5;
	do
	{
		printf( "How many student would you like to input: " );
		scanf( "%d", &studentLimiter );
		bufferCleaner();
		if( studentLimiter >= 0 && studentLimiter <= 125 )
		{
			for( studentsNum = 0; studentsNum < studentLimiter;
				studentsNum++ )
			{
				printf( "|Input the student name %d: ",
					   studentsNum + 1 );
				scanf( "%34[^\n]", studentName );
				bufferCleaner();
				strcpy( studentList[studentsNum], studentName );
			}
			/*a null operator Flag for my studentlengh function to work,
			so that i can know the size of the array*/
			studentList[studentsNum][0] = '\0';
			break;
		}
		else
		{
			printf( "ERROR!!! TYPE AGAIN (MAXIMUM 125)\n" );
			limiter--;	
			printf( "You have %d attempts left\n", limiter );	
		}
		if( limiter <= 0 )
		{
			printf( "To many attempts. Program closing...\n" );
			break;
		}
	}while( 1 );
	return studentsNum; 	
}
/*This function will allows the user to add students*/
void addStudent( char studentList[MAX][LENGTH] )
{
	char newName[36];
	int nullOP = listLengh( studentList );
	printf( "ADDING NEW STUDENT.\n" );
	printf( "Input the new student name: ");
	scanf( "%35[^\n]", newName );
	bufferCleaner();
	
	strcpy( studentList[nullOP], newName );
	printf( "%s has been added.\n",studentList[nullOP] );
	studentList[nullOP + 1][0] = '\0';
	/*nullOp +1 gives the index after the former nullOp index,
	current new student */
}
/*Allows the user to change an existing name by giving it's ID*/
void changeName( char studentList[MAX][LENGTH] )
{
	int studentNum = listLengh( studentList );
	int id;
	char newName[35];
	displayNames( studentList ); 
	printf("EDIT A STUDENT NAME.\n");
	
	printf( "Chose the ID: " );
	scanf( "%d", &id );
	bufferCleaner();
	if( id < studentNum && id >= 0 )
	{
		printf( "Input the new name: " );
		scanf( "%34[^\n]", newName );
		bufferCleaner();
		strcpy( studentList[id], newName );
		printf( "Name change confirmed.\n" );
	}
	else
	{
		printf("ERROR, Invalid ID\n");
	}
}
/*Display student names one by one*/
void displayNames( char studentList[MAX][LENGTH] )
{
	int studentNum = listLengh( studentList );
	for( int id= 0; id < studentNum; id++ )
	{
		printf( "ID:%d Name: %s\n", id, studentList[id] );
	}
	printf("\n");
}
/*
Let the user input marks for a specific coursework
*/
void marksGenerator( int ( *listCourseworks[] )[1], 
					char studentList[][LENGTH], int courseWork )
{
	int studentLengh = listLengh( studentList );
	int mark = 0;
	if( courseWork <= 3 && courseWork >= 1 )
	{
		for( int nm = 0; nm < studentLengh; )
		{
			printf( "\n Student: %s Input the mark: ", 
				   studentList[nm] );
			/*It accepts letter same error as student generator
			(BUFFER PROBLEM WITH SCANF WITH NUMBERS*/
			scanf( "%d", &mark );
			bufferCleaner();
			if( mark <= 100 && mark >= 0 )
			{
				listCourseworks[courseWork -1][nm][0] = mark;
				nm++;
			}
			else
			{
				printf( "ERROR!! MARKS GOES FROM 0 to 100\n" );
				continue;	
			}
		}	
	}	
}

/*Correct Marks. Allows the user to change marks by using ID:*/
void marksCorrection(int ( *listCourseworks[] )[1],
					 char studentsList[MAX][LENGTH], int cw )
{
	int studentsNum = listLengh( studentsList );
	char test[4];
	int newGr,oldGr, id;
	
	while(1)
	{
		printf( "Would you like to change any mark (YES/NO): " );
		scanf( "%3s", test );
		
		if( strcmp( test, "YES" ) == 0 || strcmp( test, "yes" ) == 0 )
		{
			screencleaner();
			
			cwDisplay( listCourseworks[cw - 1], studentsList, 
					  studentsNum );
			
			printf( "Changing Marks\n" );
			printf( "COURSEWORK %d\n\n", cw );
			printf( "INPUT\n" );
			printf( "ID: ");
			scanf( "%d", &id );
			if( id < studentsNum && id >= 0 )
			{
				printf( "Input the new grade: " );
				scanf( "%d", &newGr );
				bufferCleaner();
				if( newGr <= 100 && newGr >= 0 )
				{
					/*It uses the parameter cw to identify which
					coursework to assign*/
					oldGr = listCourseworks[cw -1][id][0];
					printf( "Old mark:%d\n", oldGr );
					printf( "New mark:%d\n\n", newGr );
					printf( "Confirm mark change? (YES/NO): " );
					scanf( "%3s", test );
					bufferCleaner();
					/*Test to see if the user really wants to change*/
					if(strcmp(test, "YES") == 0 || 
					   strcmp(test, "yes") == 0 )
					{
						listCourseworks[cw -1][id][0] = newGr;
						printf("Mark changed.\n\n");
					}
					else if( strcmp(test, "NO" ) == 0 || 
							strcmp(test, "no") == 0 )
					{
						printf( "OLD mark KEPT\n\n" );
					}
					else
					{
						printf( "ERROR: Invalid input. Try again.\n" );
						printf( "OLD mark KEPT\n\n" );
						continue;
					}
				}
				else
				{
					printf( "ERROR: Invalid Mark. Try again.\n\n" );
				}
			}
			else
			{
				printf( "ERROR: ID not valid\n\n" );	
			}
		}
		else if( strcmp(test,"NO" ) == 0 || strcmp( test,"no" ) == 0 )
		{
			screencleaner();
			break;
		}
		else
		{
			printf( "ERROR: Input %s not valid. Try again.\n\n", test );
		}
	}
}
/*
Display a SINGLE courseWork mark according to the argument of the first 
parameter
*/
void cwDisplay( int ( *listCoursework )[1], 
	char studentsList[MAX][LENGTH], int studentNum )
{
	
	for( int std = 0; std < studentNum; std++ )
	{
		printf( "ID:%3d  %-36s  Mark= %3d\n", std, studentsList[std], 
			   listCoursework[std][0] );
	}
	printf( "\n" );
}
/*Display ALL Marks*/
void displayMarks( int (*listCourseworks[])[1],
				  char studentsList[MAX][LENGTH] ) 
{
	int studentsNum = listLengh( studentsList );
	for (int sdt = 0; sdt < studentsNum; sdt++) 
	{
		printf( "ID:%3d Name: %-30s ", sdt, studentsList[sdt] );
		for( int cw = 0; cw < 3; cw++ )
		{
			if( listCourseworks[cw][sdt][0] == -1 )
			{
				printf( "CW%d= %3d ",cw + 1,
					   listCourseworks[cw][sdt][0] + 1 );
			}
			else
			{
				printf( "CW%d= %3d ", cw + 1,
					   listCourseworks[cw][sdt][0] );	
			}
			
		}
		printf( "\n" );
	}
}
/*
Calculate the grades CW1 20% CW2 30% CW3 50%
*/
void gradeGenerator( int (*listCoursework[MAX])[1],
					char studentList[MAX][LENGTH], int grades[MAX][1] ) 
{
	int lcw[3];
	int studentNum = listLengh( studentList );
	for ( int sdt = 0; sdt < studentNum; sdt++ )
	{
		for( int cw = 0; cw < 3; cw++ )
		{
			lcw[cw] = listCoursework[cw][sdt][0];	
		}
		grades[sdt][0] = ( lcw[0] * 0.20 ) + ( lcw[1] * 0.30 ) + 
		( lcw[2] * 0.50 );
	}
}
/*This Function will display grades formatted*/
void displayGrades( int ( *listCourseworks[MAX])[1], 
				   char studentList[MAX][LENGTH], int grades[MAX][1])
{
	
	int	studentNum = listLengh( studentList );
	for( int sdt = 0; sdt < studentNum ; sdt++ )
	{
		printf( "ID:%3d Name: %30s: ", sdt, studentList[sdt] );
		for( int cw = 0; cw < 3; cw++ )
		{
			printf( "CW%d= %3d |",
				   cw + 1, listCourseworks[cw][sdt][0] );
		}	
		printf( "GRADE:%3d\n", grades[sdt][0] );
		/*  ID:       NAME:   GRADE:CW1  CW2 CW3  GRADE:*/    
	}
}
/*Display main MENU*/
int menu( void )
{
	int menuOption;
	
	printf( "1 Enter Marks\n" );
	printf( "2 Display student's marks\n" );
	printf( "3 Supervisor Mode\n" );
	do
	{
		printf( "Input the menu options (1, 2 or 3): " );
		scanf( "%d", &menuOption );
		bufferCleaner();
		if( menuOption >= 1 && menuOption <= 3 )
		{
			return menuOption;
		}
		else
		{
			printf( "ERROR: Invalid Input" );
		}
	}while( 1 );
}
/*Display the first option in the main menu*/
int displayMenu1( void )
{
	int menu1;
	printf("    INPUT MARKS \n"
		   "(1)-CourseWork 1\n"
		   "(2)-CourseWork 2\n"
		   "(3)-CourseWork 3\n"
		   "(4)-    Exit    \n");
	
	
	do
	{
		printf( "INPUT: " );
		scanf( "%d", &menu1 );
		bufferCleaner();
		if( menu1 >= 1 && menu1 <= 3 )
		{
			return menu1;
		}
		else if( menu1 == 4 )
		{
			return 0;
		}
		else
		{
			printf( "ERROR: Invalid Input\n" );
			
		}
	}while( 1 );
}
/*Display the second option in the main menu*/
int displayMenu2( void )
{
	int menu2;
	printf("    Display     \n"
		   "(1)-CourseWork 1\n"
		   "(2)-CourseWork 2\n"
		   "(3)-CourseWork 3\n"
		   "(4)-All Grades  \n" 
		   "(5)-Exit.       \n");
	do
	{
		printf("INPUT: ");
		scanf( "%d", &menu2 );
		bufferCleaner();
		if( menu2 >= 1 && menu2 <= 4 )
		{
			return menu2;
		}
		else if( menu2 == 5 )
		{
			return 0;
		}
		else
		{
			printf( "ERROR: Invalid Input" );
		}
	}while( 1 );
}
/*Display the supervisor menu*/
int displayMenu3( void )
{
	int menu3;
	printf("1-Change the password\n"
		   "2-Modify a specific Mark\n"
		   "3-Add a new student\n"
		   "4-Edit a student's name\n"
		   "5-EXIT\n"
		   "INPUT: "
		   );
	do
	{
		scanf( "%d", &menu3 );
		bufferCleaner();
		if( menu3 >= 1 && menu3 <= 5 )
		{
			return menu3;
		}
		else if( menu3 == 5 )
		{
			return 5;
			break;
			
		}
		else
		{
			printf( "ERROR: Invalid Input" );
		}
	}while( 1 );
}
/*Validate the user password*/
void passwordChange( char passwordChecker[13], char password[13] )
{
	int limiter = 7;
	char tempPass[13];
	while( 1 )
	{
		printf("Input the current password: ");
		scanf("%12[^\n]", password);
		bufferCleaner();
		if(strcmp(password, passwordChecker) == 0)
		{
			printf( "Input your new Password: " );
			scanf("%12[^\n]", tempPass);
			bufferCleaner();
			strcpy( passwordChecker, tempPass );
			break;
		}
		else if( limiter <= 3 )
		{
			printf( "You have more %d chances left\n", limiter );
			if( limiter == 0 )
			{
				break;
			}
		}
		else
		{
			printf( "Wrong Password!\n" );
		}
		limiter--;
	}
}
/*Count and return the lengh of rows of a list*/
int listLengh( char list[][LENGTH] ) 
{
	int listCount;
	for( listCount = 0; listCount < MAX; listCount++ ) 
	{
		if( list[listCount][0] == '\0' )
		{
			break;
		}		
	}
	return listCount;
}
/*
This function put a flag in the first value of a 2d array 
*/
void flagMaker( int ( *listCoursework[] )[1] )
{
	for( int cw = 0; cw <= 2; cw++ )
	{
		for( int sdt = 0 ; sdt < MAX ; sdt++ )
		{
			listCoursework[cw][sdt][0] = -1;
		}
	}
}
/*Clean the CMD display*/
void screencleaner( void ) 
{
	for ( int i = 0; i < 50; i++ ) 
	{
		printf("\n");
	}
}
/*
Hold display until enter is pressed
*/
void enterPress( void )
{
	printf("Press ENTER to exit.");
	while(getchar() != '\n')
	{
		;
	}
}
/*Clean the buffer*/
void bufferCleaner()
{
	while( getchar() != '\n' ){
		;
	}
}
