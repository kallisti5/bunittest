/*
 * Copyright 2015 Haiku, Inc. All rights reserved
 * Released under the terms of the MIT license.
 *
 * Authors:
 *	Alexander von Gluck IV <kallisti5@unixzen.com>
 */


#include <OS.h>

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
		TEST(AreaFixture::CreateArea_1G)
	)
	{}


	void
	CreateArea_128K()
	{
		void* address;
		area_id area = create_area("128k Test", &address, B_ANY_ADDRESS,
			131072, B_FULL_LOCK, B_READ_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_512K()
	{
		void* address;
		area_id area = create_area("512k Test", &address, B_ANY_ADDRESS,
			524288, B_FULL_LOCK, B_READ_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_1M()
	{
		void* address;
		area_id area = create_area("1MiB Test", &address, B_ANY_ADDRESS,
			1048576, B_FULL_LOCK, B_READ_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_10M()
	{
		void* address;
		area_id area = create_area("10MiB Test", &address, B_ANY_ADDRESS,
			10485760, B_FULL_LOCK, B_READ_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_100M()
	{
		void* address;
		area_id area = create_area("100MiB Test", &address, B_ANY_ADDRESS,
			104857600, B_FULL_LOCK, B_READ_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_500M()
	{
		void* address;
		area_id area = create_area("500MiB Test", &address, B_ANY_ADDRESS,
			524288000, B_FULL_LOCK, B_READ_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}

	void
	CreateArea_1G()
	{
		void* address;
		area_id area = create_area("1GiB Test", &address, B_ANY_ADDRESS,
			1073741824, B_FULL_LOCK, B_READ_AREA);
		ASSERT_TRUE(area >= 0);
		EXPECT_EQUAL(delete_area(area), B_OK);
	}
} __AreaFixture;
