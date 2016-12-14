/*
input flags:
-n number of runs
-i input binary + binary args

*/

#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <time.h>
#include <sstream>
#include <sys/time.h>
#include <unistd.h> 
using namespace std;

// Define Classes
#include "RunningStats.h"
// Prototype Functions
int stoi( string input);
char *getcwd(char *buf, size_t size);
// Main Function
int main(int argc, char *argv[])
{
char cwd[1024];
getcwd(cwd, sizeof(cwd));
cout<<"cwd "<<cwd<<endl;


if (argc<3){
	cout<<"Error: Too few arguments!"<<endl;
	exit(0);
}

//number of trials - default 3
int n = stoi(argv[1]);
if (n<3){
	cout<<"Warning: number of cycles less than 3!"<<endl;
	cout<<"Resetting to 3"<<endl;
	n=3;
}
// input binary
string ibin = argv[2];

string ibinarg = "--NONE";
bool ibinargflag = 0;
// input binary args
for (int i = 3; i < argc; ++i)
{
	if(!ibinargflag){
		ibinarg=argv[i];
		ibinargflag=1;
	}
	else{
		ibinarg+=" ";	
		ibinarg+=argv[i];
	}
}

//determine input for system function
string sysin;
if (ibinarg=="--NONE"){
	sysin=ibin;
}
else{
	sysin=ibin+" "+ibinarg;
}

//Initialize the running stat object
RunningStats Timer;
cout<<"sysin "<<sysin<<endl;
cout<<setiosflags(ios::fixed) << setprecision(5);
int run;
timeval tv;
timeval start_tv;




for (int i = 0; i < n; ++i)
{
	//start time for benchmark	 
//	clock_t startTime = clock();
//	cout<<"startTime: "<<startTime<<endl;
	gettimeofday(&start_tv, NULL);
	run=system(sysin.c_str());
	gettimeofday(&tv, NULL);
	// to compute its execution duration in runtime
	// sampling execution time in seconds
	//clock_t finishTime = clock();
	//cout<<"finishTime "<<finishTime<<endl;
	//long double tsec= (long double)( finishTime - startTime ) / (long double)(CLOCKS_PER_SEC);
	long double tsec = (tv.tv_sec - start_tv.tv_sec) + (tv.tv_usec - start_tv.tv_usec) / 1000000.0;
	//cout<<"tsec "<<tsec<<endl;
	Timer.Push(tsec);
}
cout<<"For "<<n<<" cycles the average run time is: "<<Timer.Mean()<<" with std dev: "<<Timer.StandDev()<<endl;
//cout<<"ibin "<<ibin<<" ibinarg "<<ibinarg<<endl;
return EXIT_SUCCESS;

}

// Define Functions
int stoi( string input){
	
	int numb;
	istringstream ( input ) >> numb;
	return(numb);
}
