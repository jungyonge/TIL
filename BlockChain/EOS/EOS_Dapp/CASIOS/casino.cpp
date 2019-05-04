/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include "casino.hpp"

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

        statstable.emplace(_self, [&](auto& s){
            s.supply.symbol = maximum_supply.symbol;
            s.max_supply    = maximum_supply;
            s.issuer        = issuer;
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

        statstable.modify(st, 0, [&](auto& s){
            s.supply += quantity;
        });

        add_balance(st.issuer, quantity, st.issuer);

        if(to != st.issuer){
            SEND_INLINE_ACTION(*this, transfer, {st.issuer, N(active)}, {st.issuer, to, quantity, memo});
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

        if(from.balance.amount == value.amount){
            from_acnts.erase(from);
        }
        else{
            from_acnts.modify(from, owner, [&](auto& a){
                a.balance -= value;
            });
        }
    }

    void token::add_balance(account_name owner, asset value, account_name ram_payer)
    {
        accounts to_acnts(_self, owner);
        auto to = to_acnts.find(value.symbol.name());
        if(to == to_acnts.end()){
            to_acnts.emplace( ram_payer, [&](auto& a){
                a.balance = value;
            });
        }
        else{
            to_acnts.modify(to, 0, [&](auto& a){
                a.balance += value;
            });
        }
    }

    void token::bet(account_name payer, asset quantity, uint64_t betType, uint64_t betNum)
    {
        accounts from_acnts(_self, payer);

        const auto& from = from_acnts.get(quantity.symbol.name(), "No balance object found");

        from_acnts.modify(from, 0, [&](auto& a){
            print("You has : ");
            print(a.balance);
        });

        checksum256 result;
        uint64_t source = tapos_block_num() * tapos_block_prefix();
        sha256((char *)&source, sizeof(source), &result);
        uint64_t* p = reinterpret_cast<uint64_t*>(&result.hash);
        uint64_t randNum = *p % 37;
        print(" >> RandNum : ");
        print(randNum);  

        if(betType == straight){
            if(betNum == randNum){
                print(" >> You get ");
                print(quantity * reward[straight]);
            }
            else{
                print(" >> You lost ");
                print(quantity);
            }
        }
        if(betType == split){
            bool flag = false;
            for(uint64_t i = 0; i < 2; i++){
                if(splitList[betNum][i] == randNum){
                    flag = true;
                    print(" >> You get ");
                    print(quantity * reward[split]);
                    break;
                }
            }
            if(!flag){
                print(" >> You lost ");
                print(quantity);
            }
        }
        if(betType == street){
            bool flag = false;
            for(uint64_t i = 0; i < 3; i++){
                if(streetList[betNum][i] == randNum){
                    flag = true;
                   print(" >> You get ");
                    print(quantity * reward[street]);
                    break;
                }
            }
            if(!flag){
                print(" >> You lost ");
                print(quantity);
            }
        }
        if(betType == square){
            bool flag = false;
            for(uint64_t i = 0; i < 4; i++){
                if(squareList[betNum][i] == randNum){
                    flag = true;
                    print(" >> You get ");
                    print(quantity * reward[square]);
                    break;
                }
            }
            if(!flag){
                print(" >> You lost ");
                print(quantity);
            }
        }
        if(betType == fivenum){
            if(randNum == 1 || randNum == 2 || randNum == 3 || randNum == 0){
                print(" >> You get ");
                print(quantity * reward[fivenum]);
            }
            else{
                print(" >> You lost ");
                print(quantity);
            }
        }
        if(betType == sixnum){
            bool flag = false;
            for(uint64_t i = 0; i < 6; i++){
                if(sixnumList[betNum][i] == randNum){
                    flag = true;
                    print(" >> You get ");
                    print(quantity * reward[sixnum]);
                    break;
                }
            }
            if(!flag){
                print(" >> You lost ");
                print(quantity);
            }
        }
        if(betType == column){
            bool flag = false;
            for(uint64_t i = 0; i < 12; i++){
                if(columnList[betNum][i] == randNum){
                    flag = true;
                   print(" >> You get ");
                    print(quantity * reward[column]);
                    break;
                }
            }
            if(!flag){
                print(" >> You lost ");
                print(quantity);
            }
        }
        if(betType == dozen){
            if(betNum == 0 && randNum >= 1 && randNum <= 12)
            {
                print(" >> You get ");
                print(quantity * reward[dozen]);
            }
            else if(betNum == 1 && randNum >= 13 && randNum <= 24)
            {
                print(" >> You get ");
                print(quantity * reward[dozen]);
            }
            else if(betNum == 2 && randNum >= 25 && randNum <= 36)
            {
                print(" >> You get ");
                print(quantity * reward[dozen]);
            }
            else{
                print(" >> You lost ");
                print(quantity);
            }
        }
        if(betType == hilo){
            if(betNum == 0 && randNum >= 1 && randNum <= 18)
            {
                print(" >> You get ");
                print(quantity * reward[hilo]);
            }
            else if(betNum == 1 && randNum >= 19 && randNum <= 36)
            {
                print(" >> You get ");
                print(quantity * reward[hilo]);
            }
            else{
                print(" >> You get ");
                print(quantity);
            }
        }
        if(betType == evenodd){
            if(betNum == 0 && randNum%2 == 0)
            {
                print(" >> You get ");
                print(quantity * reward[evenodd]);
            }
            else if(betNum == 1 && randNum%2 == 1)
            {
                print(" >> You get ");
                print(quantity * reward[evenodd]);
            }
            else{
                print(" >> You get ");
                print(quantity);
            }
        }
        if(betType == redblack){
            bool flag = false;
            if(betNum == 0){
                for(uint64_t i = 0 ; i < 18 ; i++ ){
                    if(redList[i] == randNum){
                        flag = true;
                        print(" >> You get ");
                        print(quantity * reward[redblack]);
                        break;
                    }
                }
                if(!flag){
                    print(" >> You lost ");
                    print(quantity);
                }
            }
            if(betNum == 1){
                for(uint64_t i = 0 ; i < 18 ; i++ ){
                    if(redList[i] == randNum){
                        flag = true;
                        print(" >> You lost ");
                        print(quantity);
                        break;
                    }
                }
                if(!flag){
                    print(" >> You get ");
                    print(quantity * reward[redblack]);
                }
            }
        }
    }

    void token::check(uint64_t betType, uint64_t betNum){
        if(betType == split){   // ok
            for(uint64_t i = 0; i < 2 ; i++)
            {
                 print(splitList[betNum][i]);
                 print(" ");
            }           
        }
        if(betType == street){
            for(uint64_t i = 0; i < 3 ; i++)
            {
                 print(streetList[betNum][i]);
                 print(" ");
            }     
        }
        if(betType == square){   // ok
            for(uint64_t i = 0; i < 4 ; i++)
            {
                 print(squareList[betNum][i]);
                 print(" ");
            }     
        }
        if(betType == sixnum){
            for(uint64_t i = 0; i < 6 ; i++)
            {
                 print(sixnumList[betNum][i]);
                 print(" ");
            }     
        }
        if(betType == column){
            for(uint64_t i = 0; i < 12 ; i++)
            {
                 print(columnList[betNum][i]);
                 print(" ");
            }     
        }
        if(betType == redblack){   // ok
            for(uint64_t i = 0; i < 18 ; i++)
            {
                 print(redList[i]);
                 print(" ");
            }     
        }
    }
}

EOSIO_ABI( eosio::token, (create)(issue)(transfer)(bet)(check) )