#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

struct grid {
	int row;
	int col;
};

struct character {
	char ident_flag = 'P';
	std::string name;
	int health = 150;
	int armor = 50;
	int damage = 30;
	grid position;
};

void save_game(std::ofstream& save_file, character players[]) {
	for (int i = 0; i < 6; i++) {
		save_file.write((char *) &(players[i].ident_flag), sizeof(players[i].ident_flag));
		save_file.write((char *) &(players[i].name), players[i].name.size());
		save_file.write((char *) &(players[i].health), sizeof(players[i].health));
		save_file.write((char *) &(players[i].armor), sizeof(players[i].armor));
		save_file.write((char *) &(players[i].damage), sizeof(players[i].damage));
		save_file.write((char *) &(players[i].position), sizeof(players[i].position));
	}
}

void load_game(std::ifstream& save_file, character players[]) {
	for (int i = 0; i < 6; i++) {
		save_file.read((char *) &(players[i].ident_flag), sizeof(players[i].ident_flag));
		save_file.read((char *) &(players[i].name), players[i].name.size());
		save_file.read((char *) &(players[i].health), sizeof(players[i].health));
		save_file.read((char *) &(players[i].armor), sizeof(players[i].armor));
		save_file.read((char *) &(players[i].damage), sizeof(players[i].damage));
		save_file.read((char *) &(players[i].position), sizeof(players[i].position));
	}
}

int main() {
	std::srand(std::time(nullptr));
	
}
