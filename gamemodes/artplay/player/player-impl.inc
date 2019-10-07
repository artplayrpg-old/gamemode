/**
 * @file        player-impl.inc
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

static ORM:PlayerORM[MAX_PLAYERS];
static PlayerID[MAX_PLAYERS];
static PlayerPasswordHash[MAX_PLAYERS][SHA256_HASH_LENGTH];
static PlayerPasswordSalt[MAX_PLAYERS][SHA256_SALT_LENGTH];
static PlayerName[MAX_PLAYERS][MAX_PLAYER_NAME];
static PlayerSkin[MAX_PLAYERS];
static PlayerMoney[MAX_PLAYERS];
static PlayerStatus[MAX_PLAYERS];

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

}

/**
 * OnPlayerConnect
 *
 * Called when a player connects to the server.
 *
 * Params:
 *  playerid - Player who connected.
 *
 * Return:
 *  This callback does not handle returns.
 */

hook OnPlayerConnect(playerid) {
    // Get a player's name.
    GetPlayerName(playerid, PlayerName[playerid], MAX_PLAYER_NAME);
}

/**
 * OnPlayerFullyConnected
 *
 * Called when a player is fully connected to the server.
 *
 * Params:
 *  playerid - Player who connected.
 *
 * Return:
 *  This callback does not handle returns.
 */

hook OnPlayerFullyConnected(playerid) {
    call OnPlayerScreen(playerid);
}

/**
 * OnPlayerDisconnect
 *
 * Called when a player disconnects from the server.
 *
 * Params:
 *  playerid - Player who disconnected.
 *  reason - The reason for the disconnection.
 *
 * Returns:
 *  This callback does not handle returns.
 */

hook OnPlayerDisconnect(playerid, reason) {
    call OnPlayerDespawn(playerid);
    call OnResetPlayerVars(playerid);
}

/**
 * OnPlayerDespawn
 *
 * Called when a player disconnects from the server.
 *
 * Params:
 *  playerid - Player who disconnected.
 *
 * Returns:
 *  This callback does not handle returns.
 */

hook OnPlayerDespawn(playerid) {
    Player_Save(playerid);

    //log("OnPlayerDespawn",
       // _i("orm_destroy", _:PlayerORM[playerid]));

    orm_destroy(PlayerORM[playerid]);
}

/**
 * OnCreatePlayerORM
 *
 * Called when a player authenticate on server.
 * Loads a player's data.
 *
 * Params:
 *  ORM:ormid - The id of the ORM instance.
 *  playerid - Player who is recieving data.
 *
 * Return:
 *  This callback does not handle returns.
 */

hook OnCreatePlayerORM(ORM:ormid, playerid) {
    orm_addvar_int(ormid, PlayerID[playerid], "id");
    orm_addvar_string(ormid, PlayerPasswordHash[playerid], SHA256_HASH_LENGTH, "password_hash");
    orm_addvar_string(ormid, PlayerPasswordSalt[playerid], SHA256_SALT_LENGTH, "password_salt");
    orm_addvar_string(ormid, PlayerName[playerid], MAX_PLAYER_NAME, "name");
    orm_addvar_int(ormid, PlayerSkin[playerid], "skin");
    orm_addvar_int(ormid, PlayerMoney[playerid], "money");
}

/**
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
    PlayerStatus[playerid] |= PLAYER_STATUS_LOGGED;
}

/**
 * OnResetPlayerVars
 *
 * Resets variables when a player disconnects.
 *
 * Params:
 *  playerid - Player who disconnected.
 *
 * Returns:
 *  This callback does not handle returns.
 */

hook OnResetPlayerVars(playerid) {
    PlayerID[playerid]                = 0;
    PlayerPasswordHash[playerid][0]   = EOS;
    PlayerPasswordSalt[playerid][0]   = EOS;
    PlayerName[playerid][0]           = EOS;
    PlayerORM[playerid]               = ORM:0;
    PlayerSkin[playerid]              = 0;
    PlayerMoney[playerid]             = 0;
    PlayerStatus[playerid]            = 0;
}

/**
 *   /\/\   ___| |_| |__   ___   __| |___
 *  /    \ / _ | __| '_ \ / _ \ / _` / __|
 * / /\/\ |  __| |_| | | | (_) | (_| \__ \
 * \/    \/\___|\__|_| |_|\___/ \__,_|___/
 *
 *
 * Player_LoadFromDatase
 *
 * Checks account and load.
 *
 * Params:
 *  playerid - Player whose data should be loaded.
 *
 * Returns:
 *  This callback does not handle returns.
 */

void:Player_LoadFromDatase(playerid) {
    new ORM:ormid = orm_create("players", Database_Get());
    PlayerORM[playerid] = ormid;

    // Call
    call OnCreatePlayerORM(_:ormid, playerid);

    // Query key
    orm_setkey(ormid, "name");

    inline const OnPlayerDataLoad() {

        switch(orm_errno(ormid)) {

            case ERROR_OK: {
                // Account found.
                // Show the login dialog box.
                Player_TryLogin(playerid);
            }

            case ERROR_NO_DATA: {
                SendClientMessage(playerid, X11_WHITE, "Você não possui uma conta nesse servidor!");
                SendClientMessage(playerid, X11_WHITE, "     Para se registrar, vá para "SERVER_WEBSITE" e clique em cadastro.");

                Kick(playerid);
            }
        }
    }

    ORM_SelectInline(ormid, using inline OnPlayerDataLoad);
}

