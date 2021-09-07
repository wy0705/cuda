#include <iostream>

/*int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <hiredis/hiredis.h>
#include "fputcget.cpp"


/*void add(redisContext* conn,redisReply *reply){
    for (int i = 0; i < 100; ++i) {
        const char* a= reinterpret_cast<const char *>(i);
        printf("%s\n",&a);
        redisCommand(conn,"set %s %s",a,"hello");
        printf("set ok!");
        freeReplyObject(reply);
    }
}*/
int conredis(char* buf){
    char *hostname = "127.0.0.1";
    int port = 6379;
    //char *password = "";

    redisContext *conn;
    redisReply *reply;
    struct timeval timeout = {1, 500000};
    conn = redisConnectWithTimeout(hostname, port, timeout);
    // conn erro
    if (conn == NULL || conn->err) {
        if (conn) {
            printf("connection error %s\n", conn->errstr);
            exit(1);
        } else {
            printf("cannot alloc redis context\n");
            exit(1);
        }
    }

    // set
    string s=buf;
    vector<string> vector=split(s,"\n");
    char *argv[vector.size()];
    char* c;
    for (int i = 0; i < vector.size(); ++i) {
        const int len=vector[i].length();
        c=new char[len+1];
        strcpy(c,vector[i].c_str());
        argv[i]=c;
    }
    for (int i = 0; i < vector.size(); ++i) {
        //printf("%s\n%s",argv[i],argv[i+1]);
        redisCommand(conn,"set %s %s",argv[i],argv[i+1]);
        printf("set ok!");
        i++;
        //freeReplyObject(reply);
    }


    // get
    for (int i = 0; i < vector.size(); ++i) {
        reply=(redisReply*)redisCommand(conn, "get %s",argv[i]);
        if (reply->type != REDIS_REPLY_STRING) {
            printf("Failed to execute command[].\n");
            freeReplyObject(reply);
            redisFree(conn);
            return 0;
        }
        printf("The value of '%s' is %s.\n",argv[i],reply->str);
        freeReplyObject(reply);
        printf("Succeed to execute command[].\n");
        i++;
    }


    // free conn
    redisFree(conn);
}
int main() {

    char* buf=(char *)malloc(1024);
    fputcget(buf);
    printf("11111\n%s",buf);

    conredis(buf);

    return 0;
}