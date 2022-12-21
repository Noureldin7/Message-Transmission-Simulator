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

//int Node::readMessages(string filepath)
//{
//    // TODO - Generated method body
//    ifstream file;
//    string line;
//    int i = 0;
//    file.open(filepath,ifstream::in);
//    while(getline(file,line))
//    {
//        prefixbuffer[i] = line.substr(0, 4);
//        msgbuffer[i] = line.substr(5);
//        i++;
//    }
//    file.close();
//    return i;
//}
void Node::initialize()
{
    // TODO - Generated method body
    imSender = 0;
    isInit = 1;
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(string(msg->getName())=="-1")
    {
        isInit = 0;
        senderWindow = NULL;
    }
    else if(isInit)
    {
        imSender = 1;
        isInit = 0;
        string filepath = "../texts/inputx.txt";
        char index = par("Index").stringValue()[0];
        filepath[14] = index;
        senderWindow = new SenderWindow(getParentModule()->par("WS").intValue(),filepath);
        int startTime = atoi(msg->getName());
        cMessage * mssg = new cMessage();
        scheduleAt(simTime()+startTime, mssg);
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
            }
            int seq = senderWindow->nextSeqNumToSend();
            if(seq!=-1)
            {
                message = new DataMessage(*(senderWindow->getMsg(seq)));
                message->setPayload(char(message->getPayloadWithFraming()[0] ^ char(16)) + message->getPayloadWithFraming().substr(1));
                cout<<"Message without framing: " << message->getPayload()<<endl;
                send(message,"outNode");
                senderWindow->advanceSendingPointer();
            }
//              DataMessage* message = new DataMessage(69, string("A$/"));
//              cout<<"Message after framing: " << message->getPayloadWithFraming()<<endl;
//              cout<<"Message SequenceNumber: " << message->getSeqNum()<<endl;
//              cout<<"Message frame type: " << message->getFrameType()<<endl;
//              cout<<"Message is Valid? : " << message->isValid()<<endl;
        }
        else{
            DataMessage * message = check_and_cast<DataMessage*>(msg);
            cout<<"Message after framing with error: " << message->getPayloadWithFraming()<<endl;
            cout<<"Message is Valid? after error in bit 0: " << message->isValid()<<endl;
            if(message->isValid()==-1)
            {
                message = new DataMessage(message->getSeqNum(),"Ack");
                message->setFrameType(1);
            }
            else
            {
                message = new DataMessage(message->getSeqNum(),"Nack");
                message->setFrameType(2);
            }
            cout << "Response Frame Type: "<< message->getFrameType()<<endl;
            cout << "Response Sequence Number: "<< message->getSeqNum()<<endl;
            send(message, "outNode");
        }
    }
    cancelAndDelete(msg);
}



Node::~Node() {
    cout<<"Destructor Node"<<endl;
    if(senderWindow)
    {
        delete senderWindow;
    }
    cout<<"Destructor Node end"<<endl;
}
