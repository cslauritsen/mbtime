set(CMAKE_C_COMPILER c99)
cmake_minimum_required(VERSION 2.6)
project(mbtime)

if(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
	set(CMAKE_INSTALL_RPATH "/usr/sfw/lib;/usr/ccs/lib")
endif(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")

if ( CMAKE_COMPILER_IS_GNUCC )
	add_compile_options(-Wall)
endif ( CMAKE_COMPILER_IS_GNUCC )


add_compile_options(-g)
add_definitions(-D_GNU_SOURCE -DHAVE_EXPAT_H -D__EXTENSIONS__ -D_XPG6)
include_directories(/usr/include /usr/local/include /opt/mqm/inc include /usr/sfw/include /usr/include/glib-2.0 /usr/lib64/glib-2.0/include /usr/lib/glib-2.0/include)
link_directories(/lib64 /usr/lib64 /usr/sfw/lib /usr/lib /usr/ccs/lib)

add_library(mbtime SHARED src/mbtime01.c)

link_libraries(mbtime)

add_executable(mbtime_test ../src/mbtime_test.cpp)

# INSTALLATION SECTION
# By default, install the library & includes to /usr/local
install(TARGETS mbtime DESTINATION /usr/local/lib)
install(FILES src/mbtime01.h DESTINATION /usr/local/include)

