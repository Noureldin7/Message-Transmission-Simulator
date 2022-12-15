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
    messages = new DataMessage * [WS + 1];
    file.open(filepath,ifstream::in);
    string line;
    for (int i = 0; i <= WS; i++)
    {
        if(!getline(file,line))
        {
            break;
        }
        messages[i] = new DataMessage(line.c_str(), 0);
    }
}

void SenderWindow::init(int WS,string filepath)
{
    lowerEdge = 0;
    upperEdge = 0;
    toBeSent = 0;
    MAX_SEQ = WS + 1;
    messages = new DataMessage * [WS + 1];
    file.open(filepath,ifstream::in);
    string line;
    for (int i = 0; i <= WS; i++)
    {
        if(!getline(file,line))
        {
            break;
        }
        messages[i] = new DataMessage(line.c_str(), 0);
    }
}

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
    if(msg->getFrameType()==1)
    {
        if(msg->getSeqNum()==lowerEdge)
        {
            messages[lowerEdge]=NULL;
            lowerEdge = (lowerEdge + 1) % MAX_SEQ;
        }
        //Auto Extend If Possible
    }
}

void SenderWindow::advanceSendingPointer()
{
    if(toBeSent==upperEdge)
    {
        toBeSent = lowerEdge;
    }
    else
    {
        toBeSent = (toBeSent + 1) % MAX_SEQ;
    }
}


SenderWindow::~SenderWindow() {
    cout<<"Destructor call"<<endl;
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
    cout<<"Destructor end"<<endl;
}

