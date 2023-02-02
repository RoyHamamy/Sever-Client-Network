#include "../include/Task.h"
Task::Task (ConnectionHandler* handler):_handler(handler),cv(){}
void Task::run(){
    std::vector<char> bytes;
    while (!_handler->getProt().shouldTerminate()) {
        if (!_handler->getLine(bytes)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        cv.notify_all();
    }
}
std::condition_variable &Task::getCv()  {
    return cv;
}

Task &Task::operator=(const Task &other) {
    return *this;
}

Task::Task(const Task &other):_handler(other._handler),cv() {
}

