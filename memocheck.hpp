#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/print.hpp>

class memocheck : public eosio::contract {
public:
	memocheck(account_name self) :
		eosio::contract(self)
	{}
	void on_deposit(account_name from, eosio::extended_asset quantity);
	void transfer(uint64_t sender, uint64_t receiver);
};
