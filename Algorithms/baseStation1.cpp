//Base Station 1
// MS1 is the caller from Dallas
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(){
	int MS1, distance, quit;
// have listening loop forever; listening for communication from mobile 1
	bool loop = true;
	while(loop){

	cout << "Do you want to quit? 1 for YES. 0 for NO. Then press ENTER." << endl;
	cin >> quit;
	if(quit == 1){
		loop = false;
	}
	else{
		cout << "Ready State" << endl;	
		cout << "Is a call being received from the MS1? 1 for YES. 0 for NO. Then press ENTER." << endl;
		cin >> MS1;

			if (MS1 == 1){ 		//Base Station 1 receives call from MS1 and forwards the BS2
				cout << "Forward to BS2" << endl;
				//connect to BS2 here
				}
			else{
					cout << "No incoming calls from MS" << endl;
					cout << "Is the distance betweent the MS and this BS reaching the threshold? 1 for YES. 0 for NO. Then press ENTER." << endl;
					cin >> distance;

		/*			if(distance == 1){
						cout << "Hanover to another BS." << endl;
					}
					else{
						cout << "No handover" << endl;}*/
			}
		}
}//end while loop

return 0;
}
