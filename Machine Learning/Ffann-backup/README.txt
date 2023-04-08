Name: Phillip Graham
Start Time: March, 05, 2023 @ 5:30 pm
Last Updated: April, 08, 2023 @ 1:45 pm
Logged Time: 5hr 45min 

March, 05, 2023: Created some of the files, and started outlining the structure of my network

March, 27, 2023: Started creatign the classes that will be used for my implementation of the ffann. Researched on common implimentations of 
		 feed forward artificial neural networks.

April, 08, 2023: Finished making the code for my feed forward artificial neural network, and began some groundwork to start interfacing with
		 the script and blender.


DESCRIPTION:	This file contains my implementation of a neural network. This neural network will be a simple feed forward, fully connected,
		artificial neural network. In order to simplify and abstract the code for this network, it will be implemented using objects to
		represent the neurons and synapses contained within the network. The network will be trained using supervised learning, mostt
		likely linear regression. The outputs and inputs will give and take respectively integer values, which will correlate directly
		to the inputs and outputs taken and provided by our rocket.

DESCRIPTION OF CODE:

	My code for generating these brains will be very simple, and will be designed to be integrated with something like a script to produce many
	different and randomized varients of the network. The main file will take in command line input, and will then propt the user to describe the
	thresholds for every node in the network. After this, it will go through the very lengthy process of describing the weights of every synapse in
	the network. Once it is finished, it will output a text file describing the given network.

DESCRIPTION OF FORMAT FOR NETWORK INPUT:
	
	Every neural netwrok that is to be passed to my program must be described in one line. This line will simply be a string of integers seperated by
	space. The first three integers will be the number of inputs, the number of outputs, and the number of hidden layers in that order. After this,
	each neuron will be represented by a number represeting its threshold, and then the following numbers will represent the synapse weights to the
	post neurons in the next slice, the numbr of integers following a nodes weight will be equal to the number of neurons in the following slice, this
	is what allows the user to distinguish between synapse weights and thresholds. In my implementation the number of neurons per hidden layer is the
	sum of the number of input neurons and output neurons. 

	If we wanted to implement a simple network of four neurons with one input, one output, and one hidden layer we would pass the following string.
	Let us say that the input has a threshold of zero, the synapse to the first hidden neuron has a weight of 1, the synapse to the second hidden
	neuron has a weight of 2, the threshold of the first hidden neuron is 2, the threshold of the second hidden neuron is 3, the synapse from the first
	hidden neuron to the output has a weight of 1, the synapse from the second hidden neuron to the output has a weight of 3, and the output has a threshold
	of 4.

	1 1 1 0 1 2 2 1 3 3 4
