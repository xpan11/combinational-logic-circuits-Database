//CIS554 HW6. Due: 11:59pm, Monday, Dec. 13.
//Store combinational logic circuits with one or more outputs to a database, implemented using unordered_map.
//If you finish the above, you can consider also support sequential circuits. A limited bonus will be given for this.
//In addition to submitting your code, you need to submit a PDF file ducumenting your design.
//The PDF file should contain at least 2-3 pages with single space.

/*This is more a take-home exam than regular HW. You are not allowed to discuss with other students.
I will only reply to clarification questions or anything that leads to sharing reply to the whole class.
Your design has to be realistic for applications.
Note that permuting input columns, output columns, or rows
will not affect the function of a circuit.

*/
#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class Circuit {//Truth Table
public:
	int Inputs;//number of inputs
	int Output; //number of outputs
	int decsum;
	map<string, string> truthtable;
	Circuit() :Inputs{ 0 }, Output{ 0 }, decsum{ 0 }{};
	Circuit(int i, int j) :Inputs(i), Output(j), decsum{0} {};
	void tadd(string c);
	//void tsort();
	int produce_key();




//Design your own structure to store the Truth Table

//Optionally, you can design a function to preprocess the circuit (i.e., Truth Table) before hashing or equal_to.

//Note that permuting input columns, output columns, or rows
//will not affect the function of a circuit.c

};//End of class
void Circuit::tadd(string c) {
	string input = c.substr(0,Inputs);
	//cout << "first" << input<<endl;
	string output = c.substr(Inputs+1, Output+Inputs);
	//cout << "next" << output<<endl;

	string dec = input + output;
	/*for (int i = 0; i < Inputs+Output; i++) 	{
		string cur = c.substr(i, c.find(""));
		std::string::size_type sz;
		decsum = (std::stoi(input, &sz))*(2^i)* (i+1)*10;

	}*/
	decsum = decsum + std::stoi(dec, nullptr, 2);


	//decsum = decsum + Idec + Odec;
	pair<string, string> v = pair<string, string>(input, output);
	truthtable.insert(v);
}
int Circuit::produce_key() {
	return truthtable.size()* decsum*(Inputs * 10 + Output);
}


class Thash {
public:
	bool operator()(int a, int b) const;
	size_t operator()(int a) const;
};


//You also need to design the needed hash and equal_to.

//You will need to design a way to produce key for hashing and equal_to such that 
//there will not be duplicates
ostream& operator<<(ostream& str, const Circuit C) {
	str << "{ " << "input = " << C.Inputs << " Output = " << C.Output << " ";
	auto it = C.truthtable.begin();
	while (it != C.truthtable.end()) {
		str << "< " << it->first << ", " << it->second << " > ";
		++it;
	}
	str << " }";
	return str;

}

ostream& operator<<(ostream& str, const unordered_map<int, Circuit,Thash> DB) {
	str << "{";
	auto it = DB.begin();
	while (it != DB.end()) {
		str << "< " << it->first << ", " << it->second << "> "<<endl;
		++it;
	}
	str << "}";
	return str;
}

int main() {
	unordered_map<int, Circuit, Thash> DB;
	ifstream f("a1.txt");
	string numC;
	getline(f, numC);
	//cout << "total" << numC << endl;
	std::string::size_type sz;
	int total = (std::stoi(numC, &sz));
	for (int i = 0; i < total; i++) {
		getline(f, numC);
		int in = (std::stoi(numC, &sz));
		//cout <<"input" << in << endl;

		getline(f, numC);

		int out = (std::stoi(numC, &sz));
		//cout << "outputnumC" << out << endl;

		Circuit tmp = Circuit(in, out);
		//cout << tmp.Inputs << " " << tmp.Output << endl;
		//cout << "2power" << (2 ^ in) << endl;
		for (int j = 0; j < pow(2,in); j++) {

			getline(f, numC);
			//cout << "line"<< j<<" " << numC << endl;

			tmp.tadd(numC);
		}
		if (DB.find(tmp.produce_key())==DB.end()) {
			DB[tmp.produce_key()] = tmp;

		}
		else { cout << "The circuit is already in DB" << endl; }
	
	//cout << DB.find(31488)->second << endl;
	//cout << DB.find(67056)->second << endl;

	//cout << DB.find(140352)->second << endl;
	}

	//cout << DB << endl;
	//cout << DB.find(31488)->second << endl;
	//cout << DB.find(67056)->second << endl;

//	cout << DB.find(140352)->second << endl;

	return 0;
}
bool Thash::operator()(int a, int b) const{
	return a == b;
}
size_t Thash::operator()(int a) const{
	//int sum = c.decsum;
	return hash<int>()(a);
}


//input circuits in file circuits.txt

////const
//16//number of circuits
//3//number of inputs; the number of rows will be 2^(number of inputs)
//2//number of outputs
//000 10
//001 00
//010 00
//011 10
//100 00
//101 11
//110 01
//111 11
//4
//1
//0000 0
//0001 1
//0010 0
