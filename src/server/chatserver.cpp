#include "chatserver.hpp"
#include <iostream>
#include "chatservice.hpp"
#include <functional>
#include <string>
#include "json.hpp"
using JSON = nlohmann::json;
ChatServer::ChatServer(muduo::net::EventLoop *loop,
               const muduo::net::InetAddress &listenAddr,
               const std::string &nameArg):server_(loop, listenAddr, nameArg), loop_(loop)
{
    server_.setConnectionCallback(std::bind(&ChatServer::on_conntion, this, std::placeholders::_1));
    server_.setMessageCallback(std::bind(&ChatServer::on_message, this, std::placeholders::_1,
                                                                        std::placeholders::_2,
                                                                        std::placeholders::_3));
    server_.setThreadNum(4);
}
void ChatServer::start()
{
    server_.start();

}
void ChatServer::on_conntion(const muduo::net::TcpConnectionPtr & conn)
{
    if (!conn->connected())
    {
        ChatService::get_instance()->clientCloseException(conn);
        conn->shutdown();
    }
}
void ChatServer::on_message(const muduo::net::TcpConnectionPtr &conn,
                   muduo::net::Buffer * buffer,
                   muduo::Timestamp time)
{
    std::string buf = buffer->retrieveAllAsString();
    JSON json = JSON::parse(buf);

    auto msgHandler = ChatService::get_instance()->getHandler(json["msgid"].get<int>());
    msgHandler(conn, json, time);
}