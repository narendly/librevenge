/* libwpd
 * Copyright (C) 2003 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2003-2004 Marc Maurer (j.m.maurer@student.utwente.nl)
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

#include "WP5VariableLengthGroup.h"
#include "WP5UnsupportedVariableLengthGroup.h"
#include "libwpd_internal.h"
#include "WP5FormatGroup.h"

WP5VariableLengthGroup::WP5VariableLengthGroup()
{
}

WP5VariableLengthGroup * WP5VariableLengthGroup::constructVariableLengthGroup(WPXInputStream *input, guint8 group)
{
	switch (group)
	{
		case WP5_TOP_FORMAT_GROUP:
			return new WP5FormatGroup(input);
		default:
			// this is an unhandled group, just skip it
			return new WP5UnsupportedVariableLengthGroup(input);
	}
}

void WP5VariableLengthGroup::_read(WPXInputStream *input)
{
	guint32 startPosition = input->tell();

	WPD_DEBUG_MSG(("WordPerfect: handling a variable length group\n"));	
	
	m_subGroup = gsf_le_read_guint8(input);
	m_size = gsf_le_read_guint16(input) + 4; // the length is the number of data bytes minus 4 (ie. the function codes)
	
	WPD_DEBUG_MSG(("WordPerfect: Read variable group header (start_position: %i, sub_group: 0x%x, size: %i)\n", startPosition, m_subGroup, m_size));
	
	_readContents(input);
	
	input->seek((startPosition + m_size - 1 - input->tell()), WPX_SEEK_CUR);

}
