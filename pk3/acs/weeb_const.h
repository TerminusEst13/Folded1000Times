// Script names

#define WEEB_RESPAWN                         266
#define WEEB_DECORATE                        267
#define WEEB_ENTER                           268
#define WEEB_DOUBLETAP                       269
#define WEEB_ENTERDOUBLETAP                  270
#define WEEB_TAPSPECIFY                      271
#define WEEB_COMBOREMOVAL                    272
#define WEEB_UNLOADING                       273
#define WEEB_OPEN                            274
#define WEEB_CLIENTDECORATE                  275
#define WEEB_DEATH                           276
#define WEEB_OPEN_CLIENT                     277
#define WEEB_ENTER_CLIENT                    278
#define WEEB_PUKE                            279
#define WEEB_CREDITS                         280

// Definitions

#define IRONMUS 7

#define WB_DODGE         0
#define WD_FORWARD       0
#define WD_FORWRITE      1
#define WD_RIGHT         2
#define WD_BACKRITE      3
#define WD_BACK          4
#define WD_BACKLEFT      5
#define WD_LEFT          6
#define WD_FORWLEFT      7
#define WD_KICK          8

#define TIMER_COUNT      7

#define TIMER_CFORWARD   0
#define TIMER_CRIGHT     1
#define TIMER_CBACK      2
#define TIMER_CLEFT      3
#define TIMER_BOUNCED    4
#define TIMER_DIDDODGE   5
#define TIMER_HBACK      6

#define WEEB_DEC_DAMAGE       0
#define WEEB_DEC_FREEZE       1
#define WEEB_DEC_UNFREEZE     2
#define WEEB_DEC_SHOTCHECK    3
#define WEEB_DEC_CARRCHECK    4
#define WEEB_DEC_UZICHECK     5
//#define WEEB_DEC_ICANTREMEMBERANDIDONTCARE     6
#define WEEB_DEC_MEGASPHERE   7
#define WEEB_DEC_WEPSTAY      8
#define WEEB_DEC_HAMCHECK     9
#define WEEB_DEC_HAMAMMO1     10
#define WEEB_DEC_HAMAMMO2     11
#define WEEB_DEC_HAMAMMO3     12
#define WEEB_DEC_FREEZE2      13
#define WEEB_DEC_UNFREEZE2    14
#define WEEB_DEC_REMOVEKEBAB  15
#define WEEB_DEC_DIFFCHECK    16
#define WEEB_DEC_ONLINECHECK  17
#define WEEB_DEC_HENSHIN      18

#define WEEB_DEC_GETMESSAGES    0
#define WEEB_DEC_CHANGEMUS      1
#define WEEB_DEC_CHANGEMUSBACK  2

