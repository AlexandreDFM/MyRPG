/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** my_sfalloc
*/

#include "rpg.h"

sfSoundBuffer *my_buffer_from_file(char *path)
{
    static list *garbage2 = 0;
    int nbfree = 0;
    if (!path) {
        while (garbage2) {
            list *ne = garbage2->next;
            sfSoundBuffer_destroy(garbage2->data);
            free(garbage2);
            garbage2 = ne;
            nbfree++;
        }
        my_printf(stdout, "Freed %d buffer%s automatically\n", nbfree,
        (nbfree > 1 ? "s" : ""));
        return NULL;
    } void *data = sfSoundBuffer_createFromFile(path);
    if (data) {
        list *nl = malloc(sizeof(list));
        nl->data = data; nl->next = garbage2;
        garbage2 = nl;
    } return data;
}

sfShader *my_shader_from_file(char *vertex, char *geometry, char *path)
{
    static list *garbage2 = 0; int nbfree = 0;
    if (!path) {
        while (garbage2) {
            list *ne = garbage2->next;
            sfShader_destroy(garbage2->data);
            free(garbage2); garbage2 = ne;
            nbfree++;
        }
        my_printf(stdout, "Freed %d shader automatically\n", nbfree);
        return NULL;
    }
    void *data = sfShader_createFromFile(vertex, geometry, path);
    if (data) {
        list *nl = malloc(sizeof(list));
        nl->data = data; nl->next = garbage2;
        garbage2 = nl;
    } return data;
}

sfImage *my_image_from_file(char *path)
{
    static list *garbage2 = 0;
    int nbfree = 0;
    if (!path) {
        while (garbage2) {
            list *ne = garbage2->next;
            sfImage_destroy(garbage2->data);
            free(garbage2);
            garbage2 = ne;
            nbfree++;
        }
        my_printf(stdout, "Freed %d image%s automatically\n", nbfree,
        (nbfree > 1 ? "s" : ""));
        return NULL;
    } void *data = sfImage_createFromFile(path);
    if (data) {
        list *nl = malloc(sizeof(list));
        nl->data = data; nl->next = garbage2;
        garbage2 = nl;
    } return data;
}

sfTexture *my_texture_from_image(sfImage *image, sfIntRect *r)
{
    static list *garbage2 = 0;
    int nbfree = 0;
    if (!image) {
        while (garbage2) {
            list *ne = garbage2->next;
            sfTexture_destroy(garbage2->data);
            free(garbage2);
            garbage2 = ne;
            nbfree++;
        }
        my_printf(stdout, "Freed %d texture%s automatically\n", nbfree,
        (nbfree > 1 ? "s" : ""));
        return NULL;
    } void *data = sfTexture_createFromImage(image, r);
    if (data) {
        list *nl = malloc(sizeof(list));
        nl->data = data; nl->next = garbage2;
        garbage2 = nl;
    } return data;
}

void *my_sfalloc(void *(*create)(void), void *(*destroy)(void *))
{
    static list *garbage2 = 0; int nbfree = 0;
    if (!create) {
        while (garbage2) {
            list *ne = garbage2->next;
            ((cpp_garbage *)garbage2->data)->destroy(
                ((cpp_garbage *)garbage2->data)->data);
            free(garbage2->data);
            free(garbage2);
            garbage2 = ne;
            nbfree++;
        } my_printf(stdout, "Freed %d items from CPP automatically\n", nbfree,
        (nbfree > 1 ? "s" : "")); return NULL;
    } cpp_garbage *garbage = malloc(sizeof(cpp_garbage));
    if (garbage) {
        list *nl = malloc(sizeof(list));
        garbage->create = create, garbage->destroy = destroy;
        garbage->data = garbage->create();
        nl->data = garbage, nl->next = garbage2; garbage2 = nl;
    } return garbage->data;
}
