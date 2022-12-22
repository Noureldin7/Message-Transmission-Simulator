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
    WS = getParentModule()->par("WS").intValue();
    TO = getParentModule()->par("TO").doubleValue();
    PT = getParentModule()->par("PT").doubleValue();
    TD = getParentModule()->par("TD").doubleValue();
    ED = getParentModule()->par("ED").doubleValue();
    DD = getParentModule()->par("DD").doubleValue();
    LP = getParentModule()->par("LP").doubleValue();
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    bool is_timeout = false;
    if(string(msg->getName())=="-1")
    {
        isInit = 0;
        senderWindow = NULL;
        timers = NULL;
//        cancelAndDelete(msg);
    }
    else if(isInit)
    {
        imSender = 1;
        isInit = 0;

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
        cMessage * mssg = new cMessage("",0);
        scheduleAt(simTime()+startTime, mssg);
//        cancelAndDelete(msg);
    }
    else
    {
        //Sending and Receiving Logic
        if(imSender)
        {
            DataMessage * message;
            if(!msg->isSelfMessage())
            {
                message = check_and_cast<DataMessage*>(msg);
                senderWindow->moveLowerEdge(message);
                cout<<"done"<<endl;
                int seq = message->getSeqNum();
                if(timers[seq]->isScheduled())
                {
                    cancelEvent(timers[seq]);
                }
//                cancelAndDelete(msg);
            }
            else
            {
                if(msg->getKind()==processTime)
                {
                    int seq = senderWindow->nextSeqNumToSend();
                    message = senderWindow->getMsg(seq);
                    cout<<seq<<endl;
                    int prefix = message->getKind();
                    bool delay = prefix & 0b0001;
//                    bool dup = prefix & 0b0010;
                    bool loss = prefix & 0b0100;
                    bool mod = prefix & 0b1000;
                    double delayValue = TD;
                    if(!loss)
                    {
                        if(delay)
                        {
                            delayValue+=ED;
                        }
//                        cout<<msg->getName()<<"===========";
                        if(msg->getName()[0]!='\0')
                        {
                            message = senderWindow->getMsg(atoi(msg->getName()));
                        }
                        message = new DataMessage(*message);
                        if(mod)
                        {
                            string temp = message->getPayloadWithFraming();
                            temp[1] = char(temp[1]^4);
                            message->setPayload(temp);
                        }
                        sendDelayed(message,delayValue,"outNode");
                    }
                    if(msg->getName()[0]=='\0')
                    {
                        senderWindow->advanceSendingPointer();
                    }
                    // Log 2
                    if(msg->getName()[0]!='\0')
                    {
                        cancelAndDelete(msg);
                        return;
                    }
//                    cancelAndDelete(msg);
                }

                if (msg->getKind() == timeout)
                {
                    is_timeout = true;
                    senderWindow->resetSendingPointer();
                    for (int i = 0; i <= WS; ++i)
                    {
                        if(timers[i]->isScheduled())
                        {
                            cancelEvent(timers[i]);
                        }
                    }
                    int seq = senderWindow->nextSeqNumToSend();
                    senderWindow->getMsg(seq)->setKind(0);
                    //CLEAR KIND, DISABLE TIMERS, RESET SENDING POINTER

                }
                int seq = senderWindow->nextSeqNumToSend();
                if(seq!=-1)
                {
                    // Log 3 with if condition
                    message = senderWindow->getMsg(seq);
                    int prefix = message->getKind();
                    bool dup = prefix & 0b0010;
                    if(dup)
                    {
                        scheduleAt(simTime() + PT + DD, new cMessage(to_string(seq).c_str(),processTime));
                    }
                    scheduleAt(simTime() + PT, new cMessage("",processTime));
                    // Log 1
                    if(timers[seq]->isScheduled())
                    {
                        cancelEvent(timers[seq]);
                    }
                    scheduleAt(simTime() + TO, timers[seq]);
                }
            }
        }
        else
        {
            DataMessage * message = check_and_cast<DataMessage*>(msg);
//            cout<<"Message after framing with error: " << message->getPayloadWithFraming()<<endl;
//            cout<<"Message is Valid? after error in bit 0: " << message->isValid()<<endl;
            if(message->isValid()==-1 && message->getSeqNum() == frameExpected)
            {
                message = new DataMessage(message->getSeqNum(),FrameType::Ack);
                frameExpected = (frameExpected + 1) % (WS + 1);
            }
            else
            {
                message = new DataMessage(message->getSeqNum(),FrameType::Nack);//nack here
            }
//            cout << "Response Frame Type: "<< message->getFrameType()<<endl;
//            cout << "Response Sequence Number: "<< message->getSeqNum()<<endl;
            send(message, "outNode");
            // Log 4
        }
    }
    if (!is_timeout)
    {
        cancelAndDelete(msg);
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
