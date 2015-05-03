// ppp.cpp : Defines the entry point for the console application.
//

// comp3311-project.cpp : Defines entry point for the console application.
// No marks will be given if we can't compile your file
// No marks will be given if the SQL statement is fundementally incorrect and no partial credits will be given
// No marks will be given for a TODO task if it fails to get the same result from the check case in the assignment description
// If you want to appeal the score,  please run the suggested solution and compare the result
// you can print the retrieved results using printRecordIntoCol(HSTMT stmt) and printIntoRow(HSTMT stmt, int maxColumnWidth);
#include "stdafx.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
using namespace std;


HENV   henv;
HDBC   hdbc;
HSTMT  hstmt;
RETCODE	ret;

SQLINTEGER staff_id,cbStaffId; // global variables




boolean ConnectDB();
void DisconnectDB();
boolean userLogin();


void prof_menu(); // the menu for prof.
void teachInfo(); // show teaching information
void superInfo(); // show supervision information
void adminInfo(); // show administrative information
void showTeach(); // show offerings being taught by the prof in the current semester 'Spring2014'
void showLead();  // show offerings being led by the prof in the current semester 'Spring2014'
void showPre();   // show prerequisites of all the courses
void showSuper(); // show students being supervised by the prof
void showSuperGroup(); // show supervision information of the school
void changePassword(); // change password for the prof
void addPhone();       // add a new phone for the prof
void showCourseTA();   // show all the TAs working with the prof in the current semester
void showTAPref();     // show the offering preference of all the TAs

void printRecordIntoCol(HSTMT stmt);
SQLCHAR*** printIntoRow(HSTMT stmt, int maxColumnWidth);


int main(){
	int command = 0;
	// set the width and line displayed in the command prompt
	system("mode con cols=80 lines=50");

	if (ConnectDB()) {
		while(userLogin()){
			do {
				system ("CLS"); // clear the screen
				prof_menu(); //menu for the prof
			
			} while ( command != 0);
		}
	}else {
		cout << "Oracle Connection unsuccessful.\n";
		system("pause");
	}
	DisconnectDB();
}


void prof_menu(){

	int command = 0;
	int ISdone=0;

	while (!ISdone){
		system ("CLS"); // Clear the screen
		cout << "============ Information System for Professors ===============\n\n";
		cout << "0. Return to the previous menu                     (input '0').\n";
		cout << "1. Show Teaching related information               (input '1').\n";
		cout << "2. Show Supervision information                    (input '2').\n";
		cout << "3. Show Administrative information                 (input '3').\n";
		cout << "Please enter your choice: ";

		cin >> command ;

		char buf[2];
		cin.getline(buf, 2); // grab the endline character when the user press "Enter"

		cout<<endl;

		switch (command){
			case 1:
				teachInfo();
				ISdone=0;
				break;
				
			case 2:
				superInfo();
				ISdone=0;
				break;
			case 3:
				adminInfo();
				ISdone=0;
				break;
			case 0:
				ISdone=1;
				break;
			default: 
				break;
		}
	}
}


void teachInfo(){

	int command = 0;
	int ISdone=0;

	while (!ISdone){
		system("CLS");
		cout << "=================== Teaching Information ======================\n\n";
		cout << "0. Return to the previous menu                        (input '0').\n";
		cout << "1. Display course(s) teaching in the current semester (input '1').\n";
		cout << "2. Display the course being led                       (input '2').\n";
		cout << "3. See prerequisites of the courses                   (input '3').\n";
		cout << "Please enter your choice: ";

		cin >> command ;

		char buf[2];
		cin.getline(buf, 2); // grab the endline character when the user press "Enter"

		cout<<endl;

		switch (command){
			case 1:
				showTeach();
				ISdone=0;
				break;
				
			case 2:
				showLead();
				ISdone=0;
				break;
			case 3:
				showPre();
				ISdone=0;
				break;
			case 0:
				ISdone=1;
				break;
			default: 
				break;
		}
	}

}

