//Gabe Meros
//Bankers Algorithim Assignment


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctype.h>

//gathers data from input file
void getData(std::vector< std::vector<int> > &all, std::vector< std::vector<int> > &max, std::vector<int> &ava, int &proc, int &reso) {
    std::ifstream in; 
    in.open("input.txt");

    if(!in) { //check if file failed to open
        std::cerr << "File failed to open..." << '\n';
        exit(1);
    }

    char c; //char for reading file by characters
    int i = 0; //iterator for different vectors
    std::string word; //string to hold value

    std::vector<int> row; //vector to hold all values in row


    while(!in.eof()) { //while not end of file
        in.get(c); //reads character
            if(!isdigit(c)) { //check if c is digit, if not read as word
                if(word != "") { //if word is not blank, convert word to int
                    int num = std::stoi(word);

                    if(i == 2) { //if itr is 2, add to available vector
                        ava.push_back(num);
                    }
                    
                    row.push_back(num); //push num onto row
                }

                word = ""; //reset word
            }
            else if(isdigit(c) && c != ' ' && c != ',') { //adds c to string if c is numeric
                word.push_back(c);
            }

            if(c == '\n' || c == '\t' || c == '\r') { //checks if c is a newline char
                i = 0; //resets iterator
                row.clear(); //clears row            
            }
            else if(c == ',') { //checks if c is a comma
                if(i == 0) { //checks if row adds to allocate vector
                    all.push_back(row); //pushes row into allocate vector
                }
                else if(i == 1) { //checks if row adds to max vector
                    max.push_back(row); //pushes row into max vector
                }
                row.clear(); //clears row values            
                i++; // iterate vector
            }
        }

    proc = all.size(); //assigns # of processes to # of rows in allocate vector
    reso = ava.size(); //assigns # of resources to # of items in available vector
}

int main() {
    int proc, reso; //to hold num of processes and resources

    std::vector< std::vector<int> > all; // vector of allocated resources
    std::vector< std::vector<int> > max; // vector of max resources
    std::vector<int> ava; //vector of available resources
    
    getData(all, max, ava, proc, reso); //inputs data from file into vectors and 2 variables

    std::cout << "\nAlloc resource table\n"; //Label outputted table
    for(int i = 0; i < proc; i++) { //Output all values in alloc vector as a table
        for(int j = 0; j < reso; j++) {
            std::cout << all[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << '\n';

    std::cout << "Max resource table\n"; //Label outputted table
    for(int i = 0; i < proc; i++) { //Output all values in max vector as a table
        for(int j = 0; j < reso; j++) {
            std::cout << max[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << '\n';

    std::cout << "Available resource list\n"; //Label outputted list
    for(int i = 0; i < reso; i++) {
       std::cout << ava[i] << " "; //Output all values in available vector as list
    }

    std::cout << "\n\n";

    int fin[proc]; //vectors for determining finished processes
    int end[proc]; //vector for holding safe seq order

    int need[proc][reso]; //vector for needed resources

    int order = 0; //iterator for process order

    for(int i = 0; i < proc; i++) //initialize all finishing values to 0
        fin[i] = 0;

    
    for(int i = 0; i < proc; i++) { //for calculating needed resources
        for(int j = 0; j < reso; j++) {
            need[i][j] = max[i][j] - all[i][j];
        }
    }

    std::cout << "Needed resource list\n"; //Label outputted list
    for(int i = 0; i < proc; i++) { //output all values in need vector as table
        for(int j = 0; j < reso; j++) {
            std::cout << need[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << '\n';

    for(int i = 0; i < proc; i++) { //iterate through all processes
        for(int j = 0; j < proc; j++) {
            if(fin[j] == 0) { //if process is not finished
                int boo = 0; //track bool
            
                for(int k = 0; k < reso; k++) { //iterate through all resources
                    if(need[j][k] > ava[k]) { //if needed  > available resources, set track bool to true
                        boo = 1;
                        break;
                    }
                }
            
                if(boo == 0) { //if flag bool is false
                    end[order++] = j; //add process to position of iterator in sequence

                    for(int l = 0; l < reso; l++) //iterate through all resources 
                        ava[l] += all[j][l]; //add allocated resource to available
                    
                    fin[j] = 1; //set process to finished
                }
            }
        }
    }

    int boo = 1; //set safe bool to true 

    for(int i = 0; i < proc; i++) { //iterate through all processes
        if(fin[i] == 0) { //if process is unfinished, print unsafe and set safe bool to false
            boo = 0;
            std::cout << "Sequence is unsafe\n";
            break;
        }
    }

    if(boo == 1) { //if safe bool is true, print safe sequence order
        std::cout << "Safe sequence is: \n";
        for(int i = 0; i < proc - 1; i++) //iterate through processes - 1
            std::cout << " P" << end[i] << " to"; //print safe process order
        std::cout << " P" << end[proc-1] << '\n'; //print last process
    }
    return 0;
}