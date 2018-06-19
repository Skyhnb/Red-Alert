
//定义传输命令的编码

#ifndef OrderCode_h
#define OrderCode_h

/* 查找是否存在已经建立好的游戏房间*/
#define FIND_FOR_ROOM  "a"

/*回应FIND_FOR_ROOM, 并提供房间基本信息*/
#define ANSWER_FOR_ROOM "b"

//开启client的filter mode, 并传输过滤关键词
#define OPEN_KEY "c"

/*广播开始游戏指令*/
#define START_GAME "d"

/*向房间内所有玩家传输新加入房间的玩家信息*/
#define JOIN_ROOM "e"

/*新加入房间的玩家向房间拥有者请求房间内所有玩家的信息*/
#define ASK_FOR_ALL_PLAYERS_IN  "f"

/*房间所有者向新加入者传输房间内所有玩家的信息*/
#define ANSWER_FOR_ALL_PLAYERS_IN "g"

/*向房间内所有玩家传输聊天信息*/
#define CHAT_MES "h"

/*向游戏内其他玩家广播被消灭消息，确保同步消灭*/
#define DEAD_MES "i"
#endif /*OrderCode_h */

