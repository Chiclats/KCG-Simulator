#ifndef card_hpp
#define card_hpp

#include"./std_headers.hpp"

namespace card{

  //--------------- static card info

  struct card_info
  {// Static information of a card.

    //general
    std::string name;
    std::string card_class; // {"Artist", "Song", "Magic", "Direction"}
    inline static const std::set<std::string> card_class__valid{"Artist", "Song", "Magic", "Direction"};
    std::string rarity;
    std::pair<std::string,unsigned int> index;

    //Artist
    bool artist_entering_condition_p; // whether artist entering condition exists or not
    std::string artist_entering_condition;
    std::string artist_specific_ability;
    std::string artist_card_type; // {"RD", "BL", "YL", "WH", "BK"}
    std::vector<unsigned int> artist_entering_effect{0,0,0,0}; // 1x4 vector, {alpha, beta, omega, vol}

    inline static const std::set<std::string> artist_song_card_type__valid{"RD", "BL", "YL", "WH", "BK"}; // for both Artist and Song
    
    //Song
    std::string song_effect;
    bool song_center_effect_p; // whether song center effect exists or not
    std::string song_center_effect;
    std::vector<std::string> song_card_type; // a vector of all types possessed by the song card, {"RD", "BL", "YL", "WH", "BK"}

    //Magic
    std::string magic_card_type; // {"Instant", "Equipment"}
    inline static const std::set<std::string> magic_card_type__valid{"Instant", "Equipment"};
    std::string magic_effect;

    //Direction
    std::string direction_card_type; // {"Set"}
    inline static const std::set<std::string> direction_card_type__valid{"Set"};
    std::string direction_effect;
  };

  void print(const card_info& card_info_)
  {// Print out card info
    if(card_info_.card_class=="Artist"){
      std::cout<<card_info_.name<<std::endl;
      std::cout<<card_info_.card_class<<"\t"<<card_info_.index.first<<"-"<<card_info_.index.second<<"\t"<<card_info_.rarity<<std::endl;
      std::cout<<"[TYPE] "<<card_info_.artist_card_type<<std::endl;
      std::cout<<"Alpha +"<<card_info_.artist_entering_effect[0]<<"\tBeta  +"<<card_info_.artist_entering_effect[1]
	       <<"\tOmega +"<<card_info_.artist_entering_effect[2]<<"\tVol   +"<<card_info_.artist_entering_effect[3]<<std::endl;
      if(card_info_.artist_entering_condition_p)
	std::cout<<"[ENTERING CONDITION] "<<card_info_.artist_entering_condition<<std::endl;
      std::cout<<"[SPECIFIC ABILITY] "<<card_info_.artist_specific_ability<<std::endl;
    }
    else if(card_info_.card_class=="Song"){
      std::cout<<card_info_.name<<std::endl;
      std::cout<<card_info_.card_class<<"\t"<<card_info_.index.first<<"-"<<card_info_.index.second<<"\t"<<card_info_.rarity<<std::endl;
      std::cout<<"[TYPES] ";
      for(size_t i=0; i<card_info_.song_card_type.size(); ++i){
	std::cout<<card_info_.song_card_type[i];
	if(i != card_info_.song_card_type.size()-1) std::cout<<", ";
      }
      std::cout<<std::endl;
      std::cout<<"[SONG EFFECT] "<<card_info_.song_effect<<std::endl;
      if(card_info_.song_center_effect_p)
        std::cout<<"[CENTER EFFECT] "<<card_info_.song_center_effect<<std::endl;
    }
    else if(card_info_.card_class=="Magic"){
      std::cout<<card_info_.name<<std::endl;
      std::cout<<card_info_.card_class<<"\t"<<card_info_.index.first<<"-"<<card_info_.index.second<<"\t"<<card_info_.rarity<<std::endl;
      std::cout<<"[TYPE] "<<card_info_.magic_card_type<<std::endl;
      std::cout<<"[MAGIC EFFECT] "<<card_info_.magic_effect<<std::endl;
    }
    else if(card_info_.card_class=="Direction"){
      std::cout<<card_info_.name<<std::endl;
      std::cout<<card_info_.card_class<<"\t"<<card_info_.index.first<<"-"<<card_info_.index.second<<"\t"<<card_info_.rarity<<std::endl;
      std::cout<<"[TYPE] "<<card_info_.direction_card_type<<std::endl;
      std::cout<<"[DIRECTION EFFECT] "<<card_info_.direction_effect<<std::endl;
    }
    else throw(std::runtime_error("[card::print] Illegal card_class: "+card_info_.card_class));
  }

