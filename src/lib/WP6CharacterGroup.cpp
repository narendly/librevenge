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

#include "WP6CharacterGroup.h"
#include "WP6LLListener.h"
#include "libwpd_internal.h"

/*************************************************************************
 * WP6CharacterGroup_ColorSubGroup
 *************************************************************************/

WP6CharacterGroup_ColorSubGroup::WP6CharacterGroup_ColorSubGroup(WPXInputStream *input)
{
	m_red = gsf_le_read_guint8(input);
	m_green = gsf_le_read_guint8(input);
	m_blue = gsf_le_read_guint8(input);
	WPD_DEBUG_MSG(("WordPerfect: Character Group Color subgroup info (red: %i, green: %i, blue: %i)\n", m_red, m_green, m_blue));
}

void WP6CharacterGroup_ColorSubGroup::parse(WP6HLListener *listener, const guint8 numPrefixIDs, guint16 const *prefixIDs) const
{
	listener->characterColorChange(m_red, m_green, m_blue);
}

/*************************************************************************
 * WP6CharacterGroup_CharacterShadingChangeSubGroup
 *************************************************************************/

WP6CharacterGroup_CharacterShadingChangeSubGroup::WP6CharacterGroup_CharacterShadingChangeSubGroup(WPXInputStream *input)
{
	m_shading = gsf_le_read_guint8(input);
	WPD_DEBUG_MSG(("WordPerfect: Character Group Character Shading Change subgroup info (shading: %i)\n", m_shading));
}

void WP6CharacterGroup_CharacterShadingChangeSubGroup::parse(WP6HLListener *listener, const guint8 numPrefixIDs, guint16 const *prefixIDs) const
{
	listener->characterShadingChange(m_shading);
}

/*************************************************************************
 * WP6CharacterGroup_FontFaceChangeSubGroups
 *************************************************************************/

WP6CharacterGroup_FontFaceChangeSubGroup::WP6CharacterGroup_FontFaceChangeSubGroup(WPXInputStream *input)
{
	m_oldMatchedPointSize = gsf_le_read_guint16(input);
	m_hash = gsf_le_read_guint16(input);
	m_matchedFontIndex = gsf_le_read_guint16(input);
	m_matchedFontPointSize = gsf_le_read_guint16(input);
	WPD_DEBUG_MSG(("WordPerfect: Character Group Font Face Change subgroup info (old matched point size: %i, hash: %i, matched font index: %i, matched font point size: %i\n", m_oldMatchedPointSize, m_hash, m_matchedFontIndex, m_matchedFontPointSize));
}

void WP6CharacterGroup_FontFaceChangeSubGroup::parse(WP6HLListener *listener, const guint8 numPrefixIDs, guint16 const *prefixIDs) const
{
	WPD_DEBUG_MSG(("WordPerfect: FontFaceChangeSubGroup parsing\n"));
	// TODO: check that we have 1 prefix id
	// emit an exception otherwise
	listener->fontChange(m_matchedFontPointSize, prefixIDs[0]);
}

/*************************************************************************
 * WP6CharacterGroup_ParagraphNumberOnSubGroup
 *************************************************************************/

WP6CharacterGroup_ParagraphNumberOnSubGroup::WP6CharacterGroup_ParagraphNumberOnSubGroup(WPXInputStream *input)
{
	m_outlineHash = gsf_le_read_guint16(input);
	m_level = gsf_le_read_guint8(input);
	m_flag = gsf_le_read_guint8(input);
}

void WP6CharacterGroup_ParagraphNumberOnSubGroup::parse(WP6HLListener *listener, const guint8 numPrefixIDs, guint16 const *prefixIDs) const
{
	listener->paragraphNumberOn(m_outlineHash, m_level, m_flag);
}

/*************************************************************************
 * WP6CharacterGroup_TableDefinitionOnSubGroup
 *************************************************************************/

WP6CharacterGroup_TableDefinitionOnSubGroup::WP6CharacterGroup_TableDefinitionOnSubGroup(WPXInputStream *input)
{
	m_flags = gsf_le_read_guint8(input);
	m_position = gsf_le_read_guint8(input);
	m_leftOffset = gsf_le_read_guint16(input);
	// TODO: add the remaining table properties here
}

void WP6CharacterGroup_TableDefinitionOnSubGroup::parse(WP6HLListener *listener, const guint8 numPrefixIDs, guint16 const *prefixIDs) const
{
	listener->defineTable(m_position, m_leftOffset);
}

/*************************************************************************
 * WP6CharacterGroup_TableDefinitionOffSubGroup
 *************************************************************************/

WP6CharacterGroup_TableDefinitionOffSubGroup::WP6CharacterGroup_TableDefinitionOffSubGroup(WPXInputStream *input)
{

}

void WP6CharacterGroup_TableDefinitionOffSubGroup::parse(WP6HLListener *listener, const guint8 numPrefixIDs, guint16 const *prefixIDs) const
{
	// the table is degined now; start the table
	listener->startTable();
}

