#include "zcommon.acs"
#library "weeaboo"

#include "commonfuncs.h"
#include "weeb_const.h"

int playerTimers[PLAYERMAX][TIMER_COUNT];
int ClientEnterLocks[PLAYERMAX];
int dodgeitem;
int IsServer;

int GotShotgun;
int GotCarronade;
int GotUzi;
int GotHam; // HAM

//#include "weeb_doubletap.h"

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

    while (1)
    {
        if (GetCvar("ds_runninginzdoom") == 0) { if (!GetCvar("compat_clientssendfullbuttoninfo")) { ConsoleCommand("set compat_clientssendfullbuttoninfo 1"); } }
        delay(1);
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
        SetActorProperty(0,APROP_Species,"Player");
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
    SetActorProperty(0,APROP_INVULNERABLE,0); // Just in case some wiseass exits while invuln.
    SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Normal);
    SetActorProperty(0,APROP_Species,"Player");
    SetPlayerProperty(0,0,PROP_TOTALLYFROZEN);
    GiveInventory("NewLevelStatReset",1);
    if (CheckInventory("HammerCharge") > 100) { SetAmmoCapacity("HammerCharge",100); SetInventory("HammerCharge",80); }
    
    while (1)
    {
        //if (CheckInventory("ImAlive") == 1) { if (ConsolePlayerNumber() != PlayerNumber()) { terminate; } }

        // I will not make a Hammertime joke. I will not make a Hammertime joke. I will not make a Hammertime joke.
        if (CheckInventory("HammerUp") == 1)
        {
           if (CheckInventory("HammerCharge") >= 90 && CheckInventory("HammerCharge") <= 100 )
               { if (RideTheLightning >= 30) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
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
        else { if (RideTheLightning >= 40)  { TakeInventory("HammerCharge",1); RideTheLightning = 0; }}
        RideTheLightning++;

        TakeInventory("GhostStepCooldown",1);
        TakeInventory("DoubleTapCooldown",1);
        TakeInventory("EnviroDamageCooldown",1);
        TakeInventory("DoubleTapReadyRight",1);
        TakeInventory("DoubleTapReadyForward",1);
        TakeInventory("DoubleTapReadyLeft",1);
        TakeInventory("DoubleTapReadyBack",1);
        TakeInventory("MidCombat",1);
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

        // For back-back-attack block. Likely to be removed.
        if (buttons & BT_ATTACK)
        { GiveInventory("FakeAttack",1); }
        else
        { TakeInventory("FakeAttack",0x7FFFFFFF); }

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
        if (GetActorVelZ(0) <= 8 && !CheckInventory("OnTheGround") && !CheckInventory("AcesHigh") && keypressed(BT_JUMP))
        {
            ActivatorSound("ghost/jump", 127);
            ThrustThingZ(0, 36, 0, 0);
            GiveInventory("AcesHigh", 1);
        }
        // Remove AcesHigh when we're back on the ground
        if (CheckInventory("OnTheGround") && CheckInventory("AcesHigh"))
            TakeInventory("AcesHigh", 1);
    // This concludes the block of code done by Kyle873.
    // You may now applaud his genius.

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
    TakeInventory("KatanaSwung",1);
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

/*

int array_custmischarg[PLAYERMAX];
int array_runrunruu[PLAYERMAX];
int array_doomHealth[PLAYERMAX];
int array_metpick[PLAYERMAX];
int array_hitindic[PLAYERMAX];

function int MetroidClientVars(void)
{
    int custmischarg      = !!GetCVar("metroid_cl_custommissilecharge");
    int hitindic          = !!GetCVar("metroid_cl_hitindicator");
    int metpick           = !!GetCVar("metroid_cl_nometroidpickups");
    int doomHealth        = !!GetCVar("metroid_cl_doomhealth");
    int runrunruu         = !!GetCVar("cl_run");

    return (custmischarg << 4) + (hitindic << 3) + (metpick << 2) + (doomHealth << 1) + runrunruu;
}

script METROID_ENTER_CLIENTSIDE ENTER clientside
{
    int execInt, oExecInt, execStr;
    int pln = PlayerNumber();

    while(1)
    {
        if (ConsolePlayerNumber() != PlayerNumber()) { Delay(1); continue; }

        oExecInt = execInt;
        execInt = MetroidClientVars();

        if (execInt != oExecInt)
        {
            if (!IsServer)
            {
                execStr = StrParam(s:"puke -", d:METROID_PUKE, s:" ", d:execInt, s:" ", d:pln);
                ConsoleCommand(execStr);
            }
            else
            {
                ACS_ExecuteWithResult(METROID_PUKE, execInt, pln);
            }
        }

        delay(1);
    }
}

script METROID_PUKE (int values) net
{
    int pln = PlayerNumber();

    array_runrunruu[pln]     = values & 1;
    array_doomHealth[pln]    = values & 2;
    array_metpick[pln]       = values & 4;
    array_hitindic[pln]      = values & 8;
    array_custmischarg[pln]  = values & 16;
}

        if (array_custmischarg[pln]) { GiveInventory("CustomMissileCharge", 1); }
        else { TakeInventory("CustomMissileCharge", 0x7FFFFFFF); }

        if (array_doomHealth[pln]) { GiveInventory("DoomHealthCounter", 1); }
        else { TakeInventory("DoomHealthCounter", 0x7FFFFFFF); }
        
        if (array_runrunruu[pln]) { GiveInventory("AlwaysRunIsOn", 1); }
        else { TakeInventory("AlwaysRunIsOn", 0x7FFFFFFF); }
        
        if (array_metpick[pln]) { GiveInventory("NoMetroidPickupSystem", 1); }
        else { TakeInventory("NoMetroidPickupSystem", 0x7FFFFFFF); }