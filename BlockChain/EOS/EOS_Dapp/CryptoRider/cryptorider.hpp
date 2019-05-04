#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/crypto.h>
#include <array>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

    class cryptorider : public contract
    {
    public:
		cryptorider(account_name self):contract(self), globals(self, self){}

        //@abi action
        void createrider(const account_name user);
        void setjob(const account_name user, const uint32_t _job);
        void setappearance(
                           const account_name user,
                           const uint32_t _helmet,
                           const uint32_t _face,
                           const uint32_t _tire,
                           const uint32_t _carBody);
        void setparam(
                       const account_name user,
                       const uint32_t _speed,
                       const uint32_t _boost,
                       const uint32_t _hp);
        void setskill(
                      const account_name user,
                      const uint32_t _skill_1,
                      const uint32_t _skill_2,
                      const uint32_t _skill_3);
       void addExp(const account_name user); 
        struct AppearanceComponent
        {
            uint32_t _helmet;
            uint32_t _face;
            uint32_t _tire;
            uint32_t _carBody;

            std::string ToString() const
            {
                std::string str;
                str.reserve(50);
                str += "Helmet : ";
                str += std::to_string(_helmet);
                str += "Face : ";
                str += std::to_string(_face);
                str += "tire : ";
                str += std::to_string(_tire);
                str += "carBody : ";
                str += std::to_string(_carBody);
                return str;
            }
        };

        struct ParameterComponent
        {
            uint32_t _speed;
            uint32_t _boost;
            uint32_t _hp;

            std::string ToString() const
            {
                std::string str;
                str.reserve(50);
                str += "Speed : ";
                str += std::to_string(_speed);
                str += ", Boost : ";
                str += std::to_string(_boost);
                str += ", HP : ";
                str += std::to_string(_hp);
                return str;
            }
        };

        struct Skill
        {
            uint32_t _skillId;
        };

        struct SkillComponent
        {
            uint32_t _skill_1;
            uint32_t _skill_2;
            uint32_t _skill_3;
            uint32_t _skill_4;

            std::string ToString() const
            {
                std::string str;
                str.reserve(50);
                str += "Skill_1 : ";
                str += std::to_string(_skill_1);
                str += ", Skill_2 : ";
                str += std::to_string(_skill_2);
                str += ", Skill_3 : ";
                str += std::to_string(_skill_3);
                str += ", Skill_4 : ";
                str += std::to_string(_skill_4);
                return str;
            }
        };
        
    /*
        class hero
        {
            public:
                hero(
                        const uint32_t job,
                        const AppearanceComponent& appear,
                        const ParameterComponent& param,
                        const SkillComponent& skill)
                : _job(job)
                , _appear(appear)
                , _param(param)
                , _skill(skill)
                {
                }

                std::string ToString() const
                {
                    std::string str;
                    str.reserve(200);
                    str += "[HeroInfo - job : ";
                    str += std::to_string(_job);
                    str += " / ";
                    str += _appear.ToString();
                    str += " / ";
                    str += _param.ToString();
                    str += " / ";
                    str += _skill.ToString();
                    str += " ]";
                    return str;
                }

                // todo@cityofstars - change to private
            public:
                uint32_t _job;
                AppearanceComponent _appear;
                ParameterComponent _param;
                SkillComponent _skill;

                // todo@cityofstars - Serialize?
        };
    */
        //@abi table rider i64
        class rider
        {
        public:
            account_name to;
            uint32_t exp;
            uint32_t job;
            AppearanceComponent appear;
            ParameterComponent param;
            SkillComponent skills;
            uint64_t primary_key() const {return to;}

            std::string ToString() const
            {
                std::string str;
                str.reserve(200);
                str += "[RiderInfo - job : ";
                str += std::to_string(job);
                str += " / ";
                str += appear.ToString();
                str += " / ";
                str += param.ToString();
                str += " / ";
                str += skills.ToString();
                str += " ]";
                return str;
            }

            EOSLIB_SERIALIZE(rider,(to)(exp)(job)(appear)(param)(skills))
        };

        typedef multi_index<N(rider), rider> t_rider;

        // random impliment
    private:
        struct globalvariable
        {
            int randCount = 0;
            globalvariable() = default;

            uint64_t primary_key()const { return 0; }   // global
        };

        typedef eosio::multi_index<N(globals), globalvariable> global_index;
        global_index     globals;

        int provideNonce()
        {
            auto it = globals.find(0);
            if (it == globals.end())
            {
                it = globals.emplace(_self, [&](auto& e){
                    e.randCount = 0;
                });
            }
            int ret = it->randCount;

            globals.modify(it, 0, [&](auto& e){
                ++e.randCount;
            });
            return ret;
        }

        uint64_t rand()
        {
            uint64_t source = current_time() + provideNonce();
            checksum256 result;
            sha256( (char *)&source, sizeof(source), &result);
            uint64_t* p = reinterpret_cast<uint64_t*>(&result.hash);
            // print(source, ", ", *p);
            return *p;
        }

        // random number 0-to-v
        uint32_t rand32()
        {
            return rand()%32;
        }
    };
}
