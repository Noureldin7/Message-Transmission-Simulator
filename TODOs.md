### DO NOT "CLEAN PROJECT" ... REMOVES THE CUSTOM MESSAGE IMPLEMENTATION
# EventMessage //34an @Noureldin7 ❤
### Purpose: Simulate Processing Delays, Timers
## Data members:
1. ### seqNum
2. ### eventType

<br/>

# SenderWindow (Not discussed yet)

### An object built around an array of data message pointers of fixed size (WS + 1), where out-of-window sequence numbers are null
## Data Members:
1. ### LowerEdge
2. ### UpperEdge
3. ### toBeSent
4. ### Messages

## Functions:
- ### DataMessage* getMsg(int seqNum) //returns NULL if not in queue
- ### void moveLowerEdge(DataMessage* msg) //if ack for first in queue moves lower edge, else no change, should auto extend window if possible
- ### int nextSeqNumToSend() // returns -1 if end of window reached
- ### void advanceSendingPointer() // circular-increment (toBeSent) if not at upper edge
- ### void setSendingPointer(int seqNum) //sets (toBeSent)

<br/>

# DataMessage (Done)
## Data members:
1. ### seqNum: Sequence Number
2. ### payload: after byte stuffing, wrapped with flags
3. ### trailer: Parity Byte (payload after byte stuffing)
4. ### frameType:
	- 0: Data
	- 1: Ack
	- 2: Nack
5. ### ackSeqNum: Ack Sequence Number

## Functions:
- ### Constructor(int SeqNum, string Msg)
- ### Constructor(int AckSeqNum, int Ack/Nack) //1 if Ack 2 if Nack
- ### string getPayload() //Gets Stripped Payload
- ### string getPayloadWithFraming() //Duh
- ### int getSeqNum() //gets ackSeqNum or SeqNum
- ### int getFrameType()
- ### int isValid() //returns bit index or -1 if no error