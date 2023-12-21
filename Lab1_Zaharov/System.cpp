#include "System.h"
#include "Utilities.h"
#include "Graph.h"
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

bool CheckByDiametr(Pipe& pipe, int diameter) {
    return pipe.GetDiametr() == diameter;
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
        file << pipes.size() << " " << stations.size() << " " << connections.edges.size() << endl;
        for (auto& pipe : pipes) { file << pipe.second; }
        for (auto& station : stations) { file << station.second; };
        file << connections;
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
        cout << count << ". " << name.path().filename() << endl;
    }

    cout << "Choose the file" << endl;
    int save = GetCorrectNumber(1, count);

    pipes.clear();
    stations.clear();
    connections.Clear();
    Pipe pipe;
    Station station;
    Edge edge;
    int count_pipes, count_cs, count_connectios;

    file.open(names[save - 1]);
    file >> count_pipes >> count_cs >> count_connectios;

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
    while (count_connectios--)
    {
        file >> edge;
        connections.Insert(edge);
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

//-------------------------For graph------------------//
void System::ViewConnections() {
    connections.ViewConnections();
}

int System::InputExistIdStation() {
    int id;
    do {
        id = GetCorrectNumber(1001, Station::GetMaxId());
        if (!stations.contains(id)) { cout << "No connections available!" << endl; }
    } while (!stations.contains(id));
    return id;
}

unordered_set<int> System::GetFreePipes(const unordered_set<int>& IDs) {
    unordered_set<int> free_IDs;
    for (auto& id : IDs) {
        if (!connections.edges.contains(id)) {
            free_IDs.insert(id);
        }
    }
    return free_IDs;
}

void System::CreateStateDiametrPipe(Pipe& pipe, int diameter) {
    pipe.WriteInfo_WithStateDiametr(diameter);
    pipes.insert({ pipe.GetId(), pipe });
}

void System::CreateConnection() {
    if (stations.size() < 2) { cout << "There are not enough stations to create a connection!" << endl; return; }
    ViewStations();
    cout << "Enter the ID of the starting station: " << endl;
    int from, to, id;
    from = InputExistIdStation();
    cout << "Enter the terminal station ID: " << endl;
    to = InputExistIdStation();

    if (connections.UncorrectNodes(from, to)) { return; }

    cout << "Enter the diameter of the pipe you want to connect the stations with: " << endl;
    vector<int> sizes = Pipe::GetSizes();
    int diameter = SwitchNumber(sizes);
    unordered_set<int> result = Find_By_Filter<Pipe, int>(pipes, CheckByDiametr, diameter);
    result = GetFreePipes(result);

    if (!result.size()) {
        cout << "No pipes with the specified diameter were found. Do you want to create such a pipe?(0 - no(exit), 1 - yes)" << endl;
        if (!GetCorrectNumber(0, 1)) { return; }
        else {
            Pipe pipe;
            CreateStateDiametrPipe(pipe, diameter);
            id = pipe.GetId();
            connections.CreateConnection(from, to, id);
            return;
        }
    }

    ViewObjects(result, pipe);
    cout << "Select the pipe ID for communication: ";
    do {
        id = GetCorrectNumber(1, Pipe::GetMaxId());
        if (!result.contains(id)) { cout << "There is no such ID among the pipes found! Enter it again." << endl; }
    } while (!result.contains(id));

    connections.CreateConnection(from, to, id);
    return;
}

void System::DeleteConnection() {
    if (connections.Empty()) {
        cout << "No connections available!";
        return;
    }

    connections.ViewConnections();
    cout << "Enter the ID of the connection to be deleted: " << endl;
    int id;
    do {
        id = GetCorrectNumber(1, Pipe::GetMaxId());
        if (!connections.edges.contains(id)) { cout << "There is no such ID among the pipes found! Enter it again." << endl; }
    } while (!connections.edges.contains(id));
    connections.DeleteConnection_ByPipeID(id);
}


void System::TopologicalSort() {
    if (connections.Empty()) { cout << "No connections available!"; return; }
    Graph graph = Graph(connections.edges, connections.nodes, pipes);
    vector<int> result = graph.TopologicalSort();
    if (!result.size()) { cout << "Topological sort: - "; return; }
    cout << "Topological sorting: ";
    for (auto& i : result) {
        cout << i << " ";
    }
    cout << endl;
}

void System::ShortestPath() {
    if (connections.Empty()) { cout << "No connections available!"; return; }
    Graph graph = Graph(connections.edges, connections.nodes, pipes);

    connections.ViewConnections();
    cout << "Enter the starting vertex of the path: " << endl;
    int StartNode = GetCorrectNumber(1001, Station::GetMaxId());

    cout << "Enter the final vertex of the path: " << endl;
    int EndNode = GetCorrectNumber(1001, Station::GetMaxId());

    vector<int> result = graph.Metod_Deikstra(StartNode, EndNode);
    if (!result.size()) { cout << "Path: - "; return; }
    cout << "Path: ";
    for (auto& i : result) {
        cout << i << " -> ";
    }
    cout << "end" << endl;
    cout << "Path length: " << graph.Lenght_ShortestPath(result) << endl;
}

void System::MaxFlow() {
    if (connections.Empty()) { cout << "No connections available!"; return; }
    Graph graph = Graph(connections.edges, connections.nodes, pipes);

    connections.ViewConnections();
    cout << "Enter the starting vertex of the path: " << endl;
    int StartNode = GetCorrectNumber(1001, Station::GetMaxId());

    cout << "Enter the final vertex of the path: " << endl;
    int EndNode = GetCorrectNumber(1001, Station::GetMaxId());

    double result = graph.Ford_Fulkerson(StartNode, EndNode);
    cout << "Maximum flow: " << result << endl;
}