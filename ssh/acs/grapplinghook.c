#include "zcommon.acs"

#library "GRAPPLINGHOOK"

#include "grappleConstants.h" // I must include it forever from now on
#include "commonFuncs.h"

int grappled[32];

/* -- script GETFIRERPLN  --
 *   Gets the player number of the firer of the projectile this script was
 * called from. Obviously, this won't work if not called from a projectile.
 */

script GETFIRERPLN (void)
{
    int switchWorked = SetActivatorToTarget(0);

    if (switchWorked)
    {
        SetResultValue( PlayerNumber() );
    }
    else
    {
        SetResultValue(-1);
    }
}




/* -- script GRAPPLE_HOOK (int strength, int firetype) --
 *   This script is called the moment the grapple shot is fired. First, it sets
 * its TID to one not taken, and sets its focus to the firer of the shot. Then,
 * it checks if the projectile still exists, and if so, gets the X, Y, and Z
 * coordinates of the projectile. However, if the player let go of the +attack
 * key (or isn't allowed to attack, hence the MODINPUT), the projectile just...
 * kinda teleports away. Who knows.
 * If the projectile successfully connects with a surface (any surface), it
 * calls GRAPPLE_REEL, and the real fun (ow puns) starts.
 */

script GRAPPLE_HOOK (int strength, int firetype)
{
    int playerInput;
    int myX; int myY; int myZ;

    int firerPln = ACS_ExecuteWithResult(GETFIRERPLN, 0,0,0);
    int projTid = PROJOFFSET+firerPln;

    while (ThingCount(0, projTid) > 0)
    {
        projTid++;
    }

    Thing_ChangeTID(0, projTid);

    SetActivatorToTarget(0);

    while (ThingCount(0, projTid) > 0)
    {
        myX = GetActorX(projTid);
        myY = GetActorY(projTid);
        myZ = GetActorZ(projTid);
        playerInput = GetPlayerInput(-1, MODINPUT_BUTTONS);

        switch (firetype)
        {
        case 0:
            if (!(GetPlayerInput(-1, MODINPUT_BUTTONS) & BT_ALTATTACK))
            {
                Thing_Remove(projTid);
                Spawn("GuaranteedTeleportFog", myX, myY, myZ-20.0);
                terminate;
            }
            break;

        case 1:
            if (!(GetPlayerInput(-1, MODINPUT_BUTTONS) & BT_ATTACK))
            {
                Thing_Remove(projTid);
                Spawn("GuaranteedTeleportFog", myX, myY, myZ-20.0);
                terminate;
            }
            break;

        case 2:
            if (CheckInventory("InventoryToggle"))
            {
                Thing_Remove(projTid);
                Spawn("GuaranteedTeleportFog", myX, myY, myZ-20.0);
                terminate;
            }
            break;
        }

        Delay(1);
    }

    Spawn("GrappleSpot", myX, myY, myZ, projTid);

    ACS_ExecuteAlways(GRAPPLE_REEL, 0, projTid, strength, firetype);
}

script GRAPPLE_REEL (int grappleTid, int strength, int firetype)
{
    int nX;   int nY;   int nZ;
    int plX;  int plY;  int plZ;
    int vX;   int vY;   int vZ;
    int velX; int velY; int velZ;

    int breakLoop = false;

    int magnitude;

    int pln = PlayerNumber();
    int playerTid = ActivatorTID();

    if (playerTid == 0) // can we give him a TID without breaking anything?
    {
        playerTid = unusedTID(TIDSTART, -1);
        Thing_ChangeTID(0, playerTid);
    }

    // if not, then okay, just use the one he has already

    int grX = GetActorX(grappleTid);
    int grY = GetActorY(grappleTid);
    int grZ = GetActorZ(grappleTid);

    while (!breakLoop)
    {
        if (ThingCount(0, grappleTID) != 1)
        {
            break;
        }
        
        plX  = GetActorX(0);    plY  = GetActorY(0);    plZ  = GetActorZ(0);
        vX   = grX - plX;       vY   = grY - plY;       vZ   = grZ - plZ;

        // NOTE: I had to drop precision here in exchange for not overflowing
        magnitude = magnitudeThree(vX >> 16, vY >> 16, vZ >> 16);

        if (magnitude != 0)
        {
            nX = vX / magnitude; nY = vY / magnitude; nZ = vZ / magnitude;
            ACS_ExecuteAlways(GRAPPLE_DRAWLINE, 0, grappleTid, playerTid, 16);
        }
        else
        {
            nX = 0; nY = 0; nZ = 0;
        }

        SetActorVelocity(0, nX*strength, nY*strength, nZ*strength, true, true);

        if (CheckInventory("Grappling") == 0)
            { breakLoop = true; }

        Delay(1);
    }

    Thing_Remove(grappleTid);
}

script GRAPPLE_DRAWLINE (int grappleTid, int playerTid, int density)
{
    int plX; int plY;  int plZ;
    int grX; int grY;  int grZ;
    int vX;  int vY;   int vZ;
    int nX;  int nY;   int nZ;
    int bX;  int bY;   int bZ;
    int magnitude;
    int pointCount;
    int pointOffset;

    if (ThingCount(0, grappleTid) != 1)
    {
        terminate;
    }

    if (ThingCount(0, playerTid) != 1)
    {
        terminate;
    }

    plX = GetActorX(playerTid); grX = GetActorX(grappleTid);
    plY = GetActorY(playerTid); grY  = GetActorY(grappleTid);
    plZ = GetActorZ(playerTid) + 2400000; grZ  = GetActorZ(grappleTid);
    vX   = grX - plX;       vY   = grY - plY;       vZ   = grZ - plZ;

    // NOTE: More precision bullshit
    magnitude = magnitudeThree(vX >> 16, vY >> 16, vZ >> 16);

    pointCount  = magnitude / density;
    pointOffset = magnitude - (pointCount * density);

    if (magnitude != 0)
    {
        nX = vX / magnitude; nY = vY / magnitude; nZ = vZ / magnitude;

        int i; int j;
        for (i = 0; i < pointCount; i++)
        {
            j = (i * density) + pointOffset;

            bX = (nX * j) + plX;
            bY = (nY * j) + plY;
            bZ = (nZ * j) + plZ;

            Spawn("GrapplePoint", bX, bY, bZ);
        }
    }

}

script GRAPPLE_GETUNUSEDTID (int mode, int fromItem)
{
    int newTID = TIDSTART;

    switch (mode)
    {
    case 0:
        while (ThingCount(0, newTID) > 0)
        {
            newTID++;
        }

        if (fromItem)
        {
            GiveInventory("ItemGrappleTID", newTID);
        }
        else
        {
            GiveInventory("GrappleTIDIndicator", newTID);
        }

        Thing_ChangeTID(0, newTID);
        break;

    case 1:
        if (fromItem)
        {
            SetResultValue(CheckInventory("ItemGrappleTID"));
        }
        else
        {
            SetResultValue(CheckInventory("GrappleTIDIndicator"));
        }
        break;

    case 2:
        while (ThingCount(0, newTID) > 0)
        {
            newTID++;
        }


        if (fromItem)
        {
            GiveInventory("ItemGrappleTID", newTID);
        }
        else
        {
            GiveInventory("GrappleTIDIndicator", newTID);
        }

        Thing_ChangeTID(0, newTID);
        SetResultValue(newTID);
        break;
    }
}