// main.cpp
// Contributor: Phillip Graham
// Start Time: March 05, 2023
// Last Edited: April, 08, 2023
// Logged Time: 0:05

using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string> 

//using namespace std;

class ffann
{
	public:
		ffann(int,int,int,string);
		vector<int> evaluate_network(vector<int>);
		void print_network ();
	private:
		vector<vector<int>> states;
		vector<vector<int>> thresholds;
		vector<vector<vector<int>>> weights;
		int num_input;
		int num_output;
		int num_hidden_layer;
		int num_neurons;
};


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
		int num_inputs;
		int num_outputs;
		int num_hidden;
		cin >> num_inputs >> num_outputs >> num_hidden;
		getline(cin,network_description);
		ffann network (num_inputs,num_outputs,num_hidden,network_description);
		bool con_loop = true;
		while (con_loop)
		{
			network.print_network();
			cout << endl;
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

ffann::ffann (int num_input_param,int num_output_param,int num_hidden_layer_param,string network_param)
{
    num_input = num_input_param;
	num_output = num_output_param;
    num_hidden_layer = num_hidden_layer_param;
    num_neurons = num_input + num_output + (num_input + num_output) * num_hidden_layer_param;
    states.resize(2+num_hidden_layer);
    weights.resize(2+num_hidden_layer);
    thresholds.resize(2+num_hidden_layer);

    istringstream istr (network_param);
    for (int i = 0; i < (2 + num_hidden_layer); i++)
    {
        int slice_height;
        int post_per_node;

        if (i == 0)
        {
            slice_height = num_input;
            post_per_node = num_input + num_output;
        }
        else if (i < num_hidden_layer + 1)
        {
            slice_height = num_input + num_output;
            if (i == num_hidden_layer) post_per_node = num_output;
            else post_per_node = num_output + num_input;
        }
        else
        {
            slice_height = num_output;
            post_per_node = 0;
        }

        thresholds[i].resize(slice_height,0);
        states[i].resize(slice_height,0);
        weights[i].resize(slice_height);
        for (int j = 0; j < slice_height; j++)
        {
            weights[i][j].resize(post_per_node,0);
        }
        

        for (int j = 0; j < slice_height; j++)
        {
            int thresh_val;
            istr >> thresh_val;
            thresholds[i][j] = thresh_val;
            for (int k = 0; k < post_per_node; k++)
            {
                int weight_val;
                istr >> weight_val;
                weights[i][j][k] = weight_val;
            }
        }
    }
}

vector <int> ffann::evaluate_network(vector<int> inp_param)
{
    vector <int> out_vect;
    
    for (int i = 0; i < num_input; i++)
    {
        states[0][i] = inp_param[i];
    }
    
    // Propigate the signals
    for (unsigned int i = 0; i < states.size() - 1; i++)
    {
        for (unsigned int j = 0; j < states[i].size(); j++)
        {
            if (states[i][j] >= thresholds[i][j])
            {
                for (unsigned int k = 0; k < weights[i][j].size(); k++)
                {
                    states[i+1][k] += states[i][j] * weights[i][j][k];
                }
            }
        }
        for (unsigned int j = 0; j < states[i].size(); j++)
        {
            states[i][j] = 0;
        }
    }
    
    for (int i = 0; i < num_output; i++)
    {
        out_vect.push_back(states[num_hidden_layer + 1][i]);
        states[num_hidden_layer + 1][i] = 0;
    }
    
    

    return out_vect;
}

void ffann::print_network()
{
    for (int i = 0; i < num_hidden_layer + 2; i++)
    {
        for (unsigned int j = 0; j < states[i].size(); j++)
        {
            cout << "S=" << states[i][j] << " T=" << thresholds[i][j];
            for (unsigned int k = 0; k < weights[i][j].size();k++)
            {
                cout << " W=" << weights[i][j][k];
            }
            if (j != states[i].size() - 1) cout << "___";
        }
        if (i != states.size() - 1) cout << "\n";
    }
}