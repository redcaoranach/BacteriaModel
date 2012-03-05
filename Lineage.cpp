#include "Lineage.h"
#include "Bacterium.h"

using namespace std;

Lineage::Lineage(int generations)
{
	int pop0 = 1;
	for (int i = 0; i<pop0; i++)
		lineage.push_back(new Bacterium());
	
/*	for (int i = 0; i<generations; i++)
		lineage.divide((int) lineage.size());*/
	
	/*lineage.push_back( new Bacterium() );
	lineage.push_back( new Bacterium() );
	lineage.push_back( new Bacterium() );
	lineage.push_back( new Bacterium() );
	lineage.push_back( new Bacterium() );
	lineage.push_back( new Bacterium() );
	lineage.push_back( new Bacterium() );
	lineage.push_back( new Bacterium() );
	lineage.push_back( new Bacterium() );
	lineage.push_back( new Bacterium() );
	printf("Number of lineage: %d\n", (int)lineage.size());*/
	printf("Number of lineages: %d\n", (int)lineage.size());
}

Lineage::~Lineage()
{

}

bool Lineage::divide(int index)
{
	
	if ( index < lineage.size() )
	{
		lineage.insert(lineage.begin() + index, new Bacterium());
		return true;

	}
	else
	{

		fprintf(stderr, "Invalid index (%d)!\n", index);
		return false;

	}
}

bool Lineage::die(int index)
{
	if ( index < lineage.size() )
	{

		lineage.erase( lineage.begin() + index );
		return true;

	}
	else
	{

		fprintf(stderr, "Invalid index (%d)!\n", index);
		return false;

	}

} 

int Lineage::get_size()
{
	return (int)lineage.size();
}
