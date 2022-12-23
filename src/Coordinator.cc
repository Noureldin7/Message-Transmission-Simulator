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

#include "Coordinator.h"
using namespace std;
Define_Module(Coordinator);

string Coordinator::readInput(string filepath)
{
    ifstream file;
    string line;
    file.open(filepath,ifstream::in);
    getline(file,line);
    file.close();
    return line;
}

void Coordinator::initialize()
{
    string input = readInput("../texts/coordinator.txt");
    string startingNode = "out";
    startingNode += input[0];
    string startTime = input.substr(2);
    cMessage * msg0 = new cMessage("-1");
    cMessage * msg1 = new cMessage(startTime.c_str());
    if(input[0]=='0')
    {
        msg0->setName(startTime.c_str());
        msg1->setName("-1");
    }
    send(msg0,"out0");
    send(msg1,"out1");
}

void Coordinator::handleMessage(cMessage *msg)
{

}
