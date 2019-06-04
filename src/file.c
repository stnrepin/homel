#include "file.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "app-error.h"
#include "utils.h"

TagPath *TagPath_new() {
    TagPath *tp;

    tp = malloc(sizeof(TagPath));
    if (tp == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    tp->count = 0;
    tp->tags = NULL;

    return tp;
}

TagPath *TagPath_build(char **tp_arr, int count) {
    int i, has_error;
    TagPath *tp;

    has_error = 0;
    tp = TagPath_new();

    if (count > 0) {
        tp->tags = (char **)malloc(count * sizeof(char*));
        for (i = 0; i < count && !has_error; i++) {
            tp->tags[i] = malloc((strlen(tp_arr[i]) + 1) * sizeof(char));
            if (tp->tags[i] == NULL) {
                has_error = 1;
            }
            else {
                tp->count++;
                strcpy(tp->tags[i], tp_arr[i]);
            }
        }
    }

    if (has_error) {
        TagPath_destroy(tp);
        handle_fatal_error(E_ALLOC);
    }

    return tp;
}

void TagPath_destroy(TagPath *tp) {
    int i;

    if (tp != NULL) {
        if (tp->count > 0 && tp->tags != NULL) {
            for(i = 0; i < tp->count; i++) {
                free(tp->tags[i]);
            }
        }
        free(tp->tags);
        tp->count = 0;
    }
    free(tp);
}

TagPath *TagPath_clone(TagPath *tp) {
    TagPath *clone;

    if (tp != NULL) {
        clone = TagPath_build(tp->tags, tp->count);
    }
    else {
        clone = NULL;
    }

    return clone;
}

char *TagPath_to_str(TagPath *tp) {
    int i;
    size_t tp_str_len;
    char *tp_str;

    tp_str_len = 0;
    for (i = 0; i < tp->count; i++) {
        tp_str_len += strlen(tp->tags[i]);
        tp_str_len += 1; /* Symbol '/' or '\0' */
    }

    tp_str = malloc(tp_str_len * sizeof(char));
    if (tp_str == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    tp_str[0] = '\0';
    for (i = 0; i < tp->count; i++) {
        strcat(tp_str, tp->tags[i]);
        if (i != tp->count - 1) {
            strcat(tp_str, "/");
        }
    }

    return tp_str;
}

TagPath *TagPath_from_str(char *str) {
    TagPath *tpath;
    char *tpath_str, **tpath_parts, *t_str;
    int tpath_count, i;

    tpath_count = strcnt_(str, '/') + 1;

    tpath_parts = malloc(tpath_count * sizeof(char*));
    if (tpath_parts == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    i = 0;
    tpath_str = strdup_(str);
    while ((t_str = strsep_(&tpath_str, "/")) != NULL) {
        tpath_parts[i++] = t_str;
    }

    tpath = TagPath_build(tpath_parts, tpath_count);

    free(tpath_parts);

    return tpath;
}

File *File_new() {
    File *f;

    f = malloc(sizeof(File));
    if (f == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    f->id = -1;
    f->rel_path = NULL;
    f->tps_count = 0;
    f->tpathes = NULL;

    return f;
}

File *File_build(int id, TagPath **tps, int tpathes_count, char *path) {
    int i;
    File *f;

    f = File_new();
    f->id = id;
    f->rel_path = malloc((strlen(path) + 1) * sizeof(char));

    if (f->rel_path == NULL) {
        File_destroy(f);
        handle_fatal_error(E_ALLOC);
    }

    strcpy(f->rel_path, path);

    if (tpathes_count > 0) {
        f->tpathes = malloc(tpathes_count * sizeof(TagPath));
        if (f->tpathes == NULL) {
            File_destroy(f);
            handle_fatal_error(E_ALLOC);
        }

        for (i = 0; i < tpathes_count; i++) {
            f->tpathes[i] = TagPath_clone(tps[i]);
            f->tps_count++;
        }
    }

    return f;
}

void File_destroy(File *file) {
    int i;
    if (file != NULL) {
        free(file->rel_path);
        if (file->tps_count > 0 && file->tpathes != NULL) {
            for (i = 0; i < file->tps_count; i++) {
                TagPath_destroy(file->tpathes[i]);
            }
        }
        free(file->tpathes);
    }
    free(file);
}

File *File_clone(File *file) {
    int i;
    File *cl;

    cl = File_new();

    cl->id = file->id;

    cl->rel_path = strdup_(file->rel_path);
    if (cl->rel_path == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    cl->tpathes = malloc(file->tps_count * sizeof(TagPath *));
    if (cl->tpathes == NULL) {
        handle_fatal_error(E_ALLOC);
    }

    for (i = 0; i < file->tps_count; i++) {
        cl->tpathes[i] = TagPath_clone(file->tpathes[i]);
    }

    cl->tps_count = file->tps_count;

    return cl;
}

int File_equals(File *f1, File *f2) {
    return  f1 == f2 ||
            (f1 != NULL && f2 != NULL && f1->id == f2->id);
}

