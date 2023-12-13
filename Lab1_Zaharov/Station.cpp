#include "Station.h"
#include "Utilities.h"
using namespace std;

int Station::MaxId = 1000;


Station::Station() {
	name = "Non";
	number_workshop = 0;
	work_workshop = 0;
	performance = 0;
	Id = ++MaxId;
}

void Station::Edit(int active) {
	work_workshop = active;
	if (work_workshop > number_workshop)
	{
		work_workshop = number_workshop;
	}
}


int workshops_check(int nw)
{
	while (true)
	{
		int ww = GetCorrectNumber(0, 10000);
		if (ww <= nw) {
			return ww;
		}
		else if (ww > nw) {
			cout << "Work workshops more than workshops! Try again" << endl;
		}
	}
}


void Station::add_compressor() {
	cout << "Enter properties of a compressor station (name, number workshops, number of work workshops, perfomance(0-100)):" << endl;
	getline(cin, name);
	number_workshop = GetCorrectNumber(0, 10000);
	work_workshop = workshops_check(number_workshop);
	performance = GetCorrectNumber(0, 100);
	cout << endl;
}


void Station::ShowInfo() {
	cout << "Name: " << name << endl
		<< "Workshops: " << number_workshop << endl
		<< "Work workshops: " << work_workshop << endl
		<< "Perfomance: " << performance << endl
		<< "ID: " << Id << endl;
}

ofstream& operator << (ofstream& file, const Station& CS) {
	if (file.is_open()) {
		file << CS.name << endl;
		file << CS.number_workshop << endl;
		file << CS.work_workshop << endl;
		file << CS.performance << endl;
		file << CS.Id << endl;
	}
	return file;
}

ifstream& operator >> (ifstream& file, Station& CS) {
	if (file.is_open()) {
		file >> ws;
		getline(file, CS.name);
		file >> CS.number_workshop;
		file >> CS.work_workshop;
		file >> CS.performance;
		file >> CS.Id;
		if (CS.Id > Station::MaxId)
			Station::MaxId = CS.Id;
	}
	return file;
}