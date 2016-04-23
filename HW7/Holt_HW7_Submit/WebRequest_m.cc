//
// Generated file, do not edit! Created by nedtool 4.6 from WebRequest.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WebRequest_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
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

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(WebRequest);

WebRequest::WebRequest(const char *name, int kind) : ::cMessage(name,kind)
{
    this->served_var = 0;
    this->startTime_var = 0;
    this->requestNumber_var = 0;
}

WebRequest::WebRequest(const WebRequest& other) : ::cMessage(other)
{
    copy(other);
}

WebRequest::~WebRequest()
{
}

WebRequest& WebRequest::operator=(const WebRequest& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void WebRequest::copy(const WebRequest& other)
{
    this->served_var = other.served_var;
    this->startTime_var = other.startTime_var;
    this->requestNumber_var = other.requestNumber_var;
}

void WebRequest::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->served_var);
    doPacking(b,this->startTime_var);
    doPacking(b,this->requestNumber_var);
}

void WebRequest::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->served_var);
    doUnpacking(b,this->startTime_var);
    doUnpacking(b,this->requestNumber_var);
}

bool WebRequest::getServed() const
{
    return served_var;
}

void WebRequest::setServed(bool served)
{
    this->served_var = served;
}

simtime_t WebRequest::getStartTime() const
{
    return startTime_var;
}

void WebRequest::setStartTime(simtime_t startTime)
{
    this->startTime_var = startTime;
}

int WebRequest::getRequestNumber() const
{
    return requestNumber_var;
}

void WebRequest::setRequestNumber(int requestNumber)
{
    this->requestNumber_var = requestNumber;
}

class WebRequestDescriptor : public cClassDescriptor
{
  public:
    WebRequestDescriptor();
    virtual ~WebRequestDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(WebRequestDescriptor);

WebRequestDescriptor::WebRequestDescriptor() : cClassDescriptor("WebRequest", "cMessage")
{
}

WebRequestDescriptor::~WebRequestDescriptor()
{
}

bool WebRequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<WebRequest *>(obj)!=NULL;
}

const char *WebRequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int WebRequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int WebRequestDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *WebRequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "served",
        "startTime",
        "requestNumber",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int WebRequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "served")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "startTime")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "requestNumber")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *WebRequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "simtime_t",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *WebRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int WebRequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    WebRequest *pp = (WebRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WebRequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    WebRequest *pp = (WebRequest *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getServed());
        case 1: return double2string(pp->getStartTime());
        case 2: return long2string(pp->getRequestNumber());
        default: return "";
    }
}

bool WebRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    WebRequest *pp = (WebRequest *)object; (void)pp;
    switch (field) {
        case 0: pp->setServed(string2bool(value)); return true;
        case 1: pp->setStartTime(string2double(value)); return true;
        case 2: pp->setRequestNumber(string2long(value)); return true;
        default: return false;
    }
}

const char *WebRequestDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *WebRequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    WebRequest *pp = (WebRequest *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


