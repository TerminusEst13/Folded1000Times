function int getTimer(int pln, int which)
{
    return playerTimers[pln][which];
}

function void addTimer(int pln, int which, int add)
{
    if (add) { playerTimers[pln][which] = add; }
}

function void addCTimers(int pln)
{
    int i = max(0, defaultCVar("ds_doubletapwindow",  8));

    addTimer(pln, TIMER_CFORWARD,  keyPressed(BT_FORWARD)   * i);
    addTimer(pln, TIMER_CRIGHT,    keyPressed(BT_MOVERIGHT) * i);
    addTimer(pln, TIMER_CBACK,     keyPressed(BT_BACK)      * i);
    addTimer(pln, TIMER_CLEFT,     keyPressed(BT_MOVELEFT)  * i);
}

function void addCTimersZD(int pln) // Hack, hack, hack.
{
    int i = max(0, GetCVar("ds_doubletapwindow"));

    addTimer(pln, TIMER_CFORWARD,  keyPressed(BT_FORWARD)   * i);
    addTimer(pln, TIMER_CRIGHT,    keyPressed(BT_MOVERIGHT) * i);
    addTimer(pln, TIMER_CBACK,     keyPressed(BT_BACK)      * i);
    addTimer(pln, TIMER_CLEFT,     keyPressed(BT_MOVELEFT)  * i);
}

function int tickTimer(int pln, int timerNum)
{
    int i = max(playerTimers[pln][timerNum]-1, 0);
    playerTimers[pln][timerNum] = i;
    return i;
}

function void tickTimers(int pln)
{
    int i;
    for (i = 0; i < TIMER_COUNT; i++)
    {
        tickTimer(pln, i);
    }
}

script WEEB_TAPSPECIFY (int type, int direction, int mask)
{
    int newDir = -1;

    if (CheckInventory("GhostStepCooldown") == 0)
	{
    if (type == WB_DODGE)
    {
        int sideMove = keyDown(BT_MOVERIGHT) - keyDown(BT_MOVELEFT);
        int forwMove = keyDown(BT_FORWARD) - keyDown(BT_BACK);

        switch (direction)
        {
          case WD_FORWARD: 
            switch (sideMove)
            {
                case -1: newDir = WD_FORWLEFT; break;
                case  0: break;
                case  1: newDir = WD_FORWRITE; break;
            }
            break;
            
          case WD_BACK: 
            switch (sideMove)
            {
                case -1: newDir = WD_BACKLEFT; break;
                case  0: break;
                case  1: newDir = WD_BACKRITE; break;
            }
            break;
            
          case WD_LEFT: 
            switch (forwMove)
            {
                case -1: newDir = WD_BACKLEFT; break;
                case  0: break;
                case  1: newDir = WD_FORWLEFT; break;
            }
            break;
            
          case WD_RIGHT: 
            switch (forwMove)
            {
                case -1: newDir = WD_BACKRITE; break;
                case  0: break;
                case  1: newDir = WD_FORWRITE; break;
            }
            break;
        }

        if (newDir != -1) { direction = newDir; }
    }

    if (type == WB_DODGE)
    {
        if (CheckInventory("SuperMeterCounter") >= 10) {
	    GiveInventory("GhostStepCooldown",25);
        GiveInventory(dodgeitem,1); }
    }
    terminate;

    if (mask == 0) { mask = 1; }
	}
}

script WEEB_ENTERDOUBLETAP enter clientside
{
    int pln = PlayerNumber();
    int dodgeDir, pukeStr;
    int myLock = ClientEnterLocks[pln] + 1;

    ClientEnterLocks[pln] = myLock;

    while (ClientEnterLocks[pln] == myLock)
    {
        dodgeDir = -1;

        if (!getTimer(pln, TIMER_DIDDODGE))
        {
            if (keyPressed(BT_MOVELEFT) && getTimer(pln, TIMER_CLEFT))
            {
                dodgeDir = WD_LEFT;
                dodgeitem = "DoubleTapLeft";
            }
            else if (keyPressed(BT_FORWARD) && getTimer(pln, TIMER_CFORWARD))
            {
                dodgeDir = WD_FORWARD;
                dodgeitem = "DoubleTapForward";
            }
            else if (keyPressed(BT_MOVERIGHT) && getTimer(pln, TIMER_CRIGHT))
            {
                dodgeDir = WD_RIGHT;
                dodgeitem = "DoubleTapRight";
            }
            else if (keyPressed(BT_BACK) && getTimer(pln, TIMER_CBACK))
            {
                dodgeDir = WD_BACK;
                dodgeitem = "DoubleTapBack";
            }

            if (dodgeDir != -1)
            {
                addTimer(pln, TIMER_DIDDODGE, 2);
                ACS_ExecuteAlways(WEEB_TAPSPECIFY, 0, WB_DODGE, dodgeDir, 0);
            }
        }

        tickTimer(pln, TIMER_CFORWARD);
        tickTimer(pln, TIMER_CRIGHT);
        tickTimer(pln, TIMER_CBACK);
        tickTimer(pln, TIMER_CLEFT);
        tickTimer(pln, TIMER_HBACK);
        if (GetCvar("ds_runninginzdoom") == 0 ) { addCTimers(pln); } else { addCTimersZD(pln); }

        tickTimer(pln, TIMER_DIDDODGE);

        Delay(1);
    }

}