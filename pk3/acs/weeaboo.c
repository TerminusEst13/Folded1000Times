#include "zcommon.acs"
#library "weeaboo"

#include "commonfuncs.h"
#include "weeb_const.h"

global int 58:LevelCount;

int playerTimers[PLAYERMAX][TIMER_COUNT];
int ClientEnterLocks[PLAYERMAX];
int dodgeitem;
int IsServer;
int array_recoilrules[PLAYERMAX];

int GotShotgun;
int GotCarronade;
int GotUzi;
int GotHam; // HAM

int IronMaidenMusic[IRONMUS] = 
{ "D_IRONM1","D_IRONM2","D_IRONM3","D_IRONM4","D_IRONM5","D_IRONM6","D_IRONM7" };



script WEEB_RESPAWN respawn
{
    if (GameSkill () == 0) { GiveInventory("ContraLifeToken",10); }
    if (GameSkill () == 1) { GiveInventory("ContraLifeToken",8);  }
    if (GameSkill () == 2) { GiveInventory("ContraLifeToken",6); }
    if (GameSkill () == 3) { GiveInventory("ContraLifeToken",4); }
    if (GameSkill () == 4) { GiveInventory("ContraLifeToken",2); }
    
    ACS_ExecuteAlways(268,0,0,0);
    //ACS_ExecuteAlways(269,0,0,0);
}

script WEEB_OPEN OPEN
{
    IsServer = 1;
    LevelCount++;

    if (GetCvar("ds_runninginzdoom") == 0)
    {
        if (!GetCvar("compat_clientssendfullbuttoninfo"))
            { ConsoleCommand("set compat_clientssendfullbuttoninfo 1"); }

        if (!GetCvar("ds_noshotgunlimiter"))
            { ConsoleCommand("set ds_noshotgunlimiter 0");
              ConsoleCommand("archivecvar ds_noshotgunlimiter 0"); }

        if (!GetCvar("ds_noshotgun"))
            { ConsoleCommand("set ds_noshotgun 0");
              ConsoleCommand("archivecvar ds_noshotgun 0"); }
    }
}

script WEEB_OPEN_CLIENT OPEN clientside
{
    delay(1);
    if (GetCvar("ds_runninginzdoom") == 0)
    {
        if (!GetCvar("ds_cl_nomusic"))
            { ConsoleCommand("set ds_cl_nomusic 0");
              ConsoleCommand("archivecvar ds_cl_nomusic"); }

        if (!GetCvar("ds_cl_norecoil"))
            { ConsoleCommand("set ds_cl_norecoil 0");
              ConsoleCommand("archivecvar ds_cl_norecoil"); }
    }
}

