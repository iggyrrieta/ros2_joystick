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

  joystick::joystick(int argc, char **argv, const char * topic) :
      init_argc(argc),
      init_argv(argv),
      m_topic(topic)
      {}

  joystick::~joystick()
  {
    rclcpp::shutdown();

  }//end destructor

  bool joystick::init()
  {
    rclcpp::init(init_argc,init_argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("joystick");

    //Create publishers and subscribers
    sim_velocity = node->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel",100);
    //pose_listener = node->create_subscription<nav_msgs::msg::Odometry>("/odom", 10, std::bind(&joystick::poseCallback, this, _1));

    return 0;

  }//set up the node

  void joystick::poseCallback(const nav_msgs::msg::Odometry msg)
  {
    QMutex * pMutex = new QMutex();

    pMutex->lock();
    m_xPos = msg.pose.pose.position.x;
    m_yPos = msg.pose.pose.position.y;
    m_aPos = msg.pose.pose.orientation.w;
    pMutex->unlock();

    delete pMutex;
  }//callback method to update the robot's position.

  void joystick::run()
  {
    while (rclcpp::ok())
    {
      QMutex * pMutex;
      pMutex = new QMutex();
      auto cmd_msg = geometry_msgs::msg::Twist();

      pMutex->lock();
      cmd_msg.linear.x = m_speed;
      cmd_msg.angular.z = m_angle;
      pMutex->unlock();

      sim_velocity->publish(cmd_msg);
      delete pMutex;
    }
  }//run

  void joystick::SetSpeed(double speed, double angle)
  {
    QMutex * pMutex = new QMutex();
    pMutex->lock();
    m_speed = speed;
    m_angle = angle;
    pMutex->unlock();

    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"Consigna velocidad : (%.2f, %.2f)", m_speed, m_angle);

    delete pMutex;
  }//set the speed of the robot.

  double joystick::getXSpeed(){ return m_speed; }
  double joystick::getASpeed(){ return m_angle; }

  double joystick::getXPos(){ return m_xPos; }
  double joystick::getYPos(){ return m_yPos; }
  double joystick::getAPos(){ return m_aPos; }

} //namespace ros2joystick
