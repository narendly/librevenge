/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 */

#ifndef RVNGBINARYDATATEST_H
#define RVNGBINARYDATATEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace test
{

class RVNGBinaryDataTest : public CPPUNIT_NS::TestFixture
{
public:
	virtual void setUp();
	virtual void tearDown();

private:
	CPPUNIT_TEST_SUITE(RVNGBinaryDataTest);
	CPPUNIT_TEST(testConstruction);
	CPPUNIT_TEST(testAppend);
	CPPUNIT_TEST(testClear);
	CPPUNIT_TEST(testBase64);
	CPPUNIT_TEST(testStream);
	CPPUNIT_TEST_SUITE_END();

private:
	void testConstruction();
	void testAppend();
	void testClear();
	void testBase64();
	void testStream();
};

}

#endif // RVNGBINARYDATATEST_H

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
