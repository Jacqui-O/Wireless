//Mobile 1 state machine; Caller from Dallas Texas

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//send communication to base station
// This code may make more sense in the BS2; Receive the busy message and relay back to MS1

int main(){
	int call, ms2Busy, ms2Unavailable, forward, networkBusy, ms2Off, available, pickUp, ring, hangUp, quit, i=1;
	
	bool loop = true;
while(loop){
	
	cout << "Do you want to quit? 1 for YES. 0 for NO. Then press ENTER." << endl;
	cin >> quit;
	if(quit == 1){
		loop = false;
	}
	else{

		cout << "Ready state." << endl;
		cout << "Do you want to make a call? 1 for YES. 0 for NO. Then press ENTER." << endl;
		cin >> call;

		if(call != 1){
			cout << "No call made" << endl;
		}
		else{

			cout << "Is the MS2 Busy? 1 for YES. 0 for NO. Then press ENTER. " << endl;
			cin >> ms2Busy;

			if(ms2Busy == 1){  //line is busy
			cout << "MS Busy. Busy Tone." << endl;
			//go back to ready state, want to dial again?
			}
		
			else {
				cout << "Is the MS unavailable? 1 for YES. 0 for NO. Then press ENTER." << endl;
				cin >> ms2Unavailable;

				if (ms2Unavailable == 1){ //Out of range
					cout << "MS unavailable. Call Dropped." << endl;
					//go back to ready state, want to dial again?
				}
				else{
					cout << "Is the call forwarded? 1 for YES. 0 for NO. Then press ENTER." << endl;
					cin >> forward;

					if (forward == 1){ //call forward
						cout << "Forward Call." << endl;
						//go back to ready state, want to dial again?	
					}	
					else{
						cout << "Is the network busy? 1 for YES. 0 for NO. Then press ENTER." << endl;
						cin >> networkBusy;
	
						if (networkBusy == 1){ // network is busy
							cout << "Network Busy." << endl;
								if(i<4){
									cout << "Attempt" << i << endl;
									sleep(3);
									i++;
									//cout << "Is the network still busy? 1 for YES. 0 for NO. Then press ENTER." << endl;
									//cin >> open;
										//if (open == 0){ //network clear
											//exit. go to next else statement}
								}
							//cout << "Giving Up. Back to the top."
							//try 3 times before giving up
						}
						else{ 
							cout << "Is the MS2 turned off? 1 for YES. 0 for NO. Then press ENTER." << endl;
							cin >> ms2Off;
	
							if (ms2Off == 1){ //ms2 is off
								cout << "MS is off. Go to Voice Mail." << endl;
								//go back to ready state, want to dial again?
							}
							else{
								cout << "Is the line available? 1 for YES. 0 for NO. Then press ENTER." << endl;
								cin >> available;
									if (available == 1){
									for (ring=0; ring < 5; ring++){

										cout << "Will the callee answer your call? 1 for YES. 0 for NO. Then press ENTER" << endl;
										cin >> pickUp;
										if (pickUp == 1){
											cout << "Connected" << endl;
											cout << "To hangup the call press 1. Otherwise, press 0. Then press ENTER: " << endl;
											cin >> hangUp;

												while(hangUp !=1){	//User hangs up
													cout << "Still connected. " << endl;
													cout << "To hangup the call press 1. Otherwise, press 0. Then press ENTER: " << endl;
													cin >> hangUp;
												}//end while

											cout << "Disconnected" << endl;
											break; //break out of for loop 
											//go back to ready state, want to dial again?
											
										}//end if pickup
									}//end for
									if (ring == 5){
										cout << "Stop Ringing. Go to Voice Mail. Disconnect" << endl;
										//go back to ready state, want to dial again?
									}
								}//end if available
							}
						}
					}
				}
			}
		}
	
	}//end if make a call
	
}//end while
return 0;

}
