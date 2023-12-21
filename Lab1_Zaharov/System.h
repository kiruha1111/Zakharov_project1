#pragma once
#include "Utilities.h"
#include "Pipe.h"
#include "Station.h"
#include "Connections.h"

class System
{
public:
	enum ObjectType {pipe, station};
	bool HasObject(const ObjectType obj);
	std::unordered_set<int> GetIDs(const ObjectType obj);
	void add_p();
	void add_CS();
	void Watch_All(System& GasSystem);
	void Save();
	void Download();
	void ViewStations();
	void ViewPipes();
	void EditPipes(std::unordered_set<int>& IDs);
	void EditStations(std::unordered_set<int>& IDs);
	void Edit_ByName(const ObjectType obj);
	void Edit_ByParametr(const ObjectType obj);
	void DeletePipes(std::unordered_set<int>& IDs);
	void DeleteStations(std::unordered_set<int>& IDs);
	void Delete_ByName(const ObjectType obj);
	void Delete_ByParametr(const ObjectType obj);
	void ViewConnections();
	Connections connections;
	void CreateConnection();
	void DeleteConnection();
	void TopologicalSort();
	void ShortestPath();
	void MaxFlow();
	void CreateStateDiametrPipe(Pipe& pipe, int diameter);
	
private:
	int InputExistIdStation();
	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Station> stations;
	void ViewObjects(std::unordered_set<int> result, const System::ObjectType obj);
	std::unordered_set<int> GetEditNumbers(std::unordered_set<int>& result, const System::ObjectType obj);
	std::unordered_set<int> GetFreePipes(const std::unordered_set<int>& IDs);
};

