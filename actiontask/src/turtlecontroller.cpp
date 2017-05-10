#include<actiontask/turtlecontroller.h>

turtlecontroller::turtlecontroller():controller(){
  Kp = 1;
  Kd = 0.01;
  Ki = 0;
  aKp = 4;
  aKd = 0.1;
  aKi = 0;
}
void turtlecontroller::stop(){
  Kp = 0;
  Kd = 0;
  Ki = 0;
  aKp = 0;
  aKd = 0;
  aKi = 0;
}
void turtlecontroller::move(){
  vel_msg.linear.x = Kp*error[0] + Ki*error[2] + Kd*error[1];
  vel_msg.linear.y = 0;
  vel_msg.linear.z = 0;
}
void turtlecontroller::turn(){
  vel_msg.angular.z = aKp*error[3] + aKi*error[5] + aKd*error[4];
  vel_msg.angular.y = 0;
  vel_msg.angular.x = 0;
}
void turtlecontroller::calError(double _error[], const actiontask::waypointFeedback _feedback, const actiontask::waypointGoal _setPoint){
  _error[1] = getDis(_setPoint.goal_x, _setPoint.goal_y, _feedback.curr_x, _feedback.curr_y) - _error[0];
  _error[0] = getDis(_setPoint.goal_x, _setPoint.goal_y, _feedback.curr_x, _feedback.curr_y);
  _error[2] = _error[0] + _error[2];
  _error[4] = (atan2(_setPoint.goal_y - _feedback.curr_y, _setPoint.goal_x - _feedback.curr_x) - _feedback.curr_theta) - _error[3];
  _error[3] = atan2(_setPoint.goal_y - _feedback.curr_y, _setPoint.goal_x - _feedback.curr_x) - _feedback.curr_theta;
  _error[5] = _error[3] + _error[5];
}
double turtlecontroller::getDis(double goalx, double goaly, double currx, double curry){
  return (sqrt(pow(goalx-currx, 2) + pow(goaly-curry, 2)));
}
bool turtlecontroller::checkError(double error[]){
  if(error[0]<0.1)
    return false;
  else
    return true;
}
