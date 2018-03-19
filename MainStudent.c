#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Student.h"
#include "Lecture.h"
#include "GPOfLecture.h"
#include "Professor.h"

int StuID = 0;
char StuName[20] = {0};
char StuMajor[20] = {0};
short Grade = 0;

void RegisterLec();
void StuPrintLec();
void PrintLAP();
void PrintGP();
void PrintSemester();
void PrintGPA();

int MainStudent(int ID)
{
	struct Student StuRec;
	FILE *StuFP;

	StuFP = fopen("Student", "rb");

	while(fread(&StuRec, sizeof(StuRec), 1, StuFP) > 0)
	{
		if(StuRec.ID == ID)
		{
			StuID = ID;
			strcpy(StuName, StuRec.Name);
			strcpy(StuMajor, StuRec.Major);
			Grade = StuRec.Grade;
			break;
		}
	}

	if(StuID == 0)
	{
		printf("Check your ID\n");
		exit(0);
	}

	while(1)
	{
		int a;

		printf("\n");
		printf("============================== FOR STUDENT ==============================\n");
		if(strcmp(StuName, "EzraMiller") == 0)
		{
			printf("Code_Name : FLASH    ");
		}
		else if(strcmp(StuName, "TomHolland") == 0)
		{
			printf("Code_Name : SPIDER-MAN    ");
		}

		printf("ID : %d    Name : %s    Major : %s    Grade : %d\n", StuID, StuName, StuMajor,Grade);
		printf("-------------------------------------------------------------------------\n");
		printf("1. Register MY Lecture\n2. Print MY Lecture Registered\n3. Print Lectures and Professors\n4. Print MY GP by Lecture\n5. Print MY Lecture by Semester\n6. Print MY GPA\n");
		printf("(If you'd like to exit, ENTER '0')\n>> ");
		scanf("%d", &a);

		switch(a)
		{
		case 1:
			RegisterLec();
			break;
		case 2:
			StuPrintLec();
			break;
		case 3:
			PrintLAP();
			break;
		case 4:
			PrintGP();
			break;
		case 5:
			PrintSemester();
			break;
		case 6:
			PrintGPA();
			break;
		case 0:
			printf("GoodBye\n");
			fclose(StuFP);
			exit(0);
		default:
			printf("Please check your answer.\n");
			break;
		}
	}	

	fclose(StuFP);
	return 0;
}

void RegisterLec()
{
	struct Lecture LecRec;
	struct GPOfLecture GPRec;
	FILE *LecFP;
	FILE *GPFP;
	LecFP = fopen("Lecture", "rb");
	GPFP = fopen("GPOfLecture", "ab+");
	char c;

	do
	{
		printf("================================ Lecture ================================\n");
		printf("Major       Lecture       Professor       Classroom      Time\n");
		printf("-------------------------------------------------------------------------\n");

		fseek(LecFP, 0, SEEK_SET);

		while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
		{
			int LecCMP = 100;

			fseek(GPFP, 0, SEEK_SET);

			while(fread(&GPRec, sizeof(GPRec), 1, GPFP) > 0)
			{
				if((GPRec.StuID == StuID) && (GPRec.LecID == LecRec.ID))
				{
					LecCMP = 0;
				}
			}
		
			if((LecCMP != 0) && (LecRec.ID != 0))
			{
				printf("%-11s %-13s %-15s %-14s %s\n", LecRec.Major, LecRec.Name, LecRec.ProfName, LecRec.Room, LecRec.Time);
			}
		}
		
		char EnterLecture[20] = {0};
	
		printf("-------------------------------------------------------------------------\n");
		printf("Enter the Name of Lecture you'll Register\n>> ");
		scanf("%s", EnterLecture);
	
		fseek(GPFP, sizeof(GPRec), SEEK_END);
		fseek(LecFP, 0, SEEK_SET);
		while((fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0))
		{
			int cmpLecName = strcmp(EnterLecture, LecRec.Name);
	
			if(cmpLecName == 0)
			{
				GPRec.StuID = StuID;
				GPRec.LecID = LecRec.ID;
				GPRec.ProfID = LecRec.ProfID;
				strcpy(GPRec.StuName, StuName);
				strcpy(GPRec.LecName, LecRec.Name);
				strcpy(GPRec.Major, StuMajor);
				GPRec.Grade = Grade;
				strcpy(GPRec.Semester, LecRec.Semester);
				GPRec.GP = 0.0;
	
				fwrite(&GPRec, sizeof(GPRec), 1, GPFP);

				sleep(1);
				printf("============================== Completed ================================\n");
				printf("(If you'd like to cancel, visit office)\n");
	
				break;
			}
		}
	
		printf("Continue to Register? (Y/N)\n>> ");
		scanf(" %c", &c);
	}while(c == 'Y');

	fclose(LecFP);
	fclose(GPFP);
}

