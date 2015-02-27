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
    int IsBrutal = 0;
    int mytid;
    int i, j, k, ang;
    int MarchOfTheImmortal;
    int IronArmor;
    int armor;
    int oarmor;
    int pln = PlayerNumber();
    int ZDum;
    int Angel;
    int xOffset, yOffset, zOffset;
    int xOffset2, yOffset2, zOffset2;
    int velx, vely, velz;
    int nx, ny, nz;
    int nx2, ny2, nz2;
    int ShieldTID;
    int SentTID;
    int TheAngerInside;
    i = unusedTID(37000, 47000);
    int u = unusedTID(37000, 47000);
    int IntroChance;
    int ShieldHP;
    int SentinelHP;
    int NewShieldHP;
    int NewSentinelHP;
    int GetSomeHealthAlready;
    int speedmod;
    int mtotal;
    int mkilled;
    int stotal;
    int sfound;
    int sfound2;

    sfound = GetLevelInfo(LEVELINFO_FOUND_SECRETS);

    if (CheckInventory("IsJungHaeLin") == 0) { terminate; }

    if (CheckInventory("ImAlive") == 0 && GameType() != GAME_TITLE_MAP)
    // If the player is spawning for the first time.
    {
        if (GameSkill () == 0) { GiveInventory("BabyMarker",1); GiveInventory("ContraLifeToken",10); }
        if (GameSkill () == 1) { GiveInventory("EasyMarker",1); GiveInventory("ContraLifeToken",8);  }
        if (GameSkill () == 2) { GiveInventory("NormalMarker",1); GiveInventory("ContraLifeToken",6); }
        if (GameSkill () == 3) { GiveInventory("HardMarker",1); GiveInventory("ContraLifeToken",4); }
        if (GameSkill () == 4) { GiveInventory("NightmareMarker",1); GiveInventory("ContraLifeToken",2); }
        FadeRange(0,0,0,1.00,0,0,0,0,3.50);
        LocalAmbientSound("level/intro",127);

        if (Spawn("DemonSteeleIsSuperCoolAndYouShouldProbablyPlayIt", GetActorX(0), GetActorY(0), GetActorZ(0), u))
        {
            Thing_Remove(u);
            MusicRandomizerIsIncluded = 1;
            GiveInventory("IAmAnAwesomePersonWhoLikesCoolMusic",1);
        }
        GiveInventory("ImAlive",1);

        if (GetCvar("ds_omenstart") == 1)
        {
            GiveInventory("Kharon + Omen",1);
            GiveInventory("GotHammer",1);
        }

        if (GetCvar("ds_backpackstart") == 1)
        {
            GiveInventory("Backpack",1);
        }
    }
    else if (CheckInventory("ImAlive") == 1 && CheckInventory("AlreadyInLevel") == 0)
    // If the player isn't respawning but is entering a level fresh.
    {
        IntroChance = random(0,2);
        if (IntroChance == 2) { LocalAmbientSound("haelin/intro",127); }
        TakeInventory("PointsFoundAllSecrets",1);
        TakeInventory("PointsKilledMonsters",1);
        //GiveInventory("PointsSpeedrunning",875);
        //GiveInventory("PointsNoSpecials",1);
        //GiveInventory("PointsNoAttacks",1);
    }

    if (CheckInventory("SentinelUp") == 1)
    {
        NewSentinelHP = CheckInventory("SentinelLifeCounter");
        TakeInventory("SentinelActive",1);
        GiveInventory("SentinelFromPreviousLevel",1);
    }
    if (CheckInventory("BlindGuardianShieldUp") == 1)
    {
        NewShieldHP = CheckInventory("BlindGuardianLifeCounter");
        TakeInventory("BlindGuardianShieldActive",1);
        GiveInventory("BlindGuardianFromPreviousLevel",1);
    }

    if (Spawn("Brutal_Blood",GetActorX(0),GetActorY(0),GetActorZ(0),i) || Spawn("BrutalPistol",GetActorX(0),GetActorY(0),GetActorZ(0),i) || GetCvar("ds_2brutal") == 1)
    {
        Thing_Remove(i);
        isbrutal = 1;
        GiveInventory("PointsIsBrutal",1);
    }

    SetActorProperty(0,APROP_INVULNERABLE,0); // Just in case some wiseass exits while invuln.
    SetActorProperty(0,APROP_RENDERSTYLE,STYLE_Normal);
    if (GameType() == GAME_NET_DEATHMATCH) { SetActorProperty(0,APROP_Species,"DMPlayer"); }
    else { SetActorProperty(0,APROP_Species,"Player"); }
    SetPlayerProperty(0,0,PROP_TOTALLYFROZEN);
    SetActorProperty(0,APROP_Gravity,0.85);
    GiveInventory("NewLevelStatReset",1);
    GiveInventory("FlashlightStopper",1);
    if (CheckInventory("HammerCharge") > 100)
    {
        TakeInventory("HammerCharge",100); // A bit brute-force, but they'll regain it back.
        SetAmmoCapacity("HammerCharge",100);
    }
    if (CheckInventory("InIronMaiden") == 1) { ACS_ExecuteAlways(275,0,WEEB_DEC_CHANGEMUS,0,0); }
    
    while (1)
    {
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

        if ((XMen2 == XMen) && (Ys2 == Ys)) { GiveInventory("WaitingTooLong",1); }
        else { TakeInventory("WaitingTooLong",0x7FFFFFFF); }

        if (GetCvar("ds_infinitesouls") == 1) { GiveInventory("SuperMeterCounter",1); }
        if (GetCvar("compat_disabletaunts") == 1) { GiveInventory("NoTauntAllowed",1); }
           else { TakeInventory("NoTauntAllowed",1); }
           
        if (GetCvar("ds_gunsouls") == 0) { GiveInventory("IAmASkilledPersonWhoWantsOnlyMySwordToGiveSouls",1); }
           else { TakeInventory("IAmASkilledPersonWhoWantsOnlyMySwordToGiveSouls",1); }

        if (GetCvar("ds_doomhealth") == 1) { GiveInventory("IAmATraditionalDoomerWhoLikesNumbersOverTokens",1); }
           else { TakeInventory("IAmATraditionalDoomerWhoLikesNumbersOverTokens",1); }

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
        // given a dummy token that indicates they got it at first.
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
        if (sfound > sfound2) // Found a secret.
        {
            GiveInventory("ManPoints",1);
            sfound2 = sfound;
        }
        if (stotal != 0 && stotal == sfound && CheckInventory("PointsFoundAllSecrets") == 0) // Found all secrets.
        {
            GiveInventory("ManPoints",9); // Plus the previous 10000 for a total of 100000.
            GiveInventory("PointsFoundAllSecrets",1);
        }

        // Health nonsense
        
        if( GetCVar( "ds_doomhealth" ) == 1 )
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
                if (CheckInventory("BlindGuardianFromPreviousLevel") == 1)
                {
                    SetActorProperty(ShieldTID,APROP_Health,NewShieldHP);
                    TakeInventory("BlindGuardianFromPreviousLevel",1);
                }
            }
            else
            {
                // WOOP WOOP PULL OVER DAT ASS TOO FAT
                // (angle's factored in; pitch isn't)
                // (it'd be bad for an attack to slip through because the player's looking up/down)
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

        // I will not make a Hammertime joke. I will not make a Hammertime joke. I will not make a Hammertime joke.
        if (CheckInventory("HammerUp") == 1)
        {
           if (CheckInventory("HammerCharge") >= 90 && CheckInventory("HammerCharge") <= 100 )
               { if (RideTheLightning >= 34) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") > 100)
               { if (RideTheLightning >= 8) { GiveInventory("HammerCharge",1); GiveInventory("ChargeScreenFlash",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 80)
               { if (RideTheLightning >= 27) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 60)
               { if (RideTheLightning >= 22) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 40)
               { if (RideTheLightning >= 17) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 20)
               { if (RideTheLightning >= 12) { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
           else if (CheckInventory("HammerCharge") >= 0)
               { if (RideTheLightning >= 7)  { GiveInventory("HammerCharge",1); RideTheLightning = 0; }}
        }
        else { if (RideTheLightning >= 40 && CheckInventory("HammerCharge") >= 30)  { TakeInventory("HammerCharge",1); RideTheLightning = 0; }}
        RideTheLightning++;

        TakeInventory("GhostStepCooldown",1);
        TakeInventory("DoubleTapCooldown",1);
        TakeInventory("EnviroDamageCooldown",1);
        TakeInventory("DoubleTapReadyRight",1);
        TakeInventory("DoubleTapReadyForward",1);
        TakeInventory("DoubleTapReadyLeft",1);
        TakeInventory("DoubleTapReadyBack",1);
        TakeInventory("MidCombat",1);
        TakeInventory("HenshinCooldown",1);
        //TakeInventory("PointsSpeedrunning",1);
        if (CheckInventory("EnviroDamageCooldown") == 0) { TakeInventory("EnviroDamageCount",3); }
    
        // If the player still has life left, they get full health.
        if( GetCVar( "ds_doomhealth" ) == 0 )
        {
            if (CheckInventory("ContraLifeToken") >= 1 || CheckInventory("OverLifeToken") >= 1 || CheckInventory("ContraArmorToken") >= 1)
            { GiveInventory("999Health",999); }
            else
            { SetActorProperty(0,APROP_HEALTH,1); }
        }
        
        // Not the kind you lean on.
        SuperCount = CheckInventory("SuperMeterCounter");
        //SetInventory("SuperCounter1",SuperCount); // Life would be so much easier if this worked online.
        TakeInventory("SuperCounter1", 0x7FFFFFFF);
        GiveInventory("SuperCounter1", SuperCount);
        if (SuperCount < 20) { if (TheAngerInside >= 280) { GiveInventory("SuperMeterCounter",1); TheAngerInside = 0; }}
        if (SuperCount > 100) { TakeInventory("SuperCounter2",0x7FFFFFFF); GiveInventory("SuperCounter2", SuperCount - 100); } //SetInventory("SuperCounter2",(SuperCount - 100)); }
            else { TakeInventory("SuperCounter2",0x7FFFFFFF); }
        if (SuperCount > 200) { TakeInventory("SuperCounter3",0x7FFFFFFF); GiveInventory("SuperCounter3", SuperCount - 200); } //SetInventory("SuperCounter3",(SuperCount - 200)); }
            else { TakeInventory("SuperCounter3",0x7FFFFFFF); }
        if (SuperCount > 300) { TakeInventory("SuperCounter4",0x7FFFFFFF); GiveInventory("SuperCounter4", SuperCount - 300); } //SetInventory("SuperCounter3",(SuperCount - 200)); }
            else { TakeInventory("SuperCounter4",0x7FFFFFFF); }
        TheAngerInside++;

        // 666 COMBO! SUPER SWEET STYLISH!
        ComboCount = CheckInventory("HyperComboCounter");
        TakeInventory("ComboCounter1",0x7FFFFFFF);
        GiveInventory("ComboCounter1",ComboCount);
        if (ComboCount <= 50) { TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); }
        if (ComboCount > 50)
            { TakeInventory("ComboCounter2",0x7FFFFFFF); GiveInventory("ComboCounter2",(ComboCount - 50)); GiveInventory("ComboDamageLevel1",1);
              GiveInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter2",0x7FFFFFFF); TakeInventory("ComboDamageLevel1",0x7FFFFFFF); }
        if (ComboCount > 100)
            { TakeInventory("ComboCounter3",0x7FFFFFFF); GiveInventory("ComboCounter3",(ComboCount - 100)); GiveInventory("ComboDamageLevel2",1);
              TakeInventory("FRank",1); GiveInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter3",0x7FFFFFFF); TakeInventory("ComboDamageLevel2",0x7FFFFFFF); }
        if (ComboCount > 150)
            { TakeInventory("ComboCounter4",0x7FFFFFFF); GiveInventory("ComboCounter4",(ComboCount - 150)); GiveInventory("ComboDamageLevel3",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); GiveInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter4",0x7FFFFFFF); TakeInventory("ComboDamageLevel3",0x7FFFFFFF); }
        if (ComboCount > 200)
            { TakeInventory("ComboCounter5",0x7FFFFFFF); GiveInventory("ComboCounter5",(ComboCount - 200)); GiveInventory("ComboDamageLevel4",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); GiveInventory("BRank",1); TakeInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter5",0x7FFFFFFF); TakeInventory("ComboDamageLevel4",0x7FFFFFFF); }
        if (ComboCount > 250)
            { TakeInventory("ComboCounter6",0x7FFFFFFF); GiveInventory("ComboCounter6",(ComboCount - 250)); GiveInventory("ComboDamageLevel5",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); GiveInventory("ARank",1); TakeInventory("SRank",1); } else { TakeInventory("ComboCounter6",0x7FFFFFFF); TakeInventory("ComboDamageLevel5",0x7FFFFFFF); }
        if (ComboCount > 300)
            { TakeInventory("ComboCounter7",0x7FFFFFFF); GiveInventory("ComboCounter7",(ComboCount - 300)); GiveInventory("ComboDamageLevel6",1);
              TakeInventory("FRank",1); TakeInventory("DRank",1); TakeInventory("CRank",1); TakeInventory("BRank",1); TakeInventory("ARank",1); GiveInventory("SRank",1); } else { TakeInventory("ComboCounter7",0x7FFFFFFF); TakeInventory("ComboDamageLevel6",0x7FFFFFFF); }

        // Global variables
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

        if (GetCvar("ds_nospecials") == 0)
        {
        if (buttons & BT_ALTATTACK && CheckInventory("SuperMeterCounter") >= 20)
            { GiveInventory("SynthAltFire",1); }
        else
            { TakeInventory("SynthAltFire",1); }

        if (keypressed(BT_MOVERIGHT))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyRight") >= 1) { GiveInventory("DoubleTapRight",1); GiveInventory("DoubleTapCooldown",20); }
                      else { GiveInventory("DoubleTapReadyRight",8); }}}
        if (keypressed(BT_MOVELEFT))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyLeft") >= 1) { GiveInventory("DoubleTapLeft",1); GiveInventory("DoubleTapCooldown",20); }
                      else { GiveInventory("DoubleTapReadyLeft",8); }}}
        if (keypressed(BT_FORWARD))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyForward") >= 1) { GiveInventory("DoubleTapForward",1); GiveInventory("DoubleTapCooldown",20); }
                      else { GiveInventory("DoubleTapReadyForward",8); }}}
        if (keypressed(BT_BACK))
            { if (CheckInventory("SuperMeterCounter") >= 20 && CheckInventory("DoubleTapCooldown") == 0)
                    { if (CheckInventory("DoubleTapReadyBack") >= 1) { GiveInventory("DoubleTapBack",1); GiveInventory("DoubleTapCooldown",20); }
                      else { GiveInventory("DoubleTapReadyBack",8); }}}
        }

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
                GiveInventory("AcesHigh", 1);
            }
            else
            {
                ThrustThingZ(0,42,0,0);
                if (CheckInventory("VertIGo") == 1 ) { GiveInventory("AcesHigh",1); }
                else { GiveInventory("VertIGo",1); }
            }
        }
        // Remove AcesHigh when we're back on the ground
        if (CheckInventory("OnTheGround") && CheckInventory("AcesHigh"))
            TakeInventory("AcesHigh", 1);
    // This concludes the block of code done by Kyle873.
    // You may now applaud his genius.

        // Dodging
        if (CheckInventory("GhostStepCooldown") == 0 && CheckInventory("GhostStepDone") == 0)
        {
          if (buttons & BT_SPEED && buttons & BT_CROUCH && CheckInventory("OnTheGround") == 0)
          {
              ThrustThingZ(0,120,1,0);
              ActivatorSound("ghost/step",127);
              GiveInventory("GhostStepDone",1);
              GiveInventory("GhostStepCooldown",35);
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

        oarmor = armor;
        armor = CheckInventory("Armor");

        if (oarmor > armor && CheckInventory("InIronMaiden") == 1)
        {
          ActivatorSound("iron/armorhit", 127);
          FadeRange(255,255,0,min(0.5,(oarmor-armor)*0.015),0,0,0,0.0,min(35.0,1.5*(oarmor-armor))/35); 
          GiveInventory("MidCombat",75);
        }

        if (CheckInventory("InIronMaiden") == 1)
        {

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

          if (CheckInventory("SuperMeterCounter") > 0)
          {
            SetActorProperty(0,APROP_JUMPZ,10.0);

            if (CheckInventory("SuperMeterCounter") < 31 && CheckInventory("IronMaidenWarning") == 0)
            {
              GiveInventory("IronMaidenWarning",1);
              FadeRange(255,255,255,0.50,0,0,0,0,0.5);
              LocalAmbientSound("henshin/warning",127);
            }

            if (CheckInventory("HenshinDeactivation") == 1)
            {
              GiveInventory("HenshinCooldown",35);
              LocalAmbientSound("henshin/complete",127);
              ActivatorSound("henshin/completedismiss",127);
              ACS_ExecuteWithResult(WEEB_DECORATE,WEEB_DEC_REMOVEKEBAB,0,0);
              MarchOfTheImmortal = 0;
              IronArmor = 0;
            }

            if (IronArmor >= 5)
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

            if (CheckInventory("MidCombat") > 1)
            {
              if (MarchOfTheImmortal >= 26)
              {
                TakeInventory("SuperMeterCounter",1);
                MarchOfTheImmortal = 0;
              }
            }
            else
            {
              if (MarchOfTheImmortal >= 21)
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

        if (GetCvar("ds_runmod") < 10001 && GetCvar("ds_runmod") > -2) // I forget what the maximum integer is. 36525? Well, whatever, anything beyond that and it'll crash.
        {
            speedmod = max(0, condFalse(GetCVar("ds_runmod"), 100)) * 0.01; // Get the percentage equivalent of the value...
            SetActorProperty(0, APROP_Speed, speedmod); // And adjust the player's speed accordingly.
        }

        if (isbrutal)
        { // Yes, this mod is 100% compatible with Brutal Doom. Absolutely nothing bad will happen!
            k = unusedTID(23000, 33000);
                
            if (ThingCountName("GoldenBoner",0) < (20 * PlayerCount()))
                { Spawn("GoldenBoner",GetActorX(0),GetActorY(0),GetActorZ(0),k); }

            Thing_Hate(k,mytid,2);
            Thing_ChangeTID(k,0);
        }

        if (array_recoilrules[pln]) { GiveInventory("IAmASillyPersonWhoDoesntLikeRecoil", 1); }
        else { TakeInventory("IAmASillyPersonWhoDoesntLikeRecoil", 0x7FFFFFFF); }
        if (array_autoswitch[pln]) { GiveInventory("IAmAnOkayPersonWhoLikesToAutoSwitch", 1); }
        else { TakeInventory("IAmAnOkayPersonWhoLikesToAutoSwitch", 0x7FFFFFFF); }
        if (array_beepbeepbeep[pln]) { GiveInventory("IAmADumbPersonWhoWillProbablyAccidentallyDie",1); }
        else { TakeInventory("IAmADumbPersonWhoWillProbablyAccidentallyDie", 0x7FFFFFFF); }
        if (array_nopan[pln]) { GiveInventory("IAmABoringPersonWhoThinksPointsAreForNerds",1); }
        else { TakeInventory("IAmABoringPersonWhoThinksPointsAreForNerds", 0x7FFFFFFF); }

        if (flashlightOn[pln])
            { GiveInventory("FlashlightSpawner", 1); }

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
        
        Delay(1);
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

script WEEB_DOUBLETAP ENTER
{
    while (1)
    {
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
    while (1)
    {
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