#include "Bacteria.h"
#include "Lineage.h"
#include "Plot.h"
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>

using namespace std;

Bacteria::Bacteria( unsigned int pop0, unsigned int generations, unsigned int cap )
{

	this->plot = Plot::CreateInstance();

	this->cap = cap;
	this->generations = generations;
	
	this->initialize( pop0 );
	this->generate();

	if ( debug ) printf("Number of lineages: %d\n", get_number());
	if ( debug ) printf("Population size: %d\n", get_pop());

}

Bacteria::~Bacteria()
{

}

//create initial deque of pop0 lineages, kill portion of these
void Bacteria::initialize(int pop0)
{

	pops.resize(generations+1); pops[0] = pop0;
	for (int i = 0; i < (int)pop0; i++)
		bacteria.push_back( new Lineage() );
	this->remove();

}


//tell each lineage to create a new generation up through the maximum given (generations)
//after each generation is created, kill a portion of these
void Bacteria::generate()
{

	for (int i = 0; i < (int)generations; i++)
	{

		reproduce(i);
		this->remove();
		//bacteria[i]->add_babies();
		
	}

}

//call each lineage within the deque and tell it to divide 
//get the population after each generation and put it in pops so growth can be plotted over time
void Bacteria::reproduce(int gen)
{
	double birthProb = 1*.5;//1 - (double)this->get_pop()/(double)this->cap;
	printf("birth probability = %f\n", birthProb);
	for (int j = 0; j < (int)bacteria.size(); j++)
	{

		if (debug) printf("Dividing in lineage %d\n",j);
		bacteria[j]->divide(birthProb);

		pops[gen+1] = get_pop();
		printf("Population = %d\n", pops[gen + 1]);
		if ( debug ) printf("Population = %d\n", get_pop());

	}			

}

//return vector of population values after each generation 
void Bacteria::get_pop_vector( vector<int> &pops )
{

	pops = this->pops;		
}

//return total number of lineages in the deque bacteria
int Bacteria::get_number()
{

	return (int)bacteria.size();

}

//return total number of bacterium in all lineages within bacteria
int Bacteria::get_pop()
{

	int pop = 0;
	for (int i=0;i < (int)bacteria.size();i++)
	{
		pop += bacteria[i]->get_size();	
	}
	return pop;

}

//calls remove on deque bacteria 
void Bacteria::remove()
{

	if ( debug ) printf("Removing within %d lineages\n", this->get_number());
	double death_prob = (1*(double)this->get_pop())/(double)(this->cap + this->get_pop());
	printf("death probability = %f\n", death_prob);
	//Tell every lineage to randomly erase bacteria
	for (int i = 0; i < this->get_number(); i++)
	{

		if ( debug ) printf("removing within lineage %d\n", i); 
		bacteria[i]->random(death_prob);

	}	

	//Take out lineages that have no more bacterium in them
	int size = bacteria.size();
	deque<int> temp;
	
	for (int i = 0; i < size; i++)
	{

		if ( debug ) printf("Size of lineage %d = %d\n", i, bacteria[i]->get_size());
	
		//add indices of empty lineages to deque temp	
		if ( bacteria[i]->get_size() == 0 )
			temp.push_back(i);		

	}

	//erase empty lineages from index values in temp
	int tsize = temp.size();
	for ( int j=0; j<tsize; j++ )
		bacteria.erase(bacteria.begin() + temp[j]);
		
	if ( debug ) printf("Number of lineages = %d\n", (int)bacteria.size());

}
