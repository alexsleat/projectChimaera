#include <stdio.h>
#include <stdlib.h>

#include <string>
// writing on a text file
#include <iostream>
#include <fstream>

#include "ros/ros.h"
#include "std_msgs/UInt32.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"
#include "std_msgs/String.h"

void drawLine(int val, int minval, int maxval);

void pilotHeading_cb(const std_msgs::Float32::ConstPtr& sub);
void compassHeading_cb(const std_msgs::Float32::ConstPtr& sub);
void pidRampYawLeft_cb(const std_msgs::UInt32::ConstPtr& sub);
void pidRampYawRight_cb(const std_msgs::UInt32::ConstPtr& sub);
void pilotDepth_cb(const std_msgs::Float32::ConstPtr& sub);
void svpDepth_cb(const std_msgs::Float32::ConstPtr& sub);
void pidRampDepthLeft_cb(const std_msgs::UInt32::ConstPtr& sub);
void pidRampDepthRight_cb(const std_msgs::UInt32::ConstPtr& sub);
void pilotPitch_cb(const std_msgs::Float32::ConstPtr& sub);
void compassPitch_cb(const std_msgs::Float32::ConstPtr& sub);
void pidRampPitch_cb(const std_msgs::UInt32::ConstPtr& sub);
void pilotRoll_cb(const std_msgs::Float32::ConstPtr& sub);	
void compassRoll_cb(const std_msgs::Float32::ConstPtr& sub);

int x, y;
float z;
char aa[100];

int 	pH, cH, 	//pilot & compass heading
	myL, myR,	//motor yaw left and right
	pD, sD,		//pilot & svp depth
	mdL, mdR,	//motor depth left & right
	pP, cP,		//pilot & compass pitch
	mp,		//motor pitch
	pR, cR;		//pilot & compass roll

using namespace std;

int main(int argc, char **argv)
{
	//Get start time, to take off from current time
	time_t startTime; 
	startTime=time(NULL);
	
	ros::init(argc, argv, "logger");
	
	ros::NodeHandle n;	
	
	//Set up subscriptions
	ros::Subscriber sub1 = n.subscribe("pilotHeading", 100, pilotHeading_cb);
	ros::Subscriber sub2 = n.subscribe("pilotPitch", 100, pilotPitch_cb);
	ros::Subscriber sub3 = n.subscribe("pilotRoll", 100, pilotRoll_cb);
	ros::Subscriber sub4 = n.subscribe("pilotDepth", 100, pilotDepth_cb);
	
	//Sensors
	ros::Subscriber sub5 = n.subscribe("svpDepth", 100, svpDepth_cb);
	ros::Subscriber sub6 = n.subscribe("compassHeading", 100, compassHeading_cb);
	ros::Subscriber sub7 = n.subscribe("compassPitch", 100, compassPitch_cb);
	ros::Subscriber sub8 = n.subscribe("compassRoll", 100, compassRoll_cb);
	
	//Motors
	ros::Subscriber sub9 = n.subscribe("pidRampDepthLeft", 100, pidRampDepthLeft_cb);
	ros::Subscriber sub10 = n.subscribe("pidRampDepthRight", 100, pidRampDepthRight_cb);
	ros::Subscriber sub11 = n.subscribe("pidRampPitch", 100, pidRampPitch_cb);
	ros::Subscriber sub12 = n.subscribe("pidRampYawLeft", 100, pidRampYawLeft_cb);
	ros::Subscriber sub13 = n.subscribe("pidRampYawRight", 100, pidRampYawRight_cb);	
	

	ros::spinOnce();
	//Set loop rate (in Hz);
	ros::Rate r(80);
	while (ros::ok())
	{

		//Check for new data:
		ros::spinOnce();
		system("clear");	//clear terminal, keep everything in the right place.
		
		//heading
		printf("compassHeading:\t");
		drawLine(cH, 0, 360);
		printf("pilotHeading:\t");
		drawLine(pH, 0, 360);
		//heading motors
		printf("Yaw Left:\t");
		drawLine(myL, 0, 100);
		printf("Yaw Right:\t");
		drawLine(myR, 0, 100);
		
		printf("\n");
		
		//depth
		printf("svpDepth:\t");
		drawLine(sD, -10, 0);
		printf("pilotDepth:\t");
		drawLine(pD, -10, 0);
		//depth motors
		printf("Depth Left:\t");
		drawLine(mdL, 0, 100);
		printf("Depth Right:\t");
		drawLine(mdR, 0, 100);		
		r.sleep();

		printf("\n");

		//pitch
		printf("compassPitch:\t");
		drawLine(cP, 0, 180);
		printf("pilotPitch:\t");
		drawLine(pP, 0, 180);
		//pitch motors
		printf("Pitch:\t\t");
		drawLine(mp, 0, 100);
		
		printf("pilotRoll:\t");
		drawLine(pR, 0, 180);
		printf("compassRoll:\t");
		drawLine(cR, 0, 180);		

		printf("\n\n\tHeading: ");		
	
		if(myL > myR)
			printf("go left.\n");
		else if(myL < myR)
			printf("go right.\n");
		else
			printf("hold.\n");
			
		
		printf("\n\tPitch: ");
		
		if((mdL + mdR / 2) > mp)
			printf("front down.\n");
		else if((mdL + mdR / 2) < mp)
			printf("front up.\n");
		else
			printf("hold.\n");	
			
		
		
		printf("\n\tDepth: ");
		
		if((mdL + mdR) / 2 > 55)
			printf("go down.\n");
		else if((mdL + mdR) / 2 < 45)
			printf("go up.\n");
		else
			printf("hold.\n");		
		

		printf("\n\tRoll: ");
		
		if(mdL > mdR)
			printf("left up.\n");
		else if(mdL < mdR)
			printf("right up.\n");
		else
			printf("hold.\n");	
		
		r.sleep();	
	}
	
}

