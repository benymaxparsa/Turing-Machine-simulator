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

private:
	Tape tape;
	Program program;
	char start, halt, init, state;
	int moves;
	int pos;
};

TuringMachine::TuringMachine(Program program, char start, char halt, char init) : 
	tape(1, init), program(program), start(start), halt(halt),
	init(init), state(start), moves(0), pos(0)
{
}

TuringMachine::~TuringMachine()
{
}



void InitTM()
{
	Program rules;
	rules.insert(make_pair("a0", "b1r"));
	rules.insert(make_pair("b0", "c0r"));
	rules.insert(make_pair("c0", "c1l"));
	rules.insert(make_pair("a1", "h1r"));
	rules.insert(make_pair("b1", "b1r"));
	rules.insert(make_pair("c1", "a1l"));
}