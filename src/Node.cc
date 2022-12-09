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
using namespace std;
Define_Module(Node);

int Node::readMessages(string filepath)
{
    // TODO - Generated method body
    ifstream file;
    string line;
    int i = 0;
    file.open(filepath,ifstream::in);
    while(getline(file,line))
    {
        prefixbuffer[i] = line.substr(0, 4);
        msgbuffer[i] = line.substr(5);
        i++;
    }
    return i;
}
void Node::initialize()
{
    // TODO - Generated method body
    imSender = 0;
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    cGate* port = msg->getArrivalGate();
    if(string(port->getName())=="inCoord")
    {
        imSender = 1;
        string filepath = "../texts/inputx.txt";
        char index = par("Index").stringValue()[0];
        filepath[14] = index;
        cout<<filepath<<endl;
        int i = readMessages(filepath);
        for(int j = 0; j < i; j++)
        {
            cout<<msgbuffer[j]<<endl;
        }
    }
    else
    {
        //Sending and Receiving Logic
    }
}