void showTeach(){
	SQLAllocStmt(hdbc, &hstmt);
	char query[1000];
	char currentSem[100]="Spring2014";

	system("CLS");

	cout<<"Here are the courses you are teaching in the current semester:\n";
	
	// TODO 1: display the course_ID, course_name, offering_no, classroom, no_of_stds, and credits of all the courses he/she is teaching in the current semester (assume the current semester is Spring2014).
	// for the expect behaviour of this part please refer to the executable program
	// Add your code here
	//char C_staffid = staff_id + '0';
	// The sql statement should be "select from course C, offering O, "
	//string SQL_statement = "select C.course_ID, C.course_name, O.offering_no, O.classroom, O.no_of_stds "
	//						+ "from course C, offering O "
	//						+ "where C.course_ID = O.course_ID and O.YearSemester = " + "Spring2014" + "and O.staff_id = " + C_staffid + ";";

	sprintf_s(query, "Select C.course_ID as \"Course ID\", C.course_name as \"Course name\", O.offering_no as \"Offering number\", O.classroom as \"Classroom\", O.no_of_stds as \"Number of students\" from prof_teach pt, course C, offering O where C.course_ID = pt.course_ID and O.offering_no = pt.offering_no and O.course_id = C.course_id and O.YearSemester = \'%s\' and pt.staff_id = %d", currentSem, staff_id);
	ret = SQLExecDirectA(hstmt, (SQLCHAR *)query, SQL_NTS);
	printIntoRow(hstmt, 15);
	SQLFreeStmt(hstmt, SQL_CLOSE);
	system("pause");
}

void showLead(){
	SQLAllocStmt(hdbc, &hstmt);
	char query[1000];
	char currentSem[100]="Spring2014";
	
	system("CLS");
	cout<<"Here are the courses you are leading in the current semester:\n";
	cout<<"-------------------------------------------------------------\n";

	// TODO 2: display the course_ID, course_name, offering_no, classroom, no_of_stds, and credits of the course he/she is leading in the current semester (assume the current semester is Spring2014)
	// Add your code here
	// The sql statement should be "select C.course_name, O.course_ID, O.offering_no, O.classroom, O.no_of_stds from offering O, course C where O.course_ID = C.course_ID and O.YearSemester = Spring2014 and O.staff_id = <staff_id>"
	//char C_staffid = staff_id + '0';
	//string SQL_statement = "select C.course_ID, C.course_name, O.offering_no, O.classroom, O.no_of_stds "
	//	+ "from course C, offering O "
	//	+ "where C.course_ID = O.course_ID and O.YearSemester = " + "Spring2014" + "and O.staff_id = " + C_staffid + ";";
	sprintf_s(query, "select C.course_id as \"Course ID\", C.course_name as \"Course Name\", O.offering_no as \"Offering Number\", O.classroom as \"Classroom\", O.no_of_stds as \"Number of Students\" from course C, offering O where C.course_ID = O.course_ID and O.YearSemester = \'%s\' and O.staff_id = %d", currentSem, staff_id);
	ret = SQLExecDirectA(hstmt, (SQLCHAR *)query, SQL_NTS);
	printRecordIntoCol(hstmt);
	SQLFreeStmt(hstmt, SQL_CLOSE);
 	system("pause");
}

void showPre(){
	SQLAllocStmt(hdbc, &hstmt);
	char query[1000];
	
	system("CLS");
	cout<<"Here are the prerequisites of the courses:\n";

	// TODO 3: group the prerequisites (course_IDs) by the course_IDs of the main courses and display the prerequisites (course_ID) in a list. See the screen shot in the assignment output section for the expected output. 
    // Hint: you will find the aggregate function LISTAGG() function useful. You can refer to http://www.oracle-developer.net/display.php?id=515 for the exact syntax of LISTAGG().
	// Add your code here
	// sql code "select main_course_ID as main_course, listagg(prereq_course_ID, ', ') within group (order by prereq_course_ID) as prerequisite_list
	//			 from prerequisite group by main_course_ID;"
	//string SQL_statement = "select main_course_ID, listagg(prereq_course_ID, ', ') within group (order by prereq_course_ID) as prerequisite_list "
	//						+ "from prerequisite group by main_course_ID;";
	sprintf_s(query, "select main_course_ID as \"Main Course\", listagg(prereq_course_ID, ', ') within group (order by prereq_course_ID) as \"Prerequisite list\" from prerequisite group by main_course_ID");	
	ret = SQLExecDirectA(hstmt, (SQLCHAR *)query, SQL_NTS);
	printIntoRow(hstmt, 15);
	SQLFreeStmt(hstmt, SQL_CLOSE);
	system("pause");
}


