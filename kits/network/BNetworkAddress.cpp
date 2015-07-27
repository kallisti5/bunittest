/*
 * Copyright 2015 Haiku, Inc. All rights reserved
 * Released under the terms of the MIT license.
 *
 * Authors:
 *	Alexander von Gluck IV <kallisti5@unixzen.com>
 */


#include <NetworkAddress.h>
#include <String.h>

#include "tpunit++.hpp"


struct BNetworkAddressFixture
	: public tpunit::TestFixture
{
	BNetworkAddressFixture() : tpunit::TestFixture(
		TEST(BNetworkAddressFixture::SetTo_IPv4),
		TEST(BNetworkAddressFixture::SetTo_IPv6),
		TEST(BNetworkAddressFixture::Unset_IPv4),
		TEST(BNetworkAddressFixture::Unset_IPv6),
		TEST(BNetworkAddressFixture::IsLocal),
		TEST(BNetworkAddressFixture::IsBroadcast),
		TEST(BNetworkAddressFixture::SetToBroadcast),
		TEST(BNetworkAddressFixture::IsMulticast),
		TEST(BNetworkAddressFixture::ToString),
		TEST(BNetworkAddressFixture::Flatten_IPv4),
		TEST(BNetworkAddressFixture::Flatten_IPv6),
		TEST(BNetworkAddressFixture::Equals),
		TEST(BNetworkAddressFixture::SetToWildcard_IPv4),
		TEST(BNetworkAddressFixture::SetToWildcard_IPv6)
	)
	{}


	void
	SetTo_IPv4()
	{
		BNetworkAddress address;
		ASSERT_EQUAL(address.InitCheck(), B_OK);
		ASSERT_TRUE(address.IsEmpty());
		address.SetTo("127.0.0.1");
		ASSERT_FALSE(address.IsEmpty());
		ASSERT_EQUAL(address.Family(), AF_INET);
	}


	void
	SetTo_IPv6()
	{
		BNetworkAddress address;
		ASSERT_EQUAL(address.InitCheck(), B_OK);
		ASSERT_TRUE(address.IsEmpty());
		address.SetTo("::1");
		ASSERT_FALSE(address.IsEmpty());
		ASSERT_EQUAL(address.Family(), AF_INET6);
	}


	void
	Unset_IPv4()
	{
		BNetworkAddress address("127.0.0.1");
		address.Unset();
		ASSERT_TRUE(address.IsEmpty());
	}


	void
	Unset_IPv6()
	{
		BNetworkAddress address("::1");
		address.Unset();
		ASSERT_TRUE(address.IsEmpty());
	}


	void
	IsLocal()
	{
		BNetworkAddress v4Local(AF_INET, "127.0.0.1");
		BNetworkAddress v6Local(AF_INET6, "::1");
		ASSERT_TRUE(v4Local.IsLocal());
		ASSERT_TRUE(v6Local.IsLocal());

		BNetworkAddress v4Remote(AF_INET, "8.8.8.8");
		BNetworkAddress v6Remote(AF_INET6, "2607:f8b0:4002:c09::8b");
		ASSERT_FALSE(v4Remote.IsLocal());
		ASSERT_FALSE(v6Remote.IsLocal());
	}


	void
	IsBroadcast()
	{
		BNetworkAddress v4Address("255.255.255.255");
		ASSERT_TRUE(v4Address.IsBroadcast());

		// XXX: No broadcast on IPv6
	}


	void
	IsMulticast()
	{
		BNetworkAddress v4Address("224.0.0.1");
		BNetworkAddress v6Address("ffx2::");

		ASSERT_TRUE(v4Address.IsMulticast());
		ASSERT_TRUE(v6Address.IsMulticast());
	}


	void
	SetToBroadcast()
	{
		BNetworkAddress v4Address;
		v4Address.SetToBroadcast(AF_INET);
		ASSERT_TRUE(v4Address.IsBroadcast());
	}


	void
	ToString()
	{
		BNetworkAddress v4Address("192.168.1.100");
		BNetworkAddress v6Address("feed::dead:beef");

		ASSERT_EQUAL(v4Address.ToString(false).String(), "192.168.1.100");
		ASSERT_EQUAL(v6Address.ToString(false).String(), "feed::dead:beef");
	}


	void
	Equals()
	{
		BNetworkAddress v4AddressA("192.168.1.100");
		BNetworkAddress v4AddressB("192.168.1.100");
		BNetworkAddress v6AddressA("feed::dead:beef");
		BNetworkAddress v6AddressB("feed::dead:beef");

		ASSERT_TRUE(v4AddressA.Equals(v4AddressB));
		ASSERT_TRUE(v6AddressA.Equals(v6AddressB));
	}


	void
	Flatten_IPv4()
	{
		BNetworkAddress v4Address(AF_INET, "localhost", 9999);

		char buffer[256];
		ASSERT_EQUAL(v4Address.Flatten(buffer, sizeof(buffer)), B_OK);

		BNetworkAddress unflattened;
		ASSERT_EQUAL(v4Address.Unflatten(B_NETWORK_ADDRESS_TYPE, buffer,
			sizeof(buffer)), B_OK);

		ASSERT_EQUAL(v4Address, unflattened);
	}


	void
	Flatten_IPv6()
	{
		BNetworkAddress v6Address(AF_INET6, "localhost", 9999);

		char buffer[256];
		ASSERT_EQUAL(v6Address.Flatten(buffer, sizeof(buffer)), B_OK);

		BNetworkAddress unflattened;
		ASSERT_EQUAL(v6Address.Unflatten(B_NETWORK_ADDRESS_TYPE, buffer,
			sizeof(buffer)), B_OK);

		ASSERT_EQUAL(v6Address, unflattened);
	}


	void
	SetToWildcard_IPv4()
	{
		BNetworkAddress v4Address;
		v4Address.SetToWildcard(AF_INET);

		ASSERT_EQUAL(v4Address.Family(), AF_INET);
		ASSERT_EQUAL(v4Address.Port(), 0);
		ASSERT_TRUE(v4Address.IsWildcard());
	}


	void
	SetToWildcard_IPv6()
	{
		BNetworkAddress v6Address;
		v6Address.SetToWildcard(AF_INET6);

		ASSERT_EQUAL(v6Address.Family(), AF_INET6);
		ASSERT_EQUAL(v6Address.Port(), 0);
		ASSERT_TRUE(v6Address.IsWildcard());
	}


} __BNetworkAddressFixture;
