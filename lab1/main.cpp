#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Pipe
{
	string name_pipe;
	double length;
	double diametr;
	bool under_repair;
};

struct Compressor_station
{
	string name_station;
	int number_workshop;
	int work_workshop;
	int performance;
};

int main() {
	string buf;
	char number;
	buf.clear();
	number = *"";
	Pipe new_pipe;
	Compressor_station new_compressor;
	new_pipe.name_pipe = "empty";
	new_compressor.name_station = "empty";
	ofstream out;// поток для записи

	while (true)
	{
		cin.ignore(10000, '\n');
		cout << "1. Add a pipe" << endl
			<< "2. Add a compressor station" << endl
			<< "3. Watch all objects" << endl
			<< "4. Edit a pipe" << endl
			<< "5. Edit a compressor station" << endl
			<< "6. Save" << endl
			<< "7. Download from file" << endl
			<< "8. Exit" << endl;
		getline(cin, buf);
		if (buf.length() == 1)
		{
			number = buf[0];
		}
		else
		{
			cout << "You enter incorrect data, please try again" << endl;
			continue;
		}

		switch (number)
		{
		case '1':
			cout << "Enter properties of a pipe (name, length, diametr and repair or not (0 or 1)):" << endl;
			cin >> new_pipe.name_pipe;
			cin >> new_pipe.length;
			cin >> new_pipe.diametr;
			cin >> new_pipe.under_repair;
			break;
		case '2':
			cout << "Enter properties of a compressor station (name, number workshops, number of work workshops, perfomance:" << endl;
			cin >> new_compressor.name_station;
			cin >> new_compressor.number_workshop;
			cin >> new_compressor.work_workshop;
			cin >> new_compressor.performance;
			break;
		case '3':
			if (new_pipe.name_pipe == "empty" && new_compressor.name_station == "empty")
			{
				cout << "All objects:" << endl;
				cout << "You have not entered the pipe data" << endl;
				cout << "You have not entered the compressor station data" << endl;
				cout << "Press enter to continue" << endl;
				break;
			}
			else if (new_pipe.name_pipe == "empty")
			{
				cout << "All objects:" << endl;
				cout << "You have not entered the pipe data" << endl;
				cout << "Compressor station: " << new_compressor.name_station << " " << new_compressor.number_workshop << " " << new_compressor.work_workshop << " " << new_compressor.performance << endl;
				cout << "Press enter to continue" << endl;
				break;
			}
			else if (new_compressor.name_station == "empty")
			{
				cout << "All objects:" << endl;
				cout << "Pipe: " << new_pipe.name_pipe << " " << new_pipe.length << " " << new_pipe.diametr << " " << new_pipe.under_repair << endl;
				cout << "You have not entered the compressor station data" << endl;
				cout << "Press enter to continue" << endl;
				break;
			}
			else
			{
				cout << "All objects:" << endl;
				cout << "Pipe: " << new_pipe.name_pipe << " " << new_pipe.length << " " << new_pipe.diametr << " " << new_pipe.under_repair << endl;
				cout << "Compressor station: " << new_compressor.name_station << " " << new_compressor.number_workshop << " " << new_compressor.work_workshop << " " << new_compressor.performance << endl;
				cout << "Press enter to continue" << endl;
				break;
			}
		case '4':
			cout << "Repair or not (0 or 1)):" << endl;
			cin >> new_pipe.under_repair;
			break;
		case '5':
			cout << "Number of work workshops:" << endl;
			cin >> new_compressor.work_workshop;
			break;
		case '6':
			out.open("save.txt");// открываем файл для записи
			if (out.is_open())
			{
				if (new_pipe.name_pipe == "empty" && new_compressor.name_station == "empty")
				{
					out << "Pipe: no data" << endl;
					out << "Compressor station: no data" << endl;
					cout << "Successful save!" << endl;
					cout << "Press enter to continue" << endl;
					out.close();
					break;
				}
				else if (new_pipe.name_pipe == "empty")
				{
					out << "Pipe: no data" << endl;
					out << "Compressor station: " << new_compressor.name_station << " " << new_compressor.number_workshop << " " << new_compressor.work_workshop << " " << new_compressor.performance << endl;
					cout << "Successful save!" << endl;
					cout << "Press enter to continue" << endl;
					out.close();
					break;
				}
				else if (new_compressor.name_station == "empty")
				{
					out << "Pipe: " << new_pipe.name_pipe << " " << new_pipe.length << " " << new_pipe.diametr << " " << new_pipe.under_repair << endl;
					out << "Compressor station: no data" << endl;
					cout << "Successful save!" << endl;
					cout << "Press enter to continue" << endl;
					out.close();
					break;
				}
				else
				{
					out << "Pipe: " << new_pipe.name_pipe << " " << new_pipe.length << " " << new_pipe.diametr << " " << new_pipe.under_repair << endl;
					out << "Compressor station: " << new_compressor.name_station << " " << new_compressor.number_workshop << " " << new_compressor.work_workshop << " " << new_compressor.performance << endl;
					cout << "Successful save!" << endl;
					cout << "Press enter to continue" << endl;
					out.close();
					break;
				}
			}
		case '7':
			cout << "Number of work workshops:" << endl;
			cin >> new_compressor.work_workshop;
			break;
		case '8':
			exit(0);
			break;
		default:
			cout << "You enter incorrect data, please try again" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		buf = "";
		number = *"";
		cin.clear();
		
	}
	return 0;
}