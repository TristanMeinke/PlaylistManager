//  main.cpp
//  CS162Assignment4-mp3Player
//
//  Created by Tristan on 2/22/16.


#include "LinkedList.h"
#include "Song.h"

void fileNotFound();
void titleNotFound();
void noPlaylistLoaded();
void inputNotValid();
void printMenu();

std::string getFilePath();

void deallocateEntireList(LinkedList &playlist, long &length, Node* &extractionNode);
//Calls LinkedList.h member function RemoveLinkFromFront();
//Recursively calls self for length of list;

void loadSongsFromFile(LinkedList &playlist, long &length, std::fstream &playlistFile);
//Calls deallocateEntireList(), to clear any data which may be occupying 'playlist'.
//Calls Song.h constructor with name parameter to create song objects
//Calls Song.h member function SetSongPath() [?] when creating song objects
//Calls readAndAddSong by line until EOF.
std::string readAndAddSong(std::fstream &playlistFile, LinkedList &playlist);

void addNewSong(LinkedList &playlist, long &length);
//Calls Song.h constructor with name parameter to create song objects
//Calls LinkedList.h member functions AddLinkToBack(); AppendToListFile()

void deleteSingleSong(LinkedList &playlist, long &length);
//Calls LinkedList.h member function RemoveThisLink();
//[Possibly] calls prepareForDeletion

void printPlayerString(LinkedList &playlist, long &length);
//Calls Song.h member function PlaySong();

void printPlaylist(LinkedList &playlist, long &length);
//Calls Song.h member function GetSongName();



int main()
{
    std::string menuInput = "";
    std::string filePath;
    long length;
    
    std::fstream playlistFile;
    
    bool end = false;
    
    LinkedList playlist;
    
    do
    {
        printMenu(); //Prints the menu.
        std::cin.clear(); //Clears the input buffer, to avoid confusion in navigation.
        std::cin >> menuInput; //Takes input from the user.
        std::cin.clear(); //Clears again.
        
        while (menuInput != "a" && menuInput != "open" &&
               menuInput != "b" && menuInput != "add" &&
               menuInput != "c" && menuInput != "delete" &&
               menuInput != "d" && menuInput != "play" &&
               menuInput != "e" && menuInput != "print" &&
               menuInput != "f" && menuInput != "quit")

        {
            inputNotValid();
            printMenu();
            std::cin.clear();
            std::cin >> menuInput;
            std::cin.clear();
        }
        
        if (menuInput == "a" || menuInput == "open")
            //If the user selects this option, they will be prompted for a filepath,
            //which the program will follow, open, read the file, and use it to populate the star catalog=
        {
            
            loadSongsFromFile(playlist, length, playlistFile);
        }
        if (menuInput == "b" || menuInput == "add")
            //If the user selects this option, they will be prompted for a series of
            //input regarding the new entry.
        {
            addNewSong(playlist, length);
        }
        if (menuInput == "c" || menuInput == "delete")
            //When the user selects this option, they will be prompted for a song name, which will then be deleted.
        {
            deleteSingleSong(playlist, length);
        }
        if (menuInput == "d" || menuInput == "play")
            //When the user selects this option, they are prompted for a song name, which is played.
        {
            printPlayerString(playlist, length);
        }
        if (menuInput == "e" || menuInput == "print")
            //If the user selects this option, the current contents of the list will
            //be printed.
        {
            printPlaylist(playlist, length);
        }
        if (menuInput == "f" || menuInput == "quit")
            //When the user selects this option, the program ends.  Additionally,
            //as a matter of practice, this option also calls clearList().
        {
            Node* extractionNode;
            
            deallocateEntireList(playlist, length, extractionNode); //call to recursive deletion function

            std::cout << "Goodbye." << std::endl;
            end = true;
            return end;
        }
        
    }
    while (end == false);
    
    
    return 0;
}

