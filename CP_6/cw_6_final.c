#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char surname[30+1];
    char initials[2+1];
    char gender[6+1];
    int school_number;
    char have_medal;
    int mathematics;
    int physics;
    int informatics;
    int literature;
    char passed_writing;
} Student;

void create()
{
    char fileName[40];
    FILE* file;
    printf("Enter the name of the file you want to create:\n");
    scanf("%s", fileName);
    file = fopen(fileName, "rb");
    if (file != NULL) {
        printf("Such file already exists\n");
    } else {
        file = fopen(fileName, "ab");
    }
    printf("Creation was successful!\n");
    fclose(file);
}

void add()
{
    int records;
    char fileName[40];
    FILE* file;
    Student add;
    printf("Enter the name of the file you want to add the records:\n");
    scanf("%s", fileName);
    file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Such file not exists!\n");
    }
    else {
        file = fopen(fileName, "a");
        printf("Enter how many records do you want to add:\n");
        scanf("%d", &records);
        for (int i = 0; i < records; i++) {
            printf("Enter student's surname:\n");
            scanf("%s", add.surname);
            printf("Enter student's initials:\n");
            scanf("%s", add.initials);
            printf("Enter student's gender:\n");
            scanf("%s", add.gender);
            printf("Enter student's number of school:\n");
            scanf("%d", &add.school_number);
            printf("Enter student's have medal:\n");
            scanf("%s", &add.have_medal);
            printf("Enter student's mathematics:\n");
            scanf("%d", &add.mathematics);
            printf("Enter student's physics:\n");
            scanf("%d", &add.physics);
            printf("Enter student's informatics:\n");
            scanf("%d", &add.informatics);
            printf("Enter student's literature:\n");
            scanf("%d", &add.literature);
            printf("Enter student's passed of writing:\n");
            scanf("%s", &add.passed_writing);
	    
	    fprintf(file, "%s %s %s %d %s %d %d %d %d %s\n", add.surname, add.initials, add.gender, add.school_number, &add.have_medal, add.mathematics, add.physics, add.informatics, add.literature, &add.passed_writing);
	   
        }
        printf("Records added successfully!\n");
        fclose(file);
    }
}

void generation()
{
    int records;
    int rd;
    char fileName[40];
    FILE* file;
    Student gen;
    printf("Enter the name of the file you want to add the records:\n");
    scanf("%s", fileName);
    file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Such file not exists!\n");
    }
    else {
        file = fopen(fileName, "a");
        printf("Enter how many records do you want to generate:\n");
        scanf("%d", &records);
        for (int i = 0; i < records; i++) {
            gen.surname[0] = rand()%26+'A';
	    rd = rand()%5+6;
            for(int e = 1; e < rd; e++) {
                gen.surname[e] = rand()%26+'a';
            }
            gen.initials[0] = rand()%26+'A';
            gen.initials[1] = rand()%26+'A';
            rd =rand()%2;
            if (rd == 0) {
                gen.gender[0] = 'f';
                gen.gender[1] = 'e';
                gen.gender[2] = 'm';
                gen.gender[3] = 'a';
                gen.gender[4] = 'l';
                gen.gender[5] = 'e';
            } else {
                gen.gender[0] = ' ';
                gen.gender[1] = ' ';
                gen.gender[2] = 'm';
                gen.gender[3] = 'a';
		gen.gender[4] = 'l';
		gen.gender[5] = 'e';
            }
            gen.school_number = 100 + rand()%3000;
            rd =rand()%2;
            if (rd == 0) {
                gen.have_medal = '-';
            } else {
                gen.have_medal = '+';
            }
            gen.mathematics = 2 + rand()%4;
            gen.physics = 2 + rand()%4;
            gen.informatics = 2 + rand()%4;
            gen.literature = 2 + rand()%4;
            rd =rand()%2;
            if (rd == 0) {
                gen.passed_writing = '-';
            } else {
                gen.passed_writing = '+';
            }

	    fprintf(file, "%s %s %s %d %s %d %d %d %d %s\n", gen.surname, gen.initials, gen.gender, gen.school_number, &gen.have_medal, gen.mathematics, gen.physics, gen.informatics, gen.literature, &gen.passed_writing);
	    
        }
	 printf("Records added successfully!\n");
        fclose(file);
    }
}

void print()

{
    char filename[40];
    printf("Enter the name of the file you want to print:\n");
    scanf("%s", filename);
    FILE *iter = fopen(filename, "rb");
    Student s;
    int prov = 0;
    int count = 0;
    while(fscanf(iter, "%s %2s %s %d %c %d %d %d %d %c", s.surname, s.initials, s.gender, &s.school_number,
		 &s.have_medal, &s.mathematics, &s.physics, &s.informatics, &s.literature, &s.passed_writing) != EOF) {
      count++;
    }
    fclose(iter);
    
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Such file not exists!\n");
    }
    else {
        Student *students = (Student*)calloc(count, sizeof(Student));
        Student *result = (Student*)calloc(count, sizeof(Student));
        int i = 0, ires = 0;
        while(!feof(file)){
            fscanf(file, "%s %2s %s %d %c %d %d %d %d %c", s.surname, s.initials, s.gender, &s.school_number,
                   &s.have_medal, &s.mathematics, &s.physics, &s.informatics, &s.literature, &s.passed_writing);
            students[i++] = s;
        }
        puts("----------------------------------------------------------------------------------------------");
        puts("|  Surname   |Initials|Gender|School|Medal|Mathematics|Physics|Informatics|Literature|Writing|");
        puts("----------------------------------------------------------------------------------------------");

        for (int j = 0; j < count; ++j) {
            Student s = students[j];
            if(s.mathematics != prov && s.physics != prov && s.informatics != prov
               && s.literature != prov){
                printf("|%11s%s|%5s%3s|%6s|%5d%s|%3c%2s|%6d%5s|%4d%3s|%6d%5s|%6d%4s|%4c%3s|\n", s.surname, " ", s.initials, " ", s.gender, s.school_number, " ",
                       s.have_medal, " ",  s.mathematics, " ",  s.physics, " ", s.informatics, " ", s.literature, " ", s.passed_writing, " ");
                result[ires++] = s;
            }
        }

        if(ires == 0){
            puts("|                                          NO DATA                                           |");
        }

        puts("----------------------------------------------------------------------------------------------");

        fclose(file);
    }
}


