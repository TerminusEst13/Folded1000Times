#include "zcommon.acs"
#library "RANDMUS"

#include "commonFuncs.h" // Even in making a silly music randomizer mod, I require ijon's funcs.

#define RANDOMMUS 301

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
   "Song150",

   "Song151",
   "Song152",
   "Song153",
   "Song154",
   "Song155",
   "Song156",
   "Song157",
   "Song158",
   "Song159",
   "Song160",
   "Song161",
   "Song162",
   "Song163",
   "Song164",
   "Song165",
   "Song166",
   "Song167",
   "Song168",
   "Song169",
   "Song170",
   "Song171",
   "Song172",
   "Song173",
   "Song174",
   "Song175",
   "Song176",
   "Song177",
   "Song178",
   "Song179",
   "Song180",
   "Song181",
   "Song182",
   "Song183",
   "Song184",
   "Song185",
   "Song186",
   "Song187",
   "Song188",
   "Song189",
   "Song190",
   "Song191",
   "Song192",
   "Song193",
   "Song194",
   "Song195",
   "Song196",
   "Song197",
   "Song198",
   "Song199",
   "Song200",
   "Song201",
   "Song202",
   "Song203",
   "Song204",
   "Song205",
   "Song206",
   "Song207",
   "Song208",
   "Song209",
   "Song210",
   "Song211",
   "Song212",
   "Song213",
   "Song214",
   "Song215",
   "Song216",
   "Song217",
   "Song218",
   "Song219",
   "Song220",
   "Song221",
   "Song222",
   "Song223",
   "Song224",
   "Song225",
   "Song226",
   "Song227",
   "Song228",
   "Song229",
   "Song230",
   "Song231",
   "Song232",
   "Song233",
   "Song234",
   "Song235",
   "Song236",
   "Song237",
   "Song238",
   "Song239",
   "Song240",
   "Song241",
   "Song242",
   "Song243",
   "Song244",
   "Song245",
   "Song246",
   "Song247",
   "Song248",
   "Song249",
   "Song250",

   "Song251",
   "Song252",
   "Song253",
   "Song254",
   "Song255",
   "Song256",
   "Song257",
   "Song258",
   "Song259",
   "Song260",
   "Song261",
   "Song262",
   "Song263",
   "Song264",
   "Song265",
   "Song266",
   "Song267",
   "Song268",
   "Song269",
   "Song270",
   "Song271",
   "Song272",
   "Song273",
   "Song274",
   "Song275",
   "Song276",
   "Song277",
   "Song278",
   "Song279",
   "Song280",
   "Song281",
   "Song282",
   "Song283",
   "Song284",
   "Song285",
   "Song286",
   "Song287",
   "Song288",
   "Song289",
   "Song290",
   "Song291",
   "Song292",
   "Song293",
   "Song294",
   "Song295",
   "Song296",
   "Song297",
   "Song298",
   "Song299",
   "Song300",
   "Song301"
};

