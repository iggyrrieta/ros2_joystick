/*****************************************************************************
** Includes
*****************************************************************************/
#include <QApplication>
#include "../include/ros2_joystick/main_window.hpp"

#include "rclcpp/rclcpp.hpp"
/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    ros2joystick::MainWindow w(argc,argv);
    w.setWindowTitle("AGEVE Joystick");
    w.show();
    int result = app.exec();

    return result;
}
