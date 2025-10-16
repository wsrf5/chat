#pragma once
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
class ChatServer
{
public:
    ChatServer(muduo::net::EventLoop *loop,
               const muduo::net::InetAddress &listenAddr,
               const std::string &nameArg);
    void start();
private:
    //连接回调
    void on_conntion(const muduo::net::TcpConnectionPtr &);
    //消息回调
    void on_message(const muduo::net::TcpConnectionPtr &,
                   muduo::net::Buffer *,
                   muduo::Timestamp);
    muduo::net::TcpServer server_;
    muduo::net::EventLoop* loop_;
};