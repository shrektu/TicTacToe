#include "Player.h"
#include <ctime>
#include <cstdlib>


bool Player::is_starting()
{
	srand(time(NULL));		// Inicjalizacja maszyny losuj¹cej
	bool randomised_number = std::rand() % 2;			// zwraca resztê z dzielenia przez 2 (0 albo 1)
	if (randomised_number)	
		return true;				// Je¿eli wylosowana zostanie 1 - zwróæ prawdê, gracz zaczyna
	return false;					// W przeciwnym wypadku fa³sz - drugi gracz zaczyna
}
