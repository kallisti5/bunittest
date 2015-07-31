/*
 * Copyright 2015 Haiku, Inc. All rights reserved
 * Released under the terms of the MIT license.
 *
 * Authors:
 *	Alexander von Gluck IV <kallisti5@unixzen.com>
 */


#include <OS.h>

#include <string.h>

#include "tpunit++.hpp"


struct AreaFixture
	: public tpunit::TestFixture
{
	AreaFixture() : tpunit::TestFixture(
		TEST(AreaFixture::CreateArea_128K),
		TEST(AreaFixture::CreateArea_512K),
		TEST(AreaFixture::CreateArea_1M),
		TEST(AreaFixture::CreateArea_10M),
		TEST(AreaFixture::CreateArea_100M),
		TEST(AreaFixture::CreateArea_500M),
		TEST(AreaFixture::CreateArea_1G),
		TEST(AreaFixture::TestArea_1M),
		TEST(AreaFixture::TestArea_10M),
		TEST(AreaFixture::TestArea_100M),
		TEST(AreaFixture::TestArea_1G)
	)
	{}


	void
	CreateArea_128K()
	{
		void* address;
		area_id area = create_area("128k Test", &address, B_ANY_ADDRESS,
			131072, B_FULL_LOCK, B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_512K()
	{
		void* address;
		area_id area = create_area("512k Test", &address, B_ANY_ADDRESS,
			524288, B_FULL_LOCK, B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_1M()
	{
		void* address;
		area_id area = create_area("1MiB Test", &address, B_ANY_ADDRESS,
			1048576, B_FULL_LOCK, B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_10M()
	{
		void* address;
		area_id area = create_area("10MiB Test", &address, B_ANY_ADDRESS,
			10485760, B_FULL_LOCK, B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_100M()
	{
		void* address;
		area_id area = create_area("100MiB Test", &address, B_ANY_ADDRESS,
			104857600, B_FULL_LOCK, B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_500M()
	{
		void* address;
		area_id area = create_area("500MiB Test", &address, B_ANY_ADDRESS,
			524288000, B_FULL_LOCK, B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_1G()
	{
		void* address;
		area_id area = create_area("1GiB Test", &address, B_ANY_ADDRESS,
			1073741824, B_FULL_LOCK, B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	TestArea_1M()
	{
		size_t testSize = 1048576;
		char* address;
		area_id area = create_area("1MiB Test", (void**)&address,
			B_ANY_ADDRESS, testSize, B_NO_LOCK,
			B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		memset(address, 0x0, testSize);
		for (size_t position = 0; position < testSize; position++)
			EXPECT_EQUAL(address[position], 0x0);
		memset(address, 0xF, testSize);
		for (size_t position = 0; position < testSize; position++)
			EXPECT_EQUAL(address[position], 0xF);

		// tpunit doesn't seem to catch :-/
		//EXPECT_ANY_THROW(address[testSize + 1] = 0);

		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	TestArea_10M()
	{
		size_t testSize = 10485760;
		char* address;
		area_id area = create_area("10MiB Test", (void**)&address,
			B_ANY_ADDRESS, testSize, B_NO_LOCK,
			B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		memset(address, 0x0, testSize);
		for (size_t position = 0; position < testSize; position++)
			EXPECT_EQUAL(address[position], 0x0);
		memset(address, 0xF, testSize);
		for (size_t position = 0; position < testSize; position++)
			EXPECT_EQUAL(address[position], 0xF);

		// tpunit doesn't seem to catch :-/
		//EXPECT_ANY_THROW(address[testSize + 1] = 0);

		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	TestArea_100M()
	{
		size_t testSize = 104857600;
		char* address;
		area_id area = create_area("100MiB Test", (void**)&address,
			B_ANY_ADDRESS, testSize, B_NO_LOCK,
			B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		memset(address, 0x0, testSize);
		for (size_t position = 0; position < testSize; position++)
			EXPECT_EQUAL(address[position], 0x0);
		memset(address, 0xF, testSize);
		for (size_t position = 0; position < testSize; position++)
			EXPECT_EQUAL(address[position], 0xF);

		// tpunit doesn't seem to catch :-/
		//EXPECT_ANY_THROW(address[testSize + 1] = 0);

		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	TestArea_1G()
	{
		size_t testSize = 1048576000;
		char* address;
		area_id area = create_area("1GiB Test", (void**)&address,
			B_ANY_ADDRESS, testSize, B_NO_LOCK,
			B_READ_AREA | B_WRITE_AREA);
		ASSERT_TRUE(area >= 0);
		memset(address, 0x0, testSize);
		for (size_t position = 0; position < testSize; position++)
			EXPECT_EQUAL(address[position], 0x0);
		memset(address, 0xF, testSize);
		for (size_t position = 0; position < testSize; position++)
			EXPECT_EQUAL(address[position], 0xF);

		// tpunit doesn't seem to catch :-/
		//EXPECT_ANY_THROW(address[testSize + 1] = 0);

		EXPECT_EQUAL(delete_area(area), B_OK);
	}

} __AreaFixture;
