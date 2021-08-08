#ifndef _ADEN_JSON_H_
#define _ADEN_JSON_H_

#include <cJSON.h>

#include <string>
#include <fstream>
#include <sstream>

enum AdenJSONParseStatus
{
	Success = 0,
	IOError,
	ParseError,
};

enum AdenJSONNodeType
{
	False = cJSON_False,
	True = cJSON_True,
	Null = cJSON_NULL,
	Number = cJSON_Number,
	String = cJSON_String,
	Array = cJSON_Array,
	Object = cJSON_Object,
};

struct AdenJSONParseResult
{
	AdenJSONParseStatus status;
	std::string description;
};

class AdenJSONNode
{
public:
	AdenJSONNode();
	virtual ~AdenJSONNode();
	bool Empty();
	std::string AsString(bool* ok = nullptr) const;
	int AsInt(bool* ok = nullptr) const;
	double AsDouble(bool* ok = nullptr) const;
	int GetArraySize(bool* ok = nullptr) const;
	std::string Print(bool formatted = true) const;
	operator bool() const;
	bool operator==(const AdenJSONNode& node) const;
	bool operator!=(const AdenJSONNode& node) const;
	AdenJSONNode operator[](const int idx) const;
	AdenJSONNode operator[](const std::string& key) const;

protected:
	AdenJSONNodeType _type = AdenJSONNodeType::Null;
	cJSON* _pCJSONNode = nullptr;
};

class AdenJSONDocument : public AdenJSONNode
{
public:
	AdenJSONDocument();
	~AdenJSONDocument();
	AdenJSONParseResult LoadFromFile(std::string path);
	AdenJSONParseResult LoadFromString(std::string str);

private:
	void _LoadFromStringImpl(std::string str, AdenJSONParseResult& result);
};

#endif // !_ADEN_JSON_H_
