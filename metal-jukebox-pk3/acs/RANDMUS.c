#include "zcommon.acs"
#library "RANDMUS"

#include "commonFuncs.h" // Even in making a silly music randomizer mod, I require ijon's funcs.

#define RANDOMMUS 150

int MusicRandomizerOn;
int MusicInfo;

int RandMusList[RANDOMMUS] = 
{
   "Song001",
   "Song002",
   "Song003",
   "Song004",
   "Song005",
   "Song006",
   "Song007",
   "Song008",
   "Song009",
   "Song010",
   "Song011",
   "Song012",
   "Song013",
   "Song014",
   "Song015",
   "Song016",
   "Song017",
   "Song018",
   "Song019",
   "Song020",
   "Song021",
   "Song022",
   "Song023",
   "Song024",
   "Song025",
   "Song026",
   "Song027",
   "Song028",
   "Song029",
   "Song030",
   "Song031",
   "Song032",
   "Song033",
   "Song034",
   "Song035",
   "Song036",
   "Song037",
   "Song038",
   "Song039",
   "Song040",
   "Song041",
   "Song042",
   "Song043",
   "Song044",
   "Song045",
   "Song046",
   "Song047",
   "Song048",
   "Song049",
   "Song050",
   "Song051",
   "Song052",
   "Song053",
   "Song054",
   "Song055",
   "Song056",
   "Song057",
   "Song058",
   "Song059",
   "Song060",
   "Song061",
   "Song062",
   "Song063",
   "Song064",
   "Song065",
   "Song066",
   "Song067",
   "Song068",
   "Song069",
   "Song070",
   "Song071",
   "Song072",
   "Song073",
   "Song074",
   "Song075",
   "Song076",
   "Song077",
   "Song078",
   "Song079",
   "Song080",
   "Song081",
   "Song082",
   "Song083",
   "Song084",
   "Song085",
   "Song086",
   "Song087",
   "Song088",
   "Song089",
   "Song090",
   "Song091",
   "Song092",
   "Song093",
   "Song094",
   "Song095",
   "Song096",
   "Song097",
   "Song098",
   "Song099",
   "Song100",
   "Song101",
   "Song102",
   "Song103",
   "Song104",
   "Song105",
   "Song106",
   "Song107",
   "Song108",
   "Song109",
   "Song110",
   "Song111",
   "Song112",
   "Song113",
   "Song114",
   "Song115",
   "Song116",
   "Song117",
   "Song118",
   "Song119",
   "Song120",
   "Song121",
   "Song122",
   "Song123",
   "Song124",
   "Song125",
   "Song126",
   "Song127",
   "Song128",
   "Song129",
   "Song130",
   "Song131",
   "Song132",
   "Song133",
   "Song134",
   "Song135",
   "Song136",
   "Song137",
   "Song138",
   "Song139",
   "Song140",
   "Song141",
   "Song142",
   "Song143",
   "Song144",
   "Song145",
   "Song146",
   "Song147",
   "Song148",
   "Song149",
   "Song150"
};