  bool card_legal_p(const card_info& card_info_)
  {// Check if the card info is legal
    bool result=true;

    if(card_info_.name.empty()){
      result=false;
      std::cout<<"[card::card_legal_p] Illegal card info: empty card name."<<std::endl;
    }
    if(not card_info::card_class__valid.count(card_info_.card_class)){
      result=false;
      std::cout<<"[card::card_legal_p] Illegal card info: illegal card class '"<<card_info_.card_class<<"'."<<std::endl;
    }

    if(card_info_.card_class=="Artist"){
      if(not card_info::artist_song_card_type__valid.count(card_info_.artist_card_type)){
	result=false;
	std::cout<<"[card::card_legal_p] Illegal Artist card type: '"<<card_info_.artist_card_type<<"'."<<std::endl;
      }
      if(card_info_.artist_entering_effect.size() !=4){
	result=false;
	std::cout<<"[card::card_legal_p] Invalid Artist entering effect vector size."<<std::endl;
      }
      if(card_info_.artist_entering_condition_p && card_info_.artist_entering_condition.empty()){
	result=false;
	std::cout<<"[card::card_legal_p] Artist entering condition marked but empty."<<std::endl;
      }
      if(card_info_.artist_specific_ability.empty()){
	result=false;
	std::cout<<"[card::card_legal_p] Artist specific ability is empty."<<std::endl;
      }
    }
    
    else if(card_info_.card_class=="Song"){
      if(card_info_.song_effect.empty()){
	result=false;
	std::cout<<"[card::card_legal_p] Song effect is empty."<<std::endl;
      }
      if(card_info_.song_center_effect_p && card_info_.song_center_effect.empty()){
	result=false;
	std::cout<<"[card::card_legal_p] Song center effect marked but empty."<<std::endl;
      }
      if(card_info_.song_card_type.empty()){
	result=false;
	std::cout<<"[card::card_legal_p] Song card types vector is empty."<<std::endl;
      }
      for(const std::string& p : card_info_.song_card_type)
	if(not card_info::artist_song_card_type__valid.count(p)){
	  result=false;
	  std::cout<<"[card::card_legal_p] Illegal Song card type: '"<<p<<"'."<<std::endl;
	}
    }
    
    else if(card_info_.card_class=="Magic"){
      if(not card_info::magic_card_type__valid.count(card_info_.magic_card_type)){
	result=false;
	std::cout<<"[card::card_legal_p] Invalid Magic card type: '"<<card_info_.magic_card_type<<"'."<<std::endl;
      }
      if(card_info_.magic_effect.empty()){
	result=false;
	std::cout<<"[card::card_legal_p] Magic effect is empty."<<std::endl;
      }
    }

    else if(card_info_.card_class=="Direction"){
      if(not card_info::direction_card_type__valid.count(card_info_.direction_card_type)){
	result=false;
	std::cout<<"[card::card_legal_p] Invalid Direction card type: '"<<card_info_.direction_card_type<<"'."<<std::endl;
      }
      if(card_info_.direction_effect.empty()){
	result=false;
	std::cout<<"[card::card_legal_p] Direction effect is empty."<<std::endl;
      }
    }
    
    return result;
  }

  using card_index=std::pair<std::string,unsigned int>;
  
