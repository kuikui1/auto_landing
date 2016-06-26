#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <keyboard/Key.h>

geometry_msgs::TwistStamped vs;

void sendCommand(const keyboard::Key &key)
{
   switch (key.code)
   {
                case 'q':
   		{
   			ROS_INFO_STREAM("up");
   			vs.twist.linear.z += 0.1;
   			break;
   		}
               case 'a':
               {
                       ROS_INFO_STREAM("down");
                       vs.twist.linear.z -= 0.1;
                       break;
               }
                case 'j':
   		{
   			ROS_INFO_STREAM("left");
                        vs.twist.linear.y += 0.1;
   			break;
   		}
   		case 'l':
   		{
   			ROS_INFO_STREAM("right");
                        vs.twist.linear.y -= 0.1;
   			break;
   		}

                case 'i':
                {
                       ROS_INFO_STREAM("forward");
                       vs.twist.linear.x += 0.1;
                       break;
                }
               case 'k':
               {
                      ROS_INFO_STREAM("backward");
                      vs.twist.linear.x -= 0.1;
                      break;
               }
               case 'u':
               {
                      ROS_INFO_STREAM("turn clockwise");
                      vs.twist.angular.z += 0.1;
                      break;
               }
               case 'o':
               {
                      ROS_INFO_STREAM("turn clockwise");
                      vs.twist.angular.z -= 0.1;
                      break;
               }
   		default:
   		{
   			
   		}

   }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "px4_velocity_control_node");
  ros::NodeHandle nodeHandle;
  ros::Publisher vel_sp_pub = nodeHandle.advertise<geometry_msgs::TwistStamped>("/mavros/setpoint_velocity/cmd_vel", 10);
  ros::Subscriber commandSubscriber = nodeHandle.subscribe("/keyboard/keydown",1,sendCommand);

  

  ros::Rate loop_rate(10.0);

  while(ros::ok())
  {

    vel_sp_pub.publish(vs);

    ros::spinOnce();

    loop_rate.sleep();
  }


}
