Main : main.o MainProfessor.o MainEmployee.o MainStudent.o
	gcc -g -o Main main.o MainProfessor.o MainEmployee.o MainStudent.o
main.o : main.c
	gcc -g -c -o main.o main.c
MainProfessor.o : MainProfessor.c
	gcc -g -c -o MainProfessor.o MainProfessor.c
MainEmployee.o : MainEmployee.c
	gcc -g -c -o MainEmployee.o MainEmployee.c
MainStudent.o : MainStudent.c
	gcc -g -c -o MainStudent.o MainStudent.c
clean :
	rm *.o Main
