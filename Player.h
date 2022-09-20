#pragma once
#include <string>
class Player
{
private:
	std::string name;
	char symbol;
public:
	Player() = default;
	~Player() = default;
	std::string get_name() const { return name; }
	char get_symbol() const{ return symbol; }
	void set_name(std::string new_name) { name = new_name; }
	void set_symbol(char new_symbol) { symbol = new_symbol; }
	bool is_starting();		// Metoda losuj¹ca czy gracz zaczyna (prawda - tak, fa³sz - nie)
};

