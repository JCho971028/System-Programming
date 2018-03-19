/*---- main.c -----*/
#include <stdio.h>
#include "Student.h"
#include "Employee.h"
#include "Professor.h"

int main()
{
	int a=0;
	int ID=0;

	printf("\n================= Hannam University Management Program ==================\n");
	printf("1. Professor\n2. Employee\n3. Student\n(If you'd like to exit, ENTER '0')\n>> ");

	scanf("%d", &a);

//	while(1)
//	{
		switch(a)
		{
		case 1:
			printf("Enter Professor's ID\n>> ");
			scanf("%d", &ID);
			MainProfessor(ID);
			break;
		case 2:
			printf("Enter Employee's ID\n>> ");
			scanf("%d", &ID);
			MainEmployee(ID);
			break;
		case 3:
			printf("Enter Student's ID\n>> ");
			scanf("%d", &ID);
			MainStudent(ID);
			break;
		case 0:
			printf("GoodBye\n");
			return 0;
		default:
			printf("Please check your answer\n");
			break;
		}
//	}
	return 0;
}


//Hannam University 20160745
