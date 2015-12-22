// Original walljump script by Xaser, manipulated and tweaked and bastardized for my own purposes.
script SINO_DOUBLEJUMP ENTER
{
    int buttons;
    int preventReset;

    if (CheckInventory("IsJungHaeLin") == 1)
    { terminate; }

    while(1) // Keep looping this script continuously.
    {
        // Check if the player is in the air.
        if(CheckInventory("InTheAir") > 5)
        {
            while(GetPlayerInput(-1, INPUT_BUTTONS) & BT_JUMP && CheckInventory("KickJumped") == 0) { delay(1); }
            // Allow for only one kick-jump per normal jump. Keep looping as long
            // as the player is off the ground.
            while(CheckInventory("InTheAir") > 5)
            {
                if(GetPlayerInput(-1, INPUT_BUTTONS) & BT_CROUCH && CheckInventory("TricksterModeOn") == 1)
                {
                    // Now attempt a kick-jump. Check to see if the player is close enough to a wall by
                    // attempting to spawn a dummy object and checking for its existence.
                    Spawn("MapSpot2",GetActorX(0),GetActorY(0),GetActorZ(0)+8.0,801+PlayerNumber());
                    SpawnProjectile(801+PlayerNumber(), "RadMarker24", 0, 1, 0, 0, 901+PlayerNumber());
                    delay(1);
                    if(thingcount(0,901+PlayerNumber())<1 || GetActorZ(901+PlayerNumber())!=GetActorZ(801+PlayerNumber())) // If the object hasn't spawned...
                    {
                        LocalAmbientSound("shihong/wallgrab", 127);
                        while(GetPlayerInput(-1, INPUT_BUTTONS) & BT_CROUCH)
                        {
                            GiveInventory("GrabbingTheWall",1);
		                    SetActorVelocity(0,0,0,0,0,1);
                            SetActorProperty(0,APROP_Gravity,0.0);
                            SetPlayerProperty(0,1,PROP_FROZEN);
                            delay(1);
                        }
                        TakeInventory("GrabbingTheWall",1);
                        //GiveInventory("WallGrabbed",1); - On second thought, limiting this is dumb.
                        SetActorProperty(0,APROP_Gravity,0.6);
                        SetPlayerProperty(0,0,PROP_FROZEN);
                    }
                    Thing_Remove(801+PlayerNumber());
                }

                if (isDead(0))
                { terminate; }
                delay(1);
            }
            //TakeInventory("KickJumped",1); // reset the kickJump switch. Allow for a later jump.
            //TakeInventory("WallGrabbed",1); // reset the wallgrab switch.
            //Actually, nah, these are taken away in the main Enter script.
        }

        if (isDead(0))
        { terminate; }
        delay(1);
    }
}

// Camera turning script by ijon tichy, again bastardized for my own purposes.
script SINO_TURN (int degrees, int factor, int direction) net clientside
{
    if (degrees < 0)
    {
        degrees *= -1;
        direction = cond(direction == CLOCKWISE, COUNTERCLOCKWISE, CLOCKWISE);
    }
    
    factor = cond(factor, factor, 4);

    int prevDegrees, addDegrees, curAngle;
    int curDegrees = 0;
    int floatDegrees = itof(degrees);
    int dirMult = cond(direction == CLOCKWISE, -1, 1);

    while (curDegrees < (floatDegrees - 0.1))
    {
        prevDegrees = curDegrees;
        addDegrees = (floatDegrees - curDegrees) / factor;
        curDegrees += addDegrees;

        SetActorAngle(0, GetActorAngle(0) + ((addDegrees * dirMult) / 360)); //}
        Delay(1);
    }

    addDegrees = floatDegrees - curDegrees;

    SetActorAngle(0, GetActorAngle(0) + ((addDegrees * dirMult) / 360));
}

