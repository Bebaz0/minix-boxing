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

bool leaderboard_is_record(const Leaderboard *lb, int ms);
void leaderboard_add(Leaderboard *lb, LeaderboardEntry e);
int  leaderboard_save(const Leaderboard *lb, const char *path);
int  leaderboard_load(Leaderboard *lb, const char *path);

#endif /* LEADERBOARD_H */
