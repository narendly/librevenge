/* libwpd
 * Copyright (C) 2002 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
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

#ifndef LIBWPD_SUPPORT_H
#define LIBWPD_SUPPORT_H
#include <glib.h>

#ifndef _MSC_VER
#include <stdint.h>
#else
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
#endif

extern const uint16_t asciiMap[];
extern const uint16_t extendedInternationalCharacterMap[];
extern const uint16_t multinationalMap[];
extern const uint16_t phoneticMap[];
extern const uint16_t boxdrawingMap[];
extern const uint16_t typographicMap[];
extern const uint16_t iconicMap[];
extern const uint16_t mathMap[];
extern const uint16_t mathextMap[];
extern const uint16_t greekMap[];
extern const uint16_t hebrewMap[];
extern const uint16_t cyrillicMap[];
extern const uint16_t japaneseMap[];
extern const uint16_t *tibetanMap1[];

int extendedCharacterToUCS2(uint8_t character, uint8_t characterSet,
			    const uint16_t **chars);

enum WPXFileType { WP6_DOCUMENT, WP5_DOCUMENT, WP42_DOCUMENT, OTHER };
enum WPXNumberingType { ARABIC, LOWERCASE, UPPERCASE, LOWERCASE_ROMAN, UPPERCASE_ROMAN };
enum WPXNoteType { FOOTNOTE, ENDNOTE };
enum WPXHeaderFooterType { HEADER, FOOTER };
enum WPXHeaderFooterOccurence { ODD, EVEN, ALL };
enum WPXFormOrientation { PORTRAIT, LANDSCAPE };
enum WPXTabAlignment { LEFT, RIGHT, CENTER, DECIMAL, BAR };

enum WPDConfidence { WPD_CONFIDENCE_NONE=0, WPD_CONFIDENCE_POOR, WPD_CONFIDENCE_LIKELY, WPD_CONFIDENCE_GOOD, WPD_CONFIDENCE_EXCELLENT};

// ATTRIBUTE bits
#define WPX_EXTRALARGE_BIT 1
#define WPX_VERYLARGE_BIT 2
#define WPX_LARGE_BIT 4
#define WPX_SMALLPRINT_BIT 8
#define WPX_FINEPRINT_BIT 16
#define WPX_SUPERSCRIPT_BIT 32
#define WPX_SUBSCRIPT_BIT 64
#define WPX_OUTLINE_BIT 128
#define WPX_ITALICS_BIT 256
#define WPX_SHADOW_BIT 512
#define WPX_REDLINE_BIT 1024
#define WPX_DOUBLE_UNDERLINE_BIT 2048
#define WPX_BOLD_BIT 4096
#define WPX_STRIKEOUT_BIT 8192
#define WPX_UNDERLINE_BIT 16384
#define WPX_SMALL_CAPS_BIT 32768
#define WPX_BLINK_BIT 65536
#define WPX_REVERSEVIDEO_BIT 131072

// JUSTIFICATION bits.
#define WPX_PARAGRAPH_JUSTIFICATION_LEFT 0x00
#define WPX_PARAGRAPH_JUSTIFICATION_FULL 0x01
#define WPX_PARAGRAPH_JUSTIFICATION_CENTER 0x02
#define WPX_PARAGRAPH_JUSTIFICATION_RIGHT 0x03
#define WPX_PARAGRAPH_JUSTIFICATION_FULL_ALL_LINES 0x04
#define WPX_PARAGRAPH_JUSTIFICATION_RESERVED 0x05

// TABLE POSITION bits.
#define WPX_TABLE_POSITION_ALIGN_WITH_LEFT_MARGIN 0x00
#define WPX_TABLE_POSITION_ALIGN_WITH_RIGHT_MARGIN 0x01
#define WPX_TABLE_POSITION_CENTER_BETWEEN_MARGINS 0x02
#define WPX_TABLE_POSITION_FULL 0x03
#define WPX_TABLE_POSITION_ABSOLUTE_FROM_LEFT_MARGIN 0x04

// TABLE CELL BORDER bits
const uint8_t WPX_TABLE_CELL_LEFT_BORDER_OFF = 0x01;
const uint8_t WPX_TABLE_CELL_RIGHT_BORDER_OFF = 0x02;
const uint8_t WPX_TABLE_CELL_TOP_BORDER_OFF = 0x04;
const uint8_t WPX_TABLE_CELL_BOTTOM_BORDER_OFF = 0x08;

// BREAK bits
#define WPX_PAGE_BREAK 0x00
#define WPX_SOFT_PAGE_BREAK 0x01
#define WPX_COLUMN_BREAK 0x02

// Generic bits
#define WPX_LEFT 0x00
#define WPX_RIGHT 0x01
#define WPX_CENTER 0x02

typedef struct _RGBSColor RGBSColor;
struct _RGBSColor
{
	_RGBSColor(uint8_t r, uint8_t g, uint8_t b, uint8_t s);
	_RGBSColor(); // initializes all values to 0
	uint8_t m_r;
	uint8_t m_g;
 	uint8_t m_b;
	uint8_t m_s;
};

typedef struct _WPXColumnDefinition WPXColumnDefinition;
struct _WPXColumnDefinition
{
	_WPXColumnDefinition(); // initializes all values to 0
	float m_width;
	float m_leftGutter;
	float m_rightGutter;
};

typedef struct _WPXTabStop WPXTabStop;
struct _WPXTabStop
{
	_WPXTabStop(float position, WPXTabAlignment alignment, uint16_t leaderCharacter, uint8_t leaderNumSpaces);
	_WPXTabStop();
	float m_position;
	WPXTabAlignment m_alignment;
	uint16_t m_leaderCharacter;
	uint8_t m_leaderNumSpaces;
};

// UCSString: minimal string class, basically an object-oriented wrapper around glib's UCS4 string
// (so we don't have to pull in yet more dependencies)
class UCSString
{
public:
	UCSString();
	UCSString(const UCSString &);
	~UCSString();
	// UCS2 conversion not needed (yet)
	// const uint16_t * getUCS2();
	void append(uint32_t);
	void append(const UCSString &);
	void append(const char *);
	void clear();

	const uint32_t * getUCS4() const { return (uint32_t *)m_stringBuf->data; }
	const int getLen() const { return m_stringBuf->len; }

private:
	GArray *m_stringBuf;
};

class UTF8String
{
public:
	UTF8String();
	UTF8String(const UTF8String &);
	UTF8String(const UCSString &, bool convertToValidXML = false);
	//UTF8String(const char *);
	UTF8String(const char *str);
	//UTF8String(const char *format, ...);
	~UTF8String() { g_string_free(m_buf, TRUE); }

	const char * getUTF8() const { return m_buf->str; }
	const int getLen() const { return m_buf->len; }

	void sprintf(const char *format, ...);
	//UTF8String & operator=(const UTF8String &);

private:
	GString *m_buf;
};

class VersionException
{
	// needless to say, we could flesh this class out a bit
};

class FileException
{
	// needless to say, we could flesh this class out a bit
};

class ParseException
{
	// needless to say, we could flesh this class out a bit
};

class GenericException
{
	// needless to say, we could flesh this class out a bit
};

class UnsupportedEncryptionException
{
	// needless to say, we could flesh this class out a bit
};

#endif