// Brute-force jetbooster script, by me! But it's bad.
script SINO_JETBOOSTER ENTER
{
    int buttons;
    int pitchy;
    int JetpackFuelCounter;
    int KurtAngle;

    while (1)
    {
        if (CheckInventory("IsJungHaeLin") == 1)
        { terminate; }

        KurtAngle = GetActorAngle(0) >> 8;
        buttons = GetPlayerInput(-1, INPUT_BUTTONS);

        pitchy = GetActorPitch(0);

    // GET OUTTA DODGE
        if (CheckInventory("JetpackCooldown") == 0 && CheckInventory("JetpackFuel") > 0 && CheckInventory("GrabbingTheWall") == 0)
        {
          // Simple stuff. If the player hits Run and another button, they get thrown in a direction
          // and are given a powerup and a cooldown.
          if (buttons & BT_SPEED && ( buttons & BT_FORWARD | buttons & BT_MOVELEFT | buttons & BT_BACK | buttons & BT_MOVERIGHT ) )
          {
              if (buttons & BT_FORWARD) { ThrustThing(KurtAngle+0,25,0,0); }
              if (buttons & BT_MOVELEFT) { ThrustThing(KurtAngle+64,25,0,0); }
              if (buttons & BT_BACK) { ThrustThing(KurtAngle+128,25,0,0); }
              if (buttons & BT_MOVERIGHT) { ThrustThing(KurtAngle+192,25,0,0); }
              ThrustThingZ(0,18,0,0);
              ActivatorSound("shihong/thruster",127);
              if (CheckInventory("TricksterModeOn") == 0) { GiveInventory("JetpackThrustLimit",30); }
                  else { GiveInventory("JetpackThrustLimit",15); }
              if (CheckInventory("TricksterModeOn") == 0) { GiveInventory("JetpackCooldown",15); }
                  else { GiveInventory("JetpackCooldown",14); }
              TakeInventory("JetpackFuel",20);
              ACS_ExecuteAlways(267,0,6,0,0);
          }
        }

        // Booster fuel regeneration.
        // Fuel regenerates faster in Dodger mode. But it also regenerates faster when on the ground.
        // First it checks to see whether you're in Dodger mode, then it checks to see whether you're on the ground or in the air.
        if (CheckInventory("JetpackThrustLimit") == 0)
        {
            if (CheckInventory("TricksterModeOn") == 1 && JetpackFuelCounter >= 1)
            {
              GiveInventory("JetpackFuel",1);
              JetpackFuelCounter = 0;
            }
            else if (CheckInventory("TricksterModeOn") == 0 && JetpackFuelCounter >= 3)
            {
              GiveInventory("JetpackFuel",1);
              JetpackFuelCounter = 0;
            }
            JetpackFuelCounter++;
        }

        Delay(1);
        if (isDead(0))
        { terminate; }
    }
}

/*


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
        if (buttons & BT_SPEED && CheckInventory("JetpackFuel") > 0 && buttons & (BT_FORWARD | BT_BACK | BT_MOVELEFT | BT_MOVERIGHT) && CheckInventory("GrabbingTheWall") == 0)
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
            if (pitchy == 0) // Pitch is an inverted value.
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
            if (pitchy > 0 && pitchy <= 500)
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
            if (pitchy > 500 && pitchy <= 1000)
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
            if (pitchy > 1000 && pitchy <= 1500)
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
            if (pitchy > 1500 && pitchy <= 2000)
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
            if (pitchy > 2000 && pitchy <= 2500)
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
            if (pitchy > 2500 && pitchy <= 3000)
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
            if (pitchy > 3000 && pitchy <= 3500)
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
            if (pitchy > 3500 && pitchy <= 4000)
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
            if (pitchy > 4000 && pitchy <= 4500)
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
            if (pitchy > 4500 && pitchy <= 5000)
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
            if (pitchy > 5000 && pitchy <= 5500)
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
            if (pitchy > 5500 && pitchy <= 6000) // This is about where Software users will stop.
            {                                      // The highest they can look is 5825.
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
            if (pitchy > 6000 && pitchy <= 6500)
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
            if (pitchy > 6500 && pitchy <= 7000)
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
            if (pitchy > 7000 && pitchy <= 7500)
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
            if (pitchy > 7500 && pitchy <= 8000)
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
            if (pitchy > 8000 && pitchy <= 8500)
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
            if (pitchy > 8500 && pitchy <= 9000)
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
            if (pitchy > 9000) // OpenGL users can go far beyond this, but if you're looking
            {                   // above this value you pretty much just want to go down.
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
            if (CheckInventory("ShadowCloak") == 0) { GiveInventory("DodgeGhostOff",1); }
            GiveInventory("JetpackModeOff",1);
        }

        // Booster fuel regeneration.
        // Fuel regenerates faster in Dodger mode. But it also regenerates faster when on the ground.
        // First it checks to see whether you're in Dodger mode, then it checks to see whether you're on the ground or in the air.
        if (CheckInventory("JetpackModeOff") == 1)
        {
            if (CheckInventory("TricksterModeOn") == 1 && ( (JetpackFuelCounter >= 2 && CheckInventory("OnTheGround") == 0) | (JetpackFuelCounter >= 2 && CheckInventory("OnTheGround") == 1) ) )
            {
              GiveInventory("JetpackFuel",1);
              JetpackFuelCounter = 0;
            }
            else if (CheckInventory("TricksterModeOn") == 0 && ( (JetpackFuelCounter >= 4 && CheckInventory("OnTheGround") == 0) | (JetpackFuelCounter >= 4 && CheckInventory("OnTheGround") == 1) ) )
            {
              GiveInventory("JetpackFuel",1);
              JetpackFuelCounter = 0;
            }
            JetpackFuelCounter++;
        }*/