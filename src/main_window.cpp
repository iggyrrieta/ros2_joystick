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
      Qjoystick(argc,argv)
  {
    ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

    //Refresh posiciones pantalla cada segundo
    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()),
    //        this, SLOT(updatePoseDisplay()));
    //timer->start(1000);

    //Inicializar Qjoystick
    Qjoystick.init();
  }

  MainWindow::~MainWindow()
  {}// End Destructor

  /*****************************************************************************
  ** JOYSTICK CONTROL
  *****************************************************************************/
  void MainWindow::on_go_forward_clicked()
  {
    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"MOVE : FORWARD!");
    Qjoystick.SetSpeed(set_Xspeed, 0);
  }

  void MainWindow::on_go_back_clicked()
  {
    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"MOVE : BACKWARD!");
    Qjoystick.SetSpeed(-set_Xspeed, 0);
  }

  void MainWindow::on_go_left_clicked()
  {
    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"MOVE : LEFT!");
    Qjoystick.SetSpeed(0, PI / set_Aspeed);
  }

  void MainWindow::on_go_right_clicked()
  {
    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"MOVE : RIGHT!");
    Qjoystick.SetSpeed(0, PI / -set_Aspeed);
  }

  void MainWindow::on_pause_clicked()
  {
    RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"STOP!");
    Qjoystick.SetSpeed(0, 0);
  }

  void MainWindow::on_x_speed_valueChanged(int value)
  {
    set_Xspeed = value/10.0;

    //Show current speed
    ui.show_x_speed->setText(QString::number(set_Xspeed,'f',2));
  }
  void MainWindow::on_a_speed_valueChanged(int value)
  {
    set_Aspeed = value;

    //Show current ANGLE
    ui.show_a_speed->setText(QString::number(set_Aspeed,'f',2));
  }

  void MainWindow::updatePoseDisplay()
  {
    if (Qjoystick.init())
    {
      //Get position
      double x = Qjoystick.getXPos();
      double y = Qjoystick.getYPos();
      double a = Qjoystick.getAPos();

      RCLCPP_INFO(rclcpp::get_logger("JOYSTICK"),"Posicion actual : (%.2f,%.2f,%.2f)", x,y,a);

      //Show current posicion
      ui.x_label->setText(QString::number(x,'f',2));
      ui.y_label->setText(QString::number(y,'f',2));
      ui.o_label->setText(QString::number(a,'f',2));
    }
  }

  void MainWindow::closeEvent(QCloseEvent *event)
  {
    QMainWindow::closeEvent(event);
  }

} //End namespace ros2joystick










