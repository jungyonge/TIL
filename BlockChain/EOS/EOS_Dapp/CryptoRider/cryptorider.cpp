#include "cryptorider.hpp"

namespace eosio
{
    void cryptorider::createrider(const account_name user)
    {
        print("Start createrider..... ID : ", name{user});

		cryptorider::AppearanceComponent appear = {rand32(), rand32(), rand32(), rand32()};
		cryptorider::ParameterComponent param = {rand32(), rand32(), rand32()};
		cryptorider::SkillComponent skills = {rand32(), rand32(), rand32(), rand32()};
        
		cryptorider::t_rider riders(_self,_self);

        auto iter = riders.find(user);
        if(iter == riders.end())
        {
            riders.emplace(_self,[&](auto& newRider)
            {
				newRider.to = user;
				newRider.exp = 0;
				newRider.job = rand32();
				newRider.appear = appear;
				newRider.param = param;
				newRider.skills = skills;
                
                print("\n\nComplete createrider... \n", newRider.ToString().c_str(), "\n\n");
            });
        }
        else
        {
            uint64_t getuser;
            getuser = iter->to;
            print("\n\nData already exist : ", name{getuser}, "\n\n");
        }
    }

    void cryptorider::addExp(const account_name user)
    {
        uint64_t getExp = rand()%1000;

		cryptorider::t_rider riders(_self,_self);
        auto iter = riders.find(user);
        if(iter != riders.end())
        {
			riders.modify(iter, _self, [&](auto& setRider)
            {
                if(setRider.exp == 999999)
                {
                    print("\n\nInvalid Request, Already Max Exp!!!\n\n");
                }
                else if(setRider.exp + getExp == 999999)
                {
					setRider.exp = 999999;
                }
                else
                {
					setRider.exp = getExp;
                }
                print("\n\nRiderExp..... ", setRider.exp, "\n\n");
            });
        }
    }

    void cryptorider::setjob(const account_name user, const uint32_t _job)
    {
        if(_job < 32)
        {
			cryptorider::t_rider riders(_self,_self);
            auto iter = riders.find(user);
            if(iter != riders.end())
            {
				riders.modify(iter, _self, [&](auto& setRider)
                {
					setRider.job = _job;

                    print("\n\nSetJob... ", setRider.job, "\n\n");
                });
            }
        }
        else
        {
            // todo@jeongseolmin - need asset revert
            print("\n\nInvalid Request\n\n");
        }
    }
    
    void cryptorider::setappearance(
                        const account_name user,
                        const uint32_t _helmet,
                        const uint32_t _face,
                        const uint32_t _tire,
                        const uint32_t _carBody)
    {
        // todo@cityofstar - find user Rider instance and set

        if(_helmet < 32 && _face < 32 && _tire < 32 && _carBody < 32)
        {
			cryptorider::t_rider riders(_self,_self);
            auto iter = riders.find(user);
            if(iter != riders.end())
            {
				cryptorider::AppearanceComponent appear = {_helmet, _face, _tire, _carBody};
                riders.modify(iter, _self, [&](auto& setRider)
                {
					setRider.appear = appear;
                    
                    print("\n\nSetAppearance... ", setRider.appear.ToString().c_str(), "\n\n");
                });
            }

        }
        else
        {
            // todo@jeongseolmin - need asset revert
            print("\n\nInvalid Request\n\n");
        }
    }
    
    void cryptorider::setparam(
                              const account_name user,
                              const uint32_t _speed,
                              const uint32_t _boost,
                              const uint32_t _hp)
    {
        if(_speed < 32 && _boost < 32 && _hp < 32)
        {
			cryptorider::t_rider riders(_self,_self);
            auto iter = riders.find(user);
            if(iter != riders.end())
            {
				cryptorider::ParameterComponent param = {_speed, _boost, _hp};
                riders.modify(iter, _self, [&](auto& setRider)
                {
					setRider.param = param;
                    
                    print("\n\nSetParam... ", setRider.param.ToString().c_str(), "\n\n");
                });
            }

        }
        else
        {
            // todo@jeongseolmin - need asset revert
            print("\n\nInvalid Request\n\n");
        }
    }
    
    void cryptorider::setskill(
                              const account_name user,
                              const uint32_t _skill_1,
                              const uint32_t _skill_2,
                              const uint32_t _skill_3)
    {
        if(_skill_1 < 32 && _skill_2 < 32 && _skill_3 < 32)
        {
			cryptorider::t_rider riders(_self,_self);
            auto iter = riders.find(user);
            if(iter != riders.end())
            {
				cryptorider::SkillComponent skills = {_skill_1, _skill_2, _skill_3};
				riders.modify(iter, _self, [&](auto& setRider)
                {
					setRider.skills = skills;
                    
                    print("\n\nSetSkills... ", setRider.skills.ToString().c_str(), "\n\n");
                });
            }

        }
        else
        {
            // todo@jeongseolmin - need asset revert
            print("\n\nInvalid Request\n\n");
        }
    }
    
EOSIO_ABI( cryptorider::cryptorider, (createrider)(setjob)(setappearance)(setparam)(setskill) )
}
