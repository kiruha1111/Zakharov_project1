#pragma once
#include <string>

class Pipe
{
private:
	double length;
	double diametr;
	bool under_repair;
	int Id;
	static int MaxId;

public:

	std::string name;
	enum Action {set_work, set_repair, set_opposite};

	void add_pipe();
	void ShowInfo();
	void Edit(const Action);
	Pipe();

	int GetId() { return Id; }
	static int GetMaxId() { return MaxId; }
	int GetRepair() { return under_repair; };
	friend std::ofstream& operator << (std::ofstream& file, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& file, Pipe& pipe);
};