/**
 * Player_TryLogin
 *
 * Tries to log in a player - hashes and checks their password and if it's
 * right calls the core login code.
 *
 * Params:
 *  playerid - Player who is trying to log in.
 *  attempts - Login attempts.
 *
 * Return:
 *  This callback does not handle returns.
 */

static Player_TryLogin(playerid, attempts = 0) {

    if(attempts) {
        if(attempts > MAX_LOGIN_ATTEMPTS) {
            SendClientMessage(playerid, X11_WHITE, "SERVER: Você foi kickado do servidor!");
            SendClientMessage(playerid, X11_WHITE, "     Excedeu o número máximo de tentativas de login!");

            Kick(playerid);
            return;
        }
    }

    inline const OnLoginResponse(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem

        // Did the user click cancel?
        if( !response ) {
            SendClientMessage(playerid, X11_WHITE, "SERVER: Você foi kickado do servidor!");
            SendClientMessage(playerid, X11_WHITE, "     Decidiu não efetuar o login no servidor!");

            Kick(playerid);
            return;
        }

        // Did the user not type anything?
        if(isnull(inputtext)) {
            Player_TryLogin(playerid, attempts);
            return;
        }

        // Hashes a password using the SHA-256 hashing algorithm.
        // Includes a salt. The output is always 256 bytes in length,
        // or the equivalent of 64 Pawn cells.
        SHA256_PassHash(inputtext, PlayerPasswordSalt[playerid], inputtext, SHA256_HASH_LENGTH);

        // Are the passwords the same?
        if(!strcmp(inputtext, PlayerPasswordHash[playerid])) {
            // New key field to query by player account ID.
            orm_setkey(PlayerORM[playerid], "id");

            call OnPlayerDataLoaded(playerid);

            //log("Player character has been loaded.",
                    //_i("user", PlayerID[playerid]));
            return;
        }

        new
            att;

        if( (att = (MAX_LOGIN_ATTEMPTS - attempts)) > 0 ) {
            SendClientMessage(playerid, X11_WHITE, "* Senha incorreta!");
            SendClientMessage(playerid, X11_WHITE, "     Você tem mais %d chance(s) para autenticar-se em sua conta.", att);
        }

        // Try again.
        Player_TryLogin(playerid, attempts + 1);
    }

    Dialog_ShowCallback(playerid,
        (using inline OnLoginResponse),
        DIALOG_STYLE_PASSWORD,
        "Login » " SERVER_NAME,
        "Bem-vindo ao "SERVER_NAME"\n\n \
            Por favor, digite a sua senha abaixo para autenticar-se em sua conta:",
        "Autenticar",
        "Cancelar"
    );
}

/**
 * Player_Save
 *
 * Saves the player data.
 *
 * Params:
 *  playerid - Player whose data should be saved.
 *
 * Return:
 *  This callback does not handle returns.
 */

static Player_Save(playerid) {
    if(PlayerID[playerid]) {
        orm_update(PlayerORM[playerid]);
    }
}

/**
 * Player_IsLoggedIn
 *
 * Checks if a player is logged in or not.
 *
 * Params:
 *  playerid - Player to check the login status of.
 *
 * Return:
 *  true - is logged in.
 *  false - is not logged in.
 */

stock Player_IsLoggedIn(playerid) {
    return (PlayerStatus[playerid] & PLAYER_STATUS_LOGGED);
}

/**
 * Player_GetORM
 *
 * Gets the ORM instance of the player account.
 *
 * Params:
 *  playerid - Player to get.
 *
 * Return:
 *  The id of the ORM instance.
 */

stock ORM:Player_GetORM(playerid) {
    return PlayerORM[playerid];
}

/**
 * Player_GetID
 *
 * Gets a player's unique ID.
 *
 * Params:
 *  playerid - Player to get.
 *
 * Return:
 *  The unique ID.
 */

stock Player_GetID(playerid) {
    return PlayerID[playerid];
}

/**
 * Player_GetName
 *
 * Get a player's name.
 *
 * Params:
 *  playerid - Player to get.
 *
 * Return:
 *  The player's name.
 */

Player_GetName(playerid, name[] = "", len = sizeof name) {
    format(name, len, PlayerName[playerid]);

    return PlayerName[playerid];
}

/**
 * Player_GetSkin
 *
 * Gets the skin of a player.
 *
 * Params:
 *  playerid - Player to get skin for.
 *
 * Return:
 *  Player's skin.
 */

stock Player_GetSkin(playerid) {
    return PlayerSkin[playerid];
}

/**
 * Player_SetSkin
 *
 * Sets the skin of a player.
 *
 * Params:
 *  playerid - Player to set the skin of.
 *
 * Return:
 *  This function does not handle returns.
 */

stock Player_SetSkin(playerid, skin) {
    PlayerSkin[playerid] = skin;
}