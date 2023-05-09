Name: Phillip Graham
Start Time: March, 05, 2023 @ 5:30
Last Updated: May, 08, 2023

DESCRIPTION:
	
	This file contains my implementation of a neural network. For this neural networ, I did not choose to go with any specific kind of network.
	Originally, I intended to make a basic feed forward artificial network, but after considering training, I decided that a sort of spiking neural
	network would be more interesting. However, my network does take on the struucture of a fully connected, feed-foward artificial neural network.
	Each network begins and ends with an input and output layer. Imbetween these slices or layers, there are a number of hidden layers inserted.
	Each layer or slices contains an abitrary number of numbers specified by the user. Between every neuron in one layer and every neuron in the
	following layer, there is one "synapse". In my implementation, I do not actually create an object to represent synapses, but the term is still
	aplicable. Each neuron also contains a bias and threshold. The threshold is how I implement the spiking nature of the network. Effectively,
	each neuron will accumulate charge until it exceedes its threshold, at which point the neuron will fire by adding its current state times its weight
	to the state of every node that follows it in the network. After it fires, its state is then reset to its bias. This allows for information to
	be hardcoded into a network in a way that does not rely on the "shape" of the input. The actual process I applied when coming up with this network
	was not scientific at all. I am essentially aproaching it with the mindset that the process of randomly generating networks of this nature and
	training them by simply selecting the highest performing networks will eventually produce viable networks.

DESCRIPTION OF CODE USE:

	The code required to begin and utilize my network is rather convoluted. The first step is to compile all of the code in the directory with the
	included makefile. This makefile is formatted for windows, so you may have to edit it so that I can function for other OS. After you have compiled
	the code, The first program you should concern yourself with is the	"ffann_random_initial_sym.py" script. This script will use gennet.exe to 
	randomly generate networks following certain parameters which are set in the file gennet.cpp at the beginning of the code. Once this program has 
	run, you will be left with 10 randomly generated networks in the network directory, and 10 report files in the ffann-reports directory. It is
	very important that you have only 10 reports and 10 networks. They are indexed from 0 so you final file should be labeled with a 9. Once you
	have successfully run the first script, then you should run "prune_select_propogate.py," which is the script which will actually identify networks
	which exhibit dessireable behaviors, and attempts to carry those behaviors over to the next generation. This is done by selecting the top ten 
	performing netwroks from the last generation, and then mutating them by adding or subtracting a random number in some arbitrary range from every
	vale which is used to describe the network. Again, the process I chose to use was not scientific and based on my very limited understanding of
	how these networks actually work. "prune_select_propogate" will run 10 generations, afterwhich it will halt, leaving all of the reports and 
	networks from he final generation in the directory. The user will then have to file through the reports to identify any networks which passed. 

