#include <iostream>

#include <fstream>
//#include "configure.h"
#include "backup.h"
using namespace std;

int main(){
	Conf c;
	Backup b;
	bool confirm = false;
	ifstream log_fin("log.txt");

	//if our log file doesn't exist it means we haven't run
	//this program before, so run the configuration function
	//.good() checks to make sure there are no stream errors
	if(!(log_fin.good())){
		//c.Init_config();
		confirm = b.Read_file();

		if(confirm){

		}
	}
	else{
        confirm = b.Read_file();

	}

	return 0;
}