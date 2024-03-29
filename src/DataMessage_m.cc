//
// Generated file, do not edit! Created by nedtool 5.6 from DataMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "DataMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(DataMessage)

DataMessage::DataMessage(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->seqNum = 0;
    this->parity = 0;
    this->frameType = 0;
    this->ackSeqNum = 0;
}

DataMessage::DataMessage(int SeqNum, string Msg) : ::omnetpp::cPacket(nullptr,0)
{
    this->seqNum = SeqNum;
    string message_payload = Msg.substr(5);
    string message_control = Msg.substr(0, 4);
    this->setKind(stoi(message_control, NULL, 2));
    this->payload = frameMessage(message_payload);
    this->parity = calculateParity(this->payload.str());
    this->frameType = FrameType::Data;
    this->ackSeqNum = 0;
    this->setName(this->payload.c_str());
}

DataMessage::DataMessage(int SeqNum, int Type) : ::omnetpp::cPacket(nullptr,0)
{
    this->seqNum = 0;
    this->payload = "$$";
    this->parity = 0;
    this->frameType = Type;
    this->ackSeqNum = SeqNum;
    this->setKind(2-Type); //Will display Green for Ack Red for Nack
    this->setName(((Type==FrameType::Ack? "ACK ":"NACK ") + to_string(SeqNum)).c_str());
}

DataMessage::DataMessage(const DataMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

DataMessage::~DataMessage()
{
}

DataMessage& DataMessage::operator=(const DataMessage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void DataMessage::copy(const DataMessage& other)
{
    this->seqNum = other.seqNum;
    this->payload = other.payload;
    this->parity = other.parity;
    this->frameType = other.frameType;
    this->ackSeqNum = other.ackSeqNum;
    this->setKind(other.getKind());
    this->setName(other.getName());
}

string DataMessage::frameMessage(const string& Msg) const
{
    string out = "$";
    for (int i = 0; i < Msg.length(); i++){
        if (Msg[i] == '$' || Msg[i] == '/') out += '/';
        out += Msg[i];
    }
    out += "$";
    return out;
}

string DataMessage::stripMessage(const string& Msg) const
{
    string out;
    for (int i = 1; i < Msg.length() - 1; i++){
        if (Msg[i] == '/') i++;
        out += Msg[i];
    }
    return out;

}

char DataMessage::calculateParity(const string& Msg) const
{
    char out = 0;
    for (int i = 0; i < Msg.length(); i++){
        out ^= Msg[i];
    }
    return out;
}

void DataMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->seqNum);
    doParsimPacking(b,this->payload);
    doParsimPacking(b,this->parity);
    doParsimPacking(b,this->frameType);
    doParsimPacking(b,this->ackSeqNum);
}

void DataMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->seqNum);
    doParsimUnpacking(b,this->payload);
    doParsimUnpacking(b,this->parity);
    doParsimUnpacking(b,this->frameType);
    doParsimUnpacking(b,this->ackSeqNum);
}

int DataMessage::isValid() const
{
    char parity_check = 0;
    string payload = this->payload.str();
    for (int i = 0; i < payload.size(); i++){
        parity_check ^= payload[i];
    }
    for (int i = 0; i < 8; i++){
        if ((parity_check ^ this->parity) & (1 << i)) return i;
    }
    return -1;
}

int DataMessage::getSeqNum() const
{
    return (this->frameType) ? this->ackSeqNum : this->seqNum;
}

void DataMessage::setSeqNum(int seqNum)
{
    this->seqNum = seqNum;
}

string DataMessage::getPayload() const
{
    return stripMessage(this->payload.str());
}

string DataMessage::getPayloadWithFraming() const
{
    return this->payload.str();
}

void DataMessage::setPayload(string payload)
{
    this->payload = payload;
    this->setName(payload.c_str());
}

// TODO: Parity with or without modification?
char DataMessage::getParity() const
{
    // return this->parity;
    char parity_check = 0;
    string payload = this->payload.str();
    for (int i = 0; i < payload.size(); i++){
        parity_check ^= payload[i];
    }
    return parity_check;
}

void DataMessage::setParity(char parity)
{
    this->parity = parity;
}

int DataMessage::getFrameType() const
{
    return this->frameType;
}

void DataMessage::setFrameType(int frameType)
{
    this->frameType = frameType;
}

void DataMessage::setAckSeqNum(int ackSeqNum)
{
    this->ackSeqNum = ackSeqNum;
}

class DataMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    DataMessageDescriptor();
    virtual ~DataMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(DataMessageDescriptor)

DataMessageDescriptor::DataMessageDescriptor() : omnetpp::cClassDescriptor("DataMessage", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

DataMessageDescriptor::~DataMessageDescriptor()
{
    delete[] propertynames;
}

bool DataMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DataMessage *>(obj)!=nullptr;
}

const char **DataMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *DataMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int DataMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int DataMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *DataMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "seqNum",
        "payload",
        "parity",
        "frameType",
        "ackSeqNum",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int DataMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "seqNum")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "parity")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameType")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "ackSeqNum")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *DataMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "char",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **DataMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *DataMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int DataMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *DataMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DataMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSeqNum());
        case 1: return oppstring2string(pp->getPayload());
        case 2: return long2string(pp->getParity());
        case 3: return long2string(pp->getFrameType());
        case 4: return long2string(pp->getSeqNum());
        default: return "";
    }
}

bool DataMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setSeqNum(string2long(value)); return true;
        case 1: pp->setPayload((string)value); return true;
        case 2: pp->setParity(string2long(value)); return true;
        case 3: pp->setFrameType(string2long(value)); return true;
        case 4: pp->setAckSeqNum(string2long(value)); return true;
        default: return false;
    }
}

const char *DataMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *DataMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


