//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __PROJECT_NODE_H_
#define __PROJECT_NODE_H_

#include <iostream>
#include <string>
#include <bitset>
#include <omnetpp.h>
#include "SenderWindow.h"
#include "DataMessage_m.h"
using namespace omnetpp;
using std::string;

/**
 * TODO - Generated class
 */
enum TimerType{
    timeout = 1,
    processTime = 2,
    duplicateProcessTime = 3
};
class Node : public cSimpleModule
{
  public:
    SenderWindow * senderWindow;
    ~Node();
  protected:
    int imSender;
    int isInit;
    int frameExpected;
    int WS;
    double TO;
    double PT;
    double TD;
    double ED;
    double DD;
    double LP;
    cMessage ** timers;  // kind = 1 for timeout timer 2 for processing time
    virtual void initialize();
    virtual void initializeRoutine(cMessage *msg);
    virtual string constructLog1Message(int error_code);
    virtual string constructLog2Message(bool sent, int seq_num, string payload, char parity, int isValid, int error_code, bool isSecondDuplicate);
    virtual string constructLog3Message(int seq_num);
    virtual string constructLog4Message(FrameType type, int seq_num, bool isLost);
    virtual bool senderProcessMessage(cMessage *msg);
    virtual void scheduleNextMessage(cMessage *msg);
    virtual void senderLogic(cMessage *msg);
    virtual void receiverLogic(cMessage *msg);
    virtual void handleMessage(cMessage *msg);
};

#endif
