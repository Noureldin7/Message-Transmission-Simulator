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

#ifndef __PROJECT_NODE_H_
#define __PROJECT_NODE_H_

#include <omnetpp.h>
#include <string>
#include <iostream>

#include "SenderWindow.h"
using namespace omnetpp;
using std::string;

/**
 * TODO - Generated class
 */
enum TimerType{
    timeout = 1,
    processTime = 2
};
class Node : public cSimpleModule
{
  public:
    SenderWindow * senderWindow;
    ~Node();
  protected:
    int imSender;
    int isInit;
    int WS;
    double TO;
    double PT;
    double TD;
    double ED;
    double DD;
    double LP;
    cMessage ** timers;  // kind = 1 for timeout timer 2 for processing time
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