void StuPrintLec()
{
	struct Lecture LecRec;
	struct GPOfLecture GPRec;
	FILE *LecFP;
	FILE *GPFP;
	LecFP = fopen("Lecture", "rb");
	GPFP = fopen("GPOfLecture", "rb");

	printf("========================== Registered Lectures ==========================\n");
	printf("Lecture     Professor     Classroom     Time\n");
	printf("-------------------------------------------------------------------------\n");
	
	while(fread(&GPRec, sizeof(GPRec), 1, GPFP) > 0)
	{
		if(GPRec.StuID == StuID && GPRec.GP == 0)
		{
			fseek(LecFP, (GPRec.LecID - Start_LecID)*sizeof(LecRec), SEEK_SET);

			if((fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0) && (LecRec.ID != 0))
				printf("%-11s %-13s %-13s %s\n", LecRec.Name, LecRec.ProfName, LecRec.Room, LecRec.Time);
		}
	}

	fclose(GPFP);
	fclose(LecFP);
}

void PrintLAP()
{
	struct Lecture LecRec;
	FILE *LecFP;
	struct Professor ProfRec;
	FILE *ProfFP;

	LecFP = fopen("Lecture", "rb");	
	ProfFP = fopen("Professor", "rb");	

	printf("======================== Lectures And Professors ========================\n");
	printf("Lecture        Major        Professor        Email\n");
	printf("-------------------------------------------------------------------------\n");

	fseek(LecFP, 0, SEEK_SET);

	while(fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0)
	{
		fseek(ProfFP, (LecRec.ProfID - Start_ProfID)*sizeof(ProfRec), SEEK_SET);

		if((fread(&ProfRec, sizeof(ProfRec), 1, ProfFP) > 0) && (ProfRec.ID != 0))
		{
			printf("%-14s %-12s %-16s %s\n", LecRec.Name, LecRec.Major, LecRec.ProfName, ProfRec.Email);
		}
	}

	fclose(LecFP);
	fclose(ProfFP);
}

void PrintGP()
{
	struct GPOfLecture GPRec;
	FILE *GPFP;
	GPFP = fopen("GPOfLecture", "rb");

	printf("=========================================================================\n");
	printf("Lecture        Grade         Semester        GradePoint\n");
	printf("-------------------------------------------------------------------------\n");

	while(fread(&GPRec, sizeof(GPRec), 1, GPFP) > 0)
	{
		if(StuID == GPRec.StuID && GPRec.GP != 0)
		{
			printf("%-14s %-13hd %-15s %.2lf\n", GPRec.LecName, GPRec.Grade, GPRec.Semester, GPRec.GP);
		}
	}

	fclose(GPFP);
}

void PrintSemester()
{
	struct GPOfLecture GPRec;
	struct Lecture LecRec;
	FILE *GPFP;
	FILE *LecFP;
	GPFP = fopen("GPOfLecture", "rb");
	LecFP = fopen("Lecture", "rb");
	
	printf("=========================================================================\n");
	printf("Year     Semester     Major          Lecture          Professor\n");
	printf("-------------------------------------------------------------------------\n");

	while(fread(&GPRec, sizeof(GPRec), 1, GPFP) > 0)
	{
		if(StuID == GPRec.StuID)
		{
			fseek(LecFP, (GPRec.LecID - Start_LecID)*sizeof(LecRec), SEEK_SET);

			if((fread(&LecRec, sizeof(LecRec), 1, LecFP) > 0) && (LecRec.ID != 0))
			{
				printf("%-8s %-12s %-14s %-16s %s\n", LecRec.Year, LecRec.Semester, LecRec.Major, LecRec.Name, LecRec.ProfName);
			}
		}
	}

	fclose(GPFP);
	fclose(LecFP);
}

void PrintGPA()
{
	struct Student StuRec;
	struct GPOfLecture GPRec;
	FILE *StuFP;
	FILE *GPFP;
	StuFP = fopen("Student", "rb+");
	GPFP = fopen("GPOfLecture", "rb");
	
	printf("=========================================================================\n");
	printf("Your GPA is ");

	double gpa = 0;
	int i = 0;

	while(fread(&GPRec, sizeof(GPRec), 1, GPFP) > 0)
	{
		if((StuID == GPRec.StuID) && (GPRec.GP != 0))
		{
			gpa += GPRec.GP;
			i++;
		}
	}

	gpa /= i;

	fseek(StuFP, (StuID - Start_StuID)*sizeof(StuRec), SEEK_SET);

	if((fread(&StuRec, sizeof(StuRec), 1, StuFP) > 0) && (StuRec.ID != 0))
	{
		StuRec.GPA = gpa;
		fseek(StuFP, -sizeof(StuRec), SEEK_CUR);
		printf("'%.2lf'\n", gpa);
		fwrite(&StuRec, sizeof(StuRec), 1, StuFP);
	}

	fclose(StuFP);
	fclose(GPFP);
}
