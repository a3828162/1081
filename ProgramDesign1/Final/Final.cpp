#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string>
#include <string.h>
using namespace std;

int adultTicketPrice[ 13 ][ 13 ] = {
   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   0,    0,    0,    0,  500,  700,  920, 1330, 1510, 1660, 1880, 2290, 2500,
   0,   40,    0,    0,  440,  640,  850, 1250, 1430, 1600, 1820, 2230, 2440,
   0,   70,   40,    0,  400,  590,  800, 1210, 1390, 1550, 1780, 2180, 2390,
   0,  200,  160,  130,    0,  400,  620, 1010, 1210, 1370, 1580, 1990, 2200,
   0,  330,  290,  260,  130,    0,  410,  820, 1010, 1160, 1390, 1790, 2000,
   0,  480,  430,  400,  280,  140,    0,  610,  790,  950, 1160, 1580, 1790,
   0,  750,  700,  670,  540,  410,  270,    0,  400,  550,  770, 1180, 1390,
   0,  870,  820,  790,  670,  540,  390,  130,    0,  370,  580, 1000, 1210,
   0,  970,  930,  900,  780,  640,  500,  230,  110,    0,  430,  830, 1040,
   0, 1120, 1080, 1050,  920,  790,  640,  380,  250,  150,    0,  620,  820,
   0, 1390, 1350, 1320, 1190, 1060,  920,  650,  530,  420,  280,    0,  410,
   0, 1530, 1490, 1460, 1330, 1200, 1060,  790,  670,  560,  410,  140,    0 };

char departureTimes[ 37 ][ 8 ] = { "",
   "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30",
   "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30",
   "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
   "18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30",
   "22:00", "22:30", "23:00", "23:30" };

struct Reservation
{
   char reservationNumber[ 12 ]; // used to identify a reservation
   char trainNumber[ 8 ];  // used to identify a train
   char idNumber[ 12 ];    // the id number of the contact person
   char phone[ 12 ];       // the (local or mobile) phone number of the contact person
   char date[ 12 ];        // outbound date
   int originStation;      // the origin station code
   int destinationStation; // the destination station code
   int carClass;           // the car class code; 1:standard car, 2:business car
   int adultTickets;       // the number of adult tickets
   int concessionTickets;  // the number of concession tickets
};

struct Train
{
   char trainNumber[ 8 ];          // used to identify a train
   char departureTimes[ 13 ][ 8 ]; // the departure time of a train for each station,
};                                 // departureTimes[0] is not used

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

void makingReservation( Train southboundTimetable[ 100 ], Train northboundTimetable[ 100 ] );

// inputs originStation, destinationStation, carClass,
// date, departureTime, adultTickets and concessionTickets
void inputReservationDetails( Reservation &reservation, int &departureTime );

// loads the southbound timetable from the file "Southbound timetable.txt"
void loadSouthboundTimetable( Train southboundTimetable[ 100 ], int &numSouthboundTrains );

// loads the northbound timetable from the file "Northbound timetable.txt"
void loadNorthboundTimetable( Train northboundTimetable[ 100 ], int &numNorthboundTrains );

// displays timetables for 10 coming southbound trains, then let user select one
void selectSouthboundTrain( Train southboundTimetable[ 100 ], int numSouthboundTrains,
                            Reservation &reservation, int departureTime );

// displays timetables for 10 coming northbound trains, then let user select one
void selectNorthboundTrain( Train northboundTimetable[ 100 ], int numNorthboundTrains,
                            Reservation &reservation, int departureTime );

// inputs idNumber and phone, and randomly generate reservationNumber
void inputContactInfo( Reservation &reservation );

// save reservation to the end of the file Reservation details.dat
void saveReservation( Reservation reservation );

void reservationHistory( Train southboundTimetable[ 100 ],
                         Train northboundTimetable[ 100 ] );

// inputs idNumber and reservationNumber, and
// checks if the corresponding reservation exists
bool existReservation( fstream &ioFile, Reservation &reservation );


void displayReservations( Train southboundTimetable[ 100 ],
                          Train northboundTimetable[ 100 ], Reservation reservation );

// displays date, originStation, destinationStation, departureTime, arrival time,
// fare for adultTickets, fare for concessionTickets and total fare
void display( Reservation reservation, Train trainTimetable[ 100 ],
              char stations[ 13 ][ 12 ], char carClass[ 12 ] );

// reduces adultTickets and/or concessionTickets in reservation
void reduceSeats( fstream &ioFile, Train southboundTimetable[ 100 ],
                  Train northboundTimetable[ 100 ], Reservation &reservation );

