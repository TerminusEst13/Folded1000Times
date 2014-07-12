#include "zcommon.acs"
#library "parkmore"

#include "commonFuncs.h"
#include "parkConst.h"

world int 0:MaxJumpCount;

int playerJumps[PLAYERMAX] = {0};
int hasKicked[PLAYERMAX]   = {0};
int grabbing[PLAYERMAX]    = {0};
int dontGrab[PLAYERMAX]    = {0};

int playerTimers[PLAYERMAX][TIMER_COUNT];
int ClientEnterLocks[PLAYERMAX];
int IsServer;
int dodgeitem;

//function int getJumpZ(void)
//{
//    int ret = GetActorProperty(0, APROP_JumpZ);
//    
//    return ret;
//}

function void wallBounce (int type, int direction) 
{
    int forwardMult, sideMult, xyMult, zMult;
    int forward, side, up;
    int forwardx, forwardy, sidex, sidey;
    int velx, vely, velz;

    int pln = PlayerNumber();
    int angle = GetActorAngle(0);

    if (type == WB_KICKUP && hasKicked[pln]) { return; }

    switch (type)
    {
        case WB_DODGE:  xyMult =  1.0;  zMult = 0.707; break;
        case WB_KICK:   xyMult =  0.8;  zMult = 1.0; break;
        case WB_KICKUP: xyMult =  0.02; zMult = 1.3; break;
        default: return;
    }

    switch (direction)
    {
        case WD_FORWARD:  forwardMult =  1.0;   sideMult =  0.0;    break;
        case WD_FORWRITE: forwardMult =  0.707; sideMult =  0.707;  break;
        case WD_RIGHT:    forwardMult =  0.0;   sideMult =  1.0;    break;
        case WD_BACKRITE: forwardMult = -0.707; sideMult =  0.707;  break;
        case WD_BACK:     forwardMult = -1.0;   sideMult =  0.0;    break;
        case WD_BACKLEFT: forwardMult = -0.707; sideMult = -0.707;  break;
        case WD_LEFT:     forwardMult =  0.0;   sideMult = -1.0;    break;
        case WD_FORWLEFT: forwardMult =  0.707; sideMult = -0.707;  break;
        case WD_KICK:     forwardMult = -1.0;   sideMult =  0.0;    break;
        default: return;
    }
    
    forward = FixedMul(WB_XYBASE, forwardMult); 
    side    = FixedMul(WB_XYBASE, sideMult); 

    up      = FixedMul(GetActorProperty(0, APROP_JumpZ), WB_ZBASE);
    up      = FixedMul(up, zMult);

    forwardx = FixedMul(cos(angle), forward);
    forwardy = FixedMul(sin(angle), forward);
    sidex = FixedMul(cos(angle-0.25), side);
    sidey = FixedMul(sin(angle-0.25), side);
    
    velx = FixedMul(forwardx + sidex, xyMult);
    vely = FixedMul(forwardy + sidey, xyMult);
    velz = up;

    switch (type)
    {
        case WB_DODGE:
		
		//SetActorVelocity(0, velx + (GetActorVelX(0)*2), vely + (GetActorVelY(0)*2), velz, 0, 1);
        SetActorVelocity(0, velx + (GetActorVelX(0)/4), vely + (GetActorVelY(0)/4), velz/1.25, 0, 1);
			 
    }

    //playerJumps[pln] = min(playerJumps[pln]+1, 1);

    grabbing[pln] = 0;
    dontGrab[pln] = 0;
}


script PARKMORE_WALLBOUNCE (int type, int direction, int mask)
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
		//ActivatorSound("ghost/step",127);
	    GiveInventory("GhostStepCooldown",25);
        GiveInventory(dodgeitem,1);
		//wallBounce(type, direction);
        //if ( (GetActorZ(0) - GetActorFloorZ(0)) > 0) { ThrustThingZ(0,12,0,0); }
    }
    terminate;

    if (mask == 0) { mask = 1; }
	}
}

/*function void MultiJump(int countJump, int force)
{
    int pln = PlayerNumber();
    int jumpHeight = getJumpZ();

    if ((force != 1) && (MaxJumpCount >= 0) && (playerJumps[pln] + countJump > MaxJumpCount)) { return; }
    if (playerJumps[pln] == 0) { return; }

    playerJumps[pln] += countJump; 

    SetActorVelocity(0, GetActorVelX(0), GetActorVelY(0), jumpHeight, 0, 1);
}*/

function void Lunge(int force)
{
    int pln = PlayerNumber();
    //int jumpHeight = FixedMul(getJumpZ(), LUNGE_ZMULT);
    int velx, vely, velz;
    int angle = GetActorAngle(0);

    if ((force != 1) && (playerJumps[pln] != 0)) { return; }

    playerJumps[pln] += 1; 

    velX = FixedMul(cos(angle), LUNGE_FORWARD);
    velY = FixedMul(sin(angle), LUNGE_FORWARD);
    //velZ = jumpHeight;

    SetActorVelocity(0, velX, velY, velZ, 0, 1);
}

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
    int i = max(0, defaultCVar("parkmore_dodgewindow",  8));

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

script PARKMORE_ENTER2 enter clientside
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

                ACS_ExecuteAlways(PARKMORE_WALLBOUNCE, 0, WB_DODGE, dodgeDir, 0);
                
                /*if (!IsServer)
                {
                    pukeStr = StrParam(s:"puke -", d:PARKMORE_REQUESTDODGE, s:" ", d:dodgeDir);
                    ConsoleCommand(pukeStr);
                }*/
            }
        }

        tickTimer(pln, TIMER_CFORWARD);
        tickTimer(pln, TIMER_CRIGHT);
        tickTimer(pln, TIMER_CBACK);
        tickTimer(pln, TIMER_CLEFT);
        tickTimer(pln, TIMER_HBACK);
        addCTimers(pln);

        tickTimer(pln, TIMER_DIDDODGE);

        Delay(1);
    }

}

script PARKMORE_REQUESTDODGE (int direction, int hijump) net
{
    int pln;
	
        ACS_ExecuteAlways(PARKMORE_WALLBOUNCE, 0, WB_DODGE, direction, 0);
		
}