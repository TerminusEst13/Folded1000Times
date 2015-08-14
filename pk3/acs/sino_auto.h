script SINO_ENTER ENTER
{
    int buttons;
    int oldbuttons;
    int MichaelAngleoBatio;
    int xxx;
    int yyy;
    int xxx2;
    int yyy2;
    int GetSomeHealthAlready;
    int JetpackFuelCounter;
    int pitchy;

    //PrintBold(s:"script firing");

    if (CheckInventory("IsJungHaeLin") == 1)
    {
        //PrintBold(s:"is hae-lin");
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

    while (1)
    {
        if (CheckInventory("IsJungHaeLin") == 1)
        { terminate; }

        TakeInventory("SwapCooldown",1);

        // Punchcombo shit
        if (CheckInventory("InCombat") == 0) { TakeInventory("PunchComboCounter",1); }
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
            TakeInventory("InTheAir",0x7FFFFFFF);
        }
        else
        {
            TakeInventory("OnTheGround",1);
            GiveInventory("InTheAir",1);
        }

        buttons = GetPlayerInput(-1, INPUT_BUTTONS);
        MichaelAngleoBatio = GetActorAngle(0) >> 8;

        pitchy = GetActorPitch(0);
        //Print(d:pitchy);

        // In Zandro 2.0, for some reason, Shihong is able to execute Hae-Lin's dash.
        // This is despite the fact that WEEB_ENTER isn't executing on Shihong, isn't
        // reading her inputs, and that specific block isn't firing. I checked. I
        // even put Print spam everywhere. And yet, somehow, the Hae-Lin dash is still
        // happening.
        // This is fixed in 3.0, but only Lord knows how long it'll be until that comes out.
        // Until then, have a dumb hack.
        GiveInventory("GhostStepCooldown",100);

        // The jet booster. Thrusts you across distances at great speeds, gives you ghost.
        // Only activates if run and a direction is pushed.
        if (buttons & BT_SPEED && CheckInventory("JetpackFuel") > 0 && buttons & (BT_FORWARD | BT_BACK | BT_MOVELEFT | BT_MOVERIGHT))
        {
        // Checks for the player's pitch and checks how high they're looking up.
        // The further up they're looking, the slower the jet speed. Doom's
        // vertical-ness is stretched down and squashed, so moving fast horizontally
        // isn't so much a big deal, but moving vertically fast is.
        // This is so brute force it's not even funny. If I wasn't going to simply
        // modify the player's APROP_SPEED for the style swapping mechanic or ds_runmod,
        // I wouldn't need to do this. But I am, so I have to.
        // May Carmack forgive me.

          if (CheckInventory("JetpackFuel") >= 20 || CheckInventory("JetpackModeOn") == 1)
          {
            if (pitchy >= 0) // Pitch is an inverted value.
            {                // Looking down increases it, looking up decreases.
              GiveInventory("JetpackSpeedPower1",1);
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
            }
            if (pitchy < 0 && pitchy >= -500)
            {
              TakeInventory("JetpackSpeedPower1",1);
              GiveInventory("JetpackSpeedPower2",1);
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
            }
            if (pitchy < -500 && pitchy >= -1000)
            {
              TakeInventory("JetpackSpeedPower1",1);
              TakeInventory("JetpackSpeedPower2",1);
              GiveInventory("JetpackSpeedPower3",1);
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
            }
            if (pitchy < -1000 && pitchy >= -1500)
            {
              TakeInventory("JetpackSpeedPower1",1);
              TakeInventory("JetpackSpeedPower2",1);
              TakeInventory("JetpackSpeedPower3",1);
              GiveInventory("JetpackSpeedPower4",1);
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
            }
            if (pitchy < -1500 && pitchy >= -2000)
            {
              TakeInventory("JetpackSpeedPower1",1);
              TakeInventory("JetpackSpeedPower2",1);
              TakeInventory("JetpackSpeedPower3",1);
              TakeInventory("JetpackSpeedPower4",1);
              GiveInventory("JetpackSpeedPower5",1);
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
            }
            if (pitchy < -2000 && pitchy >= -2500)
            {
              TakeInventory("JetpackSpeedPower1",1);
              TakeInventory("JetpackSpeedPower2",1);
              TakeInventory("JetpackSpeedPower3",1);
              TakeInventory("JetpackSpeedPower4",1);
              TakeInventory("JetpackSpeedPower5",1);
              GiveInventory("JetpackSpeedPower6",1);
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
            }
            if (pitchy < -2500 && pitchy >= -3000)
            {
              TakeInventory("JetpackSpeedPower1",1);
              TakeInventory("JetpackSpeedPower2",1);
              TakeInventory("JetpackSpeedPower3",1);
              TakeInventory("JetpackSpeedPower4",1);
              TakeInventory("JetpackSpeedPower5",1);
              TakeInventory("JetpackSpeedPower6",1);
              GiveInventory("JetpackSpeedPower7",1);
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
            }
            if (pitchy < -3000 && pitchy >= -3500)
            {
              TakeInventory("JetpackSpeedPower1",1);
              TakeInventory("JetpackSpeedPower2",1);
              TakeInventory("JetpackSpeedPower3",1);
              TakeInventory("JetpackSpeedPower4",1);
              TakeInventory("JetpackSpeedPower5",1);
              TakeInventory("JetpackSpeedPower6",1);
              TakeInventory("JetpackSpeedPower7",1);
              GiveInventory("JetpackSpeedPower8",1);
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
            }
            if (pitchy < -3500 && pitchy >= -4000)
            {
              TakeInventory("JetpackSpeedPower1",1);
              TakeInventory("JetpackSpeedPower2",1);
              TakeInventory("JetpackSpeedPower3",1);
              TakeInventory("JetpackSpeedPower4",1);
              TakeInventory("JetpackSpeedPower5",1);
              TakeInventory("JetpackSpeedPower6",1);
              TakeInventory("JetpackSpeedPower7",1);
              TakeInventory("JetpackSpeedPower8",1);
              GiveInventory("JetpackSpeedPower9",1);
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
            }
            if (pitchy < -4000 && pitchy >= -4500)
            {
              TakeInventory("JetpackSpeedPower1",1);
              TakeInventory("JetpackSpeedPower2",1);
              TakeInventory("JetpackSpeedPower3",1);
              TakeInventory("JetpackSpeedPower4",1);
              TakeInventory("JetpackSpeedPower5",1);
              TakeInventory("JetpackSpeedPower6",1);
              TakeInventory("JetpackSpeedPower7",1);
              TakeInventory("JetpackSpeedPower8",1);
              TakeInventory("JetpackSpeedPower9",1);
              GiveInventory("JetpackSpeedPower10",1);
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
            }
            if (pitchy < -4500 && pitchy >= -5000)
            {
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
              GiveInventory("JetpackSpeedPower11",1);
              TakeInventory("JetpackSpeedPower12",1);
              TakeInventory("JetpackSpeedPower13",1);
              TakeInventory("JetpackSpeedPower14",1);
              TakeInventory("JetpackSpeedPower15",1);
              TakeInventory("JetpackSpeedPower16",1);
              TakeInventory("JetpackSpeedPower17",1);
              TakeInventory("JetpackSpeedPower18",1);
              TakeInventory("JetpackSpeedPower19",1);
              TakeInventory("JetpackSpeedPower20",1);
            }
            if (pitchy < -5000 && pitchy >= -5500)
            {
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
              GiveInventory("JetpackSpeedPower12",1);
              TakeInventory("JetpackSpeedPower13",1);
              TakeInventory("JetpackSpeedPower14",1);
              TakeInventory("JetpackSpeedPower15",1);
              TakeInventory("JetpackSpeedPower16",1);
              TakeInventory("JetpackSpeedPower17",1);
              TakeInventory("JetpackSpeedPower18",1);
              TakeInventory("JetpackSpeedPower19",1);
              TakeInventory("JetpackSpeedPower20",1);
            }
            if (pitchy < -5500 && pitchy >= -6000) // This is about where Software users will stop.
            {                                      // The highest they can look is -5825.
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
              GiveInventory("JetpackSpeedPower13",1);
              TakeInventory("JetpackSpeedPower14",1);
              TakeInventory("JetpackSpeedPower15",1);
              TakeInventory("JetpackSpeedPower16",1);
              TakeInventory("JetpackSpeedPower17",1);
              TakeInventory("JetpackSpeedPower18",1);
              TakeInventory("JetpackSpeedPower19",1);
              TakeInventory("JetpackSpeedPower20",1);
            }
            if (pitchy < -6000 && pitchy >= -6500)
            {
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
              GiveInventory("JetpackSpeedPower14",1);
              TakeInventory("JetpackSpeedPower15",1);
              TakeInventory("JetpackSpeedPower16",1);
              TakeInventory("JetpackSpeedPower17",1);
              TakeInventory("JetpackSpeedPower18",1);
              TakeInventory("JetpackSpeedPower19",1);
              TakeInventory("JetpackSpeedPower20",1);
            }
            if (pitchy < -6500 && pitchy >= -7000)
            {
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
              GiveInventory("JetpackSpeedPower15",1);
              TakeInventory("JetpackSpeedPower16",1);
              TakeInventory("JetpackSpeedPower17",1);
              TakeInventory("JetpackSpeedPower18",1);
              TakeInventory("JetpackSpeedPower19",1);
              TakeInventory("JetpackSpeedPower20",1);
            }
            if (pitchy < -7000 && pitchy >= -7500)
            {
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
              GiveInventory("JetpackSpeedPower16",1);
              TakeInventory("JetpackSpeedPower17",1);
              TakeInventory("JetpackSpeedPower18",1);
              TakeInventory("JetpackSpeedPower19",1);
              TakeInventory("JetpackSpeedPower20",1);
            }
            if (pitchy < -7500 && pitchy >= -8000)
            {
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
              GiveInventory("JetpackSpeedPower17",1);
              TakeInventory("JetpackSpeedPower18",1);
              TakeInventory("JetpackSpeedPower19",1);
              TakeInventory("JetpackSpeedPower20",1);
            }
            if (pitchy < -8000 && pitchy >= -8500)
            {
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
              GiveInventory("JetpackSpeedPower18",1);
              TakeInventory("JetpackSpeedPower19",1);
              TakeInventory("JetpackSpeedPower20",1);
            }
            if (pitchy < -8500 && pitchy >= -9000)
            {
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
              GiveInventory("JetpackSpeedPower19",1);
              TakeInventory("JetpackSpeedPower20",1);
            }
            if (pitchy < -9000) // OpenGL users can go far beyond this, but if you're looking
            {                   // above this value you pretty much just want to go up.
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
              GiveInventory("JetpackSpeedPower20",1);
            }
            SetPlayerProperty(0,1,PROP_FLY);//GiveInventory("JetpackFlightPower",1);
            // PowerFlight has a few issues. One being it thrusts you upwards even if
            // you're not doing anything. Two being it jerks your view back to the
            // original pitch once it's taken away. It's a pain. This method may
            // be archaic, but it doesn't have those issues.
            GiveInventory("DodgeGhostOn",1);
            TakeInventory("JetpackModeOff",1);
            TakeInventory("JetpackFuel",2);
            if (CheckInventory("JetpackModeOn") == 0)
            {
              ActivatorSound("shihong/thruster",127);
              GiveInventory("JetpackModeOn",1);
            }
          }
        }
        else
        {
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
        }

        // Booster fuel regeneration.
        // Fuel regenerates faster in Dodger mode. But it also regenerates faster when on the ground.
        // First it checks to see whether you're in Dodger mode, then it checks to see whether you're on the ground or in the air.
        if (CheckInventory("JetpackModeOff") == 1)
        {
            if (CheckInventory("TricksterModeOn") == 1 && ( (JetpackFuelCounter >= 3 && CheckInventory("OnTheGround") == 0) | (JetpackFuelCounter >= 2 && CheckInventory("OnTheGround") == 1) ) )
            {
              GiveInventory("JetpackFuel",1);
              JetpackFuelCounter = 0;
            }
            else if (CheckInventory("TricksterModeOn") == 0 && ( (JetpackFuelCounter >= 5 && CheckInventory("OnTheGround") == 0) | (JetpackFuelCounter >= 4 && CheckInventory("OnTheGround") == 1) ) )
            {
              GiveInventory("JetpackFuel",1);
              JetpackFuelCounter = 0;
            }
            JetpackFuelCounter++;
        }

        if (buttons & BT_ALTATTACK)
            { GiveInventory("SynthAltFire",1); }
          else
            { TakeInventory("SynthAltFire",1); }

        if (buttons & BT_ATTACK)
            { GiveInventory("SynthFire",1); }
          else
            { TakeInventory("SynthFire",1); }

        // Temporary equipment workaround.
        if (CheckInventory("KharonOmen") == 1)
            { TakeInventory("KharonOmen",1); GiveInventory("01Tiger",1); }
        if (CheckInventory("KharonTestament") == 1)
            { TakeInventory("KharonTestament",1); GiveInventory("03Wolf",1); }
        if (CheckInventory("KharonExodus") == 1)
            { TakeInventory("KharonExodus",1); GiveInventory("05Dragon",1); }
        if (CheckInventory("KharonSabbath") == 1)
            { TakeInventory("KharonSabbath",1); GiveInventory("04Scorpions",1); }

        Delay(1);

        if (isDead(0))
        {
            terminate;
        }
    }
}

