#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

//declare struct for coordinates on war field.
struct grid {
	int row;
	int col;
};

//declare struct for command to move on war field.
struct move {
	char up = 'w';
	char down = 's';
	char left = 'a';
	char right = 'd';
};

//declare struct for save all parameters of character.
struct character {
	char ident_flag = 'P';
	std::string name;
	int health = 150;
	int armor = 50;
	int damage = 30;
	grid position = {0, 0};
};

//Function for save required parameters to save-file.
void save_game(std::ofstream& save_file, std::vector<character>& players, int& player_num) {
	save_file.write((char *)& player_num, sizeof(player_num));
	for (int i = 0; i <= player_num; i++) {
		save_file.write((char *)& (players[i].ident_flag), sizeof(players[i].ident_flag));
		int len = players[i].name.length();
		save_file.write((char *)& len, sizeof(len));
		save_file.write((char *) players[i].name.c_str(), len);
		save_file.write((char *)& players[i].health, sizeof(players[i].health));
		save_file.write((char *)& players[i].armor, sizeof(players[i].armor));
		save_file.write((char *)& players[i].damage, sizeof(players[i].damage));
		save_file.write((char *)& players[i].position.row, sizeof(players[i].position.row));
		save_file.write((char *)& players[i].position.col, sizeof(players[i].position.col));
	}
}

//Function for load required parameters from save-file to variables.
void load_game(std::ifstream& save_file, character& player, std::vector<character>& players, int& player_num) {
	save_file.read((char *)& player_num, sizeof(player_num));
	for (int i = 0; i < player_num; i++) {
		save_file.read((char *)& (player.ident_flag), sizeof(player.ident_flag));
		int len = 0;
		save_file.read((char *)& len, sizeof(len));
		player.name.resize(len);
		save_file.read((char *) player.name.c_str(), len);
		save_file.read((char *)& player.health, sizeof(player.health));
		save_file.read((char *)& player.armor, sizeof(player.armor));
		save_file.read((char *)& player.damage, sizeof(player.damage));
		save_file.read((char *)& player.position.row, sizeof(player.position.row));
		save_file.read((char *)& player.position.col, sizeof(player.position.col));

		players.push_back(player);
	}
}

//Function for display to console current state of war field.
void print_field(char position[20][20]) {
	std::cout << "   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19" <<std::endl;
	for (int i = 0; i < 20; i++) {
		if (i < 10)
			std::cout << i << "  ";
		else
			std::cout << i << " ";
		for (int j = 0; j < 20; j++) {
			std::cout << position[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}

int main() {
	//extended randomization.
	std::srand(std::time(nullptr));

	//declare local variables.
	//Giving allowing input for username.
	std::string user_name;

	//variable for action command.
	std::string action_command;
	//two-dimensional array for save player's position.
	char curr_pos[20][20];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			curr_pos[i][j] = '.';
		}
	}
	//variable for save current number of players.
	int player_num = 6;
	//struct for save parameters of current player.
	character player;
	//vector of structs for save all players
	std::vector<character> players;

	std::cout << "Start Game" << std::endl;
	std::cout << "-------------------------------------------------------------" << std::endl;
	//Selecting actions save or load.
	std::cout << "Input action (save/load):";
	std::cin >> action_command;
	while (action_command != "save" && action_command != "load") {
		std::cout << "ERROR input command. Try again." << std::endl;
		std::cout << "Input action (save/load):";
		std::cin >> action_command;
	}
	if (action_command == "save") {
		std::cout << "Input name of your person:" << std::endl;
		std::cin >> user_name;

		//Init the player's parameters and collect it to vector
		for (int i = 0; i < player_num - 1; i++) {
			player.ident_flag = 'E';
			player.name = "Enemy #" + std::to_string(i);
			player.health = (std::rand() % 51) + 100;
			player.armor = std::rand() % 51;
			player.damage = (std::rand() % 15) + 15;
			player.position.row = std::rand() % 20;
			player.position.col = std::rand() % 20;
			while (curr_pos[player.position.row][player.position.col] != '.') {
				player.position.row = std::rand() % 20;
				player.position.col = std::rand() % 20;
			}
			curr_pos[player.position.row][player.position.col] = 'E';
			players.push_back(player);
		}
		player.ident_flag = 'P';
		player.name = user_name;
		player.health = 150;
		player.armor = 50;
		player.damage = 30;
		player.position.row = std::rand() % 20;
		player.position.col = std::rand() % 20;
		while (curr_pos[player.position.row][player.position.col] != '.') {
			player.position.row = std::rand() % 20;
			player.position.col = std::rand() % 20;
		}
		curr_pos[player.position.row][player.position.col] = 'P';
		players.push_back(player);

		std::ofstream save_file("save.bin", std::ios::binary);
		save_game(save_file, players, player_num);
		save_file.close();
	} else {
		std::ifstream save_file("save.bin", std::ios::binary);
		load_game(save_file, player, players, player_num);
		save_file.close();
		for (int i = 0; i < player_num; i++) {
			if (i < player_num - 1)
				curr_pos[players[i].position.row][players[i].position.col] = 'E';
			else
				curr_pos[players[i].position.row][players[i].position.col] = 'P';
		}
	}

	std::cout << "-------------------------------------------------------------" << std::endl;
	print_field(curr_pos);

}
