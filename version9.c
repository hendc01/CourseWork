/***********************************************************************
  Henrique Dias Camargo
  skeletonCode1.c
  This programm
  skeleton 1
 *************************************************************************/
#include <stdio.h>
#include <string.h>

int MAX = 126;
const int LENGH = 35;

int listLengh(char list[][LENGH]);
void bufferCleaner(void);
int studentsGenerator(char studentList[][LENGH]);
void marksGenerator(int (*listCourseworks[])[1], 
					char student_list[][LENGH], int coursework);
void marksCorrection(int (*listCourseworks[])[1],
					char students_list[MAX][LENGH], int cw);
void displayMarks(int (*listCourseworks[])[1], 
				  char students_list[MAX][LENGH]); 
int menu(void);
void initializeArray(int (*listCourseworks[MAX])[1],
					 char studentsList[MAX][LENGH]);
void gradeGenerator(int(*listCourseworks[MAX])[1],
					char studentList[MAX][LENGH], int grades[MAX][1]);
void displayGrades( int ( *listCourseworks[MAX])[1], 
				   char studentList[MAX][LENGH], int grades[MAX][1], 
				   int cw );
void addStudent( char studentList[MAX][LENGH] );
void flagMaker(int (*listCoursework[])[1]);
void cwDisplay(int (*listCoursework)[1], char studentList[MAX][LENGH], 
			   int studentNum );
void changeName(char studentList[MAX][LENGH]);
void displayNames(char studentList[MAX][LENGH]);
void passwordChange(char passwordChecker[13], char password[13]);
int displayMenu1( void );
int displayMenu2( void );
int displayMenu3( void );
void screencleaner( void );
void enterPress( void );

