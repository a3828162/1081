#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <time.h>
#include <string>
#include <string.h>
#include <stdlib.h>
using namespace::std;

char foods[ 14 ][ 48 ] = { "",
                           "Pork XiaoLongBao (12)",
                           "Steamed Vegetable and Ground Pork Dumplings (8)",
                           "Steamed Shrimp and Pork Dumplings (8)",
                           "Steamed Fish Dumplings (8)",
                           "Steamed Vegetarian Mushroom Dumplings (8)",
                           "Steamed Shrimp and Pork Shao Mai (12)",
                           "Pork Buns (5)",
                           "Vegetable and Ground Pork Buns (5)",
                           "Red Bean Buns (5)",
                           "Sesame Buns (5)",
                           "Taro Buns (5)",
                           "Vegetarian Mushroom Buns (5)",
                           "Golden Lava Buns (5)" };

int price[ 14 ] = { 0, 220, 176, 216, 200, 200, 432, 225,
                       225, 200, 200, 225, 250, 225 };

struct Date
{
   int year;
   int month;
   int day;
};

struct Account
{
   char email[ 40 ]; // used as the account number
   char password[ 20 ];
   char name[ 12 ];
   char address[ 80 ];
   char phone[ 12 ];
   int cart[ 14 ]={}; // Cart[i] is the quantity of food #i in the shopping cart
};

struct Order
{
   char orderNumber[ 12 ];
   char email[ 40 ];
   Date deliveryDate;
   Date arrivalDate;
   int quantity[ 14 ]={}; // quantity[i] is the quantity of food #i in the order
};

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// add a new account to the file Accounts.dat
void registration( vector< Account > &accountDetails );

// return true if email belongs to accountDetails
bool exists( char email[], const vector< Account > &accountDetails );

// save all elements in accountDetails to the file Accounts.dat
void saveAllAccounts( const vector< Account > &accountDetails );

// login and call shopping
void login( vector< Account > &accountDetails );

// load all accounts details from the file Accounts.dat
void loadAccountDetails( vector< Account > &accountDetails );

// return true if there exists an account with specified email and password; and
// put the account with specified email and password into account
bool valid( char email[], char password[], Account &account,
            const vector< Account > &accountDetails );

// add chosen Foods to the shopping cart
void shopping( Account &account );

// return true if the shopping cart is empty
bool emptyCart( const Account &account );

// display the shopping cart in account
bool displayCart( const Account &account );

// append account in the file Accounts.dat
void saveAccount( const Account &account );

// update the shopping cart in account
void updateCart( Account &account );

// generate a Bill and reset account.cart
void check( Account &account );

// compute the current date
void compCurrentDate( Date &currentDate );

// open the file Orders.txt and call displayOrderDetails twice
void createOrder( const Account &account, const Order &order );

// write an order to Orders.txt or display it on the output window depending on os
void displayOrderDetails( ostream &os, const Account &account, const Order &order );

