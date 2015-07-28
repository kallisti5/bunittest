/*
 * Copyright 2015 Haiku, Inc. All rights reserved
 * Released under the terms of the MIT license.
 *
 * Authors:
 *	Alexander von Gluck IV <kallisti5@unixzen.com>
 */


#include <NetworkAddress.h>
#include <String.h>

#include <arpa/inet.h>

#include "tpunit++.hpp"


struct BNetworkAddressFixture
	: public tpunit::TestFixture
{
	BNetworkAddressFixture() : tpunit::TestFixture(
		TEST(BNetworkAddressFixture::SetTo_IPv4),
		TEST(BNetworkAddressFixture::SetTo_IPv6),
		TEST(BNetworkAddressFixture::SetAddress_IPv4),
		TEST(BNetworkAddressFixture::SetAddress_IPv6),
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
		EXPECT_TRUE(address.IsEmpty());
		EXPECT_EQUAL(address.SetTo("127.0.0.1"), B_OK);
		EXPECT_FALSE(address.IsEmpty());
		EXPECT_EQUAL(address.Family(), AF_INET);
	}


	void
	SetTo_IPv6()
	{
		BNetworkAddress address;
		ASSERT_EQUAL(address.InitCheck(), B_OK);
		EXPECT_TRUE(address.IsEmpty());
		EXPECT_EQUAL(address.SetTo("::1"), B_OK);
		EXPECT_FALSE(address.IsEmpty());
		EXPECT_EQUAL(address.Family(), AF_INET6);
	}


	void
	SetAddress_IPv4()
	{
		BNetworkAddress address;
		ASSERT_EQUAL(address.InitCheck(), B_OK);
		EXPECT_TRUE(address.IsEmpty());

		struct sockaddr_in socketAddr;
		ASSERT_GREATER_THAN(inet_pton(AF_INET, "192.168.1.1",
			&(socketAddr.sin_addr)), 0);
		ASSERT_EQUAL(address.SetAddress(socketAddr.sin_addr.s_addr), B_OK);

		ASSERT_EQUAL(address.ToString().String(), "192.168.1.1");
	}


	void
	SetAddress_IPv6()
	{
		//BNetworkAddress address;
		//ASSERT_EQUAL(address.InitCheck(), B_OK);
		//ASSERT_TRUE(address.IsEmpty());

		//struct sockaddr_in6 socketAddr;
		//ASSERT_GREATER_THAN(inet_pton(AF_INET6, "feed::dead:beef",
		//	&(socketAddr.sin6_addr)), 0);
		//ASSERT_EQUAL(address.SetAddress(&(socketAddr.sin6_addr.s6_addr)), B_OK);

		//ASSERT_EQUAL(address.ToString().String(), "feed::dead:beef");
	}


	void
	Unset_IPv4()
	{
		BNetworkAddress address("127.0.0.1");
		EXPECT_FALSE(address.IsEmpty());
		address.Unset();
		EXPECT_TRUE(address.IsEmpty());
	}


	void
	Unset_IPv6()
	{
		BNetworkAddress address("::1");
		EXPECT_FALSE(address.IsEmpty());
		address.Unset();
		EXPECT_TRUE(address.IsEmpty());
	}


	void
	IsLocal()
	{
		BNetworkAddress v4Local(AF_INET, "127.0.0.1");
		BNetworkAddress v6Local(AF_INET6, "::1");
		EXPECT_TRUE(v4Local.IsLocal());
		EXPECT_TRUE(v6Local.IsLocal());

		BNetworkAddress v4Remote(AF_INET, "8.8.8.8");
		BNetworkAddress v6Remote(AF_INET6, "2607:f8b0:4002:c09::8b");
		EXPECT_FALSE(v4Remote.IsLocal());
		EXPECT_FALSE(v6Remote.IsLocal());
	}


	void
	IsBroadcast()
	{
		BNetworkAddress v4Address("255.255.255.255");
		EXPECT_TRUE(v4Address.IsBroadcast());

		// XXX: No broadcast on IPv6
	}


	void
	IsMulticast()
	{
		BNetworkAddress v4Address("224.0.0.1");
		BNetworkAddress v6Address("ffx2::");

		EXPECT_TRUE(v4Address.IsMulticast());
		EXPECT_TRUE(v6Address.IsMulticast());
	}


	void
	SetToBroadcast()
	{
		BNetworkAddress v4Address;
		v4Address.SetToBroadcast(AF_INET);
		EXPECT_TRUE(v4Address.IsBroadcast());
	}


	void
	ToString()
	{
		BNetworkAddress v4Address("192.168.1.100");
		BNetworkAddress v6Address("feed::dead:beef");

		EXPECT_EQUAL(v4Address.ToString(false).String(), "192.168.1.100");
		EXPECT_EQUAL(v6Address.ToString(false).String(), "feed::dead:beef");
	}


	void
	Equals()
	{
		BNetworkAddress v4AddressA("192.168.1.100");
		BNetworkAddress v4AddressB("192.168.1.100");
		BNetworkAddress v6AddressA("feed::dead:beef");
		BNetworkAddress v6AddressB("feed::dead:beef");

		EXPECT_TRUE(v4AddressA.Equals(v4AddressB));
		EXPECT_TRUE(v6AddressA.Equals(v6AddressB));
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

		EXPECT_EQUAL(v4Address, unflattened);
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

		EXPECT_EQUAL(v6Address, unflattened);
	}


	void
	SetToWildcard_IPv4()
	{
		BNetworkAddress v4Address;
		v4Address.SetToWildcard(AF_INET);

		EXPECT_EQUAL(v4Address.Family(), AF_INET);
		EXPECT_EQUAL(v4Address.Port(), 0);
		EXPECT_TRUE(v4Address.IsWildcard());
	}


	void
	SetToWildcard_IPv6()
	{
		BNetworkAddress v6Address;
		v6Address.SetToWildcard(AF_INET6);

		EXPECT_EQUAL(v6Address.Family(), AF_INET6);
		EXPECT_EQUAL(v6Address.Port(), 0);
		EXPECT_TRUE(v6Address.IsWildcard());
	}


} __BNetworkAddressFixture;
