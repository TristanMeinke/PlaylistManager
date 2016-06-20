//  Song.cpp
//  CS162Assignment4-mp3Player
//
//  Created by Tristan on 2/22/16.


#include "Song.h"

char Song::songListFile_[ENTRY_SZ] = "";
char Song::currentMP3_[ENTRY_SZ] = "";

Song::Song()
{
    
}

Song::Song(char* name)
//constructs a song object based on a name
{
    strcpy(songName_, name);
}

Song::~Song()
{
    
}

void Song::SetSongPath(char* path)
{
    strcpy(songPath_, path);
}

const char* Song::GetSongName()
{
    return songName_;
}

void Song::AppendToListFile()
//Appends the list file with user-entered data which has been added from the console
{
    std::fstream playlistFile;
    playlistFile.open(Song::songListFile_, std::ios_base::app); //Opens the file to be appended.

    
    if (playlistFile.is_open())
    {
        playlistFile << "\n" << songPath_;  //Appends the contents of songPath_ to the file
        
//        std::cout << "File appended." << std::endl; //***DIAGNOSTIC***//
    }
    
    playlistFile.close();
    playlistFile.clear(std::ios_base::goodbit);
    
}
void Song::PlaySong()
{
    std::cout << "\nCurrently Playing: " << songName_ << "\n" << std::endl;
}
void Song::StopSong()
{
    
}