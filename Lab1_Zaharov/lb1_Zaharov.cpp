#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"
#include "Utilities.h"
#include "System.h"
#include <format>
#include <chrono>


using namespace std;
using namespace chrono;

void EditOnePipe(System& GasSystem)
{
	cout << "Pipes:" << endl;
	GasSystem.ViewPipes();
	cout << "Choose edit pipe: ";
	auto keys = GasSystem.GetIDs(System::pipe);
	int number = GetCorrectNumber<int>(1, INT_MAX);
	if (!keys.contains(number)) { cout << "No such ID!" << endl; return; }
	unordered_set<int> key = { number };
	GasSystem.EditPipes(key);
}

void EditOneStation(System& GasSystem) {
	cout << "Stations:" << endl;
	GasSystem.ViewStations();
	cout << "Choose edit station: ";
	auto keys = GasSystem.GetIDs(System::station);
	int number = GetCorrectNumber<int>(1, INT_MAX);
	if (!keys.contains(number)) { cout << "No such ID!" << endl; return; }
	unordered_set<int> key = { number };
	GasSystem.EditStations(key);
}

void Edit_Pipes(System& GasSystem) {
	if (!GasSystem.HasObject(System::pipe)) { cout << "No pipes!" << endl; return; }

	cout << "1. Edit one pipe" << endl
		<< "2. Edit by filter" << endl
		<< "0. Back" << endl;

	switch (GetCorrectNumber(0, 2))
	{

	case 1: {EditOnePipe(GasSystem); break; }
	case 2: {
		cout << "Choose:" << endl
			<< "1. Find by name" << endl
			<< "2. Find by parametr" << endl
			<< "0. Back" << endl;

		switch (GetCorrectNumber(0, 2))
		{
		case 1:
		{
			GasSystem.Edit_ByName(System::pipe);
			break;
		}
		case 2:
		{
			GasSystem.Edit_ByParametr(System::pipe);
			break;
		}
		case 0: { break; }
		}
	case 0: {break; }
	}
	}
}

void Edit_Stations(System& GasSystem)
{
	if (!GasSystem.HasObject(System::station)){ cout << "No stations!" << endl; return;}

	cout << "1. Edit one station" << endl
		<< "2. Edit by filter" << endl
		<< "0. Back" << endl;

	switch (GetCorrectNumber(0, 2))
	{
	case 1: { EditOneStation(GasSystem); break; }

	case 2: {
		cout << "Choose:" << endl
			<< "1. Find by name" << endl
			<< "2. Find by parametr" << endl
			<< "0. Back" << endl;

		switch (GetCorrectNumber(0, 2)) {
		case 1:
		{
			GasSystem.Edit_ByName(System::station);
			break;
		}
		case 2:
		{
			GasSystem.Edit_ByParametr(System::station);
			break;
		}
		case 0: { break; }
		}
		break;
	}
	case 0: { break; }
	}
}

void DeleteOnePipe(System& GasSystem)
{
	cout << "Pipes: " << endl;
	GasSystem.ViewPipes();
	cout << "Choose pipe to delete: ";
	auto keys = GasSystem.GetIDs(System::pipe);
	int number = GetCorrectNumber<int>(1, INT_MAX);
	if (!keys.contains(number)) { cout << "No such ID!" << endl; return; }
	unordered_set<int> key = { number };
	GasSystem.DeletePipes(key);
}

void DeleteOneStation(System& GasSystem) {
	cout << "Stations: " << endl;
	GasSystem.ViewStations();
	cout << "Choose station to delete: ";
	auto keys = GasSystem.GetIDs(System::station);
	int number = GetCorrectNumber<int>(1, INT_MAX);
	if (!keys.contains(number)) { cout << "No such ID!" << endl; return; }
	unordered_set<int> key = { number };
	GasSystem.DeleteStations(key);
}

