/* libwpd
 * Copyright (C) 2002 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
 * Copyright (C) 2004 Fridrich Strba (fridrich.strba@bluewin.ch)
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

#include "WP6HighlightGroup.h"
#include "WP6LLListener.h"
#include "libwpd_internal.h"

WP6HighlightGroup::WP6HighlightGroup(WPXInputStream *input, guint8 groupID)
	: WP6FixedLengthGroup(groupID)
{
	_read(input);
}

void WP6HighlightGroup::_readContents(WPXInputStream *input)
{
	m_color.m_r = gsf_le_read_guint8(input);
	m_color.m_g = gsf_le_read_guint8(input);
	m_color.m_b = gsf_le_read_guint8(input);
	m_color.m_s = gsf_le_read_guint8(input);
}

WP6HighlightOnGroup::WP6HighlightOnGroup(WPXInputStream *input, guint8 groupID)
	: WP6HighlightGroup(input, groupID)
{
}

void WP6HighlightOnGroup::parse(WP6HLListener *listener)
{
	listener->highlightChange(true, getColor());
}

WP6HighlightOffGroup::WP6HighlightOffGroup(WPXInputStream *input, guint8 groupID)
	: WP6HighlightGroup(input, groupID)
{
}

void WP6HighlightOffGroup::parse(WP6HLListener *listener)
{
	listener->highlightChange(false, getColor());
}