int RandMusInfo[RANDOMMUS] = 
{
   "Artist: 3 Inches of Blood\nSong: Goatrider's Horde\nAlbum: Fire up the Blades\nGenre: Thrash Metal",
   "Artist: AC/DC\nSong: Back in Black\nAlbum: Back in Black\nGenre: Hard Rock",
   "Artist: Accept\nSong: Fast as a Shark\nAlbum: Restless and Wild\nGenre: Speed Metal",
   "Artist: Alice in Chains\nSong: Them Bones\nAlbum: Dirt\nGenre: Hard Rock",
   "Artist: All That Remains\nSong: This Darkened Heart\nAlbum: This Darkened Heart\nGenre: Melodic Death Metal",
   "Artist: Amon Amarth\nSong: Pursuit of Vikings\nAlbum: Fate of Norns\nGenre: Melodic Death Metal",
   "Artist: Annihilator\nSong: Carnival Diablos\nAlbum: Carnival Diablos\nGenre: Groove Metal",
   "Artist: Annihilator\nSong: Denied\nAlbum: Carnival Diablos\nGenre: Thrash Metal",
   "Artist: Artillery\nSong: Beneath the Clay (R.I.P.)\nAlbum: By Inheritance\nGenre: Thrash Metal",
   "Artist: Axel Rudi Pell\nSong: Fighting the Law\nAlbum: Nasty Reputation\nGenre: Heavy Metal",
   "Artist: Axel Rudi Pell\nSong: Talk of the Guns\nAlbum: Between the Walls\nGenre: Heavy Metal",
   "Artist: Behemoth\nSong: As Above, So Below\nAlbum: Zos Kia Cultis (Here and Beyond)\nGenre: Blackened Death Metal",
   "Artist: Behemoth\nSong: Carnage\nAlbum: A Tribute to Mayhem\nGenre: Blackened Death Metal",
   "Artist: Biohazard\nSong: Punishment\nAlbum: Urban Discipline\nGenre: Groove Metal",
   "Artist: Black Sabbath\nSong: Children of the Grave\nAlbum: Master of Reality\nGenre: Classic Metal",
   "Artist: Black Sabbath\nSong: N.I.B.\nAlbum: Black Sabbath\nGenre: Classic Metal",
   "Artist: Black Sabbath\nSong: Neon Knights\nAlbum: Heaven and Hell\nGenre: Heavy Metal",
   "Artist: Black Sabbath\nSong: Paranoid\nAlbum: Paranoid\nGenre: Classic Metal",
   "Artist: Black Sabbath\nSong: Sabbath Bloody Sabbath\nAlbum: Sabbath Bloody Sabbath\nGenre: Classic Metal",
   "Artist: Black Sabbath\nSong: Supernaut\nAlbum: Vol. 4\nGenre: Classic Metal",
   "Artist: Blind Guardian\nSong: A Past and Future Secret\nAlbum: Imaginations From the Other Side\nGenre: Power Metal",
   "Artist: Blind Guardian\nSong: By the Gates of Moria\nAlbum: Battalions of Fear\nGenre: Power Metal",
   "Artist: Blind Guardian\nSong: Time Stands Still (At the Iron Hill)\nAlbum: Nightfall in Middle-Earth\nGenre: Power Metal",
   "Artist: Blind Guardian\nSong: Trial By the Archon\nAlbum: Battalions of Fear\nGenre: Power Metal",
   "Artist: Burzum\nSong: Ea, Lord of the Depths\nAlbum: Demo II\nGenre: Black Metal",
   "Artist: Cacophony\nSong: Desert Island\nAlbum: Speed Metal Symphony\nGenre: Neo-Classical Metal",
   "Artist: Candlemass\nSong: Battlecry\nAlbum: Nightfall\nGenre: Doom Metal",
   "Artist: Candlemass\nSong: Dark Reflections\nAlbum: Tales of Creation\nGenre: Doom Metal",
   "Artist: Carcass\nSong: Blackstar\nAlbum: Swansong\nGenre: Melodic Death Metal",
   "Artist: Carcass\nSong: Corporal Jigsore Quandry\nAlbum: Necroticism – Descanting the Insalubrious\nGenre: Melodic Death Metal",
   "Artist: Carcass\nSong: Heartwork\nAlbum: Heartwork\nGenre: Melodic Death Metal",
   "Artist: Celtic Frost\nSong: Circle of the Tyrants\nAlbum: To Mega Thyrion\nGenre: Black Metal",
   "Artist: Children of Bodom\nSong: Bed of Razors\nAlbum: Hatebreeder\nGenre: Neo-Classical Metal",
   "Artist: Children of Bodom\nSong: Lake Bodom\nAlbum: Something Wild\nGenre: Melodic Death Metal",
   "Artist: Covenant\nSong: The Chasm\nAlbum: In Times Before Light\nGenre: Symphonic Black Metal",
   "Artist: Covenant\nSong: Through the Eyes of the Raven\nAlbum: In Times Before Light\nGenre: Symphonic Black Metal",
   "Artist: Cryptopsy\nSong: Graves of Our Fathers\nAlbum: None So Vile\nGenre: Death Metal",
   "Artist: Daisuke Ishiwatari\nSong: Suck a Sage\nAlbum: Guilty Gear X\nGenre: Speed Metal",
   "Artist: Daisuke Ishiwatari\nSong: The Midnight Carnival\nAlbum: Guilty Gear XX\nGenre: Power Metal",
   "Artist: Danzig\nSong: Mother\nAlbum: Danzig\nGenre: Classic Metal",
   "Artist: Darkest Hour\nSong: The Patriot Virus\nAlbum: Hidden Hands of a Sadist Nation\nGenre: Melodic Death Metal",
   "Artist: Death\nSong: Bite the Pain\nAlbum: The Sound of Perseverance\nGenre: Death Metal",
   "Artist: Death\nSong: Forgotten Past\nAlbum: Leprosy\nGenre: Death Metal",
   "Artist: Destruction\nSong: Invincible Force\nAlbum: Infernal Overkill\nGenre: Thrash Metal",
   "Artist: DevilDriver\nSong: Hold Back the Day\nAlbum: The Fury of Our Maker's Hand\nGenre: Groove Metal",
   "Artist: Diamond Head\nSong: The Prince\nAlbum: Lightning to the Nations\nGenre: Heavy Metal",
   "Artist: Dimmu Borgir\nSong: Blessing Upon the Throne of Tyranny\nAlbum: Puritanical Euphoric Misanthropia\nGenre: Symphonic Black Metal",
   "Artist: Dimmu Borgir\nSong: Mourning Palace\nAlbum: Enthrone Darkness Triumphant\nGenre: Symphonic Black Metal",
   "Artist: Dio\nSong: Evil Eyes\nAlbum: The Last in Line\nGenre: Classic Metal",
   "Artist: Dio\nSong: Holy Diver\nAlbum: Holy Diver\nGenre: Classic Metal",
   "Artist: Disturbed\nSong: Down With the Sickness\nAlbum: Sickness\nGenre: Nu Metal",
   "Artist: Dream Theater\nSong: The Dance of Eternity\nAlbum: Metropolis, Pt. 2: Scenes from a Memory\nGenre: Progressive Metal",
   "Artist: Drowning Pool\nSong: Bodies\nAlbum: Sinner\nGenre: Nu Metal",
   "Artist: Ensiferum\nSong: Sword Chant\nAlbum: Iron\nGenre: Folk Metal",
   "Artist: Fear Factory\nSong: Edge Crusher\nAlbum: Obsolete\nGenre: Industrial Death Metal",
   "Artist: Fear Factory\nSong: Flashpoint\nAlbum: Demanufacture\nGenre: Industrial Death Metal",
   "Artist: Fear Factory\nSong: Replica\nAlbum: Demanufacture\nGenre: Industrial Death Metal",
   "Artist: FMS\nSong: All Guns Blazing\nAlbum: N/A\nGenre: Thrash Metal",
   "Artist: FMS\nSong: Into the Fire\nAlbum: N/A\nGenre: Thrash Metal",
   "Artist: Gamma Ray\nSong: Future Madhouse\nAlbum: Insanity and Genius\nGenre: Power Metal",
   "Artist: Gamma Ray\nSong: Land of the Free\nAlbum: Land of the Free\nGenre: Power Metal",
   "Artist: Gamma Ray\nSong: Man on a Mission\nAlbum: Land of the Free\nGenre: Power Metal",
   "Artist: Gamma Ray\nSong: Send Me a Sign\nAlbum: Power Plant\nGenre: Power Metal",
   "Artist: Gamma Ray\nSong: Strangers in the Night\nAlbum: Power Plant\nGenre: Power Metal",
   "Artist: Gamma Ray\nSong: Valley of the Kings\nAlbum: Somewhere Out in Space\nGenre: Power Metal",
   "Artist: Godsmack\nSong: Keep Away\nAlbum: Godsmack\nGenre: Nu Metal",
   "Artist: Godsmack\nSong: Whatever\nAlbum: Godsmack\nGenre: Nu Metal",
   "Artist: Graveworm\nSong: A Dreaming Beauty\nAlbum: As the Angels Reach the Beauty\nGenre: Symphonic Metal",
   "Artist: GWAR\nSong: Sick of You\nAlbum: Scumdogs of the Universe\nGenre: Heavy metal",
   "Artist: Hammerfall\nSong: Heeding the Call\nAlbum: Legacy of Kings\nGenre: Power Metal",
   "Artist: Helloween\nSong: Judas\nAlbum: Walls of Jericho\nGenre: Speed Metal",
   "Artist: Helloween\nSong: Phantoms of Death\nAlbum: Walls of Jericho\nGenre: Speed Metal",
   "Artist: Hexen\nSong: Blast Radius\nAlbum: State of Insurgency\nGenre: Thrash Metal",
   "Artist: Hexen\nSong: Gas Chamber\nAlbum: State of Insurgency\nGenre: Speed Metal",
   "Artist: Hexen\nSong: Mutiny and Betrayal\nAlbum: State of Insurgency\nGenre: Progressive Metal",
   "Artist: Hexen\nSong: Past Life\nAlbum: State of Insurgency\nGenre: Thrash Metal",
   "Artist: Hexen\nSong: State of Insurgency\nAlbum: State of Insurgency\nGenre: Thrash Metal",
   "Artist: In Flames\nSong: Food for the Gods\nAlbum: Whoracle\nGenre: Melodic Death Metal",
   "Artist: In Flames\nSong: Jotun\nAlbum: Whoracle\nGenre: Melodic Death Metal",
   "Artist: Iron Fire\nSong: Hail to Odin\nAlbum: To the Grave\nGenre: Power Metal",
   "Artist: Iron Maiden\nSong: 2 Minutes to Midnight\nAlbum: Powerslave\nGenre: Heavy Metal",
   "Artist: Iron Maiden\nSong: Judas Be My Guide\nAlbum: Fear of the Dark\nGenre: Heavy Metal",
   "Artist: It Dies Today\nSong: A Threnody For Modern Romance\nAlbum: The Caitiff Choir\nGenre: Metalcore",
   "Artist: Judas Priest\nSong: Painkiller\nAlbum: Painkiller\nGenre: Thrash Metal",
   "Artist: Judas Priest\nSong: The Sentinel\nAlbum: Defenders of the Faith\nGenre: Heavy Metal",
   "Artist: Judas Priest\nSong: Tyrant\nAlbum: Sad Wings of Destiny\nGenre: Classic Metal",
   "Artist: King Diamond\nSong: The Puppet Master\nAlbum: The Puppet Master\nGenre: Heavy Metal",
   "Artist: Lamb of God\nSong: Ruin\nAlbum: As the Palaces Burn\nGenre: Groove Metal",
   "Artist: Lazarus A.D.\nSong: Revolution\nAlbum: The Onslaught\nGenre: Speed Metal",
   "Artist: Lee Jackson\nSong: Preparation D\nAlbum: Duke Nukem 3D\nGenre: Groove Metal",
   "Artist: Macabre\nSong: Hitchhiker\nAlbum: Dahmer\nGenre: Death Metal",
   "Artist: Manowar\nSong: Kings of Metal\nAlbum: Kings of Metal\nGenre: Power Metal",
   "Artist: Megadeth\nSong: Angry Again\nAlbum: Youthanasia\nGenre: Thrash Metal",
   "Artist: Megadeth\nSong: Hangar 18\nAlbum: Rust in Peace\nGenre: Thrash Metal",
   "Artist: Megadeth\nSong: Holy Wars... The Punishment Due\nAlbum: Rust in Peace\nGenre: Thrash Metal",
   "Artist: Megadeth\nSong: Symphony of Destruction\nAlbum: Countdown to Extinction\nGenre: Heavy Metal",
   "Artist: Meshuggah\nSong: Bleed\nAlbum: obZen\nGenre: Extreme Metal",
   "Artist: Metallica\nSong: Creeping Death\nAlbum: Ride the Lightning\nGenre: Thrash Metal",
   "Artist: Metallica\nSong: Enter Sandman\nAlbum: The Black Album\nGenre: Heavy Metal",
   "Artist: Metallica\nSong: Fuel\nAlbum: Reload\nGenre: Thrash Metal",
   "Artist: Metallica\nSong: Master of Puppets\nAlbum: Master of Puppets\nGenre: Thrash Metal",
   "Artist: Motorhead\nSong: I Am the Sword\nAlbum: Bastards\nGenre: Heavy Metal",
   "Artist: Motorhead\nSong: Sacrifice\nAlbum: Sacrifice\nGenre: Heavy Metal",
   "Artist: N.EX.T.\nSong: In the Arms of Death\nAlbum: Guilty Gear XX #Reload\nGenre: Black Metal",
   "Artist: Nightwish\nSong: Elvenpath\nAlbum: Angels Fall First\nGenre: Symphonic Metal",
   "Artist: Nightwish\nSong: Planet Hell\nAlbum: Once\nGenre: Symphonic Metal",
   "Artist: Nightwish\nSong: The Pharaoh Sails to Orion\nAlbum: Oceanborn\nGenre: Symphonic Metal",
   "Artist: Nile\nSong: 4th Arra of Dagon\nAlbum: Those Whom the Gods Detest\nGenre: Death Metal",
   "Artist: Opeth\nSong: The Funeral Portrait\nAlbum: Blackwater Park\nGenre: Death Metal",
   "Artist: Overkill\nSong: Damned\nAlbum: Killbox 13\nGenre: Thrash Metal",
   "Artist: Overkill\nSong: Thunderhead\nAlbum: Bloodletting\nGenre: Thrash Metal",
   "Artist: Overkill\nSong: Wrecking Crew\nAlbum: Taking Over\nGenre: Thrash Metal",
   "Artist: Pantera\nSong: Cowboys From Hell\nAlbum: Cowboys From Hell\nGenre: Groove Metal",
   "Artist: Pantera\nSong: Drag the Waters\nAlbum: The Great Southern Trendkill\nGenre: Sludge Metal",
   "Artist: Pantera\nSong: Sandblasted Skin\nAlbum: The Great Southern Trendkill\nGenre: Groove Metal",
   "Artist: Pantera\nSong: Yesterday Don't Mean Shit\nAlbum: Reinventing the Steel\nGenre: Groove Metal",
   "Artist: PRIMEVAL\nSong: Killing Spree\nAlbum: N/A\nGenre: Thrash Metal",
   "Artist: Rage\nSong: Lost in the Ice\nAlbum: The Missing Link\nGenre: Power Metal",
   "Artist: Rammstein\nSong: Engel\nAlbum: Sehnsucht\nGenre: Industrial Metal",
   "Artist: Rammstein\nSong: Tier\nAlbum: Sehnsucht\nGenre: Industrial Metal",
   "Artist: Riot\nSong: Angel Eyes\nAlbum: Irishmore\nGenre: Speed Metal",
   "Artist: Running Wild\nSong: Angel of Mercy\nAlbum: Rogues en Vogue\nGenre: Heavy Metal",
   "Artist: Running Wild\nSong: Draw the Line\nAlbum: Rogues en Vogue\nGenre: Heavy Metal",
   "Artist: Running Wild\nSong: Port Royal\nAlbum: Port Royal\nGenre: Power Metal",
   "Artist: Running Wild\nSong: Riding the Storm\nAlbum: Death or Glory\nGenre: Power Metal",
   "Artist: Sepultura\nSong: Refuse/Resist\nAlbum: Confuse, A.D.\nGenre: Death Metal",
   "Artist: set_abominae\nSong: A Succubus in Rapture\nAlbum: N/A\nGenre: Symphonic Metal",
   "Artist: Shadows Fall\nSong: Enlightened By the Cold\nAlbum: The War Within\nGenre: Melodic Death Metal",
   "Artist: Shadows Fall\nSong: The Idiot Box\nAlbum: The Art of Balance\nGenre: Melodic Death Metal",
   "Artist: SilentZorah\nSong: Annihilation Awaits\nAlbum: N/A\nGenre: Heavy Metal",
   "Artist: Slayer\nSong: Bloodline\nAlbum: God Hates Us All\nGenre: Groove Metal",
   "Artist: Slayer\nSong: Dead Skin Mask\nAlbum: Seasons in the Abyss\nGenre: Groove Metal",
   "Artist: Slayer\nSong: Show No Mercy\nAlbum: Show No Mercy\nGenre: Thrash Metal",
   "Artist: Sonata Arctica\nSong: Abandoned, Pleased, Brainwashed, Exploited\nAlbum: Winterheart's Guild\nGenre: Power Metal",
   "Artist: Sonata Arctica\nSong: Kingdom For a Heart\nAlbum: Ecliptica\nGenre: Power Metal",
   "Artist: Sonic Mayhem\nSong: Descent into Cerberon\nAlbum: Quake II\nGenre: Industrial Metal",
   "Artist: Sonic Mayhem\nSong: Quad Machine\nAlbum: Quake II\nGenre: Industrial Metal",
   "Artist: Sonic Mayhem\nSong: Rage\nAlbum: Quake II\nGenre: Industrial Metal",
   "Artist: Symphony X\nSong: A Fool's Paradise\nAlbum: V\nGenre: Symphonic Metal",
   "Artist: Symphony X\nSong: Pharaoh\nAlbum: The Divine Wings of Tragedy\nGenre: Progressive Metal",
   "Artist: Taro Bando & Hajime Wakai\nSong: Devil's Forest\nAlbum: F-Zero X\nGenre: Thrash Metal",
   "Artist: Testament\nSong: D.N.R. (Do Not Resuscitate)\nAlbum: The Gathering\nGenre: Thrash Metal",
   "Artist: Testament\nSong: True Believer\nAlbum: The Gathering\nGenre: Thrash Metal",
   "Artist: Transmetal\nSong: Mexico Barbaro\nAlbum: Mexico Barbaro\nGenre: Death Metal",
   "Artist: Venom\nSong: Don't Burn the Witch\nAlbum: Black Metal\nGenre: Thrash Metal",
   "Artist: VKiller\nSong: Switchback\nAlbum: N/A\nGenre: Thrash Metal",
   "Artist: W.A.S.P.\nSong: Wild Child\nAlbum: The Last Command\nGenre: Heavy Metal",
   "Artist: White Zombie\nSong: I, Zombie\nAlbum: Astro-Creep: 2000\nGenre: Industrial Metal",
   "Artist: White Zombie\nSong: Temple of the Bull\nAlbum: N/A\nGenre: Industrial Metal",
   "Artist: Wizard\nSong: Hall of Odin\nAlbum: Odin\nGenre: Power Metal"
};

