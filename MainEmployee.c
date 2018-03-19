#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Employee.h"
#include "Lecture.h"
#include "Professor.h"

void CreateLec();
void ChangeLec();
void DeleteLec();
void PrintLec();

int MainEmployee(int ID)
{
	struct Employee EmpRec;
	FILE *EmpFP;
	EmpFP = fopen("Employee", "rb");
	int check = 0;


	while(fread(&EmpRec, sizeof(EmpRec), 1, EmpFP) > 0)
	{
		if(EmpRec.ID == ID)
		{
			check = ID;
			break;
		}
	}

	if(check == 0)
	{
		printf("Check Your ID\n");
		exit(0);
	}

	while(1)
	{
		int a = 0;

		printf("\n");
		printf("================================ FOR EMPLOYEE =================================\n");
		printf("1. Create Lecture\n2. Modify Lecture Information\n3. Delete Lecture\n4. Print Lecture List\n");
		printf("(If you'd like to exit, ENTER '0')\n>> ");
		scanf("%d", &a);

		switch(a)
		{
		case 1:
			CreateLec();
			break;
		case 2:
			ChangeLec();
			break;
		case 3:
			DeleteLec();
			break;
		case 4:
			PrintLec();
			break;
		case 0:
			printf("GoodBye\n");
			exit(0);
		default:
			printf("Please check your answer.\n");
			break;
		}
	}
	return 0;
}