int DemonCredits =
"SPECIAL THANKS TO:\n\
=========\n\
- Special thanks to Combine_Kegan and Shiga95, who respectively made GMOTA and Swan Fox, both of which were big inspirations for this.\n\
- Special thanks to Flying Wild Hog and MAIET Entertainment, respectively for Shadow Warrior 2013 and GunZ, both also big inspirations for this.\n\
- Special thanks to Mike12 for his incredible patience in dealing with my stubborn push of ideas and my flighty attention span, as well as his jaw-droppingly astounding artistic work.\n\
- Special thanks to Doom667Shogun for allowing me to use Doom Radys assets for kickstarting DemonSteele with, letting me have a headstart on everything.\n\
\n\
GRAPHICS:\n\
=========\n\
- Numerous artists for custom deaths (All sorted in folders according to the artist)\n\
  ^ Mike12\n\
  ^ DrDoctor\n\
  ^ David G\n\
  ^ Vader\n\
  ^ Eriance\n\
  ^ Minigunner\n\
  ^ Funktasm\n\
  ^ Neoworm\n\
  ^ ojsclatchford\n\
  ^ Sgt. Shivers\n\
- Mike12\n\
  ^ Numerous custom deaths (as mentioned)\n\
  ^ The gore decals/graphics\n\
  ^ The custom blood for the Kharon\n\
  ^ The Acacia A-22 hunting pistol\n\
  ^ The Kharon\n\
  ^ The polished Marathon shotgun for the Testament\n\
- Sgt. Shivers\n\
  ^ All of the idle animations\n\
  ^ The henshin animation\n\
  ^ Animating the Exodus\n\
- Absolutely no thanks to Rottsprite for shitting out on us and not letting us rotate the Kharon properly forcing us to rely on Photoshop's really ugly and jagged-y rotate function NO I'M NOT BITTER AT ALL WHAT GIVES YOU THAT IDEA\n\
- Captain J/Cortlong50 (The base of the Sabbath, dramatically rehauled by Mike12)\n\
- Captain J (The Sabbath large ammo pack)\n\
- Bloax (The broken bone sprites)\n\
- DonaldDuck (The Priest's sprites)\n\
- Shadow Warrior (The Exodus grenade sprites)\n\
- Aeons of Death (The Exodus explosion graphics)\n\
- Ettingrinder (The Candelabra)\n\
- NeuralStunner (The Omen's pickup sprite)\n\
- Rogue Software (All the lightning effects and the keycard bases, from Strife)\n\
- Raven Software\n\
  ^ The skull keys edited from Hexen\n\
  ^ The Steel Beast edited from the Heretic Sabreclaw\n\
  ^ The Wizard edited from the Hexen Bishop\n\
  ^ The Blackened edited from the Hexen Reiver\n\
  ^ The Priest edited from Hexen's Parias and the Heretic Iron Lich\n\
  ^ The Priest/Imp's fire effects nicked from Hexen\n\
- Id Software (The laser shots from the zombies, some electricity sprites for Omen)\n\
- Ravage/rf' (The red/blue/green torches)\n\
- KeksDose (The miniature explosions and particles used for the bullet puffs)\n\
- CastleVania: Dawn of Sorrow/Order of Ecclesia/Portrait of Ruin (Bits and pieces of the HUD)\n\
- CastleVania: Symphony of the Night (The skull used for the main menu selector)\n\
- Chrono Trigger (Bits and pieces of the HUD)\n\
- Dark Kingdom (Yup, HUD bits)\n\
- Final Fantasy 6 (The fire used to represent health)\n\
- Dungeons n' Dragons (Font used for the HUD)\n\
- HellCattX (The base for the Exodus/Acacia A-22 ammo pickups)\n\
- amv2k9 (The base for the Testament ammo pickups)\n\
- Eriance/JoeyTD (The base for the placeholder hands used for the Kharon)\n\
- Eriance\n\
  ^ Custom deaths (As mentioned)\n\
  ^ The explosion used for the Steel Beast death\n\
  ^ The balls used for the Wizard spell\n\
  ^ The skull head used for the souls\n\
- Tormentor667/Z86 (The pretty effects for the Imp/Hell Noble balls, taken from UTNT/Particle Fire Enhancer)\n\
- Jimmy91 (The fonts used, Gargoyle Wing for BIGFONT and Apostacy for SMALLFONT)\n\
- Brothers of Metal (Font used for the main menu options)\n\
- Blood (The graphics for the Black Soul)\n\
- Diavolo no Daibouken (The base for the bag of holding)\n\
- Caddilacs & Dinosaurs (One of the apples and one of the burgers)\n\
- Arx (One of the apples)\n\
- Final Fight (One of the burgers)\n\
- Knights of the Round (One of the Apples)\n\
\n\
CODE:\n\
=========\n\
- Ijon Tichy\n\
  ^ The double-tap code (taken from Parkmore)\n\
  ^ The shockwave from the spin attack\n\
  ^ The trail for the zombie lasers/razor wind\n\
  ^ The second level spatter for the Omen\n\
- Doom667Shogun (For the blood/dismembering effects)\n\
- Vaecrius (For the redone Archvile (taken from Make It Snappy))\n\
- Kyle873 (Polishing the post-damage invulnerability code, rehauling the double-jump code)\n\
- MagSigmaX (Inspiration for the dodging code)\n\
- Lioyd_Irving/le_L (The basis for the Omen's impact code)\n\
- Scroton (The 3rd level spatter for the Omen)\n\
- PillowBlaster (The overcharge shockwaves for the Omen)\n\
- Xaser/Enjay/Corwin (The TERRAIN lump from Psychic)\n\
- Tormentor667/Ghastly_Dragon (The Powerline spawners for the armor, from the Stronghold Powerpad)\n\
- PresidentPeople (Fixing the corpses to keep them from bouncing everywhere)\n\
- IvanDobrovski (Fixing the eternally-looping imp blood fountain)\n\
- Xaser/Tormentor667/Z86 (The explosive barrel, nicked from the Particle Fire Enhancer Mod)\n\
- TiberiumSoul (The code for the bulletpuffs based off of his neat little effects)\n\
\n\
MUSIC:\n\
=========\n\
- Cryptomnesia (Titlescreen: Live Like a God, Die Like a God - Free to download off Soundcloud)\n\
- Megadeth (Intermission: Kick the Chair - Released as a free download in 2004)\n\
- SlayeR (Read Me: Chaos Abounds - Free to download)\n\
- Finntroll (Final1: Haterop - Released as a free download in 2005)\n\
- Yasuharu Takanashi (Final2: Power Up, Akanbe! - Released as a promotional CD to Precure anime)\n\
- Bolt Thrower (Iron Maiden Song 1: Cenotaph - Cover downloaded from ModArchive)\n\
- Ravenlord (Iron Maiden Song 2: Erased Fantasy - Downloaded from ModArchive)\n\
- Unknown (Iron Maiden Song 3: Grey Void - Downloaded from ModArchive)\n\
- SlayeR (Iron Maiden Song 4: Come In My Pants - Downloaded from slayer.mancubus.net\n\
        ^ Iron Maiden Song 5: Get In2 It - Downloaded from slayer.mancubus.net\n\
        ^ Iron Maiden Song 6: Running Blood - Downloaded from slayer.mancubus.net\n\
        ^ Iron Maiden Song 7: Uncontrollable Dancing Fury - Downloaded from slayer.mancubus.net)\n\
\n\
SOUNDS:\n\
=========\n\
- All sounds are credited to their respective owner in SNDINFO.";