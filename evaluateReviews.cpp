// Name: Sujoy Barua
// Lab Section: 020
// Date Submitted: 11/12/2021

// Add any #includes for C++ libraries here.
// We have already included iostream as an example.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// The #include adds all the function declarations (a.k.a. prototypes) from the
// reviews.h file, which means the compiler knows about them when it is compiling
// the main function below (e.g. it can verify the parameter types and return types
// of the function declarations match the way those functions are used in main() ).
// However, the #include does not add the actual code for the functions, which is
// in reviews.cpp. This means you need to compile with a g++ command including both
// .cpp source files. For this project, we will being using some features from C++11,
// which requires an additional flag. Compile with this command:
//     g++ --std=c++11 evaluateReviews.cpp reviews.cpp -o evaluateReviews
#include "reviews.h"

using namespace std;

const double SCORE_LIMIT_TRUTHFUL = 3;
const double SCORE_LIMIT_DECEPTIVE = -3;


int main() {

    // opening a input stream to read in the keywordWeights.txt file and checking if it properly opened
    ifstream KW("keywordWeights.txt");
    if (!KW.is_open()) {
        cout << "Error: keywordWeights.txt could not be opened." <<endl;
        return 1;
    }

    // initializing necessary variables and using the readKeywordWeights to read in from the file stream opened previously
    vector<string> keywords;
    vector<double> weights;
    double totalWeight = 0;
    vector<double> totalWeight_s;
    int truthful = 0;
    int deceptive = 0;
    int uncategorized = 0;
    int review_n = 0;
    readKeywordWeights(KW, keywords, weights);
    KW.close(); //closing the output stream of keywordWeights.txt

   
    // initializing more necessary variables and opening the output stream to reporter.txt file
    // adding the header of the reporter.txt file to the open stream
    vector<string> reviewWords;
    string fileName;
    string word;
    ofstream reporter("report.txt");
    reporter << "review score category" << endl;


    // looping through the reviews one by one with for loop and categorizing each as truthful, deceptive, or uncategorized
    // adding proper statements to the reporter.txt file's stream as we go through
    for (int i = 0; i < 100; ++i) {
        fileName = makeReviewFilename(i);
        ifstream review(fileName);
        if (!review.is_open()) {
		    break;
        }
        review_n += 1;
    
        vector<string> reviewWords;

        readReview(review, reviewWords);

        totalWeight = reviewScore(reviewWords, keywords, weights);

        totalWeight_s.push_back(totalWeight);

        if (totalWeight > SCORE_LIMIT_TRUTHFUL) {
            truthful += 1;
            reporter << i << " " << totalWeight << " " << "truthful" << endl;
        }
        else if (totalWeight < SCORE_LIMIT_DECEPTIVE) {
            deceptive += 1;
            reporter << i << " " << totalWeight << " " << "deceptive" << endl; 
        }
        else {
            uncategorized += 1;
            reporter << i << " " << totalWeight << " " << "uncategorized" << endl;
        }
        review.close(); //closing the input stream of the review which will open when the loop runs again
        
    }

    // adding the second section of statements to the output file stream, after adding a blank line
    reporter << endl;
    reporter << "Number of reviews: " << review_n << endl;
    reporter << "Number of truthful reviews: " << truthful << endl;
    reporter << "Number of deceptive reviews: " << deceptive << endl;
    reporter << "Number of uncategorized reviews: " << uncategorized << endl;

    // using more loops to determine the index of reviews with the maximum and minimum scores.
    double currentMaxI = 0;
    double currentMinI = 0;
    for (int i = 0; i < totalWeight_s.size(); ++i) {
        if (totalWeight_s[i] > totalWeight_s[currentMaxI]) {
            currentMaxI = i;
        }
        else if (totalWeight_s[i] < totalWeight_s[currentMinI]) {
            currentMinI = i;
        }
    }

    // adding the last section of statements to the output file stream, after adding a blank line
    reporter << endl;
    reporter << "Review with highest score: " << currentMaxI << endl;
    reporter << "Review with lowest score: " << currentMinI << endl;
    reporter.close(); // closing the output stream to reporter.txt

}



