/**
 * @file        player-screen.inc
 * @author      Marlon "Eiss" Lorram
 * @copyright   Copyright (c) 2019 - 2021, Eiss, Inc. (https://github.com/eiskye)
 * @license     http://www.gnu.org/licenses
 * @since       Version 1.0.0
 */

#include <YSI_Coding\y_hooks>

/**
 *    __                 _
 *   /____   _____ _ __ | |_ ___
 *  /_\ \ \ / / _ | '_ \| __/ __|
 * //__  \ V |  __| | | | |_\__ \
 * \__/   \_/ \___|_| |_|\__|___/
 *
 *
 * OnPlayerScreen
 *
 * Called when a player is fully connected to the server,
 * showying the login screen for the player.
 *
 * Params:
 *  playerid - Player who connected.
 *
 * Return:
 *  This callback does not handle returns.
 */

hook OnPlayerScreen(playerid) {
    // Fetch player's data, it will display dialogs
    // to the player and eventually, once the process has completed, the event
    // `OnPlayerDataLoaded` is called.
    Player_LoadFromDatase(playerid);

    // Call our login screen.
    defer SyncScreenLogin(playerid);
}

/**
 *  _____ _
 * /__   (_)_ __ ___   ___ _ __ ___
 *   / /\| | '_ ` _ \ / _ | '__/ __|
 *  / /  | | | | | | |  __| |  \__ \
 *  \/   |_|_| |_| |_|\___|_|  |___/
 *
 *
 * SyncScreenLogin
 *
 * Timer to move a player's camera.
 *
 * Params:
 *  playerid - Player to show.
 *
 * Return:
 *  This function does not handle returns.
 */

timer SyncScreenLogin[300](playerid) {
    InterpolateCameraPos(playerid, 1326.426269, -818.895751, 79.194717, 6.976511, -2162.627197, 122.978126, 120000, CAMERA_MOVE);
    return InterpolateCameraLookAt(playerid, 1323.296020, -822.777343, 78.827857, 10.913708, -2159.674072, 122.096046, 120000, CAMERA_MOVE);
}