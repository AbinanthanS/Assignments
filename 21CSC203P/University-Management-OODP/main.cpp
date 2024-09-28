#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "mohan12345";
const char* DB = "university";

class University{
	
	private:
		
		int Id,Age;
		string Name, Subject;
		float CGPA;
		
	public:
		
	University():Id(0),Age(0),Name(""),Subject(""),CGPA(0.0) {}
	
//SETTER FUNCTIONS
	
	void setId(int id){
		Id = id;
	}
	
	void setAge(int age){
		Age = age;
	}
	
    void setName(string name){
	    Name=name;
	}	
	
    void setSubject(string subject){
	    Subject=subject;
	}
	
    void setGrade(float cgpa){
	    CGPA= cgpa;
	}	
 
//GETTER FUNCTIONS
 
 int getId(){
 	return Id;
 }
 
 int getAge(){
		return Age;
	}
	
 string getName(){
    return Name;
 }
	
 string getSubject(){
     return Subject;
 }
	
 float getGrade(){
  return CGPA;
 }
 
};




//INSERT FUNCTIONS

void insertS(MYSQL* conn, University u){
	 int id,age;
 string name,subject;
 float cgpa;
 
 cout<<"Enter Id: ";
 cin>>id;
 u.setId(id);
 

  cout<<"Enter Name: ";
  cin.ignore();
  getline(cin,name);
 u.setName(name);
 
  cout<<"Enter Age: ";
 cin>>age;
 u.setAge(age);
 

 cout<<"Enter Subject: ";
 cin.ignore();
 getline(cin,subject);
 u.setSubject(subject);

 cout<<"Enter CGPA: ";
 cin>>cgpa;
 u.setGrade(cgpa);
 
 int iId= u.getId();
 int iAge= u.getAge();
 float fGrade = u.getGrade();
 
 stringstream ss;
 ss<<iId;
 string sId = ss.str();
 
 stringstream sss;
 sss<<iAge;
 string sAge = sss.str();
 
  stringstream as;
 as<<fGrade;
 string sGrade= as.str();
 
 string ins= "INSERT INTO student (Id, Age, Name, Subject, CGPA) VALUES ('"+sId+"','"+sAge+"','"+u.getName()+"', '"+u.getSubject()+"', '"+sGrade+"')";
 if(mysql_query(conn,ins.c_str())){
 	cout<<"Error: "<<mysql_error(conn)<<endl;
 }
 else{
 	cout<<"Data Inserted Successfuly."<<endl;
 }
 Sleep(3000);
}

//DISPLAY FUNCTION

showRecord(MYSQL* conn){
string show= "SELECT * FROM student";
 if(mysql_query(conn,show.c_str())){
 	cout<<"Error: "<<mysql_error(conn)<<endl;
 }
 else{
 	MYSQL_RES* res ;
 	res = mysql_store_result(conn);
 	if(res){
 	int num = mysql_num_fields(res);
 	MYSQL_ROW row;
 	while(row=mysql_fetch_row(res)){
 		for(int i=0; i< num; i++){
 		cout<<" "<<row[i];
		 }
		 cout<<endl;
	 }
	 }
 }
 Sleep(5000);
}

//FUNCTION TO SEARCH


searchS(MYSQL* conn){
	 int id;
 cout<<"Enter Student ID: ";
 cin>>id;
 	
 stringstream ss;
 ss<<id;
 string sId= ss.str();
 
 string show = "SELECT * FROM student WHERE Id ='"+sId+"' ";
 
 if(mysql_query(conn,show.c_str())){
cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
MYSQL_RES* res;
res = mysql_store_result(conn);
if(res){
	MYSQL_ROW row = mysql_fetch_row(res);
if(row){
	int num = mysql_num_fields(res);
	for(int i=0; i<num; i++){
		cout<<" "<<row[i];
	}
}
mysql_free_result(res);
}
}
Sleep(5000);
}

// FUNCTION TO UPDATE

updateS(MYSQL* conn, University u){
	int id;
	cout<<"Enter Id: ";
	cin>>id;
	
	int iId = u.getId();
	 stringstream ss;
 ss<<id;
 string sId= ss.str();
 
  string subject;
 cout<<"Enter New Subject: ";
 cin>>subject;
 u.setSubject(subject);
 
 string upd = "UPDATE student SET Subject = '"+u.getSubject()+"' WHERE Id = '"+sId+"'";
 if(mysql_query(conn,upd.c_str())){
cout<<"Error: "<<mysql_error(conn)<<endl;
}

else{
 cout<<"Data Updated Successfuly"<<endl;
}
Sleep(3000);
}

//FUNCTION TO DELETE

deleteS(MYSQL* conn){
 int id;
 cout<<"Enter Student ID: ";
 cin>>id;
 	

 stringstream ss;
 ss<<id;
 string sId= ss.str();	
 
 string del = "DELETE FROM student WHERE Id ='"+sId+"' ";
 if(mysql_query(conn,del.c_str())){
 cout<<"Error: "<<mysql_error(conn)<<endl;
}

else{
 cout<<"Data Deleted"<<endl;
}
Sleep(3000);
}

int main() {
	
	University u;
	
MYSQL* conn;
conn = mysql_init(NULL);

if(!mysql_real_connect(conn,HOST,USER,PW,DB,3306,NULL,0)){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Logged in!"<<endl;
}
Sleep(3000);

bool exit = false;

while(!exit){
	system("cls");
	int val;
	cout<<"Welcome to University Management System"<<endl;
	cout<<"------------------------------------------"<<endl;
	cout<<"[1] Insert Student Data"<<endl;
	cout<<"[2] Show Student Data"<<endl;
	cout<<"[3] Search Student Data"<<endl;
 	cout<<"[4] Update Student Data"<<endl;
 	cout<<"[5] Delete Student Data"<<endl;
 	cout<<"[0] Exit"<<endl;
 	cout<<"Enter choice: ";
 	cin>>val;
 	
 	cout<<endl;
 	
 	if(val==1){
 	insertS(conn,u);	
	 }
	 
	else if(val==2){
	showRecord(conn);	
	}
	
	else if(val==3){
	searchS(conn);	
	}
	
	else if(val==4){
	updateS(conn,u);	
	}
	
	else if(val==5){
	deleteS(conn);	
	}
	
	else if(val==0){
		exit = true;
		cout<<"Good Luck!"<<endl;
		Sleep(3000);
	}
	else{
		cout<<"Invalid Input"<<endl;
		Sleep(300);
	}
}

    return 0;
}
