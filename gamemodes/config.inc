/**
 * @file        config.inc
 * @author      Marlon "Eiss" Lorram
 * @copyright   Copyright (C) 2019 - 2021, Eiss, Inc. (https://github.com/eiskye)
 * @license     http://www.gnu.org/licenses
 * @since       Version 1.0.0
 */

#define NONE                (-1)

//
// Config
//

#define SERVER_NAME         "ArtPlayRPG"
#define SERVER_MODE         "RPG"
#define SERVER_MAP          "San Andreas"
#define SERVER_VERSION      "v0.0.1 (0.3.7)"
#define SERVER_WEBSITE      "www.artrpg-samp.dev"
#define SERVER_PASSWORD     "0"

/**
 * Dynamic functions.
 *
 * Example:
 *   function OnPlayerLogin(playerid) { }
 */

#define function%1(%2)      forward%1(%2); public%1(%2)