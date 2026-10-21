#include <stdio.h>
#include <string.h>

#define FILE_NAME "students.dat"
#define TEMP_FILE "temp.dat"

typedef struct {
    int roll;
    char name[50];
    char course[30];
    float marks;
} Student;

void clearInput(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin)) buf[strcspn(buf, "\n")] = '\0';
}

int rollExists(int roll) {
    FILE *fp = fopen(FILE_NAME, "rb");
    Student s;
    if (!fp) return 0;
    while (fread(&s, sizeof(Student), 1, fp) == 1)
        if (s.roll == roll) { fclose(fp); return 1; }
    fclose(fp);
    return 0;
}

void addStudent(void) {
    Student s;
    printf("Roll number: ");
    if (scanf("%d", &s.roll) != 1) { clearInput(); printf("Invalid input.\n"); return; }
    clearInput();
    if (rollExists(s.roll)) { printf("A student with this roll number already exists.\n"); return; }
    printf("Name: ");   readLine(s.name, sizeof s.name);
    printf("Course: "); readLine(s.course, sizeof s.course);
    printf("Marks: ");
    if (scanf("%f", &s.marks) != 1) { clearInput(); printf("Invalid input.\n"); return; }
    clearInput();

    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) { printf("Cannot open file.\n"); return; }
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Record added successfully.\n");
}

void displayStudents(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    Student s;
    int count = 0;
    if (!fp) { printf("No records found.\n"); return; }
    printf("\n%-8s %-25s %-15s %-8s\n", "Roll", "Name", "Course", "Marks");
    printf("-------------------------------------------------------------\n");
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("%-8d %-25s %-15s %-8.2f\n", s.roll, s.name, s.course, s.marks);
        count++;
    }
    fclose(fp);
    if (count == 0) printf("No records found.\n");
}

void searchStudent(void) {
    int roll, found = 0;
    Student s;
    printf("Enter roll number to search: ");
    if (scanf("%d", &roll) != 1) { clearInput(); printf("Invalid input.\n"); return; }
    clearInput();
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No records found.\n"); return; }
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("Found -> Roll: %d | Name: %s | Course: %s | Marks: %.2f\n",
                   s.roll, s.name, s.course, s.marks);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found) printf("Student not found.\n");
}

void updateStudent(void) {
    int roll, found = 0;
    Student s;
    printf("Enter roll number to update: ");
    if (scanf("%d", &roll) != 1) { clearInput(); printf("Invalid input.\n"); return; }
    clearInput();
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) { printf("No records found.\n"); return; }
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("New name: ");   readLine(s.name, sizeof s.name);
            printf("New course: "); readLine(s.course, sizeof s.course);
            printf("New marks: ");
            if (scanf("%f", &s.marks) != 1) { clearInput(); printf("Invalid input.\n"); fclose(fp); return; }
            clearInput();
            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            found = 1;
            break;
        }
    }
    fclose(fp);
    printf(found ? "Record updated successfully.\n" : "Student not found.\n");
}

void deleteStudent(void) {
    int roll, found = 0;
    Student s;
    printf("Enter roll number to delete: ");
    if (scanf("%d", &roll) != 1) { clearInput(); printf("Invalid input.\n"); return; }
    clearInput();
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No records found.\n"); return; }
    FILE *tmp = fopen(TEMP_FILE, "wb");
    if (!tmp) { fclose(fp); printf("Cannot create temp file.\n"); return; }
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) found = 1;
        else fwrite(&s, sizeof(Student), 1, tmp);
    }
    fclose(fp);
    fclose(tmp);
    remove(FILE_NAME);
    rename(TEMP_FILE, FILE_NAME);
    printf(found ? "Record deleted successfully.\n" : "Student not found.\n");
}

int main(void) {
    int choice;
    do {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n2. Display All\n3. Search\n4. Update\n5. Delete\n6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) { clearInput(); choice = 0; }
        else clearInput();
        switch (choice) {
            case 1: addStudent();      break;
            case 2: displayStudents(); break;
            case 3: searchStudent();   break;
            case 4: updateStudent();   break;
            case 5: deleteStudent();   break;
            case 6: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);
    return 0;
}
