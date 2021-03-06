#pragma once

#include "Memory/LinearAllocator.h"

namespace EG
{
	class String
	{
	public:
		String() = default;
		String(const char* str);
		String(size_t size);
		String(const char& characher);
		~String();

		String(const String& other);

		bool Compare(const String& rString) const;
		char* GetString() const;
		void Copy(const String& other);
		size_t GetSize() const;

		void operator+=(const char& characher);
		void operator+=(const char* str);
		void operator=(const char* str);
		void operator=(char* str);
		void operator=(const char& characher);
		
		void operator=(const String& other);
		String operator+(const String& other) const;
		String operator+(const char& other) const;
		String operator+(const int& other) const;
		String operator+(const float& other) const;
		String operator+(const double& other) const;

		char operator[] (const int& index) const { return GetString()[index]; }

	private:
		LinearAllocator m_allocator;
		char* m_str = nullptr;
	};
}