void fileNotFound()
//This function just allows for easy repitition of a pleasantly
//formatted error message without clogging up other functions
//with useless print statements.
{
    std::cout << "- - - - - - - -" << std::endl;
    std::cout << "File not found." << std::endl;
    std::cout << "- - - - - - - -" << std::endl;
    
    return;
}

void titleNotFound()
//This error informs the user that the title they searched for was not
//found in the playlist.
{
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "That title was not found in the current playlist." << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    
    return;
}


void inputNotValid()
//Another error message.  These are also good for ease and efficiency
//of formatting or reformatting repeated statements.
{
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - " << std::endl;
    std::cout << "Input not valid. Please make another selection." << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - " << std::endl;
    
    return;
}

void noPlaylistLoaded()
//Explains to the user that no playlist was located, and provides
//the user with instructions on how to load a playlist.
{
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "Unable to locate a valid playlist." << std::endl;
    std::cout << "Please open a playlist file before selecting b, c, d, or e." << std::endl;
    std::cout << "To open a file, select 'a' or enter 'open'." << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    
    return;
}

void printMenu()
//Just prints the menu.
{
    
    std::cout << "a) Open a playlist" << std::endl;
    std::cout << "b) Add a song" << std::endl;
    std::cout << "c) Browse books" << std::endl;
    std::cout << "d) Play a song" << std::endl;
    std::cout << "e) Print playlist" << std::endl;
    std::cout << "f) Quit" << std::endl;
    
    return;
}

std::string getFilePath()
//Takes the filePath as string input from the user
//and returns it to the program.
{
    std::cout << "\nPlease enter the full path of the file you'd like to read: ";
    
    std::cin.ignore(ENTRY_SZ, '\n');  //Ignores spaces in the file path
    std::cin.getline(Song::songListFile_, ENTRY_SZ);  //Actually retrieves the file path
    
    return Song::songListFile_; //Returns the file path so it will be accessible to
    //AppendToFile() when it attempts to automatically
    //reopen the file.
    
}

void loadSongsFromFile(LinkedList &playlist, long &length, std::fstream &playlistFile)
//This function should read text like the previous file readers,
//using slashes and newlines as separators.
//Saves songPath_ as the entire line.
//Saves songName_ as the remainder of the line after the last slash.
{
    std::string nameReader;
    char* nameHolder;
    char pathReader[ENTRY_SZ];
    Node* extractionNode; // this variable used only as a parameter in deleteAllSongs();
    
    deallocateEntireList(playlist, length, extractionNode); //call to recursive deletion function
    
    getFilePath();
    
    playlistFile.open(Song::songListFile_, std::ios::in);
    
    if (!playlistFile.is_open()) //File check
    {
        fileNotFound(); //deploys error message
        return;
    }
    if (playlistFile.is_open()) //File check
    {
        std::cout << "\nPlaylist opened succesfully." << std::endl;
    }
    
    while (!playlistFile.eof()) //Until end of file is reached...
    {
        nameReader = readAndAddSong(playlistFile, playlist); //...builds a song object based on each line in the file
    }
    
    playlistFile.close();
    playlistFile.clear(std::ios_base::goodbit);
    
    printPlaylist(playlist, length); //Provides an initial printout of the playlist,
    //which both confirms that the list has been constructed,
    //and is additionally convenient for copying and pasting
    
    return;
}

