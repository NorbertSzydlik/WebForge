set(Boost_DEBUG ON)

set(BOOST_ROOT "${PROJECT_SOURCE_DIR}/lib/boost_1_60_0")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost REQUIRED system)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(SOURCE_FILES main.cpp Server.hpp IncomingMessage.hpp ServerResponse.hpp Server.cpp Connection.cpp Connection.hpp ServerResponse.cpp)
    add_executable(WebForge ${SOURCE_FILES})

    set_property(TARGET WebForge PROPERTY CXX_STANDARD 14)

    target_link_libraries(WebForge ${Boost_LIBRARIES})
endif()


