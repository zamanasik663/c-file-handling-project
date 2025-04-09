// file handling project in c
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


void insert_record();
void display_record();
void delete_record();
void search_record();
void update_record();
// void sort_record();

// structure to store student information
struct student
{
    int roll_no;
    char name[50];
    char sec[10];
    int marks;
    float grade;
};
struct student s;

int main()
{
    system("cls");
    int choice;

    do
    {
        
        printf("\n\n\t\t\tSTUDENT RECORD MANAGEMENT SYSTEM\n\n");
        printf("\t\t\t------------------------------------");
        printf("\n\t\t\t1. Insert Student Record\n");
        printf("\n\t\t\t2. Display Student Record\n");
        printf("\n\t\t\t3. Delete Student Record\n");
        printf("\n\t\t\t4. Search Student Record\n");
        printf("\n\t\t\t5. Update Student Record\n");
        // printf("6. Sort Student Record\n");
        printf("\n\t\t\t6. Exit\n");
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &choice);
        
        system("cls");

        switch (choice)
        {
        case 1:
            
            insert_record();
            break;
        case 2:
            
            display_record();
            break;
        case 3:
            
            delete_record();
            break;
        case 4:
            
            search_record();
            break;
        case 5:
            
            update_record();
            break;
        // case 6:
        //     sort_record();
        //     break;
        case 6:
            exit(0); // Use exit(0) for proper program termination
        default:
            printf("\nInvalid choice! Please try again.\n");
            break;
        }

    } while (choice != 6); // Exit when choice is 6
    system("cls");

    return 0;
}

// Function to insert a student record
void insert_record()
{
    FILE *fp;
    fp = fopen("stu.txt", "ab+"); // Open file in append mode
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    printf("\n\t\tprevious stored data: ");
    display_record(); // Display previous records

    printf("\n\t\t------ Enter new Student data -------");

    printf("\n\t\tEnter student Roll No: ");
    scanf("%d", &s.roll_no);
    fflush(stdin);
    printf("\n\t\tEnter student Name: ");
    gets(s.name);
    printf("\n\t\tEnter student Section: ");
    gets(s.sec);
    printf("\n\t\tEnter total Marks: ");
    scanf("%d", &s.marks);
    printf("\n\t\tEnter Grade: ");
    scanf("%f", &s.grade);

    fwrite(&s, sizeof(s), 1, fp); // Write record to file
    {
        printf("\n\t\tStudent Record inserted successfully!");
    }
    fclose(fp); // Close the file

    printf("\n\t\tUpdated Record!\n");
    display_record(); // Display updated records
}

// Function to display all student records
void display_record()
{
    FILE *fp;
    fp = fopen("stu.txt", "rb"); // Open file in read mode
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    printf("\n\t\t------ Student Records -------\n\n");
    printf("\t\tRoll_No\t\tName\t\tSection\t\tMarks\t\tGrade\n");
    while (fread(&s, sizeof(s), 1, fp) == 1) // Read records from file
    {
        printf("\t\t%d\t\t%s\t\t%s\t\t%d\t\t%.2f\n", s.roll_no, s.name, s.sec, s.marks, s.grade);
    }
    fclose(fp); // Close the file
}

// search function to search for a student record by roll number
void search_record()
{
    FILE *fp;
    int roll_no, found = 0;
    fp = fopen("stu.txt", "rb"); // Open file in read mode
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    printf("\n\t\tEnter Roll No which you want to search: ");
    scanf("%d", &roll_no);
    while (fread(&s, sizeof(s), 1, fp) > 0 && found == 0) // Read records from file
    {
        if (s.roll_no == roll_no) // Check if roll number matches
        {
            printf("\n\t\tStudent Record Found!\n\n");
            printf("\t\tRoll_No\t\tName\t\tSection\t\tMarks\t\tGrade\n");
            printf("\t\t%d\t\t%s\t\t%s\t\t%d\t\t%.2f\n", s.roll_no, s.name, s.sec, s.marks, s.grade);
            found = 1;
            break; // Exit loop if record is found
        }
    }
    if (found == 0)
    {
        printf("\n\t\tRecord not found!\n");
    }
    fclose(fp); // Close the file
}

// Function to delete a student record by roll number
void delete_record()
{

    char name[40];
    unsigned flag = 0;
    FILE *fp, *ft;
    fp = fopen("stu.txt", "rb"); // Open file in read mode
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\n\t\tPrevious Stored Data -----");
    display_record();
    printf("\n\t\tEnter student name which you want to delete:  ");
    scanf("%39s", name); // Safer input with length limit
    ft = fopen("stu1.txt", "ab+");
    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        if (strcmp(name, s.name) == 0)
        {
            flag = 1; // Record found and will be skipped (not written to new file)
        }
        else
        {
            fwrite(&s, sizeof(s), 1, ft); // Write all non-matching records
        }
    }
    if (flag)
    {
        printf("\n\t\tRecord deleted successfully!!");
    }
    else
    {
        printf("\n\t\tNo such record found!!");
    }
    fclose(fp);
    fclose(ft);
    remove("stu.txt");
    rename("stu1.txt", "stu.txt");
    printf("\n\t\tUpdate Record");
    display_record();
}

// function to update a student record by roll number
void update_record()
{
    int ro, flag = 0;
    FILE *fp;
    fp = fopen("stu.txt", "rb+"); // Open file in append mode
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    printf("\n\t\tEnter roll number which you want to update:  ");
    scanf("%d", &ro);
    printf("\n\t\tPreviously stored record of given roll number----");
    while (fread(&s, sizeof(s), 1, fp) > 0 && flag == 0)
    {
        if (s.roll_no == ro)
        {
            flag = 1;
            printf("\n\t\tRoll_No\t\tName\t\tSection\t\tMarks\t\tGrade\n");
            printf("\t\t%d\t\t%s\t\t%s\t\t%d\t\t%.2f\n", s.roll_no, s.name, s.sec, s.marks, s.grade);

            printf("\n\t\tEnter new data which you want!!");

            printf("\n\t\tUpdate student Roll No: ");
            scanf("%d", &s.roll_no);
            fflush(stdin);
            printf("\n\t\tUpdate student Name: ");
            gets(s.name);
            printf("\n\t\tUpdate student Section: ");
            gets(s.sec);
            printf("\n\t\tUpdate total Marks: ");
            scanf("%d", &s.marks);
            printf("\n\t\tUpdate Grade: ");
            scanf("%f", &s.grade);
            fseek(fp, -(long)sizeof(s), 1);
            fwrite(&s, sizeof(s), 1, fp);
            printf("\n\t\tsuccessfully updated record.Check to the display");
        }
    }
    if (flag == 0)
    {
        printf("\n\t\tError: Something went wrong!!");
    }
    fclose(fp);
}
