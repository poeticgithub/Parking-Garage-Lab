/*****************************************************************************
* Nujoma Halls
* CSC 326
* Lab 4A

The following program will create a parking garage with two lanes: Lane 1 and Lane 2. These lanes will be stack objects and 
each lane can hold a maximum of ten cars.
There is also a third stack object called the Street where cars will be temporarily moved if a lane is full.

1. The  program will read in the contents from a file called "Cars.txt"
   The contents of the file are in the following format:
   A PRETTY
   D MICKEY
   where A stands for "arriving", D stands for "departing" and the letters PRETTY and MICKEY are car licence plates.

2. The program will define a stack class. The stack objects will create string arrays which will hold the license plates 
   of the cars read in from the file.
3. The program will also define a car class. The car objects will hold the license plates, the car's status (A or D), and 
   the number of times the car was moved.

4. All the cars read in from the file with 'A' (arriving) status will be added to the lanes by "pushing" them into the lanes if there is room. 
  If a car has a 'D' status this means it has to depart. All the cars in front of it will be "popped" into the other lane if there is room there. 
  If there is no room, they will be popped into the street temporarily then moved back into an open lane after the departing car has left.
  If a car has a 'D' status but is not found in the garage, the program will display an error message.

5. The program will print the two lanes, and any cars left in the street.

******************************************************************************/


#include "stackClass.h"
#include "carClass.h"

