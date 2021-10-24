#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double ConvertToCelsius( double lb);
double ConvertToFahrenheit( double lb);

int main(){
	
	int conversion = 0;
	double lb = 0, ub = 0;
	cout << "Please choose which conversion you want to use:\n1.Celsius to Fahrenheit\n2. Fahrenheit to Celsius\n";
	cin >> conversion;    //choose your conversion
	cout << "Please input the lower bond and upper bond of the temperature you want to convert:\nlower bond:";
	cin >> lb;  // set lower bond value
	cout << "upper bond:";  // set upper bond value
	cin >> ub;
	
	if(conversion == 1){
		cout << setw(10) << "Celsius" << setw(15) << "Fahrenheit" << setw(10) << "Celsius" << setw(15) << "Fahrenheit" << endl;
		int a = 0, b = 0;
		a = (ub + lb)/2 + 1; // set Median 'a'
		b = (ub - lb)/2 + 1; // set Full Distance/2 'b'
		for( double i = lb; i<a; i++){ 
			cout << setw(10) << setprecision(1) << fixed << i << setw(15) << setprecision(1) << fixed << ConvertToCelsius( i); // output value
			if( i+1 == a )   // avoid output ub+1
				break;
			cout << setw(10) << setprecision(1) << fixed << i+b << setw(15) << setprecision(1) << fixed << ConvertToCelsius( i+b) << endl;
		}
	}else{
		cout << setw(10) << "Fahrenheit" << setw(15) << "Celsius" << setw(10) << "Fahrenheit" << setw(15) << "Celsius" << endl;
		int a = 0, b = 0;
		a = (ub + lb)/2 + 1;
		b = (ub - lb)/2 + 1;
		for( double i = lb; i<a; i++){
			cout << setw(10) << setprecision(1) << fixed << i << setw(15) << setprecision(1) << fixed << ConvertToFahrenheit( i);
			if( i+1 == a )
				break;
			cout << setw(10) << setprecision(1) << fixed << i+b << setw(15) << setprecision(1) << fixed << ConvertToFahrenheit( i+b) << endl;
		}		
	}
	
} 

double ConvertToCelsius( double lb){
	double n;
	n = lb*9/5+32;  //Convert Fahrenheit to Celsius
	return n;
}

double ConvertToFahrenheit(double lb){
	double n;
	n = (lb-32)*5/9;  //Convert Celsius to Fahrenheit
	return n;	
}