Script 346 OPEN NET clientside
{
int i;
int randomhack;
int lastmus;

    if (GetCvar("norandommusic") == 0)
    {
        MusicRandomizerOn = 1;
        if (GetCvar("mus_runninginzdoom") == 1)
        {
            i = random(0, RANDOMMUS-1);
            SetMusic(RandMusList[i],0);
        }
        else
        // Zandronum is funny about this. Online, it generates the same random seed every
        // time, even though that's the opposite of what you'd expect from a random call.
        // I have to use a workaround to generate pseudo-random behavior.
        // But it's better than dealing with ZDoom's barely-functional slapshod netcode!
        {
            randomhack = defaultCVar("mus_cl_randomhack",   0);
            lastmus    = defaultCVar("mus_cl_lastmusic",    0) - 1;

            for (i = 0; i < randomhack; i++) { random(0, 1); }
            randomhack = random(0, 500);
            SaveCVar("mus_cl_randomhack", randomhack);

            do { i = random(0, RANDOMMUS-1); }
            while (i == lastmus);

            SetMusic(RandMusList[i], 0);
            SaveCVar("mus_cl_lastmusic", i + 1);
        }
        Delay(35);
        if (GetCvar("nomusicinfo") == 0)
        {
            MusicInfo = RandMusInfo[i];
            SetFont("SmallFont");
            hudmessage(s:MusicInfo; HUDMSG_FADEINOUT | HUDMSG_LOG, 0, CR_WHITE, 0.1, 0.8, 3.0, 0.5, 1.0);
        }
    }
    else
    {
        MusicRandomizerOn = 0;
    }
}

