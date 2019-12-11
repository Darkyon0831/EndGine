#include  "String.h"

#include <string>

EG::String::String(const char* str)
{
	const size_t strLen = strlen(str);
	m_allocator.AllocBlock(strLen + 1);
	void* alloc = m_allocator.Alloc(strLen + 1);
	memcpy(alloc, &str[0], strLen);
	memset(&static_cast<char*>(alloc)[strLen], '\0', 1);

	m_str = static_cast<char*>(m_allocator.GetFirst());
}

EG::String::String(size_t size)
{
	m_allocator.AllocBlock(size + 1);

	m_str = static_cast<char*>(m_allocator.GetFirst());
}

EG::String::String(const char& characher)
{
	const size_t charLen = sizeof(char);
	m_allocator.AllocBlock(charLen + 1);
	void* alloc = m_allocator.Alloc(charLen + 1);
	memcpy(alloc, &characher, charLen);
	memset(&static_cast<char*>(alloc)[charLen], '\0', 1);

	m_str = static_cast<char*>(m_allocator.GetFirst());
}

EG::String::~String()
{
	m_allocator.Free();
}

EG::String::String(const String& other)
{
	const size_t otherStringBlockSize = other.m_allocator.GetBlockSize();
	
	m_allocator.Free();
	m_allocator.AllocBlock(otherStringBlockSize);
	void* newPtr = m_allocator.Alloc(otherStringBlockSize);
	char* copyStr = other.GetString();
	
	memcpy(newPtr, &copyStr[0], otherStringBlockSize);

	m_str = static_cast<char*>(m_allocator.GetFirst());
}

char* EG::String::GetString() const
{
	return static_cast<char*>(m_allocator.GetFirst());
}

void EG::String::Copy(const String& other)
{
	const size_t otherStringBlockSize = other.m_allocator.GetBlockSize();

	m_allocator.Free();
	m_allocator.AllocBlock(otherStringBlockSize);
	void* newPtr = m_allocator.Alloc(otherStringBlockSize);
	char* copyStr = other.GetString();

	memcpy(newPtr, &copyStr[0], otherStringBlockSize);

	m_str = static_cast<char*>(m_allocator.GetFirst());
}

size_t EG::String::GetSize() const
{
	return m_allocator.GetOffset();
}

void EG::String::operator+=(const char& characher)
{
	const bool isOffset = m_allocator.GetOffset() == 0;

	const size_t charSize = sizeof(char) + static_cast<int>(isOffset);

	if (charSize != 0)
	{
		void* newPtr = m_allocator.Alloc(charSize);

		if (newPtr == nullptr)
		{
			m_allocator.Realloc(charSize);
			newPtr = m_allocator.Alloc(charSize);
		}

		char* cPtr = static_cast<char*>(newPtr);

		if (isOffset == false)
			cPtr -= 1;

		memcpy(cPtr, &characher, charSize - static_cast<int>(isOffset));

		cPtr += charSize - static_cast<int>(isOffset);
		memset(cPtr, '\0', 1);

		m_str = static_cast<char*>(m_allocator.GetFirst());
	}
}

void EG::String::operator+=(const char* str)
{
	const bool isOffset = m_allocator.GetOffset() == 0;

	const size_t strSize = strlen(str) + static_cast<int>(isOffset);

	if (strSize != 0)
	{
		void* newPtr = m_allocator.Alloc(strSize);

		if (newPtr == nullptr)
		{
			m_allocator.Realloc(strSize);
			newPtr = m_allocator.Alloc(strSize);
		}

		char* cPtr = static_cast<char*>(newPtr);

		if (isOffset == false)
			cPtr -= 1;

		memcpy(cPtr, &str[0], strSize - static_cast<int>(isOffset));

		cPtr += strSize - static_cast<int>(isOffset);
		memset(cPtr, '\0', 1);

		m_str = static_cast<char*>(m_allocator.GetFirst());
	}
}

void EG::String::operator=(const char* str)
{
	const size_t strSize = strlen(str);
	m_allocator.Free();
	m_allocator.AllocBlock(strSize + 1);
	void* newPtr = m_allocator.Alloc(strSize + 1);
	memcpy(newPtr, &str[0], strSize);
	memset(&static_cast<char*>(newPtr)[strSize], '\0', 1);

	m_str = static_cast<char*>(m_allocator.GetFirst());
}

void EG::String::operator=(char* str)
{
	const size_t strSize = strlen(str);
	m_allocator.Free();
	m_allocator.AllocBlock(strSize + 1);
	void* newPtr = m_allocator.Alloc(strSize + 1);
	memcpy(newPtr, &str[0], strSize);
	memset(&static_cast<char*>(newPtr)[strSize], '\0', 1);

	m_str = static_cast<char*>(m_allocator.GetFirst());
}

void EG::String::operator=(const char& characher)
{
	const size_t charSize = sizeof(char);
	m_allocator.Free();
	m_allocator.AllocBlock(charSize + 1);
	void* newPtr = m_allocator.Alloc(charSize + 1);
	memcpy(newPtr, &characher, charSize);
	memset(&static_cast<char*>(newPtr)[charSize], '\0', 1);

	m_str = static_cast<char*>(m_allocator.GetFirst());
}

void EG::String::operator=(const String& other)
{
	const size_t otherStringBlockSize = other.m_allocator.GetBlockSize();

	m_allocator.Free();
	m_allocator.AllocBlock(otherStringBlockSize);
	void* newPtr = m_allocator.Alloc(otherStringBlockSize);
	char* copyStr = other.GetString();

	memcpy(newPtr, &copyStr[0], otherStringBlockSize);

	m_str = static_cast<char*>(m_allocator.GetFirst());
}

EG::String EG::String::operator+(const String& other) const
{
	String newString = String(GetSize() + other.GetSize());
	char* newStringPtr = newString.GetString();

	newString += GetString();
	newString += other.GetString();

	return newString;
}

EG::String EG::String::operator+(const char& other) const
{
	String newString = String(GetSize() + sizeof(char));
	char* newStringPtr = newString.GetString();

	newString += GetString();
	newString += other;

	return newString;

}

EG::String EG::String::operator+(const int& other) const
{
	String newString = String(GetSize() + sizeof(int));

	std::string str = std::to_string(other);

	newString += GetString();
	newString += str.c_str();

	return newString;
}

EG::String EG::String::operator+(const float& other) const
{
	String newString = String(GetSize() + sizeof(int));

	std::string str = std::to_string(other);

	newString += GetString();
	newString += str.c_str();

	return newString;
}

EG::String EG::String::operator+(const double& other) const
{
	String newString = String(GetSize() + sizeof(int));

	std::string str = std::to_string(other);

	newString += GetString();
	newString += str.c_str();

	return newString;
}
