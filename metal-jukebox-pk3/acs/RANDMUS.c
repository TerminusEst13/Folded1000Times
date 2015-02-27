#include "zcommon.acs"
#library "RANDMUS"

#include "commonFuncs.h" // Even in making a silly music randomizer mod, I require ijon's funcs.

int MusicRandomizerOn;
int MusicInfo;
int MusicCurrentSong;

#define SONGSTR_INFO 1
#define SONGSTR_SONG 0

function int getSongStr(int SongNumber, int Type)
{
  // if the song amount ever goes over 1000, uncomment everything but this line ...
  int OneZero = "0"; int TwoZeros = "00"; // int ThreeZeros = "000";
  int PrefixString;
  int OutputString;
  
  if(Type == SONGSTR_INFO) {
    PrefixString = "JUKEBOX_";
  } else if(Type == SONGSTR_SONG) {
    PrefixString = "Song";
  } else {
    PrefixString = "OhGodThisIsAnError";
  }
  
  // ... and remove these blocks
  if(SongNumber <= 9)
  { // if it's less than 10 (1 digit, two zeros)
    OutputString = StrParam(s:PrefixString, s:TwoZeros, d:SongNumber); // concatenate the prefix, two zeros, and the number
  }
  else if(SongNumber <= 99)
  { // if it's less than 100 (2 digits, one zero)
    OutputString = StrParam(s:PrefixString, s:OneZero, d:SongNumber); // concatenate the prefix, one zero, and the number
  }
  else
  { // if it's over 100
    OutputString = StrParam(s:PrefixString, d:SongNumber); // concatenate the prefix and the number
  }
  
  return OutputString;
}

function int getMaxRandSong(void)
{
  int temp;
  int i;
  
  for(i = 1; i < 9999; i++) { // Please do not use more than 9999 songs.
    temp = getSongStr(i, SONGSTR_INFO); // Compare the string and the language text, if they're the same it's the last one.
    if(CStrCmp(temp, StrParam(l:temp)) == 1) {
      return i - 1;
    }
  }
  
  return -1;
}

Script 346 OPEN NET clientside
{
  int i;
  int randomhack;
  int lastmus;
  
  if(GetCvar("norandommusic") == 0)
  {
    MusicRandomizerOn = 1;
    
    if(GetCvar("mus_runninginzdoom") == 1)
    {
      i = random(1, getMaxRandSong());
      SetMusic(getSongStr(i, SONGSTR_SONG),0);
      MusicCurrentSong = i;
    }
    else
    {
      // Zandronum is funny about this. Online, it generates the same random seed every
      // time, even though that's the opposite of what you'd expect from a random call.
      // I have to use a workaround to generate pseudo-random behavior.
      // But it's better than dealing with ZDoom's barely-functional slapshod netcode!
      
      // [marrub] The reason this happens is the C/S code wants to be extra-deterministic
      // so everyone gets the same (P)RNG. This is a guess. Please don't hit me, Dusk.
      // Also on ZDoom everyone knows they have the same PRNG so there's no worry there.
      
      randomhack = defaultCVar("mus_cl_randomhack", 0);
      lastmus    = defaultCVar("mus_cl_lastmusic",  0) - 1;
      
      for (i = 0; i < randomhack; i++) { random(0, 1); }
      randomhack = random(0, 500);
      SaveCVar("mus_cl_randomhack", randomhack);
      
      do { i = random(1, getMaxRandSong()); }
      while (i == lastmus);
      
      SetMusic(getSongStr(i, SONGSTR_SONG), 0);
      MusicCurrentSong = i;
      SaveCVar("mus_cl_lastmusic", i);
    }
    
    Delay(35);
    
    if(GetCvar("nomusicinfo") == 0)
    {
      MusicInfo = getSongStr(i, SONGSTR_INFO);
      if(CStrCmp(MusicInfo, StrParam(l:MusicInfo)) != 1) { // This compares the info with the language text it's associated with
        SetFont("SmallFont");                        // If it's the same, there is no language text associated with it, thus we should not print it
        hudmessage(l:MusicInfo; HUDMSG_FADEINOUT | HUDMSG_LOG, 153, CR_WHITE, 0.1, 0.8, 3.0, 0.5, 1.0);
      }
    }
  }
  else
  {
    MusicRandomizerOn = 0;
  }
}

