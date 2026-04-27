/*Yael Otmazgin 212531115
Linoy Bony 211820824 
Exercise 02*/
#include "College.h"
void College::addCourse()
{
	// Add a course to the courses table using hash table insertion.
	string name;
	int num;
	cout << "enter course name" << endl;
	cin >> name;
	cout << "enter course id" << endl;
	cin >> num;

	// TODO: Add the course to the courses table

	courses.insert(num, name); // Utilize hash table insert method
}
void College::removeCourse()
{
	// Remove a course from the courses table using hash table removal.
	int num;
	cout << "enter course id" << endl;
	cin >> num;

	// TODO: Remove the course from the course table

	courses.remove(num); // Utilize hash table remove method
}
void College::addStudent()
{
	// Add a student to the students table using hash table insertion.
	string name;
	cout << "enter students name" << endl;
	cin >> name;
	// Empty list representing no enrolled courses.
	list<int> lst;

	// TODO: Insert the student to the students table

	students.insert(name, lst); // Utilize hash table insert method
}
void College::removeStudent()
{
	// Remove a student from the students table using hash table removal.
	string name;
	cout << "enter students name" << endl;
	cin >> name;

	// TODO: Remove the student from the student table
	students.remove(name); // Utilize hash table remove method
}
void College::registration()
{
	// Register student for course, update student's table.
	string name;
	cout << "enter students name" << endl;
	cin >> name;
	int num;
	cout << "enter course id" << endl;
	cin >> num;
	try {
		// TODO: add the course id (if it exists) to the end of the student's course-list

		list<int> coursesList = students.search(name); // Retrieve student's course list
		coursesList.push_back(num); // Add the new course to the list
		students.remove(name); // Remove the student from the table
		students.insert(name, coursesList); // Insert the updated list 
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}
void College::removeReg()
{
	// Remove course registration for student, update student's table.
	string name;
	cout << "enter students name" << endl;
	cin >> name;
	int num;
	cout << "enter course id" << endl;
	cin >> num;
	try {
		// TODO: remove the course id (if it exists) from the student's list

		list<int>coursesList = students.search(name); // Get student's courses
		coursesList.remove(num); // Remove the course
		students.remove(name); // Remove the student
		students.insert(name, coursesList); // Update student's courses in the hash table
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
}
void College::print()
{
	// Print courses enrolled by a student.
	string name;
	cout << "enter students name" << endl;
	cin >> name;
	try {
		// TODO: fix, so this would be the student's courses list
		list<int> lst = students.search(name); // Student's courses list
		for (list<int>::iterator it = lst.begin(); it != lst.end(); it++)
		{
			int k = *it;
			// TODO: fix
			Course c = courses.search(k); // Find the curse.
			cout << c.getName() << ' '; // Display the name of the course
		}
		cout << endl;
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}

}
void College::printStudentsTable() {
	students.print();
}
void College::printCoursesTable() {
	courses.print();
}