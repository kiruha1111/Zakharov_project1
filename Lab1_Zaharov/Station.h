#pragma once
#include <string>

class Station
{
private:
	
	int number_workshop;
	int work_workshop;
	int performance;
	int Id;
	static int MaxId;

public:
	std::string name;

	void add_compressor();
	void ShowInfo();
	void Edit(int active);
	Station();

	int GetId() { return Id; }
	static int GetMaxId() { return MaxId; }
	double GetUnactiveWorkshop() { return ((double)number_workshop - (double)work_workshop / (double)number_workshop) * 100.0; };
	friend std::ofstream& operator << (std::ofstream& file, const Station& CS);
	friend std::ifstream& operator >> (std::ifstream& file, Station& CS);
};