script WEEB_DECORATE (int burrshet)
{
    switch (burrshet)
    {
    case WEEB_DEC_DAMAGE:
        int delaytotal = 104;
        int delaytimer = delaytotal;
        int delaytime = 10;
        int delaycount = 0;

        if (CheckInventory("PowerShieldProtection") == 1) { terminate; }
        
        if (CheckInventory("ContraArmorToken") >= 1)
            { TakeInventory("ContraArmorToken",1); TakeInventory("HyperComboCounter",25); }
        else if (CheckInventory("OverLifeToken") >= 1)
            { TakeInventory("OverLifeToken",1); TakeInventory("HyperComboCounter",50); }
        else if (CheckInventory("ContraLifeToken") >= 1)
            { TakeInventory("ContraLifeToken",1); TakeInventory("HyperComboCounter",50); }
        
        SetActorProperty(0,APROP_INVULNERABLE,1);
        
        while (delaytimer > 0)
        {
            if (delaytimer % 2)
                SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
            else
                SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
            
            delaytimer--;
            delaycount++;
            if (delaycount > 1)
            {
                delaytime--;
                delaycount = 0;
            }
            
            Delay(delaytime);
        }
        
        SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Normal);
        SetActorProperty(0,APROP_INVULNERABLE,0);
    break;

    case WEEB_DEC_FREEZE:
        SetActorProperty(0,APROP_Species,"Body");
        SetPlayerProperty(0,1,PROP_TOTALLYFROZEN);
        break;

    case WEEB_DEC_UNFREEZE:
        if (GameType() == GAME_NET_DEATHMATCH) { SetActorProperty(0,APROP_Species,"DMPlayer"); }
        else { SetActorProperty(0,APROP_Species,"Player"); }
        SetPlayerProperty(0,0,PROP_TOTALLYFROZEN);
        break;

    case WEEB_DEC_SHOTCHECK:
        if (isSinglePlayer() && GotShotgun == 1) { SetResultValue(1); }
        else { SetResultValue(0); }
        break;

    case WEEB_DEC_CARRCHECK:
        if (isSinglePlayer() && GotCarronade == 1) { SetResultValue(1); }
        else { SetResultValue(0); }
        break;

    case WEEB_DEC_UZICHECK:
        if (isSinglePlayer() && GotUzi == 1) { SetResultValue(1); }
        else { SetResultValue(0); }
        break;

    case 6:
        GiveInventory("DodgeGhostOn",1);
        Delay(18);
        GiveInventory("DodgeGhostOff",1);
        break;

    case WEEB_DEC_MEGASPHERE:
        GiveInventory("ContraArmorToken",4);
        if (GameSkill () == 0)
        {
          if (CheckInventory("ContraLifeToken") < 10) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 10) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 10) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 10) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 10) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 10) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 10) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 10) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 10) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 10) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 4) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 4) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 4) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 4) { GiveInventory("OverLifeToken",1); }
        }
        if (GameSkill () == 1)
        {
          if (CheckInventory("ContraLifeToken") < 8) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 8) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 8) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 8) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 8) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 8) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 8) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 8) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 4) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 4) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 4) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 4) { GiveInventory("OverLifeToken",1); }
        }
        if (GameSkill () == 2)
        {
          if (CheckInventory("ContraLifeToken") < 6) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 6) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 6) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 6) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 6) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 6) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 3) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 3) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 3) { GiveInventory("OverLifeToken",1); }
        }
        if (GameSkill () == 3)
        {
          if (CheckInventory("ContraLifeToken") < 4) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 4) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 4) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 4) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 3) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 3) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 3) { GiveInventory("OverLifeToken",1); }
        }
        if (GameSkill () == 4)
        {
          if (CheckInventory("ContraLifeToken") < 2) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("ContraLifeToken") < 2) { GiveInventory("ContraLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 2) { GiveInventory("OverLifeToken",1); }
          if (CheckInventory("OverLifeToken") < 2) { GiveInventory("OverLifeToken",1); }
        }
        if (GameSkill () == 5)
        {
          if (CheckInventory("OverLifeToken") < 1) { GiveInventory("OverLifeToken",1); }
        }
        break;

    case WEEB_DEC_WEPSTAY:
        SetResultValue(!!GetCVar("sv_weaponstay"));
        break;

    case WEEB_DEC_HAMCHECK: // HAAAAAM
        if (isSinglePlayer() && GotHam == 1) { SetResultValue(1); } // HAAAAAAAAAM
        else { SetResultValue(0); } // HAAAAAAAAAAAAAAAAAAAAAAM
        break;

    case WEEB_DEC_HAMAMMO1: // HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAM
        SetAmmoCapacity("HammerCharge",200);
        break;

    case WEEB_DEC_HAMAMMO2: // HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAM
        SetInventory("HammerCharge",80);
        SetAmmoCapacity("HammerCharge",100);
        break;

    case WEEB_DEC_HAMAMMO3: // HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAM
        SetInventory("HammerCharge",0);
        SetAmmoCapacity("HammerCharge",100);
        break;

    case WEEB_DEC_FREEZE2:
        SetPlayerProperty(0,1,PROP_TOTALLYFROZEN);
        break;

    case WEEB_DEC_UNFREEZE2:
        SetPlayerProperty(0,0,PROP_TOTALLYFROZEN);
        break;

    case WEEB_DEC_REMOVEKEBAB:
        FadeRange(255,255,255,1.00,0,0,0,0,1.50);
        TakeInventory("HenshinDeactivation",1);
        TakeInventory("InIronMaiden",1);
        TakeInventory("Iron Fist",1);
        TakeInventory("IronMaidenSpeed",1);
        TakeInventory("Armor",0x7FFFFFFF);
        TakeInventory("HenshinActivated",1);
        GiveInventory("Kharon + Acacia A-22",1);
        SetActorProperty(0,APROP_JUMPZ,9.0);
        if (CheckInventory("GotShotgun") == 1) { GiveInventory("Kharon + Testament",1); }
        if (CheckInventory("GotUzi") == 1) { GiveInventory("Kharon + Sabbath",1); }
        if (CheckInventory("GotCarronade") == 1) { GiveInventory("Kharon + Exodus",1); }
        if (CheckInventory("GotHammer") == 1) { GiveInventory("Kharon + Omen",1); }
        SetWeapon("Kharon + Acacia A-22");
        ACS_ExecuteAlways(275,0,WEEB_DEC_CHANGEMUSBACK,0,0);
        delay(1);
        TakeInventory("IronMaidenArmor",0x7FFFFFFF);
        TakeInventory("IronMaidenArmor2",0x7FFFFFFF);
        break;

    case WEEB_DEC_DIFFCHECK:
        if (GameSkill () == 5) { SetResultValue(1); }
        else { SetResultValue(0); }
        break;

    case WEEB_DEC_ONLINECHECK:
        if ( (GetCvar("ds_noshotgunlimiter") == 0 && LevelCount < 2) || GetCvar("ds_noshotgun") == 1) { SetResultValue(1); }
        else { SetResultValue(0); }
        break;

    case WEEB_DEC_HENSHIN:
        delay(10);
        TakeInventory("HenshinActivated",1);
        break;
    }
}

