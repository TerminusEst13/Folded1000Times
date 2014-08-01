#include "zcommon.acs"
#library "weeaboo"

#include "commonfuncs.h"
#include "weeb_const.h"

int playerTimers[PLAYERMAX][TIMER_COUNT];
int ClientEnterLocks[PLAYERMAX];
int dodgeitem;

int GotShotgun;
int GotCarronade;
int GotUzi;
int GotHam; // HAM

#include "weeb_doubletap.h"

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

script WEEB_DECORATE (int burrshet)
{
    switch (burrshet)
    {
    case WEEB_DEC_DAMAGE:
        int delaytotal = 104;
        int delaytimer = delaytotal;
        int delaytime = 10;
        int delaycount = 0;
        
        if (CheckInventory("ContraArmorToken") >= 1)
            TakeInventory("ContraArmorToken",1);
        else if (CheckInventory("OverLifeToken") >= 1)
            TakeInventory("OverLifeToken",1);
        else if (CheckInventory("ContraLifeToken") >= 1)
            TakeInventory("ContraLifeToken",1);
        
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
        SetPlayerProperty(0,1,PROP_TOTALLYFROZEN);
        break;

    case WEEB_DEC_UNFREEZE:
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
        if (GameSkill () == 0) { SetInventory("ContraLifeToken",10); SetInventory("ContraArmorToken",5); SetInventory("OverLifeToken",4); }
        if (GameSkill () == 1) { SetInventory("ContraLifeToken",8);  SetInventory("ContraArmorToken",5); SetInventory("OverLifeToken",4); }
        if (GameSkill () == 2) { SetInventory("ContraLifeToken",6);  SetInventory("ContraArmorToken",5); SetInventory("OverLifeToken",3); }
        if (GameSkill () == 3) { SetInventory("ContraLifeToken",4);  SetInventory("ContraArmorToken",5); SetInventory("OverLifeToken",3); }
        if (GameSkill () == 4) { SetInventory("ContraLifeToken",2);  SetInventory("ContraArmorToken",5); SetInventory("OverLifeToken",2); }
        if (GameSkill () == 5) { SetInventory("ContraLifeToken",0);  SetInventory("ContraArmorToken",5); SetInventory("OverLifeToken",1); }
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
    }
}

//
function void evade_start(int angle, int dir)
{
	GiveInventory("EvadingPlayer",1);
	SetPlayerProperty(0, ON, PROP_FROZEN);
	ThrustThing(angle+dir, 45, 0, 0);
	ThrustThingZ (0, 140, 1, 1);
}

function void evade_end(void)
{
	SetPlayerProperty(0, OFF, PROP_FROZEN);
	TakeInventory("EvadingPlayer",1);
}

