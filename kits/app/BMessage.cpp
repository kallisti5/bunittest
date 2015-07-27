/*
 * Copyright 2015 Haiku, Inc. All rights reserved
 * Released under the terms of the MIT license.
 *
 * Authors:
 *	Alexander von Gluck IV <kallisti5@unixzen.com>
 */


#include <Message.h>
#include <String.h>

#include <stdio.h>

#include "tpunit++.hpp"


struct BMessageFixture
	: public tpunit::TestFixture
{
	BMessageFixture() : tpunit::TestFixture(
		TEST(BMessageFixture::New),
		TEST(BMessageFixture::AddString),
		TEST(BMessageFixture::AddInt8),
		TEST(BMessageFixture::AddUInt8)
	)
	{}


	void
	New()
	{
		BMessage message;
		ASSERT_TRUE(message.IsEmpty());
		ASSERT_FALSE(message.IsSystem());
		ASSERT_FALSE(message.IsReply());
	}


	void
	AddString()
	{
		BMessage message;
		const char* string = "ThisIsATestString";
		for (int i = 0; i < 255; i++) {
			char key[16];
			snprintf(key, 16, "test_string_%d", i);
			ASSERT_EQUAL(message.AddString(key, string), B_OK);
			ASSERT_TRUE(message.HasString(key));
		}
	}


	void
	AddInt8()
	{
		BMessage message;
		int8 test = -105;
		for (int i = 0; i < 255; i++) {
			char key[16];
			snprintf(key, 16, "test_int8_%d", i);
			ASSERT_EQUAL(message.AddInt8(key, test), B_OK);
			ASSERT_TRUE(message.HasInt8(key));
		}
	}


	void
	AddUInt8()
	{
		BMessage message;
		uint8 test = 123;
		for (int i = 0; i < 255; i++) {
			char key[16];
			snprintf(key, 16, "test_uint8_%d", i);
			ASSERT_EQUAL(message.AddUInt8(key, test), B_OK);
			ASSERT_TRUE(message.HasUInt8(key));
		}
	}


} __BMessageFixture;
