/**
 * @file        commands-impl.inc
 * @author      Marlon "Eiss" Lorram
 * @copyright   Copyright (C) 2019 - 2021, Eiss, Inc. (https://github.com/eiskye)
 * @license     http://www.gnu.org/licenses
 * @since       Version 1.0.0
 */

#include <YSI_Coding\y_hooks>

/**
 *
 * /\   /\__ _ _ __(_) __ _| |__ | | ___ ___
 * \ \ / / _` | '__| |/ _` | '_ \| |/ _ / __|
 *  \ V | (_| | |  | | (_| | |_) | |  __\__ \
 *   \_/ \__,_|_|  |_|\__,_|_.__/|_|\___|___/
 *
 */

static PlayerCommand[MAX_PLAYERS];

/**
 *    __                 _
 *   /____   _____ _ __ | |_ ___
 *  /_\ \ \ / / _ | '_ \| __/ __|
 * //__  \ V |  __| | | | |_\__ \
 * \__/   \_/ \___|_| |_|\__|___/
 *
 *
 * OnGameModeInit
 *
 * Called when the script initiates.
 *
 * Params:
 *  This callback has no parameters.
 *
 * Return:
 *  This callback does not handle returns.
 */

hook OnGameModeInit() {
    
    // Sets the permissions for
    // all commands at once.
    Group_SetGlobalCommandDefault(false);
}

/**
 *    __                 _
 *   /____   _____ _ __ | |_ ___
 *  /_\ \ \ / / _ | '_ \| __/ __|
 * //__  \ V |  __| | | | |_\__ \
 * \__/   \_/ \___|_| |_|\__|___/
 *
 *
 * OnPlayerCommandReceived
 *
 * Called when someone sends a command.
 *
 * Params:
 *  playerid - Player that entered a command.
 *  cmdtext - The command that was entered.
 *  success - Value returned by command function returns.
 *
 * Return:
 *  The error enum value.
 */

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) {

    if(PlayerCommand[playerid] > GetTickCount()) {
        return COMMAND_DENIED;
    }

    if(success == COMMAND_OK) {
        PlayerCommand[playerid] = GetTickCount() + 1000;

        return COMMAND_OK;
    }

    return COMMAND_OK;
}