int main()
{
   cout << "Taiwan High Speed Rail Booking System\n";
   srand( static_cast< unsigned int >( time( 0 ) ) );

   Train southboundTimetable[ 100 ];
   Train northboundTimetable[ 100 ];
   int choice; // store user choice

   // enable user to specify action
   while( true )
   {
      cout << "\nEnter Your Choice\n"
         << "1. Booking\n"
         << "2. Booking History\n"
         << "3. End Program";

      do cout << "\n? ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch( choice )
      {
      case 1:
         makingReservation( southboundTimetable, northboundTimetable );
         break;
      case 2:
         reservationHistory( southboundTimetable, northboundTimetable );
         break;
      case 3:
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;
      default: // display error if user does not select valid choice
         cerr << "Incorrect Choice!\n";
         break;
      }
   }

   system( "pause" );
} // end main

int inputAnInteger(int begin, int end) {

	char a[50];
	cin.getline(a, 50);
	if (!strlen(a)) {
		cin.getline(a, 50);
	}
	for (int i = 0; i < strlen(a); i++) {
		if (a[i]<'0' || a[i]>'9') {
			return -1;
		}
	}

	int n = atoi(a);

	if (n >= begin && n <= end) {
		return n;
	}
	else {
		return -1;
	}

}

void makingReservation(Train southboundTimetable[100], Train northboundTimetable[100]) {

	Reservation reservation;
	int departureTime = 0, southnum = 0, northnum = 0;
	loadSouthboundTimetable(southboundTimetable, southnum);
	loadNorthboundTimetable(northboundTimetable, northnum);

	inputReservationDetails(reservation, departureTime);


	if (reservation.originStation > reservation.destinationStation)
		selectNorthboundTrain(northboundTimetable, northnum, reservation, departureTime);
	else if(reservation.originStation < reservation.destinationStation)
		selectSouthboundTrain(southboundTimetable, southnum, reservation, departureTime);

	inputContactInfo(reservation);
	saveReservation(reservation);
}

void inputReservationDetails(Reservation& reservation, int& departureTime) {
	while (1) {
		while (1) {
			cout << "Original station\n1. Nangang\n2. Taipei\n3. Banqiao\n4. Taoyuan\n5. Hsinchu\n6. Miaoli"
				<< "\n7. Taichung\n8. Changhua\n9. Yunlin\n10. Chiayi\n11. Tainan\n12. Zuoying" << endl;
			do cout << "\n? ";
			while ((reservation.originStation = inputAnInteger(1, 12)) == -1);
			cout << endl;

			cout << "Destination station\n1. Nangang\n2. Taipei\n3. Banqiao\n4. Taoyuan\n5. Hsinchu\n6. Miaoli"
				<< "\n7. Taichung\n8. Changhua\n9. Yunlin\n10. Chiayi\n11. Tainan\n12. Zuoying" << endl;
			do cout << "\n? ";
			while ((reservation.destinationStation = inputAnInteger(1, 12)) == -1);
			cout << endl;

			if (reservation.originStation != reservation.destinationStation)
				break;
			else if (reservation.originStation == reservation.destinationStation)
				cout << "不能選同一站 請重新選擇!\n" << endl;
		}
		cout << "Car Class\n1. Standard Car\n2. Business Car" << endl;
		do cout << "\n? ";
		while ((reservation.carClass = inputAnInteger(1, 2)) == -1);

		if ((reservation.carClass == 2 && reservation.originStation == 1 && reservation.destinationStation == 2) ||
			(reservation.carClass == 2 && reservation.originStation == 1 && reservation.destinationStation == 3) ||
			(reservation.carClass == 2 && reservation.originStation == 2 && reservation.destinationStation == 3))
			cout << "\n這區段沒有商務艙!\n"<<endl;
		else
			break;
	}
	cout << "\nDeparture Date: ";
	cin >> reservation.date;

	cout << "\nDeparture Time" << endl;
	for (int i = 1; i <= 34; i++)
		cout << i << ". " << departureTimes[i] << endl;
	do cout << "\n? ";
	while ((departureTime = inputAnInteger(1, 34)) == -1);

	while (1) {
		cout << "\nHow many adult tickets? ";
		cin >> reservation.adultTickets;
		cout << "\nHot many concession tickets? ";
		cin >> reservation.concessionTickets;

		if (reservation.adultTickets + reservation.concessionTickets != 0)
			break;
		cout << "\n票數不能為0" << endl;
	}
}

