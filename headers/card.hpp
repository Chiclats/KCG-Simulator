#ifndef card_hpp
#define card_hpp

#include<string>

struct card_info{

  std::string
    name,
    card_class,
    rarity,
    index;
  
};

struct card_info_artist: public card_info{

  std::string
    entering_condition,
    specific_ability,
    card_type; //RD BL YL WH BK
  std::vector<int> entering_effect(4); //1x4 vector, {alpha, beta, omega, vol}
  
  void print(){//print card info
    std::cout<<name<<std::endl;
    std::cout<<"ID:\t"<<index<<"\tRarity:\t"<<rarity<<std::endl;
    std::cout<<"Class:\t"<<card_class<<"\tType:\t"<<card_type<<std::endl;
    std::cout<<"Entering effect:"<<"\tAlpha+"<<entering_effect[0]
	     <<"\tBeta+"<<entering_effect[1]
	     <<"\tOmega+"<<entering_effect[2]
	     <<"\tVol+"<<entering_effect[3]<<std::endl;
    std::cout<<"Entering condition:\n\t"<<entering_condition<<endl;
    std::cout<<"Specific ability:\n\t"<<specific_ability<<endl;
  }
};

#endif //card_hpp