void Delete_Pipes(System& GasSystem)
{
	if (!GasSystem.HasObject(System::pipe)) { cout << "No pipes!" << endl; return; }

	cout << "1. Delete one pipe" << endl
		<< "2. Delete by filter" << endl
		<< "0. Back" << endl;

	switch (GetCorrectNumber(0, 2))
	{
	case 1: { DeleteOnePipe(GasSystem); break; }
	case 2: {
		cout << "Choose:" << endl
			<< "1. Find by name" << endl
			<< "2. Find by parametr" << endl
			<< "0. Back" << endl;

		switch (GetCorrectNumber(0, 2))
		{
		case 1:
		{
			GasSystem.Delete_ByName(System::pipe);
			break;
		}
		case 2:
		{
			GasSystem.Delete_ByParametr(System::pipe);
			break;
		}
		case 0: { break; }
		}
		break;
	}
	}

}

void Delete_Stations(System& GasSystem)
{
	if (!GasSystem.HasObject(System::station)) { cout << "No stations!" << endl; return; }

	cout << "1. Delete one station" << endl
		<< "2. Delete by filter" << endl
		<< "0. Back" << endl;

	switch (GetCorrectNumber(0, 2))
	{
	case 1: { DeleteOnePipe(GasSystem); break; }
	case 2: {
		cout << "Choose:" << endl
			<< "1. Find by name" << endl
			<< "2. Find by parametr" << endl
			<< "0. Back" << endl;

		switch (GetCorrectNumber(0, 2))
		{
		case 1: 
		{ 
			GasSystem.Delete_ByName(System::station); 
			break; 
		}
		case 2: 
		{ 
			GasSystem.Delete_ByParametr(System::station); 
			break; 
		}
		case 0: { break; }
		}
		break;
	}
	}

}


int main() {
	System system;
	redirect_stream_wrapper cerr_out(cerr);
	string time = format("{:%d_%m_%Y_%H_%M_%OS}", system_clock::now() + hours(3));
	ofstream logfile("Logs/log_" + time + ".txt");

	if (logfile) cerr_out.redirect(logfile);
	while (true)
	{
		cout << "0. Exit" << endl
			<< "1. Add a pipe" << endl
			<< "2. Add a compressor station" << endl
			<< "3. Watch all objects" << endl
			<< "4. Edit" << endl
			<< "5. Save" << endl
			<< "6. Download from file" << endl
			<< "7. Remove" << endl
			<< "8. Graph" << endl;

		switch (GetCorrectNumber(0, 8)) {
		case 0:
			exit(0);
		case 1:
			system.add_p();
			break;
		case 2:
			system.add_CS();
			break;
		case 3:
			system.Watch_All(system);
			break;
		case 4:
			cout << "1. Edit pipes" << endl
				<< "2. Edit stations" << endl
				<< "0. Back" << endl;

			switch (GetCorrectNumber(0, 2))
			{
				case 1: { Edit_Pipes(system); break; }
				case 2: { Edit_Stations(system); break; }
				case 0: { break;}
			}
			break;
		case 5:
			system.Save();
			break;
		case 6:
			system.Download();
			break;
		case 7:
			cout << "1. Remove pipes" << endl
				<< "2. Remove stations" << endl
				<< "0. Back" << endl;

			switch (GetCorrectNumber(0, 2))
			{
			case 1: { Delete_Pipes(system); break; }
			case 2: { Delete_Stations(system); break; }
			case 0: { break; }
			}
			break;
		case 8:
			cout << "1. View connections" << endl
				<< "2. Create connection" << endl
				<< "3. Delete connection" << endl
				<< "4. Topological sort" << endl
				<< "5. Shortest path" << endl
				<< "6. Algorithm Ford-Falkerson" << endl
				<< "0. Back" << endl;

			switch (GetCorrectNumber(0, 6)) {
			case 1: { system.ViewConnections(); break; }
			case 2: { system.CreateConnection(); break; }
			case 3: { system.DeleteConnection(); break; }
			case 4: { system.TopologicalSort(); break; }
			case 5: { system.ShortestPath(); break; }
			case 6: { system.MaxFlow(); break; }
			case 0: { break; }
			}
			break;
		default:
			cout << "You enter incorrect data, please try again" << endl;
		}
	}
	return 0;
}