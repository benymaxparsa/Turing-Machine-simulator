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
	void PrintTape();
	void UpdateTape(char oldSymbol, char newSymbol);
	void UpdateState(char newState);
	void MoveHead(char move);
	

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

}

int TuringMachine::GetMoves()
{
	return 0;
}

void TuringMachine::PrintTape()
{
}

void TuringMachine::UpdateTape(char oldSymbol, char newSymbol)
{

}

void TuringMachine::UpdateState(char newState)
{
}

void TuringMachine::MoveHead(char move)
{
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
}

int main()
{
	InitTM();
}