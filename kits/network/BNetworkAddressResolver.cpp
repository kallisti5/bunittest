/*
 * Copyright 2015 Haiku, Inc. All rights reserved
 * Released under the terms of the MIT license.
 *
 * Authors:
 *	Alexander von Gluck IV <kallisti5@unixzen.com>
 */


#include <NetworkAddress.h>
#include <NetworkAddressResolver.h>
#include <String.h>

#include "tpunit++.hpp"


struct BNetworkAddressResolverFixture
	: public tpunit::TestFixture
{
	BNetworkAddressResolverFixture() : tpunit::TestFixture(
		TEST(BNetworkAddressResolverFixture::SetTo_IPv4),
		TEST(BNetworkAddressResolverFixture::SetTo_IPv6),
		TEST(BNetworkAddressResolverFixture::Unset_IPv4),
		TEST(BNetworkAddressResolverFixture::Unset_IPv6)
	)
	{}


	void
	SetTo_IPv4()
	{
		BNetworkAddressResolver resolver;
		ASSERT_EQUAL(resolver.SetTo("8.8.8.8", AF_INET), B_OK);
		ASSERT_EQUAL(resolver.InitCheck(), B_OK);
	}


	void
	SetTo_IPv6()
	{
		BNetworkAddressResolver resolver;
		ASSERT_EQUAL(resolver.SetTo("2001:4860:4860::8888", AF_INET6), B_OK);
		ASSERT_EQUAL(resolver.InitCheck(), B_OK);
	}


	void
	Unset_IPv4()
	{
		BNetworkAddressResolver resolver("8.8.8.8");
		ASSERT_EQUAL(resolver.InitCheck(), B_OK);
		resolver.Unset();
		ASSERT_NOT_EQUAL(resolver.InitCheck(), B_OK);
	}


	void
	Unset_IPv6()
	{
		BNetworkAddressResolver resolver("2001:4860:4860::8888");
		ASSERT_EQUAL(resolver.InitCheck(), B_OK);
		resolver.Unset();
		ASSERT_NOT_EQUAL(resolver.InitCheck(), B_OK);
	}


} __BNetworkAddressResolverFixture;
