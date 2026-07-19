#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>

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
myAdmin admin;

// Functions prototypes
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
void update_student_info(myStudent*, const string& filename);
int str_index;

//---------------------------FUNCTION MAIN----------------------------
int main() {

	// Initialize global varibales
	teach_index = 0;
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

	// Start execution
	start();
}

// Functions definitions

//----------------------LOGIN INFO--------------------------------
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

//------------------------------ ADMIN ----------------------------------

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

//-----------------ADMIN FEATURES----------------

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
		break;
	}
}

//------------STORED ADMIN DATA ON TEXT FILE----------

void read_admin_data(myAdmin& admin, const string& filename) {
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

//------------------UPDATE ADMIN INFO--------------

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

//-----------------REGISTER TEACHER------------------

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

	
	// Add registered teachers data to Text file
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

//---------------REGISTER STUDENT---------------

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

	// Add registered students new data to Text file
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

//--------------TEACHER CREDENTIALS-----------

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

//---------------SEARCH USER-----------------

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

//------------------REMOVE A USER------------------------

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
		remove_teacher(teach, registered_teachers, "teacher_info.txt");
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

	// Shift remaining teachers
	for (int i = index; i < registered_teachers - 1; i++) {
		teach[i] = teach[i + 1];
	}

	// Rewrite file without the removed teacher
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
	Sleep(200);
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

	// Shift remaining students
	for (int i = index; i < registered_students - 1; i++) {
		student[i] = student[i + 1];
	}

	// Rewrite file without the removed student
	ofstream fout("student_info.txt", ios::trunc);
	if (fout.is_open()) {
		for (int i = 0; i < registered_students - 1; i++) {
			fout << student[i].name << endl;
			fout << student[i].age << endl;
			fout << student[i].id << endl;
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

//------------------------------- TEACHER ------------------------------- 

//-----------TEACHER LOGIN------------
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

//--------------TEACHER FEATURES-----------------

void teacher_menu() {
	Sleep(700);
	system("cls");
	int choice;
	cout << "\t\t\t\t\t---------------------------------\n";
	cout << "\t\t\t\t\t--- WELCOME TO TEACHER PORTAL ---\n";
	cout << "\t\t\t\t\t---------------------------------\n";
	cout << "1. Update your information\n";
	cout << "2. Create a quiz\n";
	cout << "3. Edit a quiz\n";
	cout << "4. Assign a quiz\n";
	cout << "5. View results\n";
	cout << "0. Logout\n\n";
	cout << "Enter Your Choice : ";
	cin >> choice;
	switch (choice) {
	case 1:
		update_teacher_info(teach, "teacher_info.txt");
		teacher_menu();
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
	case 0:
		start();
		break;
	default:
		break;
	}
}

//----------UPDATE TEACHERS INFO-----------

void update_teacher_info(myTeacher * teach, const string & filename) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t-------------------------------\n";
	cout << "\t\t\t\t\t--- UPDATE YOUR INFORMATION ---\n";
	cout << "\t\t\t\t\t-------------------------------\n";
	int update;
	read_teacher_data(teach, registered_teachers, "teacher_info.txt");

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

//----------------------------- STUDENT -------------------------------------

void Student(myStudent* student, int registered_students) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t-------------------------------\n";
	cout << "\t\t\t\t\t--- LOGIN TO STUDENT PORTAL ---\n";
	cout << "\t\t\t\t\t-------------------------------\n";
	string username;
	string pass;
	cout << "Username : ";
	cin >> username;
	cout << "Password : ";
	cin >> pass;
	read_student_data(student, registered_students, "student_info.txt");
	// Checking credentials before logging in
	for (int i = 0; i < registered_students; i++) {

		// Ensuring that student exists
		if (username == student[i].id) {
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
		else {
			cout << "Wrong Username! Enter Again.\n";
			Student(student, registered_students);
		}
	}
}

//---------------STUDENT FEATURES---------------

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
		register_teacher("teacher_info.txt");
		break;
	case 3:
		register_student("student_info.txt");
		break;
	case 4:
		teacher_credentials(teach);
		break;
	case 0:
		start();
		break;
	default:
		break;
	}
}

//---------------UPDATE STUDENTS INFO---------------

void update_student_info(myStudent * student, const string& filename) {
	Sleep(700);
	system("cls");
	cout << "\t\t\t\t\t-------------------------------\n";
	cout << "\t\t\t\t\t--- UPDATE YOUR INFORMATION ---\n";
	cout << "\t\t\t\t\t-------------------------------\n";
	int update;
	read_student_data(student, registered_students, "student_info.txt");

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
	cout << "Section : ";
	getline(cin, student[str_index].section);
	cout << "Grade : ";
	getline(cin, student[str_index].grade);
	cout << "Department : ";
	getline(cin, student[str_index].department);
	cout << "Username : ";
	getline(cin, student[str_index].id);
	cout << "Password : ";
	getline(cin, student[str_index].password);
	cout << endl;

	cout << "Press '1' to save the information and '0' to cancel." << endl;
	cout << "Are you sure you want to update : " << endl;
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