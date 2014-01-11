#include <fstream>
#include "backup.h"
#include <ctime>
#include <windows.h>

using namespace std;

Backup::Backup(){
    //do shit
}
/**
Name:       Read_file()
Param:      None
Return:     bool
Purpose:    Reads the config.txt file to get the sources and destinations, and
            the frequency (which gets sents to analyze_freq() and returns
            whether or not to run the back program Also calls Create_backup()
*/
bool Backup::Read_file(){
    ifstream fin ("config.txt");
    bool run = false;

    if(fin.is_open()){
        //loads our source and dest vectors with DIRs from config file
        while(getline(fin, line)){
            //gets frequency from file to see if we should do a backup or not
            if(line.compare(0, 4, "FREQ") == 0){
                cout << "It's a frequency!\n";
                //analyze_freq() determines how long it's been since the last
                //backup and tells us if we should do another or not
                run = analyze_freq(line);

                if(!run){
                    cout << "not time to back up yet... exiting" << endl;
                    exit(1);
                }
            }

            //All sources are denoted by 'SOURCE' in front of them, so it looks
            //for that in the file, then using istringstream it removes it from
            //the string, and passes the remainding part of the string (the
            //DIR, to our vector
            if(line.compare(0, 6, "SOURCE") == 0){
                cout << "it's a source!\n";
                std::istringstream iss(line);

                //<garbage_collector> is used to hold the "SOURCE" that is in-
                //front of our DIR, so we can extract it. I couldn't think of
                // a better way to do it at the time but I'm sure one exists
                iss >> garbage_collector >> source_temp;
                source_v.push_back(source_temp);
            }

            //All destinations are denoted by 'DEST' in front of them
            if(line.compare(0, 4, "DEST") == 0){
                cout << "it's a dest!\n";
                std::istringstream iss(line);
                iss >> garbage_collector >> dest_temp;
                dest_v.push_back(dest_temp);
            }
        }
    }
    else{
        cout << "cannot open config.txt, this shouldn't have happened...\n";
        exit(1);
    }
    Create_backup(source_v, dest_v);
    return run;
}



/**
Name:       Create_backup()
Param:      vector<string>, vector<string>
Return:     void
Purpose:    Starts the backup process (doesn't actually do any of the file
            copying). For loops to run through the destinations and sources
            then calls Copy_assist() to move the files.
*/
void Backup::Create_backup(std::vector<std::string>source_v, std::vector<std::string>dest_v){
    cout << "in Create_backup()" << endl;
    date = get_time(); //gets the date in a d-m-y format

    //creates the paths for the destinations
    for(int i = 0; i < dest_v.size(); i++){
        dest_temp = dest_v.at(i);

        //passes <date> b/c each backup container folder is named the date
        path = path_join(dest_temp, date);

        //copy all the sources to the dest
        for(int i = 0; i < source_v.size(); i++){
            source_temp = source_v.at(i);
            Copy_assist(source_temp, path);
            cout << "+++++copy assist ran fine....." << endl;
        }
    }
}


/**
Name:       path_join()
Param:      string, string
Return:     string
Purpose:    Joins the destination DIRs with the folder that is created to hold
            the backed up files, which is named the date that the backup was
            run.
*/
string Backup::path_join(std::string dest, std::string date){
    std::string joinned_path;

    //you need "\\" b/c the 1st one escapes the 2nd one
    joinned_path = std::string(dest) + "\\" + date;
    return joinned_path;
}


/**
Name:       get_time()
Param:      None
Return:     string
Purpose:    Gets the local date so we can name our backup folders
*/
string Backup::get_time(){
    time(&raw_time);
    timeinfo = localtime(&raw_time);

    strftime(buffer, 80, "%d-%m-%Y", timeinfo);
    std::string str(buffer);
    return str;
}


/**
Name:       Copy_assist()
Param:      string, string
Return:     void
Purpose:    Function uses SHFILEOPSTRUCTA from Windows to copy files to their
            destination. If you want to know more how this function works,
            please look at the msdn documentation

*/
void Backup::Copy_assist(std::string source, std::string dest){
    cout << "---- in copy assist ----\n";
    SHFILEOPSTRUCTA sf;
    int result;

    //You need to append a null terminator b/c even though strings normally
    //have one you need 2.
    source = source + std::string(1, '\0');
    dest = dest + std::string(1, '\0');

    sf.pFrom = source.c_str();
    sf.pTo = dest.c_str();
    sf.wFunc = FO_COPY;
    sf.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_SILENT;

    result = SHFileOperationA(&sf);
    if(result != 0){
        cout << "Error, non zero result from SHFileOperationA..." << endl;
        exit(1);
    }
}

