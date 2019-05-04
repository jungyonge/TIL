/**
*  @file
*  @copyright defined in eos/LICENSE.txt
*/

#include "test.hpp"

namespace eosio {

	void token::create(account_name issuer, asset maximum_supply)
	{
		require_auth(_self);

		auto sym = maximum_supply.symbol;
		eosio_assert(sym.is_valid(), "Invalid symbol name");
		eosio_assert(maximum_supply.is_valid(), "Invalid Supply");
		eosio_assert(maximum_supply.amount > 0, "Max-supply must be positive");

		stats statstable(_self, sym.name());
		auto existing = statstable.find(sym.name());
		eosio_assert(existing == statstable.end(), "Tokenwith symbol already exists");

		statstable.emplace(_self, [&](auto& s) {
			s.supply.symbol = maximum_supply.symbol;
			s.max_supply = maximum_supply;
			s.issuer = issuer;
		});
	}

	void token::issue(account_name to, asset quantity, string memo)
	{
		auto sym = quantity.symbol;
		eosio_assert(sym.is_valid(), "Invalid symbol name");
		eosio_assert(memo.size() <= 256, "Memo has more than 256 bytes");

		auto sym_name = sym.name();
		stats statstable(_self, sym_name);
		auto existing = statstable.find(sym_name);
		eosio_assert(existing != statstable.end(), "Token with symbol does now exist, Create token before issue");
		const auto& st = *existing;

		require_auth(st.issuer);
		eosio_assert(quantity.is_valid(), "Invalid quantity");
		eosio_assert(quantity.amount > 0, "Must issue positive quantity");

		eosio_assert(quantity.symbol == st.supply.symbol, "Symbol precision mismatch");
		eosio_assert(quantity.amount <= st.max_supply.amount - st.supply.amount, "Quantity exceeds available supply");

		statstable.modify(st, 0, [&](auto& s) {
			s.supply += quantity;
		});

		add_balance(st.issuer, quantity, st.issuer);

		if (to != st.issuer) {
			SEND_INLINE_ACTION(*this, transfer, { st.issuer, N(active) }, { st.issuer, to, quantity, memo });
		}
	}

	void token::transfer(account_name from, account_name to, asset quantity, string memo)
	{
		eosio_assert(from != to, "Cannot transfer to self");
		require_auth(from);
		eosio_assert(is_account(to), "To account does not exist");
		auto sym = quantity.symbol.name();
		stats statstable(_self, sym);
		const auto& st = statstable.get(sym);

		require_recipient(from);
		require_recipient(to);

		eosio_assert(quantity.is_valid(), "Invalid quantity");
		eosio_assert(quantity.amount > 0, "Must transfer positive quantity");
		eosio_assert(quantity.symbol == st.supply.symbol, "Symbol precision mismatch");
		eosio_assert(memo.size() <= 250, "Memo has more than 256 bytes");

		sub_balance(from, quantity);
		add_balance(to, quantity, from);
	}

	void token::sub_balance(account_name owner, asset value)
	{
		accounts from_acnts(_self, owner);

		const auto& from = from_acnts.get(value.symbol.name(), "No balance object found");
		eosio_assert(from.balance.amount >= value.amount, "Overdrawn balance");

		if (from.balance.amount == value.amount) {
			from_acnts.erase(from);
		}
		else {
			from_acnts.modify(from, owner, [&](auto& a) {
				a.balance -= value;
			});
		}
	}

	void token::add_balance(account_name owner, asset value, account_name ram_payer)
	{
		accounts to_acnts(_self, owner);
		auto to = to_acnts.find(value.symbol.name());
		if (to == to_acnts.end()) {
			to_acnts.emplace(ram_payer, [&](auto& a) {
				a.balance = value;
			});
		}
		else {
			to_acnts.modify(to, 0, [&](auto& a) {
				a.balance += value;
			});
		}
	}

