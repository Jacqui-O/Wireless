//Mobile 2 state machine; Callee from Austin Texas

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//listens for communication from base station 2
int main(){
	int ring = 0;

	int incomingCall, pickup, hangUp;

	cout << "To initiate a call press 1. Otherwise press 0. Then press ENTER: " << endl; //incoming call
	cin >> incomingCall;
	cout << endl;
//translate message from BS2 to incomingCall
	if(incomingCall == 1){		//A call is received
		for (ring =0; ring < 5; ring++){
	
			cout << "To pickup the call press 1. Otherwise, press 0. Then press ENTER: " << endl;  //pickup
			cin >> pickup;

			if (pickup == 1){	//User picks up
				cout << "Connected" << endl;
				cout << "To hangup the call press 1. Otherwise, press 0. Then press ENTER: " << endl;
				cin >> hangUp;

				while(hangUp !=1){	//User hangs up
					cout << "Still connected. " << endl;
					cout << "To hangup the call press 1. Otherwise, press 0. Then press ENTER: " << endl;
					cin >> hangUp;
				}//end while

				cout << "Disconnected" << endl;
				return 0;
			} //end if pickup		
	}//end for loop

		if (ring == 5){	//After 5 rings with no pickup, go to voicemail and disconnect
			cout << "Stop Ringing. Go to Voice Mail. Disconnect" << endl;
		}
	}//end if incoming call
	else
		cout << "No incoming calls" << endl; //No incoming calls

return 0;

}