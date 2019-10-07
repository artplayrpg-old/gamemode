/**
 * @file        main.pwn
 * @author      Marlon "Eiss" Lorram
 * @date        24/08/2019 at 21:55:07
 * @copyright   Copyright (C) 2019 - 2021, Eiss, Inc. (https://github.com/eiskye)
 * @license     http://www.gnu.org/licenses
 * @since       Version 1.0.0
 */

#include <a_samp>

// Fix many common issues.
#define YSI_NO_HEAP_MALLOC

// Disable the startup version check.
#define _YSI_NO_VERSION_CHECK

// Redefines MAX_PLAYERS constant before usage.
#undef MAX_PLAYERS
#define MAX_PLAYERS 3

//
// Plugins
//

#include <a_mysql> // https://github.com/pBlueG/SA-MP-MySQL
#include <streamer> // https://github.com/samp-incognito/samp-streamer-plugin
#include <sscanf2> // https://github.com/maddinat0r/sscanf

//
// YSI (https://github.com/pawn-lang/YSI-Includes)
//

#include <YSI_Coding\y_inline>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_va>
#include <YSI_Server\y_colours>
#include <YSI_Visual\y_dialog>
#include <YSI_Visual\y_commands>

//
// Vendor
//

#include <noclass> // https://github.com/eiskye/samp-noclass-ysi
#include <logger> // https://github.com/Southclaws/samp-logger
#include <formatex> // https://github.com/Southclaws/formatex

//
//  Dev
//

#include "config"

#include <utils>
#include <database>
#include <commands>
#include <player>

//
// Main func
//

main() {

    print(" ");
    print(" ");
    print(" ");
    print(" ");
    print(" ");
    print("    Eiss' " SERVER_NAME);
    print("        Copyright (C) 2019 Marlon \"Eiss\" Lorram");
    print(" ");
    print(" ");
    print(" ");
    print(" ");
    print(" ");
}

/**
 * OnScriptInit
 *
 * Called when the script initiates.
 *
 * Params:
 *  This callback has no parameters.
 *
 * Return:
 *  This callback does not handle returns.
 */

public OnScriptInit() {
    print("\n\n"); // :)
    log("Initialising...");

    Bootstrap();

    return 0;
}

/**
 * Bootstrap
 *
 * Server starting point...
 * All the main functions of the server will be handled within this function.
 *
 * Params:
 *  This function has no parameters.
 *
 * Return:
 *  This function does not handle returns.
 */

static Bootstrap() {
    log("Setting up...");

    SendRconCommand("hostname " SERVER_NAME);
    SetGameModeText(SERVER_MODE " | " SERVER_VERSION);
    SendRconCommand("mapname " SERVER_MAP);
    SendRconCommand("weburl " SERVER_WEBSITE);
    SendRconCommand("password " SERVER_PASSWORD);

    Streamer_ToggleErrorCallback(true);
    DisableInteriorEnterExits();
    UsePlayerPedAnims();
    SetNameTagDrawDistance(50.0);
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
}