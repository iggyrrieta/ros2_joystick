/*****************************************************************************
** Includes
*****************************************************************************/
#include "../include/ros2_joystick/main_window.hpp"
#include "ui_main_window.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/
namespace ros2joystick {

  /*****************************************************************************
  ** Implementation [MainWindow]
  *****************************************************************************/

  MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindowDesign),
      argc_(argc),
      argv_(argv)
  {
    ui->setupUi(this);
    ros_spin_thread_ = std::thread{std::bind(&MainWindow::rosSpinThread, this)};

  }

  MainWindow::~MainWindow(){rclcpp::shutdown();}

  // Start ROS2 NODE
  void MainWindow::rosSpinThread()
  {
    rclcpp::init(argc_, argv_);
    Qjoystick = std::make_shared<ros2joystick::joystick>();
    rclcpp::spin(Qjoystick);
    rclcpp::shutdown();
  }

  /*****************************************************************************
  ** JOYSTICK CONTROL
  *****************************************************************************/
  void MainWindow::on_go_forward_clicked()
  {
    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"MOVE : FORWARD!");
    Qjoystick->SetSpeed(set_Xspeed, 0);
  }

  void MainWindow::on_go_back_clicked()
  {
    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"MOVE : BACKWARD!");
    Qjoystick->SetSpeed(-set_Xspeed, 0);
  }

  void MainWindow::on_go_left_clicked()
  {
    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"MOVE : LEFT!");
    Qjoystick->SetSpeed(0, PI / set_Aspeed);
  }

  void MainWindow::on_go_right_clicked()
  {
    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"MOVE : RIGHT!");
    Qjoystick->SetSpeed(0, PI / -set_Aspeed);
  }

  void MainWindow::on_pause_clicked()
  {
    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"STOP!");
    Qjoystick->SetSpeed(0, 0);
  }

  void MainWindow::on_x_speed_valueChanged(int value)
  {
    set_Xspeed = value/10.0;

    //Show current speed
    ui->show_x_speed->setText(QString::number(set_Xspeed,'f',2));
  }
  void MainWindow::on_a_speed_valueChanged(int value)
  {
    set_Aspeed = value;

    //Show current ANGLE
    ui->show_a_speed->setText(QString::number(set_Aspeed,'f',2));
  }

  void MainWindow::closeEvent(QCloseEvent *event)
  {
    QMainWindow::closeEvent(event);
  }

}










