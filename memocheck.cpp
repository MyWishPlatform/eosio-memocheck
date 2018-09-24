#include "memocheck.hpp"
#include "override.hpp"

void memocheck::on_deposit(account_name from, eosio::extended_asset quantity) {
	eosio::print("HELLO WORLD");
}

EOSIO_ABI(memocheck, (transfer))
