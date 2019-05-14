#include "file.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "app-error.h"

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

TagPath *TagPath_build(char **tp_arr, size_t count) {
    size_t i, has_error;
    TagPath *tp;

    has_error = 0;
    tp = TagPath_new();

    if (count > 0) {
        tp->tags = (char **)malloc(count * sizeof(char*));
        for (i = 0; i < count && !has_error; i++) {
            tp->tags[i] = malloc(strlen(tp_arr[i]) * sizeof(char));
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
    size_t i;

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

File *File_build(size_t id, TagPath **tps, size_t tpathes_count, char *path) {
    size_t i;
    File *f;

    f = File_new();
    f->id = id;
    f->rel_path = malloc(strlen(path) * sizeof(char));

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
    size_t i;
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

int File_equals(File *f1, File *f2) {
    return  f1 == f2 ||
            (f1 != NULL && f2 != NULL && f1->id == f2->id);
}

