##############################################################################
# PROJECT
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ros2_joystick)

##############################################################################
# CMAKE | As found in ROS2 eloquent distribution
##############################################################################

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

##############################################################################
# DEPENDENCIES | Add package dependencies here
##############################################################################

# Find QT dependencies
    # Para aplicacion QWidgets añadir --> Core Gui Widgets
    # Para aplicacion QML añadir --> Core Gui Quick
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED) #Ejemplo para QWidget

# Find ROS2 dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)

##############################################################################
# QT5 - FILES PATH | AUTO SET  
##############################################################################

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB UIS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  ui/*.ui
  )
file(GLOB RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  resources/*.qrc
  )
file(GLOB_RECURSE MOC_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS
  include/${PROJECT_NAME}/*.h *.hpp
  )
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS
  src/*.cpp
  )

QT5_ADD_RESOURCES(QT_RESOURCES ${RESOURCES})
QT5_WRAP_UI(QT_UIS ${UIS})
QT5_WRAP_CPP(QT_HEADERS ${MOC_HEADERS})
  

##############################################################################
# COMPILE | Add ament_target dependencies here | Add target link ligraries
##############################################################################

## Add executables
add_executable(${PROJECT_NAME} 
  ${SOURCES} 
  ${QT_RESOURCES}
  ${QT_UIS}
  ${QT_HEADERS} 
  )


ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  geometry_msgs
  nav_msgs
  )

#En caso de QML, substituir Widgets por Quick
target_link_libraries(${PROJECT_NAME}
  Qt5::Widgets
  Qt5::Core
  Qt5::Gui
  )

## Install executable
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

ament_package()
