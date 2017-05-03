#include<iostream>
#include<math.h>
#include<actionlib/server/simple_action_server.h>
#include<actionlib_tutorials/waypointAction.h>
#include<geometry_msgs/Twist.h>
#include<turtlesim/Pose.h>
ros::Publisher vel_pub;
ros::Subscriber pose_sub;
turtlesim::Pose turtle_pose;
void poseCallback(const turtlesim::Pose::ConstPtr & pose_message);
double getDistance(double x1,double y1,double x2, double y2);

class waypointAction{
protected:
  ros::NodeHandle nh;
  actionlib::SimpleActionServer<actionlib_tutorials::waypointAction> as;/////
  std::string action_name;
  actionlib_tutorials::waypointFeedback feedback;
  actionlib_tutorials::waypointResult result;

public:
  waypointAction(std::string name):
    as(nh, name, boost::bind(&waypointAction::executeCB, this, _1), false),
    action_name(name){
      as.start();
      pose_sub = nh.subscribe("/turtle1/pose", 10, poseCallback);
      vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    }

    ~waypointAction(void){}

    void executeCB(const actionlib_tutorials::waypointGoalConstPtr &goal){
      ros::Rate r(10);
      //bool success = true;
      //feedback.curr_Pose_x = turtle_pose.x;
      //feedback.curr_Pose_y = turtle_pose.y;
      //feedback.goal.push_back(0);
      ROS_INFO("%s: Executing:", action_name.c_str());
      geometry_msgs::Twist vel_msg;
      double linear_error;
	    double old_linear_error=0;//,acc_error=0;
      double angular_error;
      double old_angular_error=0;
      while(getDistance(turtle_pose.x, turtle_pose.y, goal->goal_Pose_x, goal->goal_Pose_y) > 0.1){
        linear_error = getDistance(turtle_pose.x, turtle_pose.y, goal->goal_Pose_x, goal->goal_Pose_y);
        angular_error = atan2((goal->goal_Pose_y - turtle_pose.y) , (goal->goal_Pose_x - turtle_pose.x)) - turtle_pose.theta;
        vel_msg.linear.x = 1 * linear_error+ 0.01 * (linear_error-old_linear_error)/0.1; //+ acc_error*0.1;
        vel_msg.linear.y = 0;
		    vel_msg.linear.z = 0;
        vel_msg.angular.x = 0;
		    vel_msg.angular.y = 0;
        vel_msg.angular.z = 4 * angular_error + 0.01 * (angular_error - old_angular_error)/0.1;
        vel_pub.publish(vel_msg);
        old_linear_error = getDistance(turtle_pose.x, turtle_pose.y, goal->goal_Pose_x, goal->goal_Pose_y);
        old_angular_error = atan2(goal->goal_Pose_y - turtle_pose.y , goal->goal_Pose_x - turtle_pose.x) - turtle_pose.theta;
        //feedback.curr_Pose_x = turtle_pose.x;
        //feedback.curr_Pose_y = turtle_pose.y;
        r.sleep();
      }
      ROS_INFO("%s: Succeeded", action_name.c_str());
      as.setSucceeded();
    }
};

void poseCallback(const turtlesim::Pose::ConstPtr & pose_message)
{
	turtle_pose.x = pose_message->x;
	turtle_pose.y = pose_message->y;
	turtle_pose.theta = pose_message->theta;
}

double getDistance(double x1,double y1,double x2, double y2)
{
	return sqrt(pow((x1-x2),2) + pow((y1-y2),2));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "waypoint");
  waypointAction go("waypoint");
  ros::spin();
  return 0;
}
