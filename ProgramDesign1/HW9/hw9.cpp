#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <string>
using namespace::std;

struct MemberRecord
{
   char IDNumber[ 12 ];   // account number
   char password[ 24 ];   // password
   char name[ 8 ];        // name
};

// input memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// login
void login( const vector< MemberRecord > &memberDetails );

// there exists a member with specified IDNumber and password
bool valid( char IDNumber[], char password[],
            const vector< MemberRecord > &memberDetails );

// add a new member
void registration( vector< MemberRecord > &memberDetails );

// return true if IDNumber is a legal ID number
bool legalID( char IDNumber[] );

// return true if IDNumber belongs to memberDetails
bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails );

// output all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails );

int main()
{
   vector< MemberRecord > memberDetails; // member details for all members // 可能要清空={} 
   int numMembers = 0;                     // number of members

   loadMemberDetails( memberDetails );

   cout << "Welcome to the Cashbox Party World!\n\n";

   int choice;

   while( true )
   {
      cout << "1 - Login\n";
      cout << "2 - Registration\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );

      cout << endl;

      switch ( choice )
      {
      case 1:
         login( memberDetails );
         break;

      case 2:
         registration( memberDetails );
         break;

      case 3:
         saveMemberDetails( memberDetails );
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }

   system( "pause" );
}

/*bool legalID( char IDNumber[] ){
	
	int firstNumber, lastnumber;
	
	
}*/

void loadMemberDetails( vector< MemberRecord > &memberDetails ){
	MemberRecord in;
	fstream member1( "Members.dat", ios::in | ios::out | ios::binary ); //讀檔 
	if(!member1){
		ofstream member2( "Members.dat", ios::binary);
		if(!member2){
			cerr << "File could not be opened" << endl;
			system("pause");
			exit(1);
		}
	}else{
		while(member1.read((char *)( &in), sizeof(MemberRecord))){
			memberDetails.push_back(in);
		}		
	}	
}

int inputAnInteger( int begin, int end ){
	
	char num[50];
	
	cin.getline(num, 50);
	if(!strlen(num)){
		cin.getline(num,50); //如果為0輸入第二次,不加會錯 
	}
	for(int i=0; i<strlen(num); i++){
		if(num[i]<'0'||num[i]>'9'){ //判斷是否都是數字 
			return -1;
		}
	}
	int n = atoi(num); //把字串轉為整數 
	if(n>=begin&&n<=end){
		return n;
	}else{
		return -1;
	}
}

void login( const vector< MemberRecord > &memberDetails ){
	char idnum[12];
	char nm[8];
	while(1){
		cout << "Please enter your ID number: ";
		cin >> idnum;
		cout << endl;
		cout << "Enter your password: ";
		cin >> nm;
		cout << endl;
		if(!valid( idnum, nm, memberDetails)){ //判斷 
			cout << "Invalid account number or password. Please try again." << endl << endl;
		}else{
			cout << "Welcome!!" << endl << endl;
			break;
		}
	}
}

bool valid( char IDNumber[], char password[], const vector< MemberRecord > &memberDetails ){
	//vector< MemberRecord >::const_iterator p=memberDetails.begin();
	if(memberDetails.size()==0){
		return false;
	}
	/*for(p; p!=memberDetails.end(); ++p){
		if(strcmp(IDNumber,p->IDNumber)==0 && strcmp(password,p->password)==0){
			return true;
		}
	}*/
	for(int i=0; i<memberDetails.size(); i++){
		if(strcmp(IDNumber, memberDetails[i].IDNumber)==0 && strcmp(password, memberDetails[i].password)==0){ //比對帳號密碼是否相同 
			return true;
		}
	}
	return false;    	
}

void registration( vector< MemberRecord > &memberDetails ){
	char idnum[12];
	char pass[24];
	char nm[8];
	cout << "Input Your ID Number: "; //輸入帳號 
	cin >> idnum;
	cout << endl;
	if(!legalID( idnum)){ //檢查身分證是否符合 
		cout << "The ID Number " << idnum << " is illegal." << endl << endl;
		return;
	}
	if( !existingID( idnum, memberDetails) ){ //檢查這個帳號是否註冊過 
		cout << "You are already a member!" << endl << endl;
		return;
	}
	cout << "Input Your Name: "; //輸入帳號資訊 
	cin >> nm;
	cout << endl;
	cout << "Choose a Password: ";
	cin >> pass;
	cout << endl;
	MemberRecord cpy; //宣告一個新的structure變數  
	strcpy( cpy.IDNumber, idnum); //複製過去 
	strcpy( cpy.password, pass);
	strcpy( cpy.name, nm);
	//cout << cpy.IDNumber << cpy.name << cpy.password << endl;
	memberDetails.push_back(cpy); //放到陣列 
	cout << "Registration Completed" << endl << endl;
	//vector< MemberRecord >::iterator p=memberDetails.begin(); 
	/*vector< MemberRecord >::iterator p = memberDetails.begin();
	for(p; p != memberDetails.end(); ++p)
		cout << p->IDNumber << "   " << p->password << "   " << p->name << endl;*/
	/*
	pass.copy( cpy.password, pass.size());
	cout << cpy.password << endl;*/
	//nm.copy( cpy.name, pass, nm.size());
	
}

bool legalID( char IDNumber[] ){
	int first, last, sum, a, b; //計算是否符合身分證格式 
	int size=strlen(IDNumber);
	if(size!=10){
		return false;
	}else if(IDNumber[0]>='A' && IDNumber[0]<='H'){ //各縣市不同 
		first = IDNumber[0]-'7';
	}else if(IDNumber[0]-'I'==0){
		first = 34;
	}else if(IDNumber[0]>='J' && IDNumber[0]<='N'){
		first = IDNumber[0]-'8';
	}else if(IDNumber[0]-'O'==0){
		first = 35;
	}else if(IDNumber[0]>='P' && IDNumber[0]<='V'){
		first = IDNumber[0]-'9';
	}else if(IDNumber[0]-'W'==0){
		first = 32;
	}else if(IDNumber[0]-'X'==0){
		first = 30;
	}else if(IDNumber[0]-'Y'==0){
		first = 31;
	}else if(IDNumber[0]-'Z'==0){
		first = 33;
	}
	a = first%10;
	b = first/10;
	int c, n;
	sum+=a*9 + b;
	
	for(int i=1; i<9; i++){
		c = IDNumber[i]-'0';
		n = 9-i;
		sum += c*n;
	}
	if(sum%10==0){
		last = 0;
	}else{
		last = 10 - (sum%10);
	}
	if(last==(IDNumber[9]-'0')){
		return true;
	}else{
		return false;
	}
}

bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails ){
	//vector< MemberRecord >::const_iterator p=memberDetails.begin();
	if(memberDetails.size()==0){
		return true;
	}
	/*for(p; p!=memberDetails.end(); ++p){
		if(strcmp(IDNumber,p->IDNumber)==0){
			return false;
		}
	}*/
	for(int i=0; i<memberDetails.size(); i++){ //判斷是否存在 
		if(strcmp(IDNumber,memberDetails[i].IDNumber)==0){
			return false;
		}
	}
	return true;
}

void saveMemberDetails( const vector< MemberRecord > &memberDetails ){
	vector< MemberRecord >::const_iterator p=memberDetails.begin(); //存檔 
	ofstream member2("Members.dat", ios::out | ios::binary);
	
    if (!member2){
        cout << "File could not be open!\n";
        exit(1);
    }
	
	for(int i=0; i<memberDetails.size(); i++){
		member2.write(reinterpret_cast<const char *>( &memberDetails[i]), sizeof(MemberRecord));
	}
}
