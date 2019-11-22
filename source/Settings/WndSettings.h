#pragma once

#include "Globals/String.h"
#include  "Globals/WString.h"
#include  "Globals/Singleton.h"
#include  "Containers/WndContainer.h"

namespace EG 
{
	class WndSettings : public Singleton<WndSettings>
	{
	public:
		WndSettings()
			: m_wndName(String("EndGine"))
			, m_wndWidht(1920)
			, m_wndHeight(1080)
			, m_fullscreen(false)
			, m_vsync(false)
		{}
		
		const String& GetWndName() const { return m_wndName; }
		void SetWndName(const String& str);

		const float& GetWndWidth() const { return m_wndWidht; }
		void SetWndWidth(float wndWidth);

		const float& GetWndHeight() const { return m_wndHeight; }
		void SetWndHeight(float wndHeight);

		const bool& GetIsFullscreen() const { return m_fullscreen; }
		void SetIsFullscreen(bool isFullscreen) { m_fullscreen = isFullscreen; }

		const bool& GetIsVsync() const { return m_vsync; }
		void SetIsVsync(bool isVsync) { m_vsync = isVsync; }
	
	private:
		String m_wndName;
		float m_wndWidht;
		float m_wndHeight;
		bool m_fullscreen;
		bool m_vsync;
	};

	inline void WndSettings::SetWndName(const String& str)
	{
		m_wndName = str;
		SetWindowTextA(WndContainer::GetInstance().GetWindowHandle(), m_wndName.GetString());
	}

	inline void WndSettings::SetWndWidth(float wndWidth)
	{
		m_wndWidht = wndWidth;
		RECT rect = { NULL };

		const HWND& rWindowHandle = WndContainer::GetInstance().GetWindowHandle();
		
		GetWindowRect(WndContainer::GetInstance().GetWindowHandle(), &rect);

		SetWindowPos(rWindowHandle, rWindowHandle, rect.left, rect.top, static_cast<int>(m_wndWidht), rect.bottom, SWP_SHOWWINDOW);
	}

	inline void WndSettings::SetWndHeight(float wndHeight)
	{
		m_wndHeight = wndHeight;
		RECT rect = { NULL };

		const HWND& rWindowHandle = WndContainer::GetInstance().GetWindowHandle();

		GetWindowRect(WndContainer::GetInstance().GetWindowHandle(), &rect);

		SetWindowPos(rWindowHandle, rWindowHandle, rect.left, rect.top, rect.right, static_cast<int>(wndHeight), SWP_SHOWWINDOW);
	}
}
