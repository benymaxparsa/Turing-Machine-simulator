#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

typedef vector<char> Tape;
typedef map<string, string> Program;

class TuringMachine
{
public:
	TuringMachine(Program program, char start, char halt, char init);
	~TuringMachine();
	void Run();
	int GetMoves();

private:
	Tape tape;
	Program program;
	char start, halt, init, state;
	int moves;
	int pos;
	bool tapeChanged;
	void PrintTape();
	void UpdateTape(char oldSymbol, char newSymbol);
	void UpdateState(char newState);
	void MoveHead(char move);
	string GetKey();
	string GetValue(string& key);
};

TuringMachine::TuringMachine(Program program, char start, char halt, char init) : 
	tape(1, init), program(program), start(start), halt(halt),
	init(init), state(start), moves(0), pos(0)
{
}

TuringMachine::~TuringMachine()
{
}

void TuringMachine::Run()
{
	while (state != halt)
	{
		PrintTape();
		string key = GetKey();
		string value = GetValue(key);

		char newState = value[0];
		char newSymbol = value[1];
		char move = value[2];
		char oldSymbol = key[1];

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
	if (oldSymbol != newSymbol)
	{
		tape[pos] = newSymbol;
		tapeChanged = true;
	}
	else
		tapeChanged = false;
}

void TuringMachine::UpdateState(char newState)
{
	state = newState;
}

void TuringMachine::MoveHead(char move)
{
	if (move == 'l')
		pos--;
	else if (move == 'r')
		pos++;
	else
		throw string("unknown");

	if (pos < 0)
	{
		tape.insert(tape.begin(), init);
		pos = 0;
	}
	if (pos >= tape.size())
		tape.push_back(init);
	moves++;
}

string TuringMachine::GetKey()
{
	char key[3] = { 0 };
	key[0] = state;
	key[1] = tape[pos];
	return string(key);
}

string TuringMachine::GetValue(string& key)
{
	return program[key];
}



Program rules;
void Rules()
{
	rules.insert(make_pair("a0", "b1r"));
	rules.insert(make_pair("b0", "c0r"));
	rules.insert(make_pair("c0", "c1l"));
	rules.insert(make_pair("a1", "h1r"));
	rules.insert(make_pair("b1", "b1r"));
	rules.insert(make_pair("c1", "a1l"));
}

void InitTM()
{
	Rules();
	TuringMachine tm(rules, 'a', 'h', '0');
	tm.Run();
	cout << "Number of moves : " << tm.GetMoves() << endl;
}

int main()
{
	InitTM();
}