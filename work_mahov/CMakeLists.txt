# CMakeList.txt: проект CMake для server_mp3_manager; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.


find_package(Boost REQUIRED)
set(CMAKE_TOOLCHAIN_FILE, "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
add_executable (server_mp3_manager 
									"server.cpp" "server.h"
									"constants.h"
									"client.cpp" "client.h"
									"main.cpp"
									"asio.h"
									"filereciver.cpp" "filereciver.h"
									"tcpheader.cpp" "tcpheader.h"
									"hello_word.h"
 "hello_word.h")
include_directories(${Boost_INCLUDE_DIR})





if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET server_mp3_manager PROPERTY CXX_STANDARD 20 Boost_INCLUDE_DIR)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
