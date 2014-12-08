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

// Definitions

#define TRAILCOUNT 3
#define QUOTECOUNT 100
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
#define WEEB_DEC_TOASTER      98
#define WEEB_DEC_TOASTER2     99

#define WEEB_DEC_GETMESSAGES    0
#define WEEB_DEC_CHANGEMUS      1
#define WEEB_DEC_CHANGEMUSBACK  2

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
"FROM 0.73 TO 0.74:\n\
=======================================\n\
- The Archvile's flame turrets now have A_NoBlocking in their death state.\n\
- All of the Archvile's death states now call A_KillChildren.\n\
- The Archvile's flame turrets now are no longer considered monsters and won't spam up the monster count or block things in Invasion.\n\
- There are three more 'fade from black' sounds, thanks to torridGristle's rip of Eternal Darkness and thanks to MAGIX Soundpool DVDs.\n\
- The Exodus grenades now explode on the sky, rather than simply vanish.\n\
- The Icon of Sin now has its own custom sounds.\n\
- Hae-Lin's landing sound is now less crackly.\n\
- Pickups are now no longer considered monsters and will no longer bork things up in survival invasion.\n\
- The initial swing of the Kharon's sheathe can now be refired one tic faster. Whoo.\n\
- The Wolfenstein SS now has a replacement.\n\
- Decorations now have a slightly higher chance to spew out items.\n\
- In lieu of the Kamehameha, the Exodus no longer needs to go through walls. The explosion is now simply a 256-radius explosive, rather than four explosives with 192 radius.\n\
- The Kharon by itself now has idle animations. Oops.\n\
- Transformation has been streamlined and no longer requires 'hold fire'--just hit Use Inventory and it'll activate.\n\
- Online, people were occaisionally getting weapon desynchs, where they were in Iron Maiden but using the Kharon. This has been fixed.\n\
- A new idle animation has been implemented.\n\
- Hammering the ground will now allow Hae-Lin to jump higher, because reasons. The higher the charge, the higher the jump.\n\
- The Iron Maiden's armor will become more effective depending on your rank--at S Rank, you can no-sell practically everything.\n\
- The not-Kamehameha now takes a little over 1.5x as much soul energy but now each explosion does 128 damage instead of 96.\n\
- There are no longer double decals for the bullet weapons.\n\
- The switch-hitting no-damage bulletpuff no longer splashes on liquids.\n\
- The Invulnerability Sphere and RadSuit now have their own respective appropriate replacements.\n\
- The sound range on the not-Kamehameha has been tripled.\n\
- Enemies killed with the not-Kamehameha are now no longer resurrectable.\n\
- Meleeing enemies in pitch dark is a pain in the ass. For users who play with lower visibility settings and/or on dark maps, a flashlight has been provided. At the moment, it's an optional customizable key, but in the future (when Zandronum supports it) then it'll use the Reload key.\n\
- The Omen and Iron Maiden are more responsive online and now has multiple checks for if the player has hit something with it. This should polish up all inconsistencies in hitting and should also reduce the amount of times people hit something and then get stuck in place.\n\
- The Sentinel and the Blind Guardian can now be carried from level to level.\n\
- The Infrared Visor has been replaced with a Sentinel pickup as well, which should make it slightly more common than just the allmap.\n\
- The Archvile has +MISSILEEVENMORE removed.\n\
- The Blackened's children now have a different appearance, to prevent confusion with Lost Souls.\n\
- Lost Souls now drop souls when killed.\n\
- The Blackened now has a sound when summoning its children, to prevent confusion of when a child is attacking or being summoned.\n\
- Quakes no longer cause sounds.\n\
- All enemies now have their own custom sound set. Whew! That was a lot of work.\n\
- A few people's ears had trouble with the Kharon's sheathe, so the sheathing sound effect has been slightly softened, its pitch lowered, and its bass reduced.\n\
- There is now an options menu for handling cvars and DemonSteele-specific settings, in ZDoom.\n\
- New teleport effect. Neat!\n\
- Hae-Lin now has lines for the not-Kamehameha. I can't think of a name for it, so neither can she.\n\
- Hae-Lin now has lines for picking up food.\n\
- In the chance a player picks up a new weapon DemonSteele doesn't replace, the ammo HUD will now show the ammo for it.\n\
- ZDoom stealth monsters are now supported. Due to the gameplay style of DemonSteele, the monsters no longer flicker in and out of visibility, but are now a constant and flat 0.4 visibility.\n\
- People tended to lose track of exactly how much health they had and would die accidentally. In true retro game style, now there is a beeping warning when low on health. This can be disabled with 'ds_cl_nobeeping'.\n\
- Skulltag items and monsters now have a proper replacement. Skulltag monsters occaisionally recieve strange colors when killed, but for now this is a great step forward.\n\
- Some people wanted to be able to taunt in ZDoom. Weird. There is now a ZDoom-specific key for doing the Zandronum taunt in ZDoom.\n\
- The Blind Guardian will no longer trigger the Sentinel and send it into a Tumblr fit. In the off chance it does, the Sentinel will check its privilege and reassert itself.\n\
- The Kharon's attacks no longer pass harmlessly through ghosts.\n\
- The Keen now has a unique replacement.\n\
- The techlamps are now destructable items, like the torches, and will now provide item drops.\n\
- Techlamps and torches now have their original gldef lights back.\n\
- A new cvar has been implemented to handle Skulltag weapon replacements--ds_arrogantweapons. 0 spawns the normal weapons, 1 spawns new for-fun weapons in place of Skulltag weapons, and 2 spawns the new weapons randomly in place of the original weapons.\n\
- Holding down fire for over a second will now prepare a launching uppercut slash. (Most) enemies launched with this will be suspended in mid-air until they hit the ground--shooting them will keep them in mid-air.\n\
- There are now intermission text replacements for vanilla levels.";

