// Includes____________________________________________________________________________
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
#include "tf/tfMessage.h"
#include "sensor_msgs/Imu.h"
#include <tf/transform_broadcaster.h>
#include "geometry_msgs/TransformStamped.h"
#include <sstream>

// Globals____________________________________________________________________________
string _default_imu_topic = "imu/data";   // this will be /microstrain_imu/data/enu on jackal
sensor_msgs::Imu _latest_imu_msg;


// Code____________________________________________________________________________



void CallbackImu (const sensor_msgs::Imu imu_msg)
{
  // Just update the global storage for the IMU message
  _latest_imu_msg = imu_msg;
}



void ParseTrimbleAccessMessage (string input_ta_msg,
                                nav_msgs::Odometry& output_odom)
{

}



int main(int argc, char **argv)
{
  // Set up ROS node, including publishers and subscribers
  ros::init(argc, argv, "trimble_access_listener");
  ros::NodeHandle nh("~");
  ros::Rate loop_rate(10);      // rate for the main loop to cycle through in Hz
  ros::Publisher odom_publisher = nh.advertise<nav_msgs::Odometry>("odometry/measured", 1000);
  ros::Subscriber sub = nh.subscribe("imu/data", 10, CallbackImu);
  
  string latest_ta_position;
  nav_msg::Odometry latest_odom_msg;

  // Enter into a loop, consistently polling TA for positions, only exits
  // when "Ctrl + C" is pressed
  while (ros::ok())
  {
    /* TODO
     * Poll or wait for TA to return the next position estimate as a string
     *
     */

    // Parse the string
    ParseTrimbleAccessMessage(latest_ta_position, latest_odom_msg);

    // Publish the odometry
    odom_publisher.publish(latest_odom_msg);

    // These functions make sure this while loop runs at 10 Hz, and allows
    // callbacks to run
    ros::spinOnce();
    loop_rate.sleep();
  }

  // Sit here waiting, allowing the callbacks to run and only ending when
  // the node is shut down with "Ctrl+C"
  ros::spin();

  return 0;
}
