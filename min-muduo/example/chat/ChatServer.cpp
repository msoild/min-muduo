#include "net/EventLoop.h"
#include "net/TcpServer.h"
#include "net/InetAddress.h"
#include "net/EventLoopThreadPool.h"
#include "net/Callback.h"

#include "Codec.h" //消息的编解码器 --- 最简单的格式, 头部4个字节代表消息长度


#include <map>
#include <set>
#include <memory>
#include <functional>
#include <assert.h>


using namespace std::placeholders;

class ChatServer : smuduo::noncopyable {
public:
    
    ChatServer(EventLoop* loop, const InetAddress& listenAddr)
        : loop_(loop),
          server_(loop, listenAddr),
          codec_(
              std::bind(&ChatServer::onStringMessage, this, _1, _2, _3)
          )
    {
        server_.setConnectionCallback(
            std::bind(&ChatServer::onConnection, this, _1)
        );

        server_.setMessageCallback(
           std::bind(&Codec::onMessage, &codec_, _1, _2, _3) //ConnPtr Buffer* Timestamp
       );
    }
    
    // default dtor is okay


    void start() //开始工作
    {
        server_.start();
    }

private:
    EventLoop* loop_;
    TcpServer server_;
    std::set<TcpConnectionPtr> conns_; 
    Codec codec_;
    
    void onConnection(const TcpConnectionPtr& conn){
        if(conn->connected()) { 
            conns_.insert(conn);
         
        }
        else { 
            conns_.erase(conn);
        }
    }

    void onStringMessage(const TcpConnectionPtr& conn, const std::string msg, Timestamp recvTime){
        assert(conns_.find(conn) != conns_.end()); 
        for(const TcpConnectionPtr& conn : conns_) {
            codec_.send(conn, msg);
        }
    }

//    std::unique_ptr<EventLoopThreadPool>  threadPool_; //线程池
    
   
};


// ChatServer 0.1.0 只具有消息转发功能

int main(int argc, char** argv) {
    printf("============================================\n\n");
    printf("       ChatServer  - hiworld       \n\n");
    printf("============================================\n\n\n");

    // argv[1] - port: 缺省为9981

    EventLoop loop; //主线程
    int port = (argc > 1) ? atoi(argv[1]) : 9981;
    InetAddress listenAddr(port);

    ChatServer server(&loop, listenAddr);
    server.start();

    loop.loop();

    return 0;
}   