std::string readAndAddSong(std::fstream &playlistFile, LinkedList &playlist)
//Function to read a line of text and create a song object
{
    
    char* nameReader;
    std::string nameHolder = "";
    
    std::string pathHolder;
    char* pathReader;
    
    getline(playlistFile, pathHolder);
    
    pathReader = (char*)pathHolder.c_str();
    
    size_t i = pathHolder.rfind('/', pathHolder.length()); //This line is not compliant with Windows file paths.
    
    if (i != std::string::npos)
    {
        nameHolder = pathHolder.substr(i + 1, pathHolder.length() -1);
        nameReader = (char*)nameHolder.c_str();
        
        Song* songEntry = new Song(nameReader);
        songEntry->SetSongPath(pathReader);
        
//        std::cout << "nameReader is: " << nameReader << std::endl; //***DIAGNOSTIC***//
//        std::cout << "pathReader is: " << pathReader << std::endl; //***DIAGNOSTIC***//
        
        playlist.AddLinkToBack(songEntry);
    }
    
    if (nameHolder != pathHolder) //Condition for Windows compliance
    {
//        std::cout << "Backslash mode is firing\n"; //***DIAGNOSTIC***//
        char winSep = '\\'; //Backslash separator for windows filepaths
        size_t j = pathHolder.rfind(winSep, pathHolder.length());
        
        if (j != std::string::npos)
        {
            nameHolder = pathHolder.substr(j + 1, pathHolder.length() - 1);
            nameReader = (char*)nameHolder.c_str();
            
            Song* songEntry = new Song(nameReader);
            songEntry->SetSongPath(pathReader);
            
//            std::cout << "nameReader is: " << nameReader << std::endl; //***DIAGNOSTIC***//
//            std::cout << "pathReader is: " << pathReader << std::endl; //***DIAGNOSTIC***//
            
            playlist.AddLinkToBack(songEntry);
        }
    }
    
    return " ";
}

void addNewSong(LinkedList &playlist, long &length)
//adds a new song to the list based on user input from the console,
//accomplishes this by calling LinkedList class function AddLinkToBack(),
//and appends to file with Song class function AppendToListFile()
{
    char name[ENTRY_SZ];
    char path[ENTRY_SZ];
    void* vdSngPtr;
    
        if (length == 0)
        {
            noPlaylistLoaded(); //deploys error message
            return;
        }
    
    std::cout << "Please enter the filename of a song to be added to the list: " << std::endl;
    
    std::cin.ignore();
    std::cin.getline(name, ENTRY_SZ);
    
    Song* newSong = new Song(name);
    vdSngPtr = static_cast <void *> (newSong); //Static cast newSong to vdSngPtr.
    
    std::cout << "What is the full file path of " << name << "? " << std::endl;
    std::cin.getline(path, ENTRY_SZ);
    newSong->SetSongPath(path);
    
    playlist.AddLinkToBack(newSong);
    length++;
    
        newSong->AppendToListFile(); //Appends the new song to the playlist file
    
    
    return;
}

void deleteSingleSong(LinkedList &playlist, long &length)
//deletes a single song based on user input from the console
{
    Node* head = playlist.GetFirstNode();
    Node* current;
    Node* removal;
    
    bool songFound = false;

    char name[ENTRY_SZ];
    
//    char nameCheck[ENTRY_SZ];
    
    current = head;
    
    Song* songCheck = static_cast<Song*>(current->data_);
    const char* nameCheck = songCheck->GetSongName();
    
    if (length == 0)
    {
        noPlaylistLoaded(); //deploys error message
        return;
    }
    
    std::cout << "Please enter the filename of a song to be deleted (without path): " << std::endl;
    std::cin.ignore();
    std::cin.getline(name, ENTRY_SZ);
    
    for (int i = 0; i < length; i++)
    {
        
        songCheck = static_cast<Song*>(current->data_);
        nameCheck = songCheck->GetSongName();
        
        if(songFound == false) //checks to see if the song has been found
        {
            songCheck = static_cast<Song*>(current->data_);
            nameCheck = songCheck->GetSongName();
            
//            std::cout << "Name: " << name <<"\n"; //***DIAGNOSTIC: SERACH REPORT***//
//            std::cout << "nameCheck" << nameCheck <<"\n"; //***DIAGNOSTIC: SEARCH REPORT***//
            
            if (strcmp(name, nameCheck) == 0)
            {
                
                removal = current;
                
//                std::cout << "Match found! " << songCheck->GetSongName() << " identified for deletion." << std:: endl; //***DIAGNOSTIC: DELETION REPORT***//
                std::cout << "\n" << songCheck->GetSongName() << " has been removed from this playlist.\n" << std::endl;
                
                songFound = true; //songFound assigned as true; no further checks are made
            }
            else
            {
                current = current->next_; 
            }
            
        }

    }

    if (songFound == false) //checks to see if the song has been found
    {
        titleNotFound(); //deploys error message
        return;
    }
    
    playlist.RemoveThisLink(removal);
    length--;
    
    return;
}

