//
//  main.cpp
//  Hot plate
//
//  Created by Andre Carrera on 10/16/15.
//  Copyright © 2015 Andre Carrera. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


const int ROWMAX = 20;
const int COLUMNMAX = 20;
const int FIRST = 0;


void initHotPlate (double hotPlate[ROWMAX][COLUMNMAX]); //why this?

void averageHotPlate (double hotPlate[ROWMAX] [COLUMNMAX],double avHotPlate[ROWMAX] [COLUMNMAX]);

void printHotPlate (double hotPlate[ROWMAX] [COLUMNMAX]);

void plateCheck (double hotPlate[ROWMAX] [COLUMNMAX], double  avHotPlate[ROWMAX] [COLUMNMAX], double & checker, double & checkerFirst);

void setEqual (double hotPlate[ROWMAX] [COLUMNMAX], double avHotPlate [ROWMAX] [COLUMNMAX]);

void resetEqual (double hotPlate[ROWMAX] [COLUMNMAX], double avHotPlate [ROWMAX] [COLUMNMAX]);

void exportHotPlate (double hotPlate[ROWMAX] [COLUMNMAX]);

int main() {
    double checkerFirst= 0;
    double checker = 0;
    const double RESET = 0.0;
    const int ROWMAX = 20;
    const int COLUMNMAX = 20;
    double hotPlate[ROWMAX] [COLUMNMAX];
    double avHotPlate [ROWMAX] [COLUMNMAX];
    double const CHECKMAX = .10;
    double const CHECKMIN = .10;
    int counter = 0;
    
// initialize function
    initHotPlate (hotPlate);
    setEqual(hotPlate, avHotPlate); //avHotPlate gets hotPlate
    printHotPlate (hotPlate);
    
    while (true) { //loop until the biggest change is less than .1
        
        const int FIRSTIT= 0;
        checker = RESET;
        averageHotPlate(hotPlate, avHotPlate); //avHotPlate gets the average of hotplate
        
        plateCheck(hotPlate, avHotPlate,checker,checkerFirst); //checks to see the biggest change by: avHotPlate- Hotplate
        
        resetEqual(hotPlate, avHotPlate); // hotPlate gets AvHotPlate
        
        if (counter == FIRSTIT ) { //print first iteration.
        printHotPlate (hotPlate);
        }
        
        if (checker== CHECKMIN){ //if there is no change  reloop

        }
        else if (checker< CHECKMAX && checker != CHECKMIN){ // if the change is less than .1

            break;
        }

        else if (checker > CHECKMAX) //if the change is greater than .1 reloop
        {

        }
        
        counter++;
    }
    exportHotPlate ( hotPlate); //export to .csv file
    
    return 0;
}

void initHotPlate (double hotPlate[ROWMAX] [COLUMNMAX])
{
    const double TEMPHEAT = 100;
    const double TEMPZERO = 0;
    
    const int LASTROW = 19;
    const int LASTCOL = 19;
    
    for (int row = FIRST; row < ROWMAX; row++) //for all the rows
    {
        if (row == FIRST  || row == LASTROW) { //first and last row
            
            for (int column = FIRST; column < COLUMNMAX ; column++) { //go through the columns one by one
                
                if (column == FIRST || column == LASTROW) {
                    hotPlate[row] [column] = {TEMPZERO}; //edges set to zero
                }
                else if (column > FIRST && column <LASTCOL)
                {
                    hotPlate [row] [column] = {TEMPHEAT}; // middle set to 100
                }
                
            }
        }
        if (row> FIRST && row < LASTROW) {
            for (int column = FIRST; column < ROWMAX ; column++) { //for everything in between
                hotPlate [row] [column] = {TEMPZERO};
            }
        }
    }
}
void averageHotPlate (double hotPlate[ROWMAX] [COLUMNMAX], double avHotPlate [ROWMAX] [COLUMNMAX])
{
    int shiftOne = 1;
    double  avOfFour = 4.0;
        for (int row = FIRST + shiftOne; row < ROWMAX -shiftOne; row++) { //getting the average
            for (int column = FIRST + shiftOne; column  < COLUMNMAX - shiftOne; column ++) { //column one by one
                avHotPlate [row] [column]  = ((
                hotPlate [row-shiftOne] [column] + //goes north
                hotPlate [row +shiftOne] [column]+ //goes south
                hotPlate [row] [column -shiftOne] + // goes west
                hotPlate [row] [column +shiftOne] //goes east
                                            )
                / avOfFour ); //devides to get the average
            }
        }
}

void printHotPlate (double hotPlate[ROWMAX] [COLUMNMAX])
{
    for (int row = FIRST; row < ROWMAX; row++) { //row by row
        for (int column = FIRST ; column  < COLUMNMAX; column ++) { //column one by one
            cout << fixed << setprecision(1) << hotPlate [row] [column] << " ";
        }
        cout << endl; //next column
    }
    
}
void setEqual (double hotPlate[ROWMAX] [COLUMNMAX], double avHotPlate [ROWMAX] [COLUMNMAX])
{
    for (int row = FIRST; row < ROWMAX; row++) { //set the two arrays equal to each other.
        for (int column = FIRST ; column  < COLUMNMAX; column ++) { //column one by one
            avHotPlate [row] [column] = hotPlate [row] [column];
        }
    }
}
void resetEqual (double hotPlate[ROWMAX] [COLUMNMAX], double avHotPlate [ROWMAX] [COLUMNMAX])
{
    for (int row = FIRST; row < ROWMAX; row++) { //set the two arrays equal to each other.
        for (int column = FIRST ; column  < COLUMNMAX; column ++) { //column one by one
            hotPlate [row] [column] = avHotPlate [row] [column];
        }
    }
}
void exportHotPlate (double hotPlate[ROWMAX] [COLUMNMAX])
{
    ofstream out_file;
    out_file.open ("lab6output.csv");
    
    for (int row = FIRST; row < ROWMAX; row++) { //row by row
        for (int column = FIRST ; column  < COLUMNMAX; column ++) { //column one by one
            out_file << fixed << setprecision(1) << hotPlate [row] [column] << ",";
        }
        out_file << endl; //next column
    }
    out_file.close();
}

void plateCheck (double hotPlate[ROWMAX] [COLUMNMAX], double avHotPlate [ROWMAX] [COLUMNMAX], double & checker, double & checkerFirst)
{

    for (int row = FIRST; row < ROWMAX; row++) { //row by row
        for (int column = FIRST ; column  < COLUMNMAX; column ++) { //column one by one
            checkerFirst = avHotPlate [row] [column] - hotPlate [row] [column] ; //here's the problem.
            if (checkerFirst > checker) {
                checker = checkerFirst;
            }
            
        }
    }
    
}