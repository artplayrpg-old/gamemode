/**
 * @file        player-def.inc
 * @author      Marlon "Eiss" Lorram
 * @copyright   Copyright (C) 2019 - 2021, Eiss, Inc. (https://github.com/eiskye)
 * @license     http://www.gnu.org/licenses
 * @since       Version 1.0.0
 */

#define MAX_LOGIN_ATTEMPTS      (2)
#define SHA256_HASH_LENGTH      (65)
#define SHA256_SALT_LENGTH      (17)

//
// Bitwise values definitions for player flags.
//

#define PLAYER_STATUS_LOGGED    (1 << 0)

//
// Declarations
//

forward ORM:Player_GetORM(playerid);