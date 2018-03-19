#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Professor.h"
#include "Lecture.h"
#include "GPOfLecture.h"
#include "Student.h"

int ProfID = 0;
char ProfName[20] = {0};
char Major[20] = {0};

void EnterGP();
void ProfPrintLec();
void PrintLecTime();
void LecByYear();
void PrintStuGP();
void PrintStuRegist();

int MainProfessor(int ID)
{
	struct Professor ProfRec;
	FILE *ProfFP;
	ProfFP = fopen("Professor", "rb");

	int ck = 0;

	while(fread(&ProfRec, sizeof(ProfRec), 1, ProfFP) > 0)
	{
		if(ProfRec.ID == ID)
		{
			ProfID = ID;
			strcpy(ProfName, ProfRec.Name);
			strcpy(Major, ProfRec.Major);

			break;
		}
	}

	if(ProfID == 0)
	{
		printf("Check your ID\n");
		exit(0);
	}

	while(1)
	{
		int a;

		printf("\n============================= FOR PROFESSOR =============================\n");

		if(strcmp(ProfName, "BenAffleck") == 0)
		{
			printf("Code_Name : Bruce Wayne    ");
		}
		else if(strcmp(ProfName, "RDJ") == 0)
		{
			printf("Code_Name : IronMan    ");
		}

		printf("ID : %d    Name : %s    Major : %s\n", ProfID, ProfName, Major);
		printf("-------------------------------------------------------------------------\n");

		printf("1. Enter Grade Point\n2. Print My Lecture\n3. Print My Lecture By Time\n4. Print My Lecture By Year\n5. Print Student's GPA\n6. Print Student's GP By Lecture\n");
		printf("(If you'd like to exit, ENTER '0')\n>> ");
		scanf("%d", &a);

		switch(a)
		{
		case 1:
			EnterGP();
			break;
		case 2:
			ProfPrintLec();
			break;
		case 3:
			PrintLecTime();
			break;
		case 4:
			LecByYear();
			break;
		case 5:
			PrintStuGP();
			break;
		case 6:
			PrintStuRegist();
			break;
		case 0:
			printf("GoodBye\n");
			fclose(ProfFP);
			exit(0);
		default:
			printf("Please check your answer.\n");
			break;
		}
	}

	fclose(ProfFP);
	return 0;
}

void EnterGP()
{
	struct GPOfLecture GPRec;
	struct Lecture LecRec;
	struct Student StuRec;
	FILE *GPFP;
	FILE *LecFP;
	FILE *StuFP;
	GPFP = fopen("GPOfLecture", "rb+");
	LecFP = fopen("Lecture", "rb");
	StuFP = fopen("Student", "rb+");
	char c;

	do
	{
		fseek(GPFP, 0, SEEK_SET);
		fseek(LecFP, 0, SEEK_SET);
		fseek(StuFP, 0, SEEK_SET);

		printf("======================= Lecture Of Yours =======================\n");
		printf("Lecture_ID    Lecture_Name     Major        Year     Semester\n");
		printf("----------------------------------------------------------------\n");
	
		while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
		{
			if(LecRec.ProfID == ProfID)
			{
				printf("%-13d %-16s %-12s %-8s %s\n", LecRec.ID, LecRec.Name, LecRec.Major, LecRec.Year, LecRec.Semester);
			}
		}
	
		printf("----------------------------------------------------------------\n");
		printf("Enter the ID of Lecture to Put in Grade Point\n>> ");
		int EnterLecID;
		scanf("%d", &EnterLecID);
	
		printf("----------------------------------------------------------------\n");
		printf("Student_ID     Student_Name     Major        Grade     Semester\n");
		printf("----------------------------------------------------------------\n");
	
		while(fread(&GPRec, sizeof(GPRec), 1, GPFP) > 0)
		{
			if((GPRec.ProfID == ProfID) && (GPRec.LecID == EnterLecID) && (GPRec.GP == 0))
			{
				printf("%-14d %-16s %-12s %-10hd %s\n", GPRec.StuID, GPRec.StuName, GPRec.Major, GPRec.Grade, GPRec.Semester);
			}
		}
	
		printf("----------------------------------------------------------------\n");
		printf("Enter the ID of Student to Put in Grade Point\n>> ");
		int EnterStuID; double EnterGP;
		scanf("%d", &EnterStuID);
		printf("Enter the Grade Point\n>> ");
		scanf("%lf", &EnterGP);
	
		fseek(GPFP, 0 , SEEK_SET);
		while(fread(&GPRec, sizeof(GPRec), 1, GPFP) > 0)
		{
			if((GPRec.LecID == EnterLecID) && (GPRec.StuID == EnterStuID))
			{
				GPRec.GP = EnterGP;
				fseek(GPFP, -sizeof(GPRec), SEEK_CUR);
				fwrite(&GPRec, sizeof(GPRec), 1, GPFP);
				printf("=========================== Completed ==========================\n");
			}
		}
	
		fseek(GPFP, 0, SEEK_SET);
		double gpa = 0; int i = 0;
	
		while(fread(&GPRec, sizeof(GPRec), 1, GPFP) > 0)
		{
			if((EnterStuID == GPRec.StuID) && (GPRec.GP != 0))
			{
				gpa += GPRec.GP;
				i++;
			}
		}
	
		gpa /= i;
	
		fseek(StuFP, (EnterStuID - Start_StuID)*sizeof(StuRec), SEEK_SET);
	
		if((fread(&StuRec, sizeof(StuRec), 1, StuFP) > 0) && (StuRec.ID != 0))
		{
			StuRec.GPA = gpa;
			fseek(StuFP, -sizeof(StuRec), SEEK_CUR);
			fwrite(&StuRec, sizeof(StuRec), 1, StuFP);
		}

		printf("Continue to Enter GradePoint?(Y/N)\n>> ");
		scanf(" %c", &c);
	}while(c == 'Y');
	
	fclose(LecFP); fclose(GPFP); fclose(StuFP);
}
	
