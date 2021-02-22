#ifndef demo_joystick_MAIN_WINDOW_H
#define demo_joystick_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/
//QT
#include <QMainWindow>

//CPP
#include <chrono>
#include <memory>

//ROS2
#include "rclcpp/rclcpp.hpp"

//ros2_joystick files
#include "joystick.hpp"
#include "ui_main_window.h"

/*****************************************************************************
** Namespace
*****************************************************************************/
namespace Ui {class MainWindow;}
namespace ros2joystick {

  #define PI 3.14159265359

  /*****************************************************************************
  ** CLASSES | Mainwindow
  *****************************************************************************/
  class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    MainWindow(int argc, char** argv, QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent *event); // Overloaded function

  private Q_SLOTS:
    /*********************
    ** Botones direccion
    **********************/
    void on_go_forward_clicked();
    void on_go_back_clicked();
    void on_go_left_clicked();
    void on_go_right_clicked();
    void on_pause_clicked();

    /*********************
    ** Sliders velocidad
    **********************/
    void on_x_speed_valueChanged(int value);
    void on_a_speed_valueChanged(int value);

  private:
    Ui::MainWindowDesign *ui;
    int argc_;
    char** argv_;

    /*********************
    ** Variables velocidad
    ** de Sliders
    **********************/
    double set_Xspeed;
    double set_Aspeed;

    /*********************
    ** Link a joystick 
    **********************/
    std::shared_ptr<joystick> Qjoystick;
    std::thread ros_spin_thread_;
    void rosSpinThread();

  };
}

#endif
