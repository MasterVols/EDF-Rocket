Name: Phillip Graham
Start Time: March, 05, 2023 @ 5:30 pm
Last Updated: March, 27, 2023 @ 11:20 pm
Logged Time: 5hr 45min 

March, 05, 2023: Created some of the files, and started outlining the structure of my network

March, 27, 2023: Started creatign the classes that will be used for my implementation of the ffann. Researched on common implimentations of 
		 feed forward artificial neural networks.


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
