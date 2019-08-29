// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_bugfix
    #undef _inc_bugfix
#endif

// Custom include-guard to ensure we don't duplicate.
#if defined _bugfix_included
    #endinput
#endif
#define _bugfix_included

stock eKick(playerid) {
    defer SyncKick(playerid);
    return 1;
}

stock eBan(playerid) {
    defer SyncBan(playerid);
    return 1;
}

static timer SyncKick[100](playerid) {
    return Kick(playerid);
}

static timer SyncBan[100](playerid) {
    return Ban(playerid);
}

#if defined _ALS_Kick
    #undef Kick
#else
    #define _ALS_Kick
#endif
#define Kick eKick

#if defined _ALS_Ban
    #undef Ban
#else
    #define _ALS_Ban
#endif
#define Ban eBan
