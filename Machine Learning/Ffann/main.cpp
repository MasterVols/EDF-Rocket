// main.cpp
// Contributor: Phillip Graham
// Start Time: March 05, 2023
// Last Edited: April, 25, 2023

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
		ffann(int,int,int,int,string);
        ffann(*ifstream);
		vector<float> evaluate_network(vector<float>);
		void print_network ();
		vector<vector<float>> states;
		vector<vector<float>> thresholds;
		vector<vector<vector<float>>> weights;
		int num_input;
		int num_output;
		int num_hidden_layer;
        int num_per_hidden;
		int num_neurons;
};

bool handle_io (ffann*,bool);

const bool script_mode = true;

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
        
		string network_description;
		int num_inputs;
		int num_outputs;
		int num_hidden;
        int num_per_hidden;
		input_file >> num_inputs >> num_outputs >> num_hidden >> num_per_hidden;
        getline(input_file,network_description);
        
		ffann network (num_inputs,num_outputs,num_hidden,num_per_hidden,network_description);
        handle_io(&network, true);
	}
	else if (argc == 1)
	{
		string network_description;
		cout << "Enter the network description in one line: ";
		int num_inputs;
		int num_outputs;
		int num_hidden;
        int num_per_hidden;
		cin >> num_inputs >> num_outputs >> num_hidden >> num_per_hidden;
		getline(cin,network_description);
		ffann network (num_inputs,num_outputs,num_hidden,num_per_hidden,network_description);
		handle_io(&network, false);
	}
	else
	{
		cout << "ERROR: Faulty input, takes either one or no additional command line arguments\n";
		return 1;
	}

}

ffann::ffann (int num_input_param,int num_output_param,int num_hidden_layer_param,int num_per_hidden, string network_param)
{
    this->num_input = num_input_param;
	this->num_output = num_output_param;
    this->num_hidden_layer = num_hidden_layer_param;
    this->num_per_hidden = num_per_hidden;
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
            post_per_node = num_per_hidden;
        }
        else if (i < num_hidden_layer + 1)
        {
            slice_height = num_per_hidden;
            if (i == num_hidden_layer) post_per_node = num_output;
            else post_per_node = num_per_hidden;
        }
        else
        {
            slice_height = num_output;
            post_per_node = 0;
        }

        thresholds[i].resize(slice_height,0.0);
        states[i].resize(slice_height,0.0);
        weights[i].resize(slice_height);
        for (int j = 0; j < slice_height; j++)
        {
            weights[i][j].resize(post_per_node,0.0);
        }
        

        for (int j = 0; j < slice_height; j++)
        {
            float thresh_val;
            istr >> thresh_val;
            thresholds[i][j] = thresh_val;
            for (int k = 0; k < post_per_node; k++)
            {
                float weight_val;
                istr >> weight_val;
                weights[i][j][k] = weight_val;
            }
        }
    }
}

vector <float> ffann::evaluate_network(vector<float> inp_param)
{
    vector <float> out_vect;
    
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
        if ((unsigned)i != states.size() - 1) cout << "\n";
    }
}

bool handle_io (ffann* net_ptr, bool script_run)
{
    bool con_loop = true;
    while (con_loop)
		{
			if (script_run) 
            {
                net_ptr->print_network();
			    cout << endl;
			    cout << "Enter Input: ";
            }
			string input;
			getline(cin, input);
			if (input == "end" || input == "END" || input == "stop")
			{
				con_loop = false;
				break;
			}
			vector <float> inp_vec;
			istringstream istr;
			istr.str(input);
			float pass_flt;
			while (istr >> pass_flt)
			{
				inp_vec.push_back(pass_flt);
			}
			if (inp_vec.size() < (unsigned)net_ptr->num_input)
			{
				cout << "ERROR: Expected " << net_ptr->num_input << " number of integers\n";
                con_loop = false;
				continue;
			}
			else
			{
				vector <float> oup_vec = net_ptr->evaluate_network(inp_vec);
				if (!script_run) cout << "Output: ";
				for (size_t i = 0; i < oup_vec.size(); i++)
				{
					cout << oup_vec[i] << " ";
				}
				cout << endl;
			}
		}
    return true;
}