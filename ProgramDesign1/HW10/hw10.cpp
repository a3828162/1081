#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace::std;

struct Date
{
   int year;
   int month;
   int day;
   int hour;
};

struct MemberRecord
{
   char IDNumber[ 12 ];   // account number
   char password[ 24 ];   // password
   char name[ 8 ];        // name
};

struct ReservationRecord
{
   char IDNumber[ 12 ]; // account number
   int branchCode;      // branch code
   Date date;           // reservation date
   int numCustomers;    // number of customers
};

char branchNames[ 17 ][ 24 ] = { "", "Taipei Dunhua South", "Taipei SOGO",
                                     "Taipei Songjiang",    "Taipei Nanjing",
                                     "Taipei Linsen",       "Taipei Zhonghua New",
                                     "Banqiao Guanqian",    "Yonghe Lehua",
                                     "Taoyuan Zhonghua",    "Taoyuan Nankan",
                                     "Zhongli Zhongyang",   "Hsinchu Beida",
                                     "Taichung Ziyou",      "Chiayi Ren'ai",
                                     "Tainan Ximen",        "Kaohsiung Zhonghua New" };

// input memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails );

// input reservations from the file Reservations.dat
void loadReservations( vector< ReservationRecord > &reservations );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// login and display the submenu
void login( const vector< MemberRecord > &memberDetails,
            vector< ReservationRecord > &reservations );

// there exists a member with specified IDNumber and password
bool valid( char IDNumber[], char password[],
            const vector< MemberRecord > &memberDetails );

// add a new reservation for the member with specified IDnumber
void reservation( char IDNumber[], vector< ReservationRecord > &reservations );

// compute the current date
void compCurrentDate( Date &currentDate );

// compute 7 dates which is starting from the current date
void compAvailableDates( Date currentDate, Date availableDates[] );

// display all fields of reservation
void output( ReservationRecord reservation );

// display all reservations for the member with specified IDnumber,
// then let the member to choose one of them to delete
void queryDelete( char IDNumber[], vector< ReservationRecord > &reservations );

// add a new member
void registration( vector< MemberRecord > &memberDetails );

// return true if IDNumber is a legal ID number
bool legalID( char IDNumber[] );

// return true if IDNumber belongs to memberDetails
bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails );

// output all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails );

// output all reservations into the file Reservations.dat
void saveReservations( const vector< ReservationRecord > &reservations );