script WEEB_CLIENTDECORATE (int boreshut, int bowlshot) clientside
{
    if (ConsolePlayerNumber() != PlayerNumber()) { terminate; } 

    switch (boreshut)
    {
    case WEEB_DEC_GETMESSAGES:
        switch (bowlshot)
        {
        case 0:
          Log(s:"\cfThe \cjTestament \cfshotgun. You may wield it...");
          break;

        case 1:
          Log(s:"\cfThe \cjExodus \cfgrenade launcher. You may wield it...");
          break;

        case 2:
          Log(s:"\cfThe \cjSabbath \cfsubmachine gun. You may wield it...");
          break;

        case 3:
          Log(s:"\cfThe \cjOmen \cfwarhammer. You may wield it...");
          break;
        }
        break;

    case WEEB_DEC_CHANGEMUS:
	    int i = random(0, IRONMUS-1);
	    if(getcvar("ds_cl_nomusic") == 0) { LocalSetMusic(IronMaidenMusic[i],0); }
        break;

    case WEEB_DEC_CHANGEMUSBACK:
	    if(getcvar("ds_cl_nomusic") == 0) { LocalSetMusic("*"); }
        break;
    }
}

script WEEB_ENTER ENTER
{
    int OldButtons;
    int Buttons;
    int SuperCount;
    int ComboCount;
    int KurtAngle;
    int WalkTheDinosaur;
    int RideTheLightning;
    int XMen;
    int Ys;
    int XMen2;
    int Ys2;
    int IsBrutal = 0;
    int mytid;
    int i, j, k, ang;
    int MarchOfTheImmortal;
    int IronArmor;
    int armor;
    int oarmor;
    int pln = PlayerNumber();
    i = unusedTID(37000, 47000);

    if (CheckInventory("ImAlive") == 0)
    {
        if (GameSkill () == 0) { GiveInventory("BabyMarker",1); GiveInventory("ContraLifeToken",10); }
        if (GameSkill () == 1) { GiveInventory("EasyMarker",1); GiveInventory("ContraLifeToken",8);  }
        if (GameSkill () == 2) { GiveInventory("NormalMarker",1); GiveInventory("ContraLifeToken",6); }
        if (GameSkill () == 3) { GiveInventory("HardMarker",1); GiveInventory("ContraLifeToken",4); }
        if (GameSkill () == 4) { GiveInventory("NightmareMarker",1); GiveInventory("ContraLifeToken",2); }
        FadeRange(0,0,0,1.00,0,0,0,0,3.50);
        LocalAmbientSound("level/intro",127);
        GiveInventory("ImAlive",1);
    }

    if (Spawn("Brutal_Blood", GetActorX(0), GetActorY(0), GetActorZ(0), i) || Spawn("BrutalPistol", GetActorX(0), GetActorY(0), GetActorZ(0), i))
    {
        Thing_Remove(i);
        isbrutal = 1;
    }

    SetActorProperty(0,APROP_INVULNERABLE,0); // Just in case some wiseass exits while invuln.
    SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Normal);
    if (GameType() == GAME_NET_DEATHMATCH) { SetActorProperty(0,APROP_Species,"DMPlayer"); }
    else { SetActorProperty(0,APROP_Species,"Player"); }
    SetPlayerProperty(0,0,PROP_TOTALLYFROZEN);
    GiveInventory("NewLevelStatReset",1);
    if (CheckInventory("HammerCharge") > 100) { SetAmmoCapacity("HammerCharge",100); SetInventory("HammerCharge",80); }
    if (CheckInventory("InIronMaiden") == 1) { ACS_ExecuteAlways(275,0,WEEB_DEC_CHANGEMUS,0,0); }
    
    while (1)
    {

        mytid = defaultTID(-1);
        //if (CheckInventory("ImAlive") == 1) { if (ConsolePlayerNumber() != PlayerNumber()) { terminate; } }

        XMen2 = XMen;
        Ys2   = Ys;
        XMen  = GetActorX(0);
        Ys    = GetActorY(0);

        if ((XMen2 == XMen) && (Ys2 == Ys)) { GiveInventory("WaitingTooLong",1); } else { TakeInventory("WaitingTooLong",0x7FFFFFFF); }

        // I will not make a Hammertime joke. I will not make a Hammertime joke. I will not make a Hammertime joke.
        if (CheckInventory("HammerUp") == 1)
        {
           if (CheckInventory("HammerCharge") >= 90 && CheckInventory("HammerCharge") <= 100 )
               { if (RideTheLightning >= 18) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") > 100)
               { if (RideTheLightning >= 8) { GiveInventory("HammerCharge",1); GiveInventory("ChargeScreenFlash",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 80)
               { if (RideTheLightning >= 25) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 60)
               { if (RideTheLightning >= 20) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 40)
               { if (RideTheLightning >= 15) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 20)
               { if (RideTheLightning >= 10) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 0)
               { if (RideTheLightning >= 5)  { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
        }
        else { if (RideTheLightning >= 40 && CheckInventory("HammerCharge") >= 30)  { TakeInventory("HammerCharge",1); RideTheLightning = 0; }}
        RideTheLightning++;

        TakeInventory("GhostStepCooldown",1);
        TakeInventory("DoubleTapCooldown",1);
        TakeInventory("EnviroDamageCooldown",1);
        TakeInventory("DoubleTapReadyRight",1);
        TakeInventory("DoubleTapReadyForward",1);
        TakeInventory("DoubleTapReadyLeft",1);
        TakeInventory("DoubleTapReadyBack",1);
        TakeInventory("MidCombat",1);
        TakeInventory("HenshinCooldown",1);
        if (CheckInventory("EnviroDamageCooldown") == 0) { TakeInventory("EnviroDamageCount",3); }
    
        // If the player still has life left, they get full health.
        if (CheckInventory("ContraLifeToken") >= 1 || CheckInventory("OverLifeToken") >= 1 || CheckInventory("ContraArmorToken") >= 1)
        { GiveInventory("999Health",999); }
        else
        { SetActorProperty(0,APROP_HEALTH,1); }

        // Not the kind you lean on.
        SuperCount = CheckInventory("SuperMeterCounter");
        //SetInventory("SuperCounter1",SuperCount); // Life would be so much easier if this worked online.
        TakeInventory("SuperCounter1", 0x7FFFFFFF);
        GiveInventory("SuperCounter1", SuperCount);
        if (CheckInventory("SuperMeterCounter") > 100) { TakeInventory("SuperCounter2",0x7FFFFFFF); GiveInventory("SuperCounter2", SuperCount - 100); } //SetInventory("SuperCounter2",(SuperCount - 100)); }
            else { TakeInventory("SuperCounter2",0x7FFFFFFF); }
        if (CheckInventory("SuperMeterCounter") > 200) { TakeInventory("SuperCounter3",0x7FFFFFFF); GiveInventory("SuperCounter3", SuperCount - 200); } //SetInventory("SuperCounter3",(SuperCount - 200)); }
            else { TakeInventory("SuperCounter3",0x7FFFFFFF); }
        if (CheckInventory("SuperMeterCounter") > 300) { TakeInventory("SuperCounter4",0x7FFFFFFF); GiveInventory("SuperCounter4", SuperCount - 300); } //SetInventory("SuperCounter3",(SuperCount - 200)); }
            else { TakeInventory("SuperCounter4",0x7FFFFFFF); }

        // 666 COMBO! SUPER SWEET STYLISH!
        ComboCount = CheckInventory("HyperComboCounter");
        TakeInventory("ComboCounter1",0x7FFFFFFF);
        GiveInventory("ComboCounter1",ComboCount);
        if (CheckInventory("HyperComboCounter") <= 50) { TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); }
        if (CheckInventory("HyperComboCounter") > 50)
            { TakeInventory("ComboCounter2",0x7FFFFFFF); GiveInventory("ComboCounter2",(ComboCount - 50)); GiveInventory("ComboDamageLevel1",1);
              GiveInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter2",0x7FFFFFFF); TakeInventory("ComboDamageLevel1",0x7FFFFFFF); }
        if (CheckInventory("HyperComboCounter") > 100)
            { TakeInventory("ComboCounter3",0x7FFFFFFF); GiveInventory("ComboCounter3",(ComboCount - 100)); GiveInventory("ComboDamageLevel2",1);
              TakeInventory("FRank",1); GiveInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter3",0x7FFFFFFF); TakeInventory("ComboDamageLevel2",0x7FFFFFFF); }
        if (CheckInventory("HyperComboCounter") > 150)
            { TakeInventory("ComboCounter4",0x7FFFFFFF); GiveInventory("ComboCounter4",(ComboCount - 150)); GiveInventory("ComboDamageLevel3",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); GiveInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter4",0x7FFFFFFF); TakeInventory("ComboDamageLevel3",0x7FFFFFFF); }
        if (CheckInventory("HyperComboCounter") > 200)
            { TakeInventory("ComboCounter5",0x7FFFFFFF); GiveInventory("ComboCounter5",(ComboCount - 200)); GiveInventory("ComboDamageLevel4",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); GiveInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter5",0x7FFFFFFF); TakeInventory("ComboDamageLevel4",0x7FFFFFFF); }
        if (CheckInventory("HyperComboCounter") > 250)
            { TakeInventory("ComboCounter6",0x7FFFFFFF); GiveInventory("ComboCounter6",(ComboCount - 250)); GiveInventory("ComboDamageLevel5",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); GiveInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter6",0x7FFFFFFF); TakeInventory("ComboDamageLevel5",0x7FFFFFFF); }
        if (CheckInventory("HyperComboCounter") > 300)
            { TakeInventory("ComboCounter7",0x7FFFFFFF); GiveInventory("ComboCounter7",(ComboCount - 300)); GiveInventory("ComboDamageLevel6",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); GiveInventory("SRank",1); } else { TakeInventory("ComboCounter7",0x7FFFFFFF); TakeInventory("ComboDamageLevel6",0x7FFFFFFF); }

        // Global variables
        if (isSinglePlayer())
        {
            if (CheckInventory("GotShotgun") == 1) { GotShotgun = 1; }
            if (CheckInventory("GotCarronade") == 1) { GotCarronade = 1; }
            if (CheckInventory("GotUzi") == 1) { GotUzi = 1; }
            if (CheckInventory("GotHammer") == 1) { GotHam = 1; } // HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAM
        }

        OldButtons = GetPlayerInput(-1, INPUT_OLDBUTTONS);
        Buttons = GetPlayerInput(-1, INPUT_BUTTONS);
        KurtAngle = GetActorAngle(0) >> 8;

        if (keypressed(BT_MOVERIGHT))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyRight") >= 1) { GiveInventory("DoubleTapRight",1); GiveInventory("DoubleTapCooldown",20); }
                      else { GiveInventory("DoubleTapReadyRight",8); }}}
        if (keypressed(BT_MOVELEFT))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyLeft") >= 1) { GiveInventory("DoubleTapLeft",1); GiveInventory("DoubleTapCooldown",20); }
                      else { GiveInventory("DoubleTapReadyLeft",8); }}}
        if (keypressed(BT_FORWARD))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyForward") >= 1) { GiveInventory("DoubleTapForward",1); GiveInventory("DoubleTapCooldown",20); }
                      else { GiveInventory("DoubleTapReadyForward",8); }}}
        if (keypressed(BT_BACK))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyBack") >= 1) { GiveInventory("DoubleTapBack",1); GiveInventory("DoubleTapCooldown",20); }
                      else { GiveInventory("DoubleTapReadyBack",8); }}}

    // This block of code was done by Kyle873.
    // He wishes me to inform you that ACS is a pile of cocks that owes him money.
    // If ACS ever met him IRL for a 1v1 fite, he would totally kick ACS' ass.
    // He has a blackbelt in punchyourshitology and got a masters in ohgodmyfuckingkneecapsjutsu.
    // Unfortunately ACS is a bitch pussy and never returns his calls.
    // But he is waiting. Oh, yes, he is waiting.
        WalkTheDinosaur = GetActorZ(0) - GetActorFloorZ(0);        
        //print(f:WalkTheDinosaur, s:" ", f:GetActorVelZ(0), s:"\n", d:CheckInventory("OnTheGround"), s:" ", d:CheckInventory("AcesHigh"));
        // Floor check
        if (GetActorZ(0) - GetActorFloorZ(0) == 0)
        {
              GiveInventory("OnTheGround", 1);
              TakeInventory("GhostStepDone",1); 
        }
        else
            { TakeInventory("OnTheGround", 1); }
        // Double Jump
        if (GetActorVelZ(0) <= 8 && !CheckInventory("OnTheGround") && !CheckInventory("AcesHigh") && keypressed(BT_JUMP) && GetCvar("sv_nojump") == 0)
        {
            ActivatorSound("ghost/jump", 127);
            if (CheckInventory("InIronMaiden") == 0 ) { ThrustThingZ(0,36,0,0); } else { ThrustThingZ(0,48,0,0); }
            GiveInventory("AcesHigh", 1);
        }
        // Remove AcesHigh when we're back on the ground
        if (CheckInventory("OnTheGround") && CheckInventory("AcesHigh"))
            TakeInventory("AcesHigh", 1);
    // This concludes the block of code done by Kyle873.
    // You may now applaud his genius.

        // Dodging
        if (CheckInventory("GhostStepCooldown") == 0 && CheckInventory("GhostStepDone") == 0)
        { if (buttons & BT_SPEED && buttons & BT_FORWARD) {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(KurtAngle+0,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(KurtAngle+0,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35);
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0); }
          if (buttons & BT_SPEED && buttons & BT_MOVELEFT) {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(KurtAngle+64,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(KurtAngle+64,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0); }
          if (buttons & BT_SPEED && buttons & BT_BACK) {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(KurtAngle+128,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(KurtAngle+128,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0); }
          if (buttons & BT_SPEED && buttons & BT_MOVERIGHT) {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(KurtAngle+192,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(KurtAngle+192,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0); }
        }

        // SUPER SAIYAN HNNNNNNGGGGGGGGGGGGGGGGGGGGGHHHHHHHHHHH
        // HHHHHHHNNNNNNNNNNGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
        // HHHHHHHHHHHHHHHHHHNNNNNNNNNNNNNNNNNNNNNNNNNNNGGGGGGGGGGHHHHHHHH

        oarmor = armor;
        armor = CheckInventory("Armor");

        if (oarmor > armor && CheckInventory("InIronMaiden") == 1)
        {
          ActivatorSound("iron/armorhit", 127);
          FadeRange(255,255,0,min(0.5,(oarmor-armor)*0.015),0,0,0,0.0,min(35.0,1.5*(oarmor-armor))/35); 
        }

        if (CheckInventory("InIronMaiden") == 1)
        {
          if (CheckInventory("SuperMeterCounter") > 0)
          {
            SetActorProperty(0,APROP_JUMPZ,10.0);

            if (CheckInventory("HenshinDeactivation") == 1)
            {
              GiveInventory("HenshinCooldown",35);
              LocalAmbientSound("henshin/complete",127);
              ActivatorSound("henshin/completedismiss",127);
              ACS_ExecuteWithResult(WEEB_DECORATE,WEEB_DEC_REMOVEKEBAB,0,0);
              MarchOfTheImmortal = 0;
              IronArmor = 0;
            }

            if (IronArmor >= 7)
            {
              GiveInventory("IronMaidenArmor",1);
              IronArmor = 0;
            }

            if (MarchOfTheImmortal >= 14)
            {
              TakeInventory("SuperMeterCounter",1);
              MarchOfTheImmortal = 0;
            }

            MarchOfTheImmortal++;
            IronArmor++;
          }
          else
          {
            GiveInventory("HenshinCooldown",35);
            LocalAmbientSound("henshin/timeout",127);
            ActivatorSound("henshin/timeoutdismiss",127);
            ACS_ExecuteWithResult(WEEB_DECORATE,WEEB_DEC_REMOVEKEBAB,0,0);
            MarchOfTheImmortal = 0;
            IronArmor = 0;
          }
        }
        

        // Brutal Doom compatibility provided by ijon tichy!
        if (isbrutal)
        {
            k = unusedTID(23000, 33000);

            for (i = 0; i < 4; i++)
            {
                ang = random(0, 1.0);
                j = 0;

                while (!Spawn("GetThatShitOutOfHere", GetActorX(0) + (8192 * sin(ang)),
                                                      GetActorY(0) + (8192 * cos(ang)),
                                                      GetActorZ(0) + j, k)
                    && (j < 256.0))
                {
                    j += 16.0;
                }
            }

            Thing_Hate(k, mytid, 2);
            Thing_ChangeTID(k, 0);
        }

        if (array_recoilrules[pln]) { GiveInventory("IAmASillyPersonWhoDoesntLikeRecoil", 1); }
        else { TakeInventory("IAmASillyPersonWhoDoesntLikeRecoil", 0x7FFFFFFF); }

        Delay(1);
        if (isDead(0)) { terminate; }
    }
}

script WEEB_DOUBLETAP ENTER
{
    while (1)
    {
        if (CheckInventory("DoubleTapForward") || CheckInventory("DoubleTapLeft") || CheckInventory("DoubleTapRight") || CheckInventory("DoubleTapBack") )
        {
            Delay(13);
            TakeInventory("DoubleTapForward",1);
            TakeInventory("DoubleTapBack",1);
            TakeInventory("DoubleTapLeft",1);
            TakeInventory("DoubleTapRight",1);
        }
        Delay(1);
    }
}

script WEEB_COMBOREMOVAL ENTER
{
    while (1)
    {
        if (CheckInventory("HyperComboCounter") < 50) { Delay(12); }
        if (CheckInventory("HyperComboCounter") >= 50 && CheckInventory("HyperComboCounter") < 100 ) { Delay(10); }
        if (CheckInventory("HyperComboCounter") >= 100 && CheckInventory("HyperComboCounter") < 150 ) { Delay(8); }
        if (CheckInventory("HyperComboCounter") >= 150 && CheckInventory("HyperComboCounter") < 200 ) { Delay(6); }
        if (CheckInventory("HyperComboCounter") >= 200 && CheckInventory("HyperComboCounter") < 250 ) { Delay(4); }
        if (CheckInventory("HyperComboCounter") >= 250 && CheckInventory("HyperComboCounter") < 300 ) { Delay(2); }
        if (CheckInventory("HyperComboCounter") >= 300 ) { Delay(1); }
        if (CheckInventory("MidCombat") == 0) { TakeInventory("HyperComboCounter",1); }
    }
}

script WEEB_UNLOADING UNLOADING
{
    TakeInventory("AlreadyInLevel",1);
    TakeInventory("KharonSwung",1);
    TakeInventory("SlashingLikeAGaijin",1);
    TakeInventory("ShootingLikeABaka",1);
    TakeInventory("DoubleTapForward",1);
    TakeInventory("DoubleTapBack",1);
    TakeInventory("DoubleTapLeft",1);
    TakeInventory("DoubleTapRight",1);
    TakeInventory("DoubleTapReadyRight",0x7FFFFFFF);
    TakeInventory("DoubleTapReadyForward",0x7FFFFFFF);
    TakeInventory("DoubleTapReadyLeft",0x7FFFFFFF);
    TakeInventory("DoubleTapReadyBack",0x7FFFFFFF);
    TakeInventory("HammerOverchargeLevel",0x7FFFFFFF);
    TakeInventory("EnviroDamageCount",0x7FFFFFFF);
    TakeInventory("EnviroDamageCooldown",0x7FFFFFFF);
    TakeInventory("StopTheBlock",0x7FFFFFFF);
    TakeInventory("BlockLife",0x7FFFFFFF);
    TakeInventory("GhostStepCooldown",0x7FFFFFFF);
    TakeInventory("DoubleTapCooldown",0x7FFFFFFF);
    TakeInventory("MidCombat",0x7FFFFFFF);
}

script WEEB_DEATH DEATH { ACS_ExecuteAlways(WEEB_UNLOADING,0,0,0,0); }

//int array_custmischarg[PLAYERMAX];
//int array_doomHealth[PLAYERMAX];
//int array_metpick[PLAYERMAX];
//int array_hitindic[PLAYERMAX];

function int WeebClientVars(void)
{
    //int custmischarg      = !!GetCVar("metroid_cl_custommissilecharge");
    //int hitindic          = !!GetCVar("metroid_cl_hitindicator");
    //int metpick           = !!GetCVar("metroid_cl_nometroidpickups");
    //int doomHealth        = !!GetCVar("metroid_cl_doomhealth");
    int recoilrules         = !!GetCVar("ds_cl_norecoil");

    return /*(custmischarg << 4) + (hitindic << 3) + (metpick << 2) + (doomHealth << 1) +*/ recoilrules;
}

script WEEB_ENTER_CLIENT ENTER clientside
{
    int execInt, oExecInt, execStr;
    int pln = PlayerNumber();

    while(1)
    {
        if (ConsolePlayerNumber() != PlayerNumber()) { Delay(1); continue; }

        oExecInt = execInt;
        execInt = WeebClientVars();

        if (execInt != oExecInt)
        {
            if (!IsServer)
            {
                execStr = StrParam(s:"puke -", d:WEEB_PUKE, s:" ", d:execInt, s:" ", d:pln);
                ConsoleCommand(execStr);
            }
            else
            {
                ACS_ExecuteWithResult(WEEB_PUKE, execInt, pln);
            }
        }

        delay(1);
    }
}

script WEEB_PUKE (int values) net
{
    int pln = PlayerNumber();

    array_recoilrules[pln]     = values & 1;
    /*array_doomHealth[pln]    = values & 2;
    array_metpick[pln]       = values & 4;
    array_hitindic[pln]      = values & 8;
    array_custmischarg[pln]  = values & 16;*/
}

/*        if (array_custmischarg[pln]) { GiveInventory("CustomMissileCharge", 1); }
        else { TakeInventory("CustomMissileCharge", 0x7FFFFFFF); }

        if (array_doomHealth[pln]) { GiveInventory("DoomHealthCounter", 1); }
        else { TakeInventory("DoomHealthCounter", 0x7FFFFFFF); }
        
        if (array_metpick[pln]) { GiveInventory("NoMetroidPickupSystem", 1); }
        else { TakeInventory("NoMetroidPickupSystem", 0x7FFFFFFF); }