void superInfo(){

	int command = 0;
	int ISdone=0;

	while (!ISdone){
		system("CLS");
		cout << "=================== Supervision Information ======================\n\n";
		cout << "0. Return to the previous menu                        (input '0').\n";
		cout << "1. Display students being supervised                  (input '1').\n";
		cout << "2. Display students by their supervisor staff_ID      (input '2').\n";
		cout << "Please enter your choice: ";

		cin >> command ;

		char buf[2];
		cin.getline(buf, 2); // grab the endline character when the user press "Enter"

		cout<<endl;

		switch (command){
			case 1:
				showSuper();
				ISdone=0;
				break;
				
			case 2:
				system("mode con cols=160 lines=50"); //make the screen larger
				showSuperGroup();
				system("mode con cols=80 lines=50"); //restore the screen size
				ISdone=0;
				break;
			case 0:
				ISdone=1;
				break;
			default: 
				break;
		}
	}
}

void showSuper(){

	SQLAllocStmt(hdbc, &hstmt);
	char query[1000];
	
	system("CLS");
	cout<<"Here are the students you are supervising:\n";

	// TODO 4: display all the student_ID, last_name, first_name, phone of all the students the professor supervises.
	// Add your code here
	// SQL code: select TA.student_ID, TA.last_name, TA.first_name, TA.phone
	//			 from TA, supervise
	//			 where supervise.student_ID = TA.student_ID
	//			 and supervise.staff_ID = <staff_ID>
	//char C_staffid = staff_id + '0';
	//string SQL_statement = "select TA.student_ID, TA.last_name, TA.first_name, TA.phone "
	//	+ "from TA, supervise "
	//	+ "where supervise.student_ID = TA.student_ID "
	//	+ "and supervise.staff_ID = " + C_staffid + ";";
	sprintf_s(query, "select TA.student_ID as \"Student ID\", TA.last_name as \"Last Name\", TA.first_name as \"First Name\", TA.phone as \"Phone number\" from TA, supervise where supervise.student_ID = TA.student_ID and supervise.staff_ID = %d", staff_id);
	ret = SQLExecDirectA(hstmt, (SQLCHAR *)query, SQL_NTS);
	printIntoRow(hstmt,15);
	SQLFreeStmt(hstmt, SQL_CLOSE);
	system("pause");
}

void showSuperGroup(){


	SQLAllocStmt(hdbc, &hstmt);
	char query[1000];

	system("CLS");
	cout<<"Here are the student supervision information of the school:\n";

	// TODO 5: group the students (student_ID, last_name, first_name) according to the supervisors' staff_IDs, and display the student information in a list in ascending order of the student_IDs, 
	// see the screen shot for the exact output. Hint: you may find the LISTAGG() function and the concatenation operator are useful. 
	// Add your code here
	//string SQL_statement = "select s.staff_ID, p.last_name, p.first_name, "
	//	+ "listagg(t.student_ID || ' ' || t.last_name || ' ' || t.first_name, ',') "
	//	+ "within group (order by t.student_ID) as students "
	//	+ "from supervise s, prof p, TA t "
	//	+ "where s.staff_ID = p.staff_ID and s.student_ID = t.student_ID "
	//	+ "group by s.staff_ID, p.last_name, p.first_name;";
	sprintf_s(query, "select s.staff_ID as \"Professor staff ID\", p.last_name as \"Last Name\", p.first_name as \"First Name\", listagg(t.student_ID || ' ' || t.last_name || ' ' || t.first_name, ', ') within group (order by t.student_ID) as \"Supervising students\" from supervise s, prof p, TA t where s.staff_ID = p.staff_ID and s.student_ID = t.student_ID group by s.staff_ID, p.last_name, p.first_name");
	ret = SQLExecDirectA(hstmt, (SQLCHAR *)query, SQL_NTS);
	printIntoRow(hstmt,30);
	SQLFreeStmt(hstmt, SQL_CLOSE);
	system("pause");

}