void CreateLec()
{
	struct Lecture LecRec;
	struct Professor ProfRec;
	FILE *LecFP;
	FILE *ProfFP;
	LecFP = fopen("Lecture", "rb+");
	ProfFP = fopen("Professor", "rb");
	char c;

	do
	{
		printf("================================= List Of Lecture ===============================\n");
		printf("  Name         Major        Professor      Room       Time      Year    Semester\n");
		printf("---------------------------------------------------------------------------------\n");

		while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
		{
			if(LecRec.ID != 0)
			printf("%-13s %-11s %-14s %-12s %-9s %-10s %s\n", LecRec.Name, LecRec.Major, LecRec.ProfName, LecRec.Room, LecRec.Time, LecRec.Year, LecRec.Semester);
		}
	
		printf("------------------------------------- PLUS --------------------------------------\n");
		printf("Name\tMajor\tProfessor\tRoom\tTime\tYear\tSemester\n");
	
		fseek(LecFP, -sizeof(LecRec), SEEK_END);
	
		if(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
		{
			LecRec.ID += 1;
	
			scanf("%s %s %s %s %s %s %s", LecRec.Name, LecRec.Major, LecRec.ProfName, LecRec.Room, LecRec.Time, LecRec.Year, LecRec.Semester);
	
			while(fread(&ProfRec, sizeof(ProfRec), 1, ProfFP) > 0)
			{
				int Profcmp = strcmp(LecRec.ProfName, ProfRec.Name);

				if(Profcmp == 0)
				{
					LecRec.ProfID = ProfRec.ID;
					fseek(LecFP, 0, SEEK_END);
					fwrite(&LecRec, sizeof(LecRec), 1, LecFP);
					printf("============================= Completed ==========================\n");
					break;
				}
				else
				{
					printf("Check Professor's Name\n");
					break;
				}
			}
		}

		printf("Continue to create a lecture?(Y/N)\n>> ");
		scanf(" %c", &c);
	}while(c == 'Y');

	fclose(LecFP);
	fclose(ProfFP);
}

void ChangeLec()
{
	struct Lecture LecRec;
	FILE *LecFP;
	LecFP = fopen("Lecture", "rb+");
	char c;

	do
	{
		printf("========================================= List Of Lecture ==================================================\n");
		printf("Lecture_ID  Lecture_Name    Major    Professor_ID  Professor_Name     Room      Time       Year    Semester\n");
		printf("------------------------------------------------------------------------------------------------------------\n");
	
		while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
		{
			if(LecRec.ID != 0)
			printf(" %-11d %-13s %-12s %-12d %-15s %-10s %-10s %-10s %s\n", LecRec.ID, LecRec.Name, LecRec.Major, LecRec.ProfID, LecRec.ProfName, LecRec.Room, LecRec.Time, LecRec.Year, LecRec.Semester);
		}
	
		printf("------------------------------------------------------------------------------------------------------------\n");
	
		printf("Enter ID of Lecture\n>> ");
		
		int EnterID = 0;
		int a = 0;
	
		if(scanf("%d", &EnterID) == 1)
		{
			fseek(LecFP, (EnterID - Start_LecID)*sizeof(LecRec), SEEK_SET);
	
			if((fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0) && (LecRec.ID != 0))
			{
				printf("------------------------------------------------------------------------------------------------------------\n");
				printf("Lecture_ID  Lecture_Name    Major    Professor_ID  Professor_Name     Room      Time       Year    Semester\n");
				printf("------------------------------------------------------------------------------------------------------------\n");
				printf(" %-11d %-13s %-12s %-12d %-15s %-10s %-10s %-10s %s\n", LecRec.ID, LecRec.Name, LecRec.Major, LecRec.ProfID, LecRec.ProfName, LecRec.Room, LecRec.Time, LecRec.Year, LecRec.Semester);
				printf("------------------------------------------------------------------------------------------------------------\n");
				printf("Enter Number to Modify Information\n");
				printf("1. Lecture Name\n2. Major\n3. Classroom\n4. Time\n5. Year\n6. Semester\n>> ");
				scanf("%d", &a);
				printf("Enter New Information to change : ");
	
				switch(a)
				{
				case 1:
					scanf("%s", LecRec.Name);
					break;
				case 2:
					scanf("%s", LecRec.Major);
					break;
				case 3:
					scanf("%s", LecRec.Room);
					break;
				case 4:
					scanf("%s", LecRec.Time);
					break;
				case 5:
					scanf("%s", LecRec.Year);
					break;
				case 6:
					scanf("%s", LecRec.Semester);
					break;
				case 0:
					printf("GoodBye\n");
					exit(0);
				default:
					printf("Check your Answer\n");
					break;
				}
	
				fseek(LecFP, -sizeof(LecRec), SEEK_CUR);
				fwrite(&LecRec, sizeof(LecRec), 1, LecFP);
				printf("================================================ Completed =================================================\n");
			}
		}

		printf("Continue to Modify Information?(Y/N)\n>> ");
		scanf(" %c", &c);
	}while(c == 'Y');

	fclose(LecFP);
}

void DeleteLec()
{
	struct Lecture LecRec;
	FILE *LecFP;
	LecFP = fopen("Lecture", "rb+");
	char cc;

	do
	{
		printf("========================================= List Of Lecture ==================================================\n");
		printf("Lecture_ID  Lecture_Name    Major    Professor_ID  Professor_Name     Room      Time       Year    Semester\n");
		printf("------------------------------------------------------------------------------------------------------------\n");
	
		while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
		{
			if(LecRec.ID != 0)
			printf(" %-11d %-13s %-12s %-12d %-15s %-10s %-10s %-10s %s\n", LecRec.ID, LecRec.Name, LecRec.Major, LecRec.ProfID, LecRec.ProfName, LecRec.Room, LecRec.Time, LecRec.Year, LecRec.Semester);
		}
		
		printf("------------------------------------------------------------------------------------------------------------\n");
		printf("Enter ID of Lecture\n>> ");
		int EnterID = 0; int a = 0; char c;
	
		if(scanf("%d", &EnterID) == 1)
		{
			fseek(LecFP, (EnterID - Start_LecID)*sizeof(LecRec), SEEK_SET);
			if((fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0) && (LecRec.ID != 0))
			{
				printf("------------------------------------------------------------------------------------------------------------\n");
				printf("Lecture_ID  Lecture_Name    Major    Professor_ID  Professor_Name     Room      Time       Year    Semester\n");
				printf("------------------------------------------------------------------------------------------------------------\n");
				printf(" %-11d %-13s %-12s %-12d %-15s %-10s %-10s %-10s %s\n", LecRec.ID, LecRec.Name, LecRec.Major, LecRec.ProfID, LecRec.ProfName, LecRec.Room, LecRec.Time, LecRec.Year, LecRec.Semester);
				printf("------------------------------------------------------------------------------------------------------------\n");
				printf("Are you sure to delete this Lecture?(Y/N)\n>> ");
				scanf(" %c", &c);
	
				if(c == 'Y')
				{
					LecRec.ID = 0;
					strcpy(LecRec.Name, "0");
					strcpy(LecRec.Major, "0");
					LecRec.ProfID = 0;
					strcpy(LecRec.ProfName, "0");
					strcpy(LecRec.Room, "0");
					strcpy(LecRec.Time, "0");
					strcpy(LecRec.Year, "0");
					strcpy(LecRec.Semester, "0");
	
					fseek(LecFP, -sizeof(LecRec), SEEK_CUR);
					fwrite(&LecRec, sizeof(LecRec), 1, LecFP);
					printf("================================================ Completed =================================================\n");
				}
			}
		}

		printf("Continue to Delete Lecture?(Y/N)\n>> ");
		scanf(" %c", &cc);
	}while(cc == 'Y');

	fclose(LecFP);
}

void PrintLec()
{
	struct Lecture LecRec;
	FILE *LecFP;
	LecFP = fopen("Lecture", "rb");

	printf("========================================= List Of Lecture ==================================================\n");
	printf("Lecture_ID  Lecture_Name    Major    Professor_ID  Professor_Name     Room      Time       Year    Semester\n");
	printf("------------------------------------------------------------------------------------------------------------\n");
	
	while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
	{
		if(LecRec.ID != 0)
		printf(" %-11d %-13s %-12s %-12d %-15s %-10s %-10s %-10s %s\n", LecRec.ID, LecRec.Name, LecRec.Major, LecRec.ProfID, LecRec.ProfName, LecRec.Room, LecRec.Time, LecRec.Year, LecRec.Semester);
	}
	
	printf("------------------------------------------------------------------------------------------------------------\n");

	fclose(LecFP);
}