  card_index extract_index_from_filename(const std::string& filename)
  {// Extract index from filename, e.g. "./path/to/AA-1.txt" or "./path/to/AA-1.py". '-' and '.' are necessary.
    // 1. Find the basename (part after the last path separator)
    size_t last_separator = filename.find_last_of("/\\"); // Handle both '/' (Unix) and '\' (Windows)
    std::string basename = (last_separator == std::string::npos) ? filename : filename.substr(last_separator + 1);

    // 2. Validate and extract extension
    size_t dot_pos = basename.find('.');
    if (dot_pos == std::string::npos or dot_pos == 0) 
      throw std::invalid_argument("[card::extract_index_from_filename] Invalid filename: missing '.'");

    // 3. Extract index string (e.g., "AA-1" from "AA-1.txt")
    std::string index_str = basename.substr(0, dot_pos);
    if (index_str.empty()) 
      throw std::invalid_argument("[card::extract_index_from_filename] Invalid filename: empty index part");

    // 4. Split index into first and second parts
    size_t hyphen_pos = index_str.find('-');
    if (hyphen_pos == std::string::npos or hyphen_pos == 0 or hyphen_pos == index_str.size() - 1) 
      throw std::invalid_argument("[card::extract_index_from_filename] Invalid index format: missing or misplaced '-'");

    std::string index_first = index_str.substr(0, hyphen_pos); // e.g., "AA"
    std::string index_second_str = index_str.substr(hyphen_pos + 1); // e.g., "1"

    // 5. Convert second part to unsigned int
    unsigned int index_second;
    try {
      size_t pos;
      index_second = std::stoi(index_second_str, &pos);
      if (pos != index_second_str.size()) 
	throw std::invalid_argument("[card::extract_index_from_filename] Trailing characters after number");
      if (index_second == 0) 
	throw std::invalid_argument("[card::extract_index_from_filename] Index second part cannot be zero");
    } catch (const std::invalid_argument&) {
      throw std::invalid_argument("[card::extract_index_from_filename] Invalid index second part: not an integer");
    } catch (const std::out_of_range&) {
      throw std::invalid_argument("[card::extract_index_from_filename] Invalid index second part: integer out of range");
    }

    return {index_first, index_second};
  }

  card_info load_card_info_from_txt(std::string txt_name)
  {// Load card info from a txt, txt_name = "AA-1.txt",...

    // 1. Extract index from filename
    auto [index_first,index_second]=extract_index_from_filename(txt_name);

    // 2. Determine card_class from last letter of index_first
    if (index_first.empty()) {
      throw std::invalid_argument("Empty index first part");
    }
    char last_char = index_first.back();
    std::string card_class;
    switch (last_char) {
      case 'A': card_class = "Artist"; break;
      case 'S': card_class = "Song"; break;
      case 'M': card_class = "Magic"; break;
      case 'D': card_class = "Direction"; break;
      default: throw std::invalid_argument("[card::load_card_info_from_txt] Invalid card class indicator: " + std::string(1, last_char));
    }

    // 3. Open and read the file
    std::ifstream file(txt_name);
    if (not file.is_open())
      throw std::runtime_error("[card::load_card_info_from_txt] Cannot open file: " + txt_name);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) 
      lines.push_back(line);
    file.close();

    // 4. Parse content and populate card_info
    card_info card;
    card.index = {index_first, index_second};
    card.card_class = card_class;