int CookieQuote[QUOTECOUNT] = 
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
"Life sucks, wear a bikini and show off.",
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
"Look behind you.",
"Orange you glad this isn't a Soulsphere?",
"You can make your own happiness. In a meth lab.",
"Face facts with dignity and also a sword and a plethora of heaven-blessed firearms.",
"Adversity is the parent of virtue. Insisting on UV-ing Hell Revealed is the parent of stupidity.",
"Sometimes the best part of the journey is not the destination, but laying waste to the Cyberdemon waiting at the destination.",
"SEND HELP! I'M TRAPPED IN A GAMEPLAY MOD FACTORY!",
"Let your deeds speak for themselves. Your flashy special combo moves can do the bragging.",
"You will always be surrounded by your true friends. Yes, the guys shooting at you. They're your friends now.",
"Phew! About goddamn time I got out of that cookie.",
"Whatever you do, don't order the chicken.",
"You will take a pleasant journey to a place far away, just as soon as you can find the secret exit.",
"You believe in the goodness of mankind... but you have an internet connection?!",
"You will live long and enjoy life. Unless you get shot by demons. But what are the odds of that?",
"Someday, you'll look back on this and laugh nervously before changing the topic.",
"Just wait until you get home.",
"Your skeleton lurks inside of you, waiting patiently.",
"Seven days.",
"I know what you did last summer.",
"Caleb is never going to be added to Samsara.",
"Love will lead the way. So will IDDT.",
"Look to La Luna!",
"Buy Major Stryker.",
"Seeing is believing, unless your sanity stat is 0.",
"You'll get your own sprite set someday.",
"The best is yet to come. Unless you cheated and got the best from the start, in which case, welp.",
"Protip: To kill the Cyberdemon, stab it until it dies.",
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
"In the time it took for DemonSteele to start, enter alpha/beta, get a full weaponset, tons of new sprites, a full quote roster, and be released, Space Pirate still has not updated.",
"I should not be spending thirty goddamn minutes thinking up one single message.",
"How is eating fried chicken like being in Hell? Thigh flesh consumed.",
"This is just like one of my Korean manhwas!"
};