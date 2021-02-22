#ifndef ros2_joystick_QNODE_HPP_
#define ros2_joystick_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
//ROS2
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
//CPP
#include <chrono>
#include <memory>
#include <functional>
#include <string>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ros2joystick {

  /*****************************************************************************
  ** Class
  *****************************************************************************/

  class joystick : public rclcpp::Node
  {
  public:
      joystick();
      virtual ~joystick();

      /*********************
      ** Obtener variables
      ** posicion y velocidad
      **********************/
      double getXSpeed();
      double getASpeed();


      /*********************
      ** Aplicar cambios
      ** velocidad y posicion
      **********************/
      void SetSpeed(double speed, double angle);

  private:
      /*********************
      ** Variables
      ** posicion y velocidad
      **********************/
      double m_speed;
      double m_angle;

      /*********************
      ** Subscriber y
      ** Publisher
      **********************/
      rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr sim_velocity;
  };
} // namespace ros2joystick
#endif /* ros2_joystick_QNODE_HPP_ */
