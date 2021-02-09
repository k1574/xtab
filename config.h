/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "Consolas:pixelsize=14:antialias=true:autohint=true";
static const char* normbgcolor  = "#ffffff";
static const char* normfgcolor  = "#000000";
static const char* selbgcolor   = "#000000";
static const char* selfgcolor   = "#ffffff";
static const char* urgbgcolor   = "#111111";
static const char* urgfgcolor   = "#000000";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 0;
static Bool npisrelative  = False;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/env", "rc", "-c", \
                "prop=`{ xlsw $2" \
                		"| xmen -w $2 -p '>' -l 10" \
				"| awk '{print $1}' }" \
                 "&& xprp $2 $1 $prop", \
                p, winid, NULL \
        } \
}

#define MODKEY Mod1Mask
static Key keys[] = {
	/* Modifier, key, function, argument. */
	{ MODKEY, XK_t, focusonce, { 0 } }, /* This focuses you on the spawned command. */
	{ MODKEY, XK_t , spawn, { 0 } }, /* Spawn the command which you started with. */

	{ MODKEY, XK_Tab,    rotate,      { .i = 0 } }, /* Toggle between two last tabs. */
	{ MODKEY, XK_k, rotate, {.i = +1}}, /* Moving current focus on next/previous tab. */
	{ MODKEY, XK_j, rotate, {.i = -1}},
	{ MODKEY|ShiftMask, XK_j, movetab, { .i = +1 } }, /* Moving tab through other tabs (back/forward). */
	{ MODKEY|ShiftMask, XK_k, movetab, { .i = -1 } },

	{ MODKEY,               XK_grave,  spawn,       SETPROP("_TABBED_SELECT_TAB") }, /* Choose the tab by list. */
	/* Choose tab by num on keyboard. */
	{ MODKEY,               XK_1,      move,        { .i = 0 } },
	{ MODKEY,               XK_2,      move,        { .i = 1 } },
	{ MODKEY,               XK_3,      move,        { .i = 2 } },
	{ MODKEY,               XK_4,      move,        { .i = 3 } },
	{ MODKEY,               XK_5,      move,        { .i = 4 } },
	{ MODKEY,               XK_6,      move,        { .i = 5 } },
	{ MODKEY,               XK_7,      move,        { .i = 6 } },
	{ MODKEY,               XK_8,      move,        { .i = 7 } },
	{ MODKEY,               XK_9,      move,        { .i = 8 } },
	{ MODKEY,               XK_0,      move,        { .i = 9 } },

	{ MODKEY,               XK_x,      killclient,  { 0 } }, /* Close one tab and kill the client in it. */

	{ MODKEY,               XK_u,      focusurgent, { 0 } },
	{ MODKEY|ShiftMask,     XK_u,      toggle,      { .v = (void*) &urgentswitch } },

	{ 0,                    XK_F11,    fullscreen,  { 0 } }, /* Fullscreen. */
} ;
