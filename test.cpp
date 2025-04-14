#include"./headers/card.hpp"

int main(){

  card::card_info card_artist=card::load_card_info_from_txt("./card_data/AM-1.txt");
  card::print(card_artist);

}
