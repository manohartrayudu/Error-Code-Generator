/*
 * h.cpp
 *
 *  Created on: 18-Oct-2021
 *      Author: Gaganmanohar-T
 */
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <winsock2.h>
#include<ctime>


using namespace std;


int convert(string s);

int split(string str){

	int error_code=0;
	int num;

	string s1 = "";
	string s2 = "";
	string s3 = "";
	string s4 = "";


	int temp=0;

	for(int i=0; i<100 && str[i] != ',';i++){
		s1 = s1 + str[i];
		temp = i;
	}

	// cout << "\nTemp is : "<<temp;


	for(int j=temp+2;j<100 && str[j] != ',';j++){
		s2 = s2 + str[j];
		temp =j;
	}

	// cout << "\nTempJ is : "<<temp;

	for(int k=temp+2;k<100 && str[k] != ',';k++){
		s3 = s3 + str[k];
		temp = k;

	}

	// cout << "\nTempK is : "<<temp;

	for(int p=temp+2;p<100 && str[p] != ',';p++){
		if(str[p]=='\0'){
			break;
		}else{
			s4 = s4 + str[p];
			//temp = p;

		}

	}

	cout<<"\nevent       : "<<s1 <<'\n';
	cout<<"criticality : "<<s2 <<'\n';
	cout<<"code   	    : "<<s3 <<'\n';
	cout<<"sensor      : "<<s4 <<'\n';


	//events
	if(s1 == "M-event"){
		error_code = error_code | 0x00000001;
	}else if(s1 == "I-event"){
		error_code = error_code | 0x00000002;
	}else if(s1 == "R-event"){
		error_code = error_code | 0x00000004;
	}

	//criticality
	if(s2 == "All_well"){
		error_code = error_code | (0x00000000<<4);
	}else if(s2 == "Major"){
		error_code = error_code | (0x00000001<<4);
	}else if(s2 == "Hazardous"){
		error_code = error_code | (0x00000002<<4);
	}else if(s2 == "Catastrophic"){
		error_code = error_code | (0x00000003<<4);
	}


	//converting code string to integer
	num = convert(s3);
	//cout << num << '\n';
	//std::cout << "0x"<<std::hex<< num << '\n';


	//code
	error_code = error_code | (num<<8);

	//sensor
	if(s4=="ADU"){
		error_code = error_code | (0x00000001<<28);
	}
	else if(s4=="AHRS"){
		error_code = error_code | (0x00000002<<28);
	}
	else if(s4=="GPS"){
		error_code = error_code | (0x00000003<<28);
	}
	else if(s4=="ELEVATOR"){
		error_code = error_code | (0x00000004<<28);
	}
	else if(s4=="AILERON"){
		error_code = error_code | (0x00000005<<28);
	}
	else if(s4=="RUDDER"){
		error_code = error_code | (0x00000006<<28);
	}
	else if(s4=="MSAP"){
		error_code = error_code | (0x00000007<<28);
	}
	else if(s4=="EMS"){
		error_code = error_code | (0x00000008<<28);
	}
	else if(s4=="ADAHRS"){
		error_code = error_code | (0x00000009<<28);
	}



	//final output


	return error_code;

}



int convert(string s)
{
	// Initialize a variable
	int num = 0;
	int n = s.length();

	// Iterate till length of the string
	for (int i = 0; i < n; i++){

		num = num * 10 + (int(s[i]) - 48);
	}
	return num;
}


int main(int argc, char **argv) {

	string arr[50];
	string str;

	str.assign((const char*)&argv[1][0]);
	cout<<str<<endl;

	int err_number = split(str);
	cout<<"\nerror-code  :"<<"0x"<<std::hex << err_number<<"\n";



	fstream myfile;

	myfile.open("error_code_input.txt",ios::out);

	if(myfile)
	{
		//cout<<"0x"<<std::hex << err_number;
		myfile << "0x" ;
		myfile<<std::hex << err_number;
		myfile.close();
	}
	else
	{
		cout << "unable to ************* open the file";
	}

	//Sleep(100);


	return err_number;
}















