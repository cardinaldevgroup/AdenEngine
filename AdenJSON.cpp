#include "AdenJSON.h"

AdenJSONNode::AdenJSONNode()
{
}

AdenJSONNode::~AdenJSONNode()
{
}

bool AdenJSONNode::Empty()
{
	return _type == AdenJSONNodeType::Null;
}

std::string AdenJSONNode::AsString(bool* ok) const
{
	if (!_pCJSONNode)
	{
		if (ok) *ok = false;
		return std::string();
	}
	
	if (ok) *ok = true;
	return _pCJSONNode->valuestring;
}

int AdenJSONNode::AsInt(bool* ok) const
{
	if (!_pCJSONNode)
	{
		if (ok) *ok = false;
		return 0;
	}

	if (ok) *ok = true;
	return _pCJSONNode->valueint;
}

double AdenJSONNode::AsDouble(bool* ok) const
{
	if (!_pCJSONNode)
	{
		if (ok) *ok = false;
		return 0.0;
	}

	if (ok) *ok = true;
	return _pCJSONNode->valuedouble;
}

int AdenJSONNode::GetArraySize(bool* ok) const
{
	if (_type != AdenJSONNodeType::Array || !_pCJSONNode)
	{
		if (ok) *ok = false;
		return 0;
	}
	
	if (ok) *ok = true;
	return cJSON_GetArraySize(_pCJSONNode);
}

std::string AdenJSONNode::Print(bool formatted) const
{
	if (!_pCJSONNode)
		return std::string();

	char* strRawJSON = formatted ? cJSON_Print(_pCJSONNode) : cJSON_PrintUnformatted(_pCJSONNode);
	std::string strWrappedJSON = std::string(strRawJSON);
	free(strRawJSON);

	return strWrappedJSON;
}

AdenJSONNode::operator bool() const
{
	return _type != AdenJSONNodeType::Null;
}

bool AdenJSONNode::operator==(const AdenJSONNode& node) const
{
	return _pCJSONNode == node._pCJSONNode;
}

bool AdenJSONNode::operator!=(const AdenJSONNode& node) const
{
	return _pCJSONNode != node._pCJSONNode;
}

AdenJSONNode AdenJSONNode::operator[](const int idx) const
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !_pCJSONNode)
		return newNode;

	int arraySize = cJSON_GetArraySize(_pCJSONNode);

	if (idx >= 0 && idx < arraySize)
		newNode._pCJSONNode = cJSON_GetArrayItem(_pCJSONNode, idx);
	else if (idx < 0 && abs(idx) <= arraySize)
		newNode._pCJSONNode = cJSON_GetArrayItem(_pCJSONNode, idx + arraySize);

	if (newNode._pCJSONNode)
		newNode._type = (AdenJSONNodeType)newNode._pCJSONNode->type;

	return newNode;
}

AdenJSONNode AdenJSONNode::operator[](const std::string& key) const
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !_pCJSONNode)
		return newNode;

	newNode._pCJSONNode = cJSON_GetObjectItemCaseSensitive(_pCJSONNode, key.c_str());

	if (newNode._pCJSONNode)
		newNode._type = (AdenJSONNodeType)newNode._pCJSONNode->type;

	return newNode;
}

AdenJSONParseResult AdenJSONDocument::LoadFromFile(std::string path)
{
	if (_pCJSONNode)
	{
		cJSON_Delete(_pCJSONNode);
		_pCJSONNode = nullptr;
	}

	AdenJSONParseResult result;
	std::ifstream fin(path);
	if (!fin.good())
	{
		result.status = AdenJSONParseStatus::IOError;
		result.description = "open file failed";
		return result;
	}

	std::stringstream ssContent;
	ssContent << fin.rdbuf();
	fin.close(); fin.clear();

	_LoadFromStringImpl(ssContent.str(), result);

	ssContent.clear();

	return result;
}

AdenJSONParseResult AdenJSONDocument::LoadFromString(std::string str)
{
	AdenJSONParseResult result;
	
	_LoadFromStringImpl(str, result);

	return result;
}

void AdenJSONDocument::_LoadFromStringImpl(std::string str, AdenJSONParseResult& result)
{
	if (_pCJSONNode)
	{
		cJSON_Delete(_pCJSONNode);
		_pCJSONNode = nullptr;
	}

	_pCJSONNode = cJSON_Parse(str.c_str());
	if (!_pCJSONNode)
	{
		result.status = AdenJSONParseStatus::ParseError;
		result.description = std::string("JSON parse error before: ").append(cJSON_GetErrorPtr());
		cJSON_Delete(_pCJSONNode);
		_pCJSONNode = nullptr;
		return;
	}

	result.status = AdenJSONParseStatus::Success;
	_type = (AdenJSONNodeType)_pCJSONNode->type;
}

AdenJSONDocument::AdenJSONDocument()
{
}

AdenJSONDocument::~AdenJSONDocument()
{
	cJSON_Delete(_pCJSONNode);
	_pCJSONNode = nullptr;
}