void adminInfo(){
	
	int command = 0;
	int ISdone=0;

	while (!ISdone){
		system("CLS");
		cout << "=================== Administrative Information ======================\n\n";
		cout << "0. Return to the previous menu                          (input '0').\n";
		cout << "1. Change your password                                 (input '1').\n";
		cout << "2. Add a new phone                                      (input '2').\n";
		cout << "3. Show the TAs of your courses in the current semester (input '3').\n";
		cout << "4. Show preferred offerings for the TAs                 (input '4').\n";
		cout << "Please enter your choice: ";

		cin >> command ;

		char buf[2];
		cin.getline(buf, 2); // grab the endline character when the user press "Enter"

		cout<<endl;

		switch (command){
			case 1:
				changePassword();
				ISdone=0;
				break;
				
			case 2:
				addPhone();
				ISdone=0;
				break;

			case 3:
				system("mode con cols=160 lines=50"); //make the screen larger
				showCourseTA();
				system("mode con cols=80 lines=50"); //restore the screen
				ISdone=0;
				break;

			case 4:
				system("mode con cols=160 lines=50"); //make the screen larger
				showTAPref();
				system("mode con cols=80 lines=50"); //restore the screen
				ISdone=0;
				break;
			case 0:
				ISdone=1;
				break;
			default: 
				break;
		}
	}
}

void changePassword(){
	char newPassword[11];
	char query[1000];

	cout<< "\nPlease input your new password: (at most 10 characters):";
	cin >> newPassword;
	// TODO 6: Update the database for prof. password.
	// for the expect behaviour of this part please refer to the executable program
	// Add your code here
	//char C_staffid = staff_id + '0';
	//string C_pwd(newPassword);
	// SQL statment should be  update prof set password = <newPassword> where staff_id = <staff_id>
	//string SQL_statement = "update prof "
	//	+ "set password = " + C_pwd
	//	+ " where staff_id = " + C_staff_id + ";";
	if (strlen(newPassword) <= 10) {
		sprintf_s(query, "update prof set password = \'%s\' where staff_id = %d", newPassword, staff_id);	
		ret = SQLExecDirectA(hstmt, (SQLCHAR *)query, SQL_NTS);
		SQLFreeStmt(hstmt, SQL_CLOSE);
	} else {
		cout << "Password update unsuccessful." << endl;
	}
	system("pause");
}

void addPhone(){
	int newPhone;
	char query[1000];

	cout<< "\nPlease input the new phone number you want to add:";
	cin >> newPhone;
	// TODO 7:  add a new phone number for the prof. assume user always enter a new phone number so you do not need to check
	// for the expect behaviour of this part please refer to the executable program
	// Add your code here
	// SQL statement should be  insert into prof_phone values (a,b);
	//reverse(C_np.begin(), C_np.end());
	if (newPhone >= 100000000) {
		cout << "Unable to add a new phone number" << endl;
	} else {
		sprintf_s(query, "insert into prof_phone values (%d, %d)", staff_id, newPhone);
		ret = SQLExecDirectA(hstmt, (SQLCHAR *)query, SQL_NTS);
		SQLFreeStmt(hstmt, SQL_CLOSE);
	}
	system("pause");
}

