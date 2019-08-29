/**
 * @file        database.inc
 * @author      Marlon "Eiss" Lorram
 * @copyright   Copyright (c) 2019 - 2021, Eiss, Inc. (https://github.com/eiskye)
 * @license     http://www.gnu.org/licenses
 * @since       Version 1.0.0
 */

#include <YSI_Coding\y_hooks>
#include <env>

/**
 *
 * /\   /\__ _ _ __(_) __ _| |__ | | ___ ___
 * \ \ / / _` | '__| |/ _` | '_ \| |/ _ / __|
 *  \ V | (_| | |  | | (_| | |_) | |  __\__ \
 *   \_/ \__,_|_|  |_|\__,_|_.__/|_|\___|___/
 *
 */

static stock
    MySQL:MySQLHandler;

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
    Database_TryConnect();

    return Y_HOOKS_CONTINUE_RETURN_1;
}

/**
 * OnGameModeExit
 *
 * Called when the script ends
 * closing the MySQL connection.
 *
 * Params:
 *  This callback has no parameters.
 *
 * Return:
 *  This callback does not handle returns.
 */

hook OnGameModeExit() {
    mysql_close(MySQLHandler);

    return Y_HOOKS_CONTINUE_RETURN_1;
}

/**
 *   /\/\   ___| |_| |__   ___   __| |___
 *  /    \ / _ | __| '_ \ / _ \ / _` / __|
 * / /\/\ |  __| |_| | | | (_) | (_| \__ \
 * \/    \/\___|\__|_| |_|\___/ \__,_|___/
 *
 *
 * Database_TryConnect
 *
 * Try connects to a MySQL server and database.
 *
 * Params:
 *  This function has no parameters.
 *
 * Return:
 *  This function does not handle returns.
 */

static Database_TryConnect() {

    new
        MYSQL_HOST[64],
        MYSQL_USER[64],
        MYSQL_PASSWORD[64],
        MYSQL_DATABASE[64];

    if(GetEnv("MYSQL_HOST", MYSQL_HOST) == 0) {
        format(MYSQL_HOST, sizeof MYSQL_HOST, "localhost");
    }

    if(GetEnv("MYSQL_USER", MYSQL_USER) == 0) {
        format(MYSQL_USER, sizeof MYSQL_USER, "root");
    }

    if(GetEnv("MYSQL_PASSWORD", MYSQL_PASSWORD) == 0) {
        format(MYSQL_PASSWORD, sizeof MYSQL_PASSWORD, "secret");
    }

    if(GetEnv("MYSQL_DATABASE", MYSQL_DATABASE) == 0) {
        format(MYSQL_DATABASE, sizeof MYSQL_DATABASE, "artplay");
    }

    MySQLHandler = mysql_connect(
        MYSQL_HOST,
        MYSQL_USER,
        MYSQL_PASSWORD,
        MYSQL_DATABASE
    );

    if(MySQLHandler == MYSQL_INVALID_HANDLE) {
        err("Could not connect to database.");

        // stop here
        // :(
        return;
    }

    log("Successfully connected to database.");
    return;
}

/**
 * MySQL:Database_Get
 *
 * Gets the connection handle.
 *
 * Params:
 *  This function has no parameters.
 *
 * Return
 *  Connection handle.
 */

MySQL:Database_Get() {
    return MySQLHandler;
}