script SINO_ENTER_UNREPLACED ENTER
{
    int OldButtons;
    int Buttons;
    int SuperCount;
    int ComboCount;
    int KurtAngle;
    int RideTheLightning;
    int XMen;
    int Ys;
    int XMen2;
    int Ys2;
    int IsBrutal = 0;
    int mytid;
    int i, j, k, u, ang;
    int MarchOfTheImmortal;
    int IronArmor;
    int armor;
    int oarmor;
    int pln = PlayerNumber();
    int ZDum;
    int Angel;
    int xOffset, yOffset, zOffset;
    int xOffset2, yOffset2, zOffset2;
    int xOffset3, yOffset3, zOffset3;
    int velx, vely, velz;
    int nx, ny, nz;
    int nx2, ny2, nz2;
    int nx3, ny3, nz3;
    int ShieldTID;
    int SentTID;
    int TheAngerInside;
    int IntroChance;
    int ShieldHP;
    int SentinelHP;
    int NewShieldHP;
    int NewSentinelHP;
    int speedmod;
    int mtotal;
    int mkilled;
    int stotal;
    int sfound;
    int sfound2;
    int TimeStandStill;
    int RemoveFRankAnnouncer;
    int RemoveDRankAnnouncer;
    int RemoveCRankAnnouncer;
    int RemoveBRankAnnouncer;
    int RemoveARankAnnouncer;
    int RemoveSRankAnnouncer;
    int IFuckedTheGameUp;
    int DodgeCounter;
    int HaloTID;
    // 71 ints and counting!

    i = unusedTID(37000, 47000);
    u = unusedTID(37000, 47000);
    sfound = GetLevelInfo(LEVELINFO_FOUND_SECRETS);

    if (GetCvar("dst_debug") == 1) { Log(s:"WEEB_ENTER executing on player ", d:pln); }

    // If the player isn't playing as Hae-Lin, terminates.
    // Inter-character scripts running off each other will cause a cluster of problems.
    if (CheckInventory("IsJungHaeLin") == 1)
    {
        if (GetCvar("dst_debug") == 1) { Log(s:"Error: Player ", d:pln, s:" is not Shihong, terminating SINO_ENTER."); }
        terminate;
    }
    //if (CheckInventory("IsSSH") == 1) { terminate; }

    if (CheckInventory("ImAlive") == 0 && GameType() != GAME_TITLE_MAP)
    // If the player is spawning for the first time.
    // Don't run it on titlescreens, or else Things Would Happen.
    {
        // Check for if the metal jukebox is loaded as well.
        /*if (Spawn("DemonSteeleIsSuperCoolAndYouShouldProbablyPlayIt", GetActorX(0), GetActorY(0), GetActorZ(0), u))
        {
            Thing_Remove(u);
            MusicRandomizerIsIncluded = 1;
            GiveInventory("IAmAnAwesomePersonWhoLikesCoolMusic",1);
        }*/

        if (GetCvar("dst_omenstart") == 1)
        {
            GiveInventory("KharonOmen",1);
            GiveInventory("GotHammer",1);
        }

        if (GetCvar("dst_backpackstart") == 1)
        { GiveInventory("Backpack",1); }

    }
    else if (CheckInventory("ImAlive") == 1 && CheckInventory("AlreadyInLevel") == 0)
    // If the player isn't respawning but is entering a level fresh.
    {
        IntroChance = random(0,2);
        if (IntroChance == 2) { LocalAmbientSound("haelin/intro",127); }
        TakeInventory("PointsFoundAllSecrets",1);
        TakeInventory("PointsKilledMonsters",1);
        TakeInventory("MaidenHalo",1);
    }

    if (GetCvar("dst_doomhealth") == 1)
    {
        GiveInventory("IAmATraditionalDoomerWhoLikesNumbersOverTokens",1);
        NotADoomGame = 0;
    }
    else
    {
        TakeInventory("IAmATraditionalDoomerWhoLikesNumbersOverTokens",1);
        NotADoomGame = 1;
    }

    // Brutal Doom compatibility check.
    if (Spawn("Brutal_Blood",GetActorX(0),GetActorY(0),GetActorZ(0),i) || Spawn("BrutalPistol",GetActorX(0),GetActorY(0),GetActorZ(0),i) || GetCvar("dst_2brutal") == 1)
    {
        Thing_Remove(i);
        isbrutal = 1;
        GiveInventory("PointsIsBrutal",1);
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

    // If someone enters the map while having been overcharging the hammer.
    if (CheckInventory("HammerCharge") > 100)
    {
        TakeInventory("HammerCharge",100); // A bit brute-force, but they'll regain it back.
        SetAmmoCapacity("HammerCharge",100);
    }

    // Likewise, if someone enters while in Iron Maiden.
    if (CheckInventory("InIronMaiden") == 1) { ACS_ExecuteAlways(275,0,WEEB_DEC_CHANGEMUS,0,0); }
    
    if (GetCvar("dst_debug") == 1) { Log(s:"Entering while(1) loop on player ", d:pln); }

    while (1)
    {
        mytid = defaultTID(-1);
        //if (CheckInventory("ImAlive") == 1) { if (ConsolePlayerNumber() != PlayerNumber()) { terminate; } }

        ZDum  = GetActorZ(mytid) + 24.0;
        Angel = GetActorAngle(mytid);
        velx  = GetActorVelX(mytid); // I can't think of any witty names for these.
        vely  = GetActorVelY(mytid);
        velz  = GetActorVelZ(mytid);

        // Cvar nonsense.

        if (GetCvar("dst_infinitesouls") == 1) { GiveInventory("SuperMeterCounter",1); }
        if (GetCvar("compat_disabletaunts") == 1) { GiveInventory("NoTauntAllowed",1); }
           else { TakeInventory("NoTauntAllowed",1); }
           
        if (GetCvar("dst_gunsouls") == 0) { GiveInventory("IAmASkilledPersonWhoWantsOnlyMySwordToGiveSouls",1); }
           else { TakeInventory("IAmASkilledPersonWhoWantsOnlyMySwordToGiveSouls",1); }

        // If you do this mid-game, you're fucked.
        // Millions of games are fucked over monthly by accidental or intentional negligence.
        // Please, donate now to the Foundation for Unfucking Games, or FUG.
        if (GetCvar("dst_doomhealth") == 1) { GiveInventory("IAmATraditionalDoomerWhoLikesNumbersOverTokens",1); }
           else { TakeInventory("IAmATraditionalDoomerWhoLikesNumbersOverTokens",1); }
        if ( (NotADoomGame == 1 && CheckInventory("IAmATraditionalDoomerWhoLikesNumbersOverTokens") == 1) || (NotADoomGame == 0 && CheckInventory("IAmATraditionalDoomerWhoLikesNumbersOverTokens") == 0) || IFuckedTheGameUp == 1)
        {
           SetFont("BIGFONT");
           HudMessage(s:"PLEASE RESTART THE GAME";HUDMSG_PLAIN,13,CR_GOLD,0.5,0.2,5.25,0.5,0.5);
           IFuckedTheGameUp = 1;
        }

        // Points malarkey
        if (CheckInventory("Points") >= 10000)
        {
            TakeInventory("Points",10000);
            GiveInventory("ManPoints",1);
        }

        if (CheckInventory("ManPoints") >= 10000)
        {
            TakeInventory("ManPoints",10000);
            GiveInventory("OkuPoints",1);
        }

        mtotal = GetLevelInfo(LEVELINFO_TOTAL_MONSTERS);
        mkilled = GetLevelInfo(LEVELINFO_KILLED_MONSTERS);
        if (mtotal != 0 && mtotal == mkilled && CheckInventory("PointsKilledMonsters") == 0)
        {
        // Monster number can increase, be it through either resurrecting or summoning.
        // So because I can't check for the total amount on Unloading, the player is just
        // given a dummy token that indicates they got it, and pray that maps aren't so
        // in-depth that they suddenly spawn another massive amount as soon as the existing
        // amount is killed.
            GiveInventory("PointsKilledMonsters",1);
            if (mtotal <= 50) { GiveInventory("ManPoints",10); } // Vanilla Doom
            if (mtotal > 50 && mtotal <= 100) { GiveInventory("ManPoints",25); } // 1994 mapwad
            if (mtotal > 100 && mtotal <= 500) { GiveInventory("ManPoints",50); } // Scythe 2
            if (mtotal > 500 && mtotal <= 1000) { GiveInventory("ManPoints",100); } // Babby's first slaughtermap
            if (mtotal > 1000 && mtotal <= 5000) { GiveInventory("ManPoints",500); } // Slaughtermap
            if (mtotal > 5000 && mtotal <= 10000) { GiveInventory("ManPoints",1000); } // Chillax
            if (mtotal > 10000 && mtotal <= 50000) { GiveInventory("OkuPoints",1); } // OkuMap
            if (mtotal > 50000) { GiveInventory("OkuPoints",10); } // What the hell are you playing?!
        }

        stotal = GetLevelInfo(LEVELINFO_TOTAL_SECRETS); // Dunno if secret number can increase, though.
        sfound2 = sfound;
        sfound = GetLevelInfo(LEVELINFO_FOUND_SECRETS);
        // Found a secret.
        if (sfound > sfound2)
        {
            GiveInventory("ManPoints",1);
            sfound2 = sfound;
        }
        // Found all secrets.
        if (stotal != 0 && stotal == sfound && CheckInventory("PointsFoundAllSecrets") == 0)
        {
            GiveInventory("ManPoints",9); // Plus the previous 10000 for a total of 100000.
            GiveInventory("PointsFoundAllSecrets",1);
        }

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

        // I will not make a Hammertime joke. I will not make a Hammertime joke. I will not make a Hammertime joke.
        if (CheckInventory("HammerUp") == 1)
        {
           // Different levels of charging the hammer based on different states of the hammer
           // when you're holding it out. The more charge you have, the slower it charges.
           if (CheckInventory("HammerCharge") >= 90 && CheckInventory("HammerCharge") <= 100 )
               { if (RideTheLightning >= 34)
                  { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
               // Overcharging is put here because of the explicit need of the previous level to be
               // between 90 and 100, thanks to changing ammo capacities.
               // Everything else can just be "meh, more than X".
           else if (CheckInventory("HammerCharge") > 100)
               { if (RideTheLightning >= 8)
                  { GiveInventory("HammerCharge",1); GiveInventory("ChargeScreenFlash",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 80)
               { if (RideTheLightning >= 27)
                  { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 60)
               { if (RideTheLightning >= 22)
                  { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 40)
               { if (RideTheLightning >= 17)
                  { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 20)
               { if (RideTheLightning >= 12)
                  { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 0)
               { if (RideTheLightning >= 7)
                  { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
        }
        // If the player isn't holding the hammer, slowly take away ammo charge.
        else { if (RideTheLightning >= 40 && CheckInventory("HammerCharge") >= 30)
            { TakeInventory("HammerCharge",1); RideTheLightning = 0; }}
        RideTheLightning++;

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
        
        // THE SUPER COUNTER. Not the kind you lean on.
        SuperCount = CheckInventory("SuperMeterCounter");
        //SetInventory("SuperCounter1",SuperCount); // Life would be so much easier if this worked online.
        // This script changes the display on the HUD.
        // While SuperMeterCounter can be whatever, each of the bars on the HUD read 100 of SuperMeterCounter.
        // Because of this, I have to manually see exactly how much of each level the player has and then give
        // a dummy item which the bars then read.
        TakeInventory("SuperCounter1", 0x7FFFFFFF);
        GiveInventory("SuperCounter1", SuperCount);
        if (SuperCount > 100)
            { TakeInventory("SuperCounter2",0x7FFFFFFF);
              GiveInventory("SuperCounter2", SuperCount - 100); } //SetInventory("SuperCounter2",(SuperCount - 100)); }
            else { TakeInventory("SuperCounter2",0x7FFFFFFF); }
        if (SuperCount > 200)
            { TakeInventory("SuperCounter3",0x7FFFFFFF);
              GiveInventory("SuperCounter3", SuperCount - 200); } //SetInventory("SuperCounter3",(SuperCount - 200)); }
            else { TakeInventory("SuperCounter3",0x7FFFFFFF); }
        if (SuperCount > 300)
            { TakeInventory("SuperCounter4",0x7FFFFFFF);
              GiveInventory("SuperCounter4", SuperCount - 300); } //SetInventory("SuperCounter3",(SuperCount - 200)); }
            else { TakeInventory("SuperCounter4",0x7FFFFFFF); }
        // If the player has less than 20 of SuperMeterCounter, they slowly regenerate.
        if (SuperCount < 20) { if (TheAngerInside >= 280)
            { GiveInventory("SuperMeterCounter",1); TheAngerInside = 0; }}
        TheAngerInside++;

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

        // Global variables
        // In singleplayer, these make the weapon pickups read if the player have actually
        // picked up the weapons, and if so they...well...
        // They make the things spawn other things.
        // That makes sense. I promise.
        if (isSinglePlayer())
        {
            if (CheckInventory("GotShotgun") == 1) { GotShotgun = 1; }
            if (CheckInventory("GotCarronade") == 1) { GotCarronade = 1; }
            if (CheckInventory("GotUzi") == 1) { GotUzi = 1; }
            if (CheckInventory("GotHammer") == 1) { GotHam = 1; } // HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAM
            if (CheckInventory("GotIronMaiden") == 1) { GotIronMaiden = 1; } 
            if (CheckInventory("GotLegion") == 1) { GotLegion = 1; } 
            if (CheckInventory("GotFrosthammer") == 1) { GotFrosthammer = 1; } 
        }

        // Special move bollocks
        OldButtons = GetPlayerInput(-1, INPUT_OLDBUTTONS);
        Buttons = GetPlayerInput(-1, INPUT_BUTTONS);
        KurtAngle = GetActorAngle(0) >> 8;

        if (GetCvar("dst_nospecials") == 0)
        {
        // This entire system is so brute force it's not even funny.
        // I never said I was an elegant or even a good coder, but this is still
        // extremely brute force, even for me.
        // It's "simply" a matter of checking for what buttons the player pushed,
        // then giving an inventory item. If the player pushes the button and the
        // inventory item is still there, they're given another item saying that
        // they double-tapped the button.

          if (keypressed(BT_MOVERIGHT))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyRight") >= 1) { GiveInventory("DoubleTapRight",1); GiveInventory("DoubleTapCooldown",16); }
                      else { GiveInventory("DoubleTapReadyRight",6); }}}
          if (keypressed(BT_MOVELEFT))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyLeft") >= 1) { GiveInventory("DoubleTapLeft",1); GiveInventory("DoubleTapCooldown",16); }
                      else { GiveInventory("DoubleTapReadyLeft",6); }}}
          if (keypressed(BT_FORWARD))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyForward") >= 1) { GiveInventory("DoubleTapForward",1); GiveInventory("DoubleTapCooldown",16); }
                      else { GiveInventory("DoubleTapReadyForward",6); }}}
          if (keypressed(BT_BACK))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyBack") >= 1) { GiveInventory("DoubleTapBack",1); GiveInventory("DoubleTapCooldown",16); }
                      else { GiveInventory("DoubleTapReadyBack",6); }}}
          }      

        // SUPER SAIYAN HNNNNNNGGGGGGGGGGGGGGGGGGGGGHHHHHHHHHHH
        // HHHHHHHHHHHHHNNNNNNNNNNNNNNNNGGGGGGGGGGGGGGGGGGGGGHHHHHHHHHHH
        // HHHHHHHHHHHHHHHHHHNNNNNNNNNNNNNNNNNNNNNNNNNNNGGGGGGGGGGGGGGGHHHHHHHH
        // IRON MAIDEN SCRIPT
        // HELL FUCKING YEAH
        // THE MOST METAL SCRIPT IN ALL OF VIDEOGAMEDOM
        oarmor = armor;
        armor = CheckInventory("Armor");

        // Oarmor is always one tic behind armor. If Oarmor is higher than armor, the player took a hit.
        // Display a painflash as needed.
        if (oarmor > armor && CheckInventory("InIronMaiden") == 1)
        {
          ActivatorSound("iron/armorhit", 127);
          FadeRange(255,255,0,min(0.5,(oarmor-armor)*0.015),0,0,0,0.0,min(35.0,1.5*(oarmor-armor))/35); 
          GiveInventory("MidCombat",75);
          TakeInventory("HyperComboCounter",2);
        }

        if (CheckInventory("InIronMaiden") == 1)
        {

        // Gives differing levels of defenses based on the player's combo ranking.
        // The higher their rank, the more, uh, defense-y they are.
        GiveInventory("IronMaidenProtection",1);
        if (ComboCount <= 50) { TakeInventory("IronMaidenProtectionF",1); TakeInventory("IronMaidenProtectionD",1); TakeInventory("IronMaidenProtectionC",1); TakeInventory("IronMaidenProtectionB",1); TakeInventory("IronMaidenProtectionA",1); TakeInventory("IronMaidenProtectionS",1); }
        if (ComboCount > 50)
            { GiveInventory("IronMaidenProtectionF",1); TakeInventory("IronMaidenProtectionD",1); TakeInventory("IronMaidenProtectionC",1); TakeInventory("IronMaidenProtectionB",1); TakeInventory("IronMaidenProtectionA",1); TakeInventory("IronMaidenProtectionS",1); }
        if (ComboCount > 100)
            { GiveInventory("IronMaidenProtectionF",1); GiveInventory("IronMaidenProtectionD",1); TakeInventory("IronMaidenProtectionC",1); TakeInventory("IronMaidenProtectionB",1); TakeInventory("IronMaidenProtectionA",1); TakeInventory("IronMaidenProtectionS",1); }
        if (ComboCount > 150)
            { GiveInventory("IronMaidenProtectionF",1); GiveInventory("IronMaidenProtectionD",1); GiveInventory("IronMaidenProtectionC",1); TakeInventory("IronMaidenProtectionB",1); TakeInventory("IronMaidenProtectionA",1); TakeInventory("IronMaidenProtectionS",1); }
        if (ComboCount > 200)
            { GiveInventory("IronMaidenProtectionF",1); GiveInventory("IronMaidenProtectionD",1); GiveInventory("IronMaidenProtectionC",1); GiveInventory("IronMaidenProtectionB",1); TakeInventory("IronMaidenProtectionA",1); TakeInventory("IronMaidenProtectionS",1); }
        if (ComboCount > 250)
            { GiveInventory("IronMaidenProtectionF",1); GiveInventory("IronMaidenProtectionD",1); GiveInventory("IronMaidenProtectionC",1); GiveInventory("IronMaidenProtectionB",1); GiveInventory("IronMaidenProtectionA",1); TakeInventory("IronMaidenProtectionS",1); }
        if (ComboCount > 300)
            { GiveInventory("IronMaidenProtectionF",1); GiveInventory("IronMaidenProtectionD",1); GiveInventory("IronMaidenProtectionC",1); GiveInventory("IronMaidenProtectionB",1); GiveInventory("IronMaidenProtectionA",1); GiveInventory("IronMaidenProtectionS",1); }

          // Keeps going for as long as the player has meter.
          if (CheckInventory("SuperMeterCounter") > 0)
          {
            SetActorProperty(0,APROP_JUMPZ,10.0);

            // YO BRO
            // I'M TELLING YOU NOW
            // YOU CAN'T JUST CHECK YOUR LIFE
            // YOU GOTTA CHECK YOUR SOOOOOOOOOOUL
            if (CheckInventory("SuperMeterCounter") < 31 && CheckInventory("IronMaidenWarning") == 0)
            {
              GiveInventory("IronMaidenWarning",1);
              FadeRange(255,255,255,0.50,0,0,0,0,0.5);
              LocalAmbientSound("henshin/warning",127);
            }

            // If the player's manually de-activating with the, uh, Use Inventory thingermajob.
            if (CheckInventory("HenshinDeactivation") == 1)
            {
              GiveInventory("HenshinCooldown",35);
              LocalAmbientSound("henshin/complete",127);
              ActivatorSound("henshin/completedismiss",127);
              ACS_ExecuteWithResult(WEEB_DECORATE,WEEB_DEC_REMOVEKEBAB,0,0);
              MarchOfTheImmortal = 0;
              IronArmor = 0;
            }

            // Armor regeneration.
            if (IronArmor >= 3)
            {
              if (GetArmorType("IronMaidenArmor",PlayerNumber()) || GetArmorType("IronMaidenArmor2",PlayerNumber()))
              {
                  if (CheckInventory("Armor") < 30) { GiveInventory("IronMaidenArmor",1); }
                  GiveInventory("IronMaidenArmor",1);
              }
              else // A failsafe just in case players have somehow managed to get their hands on some other kind of armor.
              {
                  TakeInventory("Armor",armor);
                  GiveInventory("IronMaidenArmor",armor);
                  GiveInventory("IronMaidenArmor",1);
              }
              IronArmor = 0;
            }

            // Soul degeneration. Faster if in the middle of combat, due to burning more energy or something.
            if (CheckInventory("MidCombat") > 1)
            {
              if (MarchOfTheImmortal >= 21)
              {
                TakeInventory("SuperMeterCounter",1);
                MarchOfTheImmortal = 0;
              }
            }
            else
            {
              if (MarchOfTheImmortal >= 30)
              {
                TakeInventory("SuperMeterCounter",1);
                MarchOfTheImmortal = 0;
              }
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

        // NYRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
        if (GetCvar("dst_runmod") < 10001 && GetCvar("dst_runmod") > -2) // I forget what the maximum integer is. 36525? Well, whatever, anything beyond that and it'll crash.
        {
            speedmod = max(0, condFalse(GetCVar("dst_runmod"), 100)) * 0.01; // Get the percentage equivalent of the value...
            SetActorProperty(0, APROP_Speed, speedmod); // And adjust the player's speed accordingly.
        }

        // Yes, this mod is 100% compatible with Brutal Doom. Absolutely nothing bad will happen!
        if (isbrutal)
        {
            k = unusedTID(23000, 33000);
                
            if (ThingCountName("GoldenBoner",0) < (20 * PlayerCount()))
                { Spawn("GoldenBoner",GetActorX(0),GetActorY(0),GetActorZ(0),k); }

            Thing_Hate(k,mytid,2);
            Thing_ChangeTID(k,0);
        }

        // Clientside cvar arrays.
        if (array_recoilrules[pln]) { GiveInventory("IAmASillyPersonWhoDoesntLikeRecoil", 1); }
        else { TakeInventory("IAmASillyPersonWhoDoesntLikeRecoil", 0x7FFFFFFF); }
        if (array_autoswitch[pln]) { GiveInventory("IAmAnOkayPersonWhoLikesToAutoSwitch", 1); }
        else { TakeInventory("IAmAnOkayPersonWhoLikesToAutoSwitch", 0x7FFFFFFF); }
        if (array_beepbeepbeep[pln]) { GiveInventory("IAmADumbPersonWhoWillProbablyAccidentallyDie",1); }
        else { TakeInventory("IAmADumbPersonWhoWillProbablyAccidentallyDie", 0x7FFFFFFF); }
        if (array_nopan[pln]) { GiveInventory("IAmABoringPersonWhoThinksPointsAreForNerds",1); }
        else { TakeInventory("IAmABoringPersonWhoThinksPointsAreForNerds", 0x7FFFFFFF); }
        if (array_noannounce[pln]) { GiveInventory("IAmAQuietPersonWhoWantsMoreQuietRankings",1); }
        else { TakeInventory("IAmAQuietPersonWhoWantsMoreQuietRankings",0x7FFFFFFF); }

        if (flashlightOn[pln])
            { GiveInventory("FlashlightSpawner",1); }

        if (CheckInventory("ContraLifeToken") != 0 && CheckInventory("OverLifeToken") != 0 && CheckInventory("ContraArmorToken") != 0 && CheckInventory("IAmATraditionalDoomerWhoLikesNumbersOverTokens") != 0)
        { SetPlayerProperty(0,1,PROP_BUDDHA); }
        else
        { SetPlayerProperty(0,0,PROP_BUDDHA); }
        
        Delay(1);
        // RIP in peas.
        if (isDead(0))
        {
            Thing_Remove(SentTID);
            SentTID = 0;
            Thing_Remove(ShieldTID);
            ShieldTID = 0;
            flashlightOn[pln] = 0;
            TakeInventory("SentinelUp",1);
            TakeInventory("SentinelActive",1);
            TakeInventory("BlindGuardianShieldUp",1);
            TakeInventory("BlindGuardianShieldActive",1);
            TakeInventory("SentinelLifeCounter",0x7FFFFFFF);
            TakeInventory("BlindGuardianLifeCounter",0x7FFFFFFF);
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