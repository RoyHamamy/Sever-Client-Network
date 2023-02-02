#define SPL3_BIDIPROTOCOL_H
#include <string>
#include <iostream>
#include "../include/bidiProtocol.h"
bidiProtocol::bidiProtocol(): terminate_(false){}
std::string bidiProtocol::cutString(int index, std::string str){
    std::string ans;
    int len = str.length();
    while(index < len && str.at(index) != '\0'){
        ans += str.at(index);
        index++;
    }
    return ans;
}


void bidiProtocol::process(std::string message){
    std::cout<<message + " This is the message"<<std::endl;
    int index;
    std::string opcode;
    if(message.at(0) == '1') {
        opcode = message.substr(0, 2);
        index = 2;
    }
    else{
        opcode = message.at(0);
        index = 1;
    }
    //Notification
    if(opcode == "9"){
        char notifType = message.at(1);
        index=index + 1;
        std::string postingUsername = cutString(index, message);
        index += postingUsername.size() + 1;
        std::string content = cutString(index, message);
        std::string messageType;
        if(notifType =='0'){
            messageType = "PM";
        }
        else{
            messageType = "Public";
        }
        std::cout<<("NOTIFICATION " + messageType + " " + postingUsername + " " +content)<<std::endl;
    }
    //ACK
    else if(opcode == "10"){
        std::string messageOpcode;
        messageOpcode = message.at(2);
        std::cout<<messageOpcode<<std::endl;
        index ++;
        int messageLength = message.length();
        if(messageOpcode == "1"){
            if(index < messageLength && message.at(index) =='2'){
                messageOpcode += message.at(index);
                index++;
            }
        }
        if (messageOpcode == "3"){
            terminate_=true;
        }
        std::string optional;
        if(index < messageLength){
            optional = message.substr(index);
        }
        std::cout<<("ACK " + messageOpcode + " " + optional)<<std::endl;
    }
    //ERROR
    else if(opcode == "11"){
        std::string errMsg;
        errMsg = message.substr(2);
        std::cout<<("ERROR " + errMsg)<<std::endl;
    }
    std::cout<<shouldTerminate()<<std::endl;
}

bool bidiProtocol::shouldTerminate()const {
    return terminate_;
}


void bidiProtocol::setTerminate(bool ter){
    terminate_ = ter;
}


