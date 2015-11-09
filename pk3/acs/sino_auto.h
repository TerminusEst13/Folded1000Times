script SINO_ENTER ENTER
{
    int buttons;
    int oldbuttons;
    int pln = PlayerNumber();
    int MichaelAngleoBatio;
    int xxx;
    int yyy;
    int xxx2;
    int yyy2;
    int GetSomeHealthAlready;
    int KiCount;
    int ComboCount;
    int EverybodyNeeds;
    int RemoveFRankAnnouncer;
    int RemoveDRankAnnouncer;
    int RemoveCRankAnnouncer;
    int RemoveBRankAnnouncer;
    int RemoveARankAnnouncer;
    int RemoveSRankAnnouncer;
    int IntroChance;
    int speedmod;
    int zzz;
    int angle;
    int RavenLeftTID;
    int RavenRightTID;
    int xOffset, yOffset, yOffset2, zOffset;
    int velx, vely, velz;
    int nx, nx2, ny, ny2, nz;
    int RavenHPLeft;
    int RavenHPRight;
    int NewRavenHPLeft;
    int NewRavenHPRight;

    if (GetCvar("dst_debug") == 1) { Log(s:"SINO_ENTER executing on player ", d:pln); }

    if (CheckInventory("IsJungHaeLin") == 1)
    {
        if (GetCvar("dst_debug") == 1) { Log(s:"Error: Player ", d:pln, s:" is not Shihong, terminating SINO_ENTER."); }
        terminate;
    }

    if (CheckInventory("ImAlive") == 0 && GameType() != GAME_TITLE_MAP)
    {
        //PrintBold(s:"getting the things");
        if (GameSkill () == 0 || (GameSkill() == 6 && GetCvar("dst_multiplierhealth") == 0)) { GiveInventory("BabyMarker",1); GiveInventory("ContraLifeToken",10); }
        if (GameSkill () == 1 || (GameSkill() == 6 && GetCvar("dst_multiplierhealth") == 1)) { GiveInventory("EasyMarker",1); GiveInventory("ContraLifeToken",8);  }
        if (GameSkill () == 2 || (GameSkill() == 6 && GetCvar("dst_multiplierhealth") == 2)) { GiveInventory("NormalMarker",1); GiveInventory("ContraLifeToken",6); }
        if (GameSkill () == 3 || (GameSkill() == 6 && GetCvar("dst_multiplierhealth") == 3)) { GiveInventory("HardMarker",1); GiveInventory("ContraLifeToken",4); }
        if (GameSkill () == 4 || (GameSkill() == 6 && GetCvar("dst_multiplierhealth") == 4)) { GiveInventory("NightmareMarker",1); GiveInventory("ContraLifeToken",2); }

        FadeRange(64,255,64,1.00,0,0,0,0,3.50);
        ACS_ExecuteAlways(SINO_DECORATE,0,1,0,0);
        LocalAmbientSound("level/introssh",127);

        GiveInventory("ImAlive",1);

        if (GetCvar("dst_omenstart") == 1)
        {
            GiveInventory("01Tiger",1);
            GiveInventory("GotHammer",1);
        }

        if (GetCvar("dst_backpackstart") == 1)
        { GiveInventory("Backpack",1); }
    }
    else if (CheckInventory("ImAlive") == 1 && CheckInventory("AlreadyInLevel") == 0)
    // If the player isn't respawning but is entering a level fresh.
    {
        IntroChance = random(0,4);
        if (IntroChance == 4) { LocalAmbientSound("shihong/intro",127); }
        TakeInventory("PointsFoundAllSecrets",1);
        TakeInventory("PointsKilledMonsters",1);
        TakeInventory("MaidenHalo",1);
    }

    // Restoring all the stuff from previous level, just in case someone exits under a special state.
    If (CheckInventory("TricksterModeOn") == 0 )
    {
        SetActorProperty(0,APROP_Gravity,0.7);
        TakeInventory("TricksterModeSpeed",1);
    }
    else
    {
        SetActorProperty(0,APROP_Gravity,0.6);
        GiveInventory("TricksterModeSpeed",1);
    }
    SetPlayerProperty(0,0,PROP_FROZEN);
    TakeInventory("JetpackSpeedPower1",1);
    TakeInventory("JetpackSpeedPower2",1);
    TakeInventory("JetpackSpeedPower3",1);
    TakeInventory("JetpackSpeedPower4",1);
    TakeInventory("JetpackSpeedPower5",1);
    TakeInventory("JetpackSpeedPower6",1);
    TakeInventory("JetpackSpeedPower7",1);
    TakeInventory("JetpackSpeedPower8",1);
    TakeInventory("JetpackSpeedPower9",1);
    TakeInventory("JetpackSpeedPower10",1);
    TakeInventory("JetpackSpeedPower11",1);
    TakeInventory("JetpackSpeedPower12",1);
    TakeInventory("JetpackSpeedPower13",1);
    TakeInventory("JetpackSpeedPower14",1);
    TakeInventory("JetpackSpeedPower15",1);
    TakeInventory("JetpackSpeedPower16",1);
    TakeInventory("JetpackSpeedPower17",1);
    TakeInventory("JetpackSpeedPower18",1);
    TakeInventory("JetpackSpeedPower19",1);
    TakeInventory("JetpackSpeedPower20",1);
    SetPlayerProperty(0,0,PROP_FLY);//TakeInventory("JetpackFlightPower",1);
    TakeInventory("JetpackModeOn",1);
    GiveInventory("DodgeGhostOff",1);
    GiveInventory("JetpackModeOff",1);
    GiveInventory("IAmASkilledPersonWhoWantsOnlyMySwordToGiveSouls",1); // Shihong deals with ki, not souls.
                                                                        // Souls are completely irrelevant to her.

    // If the Raven was carried over from a previous level...
    if (CheckInventory("RavenUp") == 1)
    {
    // This is to prevent the Sentinel's info on the HUD from reading max value when we change levels with the Sentinel up.
    // It's very work-around-y, but it's what I get for assuming stuff can transfer across levels.
      if (CheckInventory("RavenLeftDead") == 0)
      {
        NewRavenHPLeft = CheckInventory("RavenLeftLifeCounter");
        TakeInventory("RavenLeftActive",1);
        TakeInventory("RavenLeftUp",1);
        GiveInventory("RavenLeftFromPreviousLevel",1);
      }
      if (CheckInventory("RavenRightDead") == 0)
      {
        NewRavenHPRight = CheckInventory("RavenRightLifeCounter");
        TakeInventory("RavenRightActive",1);
        TakeInventory("RavenRightUp",1);
        GiveInventory("RavenRightFromPreviousLevel",1);
      }
    }

    // Status resets for the sake of weapons/items/etc that change between levels.
    // Like in case some wiseass exits while in post-hit invulnerability.
    SetActorProperty(0,APROP_INVULNERABLE,0);
    SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Normal);
    if (GameType() == GAME_NET_DEATHMATCH) { SetActorProperty(0,APROP_Species,"DMPlayer"); }
    else { SetActorProperty(0,APROP_Species,"Player"); }
    SetPlayerProperty(0,0,PROP_TOTALLYFROZEN);
    GiveInventory("NewLevelStatReset",1);
    GiveInventory("FlashlightStopper",1);
    if (CheckInventory("HyperComboCounter") < 50) { TakeInventory("FRankAnnounced",1); }
    if (CheckInventory("HyperComboCounter") < 100) { TakeInventory("DRankAnnounced",1); }
    if (CheckInventory("HyperComboCounter") < 150) { TakeInventory("CRankAnnounced",1); }
    if (CheckInventory("HyperComboCounter") < 200) { TakeInventory("BRankAnnounced",1); }
    if (CheckInventory("HyperComboCounter") < 250) { TakeInventory("ARankAnnounced",1); }
    if (CheckInventory("HyperComboCounter") < 300) { TakeInventory("SRankAnnounced",1); }

    if (GetCvar("dst_debug") == 1) { Log(s:"Entering SINO_ENTER while(1) loop on player ", d:pln); }

    while (1)
    {
        if (CheckInventory("IsJungHaeLin") == 1)
        { terminate; }

        TakeInventory("SwapCooldown",1);

        // Punchcombo shit
        if (CheckInventory("MidCombat") == 0) { TakeInventory("PunchComboCounter",1); }
        if (CheckInventory("PunchComboCounter") == 1) { GiveInventory("ComboDamage1",1); } else { TakeInventory("ComboDamage1",1); }
        if (CheckInventory("PunchComboCounter") == 2) { GiveInventory("ComboDamage2",1); } else { TakeInventory("ComboDamage2",1); }
        if (CheckInventory("PunchComboCounter") == 3) { GiveInventory("ComboDamage3",1); } else { TakeInventory("ComboDamage3",1); }
        if (CheckInventory("PunchComboCounter") == 4) { GiveInventory("ComboDamage4",1); } else { TakeInventory("ComboDamage4",1); }
        if (CheckInventory("PunchComboCounter") == 5) { GiveInventory("ComboDamage5",1); } else { TakeInventory("ComboDamage5",1); }
        if (CheckInventory("PunchComboCounter") == 6) { GiveInventory("ComboDamage6",1); } else { TakeInventory("ComboDamage6",1); }
        if (CheckInventory("PunchComboCounter") == 7) { GiveInventory("ComboDamage7",1); } else { TakeInventory("ComboDamage7",1); }
        if (CheckInventory("PunchComboCounter") == 8) { GiveInventory("ComboDamage8",1); } else { TakeInventory("ComboDamage8",1); }
        if (CheckInventory("PunchComboCounter") == 9) { GiveInventory("ComboDamage9",1); } else { TakeInventory("ComboDamage9",1); }
        if (CheckInventory("PunchComboCounter") == 10) { GiveInventory("ComboDamage10",1); } else { TakeInventory("ComboDamage10",1); }

        // Style swapping nonsense
        if (CheckInventory("HaggarModeOn") == 1) { GiveInventory("HaggarModeExtraDamage",1); }
        else { TakeInventory("HaggarModeExtraDamage",1); }
        if (CheckInventory("RangedModeOn") == 1) { GiveInventory("RangedModeExtraDamage",1); }
        else { TakeInventory("RangedModeExtraDamage",1); }

        // OH SHIT I'M OUT OF HEALTH
        // SUDDENLY AND COINCIDENTALLY I HAVE A MASSIVE CRAVING FOR MUNCHIES
        if (CheckInventory("ContraLifeToken") == 0 && CheckInventory("OverLifeToken") == 0 && !isDead(0) && GameSkill() != 5 && CheckInventory("IAmADumbPersonWhoWillProbablyAccidentallyDie") == 0)
        {
          if (GetSomeHealthAlready >= 60)
          {
            FadeRange(255,0,0,0.25,0,0,0,0,1.00);
            LocalAmbientSound("shihong/healthwarning",127);
            GetSomeHealthAlready = 0;
          }
        GetSomeHealthAlready++;
        }
        else
        {
            GetSomeHealthAlready = 0;
        }

        // Various ground and status checks for the kickjumping and idle animation.
        xxx2 = xxx;
        yyy2 = yyy;
        xxx  = GetActorX(0);
        yyy  = GetActorY(0);
        zzz  = GetActorZ(0);
        angle = GetActorAngle(0);
        velx  = GetActorVelX(0);
        vely  = GetActorVelY(0);
        velz  = GetActorVelZ(0);

        //Print(s:"Y is ", d:yyy, s:". X is ", d:xxx, s:". Y2 is ", d:yyy2, s:". X2 is ", d:xxx2);
        if (xxx2 == xxx && yyy2 == yyy)
        { GiveInventory("WaitingTooLong",1); }
        else
        { TakeInventory("WaitingTooLong",0x7FFFFFFF); }

        // This is a now-useless function, but the math to see if someone's within a certain
        // distance of where they last were may come in handy in the future.
        /*if ( ((xxx2 <= (xxx + 8.0)) && (xxx2 >= (xxx - 8.0))) && ((yyy2 <= (yyy + 8.0)) && (yyy2 >= (yyy - 8.0))) )
        { TakeInventory("KickJumpReset",1); }
        else
        { GiveInventory("KickJumpReset",1); }*/

        // Checks if the player is actually on the floor.
        if (GetActorZ(0) - GetActorFloorZ(0) <= 0)
        {
            GiveInventory("OnTheGround",1);
            TakeInventory("JumpedUp",1);
            TakeInventory("InTheAir",0x7FFFFFFF);
        }
        else
        {
            TakeInventory("OnTheGround",1);
            GiveInventory("InTheAir",1);
        }

        OldButtons = GetPlayerInput(-1, INPUT_OLDBUTTONS);
        buttons = GetPlayerInput(-1, INPUT_BUTTONS);
        MichaelAngleoBatio = GetActorAngle(0) >> 8;

        // In Zandro 2.0, for some reason, Shihong is able to execute Hae-Lin's dash.
        // This is despite the fact that WEEB_ENTER isn't executing on Shihong, isn't
        // reading her inputs, and that specific block isn't firing. I checked. I
        // even put Print spam everywhere. And yet, somehow, the Hae-Lin dash is still
        // happening.
        // This is fixed in 3.0, but only Lord knows how long it'll be until that comes out.
        // Until then, have a dumb hack.
        GiveInventory("GhostStepCooldown",100);

        if (buttons & BT_ALTATTACK)
            { GiveInventory("SynthAltFire",1); }
          else
            { TakeInventory("SynthAltFire",1); }

        if (buttons & BT_ATTACK)
            { GiveInventory("SynthFire",1); }
          else
            { TakeInventory("SynthFire",1); }

        if (buttons & BT_JUMP)
            { GiveInventory("JumpedUp",1); }

        // Temporary equipment workaround.
        if (CheckInventory("KharonOmen") == 1)
            { TakeInventory("KharonOmen",1); GiveInventory("01Tiger",1); }
        if (CheckInventory("KharonTestament") == 1)
            { TakeInventory("KharonTestament",1); GiveInventory("03Wolf",1); }
        if (CheckInventory("KharonExodus") == 1)
            { TakeInventory("KharonExodus",1); GiveInventory("05Dragon",1); }
        if (CheckInventory("KharonSabbath") == 1)
            { TakeInventory("KharonSabbath",1); GiveInventory("04Scorpions",1); }



        // THE RAVEN
        RavenLeftTID = 15000 + pln;
        RavenRightTID = 15100 + pln;
        if (CheckInventory("RavenUp") == 1)
        {
            if (CheckInventory("RavenLeftActive") == 0 && CheckInventory("RavenLeftUp") == 0 && CheckInventory("RavenLeftDead") == 0)
            {
                Spawn("UnleashTheRaven",xxx,yyy,zzz,RavenLeftTID,angle);
                GiveInventory("RavenLeftActive",1);
                GiveInventory("RavenLeftUp",1);
                if (CheckInventory("RavenLeftFromPreviousLevel") == 1)
                {
                    SetActorProperty(RavenLeftTID,APROP_Health,NewRavenHPLeft);
                    TakeInventory("RavenLeftFromPreviousLevel",1);
                }
            }

            if (CheckInventory("RavenRightActive") == 0 && CheckInventory("RavenRightUp") == 0 && CheckInventory("RavenRightDead") == 0)
            {
                Spawn("UnleashTheRaven",xxx,yyy,zzz,RavenRightTID,angle);
                GiveInventory("RavenRightActive",1);
                GiveInventory("RavenRightUp",1);
                if (CheckInventory("RavenRightFromPreviousLevel") == 1)
                {
                    SetActorProperty(RavenRightTID,APROP_Health,NewRavenHPRight);
                    TakeInventory("RavenRightFromPreviousLevel",1);
                }
            }

            if (CheckInventory("RavenLeftActive") == 1 || CheckInventory("RavenRightActive") == 1)
            {
                xOffset = -28.0;
                yOffset = -26.0;
                yOffset2 = 26.0;
                zOffset = 4.0;

                nx = xxx + FixedMul(xOffset, cos(angle)) + FixedMul(yOffset, sin(angle));
                nx2 = xxx + FixedMul(xOffset, cos(angle)) + FixedMul(yOffset2, sin(angle));
                ny = yyy + FixedMul(xOffset, sin(angle)) - FixedMul(yOffset, cos(angle));
                ny2 = yyy + FixedMul(xOffset, sin(angle)) - FixedMul(yOffset2, cos(angle));
                nz = zzz + zOffset;

                /*if (pln != ConsolePlayerNumber())
                {
                    nx -= velx; ny -= vely; ny2 -= vely; nz -= velz;
                }
                else
                {
                    nx -= velx; ny -= vely; ny2 -= vely; nz -= 2*velz;
                }*/

                SetActorAngle(RavenLeftTID, angle);
                SetActorAngle(RavenRightTID, angle); 
                SetActorPosition(RavenLeftTID,nx + FixedMul(32.0,cos(angle)),ny + FixedMul(32.0,sin(angle)),nz + 32.0,0);
                SetActorPosition(RavenRightTID,nx2 + FixedMul(32.0,cos(angle)),ny2 + FixedMul(32.0,sin(angle)),nz + 32.0,0);
                SetActorVelocity(RavenLeftTID,velx,vely,velz,0,0);
                SetActorVelocity(RavenRightTID,velx,vely,velz,0,0);

                RavenHPLeft = GetActorProperty(RavenLeftTID, APROP_HEALTH);
                RavenHPRight = GetActorProperty(RavenRightTID, APROP_HEALTH);
                TakeInventory("RavenLeftLifeCounter",0x7FFFFFFF);
                GiveInventory("RavenLeftLifeCounter",RavenHPLeft);
                TakeInventory("RavenRightLifeCounter",0x7FFFFFFF);
                GiveInventory("RavenRightLifeCounter",RavenHPRight);

                if (CheckInventory("RavenGimmeJustALittle") == 1)
                {
                    if (CheckInventory("RavenLeftDead") == 0) { GiveActorInventory(RavenLeftTID,"RavenHealthLeft",150); }
                        else { TakeInventory("RavenLeftDead",1); TakeInventory("RavenLeftActive",1); TakeInventory("RavenLeftUp",1); }
                    if (CheckInventory("RavenRightDead") == 0) { GiveActorInventory(RavenRightTID,"RavenHealthRight",150); }
                        else { TakeInventory("RavenRightDead",1); TakeInventory("RavenRightActive",1); TakeInventory("RavenRightUp",1); }
                    TakeInventory("RavenGimmeJustALittle",1);
                }

                if (CheckActorInventory(RavenLeftTID,"RavenWhenTheGoingGetsTough"))
                {
                    Thing_Remove(RavenLeftTID);
                    RavenLeftTID = 0;
                    GiveInventory("RavenLeftDead",1);
                    TakeInventory("RavenLeftActive",1);
                    TakeInventory("RavenLeftLifeCounter",0x7FFFFFFF);
                }

                if (CheckActorInventory(RavenRightTID,"RavenWhenTheGoingGetsTough"))
                {
                    Thing_Remove(RavenRightTID);
                    RavenRightTID = 0;
                    GiveInventory("RavenRightDead",1);
                    TakeInventory("RavenRightActive",1);
                    TakeInventory("RavenRightLifeCounter",0x7FFFFFFF);
                }
            }
        }

        if (CheckInventory("RavenLeftDead") == 1 && CheckInventory("RavenRightDead") == 1)
        {
            TakeInventory("RavenUp",1);
            TakeInventory("RavenLeftUp",1); TakeInventory("RavenRightUp",1);
            TakeInventory("RavenLeftDead",1); TakeInventory("RavenRightDead",1);
        }

    // ============ GENERIC COPY/PASTED SHIT HERE

        // THE SUPER COUNTER. Not the kind you lean on.
        KiCount = CheckInventory("KiMeterCounter");
        //SetInventory("KiCounter1",KiCount); // Life would be so much easier if this worked online.
        // This script changes the display on the HUD.
        // While SuperMeterCounter can be whatever, each of the bars on the HUD read 100 of SuperMeterCounter.
        // Because of this, I have to manually see exactly how much of each level the player has and then give
        // a dummy item which the bars then read.
        TakeInventory("KiCounter1", 0x7FFFFFFF);
        GiveInventory("KiCounter1", KiCount);
        if (KiCount > 1000)
            { TakeInventory("KiCounter2",0x7FFFFFFF);
              GiveInventory("KiCounter2", KiCount - 1000); } //SetInventory("KiCounter2",(KiCount - 100)); }
            else { TakeInventory("KiCounter2",0x7FFFFFFF); }
        if (KiCount > 2000)
            { TakeInventory("KiCounter3",0x7FFFFFFF);
              GiveInventory("KiCounter3", KiCount - 2000); } //SetInventory("KiCounter3",(KiCount - 200)); }
            else { TakeInventory("KiCounter3",0x7FFFFFFF); }
        if (KiCount > 3000)
            { TakeInventory("KiCounter4",0x7FFFFFFF);
              GiveInventory("KiCounter4", KiCount - 3000); } //SetInventory("KiCounter3",(KiCount - 200)); }
            else { TakeInventory("KiCounter4",0x7FFFFFFF); }
        // If the player has less than 20 of SuperMeterCounter, they slowly regenerate.
        if (KiCount < 200) { if (EverybodyNeeds >= 280)
            { GiveInventory("KiMeterCounter",10); EverybodyNeeds = 0; }}
        EverybodyNeeds++;

        // 666 COMBO! SUPER SWEET STYLISH!
        // Likewise, this is mostly dedicated to showing the player how much combo meter they
        // have on the HUD.
        // It's all the same basic principal. Split the entire counter into bars of 1-100,
        // see how much of each level the player has, give it to them as a dummy item.
        // This is slightly more complicated by use of the ranking system.
        ComboCount = CheckInventory("HyperComboCounter");
        TakeInventory("ComboCounter1",0x7FFFFFFF);
        GiveInventory("ComboCounter1",ComboCount);
        if (ComboCount <= 50)
        {
            TakeInventory("FRank",1);
            TakeInventory("DRank",1);
            TakeInventory("CRank",1);
            TakeInventory("BRank",1);
            TakeInventory("ARank",1);
            TakeInventory("SRank",1);
        }

        // Kyle873 once told me that "one-line code" was basically the worst thing a coder could do.
        // If he ever sees this, I am so sorry. I am so, so sorry.
        if (ComboCount > 50)
            { TakeInventory("ComboCounter2",0x7FFFFFFF); GiveInventory("ComboCounter2",(ComboCount - 50)); GiveInventory("ComboDamageLevel1",1);
              GiveInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); }
              else { TakeInventory("ComboCounter2",0x7FFFFFFF); TakeInventory("ComboDamageLevel1",0x7FFFFFFF); }
        if (ComboCount > 100)
            { TakeInventory("ComboCounter3",0x7FFFFFFF); GiveInventory("ComboCounter3",(ComboCount - 100)); GiveInventory("ComboDamageLevel2",1);
              TakeInventory("FRank",1); GiveInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); }
              else { TakeInventory("ComboCounter3",0x7FFFFFFF); TakeInventory("ComboDamageLevel2",0x7FFFFFFF); }
        if (ComboCount > 150)
            { TakeInventory("ComboCounter4",0x7FFFFFFF); GiveInventory("ComboCounter4",(ComboCount - 150)); GiveInventory("ComboDamageLevel3",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); GiveInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); }
              else { TakeInventory("ComboCounter4",0x7FFFFFFF); TakeInventory("ComboDamageLevel3",0x7FFFFFFF); }
        if (ComboCount > 200)
            { TakeInventory("ComboCounter5",0x7FFFFFFF); GiveInventory("ComboCounter5",(ComboCount - 200)); GiveInventory("ComboDamageLevel4",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); GiveInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); }
              else { TakeInventory("ComboCounter5",0x7FFFFFFF); TakeInventory("ComboDamageLevel4",0x7FFFFFFF); }
        if (ComboCount > 250)
            { TakeInventory("ComboCounter6",0x7FFFFFFF); GiveInventory("ComboCounter6",(ComboCount - 250)); GiveInventory("ComboDamageLevel5",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); GiveInventory("ARank",1); TakeInventory("SRank",1); }
              else { TakeInventory("ComboCounter6",0x7FFFFFFF); TakeInventory("ComboDamageLevel5",0x7FFFFFFF); }
        if (ComboCount > 300)
            { TakeInventory("ComboCounter7",0x7FFFFFFF); GiveInventory("ComboCounter7",(ComboCount - 300)); GiveInventory("ComboDamageLevel6",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); GiveInventory("SRank",1); }
              else { TakeInventory("ComboCounter7",0x7FFFFFFF); TakeInventory("ComboDamageLevel6",0x7FFFFFFF); }

        // Technically it would be more efficient to integrate these into the combo level checks above.
        // But you just saw that code. Fuck that code.
        // FUCK that code.
        if (ComboCount > 50)
            { if (CheckInventory("FRankAnnounced") == 0)
              { GiveInventory("FRankAnnounced",1);
                if (CheckInventory("IAmAQuietPersonWhoWantsMoreQuietRankings") == 0) { LocalAmbientSound("ranking/fearless",127); }}}
        if (ComboCount > 100)
            { if (CheckInventory("DRankAnnounced") == 0)
              { GiveInventory("DRankAnnounced",1);
                if (CheckInventory("IAmAQuietPersonWhoWantsMoreQuietRankings") == 0) { LocalAmbientSound("ranking/destruction",127); }}}
        if (ComboCount > 150)
            { if (CheckInventory("CRankAnnounced") == 0)
              { GiveInventory("CRankAnnounced",1);
                if (CheckInventory("IAmAQuietPersonWhoWantsMoreQuietRankings") == 0) { LocalAmbientSound("ranking/champion",127); }}}
        if (ComboCount > 200)
            { if (CheckInventory("BRankAnnounced") == 0)
              { GiveInventory("BRankAnnounced",1);
                if (CheckInventory("IAmAQuietPersonWhoWantsMoreQuietRankings") == 0) { LocalAmbientSound("ranking/behemoth",127); }}}
        if (ComboCount > 250)
            { if (CheckInventory("ARankAnnounced") == 0)
              { GiveInventory("ARankAnnounced",1);
                if (CheckInventory("IAmAQuietPersonWhoWantsMoreQuietRankings") == 0) { LocalAmbientSound("ranking/annihilator",127); }}}
        if (ComboCount > 300)
            { if (CheckInventory("SRankAnnounced") == 0)
              { GiveInventory("SRankAnnounced",1);
                if (CheckInventory("IAmAQuietPersonWhoWantsMoreQuietRankings") == 0) { LocalAmbientSound("ranking/slayer",127); }}}

        if (ComboCount < 50 && CheckInventory("FRankAnnounced") == 1)
           { RemoveFRankAnnouncer++; }
           else { RemoveFRankAnnouncer = 0; }
        if (ComboCount < 100 && CheckInventory("DRankAnnounced") == 1)
           { RemoveDRankAnnouncer++; }
           else { RemoveDRankAnnouncer = 0; }
        if (ComboCount < 150 && CheckInventory("CRankAnnounced") == 1)
           { RemoveCRankAnnouncer++; }
           else { RemoveCRankAnnouncer = 0; }
        if (ComboCount < 200 && CheckInventory("BRankAnnounced") == 1)
           { RemoveBRankAnnouncer++; }
           else { RemoveBRankAnnouncer = 0; }
        if (ComboCount < 250 && CheckInventory("ARankAnnounced") == 1)
           { RemoveARankAnnouncer++; }
           else { RemoveARankAnnouncer = 0; }
        if (ComboCount < 300 && CheckInventory("SRankAnnounced") == 1)
           { RemoveSRankAnnouncer++; }
           else { RemoveSRankAnnouncer = 0; }

           if (RemoveFRankAnnouncer == 525) { TakeInventory("FRankAnnounced",1); }
           if (RemoveDRankAnnouncer == 525) { TakeInventory("DRankAnnounced",1); }
           if (RemoveCRankAnnouncer == 525) { TakeInventory("CRankAnnounced",1); }
           if (RemoveBRankAnnouncer == 525) { TakeInventory("BRankAnnounced",1); }
           if (RemoveARankAnnouncer == 525) { TakeInventory("ARankAnnounced",1); }
           if (RemoveSRankAnnouncer == 525) { TakeInventory("SRankAnnounced",1); }

        // Special move bollocks
        if (GetCvar("dst_nospecials") == 0)
        {

        // This entire system is so brute force it's not even funny.
        // I never said I was an elegant or even a good coder, but this is still
        // extremely brute force, even for me.
        // It's "simply" a matter of checking for what buttons the player pushed,
        // then giving an inventory item. If the player pushes the button and the
        // inventory item is still there, they're given another item saying that
        // they double-tapped the button.

          if (keypressed(BT_MOVERIGHT) && CheckInventory("SynthFire") == 1)//keypressed(BT_ATTACK))
            { if ( ((CheckInventory("HaggarModeOn") == 1 && CheckInventory("KiMeterCounter") >= 300) || (CheckInventory("RangedModeOn") == 1 && CheckInventory("KiMeterCounter") >= 300) || (CheckInventory("TricksterModeOn") == 1 && CheckInventory("KiMeterCounter") >= 200) ) && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyRight") >= 1) { GiveInventory("DoubleTapRight",1); GiveInventory("DoubleTapCooldown",16); }
                      else { GiveInventory("DoubleTapReadyRight",6); }}}
          if (keypressed(BT_MOVELEFT) && CheckInventory("SynthFire") == 1)//keypressed(BT_ATTACK))
            { if ( ((CheckInventory("HaggarModeOn") == 1 && CheckInventory("KiMeterCounter") >= 300) || (CheckInventory("RangedModeOn") == 1 && CheckInventory("KiMeterCounter") >= 300) || (CheckInventory("TricksterModeOn") == 1 && CheckInventory("KiMeterCounter") >= 200) ) && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyLeft") >= 1) { GiveInventory("DoubleTapLeft",1); GiveInventory("DoubleTapCooldown",16); }
                      else { GiveInventory("DoubleTapReadyLeft",6); }}}
          if (keypressed(BT_FORWARD) && CheckInventory("SynthFire") == 1)//keypressed(BT_ATTACK))
            { if ( ((CheckInventory("HaggarModeOn") == 1 && CheckInventory("KiMeterCounter") >= 300) || (CheckInventory("RangedModeOn") == 1 && CheckInventory("KiMeterCounter") >= 300) || (CheckInventory("TricksterModeOn") == 1 && CheckInventory("KiMeterCounter") >= 200) ) && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyForward") >= 1) { GiveInventory("DoubleTapForward",1); GiveInventory("DoubleTapCooldown",16); }
                      else { GiveInventory("DoubleTapReadyForward",6); }}}
          if (keypressed(BT_BACK) && CheckInventory("SynthFire") == 1)//keypressed(BT_ATTACK))
            { if ( ((CheckInventory("HaggarModeOn") == 1 && CheckInventory("KiMeterCounter") >= 300) || (CheckInventory("RangedModeOn") == 1 && CheckInventory("KiMeterCounter") >= 300) || (CheckInventory("TricksterModeOn") == 1 && CheckInventory("KiMeterCounter") >= 200) ) && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyBack") >= 1) { GiveInventory("DoubleTapBack",1); GiveInventory("DoubleTapCooldown",16); }
                      else { GiveInventory("DoubleTapReadyBack",6); }}}
        }

    // ============= END GENERIC COPY-PASTED SHIT

        // Cvar nonsense.

        if (GetCvar("dst_infinitemeter") == 1) { GiveInventory("KiMeterCounter",10); }
        if (GetCvar("compat_disabletaunts") == 1) { GiveInventory("NoTauntAllowed",1); }
           else { TakeInventory("NoTauntAllowed",1); }

        // Health nonsense
        if( GetCVar( "dst_doomhealth" ) == 1 )
        {
            // If we're using ye olde doome health rules,
            // set the player's inventory count for the health markers based off health
            int health = GetActorProperty( 0, APROP_HEALTH );
            
            TakeInventory( "ContraLifeToken", 0x7FFFFFFF );
            GiveInventory( "ContraLifeToken", ( health + 10 ) / 10 );
            
            TakeInventory( "OverLifeToken", 0x7FFFFFFF );
            if( health > 100 )
            {
                GiveInventory( "OverLifeToken", ( health - 90 ) / 10 );
            }
        }

        TakeInventory("DoubleTapCooldown",1);
        TakeInventory("EnviroDamageCooldown",1);
        TakeInventory("DoubleTapReadyRight",1);
        TakeInventory("DoubleTapReadyForward",1);
        TakeInventory("DoubleTapReadyLeft",1);
        TakeInventory("DoubleTapReadyBack",1);
        TakeInventory("MidCombat",1);
        TakeInventory("IsDodging",1);
        TakeInventory("HenshinCooldown",1);
        //TakeInventory("PointsSpeedrunning",1);
        if (CheckInventory("EnviroDamageCooldown") == 0) { TakeInventory("EnviroDamageCount",3); }
    
        // If the player still has life left, they get full life.
        // How's that for redundancy?
        // Next up: PEOPLE DIE WHEN THEY ARE KILLED.
        if( GetCVar( "dst_doomhealth" ) == 0 )
        {
            if (CheckInventory("ContraLifeToken") >= 1 || CheckInventory("OverLifeToken") >= 1 || CheckInventory("ContraArmorToken") >= 1)
            { GiveInventory("999Health",999); }
            else
            { SetActorProperty(0,APROP_HEALTH,1); }
        }

        // NYRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
        if (GetCvar("dst_runmod") < 10001 && GetCvar("dst_runmod") > -2) // I forget what the maximum integer is. 36525? Well, whatever, anything beyond that and it'll crash.
        {
            speedmod = max(0, condFalse(GetCVar("dst_runmod"), 100)) * 0.01; // Get the percentage equivalent of the value...
            SetActorProperty(0, APROP_Speed, speedmod); // And adjust the player's speed accordingly.
        }

        if (CheckInventory("ContraLifeToken") != 0 && CheckInventory("OverLifeToken") != 0 && CheckInventory("ContraArmorToken") != 0 && CheckInventory("IAmATraditionalDoomerWhoLikesNumbersOverTokens") != 0)
        { SetPlayerProperty(0,1,PROP_BUDDHA); }
        else
        { SetPlayerProperty(0,0,PROP_BUDDHA); }

        if (CheckInventory("FlashlightOn") == 1) { GiveInventory("SSHNightVision",1); }

        Delay(1);

        if (isDead(0))
        {
            TakeInventory("FlashlightOn",1);//flashlightOn[pln] = 0;
            TakeInventory("SSHNightVision",1);
            if (GetCvar("dst_debug") == 1) { Log(s:"Player ", d:pln, s:" dead, terminating SINO_ENTER."); }
            terminate;
        }
    }
}

script SINO_JUSTFRAME ENTER
{
    int buttons;
    while (1)
    {
        buttons = GetPlayerInput(-1, INPUT_BUTTONS);

        if (buttons & BT_ATTACK)
        {
          if (CheckInventory("JustFrameAcquired") == 0)
          {
            GiveInventory("JustFrame",1);
            GiveInventory("JustFrameAcquired",1);
            delay(2);
            TakeInventory("JustFrame",1);
          }
        }
        else
        {
            TakeInventory("JustFrame",1);
            TakeInventory("JustFrameAcquired",1);
        }

        if (isDead(0)) { terminate; }
        delay(1);
    }
}