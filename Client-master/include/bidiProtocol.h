//
//
//
#ifndef BIDIPROTOCOL_H
#define BIDIPROTOCOL_H
#include <string>
class bidiProtocol{
private:
    bool terminate_;
public:
    bidiProtocol();
    std::string cutString(int index, std::string message);
    void process(std::string message);
    bool shouldTerminate() const;
    void setTerminate(bool terminate);
};


#endif

