#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include<cstdlib>
#include<ctime>
#include<chrono>

using namespace std;

// Declaring structures
struct myAdmin {
	string name;
	int age;
	char gender;
	string mail;
	string skill;
	string id;
	string password;
};
struct myTeacher {
	string name;
	int age;
	char gender;
	string course;
	string mail;
	string id;
	string password;
};
struct myStudent {
	string name;
	int age;
	char gender;
	string section;
	string grade;
	string department;
	string id;
	string password;
};
struct myQuestion {
	int num;
	string text;
	string options[4];
	int answer;
};
struct myQuiz {
	string title;
	int id;
	string description;
	string subject;
	string section;
	myQuestion questions[5];
	int timer;
};
struct myAssign {
	string section;
	int id;
};

// Functions prototype
myAdmin admin;
void start();
void Admin(myAdmin);
void admin_menu();
void read_admin_data(myAdmin&, const string& filename);
void update_admin_info(myAdmin&, const string& filename);
void register_teacher(const string& filename);
void register_student(const string& filename);
int registered_teachers;
int count_teachers(const string& filename);
myTeacher* teach;
void read_teacher_data(myTeacher*, int, const string& filename);
int registered_students;
int count_students(const string& filename);
myStudent* student;
void read_student_data(myStudent*, int, const string& filename);
void teacher_credentials(myTeacher*);
void student_credentials(myStudent*);
void search_user();
void search_teacher(myTeacher*, int);
void search_student(myStudent*, int);
void remove_user();
void remove_teacher(myTeacher*, int, const string& filename);
void remove_student(myStudent*, int, const string& filename);
void Teacher(myTeacher*, int);
void teacher_menu();
void update_teacher_info(myTeacher*, const string& filename);
int teach_index;
void Student(myStudent*, int);
void student_menu();
void view_assigned_quiz(myStudent*, int);
void update_student_info(myStudent*, const string& filename);
int str_index;
void create_quiz();
int saved_quiz;
int count_quiz(const string& filename);
myQuiz* Quiz;
void view_quiz(myQuiz*, int);
void read_quiz_data(myQuiz*, int, const string& filename);
void edit_quiz(myQuiz*, int);
void assign_quiz(myQuiz*, int);
void solve_assigned_quiz();
char calculateGrade(int score, int total);
void view_result_student();
int assigned_quiz;
int count_assigned_quiz(const string& filename);
myAssign* Assign;
void read_assign_quiz_data(myAssign*, int, const string& filename);
void view_result_student_one();

// Main function definition
int main() {

	// Store's the index of logged in teacher
	teach_index = 0;
	// Store's the index of logged in student
	str_index = 0;

	// Load admin data from file to structure
	read_admin_data(admin, "admin.txt");

	// Counting registered teachers
	registered_teachers = count_teachers("teacher_info.txt");

	// Creating dynamic array to store data of registered teachers
	teach = new myTeacher[registered_teachers];

	// Load teachers data to dynamic array from file
	read_teacher_data(teach, registered_teachers, "teacher_info.txt");

	// Counting registered students
	registered_students = count_students("teacher_info.txt");

	// Creating dynamic array to store data of registered students
	student = new myStudent[registered_students];

	// Load teachers data to dynamic array from file
	read_student_data(student, registered_students, "student_info.txt");

	// Counting saved quizzes
	saved_quiz = count_quiz("quiz_info.txt");

	// Creating dynamic array to store data of saved quizzes
	Quiz = new myQuiz[saved_quiz];

	// Load quiz data to dynamic array from file
	read_quiz_data(Quiz, saved_quiz, "quiz_info.txt");

	// Counting assigned quizzes
	assigned_quiz = count_assigned_quiz("assign_info.txt");

	// Creating dynamic array to store data of assigned quizzes
	Assign = new myAssign[assigned_quiz];

	// Load assign quiz data to dynamic array from file
	read_assign_quiz_data(Assign, assigned_quiz, "assign_info.txt");
	/*cout << registered_students;*/

	// Start execution
	start();

	return 0;
}

