#include <bits/stdc++.h>
using namespace std;

map<string,vector<string> > yl,qz;
set<string> al;
vector<string>gp;
string tar,ver;

void del(string form,string name){
    string t="del ";
    t+=form;
    t+=name;
    system(t.c_str());
}

void cop(string from,string to,string name){
    string t="copy ";
    t+=from;
    t+=name;
    t+=" ";
    t+=to;
    t+=name;
    cout<<t;
    system(t.c_str());
}

void install(string n){
    if(yl.find(n)==yl.end()){
        cout<<"\""<<n<<"\" 不存在"<<endl;
        return;
    }
    if(al.count(n)){
        cout<<"\""<<n<<"\" 已安装"<<endl;
        return;
    }
    al.insert(n);
    cop(string(".\\mod\\")+ver+string("\\"),tar+string("\\"),n);
    cout<<"\""<<n<<"\" 成功安装"<<endl;
    for(auto iter=yl[n].begin();iter!=yl[n].end();iter++){
        install(*iter);
    }
}

void id(){
    for(auto iter=al.begin();iter!=al.end();iter++){
            cout<<*iter<<endl;
    }
}

void ls(){
    for(auto iter=yl.begin();iter!=yl.end();iter++){
            cout<<iter->first<<endl;
    }
}

void help(){
    cout<<R"(
--------------------------------------
help             获取指令帮助
list             获取可用的mod列表
grouplist        获取可用的mod包列表
installed        获取已安装的mod
quit             退出
install xx       安装名为xx的mod及其前置
installgroup xx  安装名为xx的mod包
remove xx        移除名为xx的mod及其依赖
listgroup xx     获取名为xx的mod包内mod列表
--------------------------------------
)";
}
void rem(string n){
    if(yl.find(n)==yl.end()){
        cout<<"\""<<n<<"\" 不存在"<<endl;
        return;
    }
    if(!al.count(n)){
        cout<<"\""<<n<<"\" 尚未安装"<<endl;
        return;
    }
    al.erase(n);
    del(tar+string("\\"),n);
    cout<<"\""<<n<<"\" 成功卸载"<<endl;
    for(auto iter=qz[n].begin();iter!=qz[n].end();iter++){

        rem(*iter);
    }
}

void ig(string n){
    ifstream in((string(".\\group\\")+ver+string("\\")+n).c_str());
    string t,tt;
    while(in>>t){
        in>>tt;
        if(t=="m"){
            install(tt);
        }else{
            ig(tt);
        }
    }
}

void gl(){
    for(auto iter=gp.begin();iter!=gp.end();iter++){
            cout<<*iter<<endl;
    }
}

void lg(string tt){
    ifstream in((string(".\\group\\")+ver+string("\\")+tt).c_str());
    string t;
    while(in>>t){
        cout<<t<<" ";
        in>>t;
        cout<<t<<endl;
    }
}

int main()
{

    ifstream in("setting");
    system("@echo off");
    getline(in,tar);
    getline(in,ver);
    in.close();
    in.open(string(string("./mod/")+ver+string("/LS")).c_str());
    string t,tt;
    while(getline(in,t)){
        stringstream ss(t);
        ss>>tt;
        yl[tt].size();
        while(ss>>t){
            yl[tt].push_back(t);
            qz[t].push_back(tt);
        }
    }
    in.close();
    in.open((tar+string("\\LS")).c_str());
    while(in>>t){
        al.insert(t);
    }
    in.close();
    in.open(string(string("./group/")+ver+string("/LS")).c_str());
    while(in>>t){
        gp.push_back(t);
    }
/*
--------------------------------------
help             获取指令列表
list             获取可用的mod列表
grouplist        获取可用的mod包列表
installed        获取已安装的mod
quit             退出
install xx       安装名为xx的mod及其前置
installgroup xx  安装名为xx的mod包
remove xx        移除名为xx的mod及其依赖
--------------------------------------
*/
    while(true){
        cin>>t;
        if(t=="quit"){
            ofstream out(tar.c_str()+string("\\LS"));
            for(auto iter=al.begin();iter!=al.end();iter++){
                out<<*iter<<endl;
            }
            return 0;
        }else if(t=="list"){
            ls();
        }else if(t=="grouplist"){
            gl();
        }else if(t=="installed"){
            id();
        }else if(t=="help"){
            help();
        }else if(t=="install"){
            cin>>tt;
            install(tt);
        }else if(t=="installgroup"){
            cin>>tt;
            ig(tt);
        }else if(t=="remove"){
            cin>>tt;
            rem(tt);
        }else if(t=="listgroup"){
            cin>>tt;
            lg(tt);
        }
    }
    return 0;
}
