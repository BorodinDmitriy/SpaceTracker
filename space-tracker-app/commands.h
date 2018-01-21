#ifndef COMMANDS_H
#define COMMANDS_H

#include "controller.h"
#include "information.h"

class Command {
public:
    virtual void run(Controller &controller)=0;
};

class AddInformationCommand : public Command {
protected:
    const Information newItem;
    QDateTime dateTime;
public:
    AddInformationCommand(const Information item, QDateTime date) { newItem = item; dateTime = date; }
    ~AddInformationCommand() {}
    void run(Controller &controller) {
        controller.addInformation(newItem,date);
    }
};

class AddInformationOnTableCommand : public Command {
protected:
    QDateTime dateTime;
public:
    AddInformationOnTableCommand(QDateTime date) { dateTime = date; }
    ~AddInformationOnTableCommand() {}
    void run(Controller &controller) {
        controller.addInformationOnTable(date);
    }
};

class CheckTraceCommand : public Command {
protected:
    const int X;
    const int Y;
public:
    CheckTraceCommand(const int x, const int y) { X = x; Y = y; }
    ~CheckTraceCommand() {}
    void run(Controller &controller) {
        controller.checkTrace(X,Y);
    }
};

class GetFormTleCommand : public Command {
protected:
    GetFormTleCommand dateTime;
public:
    GetFormTleCommand(QDateTime date) { dateTime = date; }
    ~GetFormTleCommand() {}
    void run(Controller &controller) {
        controller.getFormTLE(date);
    }
};


#endif // COMMANDS_H
