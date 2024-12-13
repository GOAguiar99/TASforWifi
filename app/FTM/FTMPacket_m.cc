//
// Generated file, do not edit! Created by opp_msgtool 6.1 from inet/applications/FTM/FTMPacket.msg.
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
#include <memory>
#include <type_traits>
#include "FTMPacket_m.h"

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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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

namespace inet {

Register_Class(FTMApplicationPacket)

FTMApplicationPacket::FTMApplicationPacket() : ::inet::FieldsChunk()
{
}

FTMApplicationPacket::FTMApplicationPacket(const FTMApplicationPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

FTMApplicationPacket::~FTMApplicationPacket()
{
}

FTMApplicationPacket& FTMApplicationPacket::operator=(const FTMApplicationPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void FTMApplicationPacket::copy(const FTMApplicationPacket& other)
{
    this->sequenceNumber = other.sequenceNumber;
    this->clockTime1 = other.clockTime1;
    this->clockTime2 = other.clockTime2;
    this->clockTime3 = other.clockTime3;
}

void FTMApplicationPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->clockTime1);
    doParsimPacking(b,this->clockTime2);
    doParsimPacking(b,this->clockTime3);
}

void FTMApplicationPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->clockTime1);
    doParsimUnpacking(b,this->clockTime2);
    doParsimUnpacking(b,this->clockTime3);
}

uint32_t FTMApplicationPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void FTMApplicationPacket::setSequenceNumber(uint32_t sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

clocktime_t FTMApplicationPacket::getClockTime1() const
{
    return this->clockTime1;
}

void FTMApplicationPacket::setClockTime1(clocktime_t clockTime1)
{
    handleChange();
    this->clockTime1 = clockTime1;
}

clocktime_t FTMApplicationPacket::getClockTime2() const
{
    return this->clockTime2;
}

void FTMApplicationPacket::setClockTime2(clocktime_t clockTime2)
{
    handleChange();
    this->clockTime2 = clockTime2;
}

clocktime_t FTMApplicationPacket::getClockTime3() const
{
    return this->clockTime3;
}

void FTMApplicationPacket::setClockTime3(clocktime_t clockTime3)
{
    handleChange();
    this->clockTime3 = clockTime3;
}

class FTMApplicationPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sequenceNumber,
        FIELD_clockTime1,
        FIELD_clockTime2,
        FIELD_clockTime3,
    };
  public:
    FTMApplicationPacketDescriptor();
    virtual ~FTMApplicationPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(FTMApplicationPacketDescriptor)

FTMApplicationPacketDescriptor::FTMApplicationPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::FTMApplicationPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

FTMApplicationPacketDescriptor::~FTMApplicationPacketDescriptor()
{
    delete[] propertyNames;
}

bool FTMApplicationPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FTMApplicationPacket *>(obj)!=nullptr;
}

const char **FTMApplicationPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FTMApplicationPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FTMApplicationPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int FTMApplicationPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        0,    // FIELD_clockTime1
        0,    // FIELD_clockTime2
        0,    // FIELD_clockTime3
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *FTMApplicationPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sequenceNumber",
        "clockTime1",
        "clockTime2",
        "clockTime3",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int FTMApplicationPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "clockTime1") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "clockTime2") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "clockTime3") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *FTMApplicationPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_sequenceNumber
        "inet::clocktime_t",    // FIELD_clockTime1
        "inet::clocktime_t",    // FIELD_clockTime2
        "inet::clocktime_t",    // FIELD_clockTime3
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **FTMApplicationPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FTMApplicationPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FTMApplicationPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FTMApplicationPacket *pp = omnetpp::fromAnyPtr<FTMApplicationPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FTMApplicationPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FTMApplicationPacket *pp = omnetpp::fromAnyPtr<FTMApplicationPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FTMApplicationPacket'", field);
    }
}

const char *FTMApplicationPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FTMApplicationPacket *pp = omnetpp::fromAnyPtr<FTMApplicationPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FTMApplicationPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FTMApplicationPacket *pp = omnetpp::fromAnyPtr<FTMApplicationPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        case FIELD_clockTime1: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getClockTime1()));
        case FIELD_clockTime2: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getClockTime2()));
        case FIELD_clockTime3: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getClockTime3()));
        default: return "";
    }
}

void FTMApplicationPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FTMApplicationPacket *pp = omnetpp::fromAnyPtr<FTMApplicationPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FTMApplicationPacket'", field);
    }
}

omnetpp::cValue FTMApplicationPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FTMApplicationPacket *pp = omnetpp::fromAnyPtr<FTMApplicationPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: return (omnetpp::intval_t)(pp->getSequenceNumber());
        case FIELD_clockTime1: return cValue(pp->getClockTime1().dbl(),"s");
        case FIELD_clockTime2: return cValue(pp->getClockTime2().dbl(),"s");
        case FIELD_clockTime3: return cValue(pp->getClockTime3().dbl(),"s");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FTMApplicationPacket' as cValue -- field index out of range?", field);
    }
}

void FTMApplicationPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FTMApplicationPacket *pp = omnetpp::fromAnyPtr<FTMApplicationPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FTMApplicationPacket'", field);
    }
}

const char *FTMApplicationPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr FTMApplicationPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FTMApplicationPacket *pp = omnetpp::fromAnyPtr<FTMApplicationPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FTMApplicationPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FTMApplicationPacket *pp = omnetpp::fromAnyPtr<FTMApplicationPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FTMApplicationPacket'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

