CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(min-muduo)
INCLUDE_DIRECTORIES(${PROJECT_SRC_DIR}/base)
INCLUDE_DIRECTORIES(${PROJECT_SRC_DIR}/net})
INCLUDE_DIRECTORIES(${PROJECT_SRC_DIR}/example/chat)
INCLUDE_DIRECTORIES(${PROJECT_SRC_DIR})
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})
set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS}")

set(SRCbase  ${PROJECT_SOURCE_DIR}/base/CurrentThread.cpp ${PROJECT_SOURCE_DIR}/base/Timestamp.cpp )
set(SRCnet  ${PROJECT_SOURCE_DIR}/net/EventLoop.cpp ${PROJECT_SOURCE_DIR}/net/Channel.cpp 
${PROJECT_SOURCE_DIR}/net/TimerQueue.cpp  ${PROJECT_SOURCE_DIR}/net/Timer.cpp  ${PROJECT_SOURCE_DIR}/net/EventLoopThread.cpp  
${PROJECT_SOURCE_DIR}/net/EPoller.cpp ${PROJECT_SOURCE_DIR}/net/Buffer.cpp ${PROJECT_SOURCE_DIR}/net/EventLoopThreadPool.cpp 
${PROJECT_SOURCE_DIR}/net/Acceptor.cpp ${PROJECT_SOURCE_DIR}/net/InetAddress.cpp ${PROJECT_SOURCE_DIR}/net/Socket.cpp 		
${PROJECT_SOURCE_DIR}/net/SocketOps.cpp ${PROJECT_SOURCE_DIR}/net/TcpServer.cpp  ${PROJECT_SOURCE_DIR}/net/TcpConnection.cpp  
${PROJECT_SOURCE_DIR}/net/Connector.cpp  ${PROJECT_SOURCE_DIR}/net/TcpClient.cpp )

set(SRCchatClient  ${PROJECT_SOURCE_DIR}/example/chat/ChatClient-SingleUser.cpp )
set(SRCchatServer  ${PROJECT_SOURCE_DIR}/example/chat/ChatServer.cpp)

add_executable(ChatServer ${SRCchatServer} ${SRCnet} ${SRCbase})
target_link_libraries(ChatServer pthread)
add_executable(ChatClient ${SRCchatClient} ${SRCnet} ${SRCbase})
target_link_libraries(ChatClient pthread)