int main(){

	int counter = 9, x = 0, y = 0, z = 0;
	stackType<string> lane1(10);
	stackType<string> lane2(10);
	stackType<string> street(10);
	ifstream inFile;
	bool found=false, foundInLane1=false, foundInLane2=false;
	string restofline, licensehelper, arriveordepart, tempcar, tempcar2;
	
	lane1.initializeStack();
	lane2.initializeStack();
	street.initializeStack();
	
	inFile.open("Cars.txt");
	if (!inFile.is_open()){
		cout << "File not found." << endl;
		exit(1);
	}

	Car cars[17];

	// The following while loop will read in cars from the file, fill up the lanes, and
	//remove any car that has to depart.
	while (x<17){

	    inFile >> arriveordepart;
		inFile >> licensehelper;
		getline(inFile, restofline);
		cars[x].setarriveOrdepart(arriveordepart);
		cars[x].setlicense(licensehelper);


		// In the code segment below, the license plates of arriving (A) cars are "pushed" into the lanes.
		if (cars[x].getarriveOrdepart() == "A"){  
			if (!lane1.isFullStack()){
				lane1.push(cars[x].getlicense());
				cars[x].isMoved();
				cout << cars[x].getlicense() << " has arrived at Lane 1.\n";
				y++;
			}
			else if (!lane2.isFullStack()){
				lane2.push(cars[x].getlicense());
				cars[x].isMoved();
				cout << cars[x].getlicense() << " has arrived at Lane 2.\n";
				z++;
			}
			else if (lane1.isFullStack() && lane2.isFullStack())
				cout << "Sorry, both lanes are full. We have no more room.\n";
		}


		// In the code segment below, the license plates of departing (D) cars are "popped" from the lanes.
		else if (cars[x].getarriveOrdepart() == "D"){
			//check if the departing car is found in Lane 1
			for (int i = 0; i < y && foundInLane1==false; i++){
				tempcar2 = lane1.get(i);
				found = cars[x].search(tempcar2);
				if (found == true){
					foundInLane1 = true;
					foundInLane2 = false; //car can't be in two places at once.
				}
			}
			//check if the departing car is found in Lane 2
			for (int i = 0; i < z && foundInLane2==false; i++){
				tempcar2 = lane2.get(i);
				found = cars[x].search(tempcar2);
				if (found == true){
					foundInLane2 = true;
					foundInLane1 = false; //car can't be in two places at once.
				}
			}

			// moving a car from lane 1 to lane 2 in order to make room for car departing from lane 1
			if (foundInLane1 == true){
				while ((cars[x].getlicense() != lane1.get(counter))){
					if (!lane2.isFullStack()){
						if (cars[x].getlicense() != lane1.top())
							lane2.push(lane1.top());
						    tempcar = lane1.top();
                        //keep track of the number of times the cars are moved
						for (int i = 0; i < x; i++){
							if (cars[i].getlicense() == tempcar)
								cars[i].isMoved();
						}
						lane1.pop();
					}
					else if (lane2.isFullStack()){ 
					   if (cars[x].getlicense() != lane1.top())
						   street.push(lane1.top());
						   tempcar = lane1.top();
					   //keep track of the number of times the cars are moved
					   for (int i = 0; i < x; i++){
						 if (cars[i].getlicense() == tempcar)
							cars[i].isMoved();
					   }
					   lane1.pop();
					} 
					if (counter != 0)
						counter--;
			    } 

				//The car departs.
				found = true;
				foundInLane1 = false;
				counter = 9;
				lane1.pop();
				cout << cars[x].getlicense() << " has departed from Lane1.\n";
				cout << cars[x].getlicense() << " has moved out of the way " << cars[x].getTimesMoved() << " times.\n";
			} 

			// moving a car from lane 2 to lane 1 in order to make room for car departing from lane 2
			if (foundInLane2 == true){
				while ((cars[x].getlicense() != lane2.get(counter))){
					if (!lane1.isFullStack()){
						if (cars[x].getlicense() != lane2.top())
							lane1.push(lane2.top());
						    tempcar = lane2.top();
						//keep track of the number of times the cars are moved
						for (int i = 0; i < x; i++){
							if (cars[i].getlicense() == tempcar)
								cars[i].isMoved();
						}
						lane2.pop();
					}
				    else if (lane1.isFullStack()){ 
				        if (cars[x].getlicense() != lane2.top())
					       street.push(lane2.top());
						   tempcar = lane2.top();
						//keep track of the number of times the cars are moved
						for (int i = 0; i < x; i++){
							if (cars[i].getlicense() == tempcar)
							    cars[i].isMoved();
						}
					    lane2.pop();
				    }
					if (counter != 0)
						counter--;
				}
				//The car departs
				found = true;
				foundInLane2 = false;
				counter = 9;
				lane2.pop();
				cout << cars[x].getlicense() << " has departed from Lane 2.\n";
				cout << cars[x].getlicense() << " has moved out of the way " << cars[x].getTimesMoved() << " times.\n";
			} 

			if (found == false){
				cout << "Sorry, that car is not in our garage. Contact the police in case";
			    cout << " it was stolen." << endl;
		    }
			found = false;
			street.isEmptyStack();
			
			//The following while loop will move any cars in the street back into any available lanes
			while ((!lane1.isFullStack() && !street.isEmptyStack()) || (!lane2.isFullStack() && !street.isEmptyStack())){
				if (!lane1.isFullStack() && (!street.isEmptyStack())){
					lane1.push(street.top());
					street.pop();
					street.isEmptyStack();
				}
				else if (!lane2.isFullStack() && (!street.isEmptyStack())){
					lane2.push(street.top());
					street.pop();
					street.isEmptyStack();
				}
			}
	    }//end of code segment for departing (D) cars
	x++;
	} //end of the while loop
	inFile.close(); //closes the file
	
	if (street.isEmptyStack())
		cout << endl << "At this time, there are no cars in the street." << endl << endl;

	//printing out cars in lanes 1, 2 and the street
	cout << "Lane 1: exit <-- ";
	while (!lane1.isEmptyStack()) //print Lane1. remember Last In First Out.
	{
		cout << lane1.top() << " ";
		lane1.pop();
	}
	cout << endl;
	
	cout << "Lane 2: exit <-- ";
	while (!lane2.isEmptyStack()) //print Lane2. remember Last In First Out.
	{
		cout << lane2.top() << " ";
		lane2.pop();
	}
	cout << endl;
	
	if (!street.isEmptyStack()) //don't print anything if the street is empty.
	cout << "The cars in the street: ";
	while (!street.isEmptyStack()) //print Street. remember Last In First Out.
	{
		cout << street.top() << " ";
		street.pop();
	}
	cout << endl;

	system("pause");
	return 0;
}