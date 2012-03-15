#include <iostream>
#include <typeinfo>
#include <string.h>

class CException {
public:
	virtual void GetDescription(char**) {}; //WARNING! You should manually free memory alocated by GetDescripton!
};

class COutOfRange : public CException {
public:
	COutOfRange();
	COutOfRange(const char* _data);
	COutOfRange(const COutOfRange& copy);
	~COutOfRange();
	void operator = (const COutOfRange& copy);
	void GetDescription(char** _buffer);
private:
    char* data;
};

class CIllegalOperation : public CException {
public:
	CIllegalOperation();
	CIllegalOperation(const char* _data);
	CIllegalOperation(const CIllegalOperation& copy);
	~CIllegalOperation();
	void operator = (const CIllegalOperation& copy);
	void GetDescription(char** _buffer);
private:
    char* data;
};