void ProfPrintLec()
{
	struct Lecture LecRec;
	FILE *LecFP;
	LecFP = fopen("Lecture", "rb");

	printf("==================================== Lecture ======================================\n");
	printf("Lecture_ID     Lecture_Name     Major       Room       Time     Year     Semester\n");
	printf("-----------------------------------------------------------------------------------\n");

	while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
	{
		if(LecRec.ProfID == ProfID)
		{
			printf("%-14d %-16s %-11s %-10s %-8s %-8s %s\n", LecRec.ID, LecRec.Name, LecRec.Major, LecRec.Room, LecRec.Time, LecRec.Year, LecRec.Semester);
		}
	}

	fclose(LecFP);
}

void PrintLecTime()
{
	struct Lecture LecRec;
	FILE *LecFP;
	LecFP = fopen("Lecture", "rb");

	printf("=========================================================================\n");
	printf("Lecture Name     Time     Room\n");
	printf("-------------------------------------------------------------------------\n");

	while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
	{
		int YearCMP = strcmp("2017", LecRec.Year);

		if((LecRec.ProfID == ProfID) && (YearCMP == 0))
		{
			printf("%-16s %-8s %s\n", LecRec.Name, LecRec.Time, LecRec.Room);
		}
	}

	fclose(LecFP);
}

void LecByYear()
{
	struct Lecture LecRec;
	FILE *LecFP;
	LecFP = fopen("Lecture", "rb");

	printf("=========================================================================\n");
	printf("Year     Semester     Lecture_ID     Lecture_Name     Major\n");
	printf("-------------------------------------------------------------------------\n");

	int year;

	for(year = 2017 ; year > 2011 ; year--)
	{
		fseek(LecFP, 0, SEEK_SET);

		while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
		{
			int RecYear = atoi(LecRec.Year);

			if((year == RecYear) && (LecRec.ProfID == ProfID))
			{
				printf("%-8s %-12s %-14d %-16s %s\n", LecRec.Year, LecRec.Semester, LecRec.ID, LecRec.Name, LecRec.Major);
			}

		}
	}

	fclose(LecFP);
}

void PrintStuGP()
{
	struct Student StuRec;
	FILE *StuFP;
	StuFP = fopen("Student", "rb");

	printf("=========================================================================\n");
	printf("Student_ID     Student_Name       Major         Grade     GPA\n");
	printf("-------------------------------------------------------------------------\n");

	while(fread(&StuRec, sizeof(StuRec), 1, StuFP) > 0)
	{
		printf("%-14d %-18s %-13s %-9hd %.2lf\n", StuRec.ID, StuRec.Name, StuRec.Major, StuRec.Grade, StuRec.GPA);
	}

	fclose(StuFP);
}

void PrintStuRegist()
{
	struct GPOfLecture GPRec;
	struct Lecture LecRec;
	FILE *GPFP;
	FILE *LecFP;
	GPFP = fopen("GPOfLecture", "rb");
	LecFP = fopen("Lecture", "rb");

	while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
	{
		if(LecRec.ProfID == ProfID)
		{
			printf("\n");
			printf("=========================================================================\n");
			printf("Lecture_ID     Lecture_Name     Year     Semester\n");
			printf("-------------------------------------------------------------------------\n");
			printf("%-14d %-16s %-8s %s\n", LecRec.ID, LecRec.Name, LecRec.Year, LecRec.Semester);

			fseek(GPFP, 0, SEEK_SET);

			printf("-------------------------------------------------------------------------\n");
			printf("Student_ID     Student_Name     GP('0.00' means not check yet)\n");
			printf("-------------------------------------------------------------------------\n");

			while(fread(&GPRec, sizeof(GPRec), 1, GPFP) > 0)
			{
				if(LecRec.ID == GPRec.LecID)
				{
					printf("%-14d %-16s %.2lf\n", GPRec.StuID, GPRec.StuName, GPRec.GP);
				}
			}
		}
	}

	fclose(GPFP); fclose(LecFP);
}

