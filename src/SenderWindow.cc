/*
 * SenderWindow.cc
 *
 *  Created on: Dec 12, 2022
 *      Author: noure
 */

#include "SenderWindow.h"

SenderWindow::SenderWindow(int WS, string filepath) {
    lowerEdge = 0;
    upperEdge = 0;
    toBeSent = 0;
    MAX_SEQ = WS;
    messages = new DataMessage * [MAX_SEQ + 1];
    file.open(filepath,ifstream::in);
    string line;
    for (int i = 0; i < WS; i++)
    {
        if(!getline(file,line))
        {
            messages[i] = NULL;
            continue;
        }
        messages[i] = new DataMessage(upperEdge++,line.c_str());
    }
    messages[MAX_SEQ] = NULL;
}

DataMessage * SenderWindow::getMsg(int seqNum)
{
    if(seqNum==-1)
    {
        return NULL;
    }
    return messages[seqNum];
}

void SenderWindow::resetSendingPointer()
{
    toBeSent = lowerEdge;
}

int SenderWindow::nextSeqNumToSend()
{
    return toBeSent==upperEdge?-1:toBeSent;
}

void SenderWindow::moveLowerEdge(DataMessage * msg)
{
//    if(msg->getFrameType()==FrameType::Ack)
//    {
    int tempSeq = msg->getSeqNum();
    int tempLowerEdge = lowerEdge;
    while(tempSeq!=tempLowerEdge)
    {
        tempSeq = (tempSeq + MAX_SEQ) % (MAX_SEQ + 1);
        delete messages[tempSeq];
        messages[tempSeq]=NULL;
        lowerEdge = (lowerEdge + 1) % (MAX_SEQ + 1);
        string line;
        if(getline(file,line))
        {
            messages[upperEdge] = new DataMessage(upperEdge,line.c_str()); //tbc
            upperEdge = (upperEdge + 1) % (MAX_SEQ + 1);
        }
    }
//    }
}

void SenderWindow::advanceSendingPointer()
{
    if(toBeSent!=upperEdge)
    {
        toBeSent = (toBeSent + 1) % (MAX_SEQ + 1);
    }
}


SenderWindow::~SenderWindow() {
    if(file.is_open())
    {
        file.close();
    }
    for (int i = 0; i <= MAX_SEQ; ++i) {
        if(messages[i])
        {
            delete messages[i];
        }
    }
    delete[] messages;
}

