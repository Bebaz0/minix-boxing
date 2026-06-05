#include "leaderboard.h"
#include <string.h>
#include <stdio.h>

bool leaderboard_is_record(const Leaderboard *lb, int ms) {
    if (lb->count < LEADERBOARD_MAX_ENTRIES)
        return true;
    return ms < lb->entries[lb->count - 1].match_duration_ms;
}

void leaderboard_add(Leaderboard *lb, LeaderboardEntry e) {
    int pos = lb->count < LEADERBOARD_MAX_ENTRIES ? lb->count : LEADERBOARD_MAX_ENTRIES - 1;

    for (int i = 0; i < lb->count && i < LEADERBOARD_MAX_ENTRIES; i++) {
        if (e.match_duration_ms < lb->entries[i].match_duration_ms) {
            pos = i;
            break;
        }
    }

    int end = lb->count < LEADERBOARD_MAX_ENTRIES ? lb->count : LEADERBOARD_MAX_ENTRIES - 1;
    for (int i = end; i > pos; i--)
        lb->entries[i] = lb->entries[i - 1];

    lb->entries[pos] = e;
    if (lb->count < LEADERBOARD_MAX_ENTRIES)
        lb->count++;
}

int leaderboard_save(const Leaderboard *lb, const char *path) {
    FILE *f = fopen(path, "wb");
    if (f == NULL)
        return -1;
    fwrite(lb, sizeof(*lb), 1, f);
    fclose(f);
    return 0;
}

int leaderboard_load(Leaderboard *lb, const char *path) {
    memset(lb, 0, sizeof(*lb));
    FILE *f = fopen(path, "rb");
    if (f == NULL)
        return 0;
    fread(lb, sizeof(*lb), 1, f);
    fclose(f);
    return 0;
}
