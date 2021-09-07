//
// Created by andilyliao on 16-11-14.
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <vector>
#include<string>
using namespace std;

//读取文件中的内容
int fputcget(char* buf)
{
    FILE *fp;
    //int ch;

    if ( (fp = fopen("/home/wy/CLionProjects/cuda/aaa.txt", "a+")) == NULL) {
        perror("Open file file2\n");
        exit(1);
    }
//    while ( (ch = fgetc(stdin)) != '0'){
   /* while ( (ch = getchar()) != '0'){
        fputc(ch, fp);
    }
    rewind(fp);*/
    /*while ( (ch = fgetc(fp)) != EOF) {
        //putchar(ch);
        //fputc(ch,stdout);
        fgets(buf,100,fp);
    }*/
    fread(buf,1024,1,fp);
    int res=fclose(fp);
    if(res<0){
        perror("error!!!!!");
        cout<<strerror(errno)<<"\t"<<errno<<endl;
        exit(1);
    }

    cout<<"ok"<<endl;
    return 0;
}

//区分字符串
vector<string> split(string str,string pattern) {
    string::size_type pos;
    vector<string> result;
    str+=pattern;  //扩展字符串以方便操作
    int size=str.size();
    for(int i=0;i<size;i++) {
        pos=str.find(pattern,i);
        if(pos<size) {
            string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}