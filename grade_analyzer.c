#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// custom header file
#include "grade_analyzer.h"


int main(int argc, char *argv[]) {

    // linked list head
    Student* head = NULL;

    // process the file and create a linked list
    head = processFile(head);
    if (head == NULL) {
        printf("Error processing file.\n");
        return 1;
    }

    // sort the linked list using merge sort
    head = mergeSort(head);
    if (head == NULL) {
        printf("Error sorting list.\n");
        return 1;
    }

    printf("\n");

    // print the linked list after sorting
    printList(head);

    printf("\n");

    // print the highest score
    printHighestScore(head);
    // print the lowest score
    int count = printLowestScore(head);
    // print the median score
    printMedianScore(head, count);
    // print the average score
    printAverageScore(head, count);

    printf("\n");

    // print the top 5 scores
    printTopFive(head);

    return 0;
}

// function to get the file name from the user
// and open the file
// returns NULL if the file cannot be opened
FILE* openFile() {
    char fileName[100];

    // gets the file name from the user
    // and stores it in the fileName variable
    printf("Enter the file name below (ei: text.txt):\n");
    scanf("%s", fileName);

    // opens the file in read mode
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    return file;
}

// function to close the file
void closeFile(FILE* file) {
    // closes the file
    fclose(file);
}

// function to create a new Student
// allocates memory for the new Student and its name
Student* createStudent(char* firstName, char* lastName, int score) {
    // allocate memory for the new Student
    Student* newStudent = (Student*) malloc(sizeof(Student));

    // allocates data to the new Student
    // set the next Student to NULL
    newStudent->next = NULL;
    // concatenate the first and last names
    strcpy(newStudent->first, firstName);
    strcpy(newStudent->last, lastName);
    // set the score
    newStudent->score = score;

    // return the new Student
    return newStudent;
}

// function to process the file and create a linked list
Student* processFile(Student* head) {

    // opens the file
    FILE* file = openFile();
    if (file == NULL) {
        return NULL;
    }
    
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int score;

    // read the file line by line, stopping at EOF
    while(fscanf(file, "%s %s %d\n", lastName, firstName, &score) != EOF) {
        // create a new Student
        Student* newStudent = createStudent(firstName, lastName, score);
        if (newStudent == NULL) {
            printf("Error creating Student.\n");
            closeFile(file);
            return NULL;
        }

        // add the new Student to the linked list
        newStudent->next = head;
        head = newStudent;
    }

    // close the file
    closeFile(file);

    // return the head of the linked list
    return head;
}

// function to print the linked list
void printList(Student* head) {
    // print the linked list
    Student* current = head;
    printf("Sorted List by Score:\n");
    while (current != NULL) {
        printf("%s %s - %d\n", current->last, current->first, current->score);
        current = current->next;
    }
}

// function to sort the linked list using merge sort method
Student* mergeSort(Student* head) {
    // base case: if the list is empty or has only one Student
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // split the list into two halves
    Student* middle = getMiddle(head);
    Student* nextToMiddle = middle->next;

    // set the next of the middle Student to NULL
    middle->next = NULL;

    // recursively breaks down the list into smaller lists
    // until its a single Students
    Student* left = mergeSort(head);
    Student* right = mergeSort(nextToMiddle);

    // merge the sorted halves
    Student* sortedList = sortedMerge(left, right);

    return sortedList;
}

// function to get the middle Student of the linked list
// using the fast and slow pointer method
Student* getMiddle(Student* head) {
    if (head == NULL) {
        return head;
    }

    Student* slow = head;
    Student* fast = head->next;

    // move fast pointer two Students and slow pointer one Student
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// function to merge two sorted linked lists
// returns the head of the merged list
Student* sortedMerge(Student* left, Student* right) {
    // if either list is empty, return the other list
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    // compare the grades and merge the lists
    if (left->score >= right->score) {
        left->next = sortedMerge(left->next, right);
        return left;
    }
    else {
        right->next = sortedMerge(left, right->next);
        return right;
    }
}

// function to print the highest score in a sorted list
void printHighestScore(Student* head) {
    // print the highest score
    if (head == NULL) {
        printf("No Students in the list.\n");
        return;
    }

    // print the highest score
    printf("Highest Score: %d\n", head->score);
}

// function to print the lowest score in a sorted list
// also doubles at counting the number of Students in the list
int printLowestScore(Student* head) {
    if (head == NULL) {
        printf("No Students in the list.\n");
        return 0;
    }

    int count = 0;
    // traverse to the end of the list, counting along the way
    Student* current = head;
    while (current->next != NULL) {
        count++;
        current = current->next;
    }

    // print the lowest score
    printf("Lowest Score: %d\n", current->score);

    // return the number of Students in the list
    return count + 1;
}

// function to print the median score in a sorted list
void printMedianScore(Student* head, int count) {
    if (head == NULL) {
        printf("No Students in the list.\n");
        return;
    }

    // find the median score
    Student* current = head;
    for (int i = 0; i < (count / 2) - 1; i++) {
        current = current->next;
    }

    // print the median score depending if the count is even or odd
    if (count % 2 == 0)
        printf("Median Score: %.2f\n", ((double)current->score + (double)current->next->score) / 2.0);

    else 
        printf("Median Score: %d\n", current->score);
}

// function to print the average score in a sorted list
void printAverageScore(Student* head, int count) {
    if (head == NULL) {
        printf("No Students in the list.\n");
        return;
    }

    // calculate the average score
    int sum = 0;
    Student* current = head;
    while (current != NULL) {
        sum += current->score;
        current = current->next;
    }

    // print the average score
    printf("Class Average: %.2lf\n", (double)sum / count);
}

// function to print the top 5 scores in a sorted list
// prints the first 5 Students in the list
// if there are less than 5 Students, it prints all of them
void printTopFive(Student* head) {
    if (head == NULL) {
        printf("No Students in the list.\n");
        return;
    }

    printf("Top 5 Scores:\n");
    for (int i = 0; i < 5 && head != NULL; i++) {
        printf("%s %s - %d\n", head->last, head->first, head->score);
        head = head->next;
    }
}