/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

static const int midtitle            = 0;

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const unsigned int systrayiconsize = 16; /* systray icon size in px */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */

static const unsigned int baralpha    = 0xc0;
static const unsigned int borderalpha = OPAQUE;

static const char *fonts[] =
  {"Firacode:fontformat=truetype:size=11:antialias=true:weight=bold",
   "Weather Icons:size=12:style=Regular:weight=bold",
   "ZenOwl Awesome:size=12",
  };
static const char dmenufont[]       = "Firacode:size=10";
static char normbgcolor[]           = "#282828";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#fbf1c7";
static char selfgcolor[]            = "#fabd2f";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#fabd2f";
static char *colors[][3] = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  normbgcolor,  selbordercolor  },
};

static const unsigned int alphas[][3]      = {
  /*               fg      bg        border     */
  [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
  [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class        instance        title           tags mask     iscentered   isfloating   monitor      float x,y,w,h         floatborderpx*/
  { "Gimp",         NULL,           NULL,           0,            0,             0,             -1,          50,50,500,500,        0 },
  { NULL,           NULL,           "dragon",       0,            1,             0,             -1,          0,0,500,500,          0 },
  { NULL,           "floatingwin",  NULL,           0,            1,             1,             -1,          0,0,625,450,          0 },
  { NULL,           "transmission", NULL,           0,            1,             1,             -1,          0,0,800,400,          0 },
  { "Pavucontrol",  NULL,           NULL,           0,            1,             1,             -1,          0,0,550,700,          0 },
  { "Cadence",      NULL,           NULL,           0,            1,             1,             -1,          0,0,663,526,          0 },
  { NULL,           "album",        NULL,           0,            1,             1,             -1,          -310,-90,202,202,     0 },
  { NULL,           "cavaviz",      NULL,           0,            1,             1,             -1,          -310,100,200,150,     0 },
  { NULL,           "ncmpcppwin",   NULL,           0,            1,             1,             -1,          105,0,625,400,        0 },
  { NULL,           "fzf",          NULL,           0,            1,             1,             -1,          0,0,725,200,          0 },
};

/* layout(s) */
static const float mfact     = 0.7; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "vanitygaps.c"

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",    tile },         /* Default: Master on left, slaves on right */
  { "TTT",    bstack },       /* Master on top, slaves on bottom */

  { "[@]",    spiral },       /* Fibonacci spiral */
  { "[\\]",   dwindle },      /* Decreasing in size right and leftward */

  { "H[]",    deck },         /* Master on left, slaves in monocle-like mode on right */
  { "[M]",    monocle },      /* All windows on top of eachother */

  { "|M|",    centeredmaster },       /* Master in middle, slaves on sides */
  { ">M>",    centeredfloatingmaster },   /* Same but master floats */

  { "><>",    NULL },         /* no layout function means floating behavior */
  { NULL,     NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG)                                                \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
      static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] = {
  /* modifier                     key        function        argument */

  /* Classic shit */
  { MODKEY,                       XK_space,   zoom,           {0} },
  { MODKEY|ControlMask,           XK_space,   focusmaster,     {0} },
  { MODKEY,                       XK_Tab,     view,           {0} },
  { MODKEY,                       XK_f,       togglefullscr,  {0} },
  { MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
  { MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },

  { MODKEY,                       XK_i,       incnmaster,     {.i = +1 } },
  { MODKEY|ShiftMask,             XK_i,       incnmaster,     {.i = -1 } },
  { MODKEY|ControlMask|AltMask,   XK_b,       togglebar,      {0} },
  { MODKEY,                       XK_a,       killclient,     {0} },
  { MODKEY|ShiftMask,             XK_q,       quit,           {0} },

  { MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },
  { MODKEY,                       XK_s,       togglesticky,   {0} },

  /* TAGS */
  TAGKEYS(                        XK_ampersand,                   0)
  TAGKEYS(                        XK_eacute,                      1)
  TAGKEYS(                        XK_quotedbl,                    2)
  TAGKEYS(                        XK_quoteright,                  3)
  TAGKEYS(                        XK_parenleft,                   4)
  TAGKEYS(                        XK_section,                     5)
  TAGKEYS(                        XK_egrave,                      6)
  TAGKEYS(                        XK_exclam,                      7)
  TAGKEYS(                        XK_ccedilla,                    8)

  /* LAYOUTS */
  { MODKEY,                   XK_comma,       setlayout,  {.v = &layouts[0]} }, /* tile */
  { MODKEY|ControlMask,       XK_comma,       setlayout,  {.v = &layouts[1]} }, /* bstack */
  { MODKEY,                   XK_semicolon,   setlayout,  {.v = &layouts[2]} }, /* spiral */
  { MODKEY|ControlMask,       XK_semicolon,   setlayout,  {.v = &layouts[3]} }, /* dwindle */
  { MODKEY,                   XK_colon,       setlayout,  {.v = &layouts[4]} }, /* deck */
  { MODKEY|ControlMask,       XK_colon,       setlayout,  {.v = &layouts[5]} }, /* monocle */
  { MODKEY,                   XK_equal,       setlayout,  {.v = &layouts[6]} }, /* centeredmaster */
  { MODKEY|ControlMask,       XK_equal,       setlayout,  {.v = &layouts[7]} }, /* centeredfloatingmaster */

  /* SPAWN COMMAND */
  /* { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, */
  /* { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } }, */

  /* SCRATCHPAD */
  { MODKEY,                       XK_parenright,  togglescratch,  {.v = scratchpadcmd } },

  /* GAPS */
  { MODKEY|AltMask,                   XK_parenright,  togglegaps,     {0} },
  { MODKEY|AltMask|ShiftMask,         XK_parenright,  defaultgaps,    {0} },
  { MODKEY,               XK_minus,       incrgaps,       {.i = +2 } },
  { MODKEY|ControlMask,           XK_minus,       incrgaps,       {.i = -2 } },
  { MODKEY,               XK_dollar,      incrogaps,      {.i = +2 } },
  { MODKEY|ControlMask,       XK_dollar,      incrogaps,      {.i = -2 } },
  { MODKEY,                   XK_mu,          incrigaps,      {.i = +2 } },
  { MODKEY|ControlMask,           XK_mu,          incrigaps,      {.i = -2 } },
  /* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
  /* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
  /* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
  /* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
  /* { MODKEY|AltMask,               XK_y,      incrohgaps,     {.i = +1 } }, */
  /* { MODKEY|AltMask,               XK_o,      incrohgaps,     {.i = -1 } }, */
  /* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
  /* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */

  { MODKEY,                       XK_agrave, view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_agrave, tag,            {.ui = ~0 } },
  { MODKEY,                       XK_Left,    focusmon,   {.i = -1 } },
  { MODKEY|ShiftMask,             XK_Left,    tagmon,     {.i = -1 } },
  { MODKEY,                       XK_Right,   focusmon,   {.i = +1 } },
  { MODKEY|ShiftMask,             XK_Right,   tagmon,     {.i = +1 } },

  { MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
