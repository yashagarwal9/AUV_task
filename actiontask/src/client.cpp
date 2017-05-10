#include<iostream>
#include<ros/ros.h>
#include<actionlib/client/simple_action_client.h>
#include<actionlib/client/terminal_state.h>
#include<actiontask/waypointAction.h>
using namespace std;
int main(int argc, char **argv){
  ros::init(argc, argv, "client");
  actionlib::SimpleActionClient<actiontask::waypointAction> client1("linVelControl", true);
  actionlib::SimpleActionClient<actiontask::waypointAction> client2("angVelControl", true);
  ROS_INFO("Waiting for servers");
  client1.waitForServer();
  client2.waitForServer();
  actiontask::waypointGoal goal;
  cout<<"Enter x: ";
  cin>>goal.goal_x;
  cout<<"Enter y: ";
  cin>>goal.goal_y;
  client1.sendGoal(goal);
  client2.sendGoal(goal);
  bool finished = client1.waitForResult() && client2.waitForResult();
  if(finished){
    actionlib::SimpleClientGoalState state1 = client1.getState();
    ROS_INFO("Action finished: %s", state1.toString().c_str());
    actionlib::SimpleClientGoalState state2 = client2.getState();
    ROS_INFO("Action finished: %s", state2.toString().c_str());
  }
  else
  ROS_INFO("Action did not finish");
  return 0;
}
