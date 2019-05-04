/**
*  @file
*  @copyright defined in eos/LICENSE.txt
*/
#pragma once
#include <eosiolib/eosio.hpp>

#include <eosiolib/transaction.hpp>
#include <eosiolib/action.hpp>

#include <utility>
#include <vector>
#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/print.hpp>


using eosio::key256;
using eosio::indexed_by;
using eosio::const_mem_fun;
using eosio::asset;
using eosio::permission_level;
using eosio::action;
using eosio::print;
using eosio::name;

namespace eosiosystem {
	class system_contract;
}

namespace eosio {

	using std::string;

	class token : public contract {
	public:



		token(account_name self) :contract(self) {}
		//@abi action
		void create(account_name issuer,
			asset        maximum_supply);
		//@abi action
		void issue(account_name to, asset quantity, string memo);
		//@abi action
		void transfer(account_name from,
			account_name to,
			asset        quantity,
			string       memo);
		//@abi action
		void slotmachine(account_name payer, asset quantity);

		uint64_t checkline(uint64_t line[3]);
	

		inline asset get_supply(symbol_name sym)const;

		inline asset get_balance(account_name owner, symbol_name sym)const;

	private:
		//@abi table accounts i64
		struct account {
			asset balance;

			uint64_t primary_key()const { return balance.symbol.name(); }

			EOSLIB_SERIALIZE(account, (balance))
		};
		//@abi table stat i64
		struct currencies {
			asset        supply;
			asset        max_supply;
			account_name issuer;

			uint64_t primary_key()const { return supply.symbol.name(); }

			EOSLIB_SERIALIZE(currencies, (supply)(max_supply)(issuer))
		};

		typedef eosio::multi_index<N(accounts), account> accounts;
		typedef eosio::multi_index<N(stat), currencies> stats;

		void sub_balance(account_name owner, asset value);
		void add_balance(account_name owner, asset value, account_name ram_payer);

	public:
		struct transfer_args {
			account_name from;
			account_name to;
			asset        quantity;
			string       memo;
		};
	};

	asset token::get_supply(symbol_name sym)const
	{
		stats statstable(_self, sym);
		const auto& st = statstable.get(sym);
		return st.supply;
	}

	asset token::get_balance(account_name owner, symbol_name sym)const
	{
		accounts accountstable(_self, owner);
		const auto& ac = accountstable.get(sym);
		return ac.balance;
	}
}