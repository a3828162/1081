#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	
	int gender, age;
	int mass, activity, BMR, TDEE;
	float heightm,height;
	float BMI;
	
	cout << "Input Gender(Male:1/Female:2):";
	cin >> gender;
	cout << "Input Age(year):";
	cin >> age;
	cout << "Input mass(kg):";
	cin >> mass;
	cout << "Input height(cm):";
	cin >> height;
	cout << "Activity List1. Sedentary(office job)\n2. Light Exercise(1-2 days/week)\n3. Moderate Exercise(3-5 days/week)\n4. Heavy Exercise(6-7 days/week)\n5. Athlete(2x per day)\nInput Activity:";
	cin >> activity;
	
	if(gender==1)
		cout << "Gender: Male" << endl;
	else
		cout << "Gender: Female" << endl;
	
	cout << "Age(year):" << age << endl;
	cout << "Mass(kg):" << mass << endl;
	cout << "Height(cm):" << height << endl;	
	
	heightm = height/100;
	BMI = mass/(heightm*heightm);
	cout << "BMI:" << setprecision(3) << fixed << BMI << endl;
	if(BMI<18.5)
		cout << "You are Underweight" << endl;
	else if(BMI<24)
		cout << "You are Normal" << endl;
	else if(BMI<27)
		cout << "You are Overweight" << endl;
	else if(BMI<30)
		cout << "You are Moderately obese" << endl;
	else if(BMI<35)
		cout << "You are Severely obese" << endl;
	else
		cout << "You are Very severely obese" << endl;
	
	if(gender==1)
		BMR = 10*mass+6.25*height-5*age+5;
	else
		BMR = 10*mass+6.25*height-5*age-161;
		
	if(activity==1){
		TDEE = BMR*1.2;
		cout << "BMR:" << BMR << endl; 
		cout << "You are Sedentary" << endl;
		cout << "TDEE:" << TDEE << endl;
	}else if(activity==2){
		TDEE = BMR*1.375;
		cout << "BMR:" << BMR << endl; 
		cout << "You are  Light Exercise" << endl;
		cout << "TDEE:" << TDEE << endl;		
	}else if(activity==3){
		TDEE = BMR*1.55;
		cout << "BMR:" << BMR << endl; 
		cout << "You are  Moderate Exercise" << endl;
		cout << "TDEE:" << TDEE << endl;			
	}else if(activity==4){
		TDEE = BMR*1.725;
		cout << "BMR:" << BMR << endl; 
		cout << "You are  Heavy Exercise" << endl;
		cout << "TDEE:" << TDEE << endl;			
	}else if(activity==5){
		TDEE = BMR*1.9;
		cout << "BMR:" << BMR << endl; 
		cout << "You are  Heavy Athlete" << endl;
		cout << "TDEE:" << TDEE << endl;					
	}
	
	cout << endl;
	
	return 0;
	
}
