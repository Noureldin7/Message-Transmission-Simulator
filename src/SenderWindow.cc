/*
 * SenderWindow.cc
 *
 *  Created on: Dec 12, 2022
 *      Author: noure
 */

#include "SenderWindow.h"

SenderWindow::SenderWindow(int WS, string filepath) {
    lowerEdge = 0;
    upperEdge = -1;
    toBeSent = 0;
    MAX_SEQ = WS;
    messages = new DataMessage * [MAX_SEQ];
    file.open(filepath,ifstream::in);
    string line;
    for (int i = 0; i < WS; i++)
    {
        if(!getline(file,line))
        {
            messages[i] = NULL;
            continue;
        }
        messages[i] = new DataMessage(++upperEdge,line.c_str());
    }
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
    toBeSent = 0;
}

bool SenderWindow::isBetween(int a, int b, int c) // a <=c < b
{
    // return (((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a)));
    return (((a <= b) && (b <= c)) || ((c < a) && (a <= b)) || ((b <= c) && (c < a)));
}

int SenderWindow::nextSeqNumToSend()
{
    if (!messages[lowerEdge]) return -1;
    return (isBetween(lowerEdge, (lowerEdge + toBeSent) % MAX_SEQ, upperEdge) && toBeSent < MAX_SEQ) ? ((lowerEdge + toBeSent) % MAX_SEQ) : -1;
}

void SenderWindow::moveLowerEdge(DataMessage * msg)
{
    if(msg->getFrameType()==FrameType::Ack)
    {
        if(msg->getSeqNum()==(lowerEdge + 1) % MAX_SEQ)
        {
            delete messages[lowerEdge];
            messages[lowerEdge]=NULL;
            lowerEdge = (lowerEdge + 1) % MAX_SEQ;
            string line;
            if(getline(file,line))
            {
                upperEdge = (upperEdge + 1) % MAX_SEQ;
                messages[upperEdge] = new DataMessage(upperEdge,line.c_str()); //tbc
            }
            toBeSent--;
        }
    }
}

void SenderWindow::advanceSendingPointer()
{
    if(isBetween(lowerEdge, (lowerEdge + toBeSent) % MAX_SEQ, upperEdge) && toBeSent < MAX_SEQ)
    {
        toBeSent++;
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

