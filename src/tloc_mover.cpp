#include <vector>
#include <math.h>
#include <string>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h" 
#include "nav_msgs/Odometry.h"

using std::vector;
using std::string;

class TurtleMover {
	public:
	TurtleMover(const ros::Publisher& mover_pub): mover_pub_(mover_pub){}

	void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
		double x = msg->pose.pose.position.x;
		double y = msg->pose.pose.position.y;
		double xx = 0.0;
		double zz = 0.0;
		ROS_INFO("x: %f, y: %f", x, y);
		geometry_msgs::Twist mr = Moverpub(xx , zz);
		mover_pub_.publish(mr);
}

	private:
	ros::Publisher mover_pub_;
	
	geometry_msgs::Twist Moverpub(double xx, double rz){
		geometry_msgs::Twist move;
		move.linear.x = 0.5;
		move.angular.z = 0.5;

		return move;
	}

};

int main(int argc, char** argv){
	ros::init(argc, argv, "turtle_mover");
	ros::NodeHandle nh;
	ros::Publisher mover_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
	TurtleMover mover(mover_pub);
	ros::Subscriber sub = nh.subscribe("/odom", 10, &TurtleMover::OdomCallback, &mover);
	ros::spin();

	return 0;

}


	