int RandMusInfo[RANDOMMUS] = 
{
   "JUKEBOX_001",
   "JUKEBOX_002",
   "JUKEBOX_003",
   "JUKEBOX_004",
   "JUKEBOX_005",
   "JUKEBOX_006",
   "JUKEBOX_007",
   "JUKEBOX_008",
   "JUKEBOX_009",
   "JUKEBOX_010",
   "JUKEBOX_011",
   "JUKEBOX_012",
   "JUKEBOX_013",
   "JUKEBOX_014",
   "JUKEBOX_015",
   "JUKEBOX_016",
   "JUKEBOX_017",
   "JUKEBOX_018",
   "JUKEBOX_019",
   "JUKEBOX_020",
   "JUKEBOX_021",
   "JUKEBOX_022",
   "JUKEBOX_023",
   "JUKEBOX_024",
   "JUKEBOX_025",
   "JUKEBOX_026",
   "JUKEBOX_027",
   "JUKEBOX_028",
   "JUKEBOX_029",
   "JUKEBOX_030",
   "JUKEBOX_031",
   "JUKEBOX_032",
   "JUKEBOX_033",
   "JUKEBOX_034",
   "JUKEBOX_035",
   "JUKEBOX_036",
   "JUKEBOX_037",
   "JUKEBOX_038",
   "JUKEBOX_039",
   "JUKEBOX_040",
   "JUKEBOX_041",
   "JUKEBOX_042",
   "JUKEBOX_043",
   "JUKEBOX_044",
   "JUKEBOX_045",
   "JUKEBOX_046",
   "JUKEBOX_047",
   "JUKEBOX_048",
   "JUKEBOX_049",
   "JUKEBOX_050",
   "JUKEBOX_051",
   "JUKEBOX_052",
   "JUKEBOX_053",
   "JUKEBOX_054",
   "JUKEBOX_055",
   "JUKEBOX_056",
   "JUKEBOX_057",
   "JUKEBOX_058",
   "JUKEBOX_059",
   "JUKEBOX_060",
   "JUKEBOX_061",
   "JUKEBOX_062",
   "JUKEBOX_063",
   "JUKEBOX_064",
   "JUKEBOX_065",
   "JUKEBOX_066",
   "JUKEBOX_067",
   "JUKEBOX_068",
   "JUKEBOX_069",
   "JUKEBOX_070",
   "JUKEBOX_071",
   "JUKEBOX_072",
   "JUKEBOX_073",
   "JUKEBOX_074",
   "JUKEBOX_075",
   "JUKEBOX_076",
   "JUKEBOX_077",
   "JUKEBOX_078",
   "JUKEBOX_079",
   "JUKEBOX_080",
   "JUKEBOX_081",
   "JUKEBOX_082",
   "JUKEBOX_083",
   "JUKEBOX_084",
   "JUKEBOX_085",
   "JUKEBOX_086",
   "JUKEBOX_087",
   "JUKEBOX_088",
   "JUKEBOX_089",
   "JUKEBOX_090",
   "JUKEBOX_091",
   "JUKEBOX_092",
   "JUKEBOX_093",
   "JUKEBOX_094",
   "JUKEBOX_095",
   "JUKEBOX_096",
   "JUKEBOX_097",
   "JUKEBOX_098",
   "JUKEBOX_099",
   "JUKEBOX_100",
   "JUKEBOX_101",
   "JUKEBOX_102",
   "JUKEBOX_103",
   "JUKEBOX_104",
   "JUKEBOX_105",
   "JUKEBOX_106",
   "JUKEBOX_107",
   "JUKEBOX_108",
   "JUKEBOX_109",
   "JUKEBOX_110",
   "JUKEBOX_111",
   "JUKEBOX_112",
   "JUKEBOX_113",
   "JUKEBOX_114",
   "JUKEBOX_115",
   "JUKEBOX_116",
   "JUKEBOX_117",
   "JUKEBOX_118",
   "JUKEBOX_119",
   "JUKEBOX_120",
   "JUKEBOX_121",
   "JUKEBOX_122",
   "JUKEBOX_123",
   "JUKEBOX_124",
   "JUKEBOX_125",
   "JUKEBOX_126",
   "JUKEBOX_127",
   "JUKEBOX_128",
   "JUKEBOX_129",
   "JUKEBOX_130",
   "JUKEBOX_131",
   "JUKEBOX_132",
   "JUKEBOX_133",
   "JUKEBOX_134",
   "JUKEBOX_135",
   "JUKEBOX_136",
   "JUKEBOX_137",
   "JUKEBOX_138",
   "JUKEBOX_139",
   "JUKEBOX_140",
   "JUKEBOX_141",
   "JUKEBOX_142",
   "JUKEBOX_143",
   "JUKEBOX_144",
   "JUKEBOX_145",
   "JUKEBOX_146",
   "JUKEBOX_147",
   "JUKEBOX_148",
   "JUKEBOX_149",
   "JUKEBOX_150",

   "JUKEBOX_151",
   "JUKEBOX_152",
   "JUKEBOX_153",
   "JUKEBOX_154",
   "JUKEBOX_155",
   "JUKEBOX_156",
   "JUKEBOX_157",
   "JUKEBOX_158",
   "JUKEBOX_159",
   "JUKEBOX_160",
   "JUKEBOX_161",
   "JUKEBOX_162",
   "JUKEBOX_163",
   "JUKEBOX_164",
   "JUKEBOX_165",
   "JUKEBOX_166",
   "JUKEBOX_167",
   "JUKEBOX_168",
   "JUKEBOX_169",
   "JUKEBOX_170",
   "JUKEBOX_171",
   "JUKEBOX_172",
   "JUKEBOX_173",
   "JUKEBOX_174",
   "JUKEBOX_175",
   "JUKEBOX_176",
   "JUKEBOX_177",
   "JUKEBOX_178",
   "JUKEBOX_179",
   "JUKEBOX_180",
   "JUKEBOX_181",
   "JUKEBOX_182",
   "JUKEBOX_183",
   "JUKEBOX_184",
   "JUKEBOX_185",
   "JUKEBOX_186",
   "JUKEBOX_187",
   "JUKEBOX_188",
   "JUKEBOX_189",
   "JUKEBOX_190",
   "JUKEBOX_191",
   "JUKEBOX_192",
   "JUKEBOX_193",
   "JUKEBOX_194",
   "JUKEBOX_195",
   "JUKEBOX_196",
   "JUKEBOX_197",
   "JUKEBOX_198",
   "JUKEBOX_199",
   "JUKEBOX_200",
   "JUKEBOX_201",
   "JUKEBOX_202",
   "JUKEBOX_203",
   "JUKEBOX_204",
   "JUKEBOX_205",
   "JUKEBOX_206",
   "JUKEBOX_207",
   "JUKEBOX_208",
   "JUKEBOX_209",
   "JUKEBOX_210",
   "JUKEBOX_211",
   "JUKEBOX_212",
   "JUKEBOX_213",
   "JUKEBOX_214",
   "JUKEBOX_215",
   "JUKEBOX_216",
   "JUKEBOX_217",
   "JUKEBOX_218",
   "JUKEBOX_219",
   "JUKEBOX_220",
   "JUKEBOX_221",
   "JUKEBOX_222",
   "JUKEBOX_223",
   "JUKEBOX_224",
   "JUKEBOX_225",
   "JUKEBOX_226",
   "JUKEBOX_227",
   "JUKEBOX_228",
   "JUKEBOX_229",
   "JUKEBOX_230",
   "JUKEBOX_231",
   "JUKEBOX_232",
   "JUKEBOX_233",
   "JUKEBOX_234",
   "JUKEBOX_235",
   "JUKEBOX_236",
   "JUKEBOX_237",
   "JUKEBOX_238",
   "JUKEBOX_239",
   "JUKEBOX_240",
   "JUKEBOX_241",
   "JUKEBOX_242",
   "JUKEBOX_243",
   "JUKEBOX_244",
   "JUKEBOX_245",
   "JUKEBOX_246",
   "JUKEBOX_247",
   "JUKEBOX_248",
   "JUKEBOX_249",
   "JUKEBOX_250",

   "JUKEBOX_251",
   "JUKEBOX_252",
   "JUKEBOX_253",
   "JUKEBOX_254",
   "JUKEBOX_255",
   "JUKEBOX_256",
   "JUKEBOX_257",
   "JUKEBOX_258",
   "JUKEBOX_259",
   "JUKEBOX_260",
   "JUKEBOX_261",
   "JUKEBOX_262",
   "JUKEBOX_263",
   "JUKEBOX_264",
   "JUKEBOX_265",
   "JUKEBOX_266",
   "JUKEBOX_267",
   "JUKEBOX_268",
   "JUKEBOX_269",
   "JUKEBOX_270",
   "JUKEBOX_271",
   "JUKEBOX_272",
   "JUKEBOX_273",
   "JUKEBOX_274",
   "JUKEBOX_275",
   "JUKEBOX_276",
   "JUKEBOX_277",
   "JUKEBOX_278",
   "JUKEBOX_279",
   "JUKEBOX_280",
   "JUKEBOX_281",
   "JUKEBOX_282",
   "JUKEBOX_283",
   "JUKEBOX_284",
   "JUKEBOX_285",
   "JUKEBOX_286",
   "JUKEBOX_287",
   "JUKEBOX_288",
   "JUKEBOX_289",
   "JUKEBOX_290",
   "JUKEBOX_291",
   "JUKEBOX_292",
   "JUKEBOX_293",
   "JUKEBOX_294",
   "JUKEBOX_295",
   "JUKEBOX_296",
   "JUKEBOX_297",
   "JUKEBOX_298",
   "JUKEBOX_299",
   "JUKEBOX_300",
   "JUKEBOX_301"
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
            hudmessage(l:MusicInfo; HUDMSG_FADEINOUT | HUDMSG_LOG, 153, CR_WHITE, 0.1, 0.8, 3.0, 0.5, 1.0);
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

script 348 (int musicshit) NET clientside
{
int i;
int randomhack;
int lastmus;

switch (musicshit)
{
  case 0:
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
            hudmessage(l:MusicInfo; HUDMSG_FADEINOUT | HUDMSG_LOG, 153, CR_WHITE, 0.1, 0.8, 3.0, 0.5, 1.0);
        }
    }
    else
    {
        MusicRandomizerOn = 0;
        SetMusic("*",0);
    }
    break;

  case 1:
    SetMusic("silence");
    LocalAmbientSound("music/shift",127);
    Delay(35);
    SetMusic("*",0);
    break;
}
}

script 349 (int fuckery) NET clientside
{
  if (fuckery > 0 && fuckery < 302)
  {
    if (GetCvar("norandommusic") == 0)
    {
        fuckery--; // By default, arrays start at 0. So inserting puke 349 1 would take you to song 2.

        SetMusic("silence");
        LocalAmbientSound("music/shift",127);
        Delay(35);

        MusicRandomizerOn = 1;
        if (GetCvar("mus_runninginzdoom") == 1)
        {
            SetMusic(RandMusList[fuckery],0);
        }
        else
        {
            SetMusic(RandMusList[fuckery], 0);
        }
        if (GetCvar("nomusicinfo") == 0)
        {
            MusicInfo = RandMusInfo[fuckery];
            SetFont("SmallFont");
            hudmessage(l:MusicInfo; HUDMSG_FADEINOUT | HUDMSG_LOG, 153, CR_WHITE, 0.1, 0.8, 3.0, 0.5, 1.0);
        }
    }
    else
    {
        MusicRandomizerOn = 0;
    }
  }
  else
  {
    Log(s:"Error: Invalid song number specified.");
  }
}