void showCourseTA(){
	SQLAllocStmt(hdbc, &hstmt);
	char query[1000];
	char currentSem[100]="Spring2014";

	system("CLS");

	cout<<"Here are TA information of all the courses you are teaching in the current semester:\n";
	
	// TODO 8: displays the student_ID, last_name, first_name, and phone number for each TA of the course offerings he/she teaches in the current semester (assume the current semester is Spring2014).
	// Add your code here
	// sql statement: select ta.course_ID, c.course_name, ta.offering_no, ta.last_name, ta.first_name, ta.phone 
	//				  from prof_teach pt, TA ta, course c, offering o 
	//					where c.course_ID = pt.course_ID and pt.offering_no = ta.offering_no and pt.course_ID = ta.course_ID and o.offering_no = ta.offering_no and o.YearSemester = 'Spring2014' and pt.staff_ID = 2;
	//char C_staffid = staff_id + '0';
	//string sem(currentSem);
	//string SQL_statement = "select ta.course_ID, c.course_name, ta.offering_no, ta.last_name, ta.first_name, ta.phone "
	//	+ "from prof_teach pt, TA ta, course c, offering o "
	//	+ "where c.course_ID = pt.course_ID and pt.offering_no = ta.offering_no and pt.course_ID = ta.course_ID and o.offering_no = ta.offering_no and o.YearSemester = '"
	//	+ sem + "' adn pt.staff_ID = " + C_staffid + ";";
	
	sprintf_s(query, "select ta.course_ID as \"Course ID\", c.course_name as \"Course name\", ta.offering_no as \"Offering number\", ta.student_ID as \"TA student ID\", ta.last_name as \"TA Last Name\", ta.first_name as \"TA First Name\", ta.phone as \"TA phone\"from prof_teach pt, TA ta, course c, offering o where c.course_ID = pt.course_ID and pt.offering_no = ta.offering_no and pt.course_ID = ta.course_ID and o.offering_no = ta.offering_no and o.YearSemester = \'%s\' and pt.staff_id = %d", currentSem, staff_id);
	ret = SQLExecDirectA(hstmt, (SQLCHAR *)query, SQL_NTS);
	printIntoRow(hstmt,15);
	SQLFreeStmt(hstmt, SQL_CLOSE);
	system("pause");

}

void showTAPref(){
	SQLAllocStmt(hdbc, &hstmt);
	char query[1000];
	char currentSem[100]="Spring2014";

	system("CLS");

	cout<<"Here are course preference information of the TAs:\n";
	
	// TODO 9: display the lists of all the preferred offerings (course_ID, offering_no) for all the TAs, group the result by the TAs?student_IDs. 
    // Hint: you will find the aggregate function LISTAGG() function useful.
	// Add your code here
	//string sem(currentSem);
	//string SQL_statement = "select ta.student_id, ta.last_name, ta.first_name, listagg (po.course_id|| ' ' ||po.offering_no) "
	//	+ "within group (order by po.course_id) as pref_list "
	//	+ "from TA ta, pref_offering po, offering o "
	//	+ "where ta.student_ID = po.student_ID and ta.offering_no = o.offering_no and o.YearSemester = '" + sem + "' "
	//	+ "group by ta.student_id, ta.last_name, ta.first_name;";
	sprintf_s(query, "select ta.student_id as \"TA student ID\", ta.last_name as \"Last Name\", ta.first_name as \"First Name\", listagg(po.course_id || ' ' || po.offering_no, ', ') within group (order by po.course_id) as \"Preference list\" from TA ta, pref_offering po, offering o where ta.student_ID = po.student_ID and ta.offering_no = o.offering_no group by ta.student_id, ta.last_name, ta.first_name");
	ret = SQLExecDirectA(hstmt, (SQLCHAR *)query, SQL_NTS);
	printIntoRow(hstmt,15);
	SQLFreeStmt(hstmt, SQL_CLOSE);
	system("pause");
}


