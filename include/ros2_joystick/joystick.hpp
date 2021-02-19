#ifndef ros2_joystick_QNODE_HPP_
#define ros2_joystick_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
//ROS2
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
//CPP
#include <chrono>
#include <memory>
#include <functional>
#include <string>
#endif

//QT
#include <QThread>
#include <QMutex>


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ros2joystick {

  /*****************************************************************************
  ** Class
  *****************************************************************************/

  class joystick : public QThread
  {
    Q_OBJECT
  public:
      joystick(int argc, char** argv, const char * topic  = "/odom");
      virtual ~joystick();
      bool init();
      void run();

      /*********************
      ** Obtener variables
      ** posicion y velocidad
      **********************/
      double getXPos();
      double getXSpeed();
      double getASpeed();
      double getYPos();
      double getAPos();

      /*********************
      ** Methodo callback
      **********************/
      void poseCallback(const nav_msgs::msg::Odometry msg);

      /*********************
      ** Aplicar cambios
      ** velocidad y posicion
      **********************/
      void SetSpeed(double speed, double angle);

  private:
      int init_argc;
      char** init_argv;
      const char * m_topic;

      /*********************
      ** Variables
      ** posicion y velocidad
      **********************/
      double m_speed;
      double m_angle;
      double m_xPos;
      double m_yPos;
      double m_aPos;

      /*********************
      ** Variables Rangos
      **********************/
      double m_maxRange;
      double m_minRange;

      /*********************
      ** Subscriber y
      ** Publisher
      **********************/
      rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr pose_listener;
      rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr sim_velocity;
  };
} // namespace ros2joystick
#endif /* ros2_joystick_QNODE_HPP_ */