/*************************************************
** draw a line with the value in the right place
*************************************************/

void drawLine(int val, int minval, int maxval)
{
int i;
float tempval;
	maxval = maxval - minval;
	tempval = (float(val) / float(maxval)) * 100.0;
	val = int(tempval);
	
	if(val >= 100)
		val = 100;
	
	for(i = 0; i <= 100; i ++)
	{
		if(i != val)
			printf("-");
		else
			printf("#");
	}
	
	printf("\n");
}

/*************************************************
** Returns the pilotHeading 
*************************************************/

void pilotHeading_cb(const std_msgs::Float32::ConstPtr& sub)
{
	pH = int(sub->data);
	return;
}
/*************************************************
** Returns the compassHeading 
*************************************************/

void compassHeading_cb(const std_msgs::Float32::ConstPtr& sub)
{
float tempcH;
	tempcH = sub->data;
	if(tempcH < 0)
		tempcH = tempcH + 360;	
	cH = int(tempcH);
	return;
}
/*************************************************
** Returns the left motor 
*************************************************/

void pidRampYawLeft_cb(const std_msgs::UInt32::ConstPtr& sub)
{
	myL = int(sub->data);
	myL = myL / 10;
	myL = myL - 100;
	return;
}
/*************************************************
** Returns the right motor 
*************************************************/

void pidRampYawRight_cb(const std_msgs::UInt32::ConstPtr& sub)
{
	myR = int(sub->data);
	myR = myR / 10;
	myR = myR - 100;
	return;
}

/*************************************************
** Returns the pilotDepth
*************************************************/
void pilotDepth_cb(const std_msgs::Float32::ConstPtr& sub)
{
	pD = int(sub->data * -1);
	
	return;
}
/*************************************************
** Returns the svp depth
*************************************************/

void svpDepth_cb(const std_msgs::Float32::ConstPtr& sub)
{
	sD = int(sub->data * -1);
	return;
}
/*************************************************
** Returns the depth left motor 
*************************************************/

void pidRampDepthLeft_cb(const std_msgs::UInt32::ConstPtr& sub)
{
	mdL = int(sub->data);
	mdL = mdL / 10;
	mdL = mdL - 100;
	return;
}
/*************************************************
** Returns the depth right motor 
*************************************************/

void pidRampDepthRight_cb(const std_msgs::UInt32::ConstPtr& sub)
{
	mdR = int(sub->data);
	mdR = mdR / 10;
	mdR = mdR - 100;
	return;
}
/*************************************************
** Returns the pilotPitch
*************************************************/

void pilotPitch_cb(const std_msgs::Float32::ConstPtr& sub)
{
	pP = int(sub->data);
	return;
}
/*************************************************
** Returns the compassPitch
*************************************************/

void compassPitch_cb(const std_msgs::Float32::ConstPtr& sub)
{
float tempcP;
	tempcP = int(sub->data);
	//if(tempcP < 0)
		tempcP = tempcP + 90;
	cP = int(tempcP);
	return;
}
/*************************************************
** Returns the pitch motor 
*************************************************/

void pidRampPitch_cb(const std_msgs::UInt32::ConstPtr& sub)
{
	mp = int(sub->data);
	mp = mp / 10;
	mp = mp - 100;
	return;
}
/*************************************************
** Returns the pilotRoll
*************************************************/

void pilotRoll_cb(const std_msgs::Float32::ConstPtr& sub)
{
	pR = int(sub->data);
	return;
}
/*************************************************
** Returns the compassRoll 
*************************************************/

void compassRoll_cb(const std_msgs::Float32::ConstPtr& sub)
{
float tempcR;
	tempcR = int(sub->data);
	//if(tempcR < 0)
	//	tempcR = tempcR * -1;
	cR = int(tempcR) + 90;
	return;
}

