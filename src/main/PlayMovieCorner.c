#include "wof.h"

void PlayMovieCorner(s32 movie, s32 event) {
    PlayMovie(movie, event, 0x19, 0x14);
}
