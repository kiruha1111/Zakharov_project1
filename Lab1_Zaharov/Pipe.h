#pragma once
#include <string>
#include <vector>

class Pipe
{
private:
	double length;
	double diametr;
	bool under_repair;
	int Id;
	static int MaxId;
	static std::vector<int> possible_diameters;

public:

	std::string name;
	enum Action {set_work, set_repair, set_opposite};

	void add_pipe();
	void ShowInfo();
	void Edit(const Action);
	Pipe();
	static inline std::vector<int> GetSizes() { return possible_diameters; };
	void WriteInfo_WithStateDiametr(int diameter);

	int GetId() { return Id; }
	static int GetMaxId() { return MaxId; }
	int GetRepair() { return under_repair; };
	int GetDiametr() const { return diametr; };
	double GetCapacity() const;
	double GetLenght() const { return under_repair ? length : DBL_MAX; };
	friend std::ofstream& operator << (std::ofstream& file, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& file, Pipe& pipe);
};