#ifndef GRADE_ANALYZER_H
#define GRADE_ANALYZER_H

#include <stdio.h>

#define MAX_NAME_LENGTH 30

// linked list Student structure
typedef struct Student {
    char first[30], last[30];
    int score;
    struct Student* next;
} Student;
    

// function to open the file
FILE* openFile();
// function to close the file
void closeFile(FILE* file);

// function to create a new Student
Student* createStudent(char* firstName, char* lastName, int score);

// function to process the file and create a linked list
Student* processFile(Student* head);

// function to print the linked list
void printList(Student* head);

// function to sort the linked list using merge sort method
Student* mergeSort(Student* head);
// function to get the middle Student of the linked list
Student* getMiddle(Student* head);
// function to merge two sorted linked lists
Student* sortedMerge(Student* left, Student* right);

// function to print the highest score in a sorted list
void printHighestScore(Student* head);
// function to print the lowest score in a sorted list
int printLowestScore(Student* head);
// function to print the median score in a sorted list
void printMedianScore(Student* head, int count);
// function to print the average score in a sorted list
void printAverageScore(Student* head, int count);

// function to print the top 5 scores in a sorted list
void printTopFive(Student* head);

#endif // GRADE_ANALYZER_H