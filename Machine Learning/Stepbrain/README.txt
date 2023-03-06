Name: Phillip Graham
Start Time: March, 05, 2023 @ 5:30 pm

DESCRIPTION:	This file contains my implementation of a neural network. This neural network will be a semi-fully-connected feedfoward neural network.
			This means that there wont be much complicated structures to be used. The neural network will be implemented using and adjacency
			list and a list of layers. Each layer will contain a certain number of special neurons which will be what we will call the
			input-direct-descendant nodes. Each of these will only ever have one ancestor node, that being the original input to the network.
			Each layer will also have mixed-descendant nodes. Each of these will have every other node in the last layer of the network as their
			parent nodes. Each subsequent layer in the network, except for the output layer, will have one more neuron than the last layer.
			
			Each synaps will be assigned a weight, and each node will have a threshold its inputs must reach before it will fire. The oytputs will be
			configurable to eiher output an integer value or a value determined base on their threshold. Similarily, the input nodes will be
			configurable to either take fire when a threshold is reached for a give integer value, or they will fire given that they have any input.
GRAPHIC:

	I: represents input-direct-descendant-nodes 
	H: represents nodes connect to all nodes in prior layer
	O: represents outputs connected to all nodes in the prior layer

	For a system of three inputs and three outputs.


			     |>  H -> |				
	                 |        |
                |>  H  |>  H -> |
		    |      |        |
	   |>  H  |>  H  |>  H -> |
	   |	    |	     |	  |
	I  ->  I  ->  I  ->  I -> |--> O
                                | 
	I  ->  I  ->  I  ->  I -> |--> O
                                |
	I  ->  I  ->  I  ->  I -> |--> O


DESCRIPTION OF CODE:

	My code for generating these brains will be very simple, and will be designed to be integrated with something like a script to produce many different and randomized varients of the network.
	The main file will take in command line input, and will then propt the user to describe the thresholds for every node in the network. After this, it will go through the very lengthy process of
	describing the weights of every synapse in the network. Once it is finished, it will output a text file describing the given network. This file will then be used in a later program to do things
	such as evolutionary training etc. 