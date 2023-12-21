#include "Pipe.h"
#include "Utilities.h"
using namespace std;

int Pipe::MaxId = 0;
vector<int> Pipe::possible_diameters = {500, 700, 1000, 1400};


Pipe::Pipe()
{
	name = "Non";
	length = 0.0;
	diametr = 0.0;
	under_repair = 0;
	Id = ++MaxId;
}


void Pipe::add_pipe() {
	cout << "Enter properties of a pipe (name, length, diametr and repair or not (0 or 1)):" << endl;
	name = input_string();
	length = GetCorrectNumber(0, 10000);
	diametr = GetCorrectNumber(0, 10000);
	under_repair = GetCorrectNumber(0, 10000);
	cout << endl;
}

void Pipe::ShowInfo() {
	cout << "Name: " << name << endl
		<< "Length: " << length << endl
		<< "Diametr: " << diametr << endl
		<< "Repair or not: " << under_repair << endl
		<< "ID: " << Id << endl;
}

void Pipe::Edit(const Action act) {
	switch (act) {
	case set_work: {under_repair = true; return;}
	case set_repair: {under_repair = false; return;}
	case set_opposite: {under_repair = !under_repair; return;}
	default: {return;}
	}
}

ofstream& operator << (ofstream& file, const Pipe& p) {
	if (file.is_open()) {
		file << p.name << endl;
		file << p.length << endl;
		file << p.diametr << endl;
		file << p.under_repair << endl;
		file << p.Id << endl;
	}
	return file;
}

ifstream& operator >> (ifstream& file, Pipe& pipe) {
	if (file.is_open()) {
		file >> ws;
		getline(file, pipe.name);
		file >> pipe.length;
		file >> pipe.diametr;
		file >> pipe.under_repair;
		file >> pipe.Id;
		if (pipe.Id > Pipe::MaxId)
			Pipe::MaxId = pipe.Id;
	}
	return file;
}

void Pipe::WriteInfo_WithStateDiametr(int diameter) {
	cout << "Enter the name of the pipe:" << endl;
	name = input_string();


	cout << "Enter length of the pipe:" << endl;
	length = GetCorrectNumber(1.0, 100000000.);

	this->diametr = diameter;

	cout << "Enter condition of the pipe (1 - work, 0 - under repair)" << endl;

	if (GetCorrectNumber(0, 1)) { under_repair = true; }
	else { under_repair = false; }
}

double Pipe::GetCapacity() const {
	double capacity = sqrt(pow(diametr, 5) / length);
	return under_repair ? capacity : -DBL_MAX;
}