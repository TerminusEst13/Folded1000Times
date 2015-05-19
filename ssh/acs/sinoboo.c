#include "zcommon.acs"
#library "sinoboo"

#include "commonfuncs.h"

#include "sino_const.h"

//global int 58:LevelCount;
//global int 59:RunningInZandro;
//global int 60:RunningInZDoom;

str FontZ[2] ={"0","1"};

int playerTimers[PLAYERMAX][TIMER_COUNT];
int playerTimeFreeze[PLAYERMAX];
int ClientEnterLocks[PLAYERMAX];
int dodgeitem;
int IsServer;
int array_recoilrules[PLAYERMAX];
int array_autoswitch[PLAYERMAX];
int array_beepbeepbeep[PLAYERMAX];
int array_nopan[PLAYERMAX];
int array_noannounce[PLAYERMAX];
int flashlightOn[PLAYERMAX];
int NotADoomGame;

int GotShotgun;
int GotCarronade;
int GotUzi;
int GotHam; // HAM
int GotIronMaiden;
int GotLegion;
int GotFrosthammer;

function void DrawScanlines(void)
{
    int Y = Random(0, 240) << 16;
    int Alpha = FixedDiv(Random(25, 75), 100);
    
    // Scanlines
    SetFont("Line");
    HudMessage(s:"A"; HUDMSG_FADEOUT, 0, CR_WHITE, 0.0, Y, 0.05, 1.0, Alpha);
}

function void DrawBinary(void)
{
    int X = Random(0, 320) << 16;
    int Y = Random(0, 240 / 6) << 16;
    int FadeInTime = 0.1;
    int FadeOutTime = 0.25;
    int Rows = Random(10, 30);
    str Binary;
    
    for (int i = 0; i < Rows; i++)
    {
        if (Random(0, 1))
            Binary = "1";
        else
            Binary = "0";
        
        SetFont("CYBRFONT");
        HudMessage(s:Binary; HUDMSG_FADEINOUT, 0, CR_WHITE, X, Y, 0.05, FadeInTime, FadeOutTime, 0.75);
        
        FadeInTime += 0.1;
        FadeOutTime += 0.1;
        Y += 8.0;
    }
}

#include "sino_auto.h"
#include "sino_walljump.h"
#include "sino_spacejump.h"

script SINO_DECORATE (int pihua)
{
    int FontX;
    int FontY;
    int FontTim;

    switch (pihua)
    {
    case 0:
        GiveInventory("DodgeGhostOn",1);
		Delay(2);
		SetActorVelocity(0,0,0,0,0,1);
		Delay(2);
        GiveInventory("DodgeGhostOff",1);
        break;

    case 1:
        int Time = 52;
        while (Time > 0)
        {
          SetHudSize(320, 240, false);

          // Scanlines
          if ((Timer() % 3) == 0)
            DrawScanlines();

        // Binary
          if ((Timer() % 3) == 0)
            DrawBinary();

          SetFont("CYBRBIG");
          FontX = random(0.00,320.00);
          FontY = random(0.00,240.00);
          hudmessage (s:FontZ[random(0,1)],s:"\n";
          1, 0,CR_WHITE, FontX, FontY, 0.1);
          delay(1);

          Time--;
          Delay(1);
        }
    break;
    }
}

script SINO_RESPAWN respawn
{
    if (CheckInventory("IsJungHaeLin") == 1) { terminate; }

    // Death forcefully takes away all the player's remaining tokens (if killed
    // via divine intervention or freak accident or whatever), so respawning
    // hands over a fresh batch of tokens.
    if (GameSkill () == 0) { GiveInventory("ContraLifeToken",10); }
    if (GameSkill () == 1) { GiveInventory("ContraLifeToken",8);  }
    if (GameSkill () == 2) { GiveInventory("ContraLifeToken",6); }
    if (GameSkill () == 3) { GiveInventory("ContraLifeToken",4); }
    if (GameSkill () == 4) { GiveInventory("ContraLifeToken",2); }
    // Takes away a million points on respawn.
    // If you have at least ten million points, take ten million.
    // If you have a hundred million points, take a hundred million.
    // There's a better way to do this, but not with Zandro's 32xxx integeter limit.
    if (CheckInventory("OkuPoints") >= 1) { TakeInventory("OkuPoints",1); }
    else if (CheckInventory("ManPoints") >= 1000) { TakeInventory("ManPoints",1000); }
    else if (CheckInventory("ManPoints") >= 100) { TakeInventory("ManPoints",100); }
    else { TakeInventory("ManPoints",99); TakeInventory("Points",9999); }

    if (GetCvar("dst_debug") == 1) { Log(s:"Player ", d:PlayerNumber(), s:" respawning, executing SINO_ENTER."); }
    ACS_ExecuteAlways(SINO_ENTER,0,0,0);
    ACS_ExecuteAlways(SINO_ENTER_UNREPLACED,0,0,0);
    ACS_ExecuteAlways(SINO_DOUBLEJUMP,0,0,0);
}

script SINO_UNLOADING unloading
{
    TakeInventory("KickJumped",1);
    TakeInventory("GrabbingTheWall",1);
    TakeInventory("Grappling",1);
    TakeInventory("SynthFire",1);
    TakeInventory("GrenadePunchHitWall",1);
    TakeInventory("GrenadePunchHit",1);
    TakeInventory("TriumphSwung",1);

    TakeInventory("PunchComboCounter",0x7FFFFFFF);
    TakeInventory("GrenadeTimer",0x7FFFFFFF);
    TakeInventory("WallGrabbed",0x7FFFFFFF);
}

script 583 (int x, int y, int z)
{
    if (GetActorZ(0) - GetActorFloorZ(0) > 4.0)
    {
        SetResultValue(1);
    }
    else
    {
        SetResultValue(zan_sqrt(x*x + y*y + z*z) );
    }
}