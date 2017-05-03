#include<ros/ros.h>
#include<iostream>
#include<actionlib/client/simple_action_client.h>
#include<actionlib/client/terminal_state.h>
#include<actionlib_tutorials/waypointAction.h>
using namespace std;

int main(int argc, char** argv){
  ros::init(argc, argv, "waypoint_client");
  actionlib::SimpleActionClient<actionlib_tutorials::waypointAction> ac("waypoint", true);
  ROS_INFO("Waiting for action server to start");
  ac.waitForServer();
  actionlib_tutorials::waypointGoal goal;
  cout<<"Enter x,y: ";
  cin>>goal.goal_Pose_x>>goal.goal_Pose_y;
  ROS_INFO("Action server started, sending goal");
  ac.sendGoal(goal);
  bool finished = ac.waitForResult();
  if(finished){
    actionlib::SimpleClientGoalState state = ac.getState();
    ROS_INFO("Action finished: %s", state.toString().c_str());
  }
  return 0;
}
