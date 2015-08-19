script WEEB_ENTER ENTER
{
    int OldButtons;
    int Buttons;
    int SuperCount;
    int ComboCount;
    int KurtAngle;
    int WalkTheDinosaur;
    int RideTheLightning;
    int XMen;
    int Ys;
    int XMen2;
    int Ys2;
    int mytid;
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
    int GetSomeHealthAlready;
    int speedmod;
    int TimeStandStill;
    int RemoveFRankAnnouncer;
    int RemoveDRankAnnouncer;
    int RemoveCRankAnnouncer;
    int RemoveBRankAnnouncer;
    int RemoveARankAnnouncer;
    int RemoveSRankAnnouncer;
    int DodgeCounter;
    int HaloTID;
    int u, ang;

    if (GetCvar("dst_debug") == 1) { Log(s:"WEEB_ENTER executing on player ", d:pln); }

    // If the player isn't playing as Hae-Lin, terminates.
    // Inter-character scripts running off each other will cause a cluster of problems.
    if (CheckInventory("IsSSH") == 1)
    {
        if (GetCvar("dst_debug") == 1) { Log(s:"Error: Player ", d:pln, s:" is not Hae-Lin, terminating WEEB_ENTER."); }
        terminate;
    }

    if (CheckInventory("ImAlive") == 0 && GameType() != GAME_TITLE_MAP)
    // If the player is spawning for the first time.
    // Don't run it on titlescreens, or else Things Would Happen.
    {
        if (GameSkill () == 0 || (GameSkill() == 6 && GetCvar("dst_multiplierhealth") == 0)) { GiveInventory("BabyMarker",1); GiveInventory("ContraLifeToken",10); }
        if (GameSkill () == 1 || (GameSkill() == 6 && GetCvar("dst_multiplierhealth") == 1)) { GiveInventory("EasyMarker",1); GiveInventory("ContraLifeToken",8);  }
        if (GameSkill () == 2 || (GameSkill() == 6 && GetCvar("dst_multiplierhealth") == 2)) { GiveInventory("NormalMarker",1); GiveInventory("ContraLifeToken",6); }
        if (GameSkill () == 3 || (GameSkill() == 6 && GetCvar("dst_multiplierhealth") == 3)) { GiveInventory("HardMarker",1); GiveInventory("ContraLifeToken",4); }
        if (GameSkill () == 4 || (GameSkill() == 6 && GetCvar("dst_multiplierhealth") == 4)) { GiveInventory("NightmareMarker",1); GiveInventory("ContraLifeToken",2); }
        FadeRange(0,0,0,1.00,0,0,0,0,3.50);
        LocalAmbientSound("level/intro",127);

        // Check for if the metal jukebox is loaded as well.
        if (Spawn("DemonSteeleIsSuperCoolAndYouShouldProbablyPlayIt", GetActorX(0), GetActorY(0), GetActorZ(0), u))
        {
            Thing_Remove(u);
            MusicRandomizerIsIncluded = 1;
            GiveInventory("IAmAnAwesomePersonWhoLikesCoolMusic",1);
        }

        if (GetCvar("dst_omenstart") == 1)
        {
            GiveInventory("KharonOmen",1);
            GiveInventory("GotHammer",1);
        }

        if (GetCvar("dst_backpackstart") == 1)
        { GiveInventory("Backpack",1); }

        GiveInventory("ImAlive",1);
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

    // If the Sentinel was carried over from a previous level...
    if (CheckInventory("SentinelUp") == 1)
    {
    // This is to prevent the Sentinel's info on the HUD from reading max value when we change levels with the Sentinel up.
    // It's very work-around-y, but it's what I get for assuming stuff can transfer across levels.
        NewSentinelHP = CheckInventory("SentinelLifeCounter");
        TakeInventory("SentinelActive",1);
        GiveInventory("SentinelFromPreviousLevel",1);
    }
    // Same shit, different git.
    if (CheckInventory("BlindGuardianShieldUp") == 1)
    {
        NewShieldHP = CheckInventory("BlindGuardianLifeCounter");
        TakeInventory("BlindGuardianShieldActive",1);
        GiveInventory("BlindGuardianFromPreviousLevel",1);
    }

    // Status resets for the sake of weapons/items/etc that change between levels.
    // Like in case some wiseass exits while in post-hit invulnerability.
    SetActorProperty(0,APROP_INVULNERABLE,0);
    SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Normal);
    if (GameType() == GAME_NET_DEATHMATCH) { SetActorProperty(0,APROP_Species,"DMPlayer"); }
    else { SetActorProperty(0,APROP_Species,"Player"); }
    SetPlayerProperty(0,0,PROP_TOTALLYFROZEN);
    SetActorProperty(0,APROP_Gravity,0.85);
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
    
    if (GetCvar("dst_debug") == 1) { Log(s:"Entering WEEB_ENTER while(1) loop on player ", d:pln); }

    while (1)
    {
        if (CheckInventory("IsSSH") == 1)
        {
            if (GetCvar("dst_debug") == 1) { Log(s:"Error: Player ", d:pln, s:" is not Hae-Lin, terminating WEEB_ENTER."); }
            terminate;
        }
        mytid = defaultTID(-1);
        //if (CheckInventory("ImAlive") == 1) { if (ConsolePlayerNumber() != PlayerNumber()) { terminate; } }

        XMen2 = XMen;
        Ys2   = Ys;
        XMen  = GetActorX(0);
        Ys    = GetActorY(0);
        ZDum  = GetActorZ(mytid) + 24.0;
        Angel = GetActorAngle(mytid);
        velx  = GetActorVelX(mytid); // I can't think of any witty names for these.
        vely  = GetActorVelY(mytid);
        velz  = GetActorVelZ(mytid);

        // If the player's staying in one spot, bring up the idle animation counter.
        if ((XMen2 == XMen) && (Ys2 == Ys)) { GiveInventory("WaitingTooLong",1); }
        else { TakeInventory("WaitingTooLong",0x7FFFFFFF); }

        // Cvar nonsense.

        if (GetCvar("dst_infinitesouls") == 1) { GiveInventory("SuperMeterCounter",1); }
        if (GetCvar("compat_disabletaunts") == 1) { GiveInventory("NoTauntAllowed",1); }
           else { TakeInventory("NoTauntAllowed",1); }
           
        if (GetCvar("dst_gunsouls") == 0) { GiveInventory("IAmASkilledPersonWhoWantsOnlyMySwordToGiveSouls",1); }
           else { TakeInventory("IAmASkilledPersonWhoWantsOnlyMySwordToGiveSouls",1); }

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
        
        // The Blind Guardian, AKA the BUTTSHIELD
        // It is a shield for your butt, you see.
        ShieldTID = 12000 + pln;
        if (CheckInventory("BlindGuardianShieldUp") == 1)
        {
            // OH NAW MAN DAT BOOTY UNPROTECTED
            if (CheckInventory("BlindGuardianShieldActive") == 0)
            {
                // WEEOOOWEEOOOWEEEOOO
                // DON'T WORRY, MA'AM, WE'RE PROFESSIONALS
                Spawn("BlindGuardian",XMen,Ys,ZDum,ShieldTID,Angel);
                GiveInventory("BlindGuardianShieldActive",1);
                // If the Buttshield is carried over from a previous level, this summons a new one
                // and then uses the player's NewShieldHP int (established earlier) to make it have
                // the previous entity's HP. Because you can't quite carry monsters from level to
                // level like you can inventory items.
                if (CheckInventory("BlindGuardianFromPreviousLevel") == 1)
                {
                    SetActorProperty(ShieldTID,APROP_Health,NewShieldHP);
                    TakeInventory("BlindGuardianFromPreviousLevel",1);
                }
            }
            else
            {
                // WOOP WOOP PULL OVER DAT ASS TOO FAT
                // Move the buttshield in order to match the player's position.
                // Angle's factored in but pitch isn't, since it'd be bad for an
                // attack to slip through because the player's looking up/down.
                xOffset = 0;
                yOffset = 0;
                zOffset = 0;

                nx = XMen + FixedMul(xOffset, cos(Angel)) + FixedMul(yOffset, sin(Angel));
                ny = Ys + FixedMul(xOffset, sin(Angel)) - FixedMul(yOffset, cos(Angel));
                nz = ZDum + zOffset;

                if (pln != ConsolePlayerNumber())
                {
                    // HOLD ON BACK THAT BUTT SHIELD ON UP
                    nx -= velx; ny -= vely; nz -= velz;
                }
                else
                {
                    // NOT FAR ENOUGH, KEEP BACKIN IT UP
                    // (players have weird camera interpolation re. Z movement)
                    nx -= velx; ny -= vely; nz -= 2*velz;
                }

                SetActorAngle(ShieldTID, Angel);
                SetActorPosition(ShieldTID,nx - FixedMul(32.0,cos(Angel)),ny - FixedMul(32.0,sin(Angel)),nz,0);
                SetActorVelocity(ShieldTID,velx,vely,velz,0,0);

                ShieldHP = GetActorProperty(ShieldTID, APROP_HEALTH);
                TakeInventory("BlindGuardianLifeCounter",0x7FFFFFFF);
                GiveInventory("BlindGuardianLifeCounter",ShieldHP);

                if (CheckInventory("BlindGuardianShieldHeal") == 1)
                {
                    GiveActorInventory(ShieldTID,"BlindGuardianHealth",1000);
                    SetActorState(ShieldTID,"Spawn");
                    TakeInventory("BlindGuardianShieldHeal",1);
                }

                if (CheckActorInventory(ShieldTID,"BlindGuardianWaitForAnAnswer"))
                {
                    // BUTT SHIELD'S DOWN, WHAT THE HELL
                    Thing_Remove(ShieldTID);
                    // PREPARE YOUR ANUS FOR MOURNING
                    ShieldTID = 0;
                    // RIP BUTT SHIELD ;_;7
                    TakeInventory("BlindGuardianShieldUp",1);
                    // YOU DIED AS YOU LIVED
                    TakeInventory("BlindGuardianShieldActive",1);
                    // THE OPPOSITE SIDE OF A PENIS
                    TakeInventory("BlindGuardianLifeCounter",0x7FFFFFFF);
                }
            }
        }

        // The Sentinel, AKA the FACEGUN
        // It is a gun for your face, you see.
        SentTID = 13000 + pln;
        if (CheckInventory("SentinelUp") == 1)
        {
            // Eh, that's not as funny as buttshield.
            if (CheckInventory("SentinelActive") == 0)
            {
                Spawn("AllFearTheSentinel",XMen,Ys,ZDum,SentTID,Angel);
                GiveInventory("SentinelActive",1);
                if (CheckInventory("SentinelFromPreviousLevel") == 1)
                {
                    SetActorProperty(SentTID,APROP_Health,NewSentinelHP);
                    TakeInventory("SentinelFromPreviousLevel",1);
                }
            }
            else
            // Yeah, this code is all basically copy/pasted from the buttshield.
            {
                xOffset2 = 0;
                yOffset2 = 0;
                zOffset2 = 0;

                nx2 = XMen + FixedMul(xOffset2, cos(Angel)) + FixedMul(yOffset2, sin(Angel));
                ny2 = Ys + FixedMul(xOffset2, sin(Angel)) - FixedMul(yOffset2, cos(Angel));
                nz2 = ZDum + zOffset2;

                if (pln != ConsolePlayerNumber())
                {
                    nx2 -= velx; ny2 -= vely; nz2 -= velz;
                }
                else
                {
                    nx2 -= velx; ny2 -= vely; nz2 -= 2*velz;
                }

                // What can I say? I'm lazy.
                if (CheckActorInventory(SentTID,"SentinelIdle")) { SetActorAngle(SentTID, Angel); }
                SetActorPosition(SentTID,nx2,ny2,nz2+24.0,0);
                SetActorVelocity(SentTID,velx,vely,velz,0,0);

                SentinelHP = GetActorProperty(SentTID, APROP_HEALTH);
                TakeInventory("SentinelLifeCounter",0x7FFFFFFF);
                GiveInventory("SentinelLifeCounter",SentinelHP);

                // It's probably not exactly very efficient, but honestly I don't care.
                // As long as code works and doesn't crash, I think it's fine.
                if (CheckInventory("SentinelDissidentAggressor") == 1)
                {
                    GiveActorInventory(SentTID,"SentinelHealth",200);
                    TakeInventory("SentinelDissidentAggressor",1);
                }

                // I don't have a lot of programmer friends.
                if (CheckActorInventory(SentTID,"SentinelBeyondTheRealmsOfDeath"))
                {
                    Thing_Remove(SentTID);
                    SentTID = 0;
                    TakeInventory("SentinelUp",1);
                    TakeInventory("SentinelActive",1);
                    TakeInventory("SentinelLifeCounter",0x7FFFFFFF);
                }
            }
        }

        // And then one more for show.
        HaloTID = 14000 + pln;
        if (CheckInventory("InIronMaiden") == 1)
        {
            if (CheckInventory("MaidenHalo") == 0)
            {
                Spawn("IronMaidenHalo",XMen,Ys,ZDum,HaloTID,Angel);
                GiveInventory("MaidenHalo",1);
            }
            else
            {
                // HOORAY
                xOffset3 = 0;
                yOffset3 = 0;
                zOffset3 = 0;

                // FOR
                nx3 = XMen + FixedMul(xOffset3, cos(Angel)) + FixedMul(yOffset3, sin(Angel));
                ny3 = Ys + FixedMul(xOffset3, sin(Angel)) - FixedMul(yOffset3, cos(Angel));
                nz3 = ZDum + zOffset3;

                // COPYING
                if (pln != ConsolePlayerNumber())
                {
                    nx3 -= velx; ny3 -= vely; nz3 -= velz;
                }
                // AND
                else
                {
                    nx3 -= velx; ny3 -= vely; nz3 -= 2*velz;
                }

                // PASTING
                SetActorAngle(HaloTID, Angel);
                SetActorPosition(HaloTID,nx3,ny3,nz3+24.0,0);
                SetActorVelocity(HaloTID,velx,vely,velz,0,0);
            }
        }
        else
        {
            Thing_Remove(HaloTID);
            HaloTID = 0;
            TakeInventory("MaidenHalo",1);
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

        TakeInventory("GhostStepCooldown",1);
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

          if (buttons & BT_ALTATTACK && ( (CheckInventory("20SpecialCost") == 1 && CheckInventory("SuperMeterCounter") >= 20) || (CheckInventory("10SpecialCost") == 1 && CheckInventory("SuperMeterCounter") >= 10) || (CheckInventory("00SpecialCost") == 1) ))
            { GiveInventory("SynthAltFire",1); }
          else
            { TakeInventory("SynthAltFire",1); }

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

          // Kyle873 makes a super timefreeze thing! HAVE FUN TERM
          // [13] OR WOULD HAVE IF HE HADN'T PUT IT IN THE CLIENTSIDE SCRIPT LOOP
          // I MEAN, WOW KYLE
          // WOW
          // WOOOOOOOWWWWWW
          // WOOOOOOOOOOOOWWWWWWWWWW
          /*if (buttons == (BT_MOVELEFT + BT_FORWARD + BT_MOVERIGHT))
          {
            if (CheckInventory("SuperTimeFreezer") == 0 && CheckInventory("SuperMeterCounter") == 400)
            {
              GiveInventory("TimeFreezeModeOn",1);
              playerTimeFreeze[PlayerNumber()] = true;
            }
            else if (CheckInventory("SuperTimeFreezer") == 1)
            {
              TakeInventory("SuperTimeFreezer",1);
              TakeInventory("TimeFreezeModeOn",1);
              playerTimeFreeze[PlayerNumber()] = false;
            }
          }*/
        }

        /*if (TimeStandStill >= 5 && CheckInventory("SuperTimeFreezer") == 1)
        { TakeInventory("SuperMeterCounter",1);
          TimeStandStill = 0; }
        TimeStandStill++;
        if (CheckInventory("SuperTimeFreezer") == 1 && CheckInventory("SuperMeterCounter") == 0)
        {
              TakeInventory("SuperTimeFreezer",1);
              TakeInventory("TimeFreezeModeOn",1);
              playerTimeFreeze[PlayerNumber()] = false;
        }*/

          /*playerTimeFreeze[PlayerNumber()] = !playerTimeFreeze[PlayerNumber()];
          if (PlayerTimeFreeze[PlayerNumber()] && CheckInventory("SuperMeterCounter") > 0) // If the player doesn't have time freeze on and is at full bar...
          {
            GiveInventory("SuperTimeFreezer", 1);
              if ((Timer() % 5) == 0) // 1 spirit loss per 5 tics, adjust as needed
                TakeInventory("SuperMeterCounter", 1);
              if (CheckInventory("SuperMeterCounter") == 0) // Disable automatically if we run out of super
                playerTimeFreeze[PlayerNumber()] = false;
          }*/


    // This block of code was done by Kyle873.
    // He wishes me to inform you that ACS is a pile of cocks that owes him money.
    // If ACS ever met him IRL for a 1v1 fite, he would totally kick ACS' ass.
    // He has a blackbelt in punchyourshitology and got a masters in ohgodmyfuckingkneecapsjutsu.
    // Unfortunately ACS is a bitch pussy and never returns his calls.
    // But he is waiting. Oh, yes, he is waiting.
        WalkTheDinosaur = GetActorZ(0) - GetActorFloorZ(0);        
        //print(f:WalkTheDinosaur, s:" ", f:GetActorVelZ(0), s:"\n", d:CheckInventory("OnTheGround"), s:" ", d:CheckInventory("AcesHigh"));

        // Floor check
        if (GetActorZ(0) - GetActorFloorZ(0) == 0)
        {
              GiveInventory("OnTheGround", 1);
              TakeInventory("GhostStepDone",1); 
              TakeInventory("VertIGo",1); 
        }
        else
            { TakeInventory("OnTheGround", 1); }
        // Double Jump
        if (GetActorVelZ(0) <= 8 && !CheckInventory("OnTheGround") && !CheckInventory("AcesHigh") && keypressed(BT_JUMP) && GetCvar("sv_nojump") == 0)
        {
            ActivatorSound("ghost/jump", 127);
            if (CheckInventory("InIronMaiden") == 0 )
            {
                ThrustThingZ(0,36,0,0);
                GiveInventory("DoubleJumpWingTrigger",1);//Spawn("DoubleJumpWings",nx2,ny2,nz2+24,0,angel);
                GiveInventory("AcesHigh", 1);
            }
            else
            {
                ThrustThingZ(0,42,0,0);
                GiveInventory("DoubleJumpWingTrigger",1);//Spawn("DoubleJumpWings",nx2,ny2,nz2+24,0,angel);
                if (CheckInventory("VertIGo") == 1 ) { GiveInventory("AcesHigh",1); }
                else { GiveInventory("VertIGo",1); }
            }
        }
        // Remove AcesHigh when we're back on the ground
        if (CheckInventory("OnTheGround") && CheckInventory("AcesHigh"))
            TakeInventory("AcesHigh", 1);
    // This concludes the block of code done by Kyle873.
    // You may now applaud his genius.

        // GET OUTTA DODGE
        if (CheckInventory("GhostStepCooldown") == 0 && CheckInventory("GhostStepDone") == 0)
        {
          // Simple stuff. If the player hits Run and another button, they get thrown in a direction
          // and are given a powerup and a cooldown.
          if (buttons & BT_SPEED && buttons & BT_CROUCH && CheckInventory("OnTheGround") == 0)
          {
              ThrustThingZ(0,120,1,0);
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35);
              // This script just gives +Ghost, then removes it after a short pause.
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0);
          }
          if (buttons & BT_SPEED && buttons & BT_FORWARD)
          {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(KurtAngle+0,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(KurtAngle+0,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35);
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0);
          }
          if (buttons & BT_SPEED && buttons & BT_MOVELEFT)
          {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(KurtAngle+64,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(KurtAngle+64,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0);
          }
          if (buttons & BT_SPEED && buttons & BT_BACK)
          {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(KurtAngle+128,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(KurtAngle+128,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0);
          }
          if (buttons & BT_SPEED && buttons & BT_MOVERIGHT)
          {
              if (CheckInventory("OnTheGround") == 1) { ThrustThing(KurtAngle+192,35,1,0); ThrustThingZ(0,85,1,1); } else { ThrustThing(KurtAngle+192,25,0,0); ThrustThingZ(0,20,0,0); }
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35); 
              ACS_ExecuteAlways(WEEB_DECORATE,0,6,0,0);
          }
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

        // OH SHIT I'M OUT OF HEALTH
        // SUDDENLY AND COINCIDENTALLY I HAVE A MASSIVE CRAVING FOR MUNCHIES
        if (CheckInventory("ContraLifeToken") == 0 && CheckInventory("OverLifeToken") == 0 && !isDead(0) && GameSkill() != 5 && CheckInventory("IAmADumbPersonWhoWillProbablyAccidentallyDie") == 0)
        {
          if (GetSomeHealthAlready >= 60)
          {
            FadeRange(255,0,0,0.25,0,0,0,0,1.00);
            LocalAmbientSound("health/low",127);
            GetSomeHealthAlready = 0;
          }
        GetSomeHealthAlready++;
        }
        else
        {
            GetSomeHealthAlready = 0;
        }

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
            TakeInventory("SentinelUp",1);
            TakeInventory("SentinelActive",1);
            TakeInventory("BlindGuardianShieldUp",1);
            TakeInventory("BlindGuardianShieldActive",1);
            TakeInventory("SentinelLifeCounter",0x7FFFFFFF);
            TakeInventory("BlindGuardianLifeCounter",0x7FFFFFFF);
            if (GetCvar("dst_debug") == 1) { Log(s:"Player ", d:pln, s:" dead, terminating WEEB_ENTER."); }
            terminate;
        }
    }
}

