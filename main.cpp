#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include "Player.h"

// Prototypy funkcji

void display_header();          // Wyœwietlenie wstêpu do gry
void display_menu();            // Wyœwietlenie g³ównego menu
void handle_singleplayer();     // obs³uga gry singleplayer (przeciwko komputerowi)
void handle_multiplayer();      // obs³uga gry multiplayer (2 graczy)
void display_board(std::vector<std::vector<char>> &board);      // Wyœwietlenie aktualnego stanu planszy
void start_game_multi(Player &player1, Player &player2, std::vector<std::vector<char>> &board);          // Implementacja ca³ej rozgrywki multi-player
bool is_winner(const std::vector<std::vector<char>> &board);             // Funkcja sprawdzaj¹ca czy któryœ z graczy wygra³ (natychmiastowo koñczy grê)
bool is_board_full(const std::vector<std::vector<char>>& board);        // Funkcja sprawdzaj¹ca czy ca³a plansza zosta³a w ca³oœci zajêta (koniec gry)
bool is_place_valid(char place, const std::vector<std::vector<char>> &board);       // Funkcja weryfikuj¹ca czy dane pole jest na planszy i czy nie zosta³o wczeœniej zajête
void enter_to_board(char &place, std::vector<std::vector<char>> &board, Player &player);       // Funkcja umieszczaj¹ca znak w podanym polu
void start_game_single(Player &player, Player &computer, std::vector<std::vector<char>>& board);                 // Implementacja ca³ej rozgrywki single-player
char computer_selection();        // Funkcja zwracaj¹ca pole, w które komputer wstawi znak                                                  


int main()
{
    display_header();

    char choice{};

    do
    {
        display_menu();
        std::cout << "\nPlease enter your choice: ";
        std::cin >> choice;
        choice = ::toupper(choice);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // wyczyszczenie bufora z std::cin

        switch (choice)
        {
        case 'S':
            handle_singleplayer();
            break;

        case 'M':
            handle_multiplayer();
            break;

        case 'Q':
            break;

        default:
            std::cout << "Invalid choice, please enter a right choice from menu.\n" << std::endl;
            display_menu();
        }
    } while (choice != 'Q');

    std::cout << "Thanks for playing the game." << std::endl;

    return 0;
}

// Implementacje funkcji

void display_header()
{
    std::cout << std::setw(80) << std::setfill('-') << "" << std::endl;
    std::cout << std::setw(56) << std::setfill(' ') << "Welcome to the Tic-Tac-Toe game!" << std::endl;
    std::cout << std::setw(80) << std::setfill('-') << "" << std::endl;
    std::cout << "\nPress Enter to continue. . .\n" << std::endl;
    std::cin.get();
}

void display_menu()
{
    std::cout << std::setfill('-') << std::setw(45) << "Main Menu" << std::setw(35) << "" << std::endl;
    std::cout << "\nPress 'S' to start a single-player game." << std::endl;
    std::cout << "Press 'M' to start a multi-player game." << std::endl;
    std::cout << "Press 'Q' to quit the game." << std::endl;
}

