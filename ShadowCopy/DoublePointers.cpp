#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define _CRTDBG_MAP_ALLOC // Code for detecting memory leaks. Part 1/4.
#include <stdlib.h> // Code for detecting memory leaks. Part 2/4.
#include <crtdbg.h> // Code for detecting memory leaks. Part 3/4.


using namespace std;

struct Student
{
	char *name;
	float gpa;
};

Student** createStudentList(char **names, int size); // Makes a shallow copy 
Student** createStudentList2(char **names, int size); // Makes a deep copy
bool destroyList(Student** list, int size);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Code for detecting memory leaks. Part 4/4.

	int size; // stores how many names have been inputted
	cout << "How many names do you want to enter?: ";
	cin >> size;
	cin.ignore(100, '\n'); // clears any extra data and the end of line character
	cout << endl;

	// creates and array of cstrings to store names
	char **names = new char *[size];

	// gets each name and adds it to the names array
	for (int i(0); i < size; i++)
	{
		names[i] = new char[100];
		cout << "Enter name " << i + 1 << ": ";
		cin.get(names[i], 100);
		cin.ignore(100, '\n');
		cout << endl;
	}

	// copies the names into the student arrays
	Student **listShallow = createStudentList(names, size); // listShallow is a shallow copy
	Student **listDeep = createStudentList2(names, size); // listDeep is a deep copy

														  // you can destroy them the same way. The only difference is when 
														  // you destroy the listShallow it also destroys the cstrings in the names 
														  // because both the names and list[]shallow->name are pointers that point to the same cstring
	bool worked = destroyList(listShallow, size);
	bool worked2 = destroyList(listDeep, size);


	delete[] names;
	return 0;
}

// this function does a shallow copy.
Student** createStudentList(char **names, int size)
{
	// creates a new array of student pointers
	Student **list = new Student *[size];
	for (int i(0); i < size; i++)
	{
		// allocates memory for a student object
		list[i] = new Student;

		// copies the pointer from the names list to the names field in the student object
		list[i]->name = names[i];
		list[i]->gpa = 0;
	}

	return list;
}

// creates a deep copy
Student** createStudentList2(char **names, int size)
{
	// creates a new array of student pointers
	Student **list = new Student *[size];

	// Loops through and copies each element one by one
	for (int i(0); i < size; i++)
	{
		// allocates memory for a student object
		list[i] = new Student;

		//** next two steps do the deep copy
		// Step 1: allocates just enough memory to store names[i] into list[i]->name
		// The reason you need to create the name strlen + 1 size instead of just strlen size is
		// because you need to allow for the \0 after the name to mark the end position
		list[i]->name = new char[strlen(names[i]) + 1];

		// copies names[i] into list[i]->name 
		// Step 2: copies the pointer from the names list to the names field in the student object
		strcpy(list[i]->name, names[i]);

		// the gpa is just a float and not a pointer so it always does a deep copy
		// even if the next line had something like list[i]->gpa = gpa[i]
		list[i]->gpa = 0;
	}

	return list;
}

bool destroyList(Student** list, int size)
{
	for (int i(0); i < size; i++)
	{
		// deletes the student name cstring at list[i]
		delete[] list[i]->name;

		// deletes the student pointer at list[i]
		delete list[i];
	}
	// deletes all the pointers in list
	delete[] list;
	return true;
}