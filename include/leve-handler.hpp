#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>


/**
On peut avoir des caractères parmi les suivants pour représenter les briques:
- '-' : brique rectangulaire
- 'o' : brique circulaire
- 'x' : brique triangulaire
- ' ' : espace
- 'p' : brique pyramidale
Format d'un fichier à parser
hauteur largeur





*/




class Level_Handler{
	public:
		Level_Handler(std::string file_name );
		~Level_Handler();
		void add_level(std::string level_name);
		void remove_level(std::string level_name);
		void load_level(std::string level_name);
		void save_level(std::string level_name);
		void print_levels();
	private:
		int n_bri
};