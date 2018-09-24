#undef EOSIO_ABI
#define EOSIO_ABI(TYPE, MEMBERS)\
extern "C" {\
	void apply(uint64_t receiver, uint64_t code, uint64_t action) {\
		auto self = receiver;\
		if (action == N(onerror)) {\
			eosio_assert(code == N(eosio), "onerror action's are only valid from the \"eosio\" system account");\
		}\
		if (code == self || action == N(onerror) || code == N(eosio.token)) {\
			TYPE thiscontract(self);\
			switch (action) {\
				EOSIO_API(TYPE, MEMBERS)\
			}\
		}\
	}\
}

int8_t hex(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	eosio_assert(false, "Invalid hex");
	return 0;
}

void memocheck::transfer(uint64_t sender, uint64_t receiver) {
	struct transfer_t {
		account_name from;
		account_name to;
		eosio::asset quantity;
		std::string memo;
	} data = eosio::unpack_action_data<transfer_t>();
	eosio_assert(data.quantity.amount > 0, "Transfer must be positive");
	eosio_assert(data.quantity.is_valid(), "Invalid token transfer");
	if (data.from != this->_self) {
		eosio_assert(data.quantity.symbol == eosio::string_to_symbol(4, "EOS"), "Only EOS Deposits");
		eosio_assert(data.memo.size() == 20, "Memo should contain 20 characters");
		char memo[10];
		for (int8_t i = 0; i < 10; i++) {
			int8_t ch = hex(data.memo[i*2]);
			int8_t cl = hex(data.memo[i*2+1]);
			memo[i] = (ch << 4) + cl;
		}
		checksum256 hash;
		sha256(memo, 8, &hash);
		eosio_assert((hash.hash[0] == static_cast<uint8_t>(memo[8])) && (hash.hash[1] == static_cast<uint8_t>(memo[9])), "Invalid checksum");
		this->on_deposit(data.from, eosio::extended_asset(data.quantity, N(eosio.token)));
	}
}