void printPlayerString(LinkedList &playlist, long &length)
//Prints a string to represent the play function of the .mp3 player.
{
    if (length == 0)
    {
        noPlaylistLoaded(); //deploys error message
        return;
    }
    
    Node* head = playlist.GetFirstNode();
    Node* current;
    
    bool songFound = false;
    
    char name[ENTRY_SZ];
    
    //    char nameCheck[ENTRY_SZ];
    
    current = head;
    
    Song* songCheck = static_cast<Song*>(current->data_);
    const char* nameCheck = songCheck->GetSongName();
    
    std::cout << "Please enter the filename of a song to play (without path): " << std::endl;
    std::cin.ignore();
    std::cin.getline(name, ENTRY_SZ);
    
    for (int i = 0; i < length; i++)
    {
        
        songCheck = static_cast<Song*>(current->data_);
        nameCheck = songCheck->GetSongName();
        
        if(songFound == false)
        {
            songCheck = static_cast<Song*>(current->data_);
            nameCheck = songCheck->GetSongName();
            
//            std::cout << "Name: " << name <<"\n"; //***DIAGNOSTIC: SEARCH REPORT***//
//            std::cout << "nameCheck" << nameCheck <<"\n"; //***DIAGNOSTIC: SEARCH REPORT***//
            
            if (strcmp(name, nameCheck) == 0)
            {
                
                songCheck->PlaySong(); //song.h class function to mock 'play' the song
                
                songFound = true;  //songFound assigned as true; no further checks are made
            }
            else
            {
                current = current->next_;
            }
            
        }
        
    }
    
    if (songFound == false) //checks to see if the song has been found
    {
        titleNotFound(); //deploys error message
        return;
    }
    
    return;
}

void printPlaylist(LinkedList &playlist, long &length)
//Prints the titles of the songs on the current playlist
{
    length = playlist.GetListLength();
    Node* printerNode = playlist.GetFirstNode();
    Song* songPrinter;
    
    std::cout << "\nCurrent Playlist:" << std::endl;
    
    for (int i = 0; i < length; i++)
    {
        songPrinter = static_cast <Song *> (printerNode->data_); //Static cast the void pointer stored
        //in data_ back to a song pointer.
        
        std::cout << songPrinter->GetSongName() << "\n";
        
        printerNode = printerNode->next_;
    }
    
    std::cout << "\n";
    
    return;
}

void deallocateEntireList (LinkedList &playlist, long &length, Node* &extractionNode)
//Recursive function which directly deletes a song object,
//then destroys its node by calling RemoveLinkFromFront(),
//and ultimately calls itself to repeat the process, until termination.
{
    length = playlist.GetListLength();  //Check the current value of playlist.listLen_;
    
    extractionNode = playlist.GetFirstNode();  //Get the first node
    
    if (length  <= 0) //If the recursive loop is over...
    {
        return; //...terminate and return.
    }
    
    if (length > 0) //Otherwise...
    {
        
        Song* targetSong;
        targetSong = static_cast <Song*> (extractionNode->data_); //Cast void pointer back to song for deletion.
        
        Node* nextNode = extractionNode->next_; //establishes a node to use for the recursive call
        //before deletion of the current node occurs
        
        length--; //decrement length as items are deleted from the list
        delete targetSong; //delete the song;
        extractionNode->data_ = NULL;
        
//        std::cout << "deallocateEntireList() has deleted a song." << std::endl; //***DIAGNOSTIC: DELETION REPORT***//
        
        playlist.RemoveLinkFromFront(); //Calls this function to remove and delete nodes from the list.
       
        deallocateEntireList(playlist, length, nextNode); //Recursive call, using nextNode in place of extractionNode
        
    }
    
}
