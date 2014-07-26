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
    }
}

script WEEB_ENTER ENTER
{
    int buttons;
    int SuperCount;
    int ComboCount;

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
    
    while (1)
    {
        TakeInventory("GhostStepCooldown",1);
    
        if (CheckInventory("ContraLifeToken") >= 1)
        { GiveInventory("999Health",999); }
        else
        { SetActorProperty(0,APROP_HEALTH,1); }
        Delay(1);

        buttons = GetPlayerInput(-1, INPUT_BUTTONS);
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
        }

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
}
