#include "../include/encoderDecoder.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <iostream>

encoderDecoder::encoderDecoder() {
}

std::vector<char> encoderDecoder::encode(std::string msg) const {
    std::stringstream s(msg);
    std::vector<std::string> ans;
    std::vector<char> byte;
    std::string tmp;
    short opcode;
    char opbyte [2];
    int i =0;
    while (getline(s,tmp,' ')){
        ans.push_back(tmp);
        if (ans[0] == "POST" || (ans[0] == "PM" && i==1))
            break;
        i++;
    }
    while (ans.size()<7)
        ans.push_back("");
    if (ans[0]=="REGISTER"){
        opcode =1;
        shortToBytes(opcode,opbyte);
        byte.push_back(opbyte[0]);
        byte.push_back(opbyte[1]);
        std::string userName = ans[1];
        for (char c : userName){
            byte.push_back(c);
        }
        byte.push_back('\0');
        std::string pass = ans[2];
        for (char c : pass){
            byte.push_back(c);
        }
        byte.push_back('\0');
        std::string birthday = ans[3];
        for (char c : birthday){
            byte.push_back(c);
        }
        byte.push_back('\0');
//        ans[2]=zero;
//        ans[3]=pass;
//        ans[4]=zero;
//        ans[5]=birthday;
//        ans[6]=zero;
    }

    else if (ans[0] == "LOGIN"){
        opcode =2;
        shortToBytes(opcode,opbyte);
        byte.push_back(opbyte[0]);
        byte.push_back(opbyte[1]);
        std::string userName = ans[1];
        std::string pass = ans[2];
        std::string captcha = ans[3];
        for (char c : userName){
            byte.push_back(c);
        }
        byte.push_back('\0');
        for (char c : pass){
            byte.push_back(c);
        }
        byte.push_back('\0');
        for (char c : captcha){
            byte.push_back(c);
        }
//        ans[1]=userName;
//        ans[2]=zero;
//        ans[3]=pass;
//        ans[4]=zero;
//        ans[5]=captcha;
    }
    else if (ans[0] == "LOGOUT"){
        opcode =3;
        shortToBytes(opcode,opbyte);
        byte.push_back(opbyte[0]);
        byte.push_back(opbyte[1]);
        // nothing;
    }
    else if (ans[0]=="FOLLOW"){
        opcode =4;
        shortToBytes(opcode,opbyte);
        byte.push_back(opbyte[0]);
        byte.push_back(opbyte[1]);
        std::string follow = ans[1];
        std::string userName = ans[2];
        for (char c : follow){
            byte.push_back(c);
        }
        for (char c : userName){
            byte.push_back(c);
        }
        byte.push_back('\0');
//        ans[1]=follow;
//        ans[2]=userName;
//        ans[3]=zero;
    }
    else if (ans[0]=="POST"){
        opcode =5;
        shortToBytes(opcode,opbyte);
        byte.push_back(opbyte[0]);
        byte.push_back(opbyte[1]);
        std::string content = msg.substr(5);
        for (char c : content){
            byte.push_back(c);
        }
        byte.push_back('\0');
//        ans[1]= content;
//        ans[2]=zero;
    }
    else if (ans[0]=="PM") {
        opcode =6;
        shortToBytes(opcode,opbyte);
        byte.push_back(opbyte[0]);
        byte.push_back(opbyte[1]);
        std::string userName = ans[1];
        std::string content=msg.substr(4+ans[1].length());
        for (char c : userName){
            byte.push_back(c);
        }
        byte.push_back('\0');
        for (char c : content){
            byte.push_back(c);
        }
        byte.push_back('\0');
//        ans[1]=userName;
//       ans[2]=zero;
//      ans[3]=content;
//       ans[4]=zero;
//        auto t = std::time(nullptr);
//        auto tm = *std::localtime(&t);
//        std::ostringstream oss;
//        oss << std::put_time(&tm, "%d-%m-%Y %H:%M");
//        std::string str = oss.str();
//        for (char c : str){
//            byte.push_back(c);
//        }
//        byte.push_back('\0');

//        ans[6]=zero;
    }
    else if (ans[0] == "LOGSTAT"){
        opcode =7;
        shortToBytes(opcode,opbyte);
        byte.push_back(opbyte[0]);
        byte.push_back(opbyte[1]);
    }
    else if (ans[0]=="STAT"){
        opcode =8;
        shortToBytes(opcode,opbyte);
        byte.push_back(opbyte[0]);
        byte.push_back(opbyte[1]);
        std::string listOfStrings = ans[1];
        for (char c : listOfStrings){
            byte.push_back(c);
        }
        byte.push_back('\0');
    }
    else if (ans[0] == "BLOCK"){
        opcode =12;
        shortToBytes(opcode,opbyte);
        byte.push_back(opbyte[0]);
        byte.push_back(opbyte[1]);
        std::string userName=ans[1];
        for (char c : userName){
            byte.push_back(c);
        }
        byte.push_back('\0');
    }
    return byte;
}

