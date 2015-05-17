// This shit is wizardry. I had no hand in it. All credit goes to ijon tichy.

#define SINO_SPACEJUMP_ENTER2             351
#define SINO_SPACEJUMP_ENTER              352

#define SINO_WALLBOUNCE                   353
#define SINO_REQUESTDODGE                 354

#define DASH_VEL    40

#define WB_XYBASE   35.0
#define WB_ZBASE    1.25

#define WB_DODGE    0
#define WB_KICK     1
#define WB_KICKUP   2

#define WD_FORWARD  1
#define WD_FORWRITE 2
#define WD_RIGHT    3
#define WD_BACKRITE 4
#define WD_BACK     5
#define WD_BACKLEFT 6
#define WD_LEFT     7
#define WD_FORWLEFT 8
#define WD_KICK     9

int AngleOffsets[10] = { 0.5, 0.5, 0.375, 0.25, 0.125, 0, 0.875, 0.75, 0.625, 0 };

#define LUNGE_FORWARD 20.0
#define LUNGE_ZMULT   0.8

#define MJUMP_DELAY     8


int playerJumps[PLAYERMAX] = {0};
int hasKicked[PLAYERMAX]   = {0};
int grabbing[PLAYERMAX]    = {0};
int dontGrab[PLAYERMAX]    = {0};
int oldLedgeVals[PLAYERMAX][2] = {{0}};

int CPlayerGrounds[PLAYERMAX][2];
int PlayerGrounds[PLAYERMAX][2];
int DidSpecials[PLAYERMAX];

function int parkmoreOnGround(int tid)
{
    int ctid = unusedTID(13000, 18000);
    int spawned = Spawn("ParkmoreFloorChecker", GetActorX(tid), GetActorY(tid), GetActorZ(tid)-4.0, ctid);
    if (spawned) { Thing_Remove(ctid); }

    return (onGround(tid) ||
        (GetActorVelZ(tid) == 0 && !spawned));
}

/* A note on 3D floors:
 *
 * The closest 3D floor above you in the sector you're in is considered the ceiling of the sector.
 * The closest 3D floor below you in the sector you're in is considered the floor of the sector.
 * Knowing this, we can determine three relationships:
 *
 * When changing Z height, but keeping X and Y constant:
 *  - If both ceiling and floor height change, we have skipped over a 3D floor entirely.
 *
 * When raising Z height ONLY:
 *  - If only the ceiling height changes, we have entered a 3D floor.
 *  - If only the floor height changes, we have left a 3D floor.
 *
 * When lowering Z height ONLY:
 *  - If only the ceiling height changes, we have left a 3D floor.
 *  - If only the floor height changes, we have entered a 3D floor.
 *
 * There is no way to differentiate between solid and non-solid 3D floors:
 *  at least, no way that I know of.
 */

function int parkmoreIn3DFloor(int tid)
{
    if (tid != 0 && ThingCount(0, tid) == 0) { return 0; }

    int x = GetActorX(tid);
    int y = GetActorY(tid);
    int f = GetActorFloorZ(tid);
    int c = GetActorCeilingZ(tid);
    int i = random(5, 22);
    int newtid = unusedTID(1000 * i, 1000 * (10+i));

    Spawn("ParkmoreChecker3", x, y, f, newtid);

    int ret = GetActorCeilingZ(newtid) < c;
    Thing_Remove(newtid);
    return ret;
}

function int hasHighJump(void)
{
    return CheckInventory("RuneHighJump") || CheckInventory("PowerHighJump");
}

