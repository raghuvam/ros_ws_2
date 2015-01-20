#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <stdlib.h>

int main (int argc, char **argv) {
        ros::init(argc, argv, "trigger");
        ros::NodeHandle nh;

        ros::Publisher pub = nh.advertise<std_msgs::Bool>("avp_streamcam/trigger_cmd", 1000);

        std_msgs::Bool msg;
        msg.data = 1;

	char cmd[50];

        while(ros::ok()) {
		std::cin.getline(cmd, 50);
                pub.publish(msg);

                ROS_INFO_STREAM("Sending command to capture raw image");

        }
}