void loadSouthboundTimetable(Train southboundTimetable[100], int& numSouthboundTrains) {

	ifstream inFile("Southbound timetable.txt", ios::in);

	if (!inFile) {
		cout << "File could not be opened";
		system("pause");
		exit(1);
	}

	int i = 0;

	while (!inFile.eof()) {
		inFile >> southboundTimetable[i].trainNumber;
		for (int j = 1; j <= 12; j++) {
			inFile >> southboundTimetable[i].departureTimes[j];
		}
		i++;
	}

	numSouthboundTrains = i;
}

void loadNorthboundTimetable(Train northboundTimetable[100], int& numNorthboundTrains) {

	ifstream inFile("Northbound timetable.txt", ios::in);

	if (!inFile) {
		cout << "File could not be opened";
		system("pause");
		exit(1);
	}

	int i = 0;

	while (!inFile.eof()) {
		inFile >> northboundTimetable[i].trainNumber;
		for (int j = 1; j <= 12; j++)
			inFile >> northboundTimetable[i].departureTimes[j];
		i++;
	}
	numNorthboundTrains = i;
}

void selectNorthboundTrain(Train northboundTimetable[100], int numNorthboundTrains,
	Reservation& reservation, int departureTime) {
	int i = 0, j = 0, a = 0, b = 0;

	a = reservation.destinationStation;
	b = reservation.originStation;

	cout << setw(9) << "\nTrain NO." << setw(11) << "Departure" << setw(9) << "Arrival" << endl;
	for (j = 0; j < numNorthboundTrains; j++) {
		if ((strcmp(departureTimes[departureTime], northboundTimetable[j].departureTimes[reservation.originStation]) == -1 || strlen(northboundTimetable[j].departureTimes[reservation.destinationStation]) > strlen(departureTimes[departureTime])) && strlen(northboundTimetable[j].departureTimes[reservation.destinationStation]) != 1) {
			i++;
			cout << setw(9) << northboundTimetable[j].trainNumber << setw(11) << northboundTimetable[j].departureTimes[a]
				<< setw(9) << northboundTimetable[j].departureTimes[b] << endl;
		}

		if (i == 10)
			break;
	}

	cout << "\nEnter Train Number: ";
	cin >> reservation.trainNumber;
	cout << "\nTrip Details" << endl;

	char stations[13][12] = { "","Nangang","Taipei" ,"Banqiao","Taoyuan","Hsinchu","Miaoli","Taichung",
							"Changhua","Yunlin","Chiayi","Tainan","Zuoying" };
	char carclass[12] = {};

	if (reservation.carClass == 1)
		strcpy_s(carclass, "Standard");
	else if (reservation.carClass == 2)
		strcpy_s(carclass, "Business");

	display(reservation, northboundTimetable, stations, carclass);
}

void selectSouthboundTrain(Train southboundTimetable[100], int numSouthboundTrains,
	Reservation& reservation, int departureTime) {
	int i = 0, j = 0;

	cout << setw(9) << "\nTrain NO." << setw(11) << "Departure" << setw(9) << "Arrival" << endl;
	for (j = 0; j < numSouthboundTrains; j++) {
		if ((strcmp(departureTimes[departureTime], southboundTimetable[j].departureTimes[reservation.originStation]) == -1 || strlen(southboundTimetable[j].departureTimes[reservation.destinationStation]) > strlen(departureTimes[departureTime])) && strlen(southboundTimetable[j].departureTimes[reservation.destinationStation]) != 1) {
			i++;
			cout << setw(9) << southboundTimetable[j].trainNumber << setw(11) << southboundTimetable[j].departureTimes[reservation.originStation]
				<< setw(9) << southboundTimetable[j].departureTimes[reservation.destinationStation] << endl;
		}

		if (i == 10)
			break;
	}

	cout << "\n\nEnter Train Number: ";
	cin >> reservation.trainNumber;
	cout << "\nTrip Details" << endl;

	char stations[13][12] = { "","Nangang","Taipei" ,"Banqiao","Taoyuan","Hsinchu","Miaoli","Taichung",
							"Changhua","Yunlin","Chiayi","Tainan","Zuoying" };
	char carclass[12] = {};

	if (reservation.carClass == 1)
		strcpy_s(carclass, "Standard");
	else if(reservation.carClass == 2)
		strcpy_s(carclass, "Business");

	display(reservation, southboundTimetable, stations, carclass);
}

