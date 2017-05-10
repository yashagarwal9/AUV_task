#ifndef TURTLECONTROLLER_H
#define TURTLECONTROLLER_H
#include<actiontask/controller.h>
#include<math.h>
#include<actiontask/waypointAction.h>
#include<geometry_msgs/Twist.h>

class turtlecontroller: public controller{
public:
  turtlecontroller();
  void stop();
  void move();
  void turn();
  bool checkError(double error[]);
  void calError(double error[], const actiontask::waypointFeedback _feedback, const actiontask::waypointGoal _setPoint);
  double getDis(double goalx, double goaly, double currx, double curry);
  geometry_msgs::Twist vel_msg;
private:
  float Kp, Kd, Ki, aKp, aKd, aKi;
};
#endif // TURTLECONTROLLER_H
