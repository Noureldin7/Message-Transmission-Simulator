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
    return line;
}

void Coordinator::initialize()
{
    // TODO - Generated method body
    string input = readInput("../texts/coordinator.txt");
    string startingNode = "out";
    startingNode += input[0];
    string startTime = input.substr(2);
    cMessage * msg = new cMessage(startTime.c_str());
    send(msg,startingNode.c_str());
}

void Coordinator::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}