void display(Reservation reservation, Train trainTimetable[100],
	char stations[13][12], char carClass[12]) {

	cout << setw(10) << "Date" << setw(11) << "Train NO." << setw(8) << "From" << setw(10) << "To" << setw(11)
		<< "Departure" << setw(9) << "Arrival" << setw(8) << "Adult" << setw(12) << "Concession" << setw(6) << "Fare"
		<< setw(10) << "Class" << endl;

	int i = 0, a = 0, b = 0;

	for ( i = 0; i < 100; i++) {
		if (strcmp(reservation.trainNumber, trainTimetable[i].trainNumber) == 0)
			break;
	}

	if (reservation.originStation < reservation.destinationStation) {
		a = reservation.originStation, b = reservation.destinationStation;
	}
	else {
		a = reservation.destinationStation, b = reservation.originStation;
	}

	if (reservation.carClass == 1) {

		cout << setw(10) << reservation.date << setw(11) << reservation.trainNumber << setw(8) << stations[reservation.originStation]
			<< setw(10) << stations[reservation.destinationStation] << setw(11) << trainTimetable[i].departureTimes[a] << setw(9) << trainTimetable[i].departureTimes[b]
			<< setw(6) << adultTicketPrice[reservation.destinationStation][reservation.originStation] << "*" << reservation.adultTickets
			<< setw(10) << (adultTicketPrice[reservation.destinationStation][reservation.originStation] / 2) << "*" << reservation.concessionTickets
			<< setw(6) << (adultTicketPrice[reservation.destinationStation][reservation.originStation] * reservation.adultTickets) + ((adultTicketPrice[reservation.destinationStation][reservation.originStation] / 2) * reservation.concessionTickets)
			<< setw(10) << carClass;
	}
	else if (reservation.carClass == 2) {
		cout << setw(10) << reservation.date << setw(11) << reservation.trainNumber << setw(8) << stations[reservation.originStation]
			<< setw(10) << stations[reservation.destinationStation] << setw(11) << trainTimetable[i].departureTimes[a] << setw(9) << trainTimetable[i].departureTimes[b]
			<< setw(6) << adultTicketPrice[reservation.originStation][reservation.destinationStation] << "*" << reservation.adultTickets
			<< setw(10) << (adultTicketPrice[reservation.originStation][reservation.destinationStation] / 2) << "*" << reservation.concessionTickets
			<< setw(6) << (adultTicketPrice[reservation.originStation][reservation.destinationStation] * reservation.adultTickets) + ((adultTicketPrice[reservation.originStation][reservation.destinationStation] / 2) * reservation.concessionTickets)
			<< setw(10) << carClass;
	}
	
}

void inputContactInfo(Reservation& reservation) {
	cout << "\nEnter Contact Person Information" << endl;
	cout << "\nID Number: ";
	cin >> reservation.idNumber;
	cout << "\nPhone: ";
	cin >> reservation.phone;
	for (int i = 0; i < 8; i++) {
		int a = rand() % 10;
		reservation.reservationNumber[i] = '9' - a;
	}
	reservation.reservationNumber[8] = '\0';
	cout << "\nReservation Number: " << reservation.reservationNumber << endl << endl;
	cout << "Reservation Completed!" << endl << endl;
}

void saveReservation(Reservation reservation) {

	fstream m1("details.dat", ios::binary | ios::out | ios::app);

	if (!m1) {
		ofstream m2("details.dat", ios::binary | ios::out);

		if (!m2) {
			cout << "File could not be opened!" << endl;
			system("pause");
			exit(1);
		}

		m2.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));
	}
	else {
		if (!m1) {
			cout << "File could not be opened!" << endl;
			system("pause");
			exit(1);
		}

		m1.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));
	}
}

void reservationHistory(Train southboundTimetable[100],
	Train northboundTimetable[100]) {
	fstream ioFile("details.dat", ios::binary | ios::in | ios::out);
	if (!ioFile) {
		cout << "File could not be opened!" << endl;
		system("pause");
		exit(1);
	}
	Reservation reservation, out;
	cout << "Enter ID Number: ";
	cin >> reservation.idNumber;
	cout << "\nEnter Reservation Number: ";
	cin >> reservation.reservationNumber;
	while (!existReservation(ioFile, reservation)) {
		cout << "\nReservation record not found.\n" << endl;
		cout << "Enter ID Number: ";
		cin >> reservation.idNumber;
		cout << "\nEnter Reservation Number: ";
		cin >> reservation.reservationNumber;
	}
	displayReservations(southboundTimetable, northboundTimetable, reservation);
	int choice = 0, n = 0, i = 0;
	while (true)
	{
		cout << "\n\nEnter Your Choice\n"
			<< "1. Cancellation\n"
			<< "2. Reduce\n"
			<< "3. End";
		do cout << "\n? ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;
		switch (choice)
		{
		case 1:
			ioFile.seekg(0, ios::end);
			n = ioFile.tellg();
			ioFile.seekg(0, ios::beg);
			for (i = 0; i < n; i += sizeof(Reservation)) {
				Reservation in;
				ioFile.seekp(i, ios::beg);
				ioFile.read(reinterpret_cast<char*>(&in), sizeof(Reservation));
				if (strcmp(reservation.idNumber, in.idNumber) == 0 && strcmp(reservation.reservationNumber, in.reservationNumber) == 0) {
					break;
				}
			}
			ioFile.seekg(i, ios::beg);
			ioFile.write(reinterpret_cast<const char*>(&out), sizeof(Reservation));
			cout << "Reservation Cancelled!" << endl;
			return;
		case 2:
			reduceSeats(ioFile, southboundTimetable, northboundTimetable, reservation);
			return;
		case 3:
			return ;
		default: // display error if user does not select valid choice
			cerr << "Incorrect Choice!\n";
			break;
		}
	}
}

