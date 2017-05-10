#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<ros/ros.h>
#include<actiontask/waypointAction.h>
class controller{
public:
  controller();
  virtual void stop()=0;
  virtual void move()=0;
  virtual void turn()=0;
  void resetController();
  double error[6];
};
#endif // CONTROLLER_H
