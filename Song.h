//  Song.h
//  CS162Assignment4-mp3Player
//
//  Created by Tristan on 2/22/16.


#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>

#ifndef Song_h
#define Song_h

const int ENTRY_SZ = 512;

class Song
{
private:
    char songPath_[ENTRY_SZ];
    char songName_[ENTRY_SZ];
    
public:
    
    static char songListFile_[ENTRY_SZ];
    static char currentMP3_[ENTRY_SZ];

//    static void ClearListFile();
    
    Song();
    Song(char* name);
    ~Song();
    void SetSongPath(char* path);
    const char* GetSongName();
    void AppendToListFile();
    void PlaySong();
    void StopSong();
};



#endif /* Song_h */
