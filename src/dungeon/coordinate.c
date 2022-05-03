/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** coordinate
*/

#include "rpg.h"
#include "dungeon.h"

sfVector2f **get_random_position(sfIntRect **rooms, int count, char ***map)
{
    int rdm = (rand() % count);
    sfVector2i start_pos = (sfVector2i){rooms[rdm]->left + rand() %
    rooms[rdm]->width, rooms[rdm]->top + rand() % rooms[rdm]->height};
    int last = (rdm + count) >= count ? (count - rdm) : rdm + count;
    sfVector2i last_pos = (sfVector2i){rooms[last]->left + rand() %
    rooms[last]->width, rooms[last]->top + rand() % rooms[last]->height};
    sfVector2f **array = malloc(2 * sizeof(sfVector2f*));
    sfVector2f *start_posf = malloc(sizeof(sfVector2f));
    sfVector2f *last_posf = malloc(sizeof(sfVector2f));
    *start_posf = local_to_global(start_pos.x, start_pos.y);
    *last_posf = local_to_global(last_pos.x, last_pos.y);
    (*map)[start_pos.y][start_pos.x + 1] = 'F';
    array[0] = start_posf;
    array[1] = last_posf;
    return array;
}

sfVector2f local_to_global(int x, int y)
{
    return (sfVector2f){x * 24.0f + 12.0f, y * 24.0f + 12.0f};
}

sfVector2i global_to_local(sfVector2f p) {
    int a = p.x / 24.0f;
    int b = p.y / 24.0f;
    return (sfVector2i){a, b};
}

int get_current_roomlo(sfVector2i pos, map_inf *inf)
{
    for (int i = 0; inf->rooms[i]; i++) {
        sfIntRect *rect = inf->rooms[i];
        if (sfIntRect_contains(rect, pos.x, pos.y)) {
            return i;
        }
    }
    return -1;
}

int get_current_room(sfVector2f pos, map_inf *inf)
{
    sfVector2i lpos = global_to_local(pos);
    return get_current_roomlo(lpos, inf);
}

sfVector2i get_closest_exit(int r, sfVector2f t, map_inf *inf)
{
    if (r == -1) return (sfVector2i){0, 0};
    sfIntRect croom = *(inf->rooms[r]);
    float dst = MAP_SIZE * 2;
    sfVector2i lt = global_to_local(t);
    sfVector2i endp = (sfVector2i){0, 0};
    for (int y = croom.top; y < croom.top + croom.height + 1; y++) {
        for (int x = croom.left; x < croom.left + croom.width; x++) {
            if (inf->map[y][x] != 'E') continue;
            sfVector2f exi = (sfVector2f){x, y};
            float ndst = distance(exi, (sfVector2f){lt.x, lt.y});
            if (dst > ndst) {
                dst = ndst;
                endp = (sfVector2i){x, y};
            }
        }
    }
    return endp;
}