boolean userLogin(){

	int loginOption;
	char username[20], password[11];
	char query[1000];
	char inputUsername[20];	
	string inputPassword;
	SQLINTEGER cbUsername, cbPassword;


	boolean success= false;

	while (!success){
		system ("CLS"); // Clear the screen
		cout << "===Welcome to Information System of the University of ST===\n\n";
		cout << "Please choose one of the follow options:\n";
		cout << "0. to terminate the program                      (input '0').\n";
		cout << "1. Log in as a professor                         (input '1').\n";
		cout << "Please enter your choice: ";
		cin >> loginOption;
		
		char buf[2];
		cin.getline(buf, 2); // grab the endline character when the user press "Enter"

		// Exit if the user keys in "0"
		if (loginOption == 0) 
			break;

		if (loginOption==1){

			cout << "Please enter your username: ";
			cin >> inputUsername;

			// Exit if the user keys in "0"
			//if (strcmp(inputUsername,"0") == 0) 
			//	break;

			cout << "Please enter your Password: ";		
			inputPassword="";

			// Get the input character by character and mask the password
			boolean flag=true;
			while(flag)
			{
			char chr=getch(); 
			if (chr=='\r') flag=false;
	
				else{putch('*'); inputPassword += chr;}
			}		
		
			cin.clear();
            cin.ignore(256, '\n');
			cout << endl;

			// This part has been Done for you. 
			// Check whether the user is a valid user. This is done through checking inputUsername and password and see whether 
			// they match with prof.user_name and prof.password. The user_name and password are new added attributes, please 
			// refer to the 'insert_record.sql' for the exact values. Note that we are using SQLExecDirectA(), and we copy the 
			// returned values from the Oracle server using the SQLBindCol() function. We then SQLFetch() to retrieve the results 
			//(the columns: user_name,password,staff_id) from Oralce and copy them to the local variables username,password, 
			//staff_id.
		
			SQLAllocStmt(hdbc, &hstmt);
			sprintf_s(query,"select user_name, password, staff_id from prof where user_name=\'%s\'",inputUsername);
			SQLExecDirectA(hstmt, (SQLCHAR *)query, SQL_NTS);
			SQLBindCol(hstmt,1,SQL_C_CHAR,username,20,&cbUsername);
			SQLBindCol(hstmt,2,SQL_C_CHAR,password,11,&cbPassword);
			SQLBindCol(hstmt,3,SQL_INTEGER,&staff_id,1,&cbStaffId);
			ret = SQLFetch(hstmt);

			if (ret==SQL_SUCCESS || ret ==SQL_SUCCESS_WITH_INFO) {
				if (strcmp(inputPassword.c_str(),password) != 0) {
					cout << "Password Incorrect, please try again.\n";
					success = false;
					system("pause");
					system("CLS");
					
				} else{				
					success = true;
				}
			} else {
				cout << "User does not exist, please try again.\n";
				success = false;
				system("pause");
				system("CLS");
			
			}
			SQLFreeStmt(hstmt,SQL_CLOSE);
			cout<<endl;	
		}
	}

	return success;
}












boolean ConnectDB() {
	RETCODE        ret;	
	/* Allocate environment handle */
	ret = SQLAllocEnv( &henv);
	/* Allocate connection handle */
	ret = SQLAllocConnect(henv, &hdbc);
	/* Connect to the service */

	char oracleAccountName[20];
	string inputPassword;

	cout << "========Information System DB manager logon page=========\n\n";
		
	cout << "Please enter your Oracle account username: ";
	cin >> oracleAccountName;
	cout << "Please enter your Oracle account Password: ";		
	inputPassword="";

	// Mask the password
	boolean flag=true;
	while(flag){
          char chr=getch(); 
          if (chr=='\r') flag=false;

               else{putch('*'); inputPassword += chr;}
	}		
	cout << endl;


	ret = SQLConnectA(hdbc, (SQLCHAR*) "comp3311.cse.ust.hk", SQL_NTS, (SQLCHAR*) oracleAccountName, SQL_NTS, (SQLCHAR*) inputPassword.c_str(), SQL_NTS);
	system ("CLS"); // clear the screen
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		return TRUE;
	return FALSE;
}

void DisconnectDB() {
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);
}

