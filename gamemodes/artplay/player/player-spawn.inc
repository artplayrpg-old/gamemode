/**
 * @file        player-spawn.inc
 * @author      Marlon "Eiss" Lorram
 * @copyright   Copyright (C) 2019 - 2021, Eiss, Inc. (https://github.com/eiskye)
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
 * OnPlayerDataLoaded
 *
 * Called when loading player data.
 *
 * Params:
 *  playerid - Player to load.
 *
 * Return:
 *  This callback does not handle returns.
 */

hook OnPlayerDataLoaded(playerid) {
    SetPVarInt(playerid, "spawn", 1);

    if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) {
        TogglePlayerSpectating(playerid, false);
    }

    GameTextForPlayer(playerid, "~w~Bem vindo ~n~~Y~%s", 6000, 1, Player_GetName(playerid));

    SetSpawnInfo(playerid, -1, Player_GetSkin(playerid), 1726.7014, -1687.1825, 13.5164, 178.1227, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);

    Streamer_UpdateEx(playerid, 1726.7014, -1687.1825, 13.5164);
}

/**
 * OnPlayerSpawn
 *
 * Called when a player spawns,
 * calling the hooks version of this.
 * 'OnPlayerSpawned'.
 *
 * Params:
 *  playerid - Player who spawned.
 *
 * Return:
 *  This callback does not handle returns.
 */

hook OnPlayerSpawn(playerid) {

    if(GetPVarType(playerid, "spawn")) {
        DeletePVar(playerid, "spawn");

        // Call
        call OnPlayerSpawned(playerid);
    }
}

/**
 * OnPlayerSpawned
 *
 * Called when a player spawns.
 *
 * Params:
 *  playerid - Player who spawned.
 *
 * Return:
 *  This callback does not handle returns.
 */

hook OnPlayerSpawned(playerid) {
    SetCameraBehindPlayer(playerid);
}