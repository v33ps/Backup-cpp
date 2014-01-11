#include <fstream>
#include "configure.h"
using namespace std;


Conf::Conf(){

	num_sources = 0;
	num_dests	= 0;
}
/*
This function only gets called when we detect that the user
has never run the program before. It gets important info like
how often they want it to run, what to backup and where to
*/
void Conf::Init_config(){
	cout << "Hello, it appears this is the first time you\
	have run this program before, I'm going to ask you some\
	basic questions so this doesn't have to happen again!\n" << endl;

	cout << "How many sources do you want to backup?\n";
	cin >> num_sources;
	cin.ignore(); //this is so it doesn't skip over input later on
	for(int i = 0; i < num_sources; i++){
		cout << "Enter your source direcotry: ";
		// you need getline() b/c <source> is a string and if there is any
		//whitespace, cin stops reading input after the 1st whitespace.
		getline(cin, source);
		source_v.push_back(source);
		cout << endl;
	}

	cout << "How many destinations would you like to have?\n";
	cin >> num_dests;
	cin.ignore();
	for(int i = 0; i < num_dests; i++){
		cout << "Enter your destination directory: ";
		getline(cin, dest);
		dest_v.push_back(dest);
		cout << endl;
	}

    cout << "How frequently would you like to backup? (hours, days, weeks, months)\n";
    getline(cin, frequency);
    cout << "Freq: " << frequency << endl;

    Write_to_file(source_v, dest_v, frequency);
}

/*
This function writes our config.txt file so we don't have to ask
the user ever again for their inputs
*/
int Conf::Write_to_file(std::vector<std::string> source, std::vector<std::string> dest, std::string frequency){
    ofstream fout ("config.txt");

    if(fout.is_open()){
        while(source.size() > 0){
            source.erase(source.begin());
        }

        while(dest.size() > 0){
            dest.erase(dest.begin());
        }
    }
    else{
        cout << "Couldn't open config.txt, exiting..." << endl;
        return 0; //exits program
    }
    fout.close();

}