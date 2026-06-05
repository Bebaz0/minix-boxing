#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <stdint.h>
#include <stdbool.h>
#include "rtc.h"

#define LEADERBOARD_MAX_ENTRIES 9
#define LEADERBOARD_FILE        "/root/lcom_leaderboard_9.dat"
#define LEADERBOARD_NAME_LEN    16

typedef struct {
    char     name[LEADERBOARD_NAME_LEN];
    int      winner;
    int      match_duration_ms;
    rtc_date date;
} LeaderboardEntry;

typedef struct {
    LeaderboardEntry entries[LEADERBOARD_MAX_ENTRIES];
    int count;
} Leaderboard;

/**
 * @brief Checks whether a match time qualifies for the leaderboard.
 *
 * A time is a record while the board is not full, or once full when it beats the
 * slowest stored entry.
 *
 * @param lb Leaderboard to query
 * @param ms Match duration to test, in milliseconds
 * @return true if the time would enter the top entries
 */
bool leaderboard_is_record(const Leaderboard *lb, int ms);

/**
 * @brief Inserts an entry into the leaderboard, kept sorted by ascending time.
 *
 * Shifts slower entries down and drops the slowest one when the board is full.
 *
 * @param lb Leaderboard to update
 * @param e Entry to insert
 */
void leaderboard_add(Leaderboard *lb, LeaderboardEntry e);

/**
 * @brief Writes the leaderboard to a file.
 *
 * @param lb Leaderboard to save
 * @param path Destination file path
 * @return 0 on success, -1 if the file could not be opened
 */
int  leaderboard_save(const Leaderboard *lb, const char *path);

/**
 * @brief Loads the leaderboard from a file.
 *
 * A missing file is treated as an empty leaderboard. The loaded count is clamped
 * and names are null-terminated defensively.
 *
 * @param lb Leaderboard to fill
 * @param path Source file path
 * @return 0 always (a missing file yields an empty, valid leaderboard)
 */
int  leaderboard_load(Leaderboard *lb, const char *path);

#endif /* LEADERBOARD_H */