void display_board(std::vector<std::vector<char>> &board)
{
    std::cout << std::endl;
    for (auto row : board)
    {
        for (auto place : row)
        {
            std::cout << place << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void handle_multiplayer()
{
    Player player1, player2;
    std::string player1_name, player2_name;

    std::cout << "\nEnter the name for player 1: ";
    std::getline(std::cin, player1_name);
    player1.set_name(player1_name);

    std::cout << "\nEnter the name for player 2: ";
    std::getline(std::cin, player2_name);
    player2.set_name(player2_name);

    // Losowanie kto ma kó³ko a kto krzy¿yk (kto zaczyna)


    if (player1.is_starting())
    {
        player1.set_symbol('O');
        player2.set_symbol('X');
        std::cout << "\nPlayer " << player1.get_name() << " is starting! [O]" << std::endl;
    }
    else
    {
        player1.set_symbol('X');
        player2.set_symbol('O');
        std::cout << "\nPlayer " << player2.get_name() << " is starting! [O]" << std::endl;
    }
    
    std::vector<std::vector<char>> board = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };

    start_game_multi(player1, player2, board);


}

void handle_singleplayer()
{
    Player player;
    std::string player_name;
    std::cout << "\nEnter the name for player: ";
    std::getline(std::cin, player_name);
    player.set_name(player_name);
    player.set_symbol('O');
 
    Player computer;
    computer.set_name("Computer");
    computer.set_symbol('X');

    std::vector<std::vector<char>> board = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };

    

    start_game_single(player, computer, board);

    
}

void start_game_multi(Player& player1, Player& player2, std::vector<std::vector<char>> &board)
{


    do
    {

        if (player1.get_symbol() == 'O')
        {
            display_board(board);

            std::cout << "\n" << player1.get_name() << "'s turn!" << std::endl;
            std::cout << "\nEnter the number you want to place [" << player1.get_symbol() << "] in: ";

            char place1{};
            std::cin >> place1;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (!is_place_valid(place1, board))
            {
                std::cout << "\nYou entered invalid or already taken place, please try again!" << std::endl;
                std::cout << "Enter the valid place: ";
                std::cin >> place1;
            }
            
            enter_to_board(place1, board, player1);

            display_board(board);

            if (is_winner(board))
            {
                std::cout << "\nPlayer: " << player1.get_name() << " won!\nCongrats!!" << std::endl;
                break;
            }

            if (is_board_full(board))
                break;

            std::cout << "\n" << player2.get_name() << "'s turn!" << std::endl;
            std::cout << "\nEnter the number you want to place [" << player2.get_symbol() << "] in: ";

            char place2{};
            std::cin >> place2;

            while (!is_place_valid(place2, board))
            {
                std::cout << "\nYou entered invalid or already taken place, please try again!" << std::endl;
                std::cout << "Enter the valid place: ";
                std::cin >> place2;
            }
            enter_to_board(place2, board, player2);


            if (is_winner(board))
            {
                display_board(board);
                std::cout << "\nPlayer: " << player2.get_name() << " won!\nCongrats!!" << std::endl;
                break;
            }

        }
        else
        {
            display_board(board);

            std::cout << "\n" << player2.get_name() << "'s turn!" << std::endl;
            std::cout << "\nEnter the number you want to place [" << player2.get_symbol() << "] in: ";

            char place2{};
            std::cin >> place2;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (!is_place_valid(place2, board))
            {
                std::cout << "\nYou entered invalid or already taken place, please try again!" << std::endl;
                std::cout << "Enter the valid place: ";
                std::cin >> place2;
            }

            enter_to_board(place2, board, player2);

            display_board(board);

            

            if (is_winner(board))
            {
                std::cout << "\nPlayer: " << player2.get_name() << " won!\nCongrats!!" << std::endl;
                break;
            }

            if (is_board_full(board))
                break;

            std::cout << "\n" << player1.get_name() << "'s turn!" << std::endl;
            std::cout << "\nEnter the number you want to place [" << player1.get_symbol() << "] in: ";

            char place1{};
            std::cin >> place1;

            while (!is_place_valid(place1, board))
            {
                std::cout << "\nYou entered invalid or already taken place, please try again!" << std::endl;
                std::cout << "Enter the valid place: ";
                std::cin >> place1;
            }
            enter_to_board(place1, board, player1);


            if (is_winner(board))
            {
                display_board(board);
                std::cout << "\nPlayer: " << player1.get_name() << " won!\nCongrats!!" << std::endl;
                break;
            }
        }
    } while (!is_board_full(board));
    if (is_board_full(board) && (!is_winner(board)))
        std::cout << "It's a draw!" << std::endl;


}

void start_game_single(Player& player, Player &computer, std::vector<std::vector<char>>& board)
{
    srand(time(NULL));          //Inicjalizacja maszyny losuj¹cej pola komputerowi

    do
    {
        display_board(board);

        std::cout << "\n" << player.get_name() << "'s turn!" << std::endl;
        std::cout << "\nEnter the number you want to place [" << player.get_symbol() << "] in: ";

        char place{};
        std::cin >> place;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while (!is_place_valid(place, board))
        {
            std::cout << "\nYou entered invalid or already taken place, please try again!" << std::endl;
            std::cout << "Enter the valid place: ";
            std::cin >> place;
        }

        enter_to_board(place, board, player);

        display_board(board);

        if (is_winner(board))
        {
            std::cout << "\nPlayer: " << player.get_name() << " won!\nCongrats!!" << std::endl;
            break;
        }

        if (is_board_full(board))
            break;

        std::cout << "\nComputer's turn!" << std::endl;
        
        char computer_place = computer_selection();
        while (!is_place_valid(computer_place, board))
        {
            computer_place = computer_selection();
        }
        
        enter_to_board(computer_place, board, computer);

        if (is_winner(board))
        {
            display_board(board);
            std::cout << "Computer won!\nBetter luck next time!" << std::endl;
            break;
        }

    } while (!is_board_full(board));
    if (is_board_full(board) && (!is_winner(board)))
        std::cout << "It's a draw!" << std::endl;
}

bool is_winner(const std::vector<std::vector<char>> &board)
{
    // Checking if 3 in row
    for (size_t i{}; i < board.size(); ++i)
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return true;

    // Checking if 3 in column
    for (size_t i{}; i < board.size(); ++i)
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return true;

    // Checking if 3 in diagonals
    if ((board[0][0] == board[1][1] && board[0][0] == board[2][2]) || (board[2][0] == board[1][1] && board[2][0] == board[0][2]))
        return true;
    
    return false;
    
}

bool is_board_full(const std::vector<std::vector<char>> &board)
{
    int taken_place_counter{};
    for (auto row : board)
        for (char element : row)
            if (element == 'O' || element == 'X')
                ++taken_place_counter;

    if (taken_place_counter > 8) 
    {
        return true;
    }
        
    return false;
}

bool is_place_valid(char place, const std::vector<std::vector<char>> &board) {
    if (place != '1' && place != '2' && place != '3' && place != '4' && place != '5' && place != '6' && place != '7' && place != '8' && place != '9')
        return false;
    
    for (auto vec : board)
    {
        if (std::find(vec.begin(), vec.end(), place) != vec.end())
            return true;
    }
    return false;
}

void enter_to_board(char &place, std::vector<std::vector<char>> &board, Player &player)
{
    for (auto &row : board)
    {
        for (char &position : row)
        {
            if (place == position)
            {
                position = player.get_symbol();
                break;
            }
                
        }
    }
}

char computer_selection()
{
    int random_number {(std::rand() % 9) + 1};      // Inicjalizacja i wylosowanie liczby z przedzia³u 1-9

    switch (random_number)
    {
    case 1:
        return '1';
        break;
    case 2:
        return '2';
        break;
    case 3:
        return '3';
        break;
    case 4:
        return '4';
        break;
    case 5:
        return '5';
        break;
    case 6:
        return '6';
        break;
    case 7:
        return '7';
        break;
    case 8:
        return '8';
        break;
    case 9:
        return '9';
        break;
    }
}