    if (card_class == "Artist") {
      if (lines.size() != 6)
	throw std::runtime_error("[card::load_card_info_from_txt] Expected 6 lines for Artist card, got " + std::to_string(lines.size()));
      
      card.name = lines[0]; // e.g., "Kafu [huakui niao]"
      card.rarity = lines[1]; // e.g., "R"
      card.artist_card_type = lines[2]; // e.g., "RD"
      // Validate artist_card_type
      if (not card_info::artist_song_card_type__valid.count(card.artist_card_type))
	throw std::invalid_argument("[card::load_card_info_from_txt] Invalid artist card type: " + card.artist_card_type);
	
      // Parse artist_entering_effect (4 integers)
      std::istringstream iss(lines[3]); // e.g., "0 0 0 1"
      card.artist_entering_effect.resize(4);
      for (int i = 0; i < 4; ++i) 
	if (not (iss >> card.artist_entering_effect[i])) 
	  throw std::runtime_error("[card::load_card_info_from_txt] Failed to parse artist entering effect");
      
      // Parse entering condition
      if (lines[4].empty())
	throw std::runtime_error("[card::load_card_info_from_txt] No entry of artist entering condition");
      else if (lines[4]=="-"){
	card.artist_entering_condition_p=false;
	card.artist_entering_condition="";
      }
      else{
	card.artist_entering_condition_p=true;
	card.artist_entering_condition=lines[4];
      }
      
      // Parse specific ability
      if (lines[5].empty())
	throw std::runtime_error("[card::load_card_info_from_txt] No entry of artist specific ability");
      else
	card.artist_specific_ability=lines[5];
    }
    
    else if (card_class == "Song") {
      if (lines.size() != 5) 
	throw std::runtime_error("Expected 5 lines for Song card, got " + std::to_string(lines.size()));
	
      card.name = lines[0]; // e.g., "Denno"
      card.rarity = lines[1]; // e.g., "N"
      
      // Parse song_card_type (multiple types)
      std::istringstream iss(lines[2]); // e.g., "RD BL YL WH BK"
      std::string type;
      while (iss >> type) {
	if (not card_info::artist_song_card_type__valid.count(type))
	  throw std::invalid_argument("[card::load_card_info_from_txt] Invalid song card type: " + type);
	card.song_card_type.push_back(type);
      }
      
      // Parse song effect
      if (lines[3].empty())
	throw std::runtime_error("[card::load_card_info_from_txt] No entry of song effect");
      card.song_effect=lines[3];
      
      // Parse song center effect
      if (lines[4].empty())
	throw std::runtime_error("[card::load_card_info_from_txt] No entry of song center effect");
      if (lines[4]=="-"){
	card.song_center_effect_p=false;
	card.song_center_effect="";
      }
      else{
	card.song_center_effect_p=true;
	card.song_center_effect = lines[4];
      }
    }
    
    else if (card_class == "Magic") {
      if (lines.size() != 4)
	throw std::runtime_error("[card::load_card_info_from_txt] Expected 4 lines for Magic card, got " + std::to_string(lines.size()));
	
      card.name = lines[0]; // e.g., "\"Dimension\" Qiaoqu"
      card.rarity = lines[1]; // e.g., "N"
      
      card.magic_card_type = lines[2]; // e.g., "Instant"
      // Validate magic_card_type
      if (not card_info::magic_card_type__valid.count(card.magic_card_type)) 
	throw std::invalid_argument("[card::load_card_info_from_txt] Invalid magic card type: " + card.magic_card_type);
      
      // Parse magic effect
      if (lines[3].empty())
	throw std::runtime_error("[card::load_card_info_from_txt] Empty magic effect");
      card.magic_effect = lines[3]; // e.g., "abc abc..."
    }
    
    else if (card_class == "Direction") {
      if (lines.size() != 4) 
	throw std::runtime_error("[card::load_card_info_from_txt] Expected 4 lines for Direction card, got " + std::to_string(lines.size()));
        
      card.name = lines[0]; // e.g., "\"Toy\" Creator"
      card.rarity = lines[1]; // e.g., "N"
      
      card.direction_card_type = lines[2]; // e.g., "Set"
      // Validate direction_card_type
      if (not card_info::direction_card_type__valid.count(card.direction_card_type)) 
	throw std::invalid_argument("[card::load_card_info_from_txt] Invalid direction card type: " + card.direction_card_type);
      
      // Parse direction effect
      if (lines[3].empty()) {
	throw std::runtime_error("[card::load_card_info_from_txt] Empty for direction effect");
      }
      card.direction_effect = lines[3]; // e.g., "abc abc..."
    }

    return card;
}

  //--------------- card deck

  using deck=std::vector<card_index>;

  
}

#endif//card_hpp
