#pragma once

#include "Memory/LinearAllocator.h"

namespace EG
{
	class WString
	{
	public:
		WString() = default;
		WString(const wchar_t* str);
		WString(int size);
		WString(const wchar_t& characher);
		~WString();

		WString(const WString& other);

		wchar_t* GetString() const;
		void Copy(const WString& other);
		size_t GetSize() const;

		void operator+=(const wchar_t& characher);
		void operator+=(const wchar_t* str);
		void operator=(const wchar_t* str);
		void operator=(const wchar_t& characher);
		void operator=(const WString& other);

	private:
		LinearAllocator m_allocator;

		wchar_t* m_str = nullptr;
	};
}