script WEEB_ENTER ENTER
{
    int Buttons;
    int SuperCount;
    int ComboCount;
    int KurtAngle;
    int WalkTheDinosaur;
    int RideTheLightning;

    if (PlayerNumber() != ConsolePlayerNumber()) { terminate; }

    if (CheckInventory("ImAlive") == 0)
    {
        if (GameSkill () == 0) { GiveInventory("BabyMarker",1); GiveInventory("ContraLifeToken",10); }
        if (GameSkill () == 1) { GiveInventory("EasyMarker",1); GiveInventory("ContraLifeToken",8);  }
        if (GameSkill () == 2) { GiveInventory("NormalMarker",1); GiveInventory("ContraLifeToken",6); }
        if (GameSkill () == 3) { GiveInventory("HardMarker",1); GiveInventory("ContraLifeToken",4); }
        if (GameSkill () == 4) { GiveInventory("NightmareMarker",1); GiveInventory("ContraLifeToken",2); }
        GiveInventory("ImAlive",1);
    }
    SetActorProperty(0,APROP_INVULNERABLE,0); // Just in case some wiseass exits while invuln.
    SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Normal);
    SetPlayerProperty(0,0,PROP_TOTALLYFROZEN);
    GiveInventory("NewLevelStatReset",1);
    if (CheckInventory("HammerCharge") > 100) { SetAmmoCapacity("HammerCharge",100); SetInventory("HammerCharge",80); }
    
    while (1)
    {
        // I will not make a Hammertime joke. I will not make a Hammertime joke. I will not make a Hammertime joke.
        if (CheckInventory("HammerUp") == 1)
        {
           if (CheckInventory("HammerCharge") >= 90 && CheckInventory("HammerCharge") <= 100 )
               { if (RideTheLightning >= 30) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") > 100)
               { if (RideTheLightning >= 7) { GiveInventory("HammerCharge",1); GiveInventory("ChargeScreenFlash",1); RideTheLightning = 0; }}
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
           RideTheLightning++;
        }

        Buttons = GetPlayerInput(-1, INPUT_BUTTONS);
        KurtAngle = GetActorAngle(0) >> 8;

        TakeInventory("GhostStepCooldown",1);
        TakeInventory("DoubleTapCooldown",1);
    
        // If the player still has life left, they get full health.
        if (CheckInventory("ContraLifeToken") >= 1 || CheckInventory("OverLifeToken") >= 1)
        { GiveInventory("999Health",999); }
        else
        { SetActorProperty(0,APROP_HEALTH,1); }

        // For back-back-attack block. Likely to be removed.
        if (buttons & BT_ATTACK)
        { GiveInventory("FakeAttack",1); }
        else
        { TakeInventory("FakeAttack",0x7FFFFFFF); }

        // MAAAAAX!!
        SuperCount = CheckInventory("SuperMeterCounter");
        SetInventory("SuperCounter1",SuperCount);
        if (CheckInventory("SuperMeterCounter") > 100) { SetInventory("SuperCounter2",(SuperCount - 100)); } else { TakeInventory("SuperCounter2",0x7FFFFFFF); }
        if (CheckInventory("SuperMeterCounter") > 200) { SetInventory("SuperCounter3",(SuperCount - 200)); } else { TakeInventory("SuperCounter3",0x7FFFFFFF); }

        // 666 COMBO! SUPER SWEET STYLISH!
        ComboCount = CheckInventory("HyperComboCounter");
        SetInventory("ComboCounter1",ComboCount);
        if (CheckInventory("HyperComboCounter") <= 50) { TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); }
        if (CheckInventory("HyperComboCounter") > 50) { SetInventory("ComboCounter2",(ComboCount - 50)); GiveInventory("ComboDamageLevel1",1); GiveInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter2",0x7FFFFFFF); TakeInventory("ComboDamageLevel1",0x7FFFFFFF); }
        if (CheckInventory("HyperComboCounter") > 100) { SetInventory("ComboCounter3",(ComboCount - 100)); GiveInventory("ComboDamageLevel2",1); TakeInventory("FRank",1); GiveInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter3",0x7FFFFFFF); TakeInventory("ComboDamageLevel2",0x7FFFFFFF); }
        if (CheckInventory("HyperComboCounter") > 150) { SetInventory("ComboCounter4",(ComboCount - 150)); GiveInventory("ComboDamageLevel3",1); TakeInventory("FRank",1); TakeInventory("DRank",1); GiveInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter4",0x7FFFFFFF); TakeInventory("ComboDamageLevel3",0x7FFFFFFF); }
        if (CheckInventory("HyperComboCounter") > 200) { SetInventory("ComboCounter5",(ComboCount - 200)); GiveInventory("ComboDamageLevel4",1); TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); GiveInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter5",0x7FFFFFFF); TakeInventory("ComboDamageLevel4",0x7FFFFFFF); }
        if (CheckInventory("HyperComboCounter") > 250) { SetInventory("ComboCounter6",(ComboCount - 250)); GiveInventory("ComboDamageLevel5",1); TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); GiveInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter6",0x7FFFFFFF); TakeInventory("ComboDamageLevel5",0x7FFFFFFF); }
        if (CheckInventory("HyperComboCounter") > 300) { SetInventory("ComboCounter7",(ComboCount - 300)); GiveInventory("ComboDamageLevel6",1); TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); GiveInventory("SRank",1); } else { TakeInventory("ComboCounter7",0x7FFFFFFF); TakeInventory("ComboDamageLevel6",0x7FFFFFFF); }

        // Global variables
        if (isSinglePlayer())
        {
            if (CheckInventory("GotShotgun") == 1) { GotShotgun = 1; }
            if (CheckInventory("GotCarronade") == 1) { GotCarronade = 1; }
            if (CheckInventory("GotUzi") == 1) { GotUzi = 1; }
            if (CheckInventory("GotHammer") == 1) { GotHam = 1; } // HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAM
        }

        // Floor
        WalkTheDinosaur = GetActorZ(0) - GetActorFloorZ(0);
        if (WalkTheDinosaur >= 0 && WalkTheDinosaur <= 10) { GiveInventory("OnTheGround",1); TakeInventory("GhostStepDone",1); } else { TakeInventory("OnTheGround",1); }
        // Dodging
        if (CheckInventory("GhostStepCooldown") == 0 && CheckInventory("GhostStepDone") == 0)
        { if (buttons & BT_SPEED && buttons & BT_FORWARD)
              { ThrustThing(KurtAngle+0,45,0,0);
              if (CheckInventory("OnTheGround") == 1) { ThrustThingZ(0,85,1,1); } else { ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35);
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0); }
          if (buttons & BT_SPEED && buttons & BT_MOVELEFT)
              { ThrustThing(KurtAngle+64,45,0,0);
              if (CheckInventory("OnTheGround") == 1) { ThrustThingZ(0,85,1,1); } else { ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0); }
          if (buttons & BT_SPEED && buttons & BT_BACK)
              { ThrustThing(KurtAngle+128,45,0,0);
              if (CheckInventory("OnTheGround") == 1) { ThrustThingZ(0,85,1,1); } else { ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0); }
          if (buttons & BT_SPEED && buttons & BT_MOVERIGHT)
              { ThrustThing(KurtAngle+192,45,0,0);
              if (CheckInventory("OnTheGround") == 1) { ThrustThingZ(0,85,1,1); } else { ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0); }
          /*if (buttons & BT_SPEED && buttons & BT_JUMP && CheckInventory("SuperMeterCounter") >= 5)
              { if (CheckInventory("OnTheGround") == 1) { ThrustThingZ(0,120,0,0); } else { ThrustThingZ(0,52,0,0); } // Bleh, doesn't work. I'll need to think of a way to get a higher jump while on the ground.
              ActivatorSound("ghost/jump",127);
              GiveInventory("GhostStepDone",1);
              TakeInventory("SuperMeterCounter",5);
              GiveInventory("GhostStepCooldown",35); }*/
        }

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
        if (CheckInventory("HyperComboCounter") < 50) { Delay(22); }
        if (CheckInventory("HyperComboCounter") >= 50 && CheckInventory("HyperComboCounter") < 100 ) { Delay(18); }
        if (CheckInventory("HyperComboCounter") >= 100 && CheckInventory("HyperComboCounter") < 150 ) { Delay(16); }
        if (CheckInventory("HyperComboCounter") >= 150 && CheckInventory("HyperComboCounter") < 200 ) { Delay(14); }
        if (CheckInventory("HyperComboCounter") >= 200 && CheckInventory("HyperComboCounter") < 250 ) { Delay(12); }
        if (CheckInventory("HyperComboCounter") >= 250 && CheckInventory("HyperComboCounter") < 300 ) { Delay(10); }
        if (CheckInventory("HyperComboCounter") >= 300 ) { Delay(8); }
        TakeInventory("HyperComboCounter",1);
    }
}

script WEEB_UNLOADING UNLOADING
{
    TakeInventory("AlreadyInLevel",1);
    TakeInventory("KatanaSwung",1);
    TakeInventory("SlashingLikeAGaijin",1);
    TakeInventory("ShootingLikeABaka",1);
    TakeInventory("DoubleTapForward",1);
    TakeInventory("DoubleTapBack",1);
    TakeInventory("DoubleTapLeft",1);
    TakeInventory("DoubleTapRight",1);
    TakeInventory("StopTheBlock",0x7FFFFFFF);
    TakeInventory("BlockLife",0x7FFFFFFF);
    TakeInventory("GhostStepCooldown",0x7FFFFFFF);
    TakeInventory("DoubleTapCooldown",0x7FFFFFFF);
}