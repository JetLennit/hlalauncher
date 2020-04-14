#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstddef> 

using namespace std;

const string exepath = "\\game\\bin\\win64\\hlvr.exe";
const string destination = "\\game\\hlvr\\maps\\";

string mapname;
string prgpath;
string path;


string getfilename (const string& str) {
    size_t found = str.find_last_of("/\\");
    return str.substr(found+1);
}

string getpath (const string& str) {
    size_t found = str.find_last_of("/\\");
    return str.substr(0, found);
}

bool fexists(const string filename) {
    return access(&(filename[0]), F_OK) != -1;
}

void createconfig(){
    ofstream config;

    if(fexists("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Half-Life Alyx\\game\\bin\\win64\\hlvr.exe"))
        path = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Half-Life Alyx";
    else{
        int presult = 0;
        while(presult != 1){
            path = "";
            cout <<("Couldn't find HLA at default directory...") << endl;
            cout <<("Please paste the path to your Half-Life Alyx folder: ");
            getline(std::cin, path);
            if (!path.empty() && path[path.length()-1] == '\n') {
                path.erase(path.length()-1);
            }
            if(fexists(path+"\\game\\bin\\win64\\hlvr.exe"))
                presult = 1;
        }
    }

    config.open(prgpath + "\\hlalaunchconfig.txt");
    config << path;
    config.close();
}

void readconfig(){
    fstream config(prgpath + "\\hlalaunchconfig.txt");

    getline(config, path);

    config.close();
}

int copy(string sp, string dp){
    string cmd;
    cmd = "copy \"" + sp + "\" \"" + dp + "\"";
    system(&(cmd[0]));
    return 1;
}

void runalyx(){
    int cmdresult;
    string command = "\"" + path + exepath + "\"" + " -novid -console -vconsole +map " + mapname;
    
    cout << command << endl;
    //run the program

    cout <<("Running Alyx\n");

    cmdresult = system(&(command[0]));

    //cout <<("Command ran: %d", cmdresult);
}

int main(int argc, char *argv[]){

    //check if map file exists and is valid
    if(argc < 2){
        cout << "Map file required" << endl;
        return 0;
    } else if((!fexists(argv[2])) || (argv[2].substr(argv[2].length() - 3) != "vpk")){
        cout << "Invalid map file" << endl;
        return 0;
    } 

    prgpath = getpath(argv[0]);
    mapname = getfilename(argv[1]);

    //create config if it doesn't already exist
    if(fexists(prgpath + "\\hlalaunchconfig.txt") != true)
        createconfig();
    else
        readconfig();


    string fdestination = path+destination+mapname;

    //copy the map to destination
    copy(argv[1], fdestination);
    
    //run half life alyx
    runalyx();

    //delete map after finished
    remove(&(fdestination[0]));
    
    //getchar();

    return 0;
}   
