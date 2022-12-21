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
    MAX_SEQ = WS + 1;
    messages = new DataMessage * [MAX_SEQ];
    file.open(filepath,ifstream::in);
    string line;
    for (int i = 0; i <= WS; i++)
    {
        if(!getline(file,line))
        {
            messages[i] = NULL;
            continue;
        }
        messages[i] = new DataMessage(upperEdge++,line.c_str());
    }
    //messages[MAX_SEQ] = NULL;
}

//void SenderWindow::init(int WS,string filepath)
//{
//    lowerEdge = 0;
//    upperEdge = 0;
//    toBeSent = 0;
//    MAX_SEQ = WS + 1;
//    messages = new DataMessage * [WS + 1];
//    file.open(filepath,ifstream::in);
//    string line;
//    for (int i = 0; i <= WS; i++)
//    {
//        if(!getline(file,line))
//        {
//            messages[i] = NULL;
//            continue;
//        }
//        messages[i] = new DataMessage(line.c_str(), 0);
//    }
//}

DataMessage * SenderWindow::getMsg(int seqNum)
{
    return messages[seqNum];
}

void SenderWindow::setSendingPointer(int seqNum)
{
    toBeSent = seqNum;
}

int SenderWindow::nextSeqNumToSend()
{
    if(lowerEdge == upperEdge)
    {
        return -1;
    }
    return toBeSent;
}

void SenderWindow::moveLowerEdge(DataMessage * msg)
{
    if(msg->getFrameType()==FrameType::Ack)
    {
        if(msg->getSeqNum()==lowerEdge)
        {
            delete messages[lowerEdge];
            messages[lowerEdge]=NULL;
            lowerEdge = (lowerEdge + 1) % (MAX_SEQ + 1);
            string line;
            if(getline(file,line))
            {
                messages[upperEdge] = new DataMessage(upperEdge,line.c_str()); //tbc
                upperEdge = (upperEdge + 1) % (MAX_SEQ + 1);
            }
        }
    }
}

void SenderWindow::advanceSendingPointer()
{
    toBeSent = (toBeSent + 1) % (MAX_SEQ + 1);
    if(toBeSent==upperEdge)
    {
        toBeSent = lowerEdge;
    }
}


SenderWindow::~SenderWindow() {
    if(file.is_open())
    {
        file.close();
    }
    for (int i = 0; i < MAX_SEQ; ++i) {
        if(messages[i])
        {
            delete messages[i];
        }
    }
    delete[] messages;
}

