/* libwpd
 * Copyright (C) 2002 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by 
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef WP6STYLEGROUP_H
#define WP6STYLEGROUP_H

#include "WP6VariableLengthGroup.h"

class WP6StyleGroup_GlobalOnSubGroup : public WP6VariableLengthGroup_SubGroup
{
public:
	WP6StyleGroup_GlobalOnSubGroup(WPXInputStream *input);
	virtual void parse(WP6HLListener *listener, const guint8 numPrefixIDs, guint16 const *prefixIDs) const;

private:
	guint16 m_hash;
	guint8 m_systemStyleNumber;
};

class WP6StyleGroup : public WP6VariableLengthGroup
{
public:
	WP6StyleGroup(WPXInputStream *input);	
	~WP6StyleGroup();
	virtual void _readContents(WPXInputStream *input);
	virtual void parse(WP6HLListener *listener);

private:
	WP6VariableLengthGroup_SubGroup *m_subGroupData;
};

#endif /* WP6STYLEGROUP_H */
