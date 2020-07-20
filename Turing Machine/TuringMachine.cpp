/* 
	course: theory of Automata and regular languages (computation)
	Professor: Professor PourGholamAli
	Semester: spring 1399
	Project creator: Parsa KamaliPour
	Project title: Turing Machine Simulator
	Project tested with Busy Beaver and it works

*/


#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

typedef vector<char> Tape;               // tape is vector that accepts char
typedef map<string, string> Program;     // sets of rules are map, example: a0 -> b1r which 'a0' will be key of map and 'b1r' will be value of that key

class TuringMachine
{
public:
	TuringMachine(Program program, char start, char halt, char init);     //constructor
	~TuringMachine();                                                     //destructor
	void Run();
	int GetMoves();           //returns number of moves that machine has done

private:
	Tape tape;
	Program program;                   //rules
	char start, halt, init, state;     // start -> first state, halt -> state that halt program, init -> tape default value, state -> current state
	int moves;           //number of moves that machine has done
	int pos;             //position of head
	bool tapeChanged;    // has tape changed?
	void PrintTape();                                    //shows tape in console
	void UpdateTape(char oldSymbol, char newSymbol);     // changes tape's old symbol with new one
	void UpdateState(char newState);                     // changes machine state
	void MoveHead(char move);                            // move head to either left or right
	string GetKey();                                     // gets first part of rules as key for map
	string GetValue(string& key);                        // gets second part of rules as value for that key in map
};

TuringMachine::TuringMachine(Program program, char start, char halt, char init) :       //constructor
	tape(1, init), program(program), start(start), halt(halt),
	init(init), state(start), moves(0), pos(0)
{
}

TuringMachine::~TuringMachine()             //destructor
{
}

void TuringMachine::Run()
{
	while (state != halt)              // if our new state is the same as halt char, halt machine
	{
		PrintTape();
		string key = GetKey();           //first part of rules
		string value = GetValue(key);    //last part of rules
	                                         //for example: a0->b1r
		char newState = value[0];            // 'b' is new state
		char newSymbol = value[1];           // '1' is new symbol
		char move = value[2];                // 'r' means move to right
		char oldSymbol = key[1];             // '0' is our old symbol

		UpdateTape(oldSymbol, newSymbol);
		UpdateState(newState);
		MoveHead(move);
	}
	PrintTape();
}

int TuringMachine::GetMoves()
{
	return moves;
}

void TuringMachine::PrintTape()
{
	if (tapeChanged)
	{
		for (int i = 0; i < tape.size(); i++)
			cout << tape[i];
		cout << endl;
	}
}

void TuringMachine::UpdateTape(char oldSymbol, char newSymbol)
{
	if (oldSymbol != newSymbol)     //change old symbol with new one
	{
		tape[pos] = newSymbol;
		tapeChanged = true;
	}
	else
		tapeChanged = false;
}

void TuringMachine::UpdateState(char newState)
{
	state = newState;                   //change state
}

void TuringMachine::MoveHead(char move)
{
	if (move == 'l')           //if 'l' move left
		pos--;
	else if (move == 'r')      //if 'r' move right
		pos++;
	else       //error
		throw string("unknown");

	if (pos < 0)          // if we have reached the leftmost part of tape, add a element to beginning of tape
	{
		tape.insert(tape.begin(), init);
		pos = 0;
	}
	if (pos >= tape.size())       // if we have reached the rightmost part of tape (end of tape), add a element to the end of tape
		tape.push_back(init);
	moves++;                   //update moves
}

string TuringMachine::GetKey()
{
	char key[3] = { 0 };      // initiate a empty char sized 3 
	key[0] = state;           // first letter is our current state
	key[1] = tape[pos];       // second letter is our current symbol on this position in tape
	return string(key);       // return char as key to be used in map
}

string TuringMachine::GetValue(string& key)
{
	return program[key];      // enter key in map to receive value of it ( last part of a rule )
}



Program rules;
void Rules()                  // this is our machine input, enter your sets of rules here 
{
	rules.insert(make_pair("a0", "b1r"));
	rules.insert(make_pair("b0", "c0r"));                 // this is a set of rules for busy beaver 3 state
	rules.insert(make_pair("c0", "c1l"));
	rules.insert(make_pair("a1", "h1r"));
	rules.insert(make_pair("b1", "b1r"));
	rules.insert(make_pair("c1", "a1l"));
}

void InitTM()
{
	Rules();                                      //get instructions as input
	TuringMachine tm(rules, 'a', 'h', '0');       // make a machine that has that rules, first state is 'a', 'h' as state halts machine, initiate tape with 0
	tm.Run();                                                 //run the turing machine
	cout << "Number of moves : " << tm.GetMoves() << endl;
}

int main()
{
	InitTM();
}