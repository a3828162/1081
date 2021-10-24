/*return-value-type function-name( parameter-list )
{
 declarations and statements
}*/

#include <iostream>
#include <iomanip>
using namespace std;
double calculateCharge( double hours){
	
	double charge=0;
	if( hours>24.0){ 
		double l;      
		for( double i=hours; i>24.0;i-24.0){
			charge += 15.0;
			l = i;
		}
		hours = l;
	}
	if( hours>0 && hours<=2.0){          //determine hours
		charge += 3.0;		// less than two hours cost 3$
	}else if(hours>2.0 && hours<=22.0){
		charge += 3.0;
		for( double i=hours; i>2.0; i-=1.0){  //one hour add 0.6$
			charge += 0.6;
		}
	}else if(hours>22 && hours<=24){
		charge += 15.0;			//one day maximun
	} 
	
	return charge;   //return charge value to main function
}

int main(){
	
	double hours[4], charge[4];
	double totalhours, totalcharge;
	cout << "Input cars parking hours(1~3):";
	for( int i=1; i<4; i++){
		cin >> hours[i];
		totalhours += hours[i];			//calculate total
		charge[i] = calculateCharge( hours[i]);  //use calculateCharge function to get value 
		totalcharge += charge[i];
	}	
	cout << "\nCar    Hours    Charge\n";
	for( int i=1; i<4; i++){
		cout << left << i;        //output value
		cout << setprecision(1) << fixed << setw(11) << right << hours[i];
		cout << setprecision(2) << fixed << setw(10) << right << charge[i];
		cout << endl;
	}
	
	cout << "Total" << setprecision(1) << fixed << setw(7) << right << totalhours 
		<< setprecision(2) << fixed << setw(10)  << right << totalcharge;
}


