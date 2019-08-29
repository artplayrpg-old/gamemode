/**
 * @file        player-hooks.inc
 * @author      Marlon "Eiss" Lorram
 * @copyright   Copyright (C) 2019 - 2021, Eiss, Inc. (https://github.com/eiskye)
 * @license     http://www.gnu.org/licenses
 * @since       Version 1.0.0
 */

// OnPlayerScreen(playerid)
#define ALS_DO_PlayerScreen<%0> %0<PlayerScreen, i>(end:playerid)

// OnPlayerDespawn(playerid)
#define ALS_DO_PlayerDespawn<%0> %0<PlayerDespawn,i>(end:playerid)

// OnResetPlayerVars(playerid)
#define ALS_DO_ResetPlayerVars<%0> %0<ResetPlayerVars,i>(end:playerid)

// OnPlayerSpawned(playerid)
#define ALS_DO_PlayerSpawned<%0> %0<PlayerSpawned,i>(end:playerid)

// OnPlayerDataLoaded(playerid)
#define ALS_DO_PlayerDataLoaded<%0> %0<PlayerDataLoaded,i>(end:playerid)

// OnCreatePlayerORM(ORM:ormid, playerid)
#define ALS_DO_CreatePlayerORM<%0> %0<CreatePlayerORM,ii>(ORM:ormid, end:playerid)