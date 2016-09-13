//Base station 2
// MS2 is the callee from Austin
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
//listens for communication from base station 1
//send values from bs1 to here
int main(){
	int BS1, MS2, distance, quit;

	bool loop = true;
	while(loop){

	cout << "Do you want to quit? 1 for YES. 0 for NO. Then press ENTER." << endl;
	cin >> quit;
	if(quit == 1){
		loop = false;
	}
	else{
		cout << "Ready State" << endl;
		cout << "Is a call being received from the BS1? 1 for YES. 0 for NO. Then press ENTER." << endl;
		cin >> BS1;
		//pass bs1 message to bs1 variable
		if(BS1 == 1){		//Base station 2 receives call from BS1 and forwards to MS2
			cout << "Forward to MS2" << endl;
			//send message to ms2
			}
		else{
					cout << "No incoming calls from BS1" << endl;
				//start listening again			
		}
	}
}//end while loop

return 0;
}