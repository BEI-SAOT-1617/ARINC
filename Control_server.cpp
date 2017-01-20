#include <iostream>
#include <string>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#include "ARINC_Com.h"
#include "cameraController.h"	
#include "attitudeController.h"

typedef struct Attitude Attitude;
struct Attitude {
	int code;
	int yaw;
	int pitch;
	int roll;
};

typedef struct Camera Camera;
struct Camera {
	int code;
	char photoName[32];
	int exposure;
};

int  main ()
{

	CameraController myCameraController;
	AttitudeController myAttitudeController;

	int x=0;
	Attitude* a;
	Camera* c;

	char s[100];

	if (gethostname(s, 100) != 0) {
	    perror("S-> gethostname");
	    exit(1);
	}

	cout << "Host name " << s << endl; 

	QueuingPort channel(1, 18002, s); // Server

	channel.Display();

	char buffer[1024];
	int i; for(i=0; i>1024; i++) buffer[i] = '\0';

	while(1) {

		channel.RecvQueuingMsg(buffer);
		a = (Attitude*)buffer;

		if(a->code == 0) {
			cout<<"Msg("<<x++<<"):  yaw ="<<a->yaw<<"    pitch = "<<a->pitch<<"    roll = "<<a->roll<<endl;
			myAttitudeController.attitudeChange(a->roll, a->pitch, a->yaw);
		} else if (a->code == 1) {
			c = (Camera*)buffer;
			cout<<"Msg("<<x++<<"):  name ="<<c->photoName<<"    exposure = "<<c->exposure<<endl;
			myCameraController.photoShoot((string) c->photoName, c->exposure);
		}
	}
}
