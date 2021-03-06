#include <math.h>
#include <stdio.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"

#include "depthMod.h"

int main(int argc, char **argv){

	ros::init(argc, argv, "depthMod");

	/* Messages and Services */

	ros::NodeHandle depthModN;

	/* Publish */

	//ros::Publisher backMsg = depthModN.advertise<std_msgs::Float32>("backRate", 100);
	ros::Publisher depthRMsg = depthModN.advertise<std_msgs::Float32>("depthRRate", 100);
	ros::Publisher depthLMsg = depthModN.advertise<std_msgs::Float32>("depthLRate", 100);

	std_msgs::Float32 depthRRate;
	std_msgs::Float32 depthLRate;

	/* Subscribe */

	ros::Subscriber sub1 = depthModN.subscribe("depthDRate", 100, depthCallback);
	ros::Subscriber sub2 = depthModN.subscribe("depthPRate", 100, pitchCallback);
	
	ros::Rate loop_rate(10);

	while(ros::ok()){

		depthChange = 0;	//clear depth flag
		ros::spinOnce();

		if(depthChange){
			depthRatePitch *= PITCHP;			//reduce power for pitch
			depthRRate.data = depthRatePitch + depthRateDepth;	//combine values
			depthLRate.data = depthRatePitch + depthRateDepth;
		}
		else{
			depthRRate.data = depthRatePitch;
			depthLRate.data = depthRatePitch;
		}

		depthRMsg.publish(depthRRate);
		depthLMsg.publish(depthLRate);

		loop_rate.sleep();

	}

	printf("Shutting Down\n");

	return 0;
}

/*************************************************
** Get what the depth is doing to the motor	**
*************************************************/

void depthCallback(const std_msgs::Float32::ConstPtr& depthDRate){
	depthRateDepth = depthDRate->data;
	depthRateDepth *= DEPTHP;	//power attributed to depth
	depthChange = 1;		//raise depth flag
	return;
}

/*************************************************
** Get what the pitch is doing to the motor	**
*************************************************/

void pitchCallback(const std_msgs::Float32::ConstPtr& depthPRate){
	depthRatePitch = depthPRate->data;
	return;
}

