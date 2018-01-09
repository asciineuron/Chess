#include <iostream>
#include <vector>
#include <string>
#include <fstream> //interesting to add a function to write to a log file to record game outcomes

using namespace std;

bool can_move = false; //used to test move legality

bool is_over = false;
bool is_started = false;

//represent the board as 8x8 array with info about pieces at each square, 0 is empty, + is white, - is black
//piece value is as follows: 1 pawn, 2 knight, 3 bishop, 4 rook, 5 queen, 6 king
// not changing size, so use array instead? vector<vector<int>> board (8, vector<int>(8));
int board[8][8];
//first array row or rank, second column or file
//for files: a,b,c,d,e,f,g,h is 1,2,3,4,5,6,7,8

int test_position[2]; //used to compare resulting position to initial position when moving pieces

class Chess_piece
{
public:
  Chess_piece(int color_set, /*int position_set[2]*/ int file, int rank) //color, position
  {
    color = color_set;
    position[0] = file;
    position[1] = rank;
  }

  int get_color()
  {
    return color;
  }

  int *get_position()
  {
    return position;
  }

  int set_position(int x)
  {
    *get_position() = x;
  }
  
  void capture_piece(Chess_piece piece_to_capture)
  {
    //give commands to remove another piece from board
    /*???*/ piece_to_capture.is_in_play = false;
  }

  void try_move()
  {
    //checks if given move is possible
    
  }

  //static bool can_move; //will reset each turn, check if a move is allowed
  
private:
  static int num_pieces;
  int position[2]; //first value is file or col, second is rank or row
  //thus moving to eg. 'e5' would be position[0] = 5 position[1] = 5 
  bool is_in_play;
  int color_val; //+ for white - for black, see scale above
  int color; //1 for white -1 for black, in order to move in proper direction
};
//following are subclasses for each individual piece, specifying specific allowed moves, etc.
class Pawn : Chess_piece
{
public:
  Pawn (int color_set, int file, int rank) : Chess_piece(color_set, file, rank)
  {

  }
  
  void try_move()
  {
    if (*get_position() + get_color() == test_position[0])
      {
	//position[0] += color;
	set_position(*get_position() + get_color());
	can_move = true;
      } else if (*get_position() + 2*get_color() == test_position[0])
      {
	//position[0] += 2*color;
	set_position(*get_position() + 2*get_color());
	can_move = true;
      } else
      {
	cout << "Please enter a valid move" << endl;
      }
  }
private:
  int val;
};

class Knight : Chess_piece
{
public:
  Knight (int color_set, int file, int rank) : Chess_piece(color_set, file, rank)
  {

  }
  
private:
};

class Bishop : Chess_piece
{
public:
  Bishop (int color_set, int file, int rank) : Chess_piece(color_set, file, rank)
  {

  }
private:
};

class Rook : Chess_piece
{
public:
  Rook (int color_set, int file, int rank) : Chess_piece(color_set, file, rank)
  {

  }
private:
};

class Queen : Chess_piece
{
public:
  Queen (int color_set, int file, int rank) : Chess_piece(color_set, file, rank)
  {

  }

private:
};

class King : Chess_piece
{
public:
  King (int color_set, int file, int rank) : Chess_piece(color_set, file, rank)
  {

  }
private:
};


void start_game()
{
  cout << "start of game to be finished!" << endl;
  is_started = true;
}