int main(void)
{
	int coursework1 [MAX][1];
	int coursework2 [MAX][1];
	int coursework3 [MAX][1];
	int (*listCourseworks[])[1] = {coursework1, coursework2, coursework3};
	int studentsNum = 0 ;
	int menuOption;
	int menu1, menu2, menu3;
	char studentsList[MAX][LENGH];
	char passwordChecker[13] = "123321Sussex";
	char password[13];
	int grades[MAX][1];
	int modfCourse;
	
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
						"Changes only possible in Supervisor Mode.\n",
						menu1 );
				continue;
			}
			else if( menu1 >= 1 && menu1 <= 3 )
			{
				screencleaner();
				printf("ENTERING MARKS. \n");
				printf("COURSEWORK %d", menu1);
				marksGenerator(listCourseworks, studentsList, menu1);
				cwDisplay(listCourseworks[menu1 -1], studentsList, 
						  studentsNum);
				marksCorrection(listCourseworks, studentsList, menu1);
				gradeGenerator(listCourseworks, studentsList, grades);
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
						cwDisplay( listCourseworks[menu2 -1], studentsList, 
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
					displayGrades( listCourseworks, studentsList, grades,   
								  menu2 );
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
					printf(" Input the coursework (1,2 or 3): ");  
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
					printf("ADDING NEW STUDENT.");
					addStudent(studentsList);
					studentsNum = listLengh(studentsList);
					enterPress();
					screencleaner();
				}
				else if(menu3 == 4)
				{
					printf("EDIT A STUDENT NAME.\n");
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
/*Function that let the user to input students according to their needs*/
int studentsGenerator( char studentList[][LENGH] )
{
	int studentsNum;
	/*It needs to have 999 assigned, otherwise if a character is input in 
	studentLimiter, the result will be false(0), therefore it will trigg
	the conditional test (TRY TO FIGURE OUT THE CORRECT WAY TO FIX IT)*/
	int studentLimiter = 127;
	char studentName[LENGH];
	int limiter = 5;
	do
	{
		/*
		ERROR IF THE USER INPUT MILLIONS OF SPACE THE PROGRAM
		WILL BREAK. I DONT KNOW HOW TO FIX IT YET
		*/
		printf( "How many student would you like to input: " );
		scanf( "%d", &studentLimiter );
		bufferCleaner();
		if( studentLimiter >= 0 && studentLimiter <= 125 )
		{
			for( studentsNum = 0; studentsNum < studentLimiter;
				studentsNum++ )
			{
				printf( "|Input the student name %d: ", studentsNum + 1 );
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
/*
Let the user input marks for a specific coursework
*/
void marksGenerator( int ( *listCourseworks[] )[1], 
					char studentList[][LENGH], int courseWork )
{
	int studentLengh = listLengh( studentList );
	int mark = 0;
	if( courseWork <= 3 && courseWork >= 1 )
	{
		for( int nm = 0; nm < studentLengh; )
		{
			printf( "\n Student: %s Input the mark: ", studentList[nm] );
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
					char studentsList[MAX][LENGH], int cw )
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
			printf("\n");
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
					oldGr = listCourseworks[cw -1][id][0];
					printf( "Old grade:%d\n", oldGr );
					printf( "New grade:%d\n", newGr );
					printf( "Confirm grade change? (YES/NO): " );
					scanf( "%3s", test );
					bufferCleaner();
					if(strcmp(test, "YES") == 0 || 
					   strcmp(test, "yes") == 0 )
					{
						listCourseworks[cw -1][id][0] = newGr;
						printf("Grades changed.\n\n");
					}
					else if( strcmp(test, "NO" ) == 0 || 
							strcmp(test, "no") == 0 )
					{
						printf( "OLD GRADE KEPT\n" );
					}
					else
					{
						printf( "ERROR: Invalid input. Try again.\n" );
						printf( "OLD GRADE KEPT\n" );
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
				printf( "ERROR: ID not valid\n" );	
			}
		}
		else if( strcmp(test,"NO" ) == 0 || strcmp( test,"no" ) == 0 )
		{
			screencleaner();
			break;
		}
		else
		{
			printf( "ERROR: Input %s not valid. Try again.\n", test );
		}
	}
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
/*
Display a SINGLE courseWork mark according to the argument of the first 
parameter
*/
void cwDisplay( int ( *listCoursework )[1], char studentsList[MAX][LENGH],
			   int studentNum )
{

	for( int std = 0; std < studentNum; std++ )
	{
		printf( "ID:%d  %s  Mark=%d\n", std, studentsList[std], 
			   listCoursework[std][0] );
	}
}

/*Display ALL Marks*/
void displayMarks( int (*listCourseworks[])[1],
				  char studentsList[MAX][LENGH] ) 
{
	int studentsNum = listLengh( studentsList );
	for (int sdt = 0; sdt < studentsNum; sdt++) 
	{
		printf( "\nID:%d Name: %s: ", sdt, studentsList[sdt] );
		for( int cw = 0; cw < 3; cw++ )
		{
			if( listCourseworks[cw][sdt][0] == -1 )
			{
				printf( "CW%d=%d ",cw + 1,
					   listCourseworks[cw][sdt][0] + 1 );
			}
			else
			{
				printf( "CW%d=%d ", cw + 1, listCourseworks[cw][sdt][0] );	
			}
			
		}
		printf( "\n" );
	}
}
/*This function will allows the user to add students*/
void addStudent( char studentList[MAX][LENGH] )
{
	char newName[36];
	int nullOP = listLengh( studentList );
	printf( "Input the new student name: ");
	scanf( "%35[^\n]", newName );
	bufferCleaner();
	
	strcpy( studentList[nullOP], newName );
	printf( "%s has been added.\n",studentList[nullOP] );
	studentList[nullOP + 1][0] = '\0';
	/*nullOp +1 gives the index after the former nullOp index,
	current new student */
}
/*
Calculate the grades CW1 20% CW2 30% CW3 50%
*/
void gradeGenerator( int (*listCoursework[MAX])[1],
					char studentList[MAX][LENGH], int grades[MAX][1] ) 
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
/*Display main MENU*/
int menu( void )
{
	int menuOption;
	
	printf( "1 Enter Marks\n" );
	printf( "2 Display student's marks\n" );
	printf( "3 Supervisor Mode\n" );
	/*Put a conditional test later so they can only input 1 2 or 3!!!!!!!*/
	do
	{
	    printf( "Input the menu options (1, 2 or 3)" );
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

int displayMenu2( void )
{
	int menu2;
	printf("    Display     \n"
		   "(1)-CourseWork 1\n"
		   "(2)-CourseWork 2\n"
		   "(3)-CourseWork 3\n"
		   "(4)-All Grades  \n" 
		   "(5)-Exit.         ");
	do
	{
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

int displayMenu3( void )
{
	int menu3;
	printf("1-Change de password\n"
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
/*This Function will display grades formatted*/
void displayGrades( int ( *listCourseworks[MAX])[1], 
				    char studentList[MAX][LENGH], int grades[MAX][1], 
				    int cw )
{
	
	int	studentNum = listLengh( studentList );
	for( int sdt = 0; sdt < studentNum ; sdt++ )
	{
		printf( "ID:%d Name: %s: ", sdt, studentList[sdt] );
		if( cw >= 0 && cw <= 2 )
		{
			printf( "CW%d=%d",
				   cw + 1, listCourseworks[cw][sdt][0] );
		}
		else
		{
			for( int cw = 0; cw < 3; cw++ )
			{
				printf( "CW%d=%d",
					   cw + 1, listCourseworks[cw][sdt][0] );
			}	
		}
		printf( "GRADE:%d", grades[sdt][0] );
		/*  ID:       NAME:   GRADE:CW1  CW2 CW3  GRADE:*/    
	}
}
/*Allows the user to change an existing name by giving it's ID*/
void changeName( char studentList[MAX][LENGH] )
{
	int id;
	char newName[35];
	displayNames( studentList ); 
	
	printf( "Chose the ID: \n" );
	scanf( "%d", &id );
	bufferCleaner();
	
	printf( "Input the new name: \n" );
	scanf( "%34[^\n]", newName );
	bufferCleaner();
	
	strcpy( studentList[id], newName );
}

/*Display student names one by one*/
void displayNames( char studentList[MAX][LENGH] )
{
	int studentNum = listLengh( studentList );
	for( int id= 0; id < studentNum; id++ )
	{
		printf( "ID:%d Name: %s", id, studentList[id] );
	}
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
int listLengh( char list[][LENGH] ) 
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
Hold display until enter is pressed
*/
void enterPress( void )
{
	printf("PRess ENTER to exit.");
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
void screencleaner( void ) 
{
	for ( int i = 0; i < 50; i++ ) 
	{
		printf("\n");
	}
}
