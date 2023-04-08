// main.cpp
// Contributor: Phillip Graham
// Start Time: March 05, 2023
// Last Edited: April, 08, 2023
// Logged Time: 0:05

#include "ffann.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main (int argc, char* argv[])
{
	if (argc == 2)
	{
		ifstream input_file (argv[1]);
		if (!input_file.is_open())
		{
			cout << "ERROR: Could not open file: " << argv[1] << endl;
			return 1;
		}

		string line;
		vector <ffann*> network_vector;
		while (getline(input_file,line))
		{
			istringstream istr;
			istr.str(line);
			int num_inputs;
			int num_outputs;
			int num_hidden;
			istr >> num_inputs >> num_outputs >> num_hidden;
			ffann* net_ptr = new ffann (num_inputs,num_outputs,num_hidden,istr.str());
			network_vector.push_back(net_ptr);
		}

	}
	else if (argc == 1)
	{
		string network_description;
		cout << "Enter the network description in one line: ";
		getline(cin,network_description);
		istringstream istr;
		istr.str(network_description);
		int num_inputs;
		int num_outputs;
		int num_hidden;
		istr >> num_inputs >> num_outputs >> num_hidden;
		ffann network (num_inputs,num_outputs,num_hidden,istr.str());
		bool con_loop = true;
		while (con_loop)
		{
			cout << "Enter Input: ";
			string input;
			getline(cin, input);
			if (input == "end" || input == "END" || input == "stop")
			{
				con_loop = false;
				break;
			}
			vector <int> inp_vec;
			istringstream istr;
			istr.str(input);
			int pass_int;
			while (istr >> pass_int)
			{
				inp_vec.push_back(pass_int);
			}
			if (inp_vec.size() < num_inputs)
			{
				cout << "ERROR: Expected " << num_inputs << " number of integers\n";
				continue;
			}
			else
			{
				vector <int> oup_vec = network.evaluate_network(inp_vec);
				cout << "Output: ";
				for (size_t i = 0; i < oup_vec.size(); i++)
				{
					cout << oup_vec[i] << " ";
				}
				cout << endl;
			}
		}
	}
	else
	{
		cout << "ERROR: Faulty input, takes either one or no additional command line arguments\n";
		return 1;
	}
	// TODO: create the main
}