void print_board()
{
  //will run through and print each board square, converting from numbering as above to character piece notation
  cout << " abcdefgh" << endl;
  for (int i = 0; i < sizeof(board)/sizeof(*board) /*total size of array divided by size of single element*/; i++)
    {
      cout << (8 - i); //represent white as caps and black as lower case?
      for (int j = 0; j < sizeof(board[0])/sizeof(*board[0]); j++)
	{
	  //cout << board[i][j];
	  if (board[i][j] > 0)
	    {
	      //white piece
	      switch (board[i][j])
		{
		case 1:
		  cout << "P"; //unconventional, pawn
		  break;
		case 2:
		  cout << "N"; //knight
		  break;
		case 3:
		  cout << "B"; //bishop
		  break;
		case 4:
		  cout << "R"; //rook
		  break;
		case 5:
		  cout << "Q"; //queen
		  break;
		case 6:
		  cout << "K";
		  break;
		default:
		  cout << "*"; //unknown
		}
	    } else if (board[i][j] < 0)
	    {
	      //black piece
	      switch (board[i][j])
		{
		case -1:
		  cout << "p"; //unconventional, pawn
		  break;
		case -2:
		  cout << "n"; //knight
		  break;
		case -3:
		  cout << "b"; //bishop
		  break;
		case -4:
		  cout << "r"; //rook
		  break;
		case -5:
		  cout << "q"; //queen
		  break;
		case -6:
		  cout << "k";
		  break;
		default:
		  cout << "*"; //unknown
		}
	    } else
	    {
	      //no piece present
	      cout << " ";
	    }
	}
      cout << (8 - i) << endl;
    }
}

void display_help()
{
  //will write help.txt with commands etc. and will be printed to console upon calling this commands
  cout << "help info to be finished!" << endl;
}

void quit_game()
{
  cout << "Thanks for playing!" << endl;
  is_over = true;
}

void parse_input(string input)
{
  //will parse the users input to issue commands
  if (!is_started)
    {
      //separates starting commands from gameplay commands
      try
	{
	  if (input == "s")
	    {
	      start_game();
	    } else if (input == "h")
	    {
	      display_help();
	    } else if (input == "q")
	    {
	      quit_game(); 
	    } else
	    {
	      cout << "Please enter a valid command:" << endl;
	    }
	}
      catch (exception &e)
	{
	  cout << "Please enter a valid command:" << endl;
	}
    }

  
}

int main()
{
  Chess_piece chess(0, 0, 0); //no info, used for control processes
  string input = "";
  
  cout << "Welcome to chess! Please enter a command:\n\ts : start the game\n\th : help information "
       << "and a list of available commands\n\tq : quit"<< endl;

  while (!is_over)
    {
      if (is_started) //will initialize all pieces if game is started
	{
	  //black side:
	  Pawn pa(-1, 1, 7);
	  Pawn pb(-1, 2, 7);
	  Pawn pc(-1, 3, 7);
	  Pawn pd(-1, 4, 7);
	  Pawn pe(-1, 5, 7);
	  Pawn pf(-1, 6, 7);
	  Pawn pg(-1, 7, 7);
	  Pawn ph(-1, 8, 7);

	  Knight nb(-1, 2, 8);
	  Knight ng(-1, 7, 8);

	  Bishop bc(-1, 3, 8);
	  Bishop bf(-1, 6, 8);

	  Rook ra(-1, 1, 8);
	  Rook rh(-1, 8, 8);

	  Queen qd(-1, 4, 8);

	  King ke(-1, 5, 8);

	  //white side:
	  Pawn Pa(1, 1, 2);
	  Pawn Pb(1, 2, 2);
	  Pawn Pc(1, 3, 2);
	  Pawn Pd(1, 4, 2);
	  Pawn Pe(1, 5, 2);
	  Pawn Pf(1, 6, 2);
	  Pawn Pg(1, 7, 2);
	  Pawn Ph(1, 8, 2);

	  Knight Nb(1, 2, 1);
	  Knight Ng(1, 7, 1);

	  Bishop Bc(1, 3, 1);
	  Bishop Bf(1, 6, 1);

	  Rook Ra(1, 1, 1);
	  Rook Rh(1, 8, 1);

	  Queen Qd(1, 4, 1);

	  King Ke(1, 5, 1);

	}



      cin >> input;
      //stuff to be executed
      parse_input(input);
      print_board();
      input = "";
      
      can_move = false;
    }
}
