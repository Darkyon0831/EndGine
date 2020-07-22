#include  "String.h"

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
	m_allocator.AllocBlock(size);

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

bool EG::String::Compare(const String& rString) const
{
	if (rString.GetSize() != GetSize()) return false;

	for (int i = 0; i < GetSize(); i++)
		if (rString[i] != (*this)[i]) return false;

	return true;
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

void EG::String::operator+=(const char* str)
{
	const bool isOffset = m_allocator.GetOffset() == 0;

	char c;
	int cIndex = 0;
	while((c = str[cIndex]) != '\0')
	{
		operator+=(c);
		
		cIndex++;
	}

	int i = 0;
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
	String newString = String();

	newString += GetString();
	newString += other.GetString();

	return newString;
}
