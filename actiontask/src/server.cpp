#include<ros/ros.h>
#include<actionlib/server/simple_action_server.h>
#include<actiontask/controlserver.h>
int main(int argc, char** argv){
  ros::init(argc, argv, "server");
  ros::NodeHandle n;
  controlserver _server;
  ROS_INFO("_server1  _server2 running");
  actionlib::SimpleActionServer<actiontask::waypointAction> _server1(n, "linVelControl", boost::bind(&controlserver::executePoseChange, &_server, _1), false);
  actionlib::SimpleActionServer<actiontask::waypointAction> _server2(n, "angVelControl", boost::bind(&controlserver::executeOrientationChange, &_server, _1), false);
  _server.setServer(&_server1, &_server2);
  ros::spin();
  return 0;
}
