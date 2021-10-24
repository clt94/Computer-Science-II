/*
COPYRIGHT (C) 2019 Connor Taylor (clt94) All rights reserved
Assignment H: The Movie Map
Author: Connor Taylor
        clt94@zips.uakron.edu
Purpose: Using a map, output the average review score of each movie from a text file.
*/

#include <iostream>
#include <iterator>
#include <map>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>

using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::string;
using std::ios;
using std::map;
using std::pair;
using std::iterator;
using std::setprecision;
using std::fixed;

// Precondition: map with a string, and pair with an in and float, by reference, and an ifstream by reference
// Postcondition: none
void setMovieMap(map<string, pair<int, float>>&, ifstream&);

// Precondition: map with a string, and pair with an in and float, by reference
// Postcondition: none
void outputMovieMap(map<string, pair<int, float>>&);

int main()
{
    ifstream reviewz;
    reviewz.open("reviewz.txt", ios::in); // opens file in input mode
    if(!reviewz) // verifies the file is opened
    {
        cout << "Failed to open file!\nEnding program!" << endl;
        return 0;
    }

    // map named movies, with a string and a pair with an int and float
    map<string, pair<int, float>> movies; // movies(name, (review count, total review score))

    setMovieMap(movies, reviewz); // sets movies using input from the text file

    outputMovieMap(movies); // outputs movies in proper format

    reviewz.close(); // closes file

    return 0;
}

// Precondition: map with a string, and pair with an in and float, by reference named movies, and an ifstream by reference named reviewz
// Takes input reviewz and inputs it into map of movies
// Postcondition: none
void setMovieMap(map<string, pair<int, float>>& movies, ifstream& reviewz)
{
    int size;
    reviewz >> size; // takes input for size from file
    reviewz.ignore(); // skips \n to go to next line

    string movieName; // temporary variable to take the movie name from the text file
    float reviewScore; // temporary variable to take the review score from text file

    for(int i = 0; i < size; ++i) // iterates through list according to size of the value listed in the text file
    {
        getline(reviewz, movieName, '\n'); // takes input until \n for the movie's name
        reviewz >> reviewScore; // takes input for the movies review score
        reviewz.ignore(); // skips \n to to go next line
        if(movies.find(movieName) != movies.end()) // checks if the movie is already in the map
        {
            movies.at(movieName).first += 1; // iterates review count by 1
            movies[movieName].second += reviewScore; // adds review score to total review score
        }
        else // if the movie not in the map already
        {
            movies[movieName].first = 1; // sets review count to 1
            movies[movieName].second = reviewScore; // sets review score to the review score from the text file
        }
    }
}

// Precondition: map with a string, and pair with an in and float, by reference named movies
// Outputs map of movies with each movies average review score
// Postcondition: none
void outputMovieMap(map<string, pair<int, float>>& movies)
{
    map<string, pair<int, float>>::const_iterator itr; // iterator to traverse the map
    float averageScore;
    for (itr = movies.begin(); itr != movies.end(); ++itr)
    {
        averageScore = itr->second.second / itr->second.first;
        if(itr->second.first > 1) // if there is more than one review
        {
            cout << itr->first << ": " << itr->second.first << " reviews, average of " // outputs average review score
                 << fixed << setprecision(1) << round(averageScore * 10) / 10 << " / 5" << endl; // multiplies the average score by 10, rounds it,
        }                                                                                        // then divides it back to its original
        else // if there is only one review score
        {
            cout << itr->first << ": " << itr->second.first << " review, average of " // outputs average review score
                 << fixed << setprecision(1) << round(averageScore * 10) / 10 << " / 5" << endl; // multiplies the average score by 10, rounds it,
        }                                                                                        // then divides it back to its original
    }
}
