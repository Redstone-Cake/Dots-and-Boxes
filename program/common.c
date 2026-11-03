#include <stdbool.h>

typedef struct {
    int x;
    int y;
} ivec2;

bool check_move(ivec2 p1, ivec2 p2) {
    int total_dist = abs(p1.x - p2.x) + abs(p1.y - p2.y);
    return total_dist == 1;
}