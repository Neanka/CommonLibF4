#pragma once

#include "RE/Bethesda/Atomic.h"
#include "RE/NetImmerse/NiAVObject.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTArray.h"

namespace RE
{
	class NiNode :
		public NiAVObject  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::NiNode };
		static constexpr auto VTABLE{ VTABLE::NiNode };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiNode };

		// add
		void AttachChild(NiAVObject* a_child, bool a_firstAvail);								  // 3A
		void InsertChildAt(std::uint32_t a_idx, NiAVObject* a_child);							  // 3B
		void DetachChild(NiAVObject* a_child, NiPointer<NiAVObject>& a_avObject);				  // 3C
		void DetachChild(NiAVObject* a_child);													  // 3D
		void DetachChildAt(std::uint32_t a_idx, NiPointer<NiAVObject>& a_avObject);				  // 3E
		void DetachChildAt(std::uint32_t a_idx);												  // 3F
		void SetAt(std::uint32_t a_idx, NiAVObject* a_child, NiPointer<NiAVObject>& a_avObject);  // 40
		void SetAt(std::uint32_t a_idx, NiAVObject* a_child);									  // 41
		void UpdateUpwardPass(NiUpdateData& a_data);											  // 42

		// members
		NiTObjectArray<NiPointer<NiAVObject>> children;	 // 120
		BSTAtomicValue<std::uint32_t> dirtyState;		 // 138
		float meshLODFadeAmount;						 // 13C
	};
	static_assert(sizeof(NiNode) == 0x140);
}
