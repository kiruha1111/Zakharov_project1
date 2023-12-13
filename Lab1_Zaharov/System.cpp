#include "System.h"
#include "Utilities.h"
#include <algorithm>
#include <filesystem>
using namespace std;


bool System::HasObject(const ObjectType obj)
{
    switch (obj)
    {
    case pipe: {
        if (pipes.size()) { return true; }
        else { return false; }
    }
    case station: {
        if (stations.size()) { return true; }
        else { return false; }
    }
    default: {return false; }
    }
}


//----------------------Filters--------------------------//
template <typename T1, typename T2>
using Filter = bool(*)(T1& element, T2 parametr);

template <typename T>
bool CheckByName(T& element, string name) {
    return (element.name.find(name) != string::npos);
}

bool CheckByStatus(Pipe& pipe, bool in_repair) {
    return pipe.GetRepair() == in_repair;
}

bool CheckByWorkshop(Station& station, int cent_non_active) {
    return station.GetUnactiveWorkshop() >= cent_non_active;
}

template <typename Element, typename Parametr>
unordered_set<int> Find_By_Filter(unordered_map<int, Element>& elements, Filter<Element, Parametr> filter, Parametr parametr)
{
    unordered_set<int> result;
    for (auto& element : elements)
    {
        if (filter(element.second, parametr))
            result.insert(element.second.GetId());
    }
    return result;
}

void System::ViewObjects(std::unordered_set<int> result, const System::ObjectType obj)
{
    switch (obj) {
    case pipe: { for (int id : result) { pipes.at(id).ShowInfo(); }; return; }
    case station: { for (int id : result) { stations.at(id).ShowInfo(); }; return; }
    default: { return; }
    }
}

unordered_set<int> System::GetEditNumbers(unordered_set<int>& result, const System::ObjectType obj)
{
    unordered_set<int> IDs;
    int id;
    int Max_ID;
    switch (obj) {
    case System::pipe: { Max_ID = Pipe::GetMaxId(); break; }
    case System::station: { Max_ID = Station::GetMaxId(); break; }
    }
    id = GetCorrectNumber(0, Max_ID);
    if (id == 0) { return result; }
    else { IDs.insert(id); }
    do {
        id = GetCorrectNumber(0, Max_ID);
        if (result.contains(id)) {
            IDs.insert(id);
        }
    } while (id != 0);

    return IDs;
}


//-----------------Add pipe-------------------------//
void System::add_p() {
    Pipe pipe;
    pipe.add_pipe();
    pipes.insert({ pipe.GetId(), pipe });
}


//---------------------Add CS---------------------------//
void System::add_CS()
{
    Station station;
    station.add_compressor();
    stations.insert({ station.GetId(), station });
}


//-------------------------Watch all objects-------------------------//
void System::Watch_All(System& GasSystem)
{
    if (!GasSystem.HasObject(System::pipe) && !GasSystem.HasObject(System::station)) { cout << "No objects!" << endl; return; }
    int i = 1;
    for (auto& element : pipes) {
        std::cout << i << ". ";
        i++;
        element.second.ShowInfo();
    }

    int i1 = 1;
    for (auto& element : stations) {
        std::cout << i1 << ". ";
        i1++;
        element.second.ShowInfo();
    }
}


//--------------------------------EditPipes-------------------------------------//
void System::EditPipes(unordered_set<int>& IDs)
{
    ViewObjects(IDs, pipe);
    cout << "Change the state of the pipe, 0 - set repair, 1 - set work, 2 - set opposite" << endl;
    switch (GetCorrectNumber(0, 2))
    {
        case 0: { for (int id : IDs) { pipes.at(id).Edit(Pipe::set_repair);} break;}
        case 1: { for (int id : IDs) { pipes.at(id).Edit(Pipe::set_work);} break;}
        case 2: { for (int id : IDs) { pipes.at(id).Edit(Pipe::set_opposite);} break;}
        default: { return; }
    }
    cout << endl << "Successful edit!" << endl;
}


//---------------------------------EditStations-----------------------------//
void System::EditStations(unordered_set<int>& IDs)
{
    ViewObjects(IDs, station);
    cout << "Enter the number of work workshops" << endl;
    int ans = GetCorrectNumber(0, INT_MAX);
    for (int id : IDs) { stations.at(id).Edit(ans); }
    cout << endl << "Successful edit!" << endl;
}


//-------------------------Utilities to edit------------------------------//
unordered_set<int> System::GetIDs(const ObjectType obj)
{
    switch (obj) {
    case pipe: { return GetKeys(pipes); }
    case station: { return GetKeys(stations); }
    default: { return unordered_set<int>{}; }
    }
}

void System::Edit_ByName(const ObjectType obj)
{
    switch (obj) {
    case pipe: {
        cout << "Enter a name: " << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, pipe);
            cout << "If 0, it is to all, that found. But you can enter the id through the enter, end the input with 0" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, pipe);
            EditPipes(numbers);
        }
        else cout << "No such name" << endl;
        break;
    }
    case station: {
        cout << "Enter a name: " << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Station, string>(stations, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, station);
            cout << "If 0, it is to all, that found. But you can enter the id through the enter, end the input with 0" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, station);
            EditStations(numbers);
        }
        else cout << "No such name" << endl;
        break;
    }
    default: { return; }
    }

}

