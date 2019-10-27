#include  "WString.h"

EG::WString::WString(const wchar_t* str)
{
	const size_t strLen = wcslen(str) * sizeof(wchar_t);
	m_allocator.AllocBlock(strLen + sizeof(wchar_t));
	void* alloc = m_allocator.Alloc(strLen + sizeof(wchar_t));
	memcpy(alloc, &str[0], strLen);
	memset(&static_cast<wchar_t*>(alloc)[strLen / sizeof(wchar_t)], '\0', sizeof(wchar_t));
	int debug = 0;

	m_str = static_cast<wchar_t*>(m_allocator.GetFirst());
}

EG::WString::WString(int size)
{
	m_allocator.AllocBlock(size + sizeof(wchar_t));

	m_str = static_cast<wchar_t*>(m_allocator.GetFirst());
}

EG::WString::WString(const wchar_t& characher)
{
	const size_t charLen = sizeof(wchar_t);
	m_allocator.AllocBlock(charLen * sizeof(wchar_t));
	void* alloc = m_allocator.Alloc(charLen * sizeof(wchar_t));
	memcpy(alloc, &characher, charLen);
	memset(&static_cast<wchar_t*>(alloc)[charLen / sizeof(wchar_t)], L'\0', charLen);

	m_str = static_cast<wchar_t*>(m_allocator.GetFirst());
}

EG::WString::~WString()
{
	m_allocator.Free();
}

EG::WString::WString(const WString& other)
{
	const size_t otherStringBlockSize = other.m_allocator.GetBlockSize();

	m_allocator.Free();
	m_allocator.AllocBlock(otherStringBlockSize);
	void* newPtr = m_allocator.Alloc(otherStringBlockSize);
	wchar_t* copyStr = other.GetString();

	memcpy(newPtr, &copyStr[0], otherStringBlockSize);

	m_str = static_cast<wchar_t*>(m_allocator.GetFirst());
}

wchar_t* EG::WString::GetString() const
{
	return static_cast<wchar_t*>(m_allocator.GetFirst());
}

void EG::WString::Copy(const WString& other)
{
	const size_t otherStringBlockSize = other.m_allocator.GetBlockSize();

	m_allocator.Free();
	m_allocator.AllocBlock(otherStringBlockSize);
	void* newPtr = m_allocator.Alloc(otherStringBlockSize);
	wchar_t* copyStr = other.GetString();

	memcpy(newPtr, &copyStr[0], otherStringBlockSize);

	m_str = static_cast<wchar_t*>(m_allocator.GetFirst());
}

size_t EG::WString::GetSize() const
{
	return m_allocator.GetOffset();
}

void EG::WString::operator+=(const wchar_t& characher)
{
	const bool isOffset = m_allocator.GetOffset() == 0;

	const size_t charSize = sizeof(wchar_t) + static_cast<int>(isOffset) * sizeof(wchar_t);

	void* newPtr = m_allocator.Alloc(charSize);

	if (newPtr == nullptr)
	{
		m_allocator.Realloc(charSize);
		newPtr = m_allocator.Alloc(charSize);
	}

	wchar_t* cPtr = static_cast<wchar_t*>(newPtr);

	if (isOffset == false)
		cPtr -= 1;

	memcpy(cPtr, &characher, charSize - static_cast<int>(isOffset) * sizeof(wchar_t));

	cPtr += charSize / sizeof(wchar_t) - static_cast<int>(isOffset);
	memset(cPtr, L'\0', sizeof(wchar_t));

	m_str = static_cast<wchar_t*>(m_allocator.GetFirst());
}

void EG::WString::operator+=(const wchar_t* str)
{
	const bool isOffset = m_allocator.GetOffset() == 0;

	const size_t charSize = wcslen(str) * sizeof(wchar_t) + static_cast<int>(isOffset) * sizeof(wchar_t);

	void* newPtr = m_allocator.Alloc(charSize);

	if (newPtr == nullptr)
	{
		m_allocator.Realloc(charSize);
		newPtr = m_allocator.Alloc(charSize);
	}

	wchar_t* cPtr = static_cast<wchar_t*>(newPtr);

	if (isOffset == false)
		cPtr -= 1;
	
	memcpy(cPtr, &str[0], charSize - static_cast<int>(isOffset));
	
	cPtr += charSize / sizeof(wchar_t) - static_cast<int>(isOffset) * sizeof(wchar_t);
	memset(cPtr, L'\0', sizeof(wchar_t));

	m_str = static_cast<wchar_t*>(m_allocator.GetFirst());
}

void EG::WString::operator=(const wchar_t* str)
{
	const size_t strSize = wcslen(str) * sizeof(wchar_t);
	m_allocator.Free();
	m_allocator.AllocBlock(strSize + sizeof(wchar_t));
	void* newPtr = m_allocator.Alloc(strSize + sizeof(wchar_t));
	memcpy(newPtr, &str[0], strSize);
	memset(&static_cast<wchar_t*>(newPtr)[strSize / sizeof(wchar_t)], L'\0', sizeof(wchar_t));

	m_str = static_cast<wchar_t*>(m_allocator.GetFirst());
}

void EG::WString::operator=(const wchar_t& characher)
{
	const size_t charSize = sizeof(wchar_t);
	m_allocator.Free();
	m_allocator.AllocBlock(charSize + sizeof(wchar_t));
	void* newPtr = m_allocator.Alloc(charSize + sizeof(wchar_t));
	memcpy(newPtr, &characher, charSize);
	memset(&static_cast<wchar_t*>(newPtr)[charSize / charSize], L'\0', sizeof(wchar_t));

	m_str = static_cast<wchar_t*>(m_allocator.GetFirst());
}
