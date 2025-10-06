#include "rbt.h"

bool alphaNumeric(char c);          //Function to check if a character is alphanumeric
string parser(string input);        //This function extracts the parameters from user inputs, example: extract "AAAA" from addLicence(AAAA)
string outputName(string input);    //This function outputs the outputFileName

int main(int arg_count, char *args[]) {
    
    //Initialize an empty Red Black Tree
    RBT rbt;

    //File names
    string inputFileName;
    string outputFileName;

    //File Streams
    ifstream infile;
    ofstream outfile;
    
    //Verifying user input
    if(arg_count == 2) {
        string iFile(args[1]);
        inputFileName = iFile;
        outputFileName = outputName(iFile);
        infile.open(inputFileName);
    }
    
    else {
        cout << "Invalid Syntax. Use the following syatax: ./pltMgmt inputFileName\n";
        return 0;
    }
    
    //variable to read lines
    string input;

    if(infile.is_open()) {
        //creating outputFile
        outfile.open(outputFileName);

        //code to read queries from input file and write to output file
        while(infile >> input) {
            if(input.find(")") != string::npos) {}
            else {      //This is to handle whitespace in lookupRange function paraeters
                string input2 = "";
                infile >> input2;
                input += input2;
            }
            if(input.find("addLicence()") != string::npos) {
                outfile << rbt.addLicence();
            }
            else if(input.find("addLicence") != string::npos) {
                string plateNum = parser(input);
                outfile << rbt.addLicence(plateNum);
            }
            else if(input.find("dropLicence") != string::npos) {
                string plateNum = parser(input);
                outfile << rbt.dropLicence(plateNum);
            }
            else if(input.find("lookupLicence") != string::npos) {
                string plateNum = parser(input);
                outfile << rbt.lookupLicence(plateNum);
            }
            else if(input.find("lookupPrev") != string::npos) {
                string plateNum = parser(input);
                outfile << rbt.lookupPrev(plateNum);
            }
            else if(input.find("lookupNext") != string::npos) {
                string plateNum = parser(input);
                outfile << rbt.lookupNext(plateNum);
            }
            else if(input.find("lookupRange") != string::npos) {
                string lo = "", hi = "", range = parser(input);
                //parser will output a string which will be 8 characters long
                //lo will be first 4 characters
                lo += range[0];
                lo += range[1];
                lo += range[2];
                lo += range[3];
                //hi will be next 4 characters
                hi += range[4];
                hi += range[5];
                hi += range[6];
                hi += range[7];
                outfile << rbt.lookupRange(lo, hi);
            }
            else if(input == "revenue()") {
                outfile << rbt.revenue();
            }
            else if(input == "quit()") {
                break;
            }
        }

        //closing both files
        outfile.close();
        infile.close();
    }

    else {
        cout << "File could not be read.\n";
    }

    return 0;
}

bool alphaNumeric(char c) {
    if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}

string parser(string input) {
    int i = 0;
    string output = "";
    while(input[i++] != '(');
    while(input[i] != ')') {
        if(alphaNumeric(input[i])) {
            output += input[i];
        }
        ++i;
    }
    return output;
}

string outputName(string input) {
    string output = "";
    int i = 0;
    while(true) {
        if(input[i] == '.' && input[i + 1] == 't' && input[i + 2] == 'x' && input[i + 3] == 't') {
            return output + "-output.txt";
        }
        output += input[i++];
    }
    return "namingError";   //could not correctly read the file name
}
