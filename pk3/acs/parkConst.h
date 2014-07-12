#define PARKMORE_BASE 354

#define PARKMORE_OPEN               (PARKMORE_BASE-1)
#define PARKMORE_ENTER              (PARKMORE_BASE-2)
#define PARKMORE_ENTER2             (PARKMORE_BASE-3)

#define PARKMORE_TURN               (PARKMORE_BASE+31)
#define PARKMORE_PITCH              (PARKMORE_BASE+32)
#define PARKMORE_SETTURN            (PARKMORE_BASE+33)
#define PARKMORE_SETPITCH           (PARKMORE_BASE+34)

#define PARKMORE_WALLBOUNCE         (PARKMORE_BASE+10)
#define PARKMORE_LEDGEWALL          (PARKMORE_BASE+11)
#define PARKMORE_LEDGEHOLD          (PARKMORE_BASE+12)
#define PARKMORE_WALLHOLD           (PARKMORE_BASE+13)
#define PARKMORE_REQUESTDODGE       (PARKMORE_BASE+14)

#define PARKMORE_HELP               (PARKMORE_BASE+20)
#define PARKMORE_TOGGLE             (PARKMORE_BASE+21)

#define PARKMORE_ASSORTED           (PARKMORE_BASE+41)

#define CLOCKWISE           0
#define COUNTERCLOCKWISE    1

#define PITCH_UP    0
#define PITCH_DOWN  1

#define WB_XYBASE   20.0
#define WB_ZBASE    1.25

#define LW_LEDGE    0
#define LW_WALL     1

#define WB_DODGE    0
#define WB_KICK     1
#define WB_KICKUP   2

#define WD_FORWARD  0
#define WD_FORWRITE 1
#define WD_RIGHT    2
#define WD_BACKRITE 3
#define WD_BACK     4
#define WD_BACKLEFT 5
#define WD_LEFT     6
#define WD_FORWLEFT 7
#define WD_KICK     8

int wallCheckers[9] =
{
    "ParkmoreCheckS",
    "ParkmoreCheckSE",
    "ParkmoreCheckE",
    "ParkmoreCheckNE",
    "ParkmoreCheckN",
    "ParkmoreCheckNW",
    "ParkmoreCheckW",
    "ParkmoreCheckSW",
    "ParkmoreCheckKick",
};

#define JUMP_FORWARD 15.0
#define JUMP_BACK    5.0
#define JUMP_SIDE    15.0

#define LUNGE_FORWARD 20.0
#define LUNGE_ZMULT   0.8

#define HIJUMP_BACK   5.0
#define HIJUMP_ZMULT  1.6

#define TIMER_COUNT     7

#define TIMER_CFORWARD   0
#define TIMER_CRIGHT     1
#define TIMER_CBACK      2
#define TIMER_CLEFT      3
#define TIMER_BOUNCED    4
#define TIMER_DIDDODGE   5
#define TIMER_HBACK      6

#define CACOUNT         15

#define HMSG_BASE       42666
#define HELPMSGCOUNT    9

int HELPTIMES[HELPMSGCOUNT] = {10, 20, 20, 20, 20, 30, 20, 20, 25};

int HELPMSGS[HELPMSGCOUNT] = {
"First off, take a look in the control menu, as there's\
\nthree keys to bind there - a ZDoom-style centerview, a\
\nsmoother turn180, and a key to disable Parkmore (if only\
\ntemporarily).",

"And what exactly do you have the ability to do? Well, if\
\nyou're familiar with Unreal Tournament 2004 to any degree,\
\nyou should already be familiar with the first move. You can\
\njump in midair (\cfmultijump\c-). By default, only once - change\
\n\caparkmore_jumpcount\c- if you want to configure this.\
\n\
\nYes, you're allowed to try this out as this goes.",

"This isn't the only thing from UT2k4. You can also \cfdodge\c-\
\naround, the same way you do there - double tap a movement\
\nkey, and you'll be sent hurtling in that direction.\
\n\cfWall-dodging\c- is in, too - it's not the only type of\
\nwall-bouncing, though. Just dodge off of a wall. It resets\
\nyour multijump counter, too.",

"You can also do traditional \cfwall jumps\c-. When you get close\
\nto the wall, press the \cdjump\c- key while 'moving' opposite to\
\nthe wall. You'll jump off, gain a horizontal and vertical\
\nboost, face the direction you jump in, and reset your\
\nmultijump counter. Find two pillars close to each other,\
\nand touch the sky.",

"As for height-gaining maneuvers, you have a couple. Should\
\nyou tap your \cdbackwards\c- movement key, and jump while still\
\nholding it, you'll do a \cfhigh jump\c-, sending yourself 2.5 times\
\nas high as normal. Also, you can \cfwall-kick\c-, sending\
\nyourself high up a wall - just jump into the wall while\
\nrunning headfirst into it.",

"And what parkour mod would be complete without\
\n\cfledge-grabbing\c-? It's automatic - as you're falling, you\
\nwill grab the first ledge that presents itself to your\
\nfingers - the faster you're falling, the higher the chance\
\nof not grabbing on.  Hoist yourself up by moving \cdforward\c-,\
\nor drop down by going \cdbackwards\c-. Moving \cdleft\c- and \cdright\c-\
\n\cfshimmies\c- you around, although expect a slingshot effect around\
\ncorners.",

"You can also grab onto walls, although you will slide down -\
\nit's not a perfect hold. Press into the direction you were\
\noriginally facing to drop, away from it to wall jump away,\
\nand hit the wall jump key to do a wall jump no matter which\
\ndirection you're looking. You slide down faster when not facing\
\naround the direction you were facing when you grabbed",

"There's a few variables you may want to look at. \caparkmore_dodgewindow\c-\
\ndefines the amount of tics you get to double-tap your dodge\
\nyour movement keys to dodge; it defaults to 8.\
\n\caparkmore_hijumpwindow\c- is similar, but for high jumping.\
\nIt defaults to 4. You cannot set these values to 0 - if you want\
\nthat, set them to a negative value. Setting them to 0 resets\
\nthem.",

"By the way, this was made in its entirety by\
\n\ccijontichy\cm@\cupowernoob\c-.  If you have any\
\nsuggestions, send them over to him through either the\
\nZandronum forums, or through \cfgztichy@lavabit.com\c-. No\
\nguarantees he'll see the email, though. He also idles on\
\n\cfirc.zandronum.com\c- - join \cd#hangman\c- and hope he's\
\nat the keyboard. Or post in the forum thread - that's where\
\nyou got this, right?"
};