void removes()
{
    char fileName[40];
    printf("Enter the name of the file you want to delete:\n");
    scanf("%s", fileName);
    FILE* file;
    file = fopen(fileName, "rb");
    if (!file) {
        printf("Such file not exists!\n");
    }
    else {
        remove(fileName);
        printf("The file was successfully deleted!\n");
        fclose(file);
    }
}

void secret()
{
    printf("\nHave a nice day!\n");
    printf("                                                       \\   \\|'\n");
    printf("                                                        -\\  -|   |/\n");
    printf("                                                       _  \\/'|/ \\/.\n");
    printf("                                                        `--\\o|o)/_/--\n");
    printf("                                                            \\^ /\n");
    printf("                    ._                                 \\__` }v\\{   |/_\n");
    printf("               _   / /                                    \\_{\\/}---'\n");
    printf("            ('o_o)/_/               'Oo                     }  {\n");
    printf("               \\ /              (\\/   .-)                   {  }\n");
    printf("              / \\               `   .-\\`\\                  //|`\\\\\n");
    printf("\n");
}

void function()
{
    char filename[40];
    printf("Enter the name of the file you want to print function result:\n");
    scanf("%s", filename);
    FILE *iter = fopen(filename, "rb");
    Student s;
    int count = 0;
    while(fscanf(iter, "%s %2s %s %d %c %d %d %d %d %c", s.surname, s.initials, s.gender, &s.school_number,
		 &s.have_medal, &s.mathematics, &s.physics, &s.informatics, &s.literature, &s.passed_writing) != EOF) {
      count++;
    }
    fclose(iter);
    
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Such file not exists!\n");
    }
    else {
        Student *students = (Student*)calloc(count, sizeof(Student));
        Student *result = (Student*)calloc(count, sizeof(Student));
        int i = 0, ires = 0;
        while(!feof(file)){
            fscanf(file, "%s %2s %s %d %c %d %d %d %d %c", s.surname, s.initials, s.gender, &s.school_number,
                   &s.have_medal, &s.mathematics, &s.physics, &s.informatics, &s.literature, &s.passed_writing);
            students[i++] = s;
        }
        puts("----------------------------------------------------------------------------------------------");
        puts("|  Surname   |Initials|Gender|School|Medal|Mathematics|Physics|Informatics|Literature|Writing|");
        puts("----------------------------------------------------------------------------------------------");

        for (int j = 0; j < count; ++j) {
            Student s = students[j];
            if(s.gender[0] == 'f' && s.mathematics != s.physics && s.physics != s.informatics && s.informatics != s.mathematics
               && s.mathematics != s.literature && s.physics != s.literature && s.informatics != s.literature){
                printf("|%11s%s|%5s%3s|%6s|%5d%s|%3c%2s|%6d%5s|%4d%3s|%6d%5s|%6d%4s|%4c%3s|\n", s.surname, " ", s.initials, " ", s.gender, s.school_number, " ",
                       s.have_medal, " ",  s.mathematics, " ",  s.physics, " ", s.informatics, " ", s.literature, " ", s.passed_writing, " ");
                result[ires++] = s;
            }
        }

        if(ires == 0){
            puts("|                                          NO DATA                                           |");
        }

        puts("----------------------------------------------------------------------------------------------");


        fclose(file);
    }
}

void print_help()
{
    printf("Welcome to the program for working with databases!\nYou have the following options:\n");
    printf("1) Create the database(-c)\n2) Add an entry to the database(-a)\n3) Print the database(-p)\n");
    printf("4) Delete the database(-d)\n5) Print function result (-f)\n6) Auto-generate entry to the database (-g)\n");
    printf("7) Print secret (-s)\n");
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Need exactly two arguments\n");
        exit(1);
    }
    if (!strcmp(argv[1], "-a")) {
        add();
    }
    else if (!strcmp(argv[1], "-p")) {
        print();
    }
    else if (!strcmp(argv[1], "-d")) {
        removes();
    }
    else if (!strcmp(argv[1], "-h")) {
        print_help();
    }
    else if (!strcmp(argv[1], "-c")) {
        create();
    }
    else if (!strcmp(argv[1], "-f")) {
        function();
    }
    else if (!strcmp(argv[1], "-g")) {
        generation();
    }
    else if (!strcmp(argv[1], "-s")) {
        secret();
    }
    else {
        printf("Unknown command\n");
    }
    return 0;

}