void System::Edit_ByParametr(const ObjectType obj) {
    switch (obj) {
    case pipe: {
        cout << "Repair or not (0 - repair, 1 - work): " << endl;
        unordered_set<int> result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));
        if (result.size())
        {
            ViewObjects(result, pipe);
            cout << "If 0, it is to all, that found. But you can enter the id through the enter, end the input with 0" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, pipe);
            EditPipes(numbers);
        }
        else cout << "No such pipes" << endl;
        break;
    }
    case station: {
        cout << "Enter the percent of unused workshops: " << endl;
        unordered_set<int> result = Find_By_Filter<Station, int>(stations, CheckByWorkshop, GetCorrectNumber(0, 100));
        if (result.size())
        {
            ViewObjects(result, station);
            cout << "If 0, it is to all, that found. But you can enter the id through the enter, end the input with 0" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, station);
            EditStations(numbers);
        }
        else cout << "No such workshops" << endl;
        break;
    }
    default: { return; }
    }
}

//---------------------------------Delete---------------------------------//
void System::DeletePipes(unordered_set<int>& IDs) {
    for (auto& id : IDs) pipes.erase(id);
    cout << endl << "Successful delete!" << endl;
}
void System::DeleteStations(unordered_set<int>& IDs) {
    for (auto& id : IDs) stations.erase(id);
    cout << endl << "Successful delete!" << endl;
}

void System::Delete_ByName(const ObjectType obj)
{
    switch (obj) {
    case pipe: {
        cout << "Enter a name: " << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Pipe, string>(pipes, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, pipe);
            cout << "If 0, it is to all, that found. But you can enter the id through the enter, end the input with 0" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, pipe);
            DeletePipes(numbers);
        }
        else cout << "No such name" << endl;
        break;
    }
    case station: {
        cout << "Enter a name: " << endl;
        string name = input_string();
        unordered_set<int> result = Find_By_Filter<Station, string>(stations, CheckByName, name);
        if (result.size())
        {
            ViewObjects(result, station);
            cout << "If 0, it is to all, that found. But you can enter the id through the enter, end the input with 0" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, station);
            DeleteStations(numbers);
        }
        else cout << "No such name" << endl;
        break;
    }
    default: { return; }
    }

}

void System::Delete_ByParametr(const ObjectType obj) {
    switch (obj) {
    case pipe: {
        cout << "Repair or not (0 - repair, 1 - work): " << endl;
        unordered_set<int> result = Find_By_Filter<Pipe, bool>(pipes, CheckByStatus, GetCorrectNumber(0, 1));
        if (result.size())
        {
            ViewObjects(result, pipe);
            cout << "If 0, it is to all, that found. But you can enter the id through the enter, end the input with 0" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, pipe);
            DeletePipes(numbers);
        }
        else cout << "No such pipe" << endl;
        break;
    }
    case station: {
        cout << "Enter the percent of unused workshops: " << endl;
        unordered_set<int> result = Find_By_Filter<Station, int>(stations, CheckByWorkshop, GetCorrectNumber(0, 100));
        if (result.size())
        {
            ViewObjects(result, station);
            cout << "If 0, it is to all, that found. But you can enter the id through the enter, end the input with 0" << endl;
            unordered_set<int> numbers = GetEditNumbers(result, station);
            DeleteStations(numbers);
        }
        else cout << "No such station" << endl;
        break;
    }
    default: { return; }
    }
}


//---------------------------------Save-----------------------------------//
void System::Save()
{
    if (HasObject(pipe) or HasObject(station)) {
        cout << "Write name of the file to save: " << endl;
        string name = input_string();
        name = name + ".txt";

        ofstream file;
        file.open(name, ios::out);
        file << pipes.size() << " " << stations.size() << endl;
        for (auto& pipe : pipes) { file << pipe.second; }
        for (auto& station : stations) { file << station.second; };
        file.close();
        cout << "Successful save!" << endl;
    }
    else { cout << "No objects to save!" << endl; }
}


//---------------------------------Download---------------------------------//
void System::Download() {
    ifstream file;
    std::string path = "Downloads\\";
    vector<std::filesystem::directory_entry> names;
    int count = 0;
    for (auto& name : filesystem::directory_iterator(path)) {
        count++;
        names.push_back(name);
        cout << count << ". " << name << endl;
    }
    cout << "Choose the file" << endl;
    int download = GetCorrectNumber(1, count);

    pipes.clear();
    stations.clear();
    Pipe pipe;
    Station station;
    int count_pipes, count_cs;

    file.open(names[download - 1]);
    file >> count_pipes >> count_cs;

    while (count_pipes--)
    {
        file >> pipe;
        pipes.insert({ pipe.GetId(), pipe });
    }
    while (count_cs--)
    {
        file >> station;
        stations.insert({ station.GetId(), station });
    }
    cout << "Successful download!" << endl;
    file.close();
}

//-------------------View-----------------------//
void System::ViewPipes()
{
    int i = 1;
    for (auto& element : pipes) {
        std::cout << i << ". ";
        i++;
        element.second.ShowInfo();
    }
}

void System::ViewStations()
{
    int i = 1;
    for (auto& element : stations) {
        std::cout << i << ". ";
        i++;
        element.second.ShowInfo();
    }
}