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
                if(GetPlayerInput(-1, INPUT_BUTTONS) & BT_CROUCH && CheckInventory("WallGrabbed") != 2)
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
                        SetActorProperty(0,APROP_Gravity,0.7);
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