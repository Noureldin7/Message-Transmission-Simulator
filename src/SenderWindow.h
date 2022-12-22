/*
 * SenderWindow.h
 *
 *  Created on: Dec 12, 2022
 *      Author: noure
 */

#ifndef SENDERWINDOWS_H_
#define SENDERWINDOWS_H_

#include <omnetpp.h>
#include <fstream>
#include <iostream>
#include "DataMessage_m.h"
using namespace omnetpp;
using std::ifstream;
using std::cout;

class SenderWindow {
private:
    int MAX_SEQ;
    int lowerEdge;
    int upperEdge;
    int toBeSent;
    ifstream file;
    DataMessage ** messages;


public:
    void init(int WS, string filepath);
    DataMessage * getMsg(int seqNum);
    void moveLowerEdge(DataMessage * msg);
    int nextSeqNumToSend();
    void advanceSendingPointer();
    void resetSendingPointer();
    SenderWindow(int WS, string filepath);
    ~SenderWindow();
};

#endif /* SENDERWINDOWS_H_ */
