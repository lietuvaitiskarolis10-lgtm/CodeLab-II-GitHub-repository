
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
using namespace std;
 
// read all the jokes from the file into a vector
vector<string> loadJokes()
{
    vector<string> jokes;
    ifstream file("randomJokes.txt");
    string line;
 
    if (!file.is_open())
    {
        cout << "Could not open randomJokes.txt" << endl;
        return jokes;
    }
 
    while (getline(file, line))
    {
        if (line != "")
            jokes.push_back(line);
    }
 
    file.close();
    return jokes;
}
 
// show the setup, wait for enter, then show the punchline
void tellJoke(string joke)
{
    int pos = joke.find('?');
    string setup = joke.substr(0, pos + 1);
    string punchline = joke.substr(pos + 1);
 
    cout << setup << endl;
    cout << "(press enter for the punchline)";
    string wait;
    getline(cin, wait);
    cout << punchline << endl << endl;
}
 
int main()
{
    random_device rd;
    vector<string> jokes = loadJokes();
 
    if (jokes.size() == 0)
        return 1;
 
    string input;
 
    while (true)
    {
        cout << "Say \"Alexa, tell me a joke\" or type quit: ";
        getline(cin, input);
 
        if (input == "quit" || input == "Quit")
        {
            cout << "Goodbye!" << endl;
            break;
        }
        else if (input == "Alexa, tell me a joke" || input == "alexa, tell me a joke")
        {
            int r = rd() % jokes.size();
            tellJoke(jokes[r]);
        }
        else
        {
            cout << "Sorry, I didn't understand that." << endl << endl;
        }
    }
 
    return 0;
}
 