	void token::slotmachine(account_name payer, asset quantity)
	{

		uint64_t line[3];

		uint64_t cardshuffle[32];

		uint64_t cardpic[3][3];

		//card shuffle
		checksum256 result;

		auto mixedBlock = tapos_block_prefix() * tapos_block_num();

		const char *mixedChar = reinterpret_cast<const char *>(&mixedBlock);

		sha256((char *)mixedChar, sizeof(mixedChar), &result);

		const char *p64 = reinterpret_cast<const char *>(&result);

		for (int i = 0; i < 32; i++)
		{
			auto ra = (abs((int64_t)p64[i]) % (100)) + 1;

			if (ra <= 3)
			{
				cardshuffle[i] = 7;
			}
			else if (ra <= 13)
			{
				cardshuffle[i] = 4;
			}
			else if (ra <= 32)
			{
				cardshuffle[i] = 3;
			}
			else if (ra <= 60)
			{
				cardshuffle[i] = 2;
			}
			else if (ra <= 100)
			{
				cardshuffle[i] = 1;
			}
		}

		//Card pick
		checksum256 result2;
		uint64_t source = now();
		sha256((char *)&source, sizeof(source), &result2);
		uint64_t* p = reinterpret_cast<uint64_t*>(&result2.hash);
		uint64_t randNum = *p % 100;
		
		for (int j = 0; j < 3; j++) {

			auto ra = (abs((int64_t)p64[randNum]) % (32)) + 1;

			int pic = cardshuffle[ra];

			cardpic[0][j] = pic;

			print("  ", cardpic[0][j]);
			randNum++;
		}
		for (int j = 0; j < 3; j++) {

			auto ra = (abs((int64_t)p64[randNum]) % (32)) + 1;

			int pic = cardshuffle[ra];

			cardpic[1][j] = pic;

			print("  ", cardpic[1][j]);
			randNum++;
		}
		for (int j = 0; j < 3; j++) {

			auto ra = (abs((int64_t)p64[randNum]) % (32)) + 1;

			int pic = cardshuffle[ra];

			cardpic[2][j] = pic;

			print("  ", cardpic[2][j]);
			randNum++;
		}

		uint64_t lineValues[3];

		uint64_t winnings = 0;

		// Check line middle line

			for (int i = 0; i < 3; i++) {

				lineValues[i] = cardpic[1][i];

			}
			winnings += checkline(lineValues);
		
		// Check line top line

			for (int i = 0; i < 3; i++) {
				lineValues[i] = cardpic[0][i];
			}

			winnings += checkline(lineValues);
		
		// Check bottom line

			for (int i = 0; i < 3; i++) {

				lineValues[i] = cardpic[2][i];

			}

			winnings += checkline(lineValues);
		
		// Check left to right diagonal

			for (int i = 0; i < 3; i++) {

				lineValues[i] = cardpic[i][i];

			}

			winnings += checkline(lineValues);
		
		// Check right to left diagonal

			for (int i = 2; i >= 0; i--) {

				lineValues[i] = cardpic[i][i];

			}

			winnings += checkline(lineValues);
		
		if (winnings > 0) {

			print("You won ", winnings, " credits!");
			



		}

		else {

			print("Sorry, you did not win anything.");
			
		}



		print("You have ", winnings, " credits left.");

	}

	uint64_t token::checkline(uint64_t line[3])
	{
		if (line[0] == 7 && line[1] == 7 && line[2] == 7) { return 300; }

		if (line[0] == 4 && line[1] == 4 && line[2] == 4) { return 100; }

		if (line[0] == 3 && line[1] == 3 && line[2] == 3) { return 50; }

		if (line[0] == 2 && line[1] == 2 && line[2] == 2) { return 25; }

		if (line[0] == 1 && line[1] == 1 && line[2] == 1) { return 5; }

		return 0;

	}
	


}

EOSIO_ABI(eosio::token, (create)(issue)(transfer)(slotmachine))