/*************************************************************************
 * WP6CharacterGroup_TableColumnSubGroup
 *************************************************************************/

WP6CharacterGroup_TableColumnSubGroup::WP6CharacterGroup_TableColumnSubGroup(WPXInputStream *input)
{
	m_flags = gsf_le_read_guint8(input);
	m_width = gsf_le_read_guint16(input);

	m_leftGutter = gsf_le_read_guint16(input);
	m_rigthGutter = gsf_le_read_guint16(input);
	m_attribWord1 = gsf_le_read_guint16(input);
	m_attribWord2 = gsf_le_read_guint16(input);
	m_alignment = gsf_le_read_guint8(input);
	m_absPosFromRight = gsf_le_read_guint16(input);
	m_numberType = gsf_le_read_guint16(input);
	m_currencyIndex = gsf_le_read_guint8(input);
}

void WP6CharacterGroup_TableColumnSubGroup::parse(WP6HLListener *listener, const guint8 numPrefixIDs, guint16 const *prefixIDs) const
{
	listener->addTableColumnDefinition(m_width, m_leftGutter, m_rigthGutter);
}

/*************************************************************************
 * WP6CharacterGroup
 *************************************************************************/

WP6CharacterGroup::WP6CharacterGroup(WPXInputStream *input) :
	WP6VariableLengthGroup(),
	m_subGroupData(NULL)
{
	_read(input);
}

WP6CharacterGroup::~WP6CharacterGroup()
{
	delete m_subGroupData;
}

void WP6CharacterGroup::_readContents(WPXInputStream *input)
{
	// this group can contain different kinds of data, thus we need to read
	// the contents accordingly
	switch (getSubGroup())
	{
		case WP6_CHARACTER_GROUP_FONT_FACE_CHANGE:
		case WP6_CHARACTER_GROUP_FONT_SIZE_CHANGE:
			m_subGroupData = new WP6CharacterGroup_FontFaceChangeSubGroup(input);
			break;
		case WP6_CHARACTER_GROUP_COLOR:
			m_subGroupData = new WP6CharacterGroup_ColorSubGroup(input);
			break;
		case WP6_CHARACTER_GROUP_CHARACTER_SHADING_CHANGE:
			m_subGroupData = new WP6CharacterGroup_CharacterShadingChangeSubGroup(input);
			break;
		case WP6_CHARACTER_GROUP_PARAGRAPH_NUMBER_ON:
			m_subGroupData = new WP6CharacterGroup_ParagraphNumberOnSubGroup(input);
			break;
		case WP6_CHARACTER_GROUP_TABLE_DEFINITION_ON:
			m_subGroupData = new WP6CharacterGroup_TableDefinitionOnSubGroup(input);
			break;
		case WP6_CHARACTER_GROUP_TABLE_DEFINITION_OFF:
			m_subGroupData = new WP6CharacterGroup_TableDefinitionOffSubGroup(input);
			break;
		case WP6_CHARACTER_GROUP_TABLE_COLUMN:
			m_subGroupData = new WP6CharacterGroup_TableColumnSubGroup(input);
			break;
		default:
			break;
	}
}

void WP6CharacterGroup::parse(WP6HLListener *listener)
{
	WPD_DEBUG_MSG(("WordPerfect: handling a Character group\n"));

	switch (getSubGroup())
	{
		case WP6_CHARACTER_GROUP_FONT_FACE_CHANGE:
		case WP6_CHARACTER_GROUP_FONT_SIZE_CHANGE:
		case WP6_CHARACTER_GROUP_COLOR:
		case WP6_CHARACTER_GROUP_CHARACTER_SHADING_CHANGE:
		case WP6_CHARACTER_GROUP_PARAGRAPH_NUMBER_ON:
			m_subGroupData->parse(listener, getNumPrefixIDs(), getPrefixIDs());
			break;
		case WP6_CHARACTER_GROUP_PARAGRAPH_NUMBER_OFF:
			listener->paragraphNumberOff();
			break;
		case WP6_CHARACTER_GROUP_TABLE_DEFINITION_ON:
			WPD_DEBUG_MSG(("WordPerfect: TABLE Definition ON\n"));
			m_subGroupData->parse(listener, getNumPrefixIDs(), getPrefixIDs());
			break;
		case WP6_CHARACTER_GROUP_TABLE_DEFINITION_OFF:
			WPD_DEBUG_MSG(("WordPerfect: TABLE Definition OFF\n"));
			m_subGroupData->parse(listener, getNumPrefixIDs(), getPrefixIDs());
			break;
		case WP6_CHARACTER_GROUP_TABLE_COLUMN:
			WPD_DEBUG_MSG(("WordPerfect: Table Column\n"));
			m_subGroupData->parse(listener, getNumPrefixIDs(), getPrefixIDs());
			break;
		default: // something else we don't support yet
			break;
	}
}