int main()
{
   vector< Account > accountDetails; // account details for all accounts

   cout << "Welcome to DintaiFung Shopping Mall!\n";
   srand( static_cast< int >( time( 0 ) ) );

   int choice;
	loadAccountDetails(accountDetails);
   while( true )
   {
      cout << "\n1 - Registration\n";
      cout << "2 - Login\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch( choice )
      {
      case 1:
         registration( accountDetails );
         break;

      case 2:
         login( accountDetails );
         break;

      case 3:
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;
      }
   }

   system( "pause" );
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

void registration( vector< Account > &accountDetails ){
	
	Account in;
	
	cout << "Email address (Account number): ";  
	cin >> in.email;
	
	if( !exists( in.email, accountDetails) ){ //判斷帳號是否存在 
		cout << "You are already a member!" << endl << endl;
		return;
	}
	
	cout << "Password: ";
	cin >> in.password;
	
	cout << "Name: ";
	cin >> in.name;
	
	cout << "Shipping address: ";
	cin >> in.address;
	
	cout << "Contact phone number: ";
	cin >> in.phone;
	
	accountDetails.push_back(in);
	
	saveAllAccounts( accountDetails );
}

bool exists( char email[], const vector< Account > &accountDetails ){
	
	if(accountDetails.size()==0){  
		return true;
	}

	for(int i=0; i<accountDetails.size(); i++){ //判斷是否已經存在 
		if(strcmp(email,accountDetails[i].email)==0){
			return false;
		}
	}
	return true;	
}

void saveAllAccounts( const vector< Account > &accountDetails ){
	
	fstream m1("Accounts.dat", ios::app | ios::binary);  //儲存帳號資訊到檔案 
	
    if (!m1){
		ofstream m2( "Accounts.dat", ios::binary);
		if(!m2){
			cerr << "File could not be opened" << endl;
			system("pause");
			exit(1);
		}
    }else{
    	for(int i=0; i<accountDetails.size(); i++){
			m1.write(reinterpret_cast<const char *>( &accountDetails[i]), sizeof(Account));
		}	
	}
	
}

void login( vector< Account > &accountDetails ){
	
	char idnum[40];
	char nm[20];
	Account account;
	while(1){
		cout << "Please enter your ID number: ";
		cin >> idnum;
		cout << endl;
		cout << "Enter your password: ";
		cin >> nm;
		cout << endl;
		if(!valid( idnum, nm, account, accountDetails)){ //判斷帳號密碼是否正確 
			cout << "Invalid account number or password. Please try again." << endl << endl;
		}else{
			break;
		}
	}
	/*for(int i=1;i<=13;i++){
		cout << accountDetails[0].cart[i] << endl;
	}
	cout << "-------" << endl;
	for(int i=1;i<=13;i++){
		cout << account.cart[i] << endl;
	}*/	
	shopping(account);

}

void loadAccountDetails( vector< Account > &accountDetails ){
	Account in;
	fstream m1( "Accounts.dat", ios::in | ios::out | ios::binary ); //讀檔 
	if(!m1){
		ofstream m2( "Accounts.dat", ios::binary); //如果原先沒有檔案先創檔 
		if(!m2){
			cerr << "File could not be opened" << endl;
			system("pause");
			exit(1);
		}
	}else{
		while(m1.read((char *)( &in), sizeof(Account))){
			accountDetails.push_back(in);
		}		
	}	
}

bool valid( char email[], char password[], Account &account,
            const vector< Account > &accountDetails ){
            	
	if(accountDetails.size()==0){
		return false;
	}
	for(unsigned int i = 0; i < accountDetails.size(); i++){ //判斷帳號密碼是符合 
	
		if(strcmp(email,accountDetails[i].email)==0 && strcmp(password,accountDetails[i].password)==0){
			strcpy_s(account.email,accountDetails[i].email); //把資料存到account 
			strcpy_s(account.password,accountDetails[i].password);
			strcpy_s(account.name,accountDetails[i].name);
			strcpy_s(account.address,accountDetails[i].address);
			strcpy_s(account.phone,accountDetails[i].phone);
			for(int j=1;j<=13;j++){
				account.cart[j]=accountDetails[i].cart[j];
			}
			return true;
		}
	}
	return false;                	
}

void shopping( Account &account ){
	
	int i=0;
	int foodchoice=0;
	int num=0;
	if(emptyCart(account)){ //判斷是否已有訂單 
		for(i=1;i<=13;i++){
			cout << right << setw(2) << i << ". " << left << setw(50)<<foods[i];
			cout << setw(20) << price[i] << endl;
		}
		foodchoice=0;
		do cout << "\nEnter your choice (0 to logout): ";
		while( ( foodchoice = inputAnInteger( 0, 16 ) ) == -1 ); //輸入選擇 
		//cout << endl;
		if(foodchoice==0){ //如果為零返回 
			return;
		}
		cout << "\n\nEnter the quantity: "; //輸入數量 
		cin >> num;
		account.cart[foodchoice]+=num;
		cout << "\nYour Shopping Cart Contents:" << endl << endl;
		displayCart( account );
		saveAccount(account);
	}else{
		for(i=1;i<=13;i++){
			cout << right << setw(2) << i << ". " << left << setw(50)<<foods[i];
			cout << setw(20) << price[i] << endl;
		}
		cout << "\n14. View your shopping cart";
		foodchoice=0;
		do cout << "\n\nEnter your choice (0 to logout): ";
		while( ( foodchoice = inputAnInteger( 0, 16 ) ) == -1 ); //輸入選擇 
		//cout << endl;
		if(foodchoice==0){ //如果為零返回 
			return;
		}
		if(foodchoice==14){
			cout << "Your Shopping Cart Contents:" << endl << endl;
			displayCart(account);
		}else{
			cout << "\nEnter the quantity: ";
			cin >> num;
			account.cart[foodchoice]+=num;
			cout << "\nYour Shopping Cart Contents:" << endl << endl;
			displayCart( account ); //展開購物車資料	
			saveAccount(account); //每次購買都存一次 
		}
	}
	
	int choice;
	while(1){
		cout << "1 - Continue Shopping\n"; //選擇要做的事情 
		cout << "2 - Update Cart\n";
		cout << "3 - Check\n";
	    do cout << "\nEnter your choice (1~3): ";
	    while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
	    cout << endl;
	    
	    switch ( choice )
	    {
	    case 1:
			for(i=1;i<=13;i++){
				cout << right << setw(2) << i << ". " << left << setw(50)<<foods[i];
				cout << setw(20) << price[i] << endl;
			}
			cout << "\n14. View yout shopping cart";
			foodchoice=0;
			do cout << "\n\nEnter your choice (0 to logout): ";
			while( ( foodchoice = inputAnInteger( 0, 16 ) ) == -1 ); //輸入選擇 
			//cout << endl;
			if(foodchoice==0){ //如果為零返回 
				return;
			}
			if(foodchoice==14){ //輸入14則展示購物車 
				cout << "\nYour Shopping Cart Contents:" << endl << endl;
				displayCart( account );
				saveAccount(account);
			}else{
				cout << "\nEnter the quantity: ";
				cin >> num;
				account.cart[foodchoice]+=num;
				cout << "Your Shopping Cart Contents:" << endl << endl;
				displayCart( account );
				saveAccount(account);
			}

			continue;
	    case 2:
	        updateCart( account );
	        continue;
	    case 3:
	    	check( account );
	        return;
	
	    default:
	        cout << "\nIncorrect choice!\n";
	        break;
	    }
	}
	
}

void saveAccount( const Account &account ){
	ifstream file("Accounts.dat", ios::binary);
	int i=0;
	int j=0;
	file.seekg(0,file.end);  
	int n=file.tellg(); //找出檔案大小 
	file.seekg(0,file.beg); //移動讀取位置 
	char a[40]={};
	//cout << "---" << sizeof(account.email) << endl;
	//file.read((char *)( &a), sizeof(account.email));
	//cout << "----" << a << endl;
	//cout << "---" << n << endl;
	for(i=0;i<n;i+=sizeof(Account)){
		//cout << "----" <<i << endl;
		file.seekg(i,file.beg); //移動到email的位址 
		file.read((char *)( &a), sizeof(account.email)); //讀email  
		if(strcmp(a,account.email)==0){  //比對 
			j=i/sizeof(Account);  
			break;
		}
		a[40]={};
	}
	//cout << j << endl;
	
	fstream f("Accounts.dat", ios::binary | ios::out | ios::in);  
	f.seekp((j*sizeof(Account)),f.beg); //移動到符合位址 
	f.write(reinterpret_cast<const char *>( &account), sizeof(Account)); //寫檔 
}

bool emptyCart( const Account &account ){
	
	for(int i=1;i<=13;i++){ //判斷有沒有商品 
		if(account.cart[i]!=0){
			return false;
		}
	}
	
	return true;
}

bool displayCart( const Account &account ){
	int total=0; //輸出資料 
	cout << "Code" << setw(50) <<right<< "Item" << setw(8) << "Price" << setw(12) << "Quantity" << setw(10) << "Subtotal" << endl;
	for(int i=1;i<=13;i++){
		if(account.cart[i]!=0){
			total+=price[i]*account.cart[i];
			cout << setw(4) << i <<right<< setw(50) << foods[i] << setw(8) << price[i] << setw(12) << account.cart[i] << setw(10) << price[i]*account.cart[i] << endl;
		}
	}
	cout << endl;
	cout <<"Total Cost: " << total << endl << endl;
	return true;
}

void updateCart( Account &account ){
	int choice=0;
	int num=0;
	while(1){
		cout << "Enter the porduct code: "; //更改商品數量 
		cin >> choice;
		cout << endl;
		if(account.cart[choice]!=0){ //只能更改已有的商品數量 
			break;
		}	
	}
	cout << "Enter the quantity: ";
	cin >> num;
	account.cart[choice]=num;
	
	displayCart( account );  
	saveAccount( account ); //存檔 
}

void check( Account &account ){
	Order order; //結帳 
	
	srand(time(NULL)); //生成訂單編號 
	int a = rand()%26;  
	order.orderNumber[0]='Z'-a;
	int b=0;
	for(int i=1;i<=9;i++){
		b=rand()%10;
		order.orderNumber[i]='9'-b;
	}
	order.orderNumber[10]='\0';
	//cout << order.orderNumber << endl;
	
	compCurrentDate( order.deliveryDate ); //輸入到達時間 
	cout << "Enter arrival Date" << endl;
	cout << "year: ";
	cin >> order.arrivalDate.year;
	cout << "month: ";
	cin >> order.arrivalDate.month;
	cout << "day: ";
	cin >> order.arrivalDate.day;
	for(int i=1;i<=13;i++){
		order.quantity[i] = account.cart[i]; //把account 的商品數量存到order 
	}
	createOrder( account, order); //生成訂單 
	for(int i=0;i<=13;i++){
		account.cart[i]=0; //結帳完account歸零 
	}
	saveAccount(account); //存檔 

}

void compCurrentDate( Date &currentDate ){
	/*
	time_t rawTime = time(0); //計算正確時間 
	tm *structuredTime = localtime(&rawTime);
	
	currentDate.year =  structuredTime->tm_year + 1900;
	currentDate.month = structuredTime->tm_mon + 1;
	currentDate.day = structuredTime->tm_mday;
	*/
	  //Demo的時候用 
	
	tm structuredTime;
	time_t rawTime = time(0);
	localtime_s( &structuredTime, &rawTime);
	currentDate.year =  structuredTime.tm_year + 1900;
	currentDate.month = structuredTime.tm_mon + 1;
	currentDate.day = structuredTime.tm_mday;
	
}

void createOrder( const Account &account, const Order &order ){
	
	ofstream outFile("Orders.txt", ios::app);
	displayOrderDetails(outFile, account, order);
	displayOrderDetails(cout, account, order);
	outFile.close();
	cout << "An order has been created.\n";
}

void displayOrderDetails( ostream &os, const Account &account, const Order &order ){
	os << "\nOrder number: " << order.orderNumber << endl;
	os << "Delivery Date: " << order.deliveryDate.year << "/" << order.deliveryDate.month << "/" << order.deliveryDate.day << endl;
	os << "Arrival Date: " << order.arrivalDate.year << "/" << order.arrivalDate.month << "/" << order.arrivalDate.day << endl;
	os << "Recipient: " << account.email << endl;
	os << "Contact Phone Number: " << account.phone << endl;
	os << "Shipping address: " << account.address << endl << endl;
	os << "Shopping details:\n\n";
	int total = 0;
	os << "Code" << setw(50) << right << "Item" << setw(8) << "Price" << setw(12) << "Quantity" << setw(10) << "Subtotal" << endl;
	for (int i = 1; i <= 13; i++) 
		if (order.quantity[i] != 0) 
		{
			total += price[i] * account.cart[i];
			os << setw(4) << i << right << setw(50) << foods[i] << setw(8) << price[i] << setw(12) << order.quantity[i] << setw(10) << price[i] * order.quantity[i] << endl;
		}
	os << endl;
	os << "Total Cost: " << total << endl << endl;
}

