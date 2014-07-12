#include "zcommon.acs"
#library "weeaboo"

#include "commonfuncs.h"

script 265 enter
{
    ACS_ExecuteAlways(268,0,0,0);
    ACS_ExecuteAlways(269,0,0,0);
}
script 266 respawn
{
    if (GameSkill () == 0) { GiveInventory("ContraLifeToken",12); }
    if (GameSkill () == 1) { GiveInventory("ContraLifeToken",10);  }
    if (GameSkill () == 2) { GiveInventory("ContraLifeToken",8); }
    if (GameSkill () == 3) { GiveInventory("ContraLifeToken",5); }
    if (GameSkill () == 4) { GiveInventory("ContraLifeToken",2); }
	ACS_ExecuteAlways(268,0,0,0);
    ACS_ExecuteAlways(269,0,0,0);
}

script 268 (void)
{
    if (CheckInventory("ImAlive") == 0)
	{
    if (GameSkill () == 0) { GiveInventory("BabyMarker",1); GiveInventory("ContraLifeToken",12); }
    if (GameSkill () == 1) { GiveInventory("EasyMarker",1); GiveInventory("ContraLifeToken",10);  }
    if (GameSkill () == 2) { GiveInventory("NormalMarker",1); GiveInventory("ContraLifeToken",8); }
    if (GameSkill () == 3) { GiveInventory("HardMarker",1); GiveInventory("ContraLifeToken",5); }
    if (GameSkill () == 4) { GiveInventory("NightmareMarker",1); GiveInventory("ContraLifeToken",2); }
	GiveInventory("ImAlive",1);
	}
	SetActorProperty(0,APROP_INVULNERABLE,0); // Just in case some wiseass exits while invuln.
	SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Normal);
	
    while (1)
    {
	    TakeInventory("GhostStepCooldown",1);
	
        if (CheckInventory("ContraLifeToken") >= 1)
	    { GiveInventory("999Health",999); }
	    else
	    { SetActorProperty(0,APROP_HEALTH,1); }
        Delay(1);
	}
}

script 267 (void)
{
    if (CheckInventory("ContraArmorToken") >= 1)
	{
		TakeInventory("ContraArmorToken",1);
		SetActorProperty(0,APROP_INVULNERABLE,1);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
		delay(10);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
		delay(10);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
		delay(9);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
		delay(9);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
		delay(8);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
		delay(8);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
		delay(7);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
		delay(7);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
		delay(6);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
		delay(6);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
		delay(5);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
		delay(5);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
		delay(4);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
		delay(4);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
		delay(3);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
		delay(3);
		SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Normal);
		SetActorProperty(0,APROP_INVULNERABLE,0);
	}
	else
	{
		if (CheckInventory("ContraLifeToken") >= 1)
		{
			TakeInventory("ContraLifeToken",1);
			SetActorProperty(0,APROP_INVULNERABLE,1);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
			delay(10);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
			delay(10);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
			delay(9);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
			delay(9);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
			delay(8);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
			delay(8);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
			delay(7);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
			delay(7);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
			delay(6);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
			delay(6);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
			delay(5);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
			delay(5);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
			delay(4);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
			delay(4);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Fuzzy);
			delay(3);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Add);
			delay(3);
			SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Normal);
			SetActorProperty(0,APROP_INVULNERABLE,0);
		}
	}
}

script 269 (void)
{
    while (1)
    {
        if (CheckInventory("DoubleTapForward") || CheckInventory("DoubleTapLeft") || CheckInventory("DoubleTapRigt") || CheckInventory("DoubleTapBack") )
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