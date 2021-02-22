/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/ros2_joystick/joystick.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ros2joystick {
  using namespace std::chrono_literals;
  using std::placeholders::_1;

  /*****************************************************************************
  ** Implementation
  *****************************************************************************/

  joystick::joystick() : Node("Joystick")
  {
      sim_velocity = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel",100);
  }

  joystick::~joystick()
  {
    rclcpp::shutdown();
  }

  void joystick::SetSpeed(double speed, double angle)
  {
    m_speed = speed;
    m_angle = angle;
    auto cmd_msg = geometry_msgs::msg::Twist();
    cmd_msg.linear.x = m_speed;
    cmd_msg.angular.z = m_angle;
    sim_velocity->publish(cmd_msg);

    RCLCPP_INFO(this->get_logger(),"Consigna velocidad : (%.2f, %.2f)", m_speed, m_angle);

  }

  double joystick::getXSpeed(){ return m_speed; }
  double joystick::getASpeed(){ return m_angle; }

}
