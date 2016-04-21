//Defines the car class used to created car objects. 

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Car
{
public:
	bool search(const string) const;
	void isMoved();
	void setlicense(string );
	void setarriveOrdepart(string );
	string getlicense() const;
	string getarriveOrdepart() const;
	int getTimesMoved() const;
	Car();

private:
	string arriveOrdepart;
	string licenseplate;
	int numberOfTimesMoved;
};