int main()
{
   vector< MemberRecord > memberDetails; // member details for all members
   vector< ReservationRecord > reservations; // all reservations

   loadMemberDetails( memberDetails );
   loadReservations( reservations );

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
         login( memberDetails, reservations );
         break;

      case 2:
         registration( memberDetails );
         break;

      case 3:
         saveMemberDetails( memberDetails );
         saveReservations( reservations );
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

void loadMemberDetails( vector< MemberRecord > &memberDetails ){
	MemberRecord in;
	fstream member1( "Members.dat", ios::in | ios::out | ios::binary ); //讀檔 
	if(!member1){
		ofstream member2( "Members.dat", ios::binary); //如果原先沒有檔案先創檔 
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

void loadReservations( vector< ReservationRecord > &reservations ){
	ReservationRecord in;
	fstream re1( "Reservations.dat", ios::in | ios::out | ios::binary );//讀另一個檔 
	if(!re1){
		ofstream re2( "Reservations.dat", ios::binary);
		if(!re2){
			cerr << "File could not be opened" << endl;
			system("pause");
			exit(1);
		}
	}else{
		while(re1.read((char *)( &in), sizeof(ReservationRecord))){
			reservations.push_back(in);
		}		
	}	
}

int inputAnInteger( int begin, int end ){
	
	char num[50];
	
	cin.getline(num, 50); // 
	if(!strlen(num)){ //如果為零輸入第二次,不用會錯 
		cin.getline(num,50);  
	}
	for(int i=0; i<strlen(num); i++){ //判斷輸入是否為數字 
		if(num[i]<'0'||num[i]>'9'){
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

void login( const vector< MemberRecord > &memberDetails, vector< ReservationRecord > &reservations ){
	char idnum[12];
	char nm[8];
	while(1){
		cout << "Please enter your ID number: ";
		cin >> idnum;
		cout << endl;
		cout << "Enter your password: ";
		cin >> nm;
		cout << endl;
		if(!valid( idnum, nm, memberDetails)){ //判斷帳號密碼是否正確 
			cout << "Invalid account number or password. Please try again." << endl << endl;
		}else{
			break;
		}
	}

	int choice;
	while(1){
		cout << "1 - Make Reservation\n"; //選擇要做的事情 
		cout << "2 - Reservation Enquiry/Canceling\n";
		cout << "3 - End\n";
	    do cout << "\nEnter your choice (1~3): ";
	    while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
	    cout << endl;
	    
	    switch ( choice )
	    {
	    case 1:
	        reservation(idnum, reservations);
	        break;
	
	    case 2:
	        queryDelete(idnum, reservations);
	        break;
	    case 3:
	        return;
	
	    default:
	        cout << "\nIncorrect choice!\n";
	        break;
	    }
	}
}    

void reservation( char IDNumber[], vector< ReservationRecord > &reservations ){
	for(int i=1; i<=16; i++){
		cout << i << ". " << branchNames[i] << endl; //輸出所有分店選擇 
	}
	int branchchoice;
	
	do cout << "\nEnter your choice (0 to end): ";
	while( ( branchchoice = inputAnInteger( 0, 16 ) ) == -1 ); //輸入選擇 
	cout << endl;
	if(branchchoice==0){ //如果為零返回 
		return;
	}
	Date currentDate; //宣告新的變數 
	compCurrentDate( currentDate);	//計算正確時間 
	cout << "The current hour is " << currentDate.year << "/" << currentDate.month << "/" << currentDate.day << ":" << currentDate.hour << endl << endl;
	//cout << "The current hour is " << currentDate.year << "/" << currentDate.month << "/" << currentDate.day << ":" << currentDate.hour << endl << endl;
	Date availableDate[8]; //宣告可能的時間 
	compAvailableDates( currentDate, availableDate);  
	for(int i=1; i<=7; i++){ //輸出可選擇的日期 
		cout << i << ". " << availableDate[i].year << "/" << availableDate[i].month << "/" << availableDate[i].day << endl;
	}
	//cout << endl;
	int timechoice;
	do cout << "\nEnter your choice (0 to end): ";
	while( ( timechoice = inputAnInteger( 0, 7 ) ) == -1 );
	//cout << endl;
	if(timechoice==0){
		cout << endl;
		return;
	}
	
	int hourchoice;
	int a = ++currentDate.hour;
	
	if(currentDate.hour!=23 && currentDate.day == availableDate[timechoice].day){ //輸入小時 
		do cout << "\nEnter hour (" << a << "~23):";  //判斷時間是否為23時,如果是則不同選項 
		while( ( hourchoice = inputAnInteger( a, 23 ) ) == -1 );		
	}else{
		do cout << "\nEnter hour (0~23): ";  
		while( ( hourchoice = inputAnInteger( 0, 23 ) ) == -1 );		
	}
	
	int numberchoice;
	do cout << "\nEnter the number of customers (1~30, 0 to end): "; //輸入有幾個人 
	while( ( numberchoice = inputAnInteger( 0, 30 ) ) == -1 );
	if(numberchoice==0){
		return;
	}
	cout << endl;
	
	ReservationRecord in; //宣告新的變數存資料 
	strcpy_s(in.IDNumber, IDNumber);
	in.branchCode = branchchoice;
	in.date.year = availableDate[timechoice].year;
	in.date.month = availableDate[timechoice].month;
	in.date.day = availableDate[timechoice].day;
	in.date.hour = hourchoice;
	in.numCustomers = numberchoice;
	//cout << in.IDNumber << " " << in.branchCode << " " << in.numCustomers << " "  << in.date.year << "/" << in.date.month << "/" << in.date.day << ":" << in.date.hour << endl;
	reservations.push_back(in); //把資料放入vector 
	cout << setw(24) << right << "Branch" << setw(18) << "Date" << setw(8) << "Hour" << setw(20) << "No of Custombers" << endl;
	output(in); //輸出訂位資訊 
	cout << endl << endl;
	//cout << setw(24) << right << branchNames[branchchoice] << setw(12) << in.date.year << "-" << in.date.month << "-" << in.date.day << setw(8) << in.date.hour << setw(20) << in.numCustomers << endl << endl;
	//cout << reservations[0].IDNumber << " " << reservations[0].branchCode << " " << reservations[0].numCustomers << " " << reservations[0].date.year << "/" << reservations[0].date.month << "/" << reservations[0].date.day << ":" << reservations[0].date.hour << endl;
	cout << "Reservation Completed!" << endl << endl;	
}

void compCurrentDate( Date &currentDate ){
	/*time_t rawTime = time(0); //計算正確時間 
	tm *structuredTime = localtime(&rawTime);
	
	currentDate.year =  structuredTime->tm_year + 1900;
	currentDate.month = structuredTime->tm_mon + 1;
	currentDate.day = structuredTime->tm_mday;
	currentDate.hour = structuredTime->tm_hour;
	*/
	  //Demo的時候用 
	tm structuredTime;
	time_t rawTime = time(0);
	localtime_s( &structuredTime, &rawTime);
	currentDate.year =  structuredTime.tm_year + 1900;
	currentDate.month = structuredTime.tm_mon + 1;
	currentDate.day = structuredTime.tm_mday;
	currentDate.hour = structuredTime.tm_hour;
	
}

void compAvailableDates( Date currentDate, Date availableDates[] ){
	int ycpy = currentDate.year;
	int mcpy = currentDate.month;
	int dcpy = 31; //判斷該月有幾天,該年是否為閏年 
	if(mcpy==4||mcpy==6||mcpy==9||mcpy==11){
		dcpy = 30;
	}
	if(mcpy==2){
		dcpy = 28 +(ycpy%4==0&&ycpy%100!=0||ycpy%400==0);
	}
	
	int day = currentDate.day;
	int day2 = currentDate.day+1;
	int month = currentDate.month;
	int year = currentDate.year;
	if(currentDate.hour!=23){
		for(int i=1; i<=7; i++ ){
			availableDates[i].year = year;
			availableDates[i].month = month;
			availableDates[i].day = day;
			availableDates[i].hour = currentDate.hour;
			day++;
			if(day>dcpy){  
				day-=dcpy; //如果到下一個月 
				month++;
			}
			if(month>12){ //如果到下一年 
				month-=12;
				year+1;
			}
		}
	}else{
		for(int i=1; i<=7; i++){
			availableDates[i].year = year;
			availableDates[i].month = month;
			availableDates[i].day = day2;
			availableDates[i].hour = currentDate.hour;
			day2++;
			if(day2>dcpy){
				day2-=dcpy;
				month++;
			}
			if(month>12){
				month-=12;
				year+1;
			}
		}	
	}
}

void output( ReservationRecord reservation ){ //輸出訂位資訊 
	cout << setw(24) << right << branchNames[reservation.branchCode] << setw(12) << reservation.date.year << "-" <<  setw(2) << reservation.date.month << "-" << setw(2) << reservation.date.day << setw(8) << reservation.date.hour << setw(20) << reservation.numCustomers;
}

void queryDelete( char IDNumber[], vector< ReservationRecord > &reservations ){
	cout << "  " << setw(24) << right << "Branch" << setw(18) << "Date" << setw(8) << "Hour" << setw(20) << "No of Custombers" << endl;
	int poin=1;
	for(int i=0; i<reservations.size(); i++){ //輸出所有訂位資訊 
		if(strcmp(IDNumber,reservations[i].IDNumber)==0){
			cout  << poin << ".";
			output(reservations[i]);
			cout << endl;
			poin++;
		}
	}
	int rechoice=0;
	do cout << "\nChoose a reservation to cancel (0:keep all reservation): "; //輸入要刪除的訂位 
	while( ( rechoice = inputAnInteger( 0, poin-1) ) == -1 );
	if(rechoice == 0){
		cout << endl;
		return;
	}
	
	int pcpy=1;
	for(int i=0; i<reservations.size(); i++){ //刪除存訂位的vector 
		if(strcmp(IDNumber, reservations[i].IDNumber)==0 && pcpy==rechoice){
			reservations.erase(reservations.begin()+i);
			break;
		}
		if (strcmp(IDNumber, reservations[i].IDNumber)==0) {
			pcpy++;
		}
	}
	cout << endl;
}

bool valid( char IDNumber[], char password[], const vector< MemberRecord > &memberDetails ){
	//vector< MemberRecord >::const_iterator p=memberDetails.begin();
	if(memberDetails.size()==0){
		return false;
	}
	for(unsigned int i = 0; i < memberDetails.size(); i++){ //判斷帳號密碼是符合 
		if(strcmp(IDNumber,memberDetails[i].IDNumber)==0 && strcmp(password,memberDetails[i].password)==0){
			return true;
		}
	}
	return false;    	
}

void registration( vector< MemberRecord > &memberDetails ){
	char idnum[12];
	char pass[24];
	char nm[8];
	cout << "Input Your ID Number: ";
	cin >> idnum;
	cout << endl;
	if(!legalID( idnum)){ //判斷身分證是否符合 
		cout << "The ID Number " << idnum << " is illegal." << endl << endl;
		return;
	}
	if( !existingID( idnum, memberDetails) ){ //判斷帳號是否存在 
		cout << "You are already a member!" << endl << endl;
		return;
	}
	cout << "Input Your Name: ";
	cin >> nm;
	cout << endl;
	cout << "Choose a Password: ";
	cin >> pass;
	cout << endl;
	MemberRecord cpy; //宣告新的變數存資料 
	strcpy_s( cpy.IDNumber, idnum);
	strcpy_s( cpy.password, pass);
	strcpy_s( cpy.name, nm);
	memberDetails.push_back(cpy); //把帳號資訊放入陣列 
	cout << "Registration Completed" << endl << endl;
}

bool legalID( char IDNumber[] ){
	int first=0, last=0, sum=0, a=0, b=0;
	int size=strlen(IDNumber);  //判斷帳號是否符合身分證規律 
	if(size!=10){
		return false;
	}else if(IDNumber[0]>='A' && IDNumber[0]<='H'){
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
	int c=0, n=0;
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
	/*for (int i = 0; i < memberDetails.size(); i++)
		if (!strcmp(IDNumber, memberDetails[i].IDNumber))
			return false;*/
	for(int i=0; i<memberDetails.size(); i++){ //判斷是否已經存在 
		if(strcmp(IDNumber,memberDetails[i].IDNumber)==0){
			return false;
		}
	}
	return true;
}

void saveMemberDetails( const vector< MemberRecord > &memberDetails ){
	//vector< MemberRecord >::const_iterator p=memberDetails.begin();  
	ofstream member2("Members.dat", ios::out | ios::binary);  //儲存帳號資訊到檔案 
	
    if (!member2){
        cout << "File could not be open!\n";
        exit(1);
    }
		
	for(int i=0; i<memberDetails.size(); i++){
		member2.write(reinterpret_cast<const char *>( &memberDetails[i]), sizeof(MemberRecord));
	}
}

void saveReservations( const vector< ReservationRecord > &reservations ){
	ofstream re2("Reservations.dat", ios::out | ios::binary); //儲存訂位資訊到檔案 
	
    if (!re2){
        cout << "File could not be open!\n";
        exit(1);
    }
		
	for(int i=0; i<reservations.size(); i++){
		re2.write(reinterpret_cast<const char *>( &reservations[i]), sizeof(ReservationRecord));
	}
}
