/* libwpd2
 * Copyright (C) 2002 William Lachance (wlach@interlog.com)
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

#ifndef WP6COLUMNGROUP_H
#define WP6COLUMNGROUP_H

#include "WP6VariableLengthGroup.h"

class WP6ColumnGroup : public WP6VariableLengthGroup
{
 public:
	WP6ColumnGroup(GsfInput *input);	
	virtual void _readContents(GsfInput *input);
	virtual void parse(WP6LLListener *llListener);

 private:
	// variables needed for subgroup 0 and 1 (Left/Right Margin Set)
	guint16 m_margin;
 
 	// variables used for subgroup 2 (Columns)
	guint8 m_colType;
	guint8 m_numColumns;
	guint8 m_rowSpacing[4]; // a WP SPacing type variable, which is 4 bytes
};

#endif /* WP6COLUMNGROUP_H */