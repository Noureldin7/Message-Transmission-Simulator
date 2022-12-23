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

#include "Node.h"
#include "DataMessage_m.h"
#include <iostream>
#include <string>
using namespace std;
Define_Module(Node);

void Node::initialize()
{
    // TODO - Generated method body
    imSender = 0;
    isInit = 1;
    frameExpected = 0;
    senderWindow = NULL;
    timers = NULL;
    WS = getParentModule()->par("WS").intValue();
    TO = getParentModule()->par("TO").doubleValue();
    PT = getParentModule()->par("PT").doubleValue();
    TD = getParentModule()->par("TD").doubleValue();
    ED = getParentModule()->par("ED").doubleValue();
    DD = getParentModule()->par("DD").doubleValue();
    LP = getParentModule()->par("LP").doubleValue();
}

void Node::initializeRoutine(cMessage *msg)
{
    isInit = 0;
    if(string(msg->getName())!="-1") //imSender
    {
        imSender = 1;

        string filepath = "../texts/inputx.txt";
        char index = par("Index").stringValue()[0];
        filepath[14] = index;

        senderWindow = new SenderWindow(WS,filepath);
        timers = new cMessage*[WS + 1];
        for (int i = 0; i <= WS; ++i)
        {

            timers[i] = new cMessage(to_string(i).c_str(),timeout);
        }

        int startTime = atoi(msg->getName());
        scheduleAt(simTime()+startTime, new cMessage("",0));
    }
    cancelAndDelete(msg);
}

// Processes send request according to the four control bits
// Returns whether the message processed was a second duplicate
bool Node::senderProcessMessage(cMessage *msg)
{
    int seq = senderWindow->nextSeqNumToSend();
    DataMessage* message;
    bool isSecondDuplicate = false;
    if(msg->getName()[0]=='\0') //if the message is not a second duplicate
    {
        message = senderWindow->getMsg(seq);
        senderWindow->advanceSendingPointer();
    }
    else
    {
        isSecondDuplicate = true;
        message = senderWindow->getMsg(atoi(msg->getName()));
        cancelAndDelete(msg);
    }
    int prefix = message->getKind();
    bool delay = prefix & 0b0001;
    bool loss = prefix & 0b0100;
    bool mod = prefix & 0b1000;
    double delayValue = TD + (delay ? ED : 0);
    // Log 2
    if (!loss)
    {
        message = new DataMessage(*message);
        if(mod)
        {
            string temp = message->getPayloadWithFraming();
            temp[1] = char(temp[1]^4); //Add randomness?
            message->setPayload(temp);
        }
        sendDelayed(message,delayValue,"outNode");
    }
    return isSecondDuplicate;
}

void Node::scheduleNextMessage(cMessage *msg)
{
    int seq = senderWindow->nextSeqNumToSend();
    if (msg->getKind() == timeout)
    {
        senderWindow->resetSendingPointer();
        for (int seqNum = 0; seqNum <= WS; ++seqNum)
        {
            if(timers[seqNum] == msg)
            {
                // Log 3
            }
            if(timers[seqNum]->isScheduled())
            {
                cancelEvent(timers[seqNum]);
            }
        }
        seq = senderWindow->nextSeqNumToSend();
        senderWindow->getMsg(seq)->setKind(0);
    }
    if(seq!=-1)
    {
        DataMessage* message = senderWindow->getMsg(seq);
        int prefix = message->getKind();
        bool dup = prefix & 0b0010;
        if(dup)
        {
            scheduleAt(simTime() + PT + DD, new cMessage(to_string(seq).c_str(),processTime));
        }
        scheduleAt(simTime() + PT, new cMessage("",processTime));
        if(timers[(seq + 1) % (WS + 1)]->isScheduled())
        {
            cancelEvent(timers[(seq + 1) % (WS + 1)]);
        }
        scheduleAt(simTime() + TO, timers[(seq + 1) % (WS + 1)]);
        // Log 1
    }

    if (msg->getKind() != timeout)
    {
        cancelAndDelete(msg);
    }
}

void Node::senderLogic(cMessage *msg)
{
    if (!msg->isSelfMessage()) //If the message is from the receiver (Ack or Nack)
    {
        DataMessage* message = check_and_cast<DataMessage*>(msg);
        senderWindow->moveLowerEdge(message);
        int seq = message->getSeqNum();
        if(timers[seq]->isScheduled() && message->getFrameType() == FrameType::Ack)
        {
            cancelEvent(timers[seq]);
        }
        cancelAndDelete(msg);
        return;
    }
    //If the message is a control message
    if(msg->getKind()==processTime && senderProcessMessage(msg))
    {
        return;
    }
    scheduleNextMessage(msg);
}

void Node::receiverLogic(cMessage *msg)
{
    if (!msg->isSelfMessage())
    {
        scheduleAt(simTime() + PT, msg);
        return;
    }
    DataMessage * message = check_and_cast<DataMessage*>(msg);
    if(message->isValid()==-1 && message->getSeqNum() == frameExpected)
    {
        // Log 4
        frameExpected = (frameExpected + 1) % (WS + 1);
        message = new DataMessage(frameExpected,FrameType::Ack);
    }
    else
    {
        // Log 4
        message = new DataMessage(frameExpected,FrameType::Nack);
    }
    sendDelayed(message, TD, "outNode");
    cancelAndDelete(msg);
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(isInit)
    {
        initializeRoutine(msg);
        return;
    }
    //Sending and Receiving Logic
    if(imSender)
    {
        senderLogic(msg);
    }
    else
    {
        receiverLogic(msg);
    }
}



Node::~Node() {
    if(senderWindow)
    {
        for (int i = 0; i <= WS; ++i)
        {
            cancelAndDelete(timers[i]);
        }
        delete[] timers;
        delete senderWindow;
    }
}