// Functions definition
void start() {
	Sleep(300);
	system("cls");
	cout << "\t\t\t\t-------------------------------------------\n";
	cout << "\t\t\t\t--- WELCOME TO MENTORA-SMART QUIZ MAKER ---\n";
	cout << "\t\t\t\t-------------------------------------------\n";
	int choice;
	cout << "1.LOGIN AS ADMIN\n";
	cout << "2.LOGIN AS TEACHER\n";
	cout << "3.LOGIN AS STUDENT\n";
	cout << "0.QUIT\n\n";
	cout << "Enter Your Choice : ";
	cin >> choice;
	switch (choice) {
	case 1:
		Admin(admin);
		break;
	case 2:
		Teacher(teach, registered_teachers);
		break;
	case 3:
		Student(student, registered_students);
		break;
	case 0:
		break;
	default:
		cout << "Invalid Option!\n";
		start();
		break;
	}
}
void Admin(myAdmin admin) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t-----------------------------\n";
	cout << "\t\t\t\t\t--- LOGIN TO ADMIN PORTAL ---\n";
	cout << "\t\t\t\t\t-----------------------------\n";
	string name;
	string pass;
	cout << "Username : ";
	cin >> name;
	cout << "Password : ";
	cin >> pass;

	// Checking credentials before logging in
	if (name == admin.id) {
		if (pass == admin.password) {
			admin_menu();
		}
		else
		{
			cout << "Wrong Password! Enter Again.\n";
			Admin(admin);
		}
	}
	else {
		cout << "Wrong Username! Enter Again.\n";
		Admin(admin);
	}
}
void admin_menu() {
	Sleep(700);
	system("cls");
	int choice;
	cout << "\t\t\t\t\t-------------------------------\n";
	cout << "\t\t\t\t\t--- WELCOME TO ADMIN PORTAL ---\n";
	cout << "\t\t\t\t\t-------------------------------\n";
	cout << "1. Update your information\n";
	cout << "2. Register a teacher\n";
	cout << "3. Register a student\n";
	cout << "4. Teachers credentials\n";
	cout << "5. Students credentials\n";
	cout << "6. Search a user\n";
	cout << "7. Remove a user\n";
	cout << "0. Logout\n\n";
	cout << "Enter Your Choice : ";
	cin >> choice;
	switch (choice) {
	case 1:
		update_admin_info(admin, "admin.txt");
		admin_menu();
		break;
	case 2:
		register_teacher("teacher_info.txt");
		break;
	case 3:
		register_student("student_info.txt");
		break;
	case 4:
		teacher_credentials(teach);
		break;
	case 5:
		student_credentials(student);
		break;
	case 6:
		search_user();
		break;
	case 7:
		remove_user();
		break;
	case 0:
		start();
		break;
	default:
		cout << "Invalid choice! Try again" << endl;
		admin_menu();
		break;
	}
}
void read_admin_data(myAdmin& admin, const string& filename) {

	// Read admin data from file to structure array
	ifstream fin;
	fin.open("admin.txt");

	if (fin.is_open()) {
		getline(fin, admin.name);
		fin >> admin.age;
		fin.ignore();
		fin >> admin.gender;
		fin.ignore();
		getline(fin, admin.mail);
		getline(fin, admin.skill);
		getline(fin, admin.id);
		getline(fin, admin.password);
	}
	else {
		cout << "Error : Unable to open file for reading." << endl;
	}
}
void update_admin_info(myAdmin& admin, const string& filename) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t-------------------------------\n";
	cout << "\t\t\t\t\t--- UPDATE YOUR INFORMATION ---\n";
	cout << "\t\t\t\t\t-------------------------------\n";
	int update;

	// Take new information from admin
	cin.ignore();
	cout << "Name : ";
	getline(cin, admin.name);
	cout << "Age : ";
	cin >> admin.age;
	cin.ignore();
	cout << "Gender(M/F) : ";
	cin >> admin.gender;
	cin.ignore();
	cout << "E-Mail : ";
	getline(cin, admin.mail);
	cout << "Qualification : ";
	getline(cin, admin.skill);
	cout << "Username : ";
	getline(cin, admin.id);
	cout << "Password : ";
	getline(cin, admin.password);
	cout << endl;

	cout << "Press '1' to save the information and '0' to cancel." << endl;
	cout << "Are you sure you want to update : " << endl;
	cin >> update;

	// Writing updated information to file and removing previous
	if (update == 1) {
		ofstream fout;
		fout.open("admin.txt", ios::trunc);
		if (fout.is_open()) {
			fout << admin.name << endl;
			fout << admin.age << endl;
			fout << admin.gender << endl;
			fout << admin.mail << endl;
			fout << admin.skill << endl;
			fout << admin.id << endl;
			fout << admin.password << endl;
			cout << endl;
			cout << "Information updated successfuly!" << endl;
		}
	}
	else {
		cout << "Information not updated!" << endl;
		admin_menu();
	}
}
void register_teacher(const string& filename) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t--------------------------\n";
	cout << "\t\t\t\t\t--- REGISTER A TEACHER ---\n";
	cout << "\t\t\t\t\t--------------------------\n\n";

	int sz;
	cout << "Dear Admin! How many teacher's you want to register : ";
	cin >> sz;

	// Create dynamic array to take input to register teachers
	myTeacher* rTeach = new myTeacher[sz];
	for (int i = 0; i < sz; i++) {
		cin.ignore();
		cout << "---------" << endl;
		cout << "TEACHER " << i + 1 << endl;
		cout << "---------" << endl;

		cout << "Name : ";
		getline(cin, rTeach[i].name);
		cout << "Age : ";
		cin >> rTeach[i].age;
		cin.ignore();
		cout << "Gender(M/F) : ";
		cin >> rTeach[i].gender;
		cin.ignore();
		cout << "Course : ";
		getline(cin, rTeach[i].course);
		cout << "E-Mail : ";
		getline(cin, rTeach[i].mail);
		cout << "Username : ";
		getline(cin, rTeach[i].id);
		cout << "Password : ";
		getline(cin, rTeach[i].password);
	}

	// Add new data to file
	ofstream fout;
	fout.open("teacher_info.txt", ios::app);

	if (fout.is_open()) {
		for (int i = 0; i < sz; i++) {
			fout << rTeach[i].name << endl;
			fout << rTeach[i].age << endl;
			fout << rTeach[i].gender << endl;
			fout << rTeach[i].course << endl;
			fout << rTeach[i].mail << endl;
			fout << rTeach[i].id << endl;
			fout << rTeach[i].password << endl;
		}
		cout << endl;
		cout << "Registered successfuly!" << endl;
		admin_menu();
	}
	else {
		cout << "Error : could not open file for writing!" << endl;
		admin_menu();
	}
	fout.close();
}
void register_student(const string& filename) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t--------------------------\n";
	cout << "\t\t\t\t\t--- REGISTER A STUDENT ---\n";
	cout << "\t\t\t\t\t--------------------------\n\n";

	int sz;
	cout << "Dear Admin! How many Students's you want to register : ";
	cin >> sz;

	// Create dynamic array to take input to register teachers
	myStudent* str = new myStudent[sz];
	for (int i = 0; i < sz; i++) {
		cin.ignore();
		cout << "---------" << endl;
		cout << "STUDENT " << i + 1 << endl;
		cout << "---------" << endl;

		cout << "Name : ";
		getline(cin, str[i].name);
		cout << "Age : ";
		cin >> str[i].age;
		cin.ignore();
		cout << "Gender(M/F) : ";
		cin >> str[i].gender;
		cin.ignore();
		cout << "Section : ";
		getline(cin, str[i].section);
		cout << "Grade : ";
		getline(cin, str[i].grade);
		cout << "Department : ";
		getline(cin, str[i].department);
		cout << "Username : ";
		getline(cin, str[i].id);
		cout << "Password : ";
		getline(cin, str[i].password);
	}

	// Add new data to file
	ofstream fout;
	fout.open("student_info.txt", ios::app);

	if (fout.is_open()) {
		for (int i = 0; i < sz; i++) {
			fout << str[i].name << endl;
			fout << str[i].age << endl;
			fout << str[i].gender << endl;
			fout << str[i].section << endl;
			fout << str[i].grade << endl;
			fout << str[i].department << endl;
			fout << str[i].id << endl;
			fout << str[i].password << endl;
		}
		cout << endl;
		cout << "Registered successfuly!" << endl;
		admin_menu();
	}
	else {
		cout << "Error : Unable to open file for writing!" << endl;
		admin_menu();
	}
}
int count_teachers(const string& filename) {

	// Count total registered teachers
	string line;
	int count = 0;
	ifstream fin;
	fin.open("teacher_info.txt");

	if (fin.is_open()) {
		while (!fin.eof()) {
			getline(fin, line);
			count++;
		}
	}
	else {
		cout << "Error : Unable to open file for reading!" << endl;
	}
	count /= 7;
	return count;
}
void read_teacher_data(myTeacher* teach, int sz, const string& filename) {

	// Read teacher data from file to structure array
	ifstream fin;
	fin.open("teacher_info.txt");

	if (fin.is_open()) {
		for (int i = 0; i < sz; i++) {
			getline(fin, teach[i].name);
			fin >> teach[i].age;
			fin.ignore();
			fin >> teach[i].gender;
			fin.ignore();
			getline(fin, teach[i].course);
			getline(fin, teach[i].mail);
			getline(fin, teach[i].id);
			getline(fin, teach[i].password);
		}
	}
	else {
		cout << "Error : Unable to open file for reading!" << endl;
	}
	fin.close();
}
int count_students(const string& filename) {

	// Count total registered teachers
	string line;
	int count = 0;
	ifstream fin;
	fin.open("student_info.txt");

	if (fin.is_open()) {
		while (!fin.eof()) {
			getline(fin, line);
			count++;
		}
	}
	else {
		cout << "Error : Unable to open file for reading!" << endl;
	}
	fin.close();
	count /= 8;
	return count;
}
void read_student_data(myStudent* student, int sz, const string& filename) {
	ifstream fin;
	fin.open("student_info.txt");

	if (fin.is_open()) {
		for (int i = 0; i < sz; i++) {
			getline(fin, student[i].name);
			fin >> student[i].age;
			fin.ignore();
			fin >> student[i].gender;
			fin.ignore();
			getline(fin, student[i].section);
			getline(fin, student[i].grade);
			getline(fin, student[i].department);
			getline(fin, student[i].id);
			getline(fin, student[i].password);
		}
	}
	else {
		cout << "Error : Unable to open file for reading!" << endl;
	}
	fin.close();
}
void teacher_credentials(myTeacher* teach) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t----------------------------\n";
	cout << "\t\t\t\t\t--- TEACHER CREDENTIAL'S ---\n";
	cout << "\t\t\t\t\t----------------------------\n\n";

	// Iterating loop through every index to show data of every teacher
	for (int i = 0; i < registered_teachers; i++) {
		cout << "----------" << endl;
		cout << "Teacher " << i + 1 << endl;
		cout << "----------" << endl;
		cout << "Name : " << teach[i].name << endl;
		cout << "Username : " << teach[i].id << endl;
		cout << "Password : " << teach[i].password << endl;
		cout << endl;
	}
	int choice;
	cout << "Press '1' to exit : ";
	cin >> choice;
	if (choice == 1) {
		admin_menu();
	}
	else {
		cout << "Invalid choice!" << endl;
	}
}
void student_credentials(myStudent* student) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t----------------------------\n";
	cout << "\t\t\t\t\t--- STUDENT CREDENTIAL'S ---\n";
	cout << "\t\t\t\t\t----------------------------\n\n";

	// Iterate loop through all indexes to show data of every student
	for (int i = 0; i < registered_students; i++) {
		cout << "-----------" << endl;
		cout << "Student " << i + 1 << endl;
		cout << "-----------" << endl;
		cout << "Name : " << student[i].name << endl;
		cout << "Username : " << student[i].id << endl;
		cout << "Password : " << student[i].password << endl;
		cout << endl;
	}
	int choice;
	cout << "Press '1' to exit : ";
	cin >> choice;
	if (choice == 1) {
		admin_menu();
	}
	else {
		cout << "Invalid choice!" << endl;
	}
}
void search_user() {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t---------------------\n";
	cout << "\t\t\t\t\t--- SEARCH A USER ---\n";
	cout << "\t\t\t\t\t---------------------\n\n";
	int choice;
	cout << "1. Teacher" << endl;
	cout << "2. Student" << endl;
	cout << "0. Go back" << endl;
	cout << endl;
	cout << "Enter your choice : ";
	cin >> choice;

	switch (choice) {
	case 1:
		search_teacher(teach, registered_teachers);
		break;
	case 2:
		search_student(student, registered_students);
		break;
	case 0:
		admin_menu();
		break;
	default:
		cout << "Invalid choice ! Try again" << endl;
		search_user();
		break;
	}
}
void search_teacher(myTeacher* teach, int registered_teachers) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t------------------------\n";
	cout << "\t\t\t\t\t--- SEARCH A TEACHER ---\n";
	cout << "\t\t\t\t\t------------------------\n\n";
	read_teacher_data(teach, registered_teachers, "teacher_info.txt");
	string username;
	int index;
	bool isPresent = 0;
	cout << "Username : ";
	cin >> username;

	// Searching for a teacher and storing index
	for (int i = 0; i < registered_teachers; i++) {
		if (username == teach[i].id) {
			index = i;
			isPresent = 1;
		}
	}

	// Show teacher data if found
	if (isPresent) {
		int goBack;
		cout << endl;
		cout << "---------------------" << endl;
		cout << "Data of searched user" << endl;
		cout << "---------------------" << endl << endl;
		cout << "Name : " << teach[index].name << endl;
		cout << "Age : " << teach[index].age << endl;
		cout << "Gender : " << teach[index].gender << endl;
		cout << "Course : " << teach[index].course << endl;
		cout << "E-Mail : " << teach[index].mail << endl;
		cout << "Username : " << teach[index].id << endl;
		cout << "Password : " << teach[index].password << endl;
		cout << endl;

		cout << "Press '1' to go back : ";
		cin >> goBack;
		if (goBack == 1) {
			search_user();
		}
	}
	else {
		cout << "No teacher found against this username!" << endl;
		search_user();
	}
}
void search_student(myStudent* student, int registered_students) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t------------------------\n";
	cout << "\t\t\t\t\t--- SEARCH A STUDENT ---\n";
	cout << "\t\t\t\t\t------------------------\n\n";
	string username;
	int index;
	bool isPresent = 0;
	cout << "Username : ";
	cin >> username;

	// Searching for user and storing index
	for (int i = 0; i < registered_students; i++) {
		if (username == student[i].id) {
			index = i;
			isPresent = 1;
		}
	}

	// Show data of student if found
	if (isPresent) {
		int goBack;
		cout << endl;
		cout << "---------------------" << endl;
		cout << "Data of searched user" << endl;
		cout << "---------------------" << endl << endl;
		cout << "Name : " << student[index].name << endl;
		cout << "Age : " << student[index].age << endl;
		cout << "Gender : " << student[index].gender << endl;
		cout << "Section : " << student[index].section << endl;
		cout << "Grade : " << student[index].grade << endl;
		cout << "Department : " << student[index].department << endl;
		cout << "Username : " << student[index].id << endl;
		cout << "Password : " << student[index].password << endl;
		cout << endl;

		cout << "Press '1' to go back : ";
		cin >> goBack;
		if (goBack == 1) {
			search_user();
		}
	}
	else {
		cout << "No student found against this username!" << endl;
		search_user();
	}
}
void remove_user() {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t---------------------\n";
	cout << "\t\t\t\t\t--- REMOVE A USER ---\n";
	cout << "\t\t\t\t\t---------------------\n\n";
	int choice;
	cout << "1. Teacher" << endl;
	cout << "2. Student" << endl;
	cout << "0. Go back" << endl;
	cout << endl;
	cout << "Enter your choice : ";
	cin >> choice;

	switch (choice) {
	case 1:
		remove_teacher(teach, registered_teachers, "teacher_infp.txt");
		break;
	case 2:
		remove_student(student, registered_students, "student_info.txt");
		break;
	case 0:
		admin_menu();
		break;
	default:
		cout << "Invalid choice ! Try again" << endl;
		remove_user();
		break;
	}
}
void remove_teacher(myTeacher* teach, int registered_teachers, const string& filename) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t------------------------\n";
	cout << "\t\t\t\t\t--- REMOVE A TEACHER ---\n";
	cout << "\t\t\t\t\t------------------------\n\n";
	read_teacher_data(teach, registered_teachers, "teacher_info.txt");
	string username;
	int index = -1;
	cout << "Enter teacher username to remove: ";
	cin >> username;

	// Search for teacher index
	for (int i = 0; i < registered_teachers; i++) {
		if (teach[i].id == username) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "Teacher not found!" << endl;
		admin_menu();
	}
	// Shifting remaining teachers to other index
	for (int i = index; i < registered_teachers - 1; i++) {
		teach[i] = teach[i + 1];
	}
	// Rewriting file without the removed teacher
	ofstream fout("teacher_info.txt", ios::trunc);
	if (fout.is_open()) {
		for (int i = 0; i < registered_teachers - 1; i++) {
			fout << teach[i].name << endl;
			fout << teach[i].age << endl;
			fout << teach[i].gender << endl;
			fout << teach[i].course << endl;
			fout << teach[i].mail << endl;
			fout << teach[i].id << endl;
			fout << teach[i].password << endl;
		}
		cout << "Teacher removed successfully!" << endl;
	}
	else {
		cout << "Error: Could not open file for writing!" << endl;
	}
	fout.close();
	admin_menu();
}
void remove_student(myStudent* student, int registered_students, const string& filename) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t------------------------\n";
	cout << "\t\t\t\t\t--- REMOVE A STUDENT ---\n";
	cout << "\t\t\t\t\t------------------------\n\n";
	string username;
	int index = -1;
	cout << "Enter student username to remove: ";
	cin >> username;
	// Search for student index
	for (int i = 0; i < registered_students; i++) {
		if (student[i].id == username) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "Student not found!" << endl;
		return;
	}
	// Shifting remaining students
	for (int i = index; i < registered_students - 1; i++) {
		student[i] = student[i + 1];
	}
	// Rewriting file without the removed student
	ofstream fout("student_info.txt", ios::trunc);
	if (fout.is_open()) {
		for (int i = 0; i < registered_students - 1; i++) {
			fout << student[i].name << endl;
			fout << student[i].age << endl;
			fout << student[i].gender << endl;
			fout << student[i].section << endl;
			fout << student[i].grade << endl;
			fout << student[i].department << endl;
			fout << student[i].id << endl;
			fout << student[i].password << endl;
		}
		cout << "Student removed successfully!" << endl;
	}
	else {
		cout << "Error: Could not open file for writing!" << endl;
	}
	fout.close();
	Sleep(200);
	admin_menu();
}
void Teacher(myTeacher* teach, int registered_teachers) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t-------------------------------\n";
	cout << "\t\t\t\t\t--- LOGIN TO TEACHER PORTAL ---\n";
	cout << "\t\t\t\t\t-------------------------------\n";
	string name;
	string pass;
	cout << "Username : ";
	cin >> name;
	cout << "Password : ";
	cin >> pass;

	// Checking credentials before logging in
	for (int i = 0; i < registered_teachers; i++) {

		if (name == teach[i].id) {
			if (pass == teach[i].password) {
				teach_index = i;
				teacher_menu();
				return;
			}
			else {
				cout << "Wrong Password! Enter Again.\n";
				Teacher(teach, registered_teachers);
			}
		}
	}
}
void teacher_menu() {
	Sleep(700);
	system("cls");
	int choice;
	cout << "\t\t\t\t\t---------------------------------\n";
	cout << "\t\t\t\t\t--- WELCOME TO TEACHER PORTAL ---\n";
	cout << "\t\t\t\t\t---------------------------------\n";
	cout << "1. Update your information\n";
	cout << "2. Create a quiz\n";
	cout << "3. View a quiz\n";
	cout << "4. Edit a quiz\n";
	cout << "5. Assign a Quiz\n";
	cout << "6. View Results\n";
	cout << "0. Logout\n\n";
	cout << "Enter Your Choice : ";
	cin >> choice;
	switch (choice) {
	case 1:
		update_teacher_info(teach, "teacher_info.txt");
		teacher_menu();
		break;
	case 2:
		create_quiz();
		break;
	case 3:
		view_quiz(Quiz, saved_quiz);
		break;
	case 4:
		edit_quiz(Quiz, saved_quiz);
		break;
	case 5:
		assign_quiz(Quiz, saved_quiz);
		break;
	case 6:
		view_result_student();
		break;
	case 0:
		start();
		break;
	default:
		cout << "Invalid choice! Try again" << endl;
		teacher_menu();
		break;
	}
}
void update_teacher_info(myTeacher* teach, const string& filename) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t-------------------------------\n";
	cout << "\t\t\t\t\t--- UPDATE YOUR INFORMATION ---\n";
	cout << "\t\t\t\t\t-------------------------------\n";
	int update;

	// Take new information from admin
	cin.ignore();
	cout << "Name : ";
	getline(cin, teach[teach_index].name);
	cout << "Age : ";
	cin >> teach[teach_index].age;
	cin.ignore();
	cout << "Gender(M/F) : ";
	cin >> teach[teach_index].gender;
	cin.ignore();
	cout << "Course : ";
	getline(cin, teach[teach_index].course);
	cout << "E-Mail : ";
	getline(cin, teach[teach_index].mail);
	cout << "Username : ";
	getline(cin, teach[teach_index].id);
	cout << "Password : ";
	getline(cin, teach[teach_index].password);
	cout << endl;

	cout << "Press '1' to save the information and '0' to cancel." << endl;
	cout << "Are you sure you want to update : " << endl;
	cin >> update;

	// Writing updated information to file and removing previous
	if (update == 1) {
		ofstream fout;
		fout.open("teacher_info.txt", ios::trunc);

		if (fout.is_open()) {
			for (int i = 0; i < registered_teachers; i++) {
				fout << teach[i].name << endl;
				fout << teach[i].age << endl;
				fout << teach[i].gender << endl;
				fout << teach[i].course << endl;
				fout << teach[i].mail << endl;
				fout << teach[i].id << endl;
				fout << teach[i].password << endl;
			}
			cout << endl;
			cout << "Information updated successfuly!" << endl;
		}
	}
	else {
		cout << "Information not updated!" << endl;
		teacher_menu();
	}
}
void Student(myStudent* student, int registered_students) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t-------------------------------\n";
	cout << "\t\t\t\t\t--- LOGIN TO STUDENT PORTAL ---\n";
	cout << "\t\t\t\t\t-------------------------------\n";
	string name;
	string pass;
	cout << "Username : ";
	cin >> name;
	cout << "Password : ";
	cin >> pass;

	// Checking credentials before logging in
	for (int i = 0; i < registered_students; i++) {

		// Ensuring that student exists
		if (name == student[i].id) {
			if (pass == student[i].password) {
				str_index = i;
				student_menu();
				return;
			}
			else {
				cout << "Wrong Password! Enter Again.\n";
				Student(student, registered_students);
			}
		}
	}
}
void student_menu() {
	Sleep(700);
	system("cls");
	int choice;
	cout << "\t\t\t\t\t---------------------------------\n";
	cout << "\t\t\t\t\t--- WELCOME TO STUDENT PORTAL ---\n";
	cout << "\t\t\t\t\t---------------------------------\n";
	cout << "1. Update your information\n";
	cout << "2. View Assigned Quiz\n";
	cout << "3. Take a Quiz\n";
	cout << "4. View Results\n";
	cout << "0. Logout\n\n";
	cout << "Enter Your Choice : ";
	cin >> choice;
	switch (choice) {
	case 1:
		update_student_info(student, "student_info.txt");
		student_menu();
		break;
	case 2:
		view_assigned_quiz(student, str_index);
		break;
	case 3:
		solve_assigned_quiz();
		break;
	case 4:
		view_result_student_one();
		break;
	case 0:
		start();
		break;
	default:
		break;
	}
}
void update_student_info(myStudent* student, const string& filename) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t-------------------------------\n";
	cout << "\t\t\t\t\t--- UPDATE YOUR INFORMATION ---\n";
	cout << "\t\t\t\t\t-------------------------------\n";
	int update;

	// Take new information from student
	cin.ignore();
	cout << "Name : ";
	getline(cin, student[str_index].name);
	cout << "Age : ";
	cin >> student[str_index].age;
	cin.ignore();
	cout << "Gender(M/F) : ";
	cin >> student[str_index].gender;
	cin.ignore();
	cout << "Password : ";
	getline(cin, student[str_index].password);
	cout << endl;

	cout << "Press '1' to save the information and '0' to cancel." << endl;
	cout << "Are you sure you want to update : ";
	cin >> update;

	// Writing updated information to file and removing previous
	if (update == 1) {
		ofstream fout;
		fout.open("student_info.txt", ios::trunc);

		if (fout.is_open()) {
			for (int i = 0; i < registered_students; i++) {
				fout << student[i].name << endl;
				fout << student[i].age << endl;
				fout << student[i].gender << endl;
				fout << student[i].section << endl;
				fout << student[i].grade << endl;
				fout << student[i].department << endl;
				fout << student[i].id << endl;
				fout << student[i].password << endl;
			}
			cout << endl;
			cout << "Information updated successfuly!" << endl;
		}
	}
	else {
		cout << "Information not updated!" << endl;
		student_menu();
	}
}
void create_quiz() {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t---------------------\n";
	cout << "\t\t\t\t\t--- CREATE A QUIZ ---\n";
	cout << "\t\t\t\t\t---------------------\n";
	myQuiz quiz;
	cin.ignore();
	cout << "Enter Quiz title : ";
	getline(cin, quiz.title);
	cout << "Enter quiz ID : ";
	cin >> quiz.id;
	cin.ignore();
	cout << "Enter Quiz Description: ";
	getline(cin, quiz.description);
	cout << "Enter Subject : ";
	getline(cin, quiz.subject);
	cout << "Enter section : ";
	getline(cin, quiz.section);

	cout << "Enter Timer (in minutes): ";
	cin >> quiz.timer;
	if (quiz.timer <= 0) {
		quiz.timer = 1;
	}
	

	// Ensure exactly 5 questions
	for (int i = 0; i < 5; ++i) {
		myQuestion& q = quiz.questions[i];
		q.num = i + 1;

		cout << "-------------" << endl;
		cout << "Question " << i + 1 << endl;
		cout << "-------------" << endl;
		cout << "Statement : ";
		cin.ignore();
		getline(cin, q.text);

		for (int j = 0; j < 4; ++j) {
			cout << (j + 1) << ". ";
			getline(cin, q.options[j]);
		}
		cout << "----------------" << endl;
		cout << "Correct option(1-4) : ";
		cin >> q.answer;
		q.answer -= 1;
		cout << endl;
	}
	cout << endl;
	int choice;
	cout << "Press '1' to save the quiz and '0' to cancel." << endl;
	cout << "Are you sure you want to save the quiz : ";
	cin >> choice;

	if (choice == 1) {
		ofstream fout;

		// Opening file in append mode 
		fout.open("quiz_info.txt", ios::app); 

		if (fout.is_open()) {
			fout << quiz.title << endl;
			fout << quiz.description << endl;
			fout << quiz.subject << endl;
			fout << quiz.section << endl;
			fout << quiz.id << endl;
			fout << quiz.timer << endl;

			for (int i = 0; i < 5; ++i) {
				myQuestion& q = quiz.questions[i];
				fout << q.num << endl;
				fout << q.text << endl;
				for (int j = 0; j < 4; ++j) {
					fout << q.options[j] << endl;
				}
				fout << q.answer << endl;
			}
			cout << "Quiz saved successfully!" << endl;
			teacher_menu();
		}
		else {
			cout << "Error: Unable to open file for writing!" << endl;
		}
		fout.close();
	}
	else if (choice == 0) {
		teacher_menu();
	}
	else {
		cout << "Invalid choice!" << endl;
		teacher_menu();
	}
}
int count_quiz(const string& filename) {
	string line;
	int count = 0;
	ifstream fin;
	fin.open("quiz_info.txt");

	if (fin.is_open()) {
		while (!fin.eof()) {
			getline(fin, line);
			count++;
		}
	}
	else {
		cout << "Error : Unable to open file for reading!" << endl;
	}
	count /= 41;
	return count;
}
void read_quiz_data(myQuiz* Quiz, int saved_quiz, const string& filename) {
	ifstream fin;
	fin.open("quiz_info.txt");

	if (fin.is_open()) {
		for (int i = 0; i < saved_quiz; i++) {
			getline(fin, Quiz[i].title);
			getline(fin, Quiz[i].description);
			getline(fin, Quiz[i].subject);
			getline(fin, Quiz[i].section);
			fin >> Quiz[i].id;
			fin >> Quiz[i].timer;
			fin.ignore();

			for (int j = 0; j < 5; j++) {
				fin >> Quiz[i].questions[j].num;
				fin.ignore();
				getline(fin, Quiz[i].questions[j].text);
				for (int k = 0; k < 4; k++) {
					fin >> Quiz[i].questions[j].options[k];
				}
				fin >> Quiz[i].questions[j].answer;
				fin.ignore();
			}
		}
	}
	else {
		cout << "Error : Unable to open file for reading!" << endl;
	}
	fin.close();
}
void assign_quiz(myQuiz* Quiz, int sz) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t\t---------------------\n";
	cout << "\t\t\t\t\t\t--- ASSIGN A QUIZ ---\n";
	cout << "\t\t\t\t\t\t---------------------\n";
	int id;
	int quiz_index;
	cout << "Saved Quiz Credentials" << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < sz; i++) {
		cout << "ID : " << Quiz[i].id << endl;
	}
	cout << endl;
	cout << "Enter Quiz ID to assign it : ";
	cin >> id;
	cin.ignore();

	// Searching for that index at which that quiz is stored
	for (int i = 0; i < sz; i++) {
		if (id == Quiz[i].id) {
			quiz_index = i;
			break;
		}
	}
	cout << endl;
	// Asking to which section quiz is to be assigned
	int assign;
	cout << "Press '1' to assign to 'Sapphire'" << endl;
	cout << "Press '2' to assign to 'Ruby'" << endl;
	cout << "Press '3' to assign to 'Emerald'" << endl;
	cout << endl;
	cout << "Your desire here : ";
	cin >> assign;

	for (int i = 0; i < assigned_quiz; i++) {
		if (Assign[i].id == id) {
			if ((assign == 1 && Assign[i].section == "Sapphire") ||
				(assign == 2 && Assign[i].section == "Ruby") ||
				(assign == 3 && Assign[i].section == "Emerald")) {
				cout << "Quiz ID: " << id << " has already been assigned to this section!" << endl;
				teacher_menu();
			}
		}
	}
	ofstream fout;
	fout.open("assign_info.txt", ios::app);

	switch (assign)
	{
	case 1:
		fout << "Sapphire" << endl;
		fout << Quiz[quiz_index].id << endl;
		cout << "ID : " << Quiz[quiz_index].id << " is assigned to Sapphire succesfuly!" << endl;
		teacher_menu();
		break;
	case 2:
		fout << "Ruby" << endl;
		fout << Quiz[quiz_index].id << endl;
		cout << "ID : " << Quiz[quiz_index].id << " is assigned to Ruby succesfuly!" << endl;
		teacher_menu();
		break;
	case 3:
		fout << "Emerald" << endl;
		fout << Quiz[quiz_index].id << endl;
		cout << "ID : " << Quiz[quiz_index].id << " is assigned to Emerald succesfuly!" << endl;
		teacher_menu();
		break;
	default:
		cout << "Invalid choice! Try again" << endl;
		teacher_menu();
		break;
	}
	int choice;
	cout << "Press '1' to exit : ";
	cin >> choice;
	if (choice == 1) {
		teacher_menu();
	}
	else {
		cout << "Invalid choice!" << endl;
	}
	teacher_menu();
}
void view_quiz(myQuiz* Quiz, int sz) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t-----------------------\n";
	cout << "\t\t\t\t\t--- SAVED QUIZ DATA ---\n";
	cout << "\t\t\t\t\t-----------------------\n";
	int id;
	cout << "Saved Quiz Credentials" << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < sz; i++) {
		cout << "ID : " << Quiz[i].id << " - " << Quiz[i].title << endl;
	}
	cout << endl;
	cout << "Enter Quiz ID to view it : ";
	cin >> id;
	cin.ignore();

	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t--------------------------\n";
	cout << "\t\t\t\t\t--- REQUIRED QUIZ DATA ---\n";
	cout << "\t\t\t\t\t--------------------------\n";
	for (int i = 0; i < sz; i++) {
		if (id == Quiz[i].id) {
			cout << "Title: " << Quiz[i].title << endl;
			cout << "Description: " << Quiz[i].description << endl;
			cout << "Subject: " << Quiz[i].subject << endl;
			cout << "Section: " << Quiz[i].section << endl;
			cout << "Quiz ID: " << Quiz[i].id << endl;
			cout << "Timer: " << Quiz[i].timer << " minutes" << endl;

			// Exactly 5 questions per quiz
			for (int j = 0; j < 5; ++j) { 
				cout << "----------" << endl;
				cout << "Question " << Quiz[i].questions[j].num << endl;
				cout << "----------" << endl;
				cout << "Statement : " << Quiz[i].questions[j].text << endl;

				for (int k = 0; k < 4; ++k) {
					cout << (k + 1) << ". " << Quiz[i].questions[j].options[k] << endl;
				}
				cout << "------------------" << endl;
				cout << "Correct option : " << (Quiz[i].questions[j].answer + 1) << endl;
				cout << "------------------" << endl;
			}
		}
	}
	int choice;
	cout << "Press '1' to exit : ";
	cin >> choice;
	if (choice == 1) {
		teacher_menu();
	}
	else {
		cout << "Invalid choice!" << endl;
		view_quiz(Quiz,sz);
	}
}
void edit_quiz(myQuiz* Quiz, int sz) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t\t-------------------\n";
	cout << "\t\t\t\t\t\t--- EDIT A QUIZ ---\n";
	cout << "\t\t\t\t\t\t-------------------\n";
	int id;
	int quiz_index;
	cout << "Saved Quiz Credentials" << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < sz; i++) {
		cout << "ID : " << Quiz[i].id << endl;
	}
	cout << endl;
	cout << "Enter Quiz ID to update it : ";
	cin >> id;
	cin.ignore();

	// Searching for that index at which that quiz is stored
	for (int i = 0; i < sz; i++) {
		if (id == Quiz[i].id) {
			quiz_index = i;
			break;
		}
		else {
			cout << "Please choose a valid Quiz ID!" << endl;
		}
	}
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t\t-----------------------\n";
	cout << "\t\t\t\t\t\t--- QUIZ TO BE EDIT ---\n";
	cout << "\t\t\t\t\t\t-----------------------\n";

	// Show information of that quiz
	cout << "Title: " << Quiz[quiz_index].title << endl;
	cout << "Description: " << Quiz[quiz_index].description << endl;
	cout << "Subject: " << Quiz[quiz_index].subject << endl;
	cout << "Section: " << Quiz[quiz_index].section << endl;
	cout << "Quiz ID: " << Quiz[quiz_index].id << endl;
	cout << "Timer: " << Quiz[quiz_index].timer << " minutes" << endl;

	for (int j = 0; j < 5; j++) {
		cout << "-------------" << endl;
		cout << "Question " << Quiz[quiz_index].questions[j].num << endl;
		cout << "-------------" << endl;
		cout << "Statement : " << Quiz[quiz_index].questions[j].text << endl;

		for (int k = 0; k < 4; k++) {
			cout << (k + 1) << ". " << Quiz[quiz_index].questions[j].options[k] << endl;
		}
	}
	// Ask which question number is to be edited
	int qNo;
	int q_index;
	cout << endl;
	cout << "Which Question do you want to update : ";
	cin >> qNo;
	cin.ignore();
	for (int i = 0; i < 5; i++) {

		if (qNo == Quiz[quiz_index].questions[i].num) {
			q_index = i;
			break;
		}
	}
	// Updating that particular quiz only
	cout << endl;
	cout << "Update Question : ";
	getline(cin, Quiz[quiz_index].questions[q_index].text);

	for (int k = 0; k < 4; k++) {
		cout << "Option " << k + 1 << ": ";
		getline(cin, Quiz[quiz_index].questions[q_index].options[k]);
	}
	cout << "Correct option : ";
	cin >> Quiz[quiz_index].questions[q_index].answer;

	// Now write the updated data to file
	ofstream fout;
	fout.open("quiz_info.txt");
	for (int i = 0; i < sz; i++) {

		// Writing quiz description
		fout << Quiz[i].title << endl;
		fout << Quiz[i].description << endl;
		fout << Quiz[i].subject << endl;
		fout << Quiz[i].section << endl;
		fout << Quiz[i].id << endl;
		fout << Quiz[i].timer << endl;

		// Writing questions description
		for (int j = 0; j < 5; j++) {
			fout << Quiz[i].questions[j].num << endl;
			fout << Quiz[i].questions[j].text << endl;

			for (int k = 0; k < 4; k++) {
				fout << Quiz[i].questions[j].options[k] << endl;
			}
			fout << Quiz[i].questions[j].answer << endl;
		}
	}
	cout << endl;
	cout << "Question updated successfuly!" << endl;
	teacher_menu();
}
void view_assigned_quiz(myStudent* str, int index) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t--------------------------\n";
	cout << "\t\t\t\t\t--- VIEW ASSIGNED QUIZ ---\n";
	cout << "\t\t\t\t\t--------------------------\n";
	string userSection, assignedQuizId;
	ifstream assignView("assign_info.txt");
	bool isAnyFound = false;

	cout << "Dear " << str[index].name << ", " << endl << endl;
	while (getline(assignView, userSection) && getline(assignView, assignedQuizId)) {
		if (userSection == str[index].section) {
			cout << "ID : " << assignedQuizId << endl;
			isAnyFound = true;
		}
	}
	if (!isAnyFound)
		cout << "No Quiz assigned to Section : " << str[index].section << endl;
	cout << endl;
	int choice;
	cout << "Press '1' to exit : ";
	cin >> choice;
	if (choice == 1) {
		student_menu();
	}
	else {
		cout << "Invalid choice!" << endl;
	}
}
void solve_assigned_quiz() {
	Sleep(300);
	system("cls");
	cout << "\t\t\t\t\t--------------------------\n";
	cout << "\t\t\t\t\t--- SOLVE ASSIGNED QUIZ ---\n";
	cout << "\t\t\t\t\t--------------------------\n";
	int score = 0;
	int index, newIndex;
	bool isIndex = 0;
	for (int i = 0; i < assigned_quiz; i++) {
		if (student[str_index].section == Assign[i].section) {
			newIndex = i;
			break;
		}
	}
	for (int i = 0; i < saved_quiz; i++) {
		if (Assign[newIndex].id == Quiz[i].id) {
			index = i;
			isIndex = 1;
			break;
		}
	}
	if (isIndex == 0) {
		cout << "Dear " << student[str_index].name << " no quiz is pending!" << endl;
	}
	// Display Quiz details
	cout << "\nStarting Quiz: " << Quiz[index].title << endl;
	cout << "Description: " << Quiz[index].description << endl;
	cout << "Subject : " << Quiz[index].subject << endl;
	cout << "Quiz ID : " << Quiz[index].id << endl;
	cout << "You have " << Quiz[index].timer << " minute to complete this quiz." << endl;

	srand(time(0));

	// Shuffle the questions
	myQuestion shuffledQuestions[5];
	for (int i = 0; i < 5; i++) {
		shuffledQuestions[i] = Quiz[index].questions[i];
	}

	for (int i = 4; i > 0; i--) {
		int j = rand() % (i + 1);
		myQuestion temp = shuffledQuestions[i];
		shuffledQuestions[i] = shuffledQuestions[j];
		shuffledQuestions[j] = temp;
	}

	// Adding time to quiz
	auto start_time = chrono::steady_clock::now();
	auto end_time = start_time + chrono::minutes(Quiz[index].timer);

	// Ensuring time validity
	for (int i = 0; i < 5; i++) {
		auto current_time = chrono::steady_clock::now();
		if (current_time >= end_time) {
			cout << "\nTime's up! The quiz has ended." << endl;
			break;
		}

		// Showing shuffeled questions
		myQuestion q = shuffledQuestions[i];
		cout << "\nQuestion : " << q.text << endl;
		for (int j = 0; j < 4; ++j) {
			cout << j + 1 << ". " << q.options[j] << endl;
		}

		int answer;
		cout << "Enter your answer (1-4): ";
		while (!(cin >> answer) || answer < 1 || answer > 4) {
			cin.clear();
			cin.ignore();
			cout << "Invalid input. Please enter a number between 1 and 4: ";
		}
		if (answer - 1 == q.answer) {
			++score;
		}
	}
	cout << "\nQuiz Completed!" << endl;

	ofstream fout;
	fout.open("student_results.txt", ios::app);
	if (fout.is_open()) {
		fout << student[str_index].name << endl;
		fout << Quiz[index].id << endl;
		fout << score << endl;
	}
	else {
		cout << "Error : Unable to open file for writing!" << endl;
	}
	fout.close();
	// Delete that assigned quiz from file

	// Shift remaining students
	for (int i = newIndex; i < assigned_quiz - 1; i++) {
		Assign[i] = Assign[i + 1];
	}

	// Rewrite file without the removed solved assigned quiz
	fout.open("assign_info.txt", ios::trunc);
	if (fout.is_open()) {
		for (int i = 0; i < assigned_quiz - 1; i++) {
			fout << Assign[i].section << endl;
			fout << Assign[i].id << endl;
		}
	}
	else {
		cout << "Error: Could not open file for writing!" << endl;
	}
	fout.close();
	cout << endl;
	int choice;
	cout << "Press '1' to exit : ";
	cin >> choice;
	if (choice == 1) {
		student_menu();
	}
	else {
		cout << "Invalid choice!" << endl;
	}
}
void view_result_student() {
	Sleep(300);
	system("cls");
	cout << "\t\t\t\t\t\t----------------------\n";
	cout << "\t\t\t\t\t\t--- VIEW MY RESULT ---\n";
	cout << "\t\t\t\t\t\t----------------------\n";
	string username;
	int quizIdFromFile, score;
	bool foundResults = false;
	for (int k = 0; k < saved_quiz; k++) {
		ifstream fin;
		fin.open("student_results.txt");
		if (fin.is_open()) {

			// Show result of student
			cout << "\nQuiz ID: " << Quiz[k].id << endl;
			while (getline(fin, username)) {
				fin >> quizIdFromFile;
				fin >> score;
				fin.ignore();

				if (quizIdFromFile == Quiz[k].id) {
					char grade = calculateGrade(score, 5);
					cout << "Student: " << username << ", Score: " << score
						<< " / 5, Grade: " << grade << endl;
					foundResults = true;
				}
			}

			if (!foundResults) {
				cout << "No students have taken this quiz yet." << endl;
			}

			fin.close();
		}
		else {
			cout << "Error opening student results file!" << endl;
		}
	}
}
char calculateGrade(int score, int total) {
	double percentage = (double)score / total * 100;

	if (percentage >= 90.0) return 'A';
	if (percentage >= 80.0) return 'B';
	if (percentage >= 70.0) return 'C';
	if (percentage >= 60.0) return 'D';
	return 'F';
}
int count_assigned_quiz(const string& filename) {
	string line;
	int count = 0;
	ifstream fin;
	fin.open("assign_info.txt");

	if (fin.is_open()) {
		while (!fin.eof()) {
			getline(fin, line);
			count++;
		}
	}
	else {
		cout << "Error : Unable to open file for reading!" << endl;
	}
	count /= 2;
	return count;
}
void read_assign_quiz_data(myAssign* Assign, int sz, const string& filename) {
	ifstream fin;
	fin.open("assign_info.txt");

	if (fin.is_open()) {
		for (int i = 0; i < sz; i++) {
			fin >> Assign[i].section;
			fin >> Assign[i].id;
			fin.ignore();
		}
	}
	else {
		cout << "Error : Unable to open file for reading!" << endl;
	}
	fin.close();
}
void view_result_student_one() {
	Sleep(300);
	system("cls");
	cout << "\t\t\t\t\t\t----------------------\n";
	cout << "\t\t\t\t\t\t--- VIEW MY RESULT ---\n";
	cout << "\t\t\t\t\t\t----------------------\n";
	string username;
	int quizIdFromFile, score;
	bool foundResults = false;
	for (int k = 0; k < saved_quiz; k++) {
		ifstream fin;
		fin.open("student_results.txt");
		if (fin.is_open()) {

			cout << "\nQuiz ID: " << Quiz[k].id << endl;
			while (getline(fin, username)) {
				fin >> quizIdFromFile;
				fin >> score;
				fin.ignore();

				if (quizIdFromFile == Quiz[k].id && student[str_index].name == username) {
					char grade = calculateGrade(score, 5);
					cout << "Student: " << username << ", Score: " << score
						<< " / 5, Grade: " << grade << endl;
					foundResults = true;
				}
			}
			fin.close();

			if (!foundResults) {
				cout << "Nothing to show here!" << endl;
			}


		}
		else {
			cout << "Error opening student results file!" << endl;
		}
	}
	cout << endl;
	int choice;
	cout << "Press '1' to exit : ";
	cin >> choice;
	if (choice == 1) {
		student_menu();
	}
	else {
		cout << "Invalid choice!" << endl;
	}
}