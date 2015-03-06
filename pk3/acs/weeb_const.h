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
#define WEEB_PUKE2                           281
#define WEEB_FROST_XYZ                       282
#define WEEB_FROST_BURST                     283
#define WEEB_FROST_TRAIL                     284
#define WEEB_FROST_COORDSHIT                 285
#define WEEB_JOY_FORW                        286
#define WEEB_JOY_LEFT                        287
#define WEEB_JOY_RITE                        288
#define WEEB_JOY_BACK                        289
#define WEEB_JOY_LOOP                        290

// Definitions

#define TRAILCOUNT 3
#define QUOTECOUNT 141
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
#define WEEB_DEC_ARMRCHECK    19
#define WEEB_DEC_BARRELSPAWN  20
#define WEEB_DEC_LEGIONCHECK  21
#define WEEB_DEC_STWEAPCHECK  22
#define WEEB_DEC_FROSTCHECK   23
#define WEEB_DEC_COOKIEQUOTE  24
#define WEEB_DEC_SLOWDOWN     25
#define WEEB_DEC_GUNSOULS     26
#define WEEB_DEC_LEGSPECIAL   27
#define WEEB_DEC_DOOMHEALTH   28

#define WEEB_DEC_GETMESSAGES    0
#define WEEB_DEC_CHANGEMUS      1
#define WEEB_DEC_CHANGEMUSBACK  2
#define WEEB_DEC_TOASTER        98
#define WEEB_DEC_TOASTER2       99

int DemonCredits =
"SPECIAL THANKS TO:\n\
=========\n\
- Special thanks to Combine_Kegan and Shiga95, who respectively made GMOTA and\n\
  Swan Fox, both of which were big inspirations for this.\n\
- Special thanks to Flying Wild Hog and MAIET Entertainment, respectively for\n\
  Shadow Warrior 2013 and GunZ, both also big inspirations for this.\n\
- Special thanks to Mike12 for his incredible patience in dealing with my\n\
  stubborn push of ideas and my flighty attention span, as well as his jaw-\n\
  droppingly astounding artistic work.\n\
- Special thanks to Sgt. Shivers for his numerous, numerous contributions to\n\
  animation, idea-polishing, and custom graphics, as well as his insane amount\n\
  of patience in dealing with my extreme forgetfulness and absent-minded-ness.\n\
- Special thanks to Doom667Shogun for allowing me to use Doom Radys assets for\n\
  kickstarting DemonSteele with, letting me have a headstart on everything.\n\
- /vr/, as always, for being an incredible source of support and ideas.\n\
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
  ^ Xim\n\
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
  ^ The pillow for the dakimakura\n\
  ^ The Frosthammer cryo railgun\n\
- Absolutely no thanks to Rottsprite for shitting out on us and not letting us\n\
  rotate the Kharon properly forcing us to rely on Photoshop's really ugly and\n\
  jagged-y rotate function NO I'M NOT BITTER AT ALL WHAT GIVES YOU THAT IDEA\n\