function int getJumpZ(void)
{
    int ret = GetActorProperty(0, APROP_JumpZ);

    ret *= (hasHighJump() + 1);
    
    return ret;
}

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
        case WB_KICK:   xyMult =  0.45;  zMult = 0.75; break; // case WB_KICK:   xyMult =  0.8;  zMult = 1.0; break;
        case WB_KICKUP: xyMult =  0.02; zMult = 0.95; break; // case WB_KICKUP: xyMult =  0.02; zMult = 1.3; break;
        default: return;
    }

    xyMult = FixedMul(xyMult, GetActorProperty(0, APROP_Speed));
    zMult  = FixedMul(zMult,  GetActorProperty(0, APROP_JumpZ));

    if (hasHighJump())
    {
        xyMult = FixedMul(xyMult, 1.4142);
        zMult  = FixedMul(zMult, 1.4142);
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

    up      = FixedMul(WB_ZBASE, zMult);

    forwardx = FixedMul(cos(angle), forward);
    forwardy = FixedMul(sin(angle), forward);
    sidex = FixedMul(cos(angle-0.25), side);
    sidey = FixedMul(sin(angle-0.25), side);
    
    velx = FixedMul(forwardx + sidex, xyMult);
    vely = FixedMul(forwardy + sidey, xyMult);
    velz = up;

    switch (type)
    {
        case WB_KICK:   SetActorVelocity(0, velx, vely, velz, 0, 1); break;
        case WB_KICKUP: SetActorVelocity(0, velx + GetActorVelX(0), GetActorVelY(0), velz, 0, 1); break;
    }

    playerJumps[pln] = min(playerJumps[pln]+1, 1);

    if (type == WB_KICK)
    {
        switch (direction)
        {
            case WD_FORWRITE: ACS_ExecuteAlways(SINO_TURN, 0, 45,  2, CLOCKWISE); break;
            case WD_RIGHT:    ACS_ExecuteAlways(SINO_TURN, 0, 90,  2, CLOCKWISE); break;
            case WD_BACKRITE: ACS_ExecuteAlways(SINO_TURN, 0, 135, 2, CLOCKWISE); break;
            case WD_BACK:     ACS_ExecuteAlways(SINO_TURN, 0, 180, 2, CLOCKWISE); break;
            case WD_BACKLEFT: ACS_ExecuteAlways(SINO_TURN, 0, 135, 2, COUNTERCLOCKWISE); break;
            case WD_LEFT:     ACS_ExecuteAlways(SINO_TURN, 0, 90,  2, COUNTERCLOCKWISE); break;
            case WD_FORWLEFT: ACS_ExecuteAlways(SINO_TURN, 0, 45,  2, COUNTERCLOCKWISE); break;
        }
    }

    if (type == WB_KICKUP) { hasKicked[pln] = 1; }
    else { hasKicked[pln] = 0; }

    grabbing[pln] = 0;
    dontGrab[pln] = 0;

    switch (type)
    {
        case WB_KICK: ActivatorSound("shihong/walljump", 127); break;
        case WB_KICKUP: ActivatorSound("shihong/walljumpup", 127); break;
    }
}

function void Lunge(int force)
{
    int pln = PlayerNumber();
    int jumpHeight = FixedMul(getJumpZ(), LUNGE_ZMULT);
    int velx, vely, velz;
    int angle = GetActorAngle(0);

    if ((force != 1) && (playerJumps[pln] != 0)) { return; }

    playerJumps[pln] += 1; 

    velX = FixedMul(cos(angle), LUNGE_FORWARD);
    velY = FixedMul(sin(angle), LUNGE_FORWARD);
    velZ = jumpHeight;

    SetActorVelocity(0, velX, velY, velZ, 0, 1);
}

// ===================

/*  :TURNING
 * Turning scripts
 */

function int getTimer(int pln, int which)
{
    return playerTimers[pln][which];
}

