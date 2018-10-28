#include <iostream>
#include <sstream>
#include <vector>
#include <random>

using namespace std;

struct Reader {
    // TODO hat ennel lehetne szebb is :(
    int data[3];
    vector<vector<char>> fields;
    vector<vector<string>> pacmans;
    vector<vector<string>> ghosts;

    Reader(istream& input) {
        string line;
        getline(input, line);
        stringstream(line) >> data[0] >> data[1] >> data[2];
        getline(input, line);
        
        int X, Y, pacmanCount, ghostCount;
        stringstream second(line);
        second >> X >> Y >> pacmanCount >> ghostCount;
        if (getline(second, line))
            cerr << "\nGot message:" << line << endl;
            
        fields.resize(X, vector<char>(Y));
        for (auto& fieldLine : fields) {
            getline(input, line);
            copy(line.begin(), line.begin() + Y, fieldLine.begin());
        }
        
        pacmans.resize(pacmanCount);
        for (auto& pacman : pacmans) {
            getline(input, line);
            stringstream ss(line);
            while(getline(ss, line, ' '))
                pacman.push_back(line);
        }

        ghosts.resize(ghostCount);
        for (auto& ghost : ghosts) {
            getline(input, line);
            stringstream ss(line);
            while(getline(ss, line, ' '))
                ghost.push_back(line);
        }
    }
};

string possibles = "v<>^";

int main(int argc, char** argv) {
    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> distribution(0,possibles.size()-1);

    while (true) {
        Reader reader(cin);
        
        if (reader.data[2] == -1)
            break;
        
        // TODO logika jobb mint a random
        char dir = possibles[distribution(generator)];
        
        // Ha szeretnetek debug uzenetet kuldeni, akkor megtehetitek.
        // Vigyazzatok, mert maximalisan csak 1024 * 1024 bajtot kaptok vissza
        cerr << dir;
        
        // standard out-ra meg mehet ki a megoldas! Mas ne irodjon ide ki ;)
        cout << reader.data[0] << " " << reader.data[1] << " " 
            << reader.data[2] << " " << dir << endl;
    }
}