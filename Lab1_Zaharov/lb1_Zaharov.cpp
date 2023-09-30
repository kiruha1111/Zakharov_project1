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

void save(Pipe p, Compressor_station cs)
{
	ofstream out("save.txt");
	if (p.name_pipe == "empty" && cs.name_station == "empty")
	{
		cout << "No data!" << endl;
		cout << "Press enter to continue" << endl;
	}
	else if (p.name_pipe == "empty")
	{
		out << "Pipe: no data" << endl;
		out << "Compressor station: " << cs.name_station << " " << cs.number_workshop << " " << cs.work_workshop << " " << cs.performance << endl;
		out.close();
	}
	else if (cs.name_station == "empty")
	{
		out << "Pipe: " << p.name_pipe << " " << p.length << " " << p.diametr << " " << p.under_repair << endl;
		out << "Compressor station: no data" << endl;
		out.close();
	}
	else
	{
		out << "Pipe: " << p.name_pipe << " " << p.length << " " << p.diametr << " " << p.under_repair << endl;
		out << "Compressor station: " << cs.name_station << " " << cs.number_workshop << " " << cs.work_workshop << " " << cs.performance << endl;
		out.close();
	}
}

string split(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ':')
		{
			str.erase(0, i + 2);
			return str;
		}
	}
}

void download(Pipe& p, Compressor_station& s)
{
	ifstream file;
	string line;
	file.open("download.txt", ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line.find("Name pipe: ") != string::npos)
			{
				p.name_pipe = split(line);
			}
			else if (line.find("Length: ") != string::npos)
			{
				p.length = stod(split(line));
			}
			else if (line.find("Diametr: ") != string::npos)
			{
				p.diametr = stod(split(line));
			}
			else if (line.find("Repair: ") != string::npos)
			{
				p.under_repair  = stoi(split(line));
			}
			else if (line.find("Name station: ") != string::npos)
			{
				s.name_station = split(line);
			}
			else if (line.find("Workshops: ") != string::npos)
			{
				s.number_workshop = stoi(split(line));
			}
			else if (line.find("Work workshops: ") != string::npos)
			{
				s.work_workshop = stoi(split(line));
			}
			else if (line.find("Performance: ") != string::npos)
			{
				s.performance = stod(split(line));
			}
		}
		file.close();
		cout << "Successful download!" << endl;
		cout << "Press enter to continue" << endl;
	}
	else
	{
		cout << "Error! File not found!" << endl;
	}
}

int number_or_letter()
{
	int number;
	while (true)
	{
		cin >> number;
		if (cin.fail() || number < 0)
		{
			cout << "Please, enter a number above zero!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			return number;
		}
	}
	
}

int proverka(int nw)
{
	int ww;
	while (true)
	{
		ww = number_or_letter();
		if (nw < ww)
		{
			cout << "Work workshops more than workshops! Try again" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			return ww;
		}

	}
}

int main() {
	string buf;
	char number;
	buf.clear();
	number = *"";
	Pipe new_pipe;
	Compressor_station new_compressor;
	new_pipe.name_pipe = "empty";
	new_compressor.name_station = "empty";
	ofstream out("save.txt");

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
			new_pipe.length = number_or_letter();
			new_pipe.diametr = number_or_letter();
			new_pipe.under_repair = number_or_letter();
			break;
		case '2':
			cout << "Enter properties of a compressor station (name, number workshops, number of work workshops, perfomance:" << endl;
			cin >> new_compressor.name_station;
			new_compressor.number_workshop = number_or_letter();
			new_compressor.work_workshop = proverka(new_compressor.number_workshop);
			new_compressor.performance = number_or_letter();
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
			if (new_pipe.name_pipe == "empty")
			{
				cout << "You don't entered any pipes!" << endl;
				cout << "Press enter to continue" << endl;
				break;
			}
			else
			{
				cout << "Repair or not (0 or 1)):" << endl;
				cin >> new_pipe.under_repair;
				break;
			}		
		case '5':
			if (new_compressor.name_station == "empty")
			{
				cout << "You don't entered any stations!" << endl;
				cout << "Press enter to continue" << endl;
				break;
			}
			else
			{
				cout << "Number of work workshops:" << endl;
				cin >> new_compressor.work_workshop;
				break;
			}
			
		case '6':
			save(new_pipe, new_compressor);
			cout << "Press enter to continue" << endl;
			break;
		case '7':
			download(new_pipe, new_compressor);
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