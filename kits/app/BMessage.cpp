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
		TEST(BMessageFixture::AddUInt8),
		TEST(BMessageFixture::AddInt16),
		TEST(BMessageFixture::AddUInt16),
		TEST(BMessageFixture::AddInt32),
		TEST(BMessageFixture::AddUInt32),
		TEST(BMessageFixture::AddInt64),
		TEST(BMessageFixture::AddUInt64)
	)
	{}


	void
	New()
	{
		BMessage message;
		EXPECT_TRUE(message.IsEmpty());
		EXPECT_FALSE(message.IsSystem());
		EXPECT_FALSE(message.IsReply());
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


	void
	AddInt16()
	{
		BMessage message;
		int16 test = -105;
		for (int i = 0; i < 255; i++) {
			char key[16];
			snprintf(key, 16, "test_int16_%d", i);
			ASSERT_EQUAL(message.AddInt16(key, test), B_OK);
			ASSERT_TRUE(message.HasInt16(key));
		}
	}


	void
	AddUInt16()
	{
		BMessage message;
		uint16 test = 123;
		for (int i = 0; i < 255; i++) {
			char key[16];
			snprintf(key, 16, "test_uint16_%d", i);
			ASSERT_EQUAL(message.AddUInt16(key, test), B_OK);
			ASSERT_TRUE(message.HasUInt16(key));
		}
	}


	void
	AddInt32()
	{
		BMessage message;
		int32 test = -105;
		for (int i = 0; i < 255; i++) {
			char key[16];
			snprintf(key, 16, "test_int32_%d", i);
			ASSERT_EQUAL(message.AddInt32(key, test), B_OK);
			ASSERT_TRUE(message.HasInt32(key));
		}
	}


	void
	AddUInt32()
	{
		BMessage message;
		uint32 test = 123;
		for (int i = 0; i < 255; i++) {
			char key[16];
			snprintf(key, 16, "test_uint32_%d", i);
			ASSERT_EQUAL(message.AddUInt32(key, test), B_OK);
			ASSERT_TRUE(message.HasUInt32(key));
		}
	}


	void
	AddInt64()
	{
		BMessage message;
		int64 test = -105;
		for (int i = 0; i < 255; i++) {
			char key[16];
			snprintf(key, 16, "test_int64_%d", i);
			ASSERT_EQUAL(message.AddInt64(key, test), B_OK);
			ASSERT_TRUE(message.HasInt64(key));
		}
	}


	void
	AddUInt64()
	{
		BMessage message;
		uint64 test = 123;
		for (int i = 0; i < 255; i++) {
			char key[16];
			snprintf(key, 16, "test_uint64_%d", i);
			ASSERT_EQUAL(message.AddUInt64(key, test), B_OK);
			ASSERT_TRUE(message.HasUInt64(key));
		}
	}


} __BMessageFixture;