function void addTimer(int pln, int which, int add)
{
    if (add) { playerTimers[pln][which] = add; }
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

function void printTimers(int pln)
{
    int i, j, printstr;
    for (i = 0; i < TIMER_COUNT; i++)
    {
        j = playerTimers[pln][i];
        printStr = StrParam(s:printStr, d:i, s:":", d:!!j, s:"  ");
    }

    Print(s:printStr);
}

/*  :MOVEMENT
 * Wall-jumping, dodging scripts
 */

script SINO_WALLBOUNCE (int type, int direction, int mask)
{
    int newDir = -1;
    int justCheck;
    int angle, x,y,z, x2,y2, i, j;
    int tid, canBounce;
    int sideMove, forwMove;
    int x3,y3;

    if (isDead(0)) { terminate; }
    if (CheckInventory("IsJungHaeLin") == 1)
    { terminate; }

    if (direction < 0) { direction = -direction; justCheck = 1; }

    if (parkmoreOnGround(0))
    {
        if (type == WB_DODGE) { wallBounce(type, direction); }
        terminate;
    }

    if (mask == 0) { mask = 1; }

    angle = GetActorAngle(0) + AngleOffsets[direction];
    angle = mod(angle, 1.0);

    x  = 20 * cos(angle); y  = 20 * sin(angle);
    x2 = 8  * cos(angle); y2 = 8  * sin(angle);

    if (abs(x) > abs(y))
    {
        y = FixedMul(y, FixedDiv(20.0, abs(x)));
        x = 20.0 * sign(x);
    }
    else
    {
        x = FixedMul(x, FixedDiv(20.0, abs(y)));
        y = 20.0 * sign(y);
    }

    canBounce = 0;
    tid = unusedTID(25000, 30000);

    for (i = 0; i < 10; i++)
    {
        x3 = GetActorX(0) + x + (x2*i);
        y3 = GetActorY(0) + y + (y2*i);
        z  = GetActorZ(0) + 16.0;

        j = Spawn("ParkmoreChecker2", x3, y3, z, tid);
        if (!j) { canBounce = 1; }
        if (parkmoreIn3DFloor(tid)) { canBounce = 1; }

        Thing_Remove(tid);

        //PrintBold(s:"(", f:x3, s:", ", f:y3, s:") type ", d:type, s:" - ", d:j);
        
        if (canBounce) { break; }
    }
    
    if (canBounce && !justCheck)
    {
        wallBounce(type, direction);
    }

    //Print(s:"wallbounce (func): ", d:canBounce, s:" - angle is ", f:angle, s:", direction is ", d:direction, s:" (", f:x, s:", ", f:y, s:")");
    SetResultValue(canBounce);
}

script SINO_SPACEJUMP_ENTER enter
{
    int pln = PlayerNumber();
    int ground, wasGround, didSpecial;
    int inWater, wasInWater;
    int i;
    int direction, dDirection;

    while (PlayerInGame(pln))
    {
        if (isDead(0))
        {
            playerJumps[pln] = 0;
            hasKicked[pln] = 0;
            grabbing[pln] = 0;
            dontGrab[pln] = 0;
            TakeInventory("HasKicked", 1);
            Delay(1);
            continue;
        }

        if (CheckInventory("IsJungHaeLin") == 1)
        { terminate; }

        if (hasKicked[pln] && !CheckInventory("HasKicked")) { GiveInventory("HasKicked", 1); }
        if (!hasKicked[pln] && CheckInventory("HasKicked")) { TakeInventory("HasKicked", 0x7FFFFFFF); }

        wasGround = ground;
        ground = parkmoreOnGround(0);

        PlayerGrounds[pln][0] = ground;
        PlayerGrounds[pln][1] = wasGround;

        wasInWater = inWater;
        inWater = CheckInventory("WaterIndicator");

        direction = getDirection();

        //if (CheckInventory("NoParkour") && !CheckInventory("ForceParkourOff"))
        if (!CheckInventory("CanSpaceJump"))
        {
            if (ground)
            {
                playerJumps[pln] = 0;
                hasKicked[pln] = 0;
                grabbing[pln] = 0;
                dontGrab[pln] = 0;
            }
            else
            {
                playerJumps[pln] = max(1, playerJumps[pln]);
            }
            Delay(1);
            continue;
        }

        didSpecial = 0;

        if (ground || inWater)
        {
            playerJumps[pln] = 0;
            hasKicked[pln] = 0;
            grabbing[pln] = 0;
            dontGrab[pln] = 0;
        }
        else
        {
            playerJumps[pln] = max(1, playerJumps[pln]);
        }

        tickTimer(pln, TIMER_BOUNCED);
        DidSpecials[pln] = max(0, DidSpecials[pln]-1);

        Delay(1);
    }
}

script SINO_SPACEJUMP_ENTER2 enter clientside
{
    int pln = PlayerNumber();
    int dodgeDir, pukeStr;
    int ground, wasGround, direction, dDirection;
    int inWater, wasInWater;
    int myLock = ClientEnterLocks[pln] + 1;
    int i, j, k;

    if (ConsolePlayerNumber() != pln && !IsServer) { terminate; }
    if (CheckInventory("IsJungHaeLin") == 1)
    { terminate; }

    ClientEnterLocks[pln] = myLock;

    while (ClientEnterLocks[pln] == myLock)
    {

        dodgeDir = -1;
        dDirection = -1;

        ground = parkmoreOnGround(0);
        direction = getDirection();

        if (ground) { wasGround = MJUMP_DELAY; }
        else { wasGround = max(0, wasGround-1); }

        wasInWater = inWater;
        inWater = CheckInventory("WaterIndicator");

        CPlayerGrounds[pln][0] = ground;
        CPlayerGrounds[pln][1] = wasGround;

        if (!(GetActorVelX(0) || GetActorVelY(0)))
        {
            playerTimers[pln][TIMER_CLEFT]      = 0;
            playerTimers[pln][TIMER_CFORWARD]   = 0;
            playerTimers[pln][TIMER_CRIGHT]     = 0;
            playerTimers[pln][TIMER_CBACK]      = 0;
        }

        if (!(getTimer(pln, TIMER_BOUNCED) || wasGround) && keyPressed(BT_JUMP) && direction != 0 && !CheckInventory("GrabbingTheWall"))
        {
            switch (direction)
            {
              case DIR_NW: dDirection = WD_FORWLEFT;    break;
              case DIR_N:  dDirection = WD_FORWARD;     break;
              case DIR_NE: dDirection = WD_FORWRITE;    break;
              case DIR_SW: dDirection = WD_BACKLEFT;    break;
              case DIR_S:  dDirection = WD_BACK;        break;
              case DIR_SE: dDirection = WD_BACKRITE;    break;
              case DIR_W:  dDirection = WD_LEFT;        break;
              case DIR_E:  dDirection = WD_RIGHT;       break;
            }

            i = 0;
            switch (dDirection)
            {
              case -1: break;

              case WD_FORWARD:
                if (!CheckInventory("HasKicked")
                    && ACS_ExecuteWithResult(SINO_WALLBOUNCE, WB_KICKUP, -WD_KICK)) 
                {
                    i = 2; break;
                }
            
              default:
                if (ACS_ExecuteWithResult(SINO_WALLBOUNCE, WB_KICK, -dDirection)) { i = 1; }
                break;
            }

            if (i == 2)
            {
                if (!IsServer)
                {
                    pukeStr = StrParam(s:"puke -", d:SINO_REQUESTDODGE, s:" ", d:-256);
                    ConsoleCommand(pukeStr);
                }
                else
                {
                    ACS_ExecuteWithResult(SINO_WALLBOUNCE, WB_KICKUP, WD_KICK);
                }
            }
            else if (i == 1)
            {
                if (!IsServer)
                {
                    pukeStr = StrParam(s:"puke -", d:SINO_REQUESTDODGE, s:" ", d:-dDirection);
                    ConsoleCommand(pukeStr);
                }
                else
                {
                    ACS_ExecuteWithResult(SINO_WALLBOUNCE, WB_KICK, dDirection);
                }
            }
            else { dDirection = -1; }

            
            if (i) { addTimer(pln, TIMER_BOUNCED, 2); }
            //Print(s:"walljump: ", d:i, s:" (", d:dDirection, s:")");
        }

        if (keyPressed(BT_JUMP) && !CheckInventory("GrabbingTheWall"))
        {
            if (!(ground || (GetActorVelZ(0) < 0 && wasGround) || wasGround >= (MJUMP_DELAY-2) || inWater || dDirection != -1))
            {
                if (!IsServer)
                {
                    pukeStr = StrParam(s:"puke -", d:SINO_REQUESTDODGE, s:" 0 0 1");
                    ConsoleCommand(pukeStr);
                }
                else if (!DidSpecials[pln] && !grabbing[pln])
                {
                    //MultiJump(1, 0);
                }
            }
        }

        tickTimer(pln, TIMER_CFORWARD);
        tickTimer(pln, TIMER_CRIGHT);
        tickTimer(pln, TIMER_CBACK);
        tickTimer(pln, TIMER_CLEFT);
        tickTimer(pln, TIMER_HBACK);

        tickTimer(pln, TIMER_DIDDODGE);
        tickTimer(pln, TIMER_BOUNCED);

        Delay(1);
    }

}

script SINO_REQUESTDODGE (int direction, int hijump, int mjump) net
{
    int pln = PlayerNumber();

    if (isDead(0)) { terminate; }

    if (mjump && !DidSpecials[pln] && !grabbing[pln])
    {
        //Print(d:playerJumps[pln]);
        //MultiJump(1, 0);
    }
    else if (direction < 0)
    {
        direction = -direction;
        if (direction == 256) { ACS_ExecuteWithResult(SINO_WALLBOUNCE, WB_KICKUP, WD_KICK); }
        else { ACS_ExecuteWithResult(SINO_WALLBOUNCE, WB_KICK, direction); }
    }
    else
    {
        ACS_ExecuteWithResult(SINO_WALLBOUNCE, WB_DODGE, direction, 0);
    }
}
