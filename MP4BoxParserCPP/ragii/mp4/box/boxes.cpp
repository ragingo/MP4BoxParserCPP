#include <assert.h>
#include "boxes.h"

namespace ragii { namespace mp4 {

	void copy_box(Box* dest, const Box* src)
	{
		assert(dest && src);

		dest->m_Type = src->m_Type;
		dest->m_TypeName = src->m_TypeName;
		dest->m_Size = src->m_Size;
		dest->m_LargeSize = src->m_LargeSize;
		dest->m_Offset = src->m_Offset;
		dest->m_NextPos = src->m_NextPos;
		dest->m_Parent = src->m_Parent;
	}

	bool is_child(const Box* parent, const Box* target)
	{
		assert(parent && target);
		return parent->m_NextPos >= target->m_NextPos;
	}

} }
