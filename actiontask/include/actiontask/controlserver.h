#ifndef CONTROLSERVER_H
#define CONTROLSERVER_H
#include<ros/ros.h>
#include<actionlib/server/simple_action_server.h>
#include<actiontask/waypointAction.h>
#include<turtlesim/Pose.h>
#include<actiontask/turtlecontroller.h>
class controlserver{
public:
  controlserver();
  ~controlserver();
  void setServer(actionlib::SimpleActionServer<actiontask::waypointAction> *_serv1, actionlib::SimpleActionServer<actiontask::waypointAction> *_serv2);
  void stateFeedBack(const turtlesim::Pose::ConstPtr &msg);
  void executePoseChange(const actiontask::waypointGoalConstPtr &msg);
  void executeOrientationChange(const actiontask::waypointGoalConstPtr &msg);
  actiontask::waypointFeedback _feedback;

private:
  //ros::NodeHandle n;
  ros::Publisher _velPub,_angvelPub;
  ros::Subscriber _stateSub;
  actionlib::SimpleActionServer<actiontask::waypointAction> *_server1;
  actionlib::SimpleActionServer<actiontask::waypointAction> *_server2;
  turtlecontroller _turtlecontrol;
};
#endif // CONTROLSERVER_H
