#pragma once
#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>

#include "groupmodel.hpp"
#include "friendmodel.hpp"
#include "usermodel.hpp"
#include "offlinemessage.hpp"
#include "json.hpp"
#include "redis.hpp"
using JSON = nlohmann::json;
using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr &conn, JSON &js, muduo::Timestamp)>;

class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService *get_instance();
    // 处理登录业务
    void login(const muduo::net::TcpConnectionPtr &conn, JSON &js, muduo::Timestamp time);
    // 处理注册业务
    void reg(const muduo::net::TcpConnectionPtr &conn, JSON &js, muduo::Timestamp time);
    // 一对一聊天业务
    void oneChat(const muduo::net::TcpConnectionPtr &conn, JSON &js, muduo::Timestamp time);
    // 添加好友业务
    void addFriend(const muduo::net::TcpConnectionPtr &conn, JSON &js, muduo::Timestamp time);
    // 创建群组业务
    void createGroup(const muduo::net::TcpConnectionPtr &conn, JSON &js, muduo::Timestamp time);
    // 加入群组业务
    void addGroup(const muduo::net::TcpConnectionPtr &conn, JSON &js, muduo::Timestamp time);
    // 群组聊天业务
    void groupChat(const muduo::net::TcpConnectionPtr &conn, JSON &js, muduo::Timestamp time);
    // 处理注销业务
    void loginout(const muduo::net::TcpConnectionPtr &conn, JSON &js, muduo::Timestamp time);
    // 处理客户端异常退出
    void clientCloseException(const muduo::net::TcpConnectionPtr &conn);
    // 服务器异常，业务重置方法
    void reset();
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    // 从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int, std::string);
private:
    ChatService();

    // 存储消息id和其对应的业务处理方法
    std::unordered_map<int, MsgHandler> _msgHandlerMap;
    // 存储在线用户的通信连接
    std::unordered_map<int, muduo::net::TcpConnectionPtr> _userConnMap;
    // 定义互斥锁，保证_userConnMap的线程安全
    std::mutex _connMutex;

    // 数据操作类对象
    UserModel _userModel;
    OfflineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;

    // redis操作对象
    Redis _redis;
};