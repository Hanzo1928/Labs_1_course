#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char surname[30+1];
    char initials[2+1];
    char gender;
    int schoolNumber;
    char haveMedal;
    int math, phys, inf;
    char passedWriting;
} Student;

int main(int argc, char* argv[]){
    char *filename;
    if(argc < 2){
        filename = "test.txt";
    } else{
        filename = argv[1];
    }

    const int count = 15;
    FILE *file = fopen(filename, "r");

    Student *students = (Student*)calloc(count, sizeof(Student));
    Student *result = (Student*)calloc(count, sizeof(Student));
    int i = 0, ires = 0;
    while(!feof(file)){
        Student s;
        fscanf(file, "%s %2s %c %d %c %d %d %d %c", s.surname, s.initials, &s.gender, &s.schoolNumber,&s.haveMedal, &s.math, &s.phys, &s.inf, &s.passedWriting);
        students[i++] = s;
    }

    puts("-----------------------------------------------------------");
    puts("|Surname     |In|Gender|School|Medal|Math|Phys|Inf|Writing|");
    puts("-----------------------------------------------------------");

    for (int j = 0; j < count; ++j) {
        Student s = students[j];
        if(s.gender == 'f' && s.math != s.phys && s.phys != s.inf && s.inf != s.math){
            printf("|%12s|%2s|%2c|%6d|%2c|%4d|%4d|%3d|%7c|\n", s.surname, s.initials, s.gender,
                   s.schoolNumber, s.haveMedal, s.math, s.phys, s.inf, s.passedWriting);
            result[ires++] = s;
        }
    }

    if(ires == 0){
        puts("|                       NO DATA                        |");
    }

    puts("--------------------------------------------------------");


    fclose(file);
}
