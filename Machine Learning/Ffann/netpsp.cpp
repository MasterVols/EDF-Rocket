// netpsp.cpp
// Contributor: Phillip Graham
// Created: 05/03/2023

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <random>
using namespace std;
namespace fs = std::filesystem;
float ranf(float min,float max);

const bool DEBUG = false;

int main ()
{
    fs::path directory_path = "C:\\Users\\reed2\\OneDrive\\Desktop\\Github Repos\\EDF-Rocket\\Machine Learning\\Ffann\\ffann-reports";
    multimap <int,int> sortmap;
    for (const auto& entry : fs::directory_iterator(directory_path))
    {
        if (entry.is_regular_file())
        {
            ifstream file(entry.path());
            if (!file)
            {
                cout << "ERROR: Could not open file: " << entry.path() << endl;
                continue;
            }
            else if (DEBUG) cout << "OPENED: " << entry.path() << endl;

            string last_line;
            for (string line; getline(file,line);) last_line = line;
             
            istringstream str;
            str.str(last_line);
            string trash;
            str >> trash;
            int score;
            while (str >> score);
            if (DEBUG) cout << "FILE: " << entry.path().filename() << " had a score " << score << endl;
            ostringstream ostr;
            ostr << entry.path().filename();
            string filename = ostr.str();
            int fd = filename.find_first_of("0123456789");
            int ld = filename.find_last_of("0123456789");
            string numstr = filename.substr(fd,ld - fd + 1);
            str.clear();
            str.str(numstr);
            int filenum;
            filenum = stoi(str.str());
            if (DEBUG) cout << "FILENUM: " << filenum << endl;
            sortmap.insert(make_pair(-score,filenum));
            file.close();
            fs::remove(entry.path());
        }
    }

    vector <vector<float>> pnets;
    int pnetindex = 0;
    pnets.resize(10);
    // Now that I have my files sorted by score in the map, delete all but the highest scoring, and store the high scoring in vectors
    directory_path = "C:\\Users\\reed2\\OneDrive\\Desktop\\Github Repos\\EDF-Rocket\\Machine Learning\\Ffann\\networks";
    for (const auto& entry : fs::directory_iterator(directory_path))
    {
        ostringstream ostr;
        istringstream istr;
        ostr << entry.path().filename();
        string filename = ostr.str();
        int fd = filename.find_first_of("0123456789");
        int ld = filename.find_last_of("0123456789");
        string numstr = filename.substr(fd,ld - fd + 1);
        istr.clear();
        istr.str(numstr);
        int filenum;
        filenum = stoi(istr.str());

        bool not_pass = true;
        auto itr = sortmap.begin();
        for (unsigned int i = 0; i < 10; i++)
        {
            if (DEBUG) cout << "Itr second " << itr->second << endl;
            if (itr->second == filenum)
            {
                not_pass = false;
                break;
            }
            itr++;
        }
        if (not_pass)
        {
            if (DEBUG) cout << "Report number " << filenum << " did not pass. Deleting..." << endl;
            // add delete
            continue;
        }
        ifstream file(entry.path());
        int pass_int;
        float pass_float = 0;
        for (int i = 0; i < 4; i ++)
        {
            file >> pass_int;
            pnets[pnetindex].push_back(pass_int);
        }
        while (file >> pass_float)
        {
            pnets[pnetindex].push_back(pass_float);
            pass_float = 0;
        }
        file.close();
        if (DEBUG) cout << "Report number " << filenum << " passed. Deleting...\n";
        fs::remove(entry.path());
        pnetindex++;
    }

    // Now generate a file for the new networks
    for (unsigned int i = 0; i < pnets.size(); i++)
    {
        // Do it ten times for each good network
        for (int j = 0; j < 10; j++)
        {
            string new_file_name = "network";
            istringstream ostr;
            int number = i * 10 + j;
            new_file_name += to_string(number) + ".txt";
            if (DEBUG) cout << "Creating new file: " << new_file_name << endl; 

            ofstream outfile("C:\\Users\\reed2\\OneDrive\\Desktop\\Github Repos\\EDF-Rocket\\Machine Learning\\Ffann\\networks\\"+new_file_name);
            unsigned int k = 0;
            outfile << ((int)pnets[i][0]);
            k++;
            for (k = k; k < 4; k++)
            {
                outfile << " " << ((int)pnets[i][k]);
            }
            for (k = k; k < pnets[i].size(); k++)
            {
                float val = pnets[i][k] + ranf(-0.2,0.2);
                if (val > 1) val = 1;
                if (val < -1) val = -1;
                outfile << " " << val;
            }
            outfile.clear();
        }
    }
    ofstream file ("repnum.txt");
    file << "0";
    file.close();
    return 0;
}

float ranf(float min,float max)
{
    mt19937 gen(random_device{}());
    uniform_real_distribution<float> distr(min,max);
    return distr(gen);
}