script 347 OPEN clientside
{
  delay(1);
  
  if(GetCvar("mus_runninginzdoom") == 0) // No option to disable on ZDoom because I'm pretty sure the only way this'll
  {                                      // be happening is when you manually load it, ergo want to listen to it...
    if(!GetCvar("norandommusic"))
    {
      ConsoleCommand("set norandommusic 0");
      ConsoleCommand("archivecvar norandommusic");
    }
    
    if(!GetCvar("nomusicinfo"))
    {
      ConsoleCommand("set nomusicinfo 0");
      ConsoleCommand("archivecvar nomusicinfo");
    }
  }
}

script 348 (int musicshit) NET clientside // Hitting "Next Song".
{
  int i;
  int randomhack;
  int lastmus;

  switch (musicshit)
  {
    case 0:
      SetMusic("silence");
      LocalAmbientSound("music/shift",127);
      Delay(35);
      if (GetCvar("norandommusic") == 0)
      {
        MusicRandomizerOn = 1;
        if (GetCvar("mus_runninginzdoom") == 1)
        {
          i = random(1, getMaxRandSong());
          SetMusic(getSongStr(i, SONGSTR_SONG),0);
          MusicCurrentSong = i;
        }
        else
        {
          randomhack = defaultCVar("mus_cl_randomhack",   0);
          lastmus    = defaultCVar("mus_cl_lastmusic",    0) - 1;
          
          for (i = 0; i < randomhack; i++) { random(0, 1); }
          randomhack = random(0, 500);
          SaveCVar("mus_cl_randomhack", randomhack);
          
          do { i = random(1, getMaxRandSong()); }
          while (i == lastmus);
          
          SetMusic(getSongStr(i, SONGSTR_SONG), 0);
          MusicCurrentSong = i;
          SaveCVar("mus_cl_lastmusic", i + 1);
        }
        if (GetCvar("nomusicinfo") == 0)
        {
          MusicInfo = getSongStr(i, SONGSTR_INFO);
          if(CStrCmp(MusicInfo, StrParam(l:MusicInfo)) != 1)
          {
            SetFont("SmallFont");
            hudmessage(l:MusicInfo; HUDMSG_FADEINOUT | HUDMSG_LOG, 153, CR_WHITE, 0.1, 0.8, 3.0, 0.5, 1.0);
          }
        }
      }
      else
      {
        MusicRandomizerOn = 0;
        SetMusic("*",0);
      }
      break;

    case 1: // Hitting "Default Song".
      SetMusic("silence");
      LocalAmbientSound("music/shift",127);
      Delay(35);
      SetMusic("*",0);
      break;
  }
}

script 349 (int fuckery) NET clientside // Manually changing the song
{
  if(fuckery > 0)
  {
    if(GetCvar("norandommusic") == 0)
    {
      SetMusic("silence");
      LocalAmbientSound("music/shift",127);
      Delay(35);
      
      MusicRandomizerOn = 1;
      if(GetCvar("mus_runninginzdoom") == 1)
      {
        SetMusic(getSongStr(fuckery, SONGSTR_SONG),0);
        MusicCurrentSong = fuckery;
      }
      else
      {
        SetMusic(getSongStr(fuckery, SONGSTR_SONG), 0);
        MusicCurrentSong = fuckery;
      }
      
      if(GetCvar("nomusicinfo") == 0)
      {
        MusicInfo = getSongStr(fuckery, SONGSTR_INFO);
        if(CStrCmp(MusicInfo, StrParam(l:MusicInfo)) != 1) { // This compares the info with the language text it's associated with
          SetFont("SmallFont");                        // If it's the same, there is no language text associated with it, thus we should not print it
          hudmessage(l:MusicInfo; HUDMSG_FADEINOUT | HUDMSG_LOG, 153, CR_WHITE, 0.1, 0.8, 3.0, 0.5, 1.0);
        }
      }
    }
    else
    {
      MusicRandomizerOn = 0;
    }
  }
}