bool existReservation(fstream& ioFile, Reservation& reservation) {

	ioFile.seekg(0, ios::end);
	int n = ioFile.tellg();
	ioFile.seekg(0, ios::beg);

	for (int i = 0; i < n; i += sizeof(Reservation)) {
		Reservation in;
		ioFile.seekp(i, ios::beg);
		ioFile.read(reinterpret_cast<char*>(&in), sizeof(Reservation));
		if (strcmp(reservation.idNumber, in.idNumber) == 0 && strcmp(reservation.reservationNumber, in.reservationNumber) == 0) {
			strcpy_s(reservation.trainNumber, in.trainNumber);
			strcpy_s(reservation.date, in.date);
			strcpy_s(reservation.phone, in.phone);
			reservation.adultTickets = in.adultTickets;
			reservation.concessionTickets = in.concessionTickets;
			reservation.carClass = in.carClass;
			reservation.originStation = in.originStation;
			reservation.destinationStation = in.destinationStation;
			return true;
		}
	}

	return false;
}

void displayReservations(Train southboundTimetable[100],
	Train northboundTimetable[100], Reservation reservation) {

	int southnum = 0, northnum = 0;

	loadSouthboundTimetable(southboundTimetable, southnum);
	loadNorthboundTimetable(northboundTimetable, northnum);

	char stations[13][12] = { "","Nangang","Taipei" ,"Banqiao","Taoyuan","Hsinchu","Miaoli","Taichung",
						"Changhua","Yunlin","Chiayi","Tainan","Zuoying" };
	char carclass[12] = {};

	if (reservation.carClass == 1)
		strcpy_s(carclass, "Standard");
	else if (reservation.carClass == 2)
		strcpy_s(carclass, "Business");	

	cout << endl;
	if (reservation.originStation < reservation.destinationStation)
		display(reservation, southboundTimetable, stations, carclass);
	else
		display(reservation, northboundTimetable, stations, carclass);
}

void reduceSeats(fstream& ioFile, Train southboundTimetable[100],
	Train northboundTimetable[100], Reservation& reservation) {

	int adult = 0, concession = 0, i = 0;

	cout << "How many adult tickets to cancell? ";
	do ;
	while ((adult = inputAnInteger(0, reservation.adultTickets)) == -1);
	cout << "\nHow many concession tickets to cancell? ";
	do ;
	while ((concession = inputAnInteger(0, reservation.concessionTickets)) == -1);

	reservation.adultTickets -= adult;
	reservation.concessionTickets -= concession;

	displayReservations(southboundTimetable, northboundTimetable, reservation);

	cout << "\n\nYou have seccessfully reduced the number of tickets!" << endl;

	ioFile.seekg(0, ios::end);
	int n = ioFile.tellg();
	ioFile.seekg(0, ios::beg);

	for (i = 0; i < n; i += sizeof(Reservation)) {
		Reservation in;
		ioFile.seekp(i, ios::beg);
		ioFile.read(reinterpret_cast<char*>(&in), sizeof(Reservation));
		if (strcmp(reservation.idNumber, in.idNumber) == 0 && strcmp(reservation.reservationNumber, in.reservationNumber) == 0) {
			break;
		}
	}

	if (!ioFile) {
		cout << "File could not be opened!" << endl;
		system("Pause");
		exit(1);
	}

	ioFile.seekg(i, ios::beg);

	if (reservation.adultTickets != 0 && reservation.concessionTickets != 0)
		ioFile.write(reinterpret_cast<const char*>(&reservation), sizeof(Reservation));
	else {
		Reservation out;
		ioFile.write(reinterpret_cast<const char*>(&out), sizeof(Reservation));
	}
}