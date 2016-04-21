#include "carClass.h"

Car::Car(){
	numberOfTimesMoved=0;
}

void Car::isMoved(){
	numberOfTimesMoved++;
}

void Car::setarriveOrdepart(string AorD) {
	   arriveOrdepart = AorD;
}

string Car::getarriveOrdepart() const {
	return arriveOrdepart;
}

void Car::setlicense(string license){
	licenseplate = license;
}

string Car::getlicense() const {
	return licenseplate;
}

int Car::getTimesMoved() const{
	return numberOfTimesMoved;
}

bool Car::search(const string license)const{
	if (license == licenseplate)
		return true;
	return false;
}