// Hook all functions that sends text to players.
// Note that all function have the support for formatted messages.

#if !defined MAX_TEXT_LENGTH
    #define MAX_TEXT_LENGTH     (2048)
#endif

static
    TextBuffer[MAX_TEXT_LENGTH];

/**
 * SendClientMessageToAll
 * ---------------------------------------------- */
stock SendClientMessageToAllEx(colour, const fmat[], ...) {

    if(numargs() > 2) {
        foreach(new i : Player) {
            format(TextBuffer, sizeof TextBuffer, fmat, ___(2));

            SendClientMessage(i, colour, TextBuffer);
        }

    } else {
        foreach(new i : Player) {
            SendClientMessage(i, colour, fmat);
        }
    }

    return 1;
}

#if defined _ALS_SendClientMessageToAll
        #undef SendClientMessageToAll
#else
        #define _ALS_SendClientMessageToAll
#endif
#define SendClientMessageToAll SendClientMessageToAllEx

/**
 * SendClientMessage
 * ---------------------------------------------- */
stock SendClientMessageEx(playerid, colour, const fmat[], ...) {

    if(numargs() > 3) {
        format(TextBuffer, sizeof TextBuffer, fmat, ___(3));

        return SendClientMessage(playerid, colour, TextBuffer);

    }

    return SendClientMessage(playerid, colour, fmat);
}

#if defined _ALS_SendClientMessage
        #undef SendClientMessage
#else
        #define _ALS_SendClientMessage
#endif
#define SendClientMessage SendClientMessageEx

/**
 * GameTextForPlayer
 * ---------------------------------------------- */
stock GameTextForPlayerEx(playerid, const fmat[], time, style, {Float, _}:...) {

    if(numargs() > 4) {
        format(TextBuffer, sizeof TextBuffer, fmat, ___(4));

        return GameTextForPlayer(playerid, TextBuffer, time, style);

    }

    return GameTextForPlayer(playerid, fmat, time, style);
}

#if defined _ALS_GameTextForPlayer
    #undef GameTextForPlayer
#else
    #define _ALS_GameTextForPlayer
#endif
#define GameTextForPlayer GameTextForPlayerEx

/**
 * TextDrawSetString
 * ---------------------------------------------- */
stock TextDrawSetStringEx(Text:text, const fmat[], {Float, _}:...) {

    if(numargs() > 2) {
        format(TextBuffer, sizeof TextBuffer, fmat, ___(2));

        return TextDrawSetString(text, gs_Buffer);

    }

    return TextDrawSetString(text, fmat);
}

#if defined _ALS_TextDrawSetString
    #undef TextDrawSetString
#else
    #define _ALS_TextDrawSetString
#endif
#define TextDrawSetString TextDrawSetStringEx

/**
 * PlayerTextDrawSetString
 * ---------------------------------------------- */
stock PlayerTextDrawSetStringEx(playerid, PlayerText:text, const fmat[], {Float, _}:...) {

    if(numargs() > 3) {
        format(TextBuffer, sizeof TextBuffer, fmat, ___(3));

        return PlayerTextDrawSetString(playerid, text, TextBuffer);

    }

    return PlayerTextDrawSetString(playerid, text, fmat);
}

#if defined _ALS_PlayerTextDrawSetString
    #undef PlayerTextDrawSetString
#else
    #define _ALS_PlayerTextDrawSetString
#endif
#define PlayerTextDrawSetString PlayerTextDrawSetStringEx