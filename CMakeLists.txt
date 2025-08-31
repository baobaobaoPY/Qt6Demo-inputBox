cmake_minimum_required(VERSION 3.20)
project(Qt6Demo)

# 强制使用C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 配置cmake搜索Qt安装路径
# 需根据实际Qt安装路径进行修改
if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/msvc2022_64/")
elseif(UNIX AND NOT APPLE)
    set(CMAKE_PREFIX_PATH "$ENV{HOME}/Qt/6.9.1/gcc_64/")
endif()

# 配置Qt6库
find_package(Qt6 REQUIRED
    COMPONENTS
    Core 
    Widgets 
)

# 配置源文件
set(SOURCE ./src/main.cpp)
set(SOURCE_HEAD 
    ./head/main.h
    ./head/globalFonts.h
    ./head/centre_XY.h
    ./head/pathProcessing.h
)
set(SOURCE_CSS 
    ./css/CSS.h
)

add_executable(Qt6Demo ${SOURCE} ${SOURCE_HEAD} ${SOURCE_CSS})

# 链接Qt6库
target_link_libraries(Qt6Demo PRIVATE 
    Qt6::Core 
    Qt6::Widgets 
)

# 配置Qt`moc|uic|rcc`自动工作
set_target_properties(
    Qt6Demo PROPERTIES 
    AUTOMOC ON 
    AUTOUIC ON 
    AUTORCC ON 
)
