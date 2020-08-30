#pragma once

#include "RE/Bethesda/Atomic.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSInputEventReceiver.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/BSTimer.h"
#include "RE/Bethesda/IMenu.h"
#include "RE/Scaleform/GFx/GFx_Player.h"

namespace RE
{
	class MenuModeChangeEvent;
	class MenuModeCounterChangedEvent;
	class MenuOpenCloseEvent;
	class TutorialEvent;

	struct UIMenuEntry
	{
	public:
		using Create_t = IMenu*(const UIMessage&);
		using StaticUpdate_t = void();

		// members
		Scaleform::Ptr<IMenu> menu;				  // 00
		Create_t* create;						  // 08
		StaticUpdate_t* staticUpdate{ nullptr };  // 10
	};
	static_assert(sizeof(UIMenuEntry) == 0x18);

	class UI :
		public BSInputEventReceiver,						 // 000
		public BSTSingletonSDM<UI>,							 // 010
		public BSTEventSource<MenuOpenCloseEvent>,			 // 018
		public BSTEventSource<MenuModeChangeEvent>,			 // 070
		public BSTEventSource<MenuModeCounterChangedEvent>,	 // 0C8
		public BSTEventSource<TutorialEvent>				 // 120
	{
	public:
		static constexpr auto RTTI{ RTTI_UI };

		using Create_t = typename UIMenuEntry::Create_t;
		using StaticUpdate_t = typename UIMenuEntry::StaticUpdate_t;

		// add
		virtual ~UI() = default;  // 01

		[[nodiscard]] static UI* GetSingleton()
		{
			REL::Relocation<UI**> singleton{ REL::ID(548587) };
			return *singleton;
		}

		inline void RegisterMenu(const char* a_menu, Create_t* a_create, StaticUpdate_t* a_staticUpdate = nullptr)
		{
			using func_t = decltype(&UI::RegisterMenu);
			REL::Relocation<func_t> func{ REL::ID(1519575) };
			return func(this, a_menu, a_create, a_staticUpdate);
		}

		// members
		BSTArray<BSFixedString> releasedMovies;			   // 178
		BSTArray<Scaleform::Ptr<IMenu>> menuStack;		   // 190
		BSTHashMap<BSFixedString, UIMenuEntry> menuMap;	   // 1A8
		BSSpinLock processMessagesLock;					   // 1D8
		std::uint32_t menuMode;							   // 1E0
		BSTAtomicValue<std::uint32_t> itemMenuMode;		   // 1E4
		BSTAtomicValue<std::uint32_t> pauseMenuDisableCt;  // 1E8
		std::uint32_t freezeFrameMenuBG;				   // 1EC
		std::uint32_t freezeFramePause;					   // 1F0
		std::uint32_t savingDisabled;					   // 1F4
		std::uint32_t disablesCompanion;				   // 1F8
		std::uint32_t largeCacheRenderModeCount;		   // 1FC
		std::uint32_t movementToDirectionalCount;		   // 200
		BSTimer uiTimer;								   // 208
		bool menuSystemVisible;							   // 248
		bool closingAllMenus;							   // 249
		bool freezeFrameScreenshotReady;				   // 24A
	};
	static_assert(sizeof(UI) == 0x250);
}