script 347 OPEN clientside
{
    delay(1);
    if (GetCvar("mus_runninginzdoom") == 0) // No option to disable on ZDoom because I'm pretty sure the only way this'll
    {                                       // be happening is when you manually load it, ergo want to listen to it...
        if (!GetCvar("norandommusic"))
            { ConsoleCommand("set norandommusic 0");
              ConsoleCommand("archivecvar norandommusic"); }
        if (!GetCvar("nomusicinfo"))
            { ConsoleCommand("set nomusicinfo 0");
              ConsoleCommand("archivecvar nomusicinfo"); }
    }
}

script 348 (void) NET clientside
{
int i;
int randomhack;
int lastmus;

    SetMusic("silence");
    LocalAmbientSound("music/shift",127);
    Delay(35);
    if (GetCvar("norandommusic") == 0)
    {
        MusicRandomizerOn = 1;
        if (GetCvar("mus_runninginzdoom") == 1)
        {
            i = random(0, RANDOMMUS-1);
            SetMusic(RandMusList[i],0);
        }
        else
        {
            randomhack = defaultCVar("mus_cl_randomhack",   0);
            lastmus    = defaultCVar("mus_cl_lastmusic",    0) - 1;

            for (i = 0; i < randomhack; i++) { random(0, 1); }
            randomhack = random(0, 500);
            SaveCVar("mus_cl_randomhack", randomhack);

            do { i = random(0, RANDOMMUS-1); }
            while (i == lastmus);

            SetMusic(RandMusList[i], 0);
            SaveCVar("mus_cl_lastmusic", i + 1);
        }
        if (GetCvar("nomusicinfo") == 0)
        {
            MusicInfo = RandMusInfo[i];
            SetFont("SmallFont");
            hudmessage(s:MusicInfo; HUDMSG_FADEINOUT | HUDMSG_LOG, 0, CR_WHITE, 0.1, 0.8, 3.0, 0.5, 1.0);
        }
    }
    else
    {
        MusicRandomizerOn = 0;
        SetMusic("*",0);
    }
}