- Shiga95/Angel_Neko-X (The Swan Fox image used for the dakimakura)\n\
- Captain J/Cortlong50 (The base of the Sabbath, dramatically rehauled by Mike12)\n\
- Captain J (The Sabbath large ammo pack)\n\
- Bloax (The broken bone sprites)\n\
- DonaldDuck (The Priest's sprites)\n\
- Shadow Warrior (The Exodus grenade sprites, the Yakuza enemy sprites)\n\
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
- Grand Knights History (The Blind Guardian shield)\n\
- PresidentPeople (Fixing the Blind Guardian's rotations so it had a proper front sprite)\n\
- MartyKirra (The very sexy sprites for the Omen)\n\
- Scuba Steve/Mike12/torridGristle (The sheathe for the Kharon, heavily edited from Action Doom 2)\n\
- The Guided Fate Paradox (The halo for the Majestic Vanguard)\n\
- SoloSpaghetti (The Boots of Protection, modified from the Doom Roguelike Arsenal boots)\n\
\n\
CODE:\n\
=========\n\
- Scroton\n\
  ^ Pretty much the entirety of ds_cl_toaster\n\
  ^ Optimizing a lot of rough spots\n\
  ^ Rehauling the destructable decorations to throw their items at the players\n\
- Ijon Tichy\n\
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
- Zael (For the Ultima Cannon, which I shamelessly ripped off for the not-Kamehameha. May your mass never go inert)\n\
- amv2k9 (The launching system, adapted from his old Devil May Cry mod)\n\
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
- Adoxographist ( adoxtalks.tumblr.com - Going above and beyond the line of duty for Hae-Lin's voice!)\n\
- John Archer (The Blackened's voice)\n\
- torridGristle (The robotic voice of the Iron Maiden)\n\
- Combine_Kegan (Ripping and gathering all of the Sentinel's sound bytes)\n\
- All sounds are credited to their respective owner in SNDINFO.";


int DemonChangelog =
"FROM 0.74 TO 0.75:\n\
=======================================\n\
- Players are now able to rocketjump with the shotgun because reasons.\n\
- The accuracy of the Testament has been tightened up dramatically, from 12 to 6. No weapon should be competing with the Kharon for close-range.\n\
- Some players had sensitive ears that were hurt by the low health beeping. It's been replaced with a more standard heartbeat.\n\
- Explosions assisting with jumping no longer cause blood splatters.\n\
- The charge-up rate for the Legion has gone from 35 tics to 25.\n\
- The weapon decorate files have been re-organized and renamed.\n\
- Barrels no longer have a SpawnStimpack error and now, well, spawn stimpacks properly.\n\
- Thanks to ShiftyAxel, there is now an option to be able to acquire souls from gun kills. ds_gunsouls will make the souls come to you on gun death as well.\n\
- Kharon's launcher attack is now easier to do, no longer throws you forward, and is quicker to recover from.\n\
- The Blind Guardian and Sentinel can no longer be telefragged.\n\
- Exodus can no longer cause infighting on enemies.\n\
- The 'ghost barrel' bug has (hopefully) been fixed.\n\
- Exodus' explosive damage has been reduced from 192 to 160.\n\
- Chaingunners and Hell Knights no longer die multiple times on one death.\n\
- Hell Knights no longer suddenly switch directions when they collapse over.\n\
- Mancubi second shots no longer fire inwards.\n\
- Thanks to ShiftyAxel, there is now an option for typical Doom-style health play--ds_doomhealth will replace the token-based health system with a traditional health system.\n\
- Dying or exiting a level with over 100% Hammer charge should no longer cause wonkiness.\n\
- Respawning no longer triggers one-liners. Like, for real this time.\n\
- The Blind Guardian, Sentinel, and Majestic Vanguard are now considered 'big'/'super' powerups and require sv_respawnsuper to respawn.\n\
- TechPillars now have a destructable replacement.\n\
- All decorations now force Y billboarding.\n\
- The smoke off of bulletpuffs is now a little bit smaller and a little bit more transparent.\n\
- The Exodus now takes four tics longer to fire.\n\
- The first damage half of the Exodus' explosions now force gibbing.\n\
- Fortune Cookies now give an over-life token instead of a life token, and now are always picked up no matter what.\n\
- Hell Noble decapitations are now properly sized.\n\
- The Sentinel now checks multiple times to see if its target is a Blind Guardian.\n\
- More Fortune Cookie quotes, because everyone likes those.\n\
- There were a few frames where the Kharon by itself mid-raise couldn't be used. This has been fixed.\n\
- It is now possible to 'dash' down in mid-air, for the sake of more air control or lower-gravity maps. As like the usual dashing, hold Run and then hit Crouch.\n\
- The Iron Maiden's holy rockets now force extreme death, as does the punchsplosion.\n\
- A new cvar has been included, ds_2brutal, for those who want to be pursued by skeletons.\n\
- As the uppercut was not a vital move to include, but with an extremely clunky execution, it has been moved over to Optional Keys, for people to trigger at will.\n\
- The uppercut can now be triggered at more areas--instead of just being held, now it can be done while at rest, after firing, or while holding.\n\
- Destructable objects can now be triggered by the uppercut.\n\
- Lost Souls are now slightly smaller graphically because reasons. Their hitbox remains the same.\n\
- ds_omenstart and ds_backpackstart have been implemented for maps that don't have chainsaw or backpack spawns, or those who simply want a boost in starting ability.\n\
- The Sentinel no longer triggers the Baron of Hell's retreat.\n\
- It's now possible to swap away from the sheathe's attack much faster.\n\
- There are now unique talking and connecting sounds.\n\
- The Black Souls that the Blackened shoots out are now -Solid. In exchange, he now has the ability to drain the soul meter from players when they get in range.\n\
- The Omen's inventory-based flashing no longer appears in the invbar.\n\
- The Kharon's uppercut, when used on projectiles, now reflects the shots back to the enemy. It's finnicky and based on Doom 'physics', but it's neat nonetheless.\n\
- Fortune cookie quotes no longer overlap each other.\n\
- Looping bloodspray enemy deaths now have a PPSSSHHHHHHHHHHHHHHHHHHHHHHHHHHHHH sound effect, using old stock anime sound effects.\n\
- In ZDoom and GZDoom, Read This! now appears no matter whether the game is Doom 1 or Doom 2. It also appears at the top, to emphasize that, yeah, you should read this. Maybe now people will stop asking how to do special attacks!\n\
- The skull icon for the main menu looks 666% edgier and more \m/ hardkore \m/.\n\
- The combo meter no longer stays the same shade of blue as it increases, but instead inches over to purple, pink, and more for the sake of visual distinction.\n\
- A new cvar has been added, ds_nodamagepenalty, that does not penalize one's combo meter when damaged. This setting is for superbad casuals.\n\
- 17 more intro taunts have been added. Chance of saying them has been increased from one-in-four to one-in-three.\n\
- The Skulltag wizards should no longer drop Claw Orbs or Tomes of Power.\n\
- The Iron Maiden's shot impacts are no longer tinged a blue-purple.\n\
- The Iron Maiden's holy rocket now travels twice as fast and does 32 more damage.\n\
- Additive translucency is handled in-sprite now for a whole ton of effects, reducing filesize and reducing lag, as well as making them look better in Software.\n\
- DemonSteele scripts now terminate if the player is not actually playing as Hae-Lin.\n\
- On average of every twelve shots, the Sentinel will need to cycle its guns for 22 tics, allowing enemies a chance to retaliate.\n\
- The Sentinel's shot accuracy has been tightened up.\n\
- All special attacks now have A_ClearRefire at the end, for smoother transitioning between special attacks and attacking right after.\n\
- The damage of the forward special has been decreased by 8 per explosion. The radius of the side specials have been increased by 64 units.\n\
- When wielding the Kharon by itself, special attacks now end with a dramatic re-sheathing. Enemies killed with these will not die until the player re-sheathes.\n\
- The armor bar, while in Iron Maiden, has been more cleanly integrated with the HUD.\n\
- The three-digit ammo counters are now properly aligned with the edges of the ammo box.\n\
- The Legion and Frosthammer now have ammo displays.\n\
- All numbered Decorate ACS calls have been named for convenience.\n\
- Thanks to Horrormovieguy, the launch sequence for the Nobles no longer looks so...off.\n\
- Skulltag armor/health bonuses and red armor should be replaced properly now.\n\
- The Sabbath no longer spits out an Idle4 error.\n\
- A new idle animation has been implemented, made by Sgt. Shivers.\n\
- Implemented a new cvar, ds_runmod, which modifies the percentage of the speed the player runs at. 100 is the default, 100% normal speed.\n\
- The main menu font has been tweaked for cleanliness and rephrasing.\n\
- As there are no Cacodemons in DemonSteele, the Dead Cacodemon decoration has bween replaced with a pile of skulls.\n\
- The Soul Prison now gives 100 souls, instead of matching the pepper's 50.\n\
- The Archvile now has a new death sequence, courtesy of Mike12.\n\
- The Mancubi and Baron of Hell now have a new death sequence, courtesy of Sgt. Shivers.\n\
- The Priest now has a unique kubiuti death sequence, courtesy of Sgt. Shivers.\n\
- Freezing Mancs now triggers A_BossDeath.\n\
- Thanks to jpalomo's code, DemonSteele's special moves and dodging now can support joystick and touchscreen movements!\n\
- Transforming into the Iron Maiden from the Omen and untransforming meant the Omen's ammo would not degrade until it was selected. This has been fixed.\n\
- Punching the Lost Souls while in Iron Maiden now gives souls.\n\
- A points system has now been implemented, for that extra arcade-y feel.\n\
- Thanks to Sgt. Shivers, the Iron Maiden's HUD sprites are now significantly better!\n\
- The MidCombat counter has had its limit increased by 1.5x, allowing for a slightly longer lull before the meters start going down.\n\
- The Iron Maiden's holy rocket is now slightly faster to charge up.\n\
- The Over-Life token cap on Facing Hell is now two, instead of three.\n\
- Much like life, the armor cap now decreases as difficulty rises. On Facing Hell and Killing Machine, max armor tokens is now three. On Angel of Death, max armor tokens is now two.\n\
- The Frosthammer's charged explosive damage is now 160.\n\
- The KubiutiUpper damagetype now properly launches the Steele Beast.\n\
- Iron Maiden's punches, on splattering enemies, now alerts nearby monsters.\n\
- The Iron Maiden's armor has been tweaked slightly. It regenerates slightly faster, but the armor resistance itself is slower--this should make it better for out-and-out brawls, but more susceptible to burst damage.";

int CookieQuote[QUOTECOUNT] = // Thanks to Kinsie, ObviousIssues, and Hostile V for helping me with these!
{
"If you want to blow someone's mind, consider hollow-point .45s.",
"Consider the horse. No, seriously. Weird damn animals.",
"Don't fry bacon in the nude.",
"The world may be your oyster, but you'll probably never get its pearl. Sorry.",
"When life gives you lemons, that means you have more than one lemon. It's plural, you see. It's an X+1 amount of lemons. It was probably a gift.",
"When you squeeze an orange, orange juice comes out. Because that's what's inside. Duh.",
"I don't know. Ask your mom.",
"Great misfortune will befall you. Blame it on lag.",
"Constant grinding can turn an iron rod into a needle, or you might just be dry-humping.",
"Shit happens when you party naked.",
"You are not illiterate.",
"What the fuck did you just fucking say about me, you little bitch?",
"You should kill all business associates.",
"Roses are red, violets are blue, I was written in black ink.",
"Life is like a car that won't slow down. Them's the brakes.",
"A good bullet is like an easy copier. Hitscan.",
"Fortune cookies aren't actually Chinese. They're a take on the Japanese 'o-mikuji senbei', a sweet cracker with a little slip of paper tucked in. Japanese-American immigrants in the 19th century sold them to Chinese restaurants.",
"Only listen to the fortune cookie. We are your friends. Everyone else lies to you.",
"Never give up. Unless defeat arouses that one girl in accounting.",
"Some fortune cookies contain no fortune.",
"Today is a huge improvement over yesterday. Probably.",
"You will recieve a fortune sometime in your future.",
"You will be hungry again in one hour.",
"You're probably thinking, 'Geeze, I could write better fortunes than that', right? Well, screw you, I have like a hundred to write.",
"I have become circus2.wad, destroyer of servers.",
"Is it wrong to fap to your ex?",
"Life sucks, unless you wear a bikini and show off.",
"It's a shame to see someone like you boarding the jelly train.",
"Your opinions are fucking shit and they are also wrong.",
"A lot of people say money doesn't lead to happiness, but I haven't seen them give their money away.",
"It takes only a word to turn away wrath. For best results, try screaming it in anger.",
"It takes many nails to build a crib, but only one screw to fill it.",
"Confuscius say: Think for your own damn self.",
"Do not despise the racketeer. Instead, despise his sport.",
"The only acceptable place to take cover is behind a wall of bullets.",
"Reloading is just foreplay for your gun.",
"Taking credit for other people's work is the cool way to get ahead.",
"They call it a bloodbath but you really can't clean anything with it.",
"Opening up people is like finding secret doors. Approach casually and UNF until it works.",
"Cut a demon in half? Whoa there, tough guy. Better put that on your resume.",
"Words left unspoken lead to regret and self doubt. Try posting angrily about it online.",
"Your erotic attack is successful. Roll 6d9s.",
"Why was six afraid of seven? It wasn't. They're symbols representing established numerical values. They don't feel fear.",
"What's brown and sticky? A stick.",
"OH NO DON'T LOOK I'M NAKED",
"I'd say red is your color, but in Korea red is the color of masculinity.",
"This is my sword, this is my gun. One is for killing, the other is for...well, also for killing, I guess.",
"You don't need a parachute to skydive. You need a parachute to skydive twice.",
"You will be attacked by demons.",
"No one ever died of a broken heart. But a sword shoved straight into it? Not gonna lie. That's killed a couple people.",
"It's not drowning, it's just putting breathing on Hard Mode.",
"If you're hungry, eat it. If it's cute, fuck it. If it's a problem, whip it.",
"Chicks dig swole pythons. Feed your pet snakes way too much!",
"You not Lo Wang. You No Wang.",
"When Navi speaks, use (^) to listen well to her words of wisdom...",
"Call Apogee, say Aardwolf.",
"You can make your own happiness. In a meth lab.",
"Face facts with dignity and also a sword and a plethora of heaven-blessed firearms.",
"Adversity is the parent of virtue. Insisting on UV-ing Hell Revealed is the parent of stupidity.",
"Sometimes the best part of the journey is not the destination, but laying waste to the Cyberdemon waiting at the destination.",
"Watashi no hobakurafuto wa unagi de ippai desu.",
"Let your deeds speak for themselves. Your flashy special combo moves can do the bragging.",
"You will always be surrounded by your true friends. Yes, the guys shooting at you. They're your friends now.",
"Phew! About goddamn time I got out of that cookie.",
"IT'S A SECRET TO EVERYBODY.",
"You will take a pleasant journey to a place far away, just as soon as you can find the secret exit.",
"You believe in the goodness of mankind... but you have an internet connection?!",
"You will live long and enjoy life. Unless you get shot by demons. But what are the odds of that?",
"Someday, you'll look back on this and laugh nervously before changing the topic.",
"Mama-say mama-sah ma-ma-coo-sah.",
"Your skeleton lurks inside of you, waiting patiently.",
"Seven days.",
"I know what you did last summer.",
"Caleb is never going to be added to Samsara.",
"Strifeguy is never going to be added to Samsara.",
"Love will lead the way. So will IDDT.",
"Look to La Luna!",
"Buy Major Stryker.",
"Seeing is believing, unless your SAN stat is 0.",
"You'll get your own sprite set someday.",
"The best is yet to come. Unless you cheated and got the best from the start, in which case, welp.",
"Protip: To defeat the Cyberdemon, stab it until it dies.",
"Believe in yourself. The rest of us think you're an idiot.",
"Pain may be weakness leaving the body, but you've got so much to give.",
"Fighting for peace may be an oxymoron, but it's more fun than the alternative.",
"A wise man once said, it is not enough to settle for mediocrity. You must git gud, scrub.",
"404: Fortune not found. Try again later.",
"I refuse to do anything productive today.",
"Axes take skill.",
"Everything's more fun when you're drunk.",
"Study finds OP still sucking cock on a regular basis.",
"99 glitches in the code on the wall, 99 glitches in the code. Take one down, patch it around, 142 glitches in the code on the wall.",
"Justice fears no skelly!",
"When tempted to fight fire with fire, remember that the Fire Department usually uses water.",
"If what you don't know can't hurt you, you're invulnerable.",
"Patience and a kind word can take care of most situations, but so can a bullet.",
"One of these days, the enemies will learn how to respawn. Then we'll all be fucked.",
"In the time it took for DemonSteele to start, enter alpha/beta, get a full weaponset, tons of new sprites, a full quote roster, be released, and win a Cacoward, Space Pirate still has not updated.",
"I should not be spending thirty goddamn minutes thinking up one single message.",
"How is eating fried chicken like being in Hell? Thigh flesh consumed.",
"This is just like one of my Korean manhwas!",
"At some point, you will be the next person on Earth to die.",
"Wow, your browser history is kind of weird.",
"Today's forecast: Not fucking going outside.",
"What do you do with an epileptic lettuce? Make a seizure salad.",
"Never trust an acupuncturist. They're back-stabbers.",
"system error 0xfded",
"If you think food has all the answers, you must be fat as hell.",
"Senpai noticed me!",
"I want to be inside you but nobody ever eats the paper. ;_;",
"I'd ask you to be gentle with me but you seem to have already snapped me in half.",
"I'm in Comic Sans and you can't do shit about it.",
"Excuse me, do you have a moment free to talk about our lord and savior, Jesus Christ?",
"I sure hope I'm not supposed to be guarding the Spear of Destiny right now.",
"I bet the UAC did this.",
"Does this run with Brutal Doom?",
"I'm surprised you can read this, what with the firing and shooting and running around at 50 MPH.",
"Mom can't make you clean your room.",
"Did you know that you can drink lava? Only once, though.",
"Go to Heaven for the men, but go to Hell for the women.",
"Dongs take skill.",
"Let me tell you why Satan is a myth and the demons are actually aliens.",
"I identify as angelkin and your powers are oppressing me you shitlord prime. #actuallydivine",
"Why bother with original content when you can just quote a meme and have an epic win?",
"John Who? John Woo.",
"Install your GPU drivers.",
"You think I have it rough? Wait until you see my friend, the New Year's Party Popper.",
"Did you know that dumb upside down is qnwp?",
"A person dies every 11 seconds. How many people have died since you started?",
"I've never seen a Kano transformation.",
"Beware of he who would deny you access to information, for in his heart he dreams himself your master.",
"I'd say it's a good day to die, but next Sunday might be good too.",
"Control the media, control the mind.",
"You're not the boss of me!",
"There's absolutely no illuminati watching you right now.",
"Protip: To kill the Cyberdemon, stab it until it dies.",
"play some punch out with these nerds and beat them 2 the punch",
"How exactly do you refine toxins?",
"HOW DOE'S IT FEEL TO BE WELL DONE? BUT I BET YOU TASTE TERRIBLE.",
"Boy, this mod would be so much better if it had its own dedicated mapset.",
"What's the speed of dark?"
};