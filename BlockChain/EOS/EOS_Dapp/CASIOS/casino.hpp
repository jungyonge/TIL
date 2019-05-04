/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/crypto.h>

#include <string>

namespace ecosystem {
    class system_contract;
}

namespace eosio {
    
    using std::string;

    class token : public contract {
        public:
        // Bet type define
        enum { straight = 0, split = 1, street = 2, square = 3, fivenum = 4, sixnum = 5, column = 6, dozen = 7, hilo = 8, evenodd = 9 , redblack = 10};
        uint64_t reward[11];
        uint64_t splitList[57][2];
        uint64_t streetList[12][3];
        uint64_t squareList[22][4];
        uint64_t sixnumList[11][6];
        uint64_t columnList[3][12];
        uint64_t redList[18];
        uint64_t temp;
        // init bet table
        token(account_name self):contract(self){
            // Init reward by betType
            reward[straight] = 35;
            reward[split] = 17;
            reward[street] = 11;
            reward[square] = 8;
            reward[fivenum] = 6;
            reward[sixnum] = 5;
            reward[column] = 2;
            reward[dozen] = 2;
            reward[hilo] = 1;
            reward[evenodd] = 1;
            reward[redblack] = 1;

            // Init splitList
            temp = 1;
            for(uint64_t i=0; i<24 ; i++){
                if(i != 0 && i%2 == 0) temp++;
                for(uint64_t j=0 ; j<2 ; j++){
                    splitList[i][j] = i + j + temp;
                }
            }
            temp = 1;
            for(uint64_t i=24; i<57 ; i++){
                if(i == 35) temp = 2;
                if(i == 46) temp = 3;
                for(uint64_t j=0; j<2; j++){
                    splitList[i][j] = temp + (j * 3);
                }
                temp += 3;
            }

            // Init streetList
            for(uint64_t i=0; i<12; i++){
                for(uint64_t j=0; j<3 ; j++){
                    streetList[i][j] = (i * 3) + j + 1;
                }
            }

            // Init squareList
            temp = 1;
            for(uint64_t i=0; i<22; i++){
                if(i%2 == 0 && i != 0) temp++;
                for(uint64_t j=0; j<4 ; j++){
                    if(j == 2) temp++;
                    squareList[i][j] = temp + j;
                }
            }

            // Init sixnumList
            for(uint64_t i=0; i<11; i++){
                for(uint64_t j=0; j<6 ; j++){
                    sixnumList[i][j] = (i * 3) + j + 1;
                }
            }   

            // Init columnList
            temp =1;
            for(uint64_t i=0; i<3; i++){
                for(uint64_t j=0; j<12 ; j++){
                    columnList[i][j] = temp + (j * 3);
                }
                temp++;
            }  

            // Init redList
            temp = 0;
            for(uint64_t i=1 ; i<37; i++){
                if(i < 10 && i%2 == 1)
                {
                    redList[temp] = i;
                    temp++;
                }
                if(i > 11 && i < 19 && i%2 == 0)
                {
                    redList[temp] = i;
                    temp++;
                }
                if(i >= 19 && i < 29 && i%2 == 1)
                {
                    redList[temp] = i;
                    temp++;
                }
                if(i > 29 && i%2 == 0)
                {
                    redList[temp] = i;
                    temp++;
                }
            }

            //tables[36].numbers = new uint64_t[18];            
        }

        //@abi action
        void create(account_name issuer, asset maximum_supply);
        //@abi action    
        void issue(account_name to, asset quantity, string memo);
        //@abi action
        void transfer(account_name from, account_name to, asset quantity, string memo);
        //@abi action 
        void bet(account_name payer, asset quantity, uint64_t betType, uint64_t betNum);
        //@abi action 
        void check(uint64_t betType, uint64_t betNum);

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

            void sub_balance( account_name owner, asset value );
            void add_balance( account_name owner, asset value, account_name ram_payer );

        public:
            struct transfer_args {
                account_name from;
                account_name to;
                asset        quantity;
                string       memo;
            };
    };

    asset token::get_supply( symbol_name sym )const
    {
        stats statstable( _self, sym );
        const auto& st = statstable.get(sym);
        return st.supply;
    }

    asset token::get_balance( account_name owner, symbol_name sym )const
    {
        accounts accountstable( _self, owner );
        const auto& ac = accountstable.get(sym);
        return ac.balance;
    }
}