void encoderDecoder::shortToBytes(short num, char *bytesArr) const {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}
short encoderDecoder::bytesToShort(char* bytesArr)
{
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}
std::string encoderDecoder::decode(std::vector<char> bytes) {
    char getBytes[2];
    std::string ans;
    getBytes[0] = bytes[0];
    getBytes[1] = bytes[1];
    short opcode = bytesToShort(getBytes);
    std::string strOpcode = std::to_string(opcode);
    ans.append(strOpcode);
    //notification
    if (opcode == 9) {
        short shortByte = bytes[2];
        ans.append(std::to_string(shortByte));
        int index = 3;
        char currByte = bytes[index];
        while (currByte != '\0') {
            ans.push_back(currByte);
            index++;
            currByte = bytes[index];
        }
        ans.push_back(' ');
        index++;
        currByte = bytes[index];
        while (currByte != '\0') {
            ans.push_back(currByte);
            index++;
            currByte = bytes[index];
        }
        ans.push_back('\0');
    }
        //ack
    else if (opcode == 10) {
        int size = bytes.size();
        int index = 4;
        char newBytes[2];
        newBytes[0] = bytes[2];
        newBytes[1] = bytes[3];
        short messageOpcode = bytesToShort(newBytes);
        std::string stringMessageOpcode = std::to_string(messageOpcode);
        ans.append(stringMessageOpcode);
        //follow
        if (messageOpcode == 4) {
            for (int i = index; i < size - 1; i++) {
                char charByte = bytes[i];
                ans.push_back(charByte);
            }
        }
        //logstat
        else if (messageOpcode == 7) {
            std::cout<<"message size is " + std::to_string(size)<<std::endl;
            while(index<size-1){
                for(int j=0; j<8;j+=2){
                    char input[2];
                    input[0] = bytes.at(index+j);
                    input[1] = bytes.at(index +j +1);
                    short shortInput = bytesToShort(input);
                    ans.append(std::to_string(shortInput));
                    ans.append(" ");
                }
                index +=8;
            }
        }
        //stat
        else if (messageOpcode == 8) {
            std::cout<<"message size is " + std::to_string(size)<<std::endl;
            while(index<size-1){
                for(int j=0; j<8;j+=2){
                    char input[2];
                    input[0] = bytes.at(index+j);
                    input[1] = bytes.at(index +j +1);
                    short shortInput = bytesToShort(input);
                    ans.append(std::to_string(shortInput));
                    ans.append(" ");
                }
                index +=8;
            }
        }
        return ans;
    }
            //error
        else if (opcode == 11) {
            char newBytes[2];
            newBytes[0] = bytes[2];
            newBytes[1] = bytes[3];
            short messageOpcode = bytesToShort(newBytes);
            std::string stringMessageOpcode = std::to_string(messageOpcode);
            ans.append(stringMessageOpcode);
        }
        return ans;
}