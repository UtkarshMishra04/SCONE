#include "stdafx.h"
#include "Link.h"

#include "Body.h"
#include "Joint.h"

namespace scone
{
	namespace sim
	{
		String Link::ToString( const String& prefix ) const
		{
			String s = prefix + GetBody().GetName() + ( HasJoint() ? ( " (" + GetJoint().GetName() + ")\n" ) : "\n" );
			for ( auto it = m_Children.begin(); it != m_Children.end(); ++it )
				s += (*it)->ToString( prefix + "  " );

			return s;
		}

	}
}