// A generic function prints each row of return value into a column of information
void printRecordIntoCol(HSTMT stmt){
   SQLCHAR columnName[10][64];
   SQLSMALLINT  noOfcolumns, columNameLength[10], dataType[10], decimalDigits[10], nullable[10];
   SQLULEN columnSize[10];
   SQLCHAR buf[10][64];
   SQLINTEGER indicator[10];

   // Find the total number of columns
   SQLNumResultCols(stmt, &noOfcolumns);
   
   for (int i = 0; i < noOfcolumns; i++) {
	  // Retrieve the column metadata
	  ret = SQLDescribeColA(hstmt,i+1,columnName[i], sizeof(columnName[i]), &columNameLength[i], &dataType[i],&columnSize[i],&decimalDigits[i],&nullable[i]);
	  // Bind the column result
	  SQLBindCol( stmt, i + 1, SQL_C_CHAR, buf[ i ], sizeof(buf[i]), &indicator[ i ]);
   }

   // Print out the query result
   while (SQL_SUCCEEDED(SQLFetch(stmt))) {
	   for ( int i = 0; i < noOfcolumns; i ++ ) {
		   cout <<setw(15)<<left<< columnName[i]<<": "<< buf[i] <<endl;		   
	   }
	   //cout<<endl;
   }
}

// A generic function prints out the query result by column with a maximum column width
SQLCHAR*** printIntoRow(HSTMT stmt, int maxColumnWidth){
   SQLCHAR columnName[10][64];
   SQLSMALLINT  noOfcolumns, columNameLength[10], dataType[10], decimalDigits[10], nullable[10];
   SQLULEN columnSize[10];
   SQLCHAR buf[10][64];
   SQLCHAR*** result;
   SQLINTEGER indicator[10];

   // Find the total number of columns
   SQLNumResultCols(stmt, &noOfcolumns);
   

   for(int i=0;i<maxColumnWidth*noOfcolumns;i++)
	   cout <<"-";
   cout<<endl;

   // Initialize the result pointer
   result = new SQLCHAR**[200];
   for(int i=0;i<100;i++){
	   result[i] = new SQLCHAR*[10];
      for(int j=0;j<noOfcolumns;j++){
		 result[i][j] = new SQLCHAR[64];
	  }
   }

   for (int i = 0; i < noOfcolumns; i++) {
	  // Retreive the column metadata
	  ret = SQLDescribeColA(hstmt,i+1,columnName[i], sizeof(columnName[i]), &columNameLength[i], &dataType[i],&columnSize[i],&decimalDigits[i],&nullable[i]);

	  // Bind the column result
	  SQLBindCol( stmt, i + 1, SQL_C_CHAR, buf[ i ], sizeof(buf[i]), &indicator[ i ]);
   }

   int totalLength=0;
   // Print out the column name
   for ( int i = 0; i < noOfcolumns; i ++ ) {
		if(columnSize[i]<columNameLength[i]){
			cout <<setw(columNameLength[i]+2)<<left<< columnName[i];		
			totalLength+=columNameLength[i]+2;
		}
	    else if(columnSize[i]<maxColumnWidth){
			cout <<setw(columnSize[i]+2)<<left<< columnName[i];		
			totalLength+=columnSize[i]+2;
		}else{
			cout <<setw(maxColumnWidth)<<left<< columnName[i];		
			totalLength+=maxColumnWidth;
		}
    }
   cout<<endl;

   // Print out separate line
   for(int i=0;i<maxColumnWidth*noOfcolumns;i++)
	   cout <<"-";
   cout<<endl;

   // Print out the query result row by row
   int j=0;
   while (SQL_SUCCEEDED(SQLFetch(stmt))) {
	   for ( int i = 0; i < noOfcolumns; i ++ ) {
		    // deep copy
			for(int k=0; k<sizeof(buf[i]);k++){
				result[j][i][k] = buf[i][k];
			}
			if(columnSize[i]<columNameLength[i]){
				cout <<setw(columNameLength[i]+2)<<left<< buf[i];		
			}
			else if(columnSize[i]<maxColumnWidth){
				cout <<setw(columnSize[i]+2)<<left<< buf[i];		
			}
			else{
				cout <<setw(maxColumnWidth)<<left<< buf[i];		
			}
	   }
	   j++;
	   cout<<endl;
   }
   
   return result;
}

