#include<actiontask/controlserver.h>

controlserver::controlserver()
{
  ros::NodeHandle n;
  _stateSub = n.subscribe("/turtle1/pose", 10, &controlserver::stateFeedBack, this);
  _velPub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
}
controlserver::~controlserver()
{}
void controlserver::setServer(actionlib::SimpleActionServer<actiontask::waypointAction> *_serv1, actionlib::SimpleActionServer<actiontask::waypointAction> *_serv2){
  _server1 = _serv1;
  _server2 = _serv2;
  _server1 -> start();
  _server2 -> start();
}
void controlserver::stateFeedBack(const turtlesim::Pose::ConstPtr &msg){
  _feedback.curr_x = msg->x;
  _feedback.curr_y = msg->y;
  _feedback.curr_theta = msg->theta;
}
void controlserver::executePoseChange(const actiontask::waypointGoalConstPtr &msg){
  bool success = true;
  actiontask::waypointGoal _setpoint;
  _setpoint.goal_x = msg->goal_x;
  _setpoint.goal_y = msg->goal_y;
  ROS_INFO("Executing liner_vel_control");
  ros::Rate r(10);
  do{
    if(_server1->isPreemptRequested() || !ros::ok()){
      ROS_INFO("server1 is preempted");
      _server1->setPreempted();
      success = false;
      break;
    }
    _turtlecontrol.calError(_turtlecontrol.error, _feedback, _setpoint);
    _turtlecontrol.move();
    _server1->publishFeedback(_feedback);
    _velPub.publish(_turtlecontrol.vel_msg);
    ros::spinOnce();
    r.sleep();
  }while(_turtlecontrol.checkError(_turtlecontrol.error));
  if(success){
    ROS_INFO("server1: Succeeded");
    _server1->setSucceeded();
  }
}
void controlserver::executeOrientationChange(const actiontask::waypointGoalConstPtr &msg){
  bool success = true;
  actiontask::waypointGoal _setpoint;
  _setpoint.goal_x = msg->goal_x;
  _setpoint.goal_y = msg->goal_y;
  ROS_INFO("Executing angular_vel_control");
  ros::Rate r(10);
  do{
    if(_server2->isPreemptRequested() || !ros::ok()){
      ROS_INFO("server2 is preempted");
      _server2->setPreempted();
      success = false;
      break;
    }
    _turtlecontrol.calError(_turtlecontrol.error, _feedback, _setpoint);
    _turtlecontrol.turn();
    _velPub.publish(_turtlecontrol.vel_msg);
    ros::spinOnce();
    r.sleep();
  }while(_turtlecontrol.checkError(_turtlecontrol.error));
  if(success){
    ROS_INFO("server2: Succeeded");
    _server2->setSucceeded();
  }
}
