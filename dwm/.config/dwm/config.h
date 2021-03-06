/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
/* static const char *fonts[]          = { "DejaVu Sans Mono for Powerline:size=14", "Noto Sans CJK SC:size=14" }; */
static const char *fonts[]          = { "Lucida Grande:style=Regular:size=14", "Noto Sans Mono CJK SC:size=14" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
/* default terminal */
static const char TERM[]        = "alacritty";

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] = {
	"bash", "/home/zhanhao/.scripts/autostart.sh", NULL,
	/* "bash", "/home/zhanhao/.scripts/fcitx-deamon.sh", NULL, */
	"dwmblocks", NULL,
	NULL /* terminate */
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = {TERM, "--class", "spterm", "-t", "spterm", "-e", "/home/zhanhao/.scripts/tmuxinit", NULL };
const char *spcmd2[] = {NULL };
const char *spcmd3[] = {TERM, "--class", "spexit", "-t", "spexit", "-e", "/home/zhanhao/.scripts/power.sh", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"spexit",   spcmd3},
};

/* tagging */
static const char *tags[] = { "", "", "", "4", "5", "6", "7", "8", "" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",	  NULL,			NULL,		0,				1,			 -1 },
	{ "Google-chrome",  NULL,			NULL,		1,			0,			 -1 },
	{ "jetbrains-idea",  NULL,			NULL,		0b100,			0,			 -1 },
	{ "code",  NULL,			NULL,		0b100,			0,			 -1 },
	{ "netease-cloud-music",  NULL,			NULL,		0b100000000,			0,			 -1 },
	{ NULL,		  "spterm",		NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spfm",		NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "spexit",	NULL,		SPTAG(2),		1,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define XF86XK_VolumeUp			0x1008ff13
#define XF86XK_VolumeDown		0x1008ff11
#define XF86XK_VolumeMute		0x1008ff12
#define XF86XK_BackLightInc		0x1008ff02
#define XF86XK_BackLightDec		0x1008ff03

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "combi", "-modi", "combi", "-lines", "3", "-eh", "1", "-width", "100", "-padding", "800", "-opacity","85"};
static const char *termcmd[]  = { "alacritty", "-e", "tmux" };
static const char *open_chrome[]  = { "google-chrome-stable", NULL };
static const char *toggle_trayer[]  = {"bash", "/home/zhanhao/.scripts/trayer.sh", NULL };
static const char *volume_up[]  = { "lmc", "up", "5", "dwmblocks" };
static const char *volume_down[]  = { "lmc", "down", "5", "dwmblocks" };
static const char *volume_mute[]  = { "lmc", "mute", "", "dwmblocks" };
static const char *back_light_inc[]  = { "xbacklight", "-inc", "20" };
static const char *back_light_dec[]  = { "xbacklight", "-dec", "20" };
static const char *audio_play[]  = { "playerctl", "play-pause" };
static const char *audio_next[]  = { "playerctl", "next" };
static const char *audio_prev[]  = { "playerctl", "previous" };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = open_chrome } },
	{ MODKEY|ControlMask,           XK_t,      spawn,          {.v = toggle_trayer } },
	{ False,                       XF86XK_VolumeUp, spawn,          {.v = volume_up } },
	{ False,                       XF86XK_VolumeDown, spawn,          {.v = volume_down } },
	{ False,                       XF86XK_VolumeMute, spawn,          {.v = volume_mute } },
	{ False,                       XF86XK_BackLightInc, spawn,          {.v = back_light_inc } },
	{ False,                       XF86XK_BackLightDec, spawn,          {.v = back_light_dec } },
	/* { MODKEY,                       XF86XK_AudioPlay, spawn,          {.v = audio_play } }, */
	/* { MODKEY,                       XF86XK_AudioNext, spawn,          {.v = audio_next } }, */
	/* { MODKEY,                       XF86XK_AudioPrev, spawn,          {.v = audio_prev } }, */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,            			XK_u,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_y,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,            	XK_e,	   togglescratch,  {.ui = 2 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
