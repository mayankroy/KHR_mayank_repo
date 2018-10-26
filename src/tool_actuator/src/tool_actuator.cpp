// Includes_____________________________________________________________________
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Transform.h>
#include <geometry_msgs/TransformStamped.h>

#include <vector>
#include <string>                             // stod
#include <cstdio>
#include <cstring>

// Setup namespaces_____________________________________________________________
using namespace std;


// Global Constants_____________________________________________________________
const int _port_number = 2001;


// Code_________________________________________________________________________


// This callback works like an interrupt, and will be executed every time the
// /tool_actuated rostopic is updated
void CallbackToolActuated (std_msgs::Bool tool_msg)
{
  /* TODO
   * - Save/send the tool data to TA
   * - Set the tool_actuated rostopic to false to let node 2 (robot_navigator)
   *   know that it can proceed with the next waypoint
   *
   *
   */
}


// This callback works like an interrupt, and will be executed every time the
// /job_completed rostopic is updated
void CallbackJobCompleted (std_msgs::Bool job_msg)
{
  /* TODO
   * Send the "job done" message to TA
   */
}


int main(int argc, char **argv)
{
  // Setup ROS node, including publishers and subscribers
  ros::init(argc, argv, "tool_actuator");
  ros::NodeHandle nh("~");
  ros::Publisher tool_publisher   = nh.advertise<std_msgs::Bool>("tool_actuated", 10);
  ros::Subscriber tool_subscriber = nh.subscribe("tool_actuated", 10, CallbackToolActuated);
  ros::Subscriber job_subscriber  = nh.subscribe("job_completed", 10, CallbackJobCompleted);

  /* TODO
   * Establish a connection to TA on port 2001
   *
   */

  // Sit here waiting, allowing the callbacks to run and only ending when
  // the node is shut down with "Ctrl+C"
  ros::spin();

  return 0;
}
