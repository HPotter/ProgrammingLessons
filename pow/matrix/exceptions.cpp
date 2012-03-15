#include "exceptions.h"

COutOfRange::COutOfRange() {
    data = new char[30];
    data[29] = '\0';
    strcpy(data, "Unknown COutOfRange exception");
}

COutOfRange::COutOfRange(const char* _data) {
    if(_data == NULL) {
        data = new char[30];
        data[29] = '\0';
        strcpy(data, "Unknown COutOfRange exception");
    } else {
        data = new char[strlen(_data) + 1];
        strcpy(data, _data);
    }
}

COutOfRange::COutOfRange(const COutOfRange& copy) {
    data = new char[strlen(copy.data)+1];
    strcpy(data, copy.data);
}

COutOfRange::~COutOfRange() {
    delete[] data;
}

void COutOfRange::GetDescription(char** _buffer) {
    char* buffer = new char[strlen(data)+1];
    strcpy(buffer, data);
    *_buffer = buffer;
}

void COutOfRange::operator = (const COutOfRange& copy) {
    data = new char[strlen(copy.data)+1];
    strcpy(data, copy.data);
}

CIllegalOperation::CIllegalOperation() {
    data = new char[31];
    data[30] = '\0';
    strcpy(data, "Unknown CIllegalOperation exception");
}

CIllegalOperation::CIllegalOperation(const char* _data) {
    if(_data == NULL) {
        data = new char[31];
        data[30] = '\0';
        strcpy(data, "Unknown CIllegalOperation exception");
    } else {
        data = new char[strlen(_data) + 1];
        strcpy(data, _data);
    }
}

CIllegalOperation::CIllegalOperation(const CIllegalOperation& copy) {
    data = new char[strlen(copy.data)+1];
    strcpy(data, copy.data);
}

CIllegalOperation::~CIllegalOperation() {
    delete[] data;
}

void CIllegalOperation::operator = (const CIllegalOperation& copy) {
    data = new char[strlen(copy.data)+1];
    strcpy(data, copy.data);
}

void CIllegalOperation::GetDescription(char** _buffer) {
    char* buffer = new char[strlen(data)+1];
    strcpy(buffer, data);
    *_buffer = buffer;
}
