#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <cstddef>
#include <Windows.h>

using namespace std;

const string exepath = "\\game\\bin\\win64\\hlvr.exe";
const string mappath = "\\game\\hlvr\\maps\\";

string launchoptions = "-novid -console -vconsole";
string mapname;
string prgpath;
string path;
string scriptsrc;

string getfilename (const string& str) {
    size_t found = str.find_last_of("/\\");
    return str.substr(found+1);
}

string getpath (const string& str) {
    size_t found = str.find_last_of("/\\");
    return str.substr(0, found);
}

string removeextension (const string& str) {
    size_t found = str.find_last_of(".");
    return str.substr(0, found);
}

bool fexists(const string filename) {
    return access(&(filename[0]), F_OK) != -1;
}

int copy(string sp, string dp){
    string cmd;
    if(GetFileAttributesA(&(sp[0])) & FILE_ATTRIBUTE_DIRECTORY)
        cmd = "echo d | Xcopy /s /y /q \"" + sp + "\" \"" + dp + "\"";
    else
        cmd = "copy \"" + sp + "\" \"" + dp + "\"";
    return system(&(cmd[0]));;
}

int removedir(string dir){
    string cmd;
    cmd = "rd \"" + dir + "\" /q /s";
    return system(&(cmd[0]));;
}

void createconfig(){
    ofstream config;
    cout << ("Searching for HLA at default directory...") << endl;

    if(fexists("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Half-Life Alyx\\game\\bin\\win64\\hlvr.exe"))
        path = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Half-Life Alyx";
    else{
        int presult = 0;
        while(presult != 1){
            path = "";
            cout <<("Couldn't find HLA at set directory...") << endl;
            cout <<("Please paste the path to your Half-Life Alyx folder: ");
            getline(cin, path);
            if (!path.empty() && path[path.length()-1] == '\n')
                path.erase(path.length()-1);
            if(fexists(path+"\\game\\bin\\win64\\hlvr.exe"))
                presult = 1;
        }
    }

    config.open(prgpath + "\\hlapath.txt");
    cout << ("Saving path to hlapath.txt") << endl;
    config << path;
    config.close();
}

void readconfig(){
    cout <<("HLA path file found...") << endl;

    fstream config(prgpath + "\\hlapath.txt");

    getline(config, path);
    config.close();

    if(!fexists(path + exepath)){
        cout <<("HLA path not configured properly") << endl;
        createconfig();
    }
}

void createargs(){
    string loinput;

    ofstream lofile;
    cout <<("Couldn't find launch options file...") << endl;
    cout <<("Please input any launch options you want (leave blank for -novid -console -vconsole): ");
    getline(cin, loinput);

    if(loinput != "")
        launchoptions = loinput;

    cout << "You can change these in hlalaunchoptions.txt in the future." << endl;

    lofile.open(prgpath + "\\hlalaunchoptions.txt");
    cout << ("Saving launch options to hlalaunchoptions.txt") << endl;
    lofile << launchoptions;
    lofile.close();
}

void readargs(){
    cout <<("HLA launch options file found...") << endl;

    fstream lofile(prgpath + "\\hlalaunchoptions.txt");

    getline(lofile, launchoptions);

    lofile.close();
}

void runalyx(){
    int cmdresult;
    string command = "\"" + path + exepath + "\" " + launchoptions + " -vr +map " + mapname;

    //run the program
    cout <<("Running " + command);

    cmdresult = system(&(command[0]));

    //cout <<("Command ran: %d", cmdresult);
}

int main(int argc, char *argv[]){
    
    //facny splash screen
    cout << " _   _  _       ___   _                                 _                 " << endl;
    cout << "| | | || |     / _ \\ | |                               | |                " << endl;
    cout << "| |_| || |    / /_\\ \\| |      __ _  _   _  _ __    ___ | |__    ___  _ __ " << endl;
    cout << "|  _  || |    |  _  || |     / _` || | | || '_ \\  / __|| '_ \\  / _ \\| '__|" << endl;
    cout << "| | | || |____| | | || |____| (_| || |_| || | | || (__ | | | ||  __/| |   " << endl;
    cout << "\\_| |_/\\_____/\\_| |_/\\_____/ \\__,_| \\__,_||_| |_| \\___||_| |_| \\___||_|   " << endl;
    cout << "==========================================================================" << endl << endl;


    //check if map file exists and is valid
    if(argc < 2){
        cout << "Map file required, press enter to exit" << endl;
        getchar();
        return 0;
    } else if( (!fexists(argv[1])) || (strstr(argv[1], "vpk") == NULL && strstr(argv[1], "VPK") == NULL)){
        cout << "Invalid map file, press enter to exit" << endl;
        getchar();
        return 0;
    }
    

    prgpath = getpath(argv[0]);

    mapname = getfilename(argv[1]);

    scriptsrc = getpath(argv[1])+"\\"+removeextension(mapname)+"\\scripts";

    //create config if it doesn't already exist
    if(fexists(prgpath + "\\hlapath.txt") != true)
        createconfig();
    else
        readconfig();

    if(fexists(prgpath + "\\hlalaunchoptions.txt") != true)
        createargs();
    else
        readargs();

    string mdestination = path+mappath+mapname;
    string sdestination = path+"\\game\\hlvr\\scripts";

    string tmpmap = path+mappath+"old"+mapname;
    string tmpscript = path+"\\game\\hlvr\\oldscripts";

    //finds if there is already a script folder, creates temp script, and copy scripts
    if(fexists(scriptsrc)){
        if(fexists(sdestination))
            rename(&(sdestination[0]), &(tmpscript[0]));
        copy(scriptsrc,sdestination);
    }

    //finds if there is already a map with the name, creates temp map, and copy maps
    if(fexists(mdestination))
        rename(&(mdestination[0]), &(tmpmap[0]));
    copy(argv[1], mdestination);

    //run half life alyx
    runalyx();
    
    //delete scripts after finished and restores old scripts
    if(fexists(sdestination)){
        removedir(sdestination);
        if(fexists(tmpscript))
            rename(&(tmpscript[0]), &(sdestination[0]));
    }

    //delete map after finished and restores old map
    remove(&(mdestination[0]));
    if(fexists(tmpmap))
        rename(&(tmpmap[0]), &(mdestination[0]));

    //getchar();

    return 0;
}
