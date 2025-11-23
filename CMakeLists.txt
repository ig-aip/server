cmake_minimum_required(VERSION 3.16)

project(easy_files LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost)
find_package(Boost REQUIRED COMPONENTS system)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


add_executable(easy_files
  main.cpp
  server.h server.cpp
  constants.h
  filereciver.h filereciver.cpp
  asio.h
)
target_link_libraries(easy_files Qt${QT_VERSION_MAJOR}::Core Boost::boost Boost::system ws2_32 mswsock )


include(GNUInstallDirs)
install(TARGETS easy_files
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