// Below are universal scripts that affect both Shihong and Hae-Lin.

script WEEB_DOUBLETAP ENTER
{
    while (1)
    {
        // After the player doubletaps, delays a short bit and then takes it away.
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
    // The higher your rank is, the faster your meter degenerates.
    while (1)
    {
        if (CheckInventory("HyperComboCounter") == 0)
        {
            TakeInventory("FRankAnnounced",1);
            TakeInventory("DRankAnnounced",1);
            TakeInventory("CRankAnnounced",1);
            TakeInventory("BRankAnnounced",1);
            TakeInventory("ARankAnnounced",1);
            TakeInventory("SRankAnnounced",1);
        }
        if (CheckInventory("HyperComboCounter") < 50) { Delay(12); }
        if (CheckInventory("HyperComboCounter") >= 50 && CheckInventory("HyperComboCounter") < 100 ) { Delay(10); }
        if (CheckInventory("HyperComboCounter") >= 100 && CheckInventory("HyperComboCounter") < 150 ) { Delay(8); }
        if (CheckInventory("HyperComboCounter") >= 150 && CheckInventory("HyperComboCounter") < 200 ) { Delay(6); }
        if (CheckInventory("HyperComboCounter") >= 200 && CheckInventory("HyperComboCounter") < 250 ) { Delay(4); }
        if (CheckInventory("HyperComboCounter") >= 250 && CheckInventory("HyperComboCounter") < 300 ) { Delay(2); }
        if (CheckInventory("HyperComboCounter") >= 300 ) { Delay(1); }
        if (CheckInventory("MidCombat") == 0) { TakeInventory("HyperComboCounter",1); }
    }
}

script WEEB_GLOBAL ENTER
{
    int IsBrutal = 0;
    int i, j, k;
    int mtotal;
    int mkilled;
    int stotal;
    int sfound;
    int sfound2;
    int IFuckedTheGameUp;
    int pln = PlayerNumber();

    i = unusedTID(37000, 47000);

    sfound = GetLevelInfo(LEVELINFO_FOUND_SECRETS);

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

    while(1)
    {
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

        // Yes, this mod is 100% compatible with Brutal Doom. Absolutely nothing bad will happen!
        if (isbrutal)
        {
            k = unusedTID(23000, 33000);
                
            if (ThingCountName("GoldenBoner",0) < (20 * PlayerCount()))
                { Spawn("GoldenBoner",GetActorX(0),GetActorY(0),GetActorZ(0),k); }

            Thing_Hate(k,0,2);
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

        delay(1);
        if (IsDead(0))
            { flashlightOn[pln] = 0; terminate; }
    }
}