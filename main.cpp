#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parg.h"
#include "tag_c.h"

static bool verbose = false;

#ifdef DEBUG
verbose = true
#endif

struct info {
    char* title;
    char* artist;
    char* album;
    char* genre;
    unsigned int track;
    unsigned int year;
    char* comment;
};

// returns true if file exits and is writeable
bool is_file_writable(const char* file)
{
    if(access(file, W_OK) == 0) {
        return true;
    } else {
        return false;
    }
}

void print_all_tags(const char *filename)
{
    TagLib_File *file;
    TagLib_Tag *tag;
    // TODO print audio properties?

    file = taglib_file_new(filename);
    if (file == NULL) {
        fprintf(stderr, "taglib failed to read %s", filename);
        exit(EXIT_FAILURE);
    }
    tag = taglib_file_tag(file);
    if (tag == NULL) {
        printf("%s: no tag found", filename);
    }
    else {
        printf("TITLE: %s\n", taglib_tag_title(tag));
        printf("ARTIST: %s\n", taglib_tag_artist(tag));
        printf("ALBUM: %s\n", taglib_tag_album(tag));
        printf("GENRE: %s\n", taglib_tag_genre(tag));
        printf("TRACK: %d\n", taglib_tag_track(tag));
        printf("YEAR: %d\n", taglib_tag_year(tag));
        printf("COMMENT: %s\n", taglib_tag_comment(tag));
    }
}

// see tag_c.h
void set_tags(const char *filename, struct info* i, bool set_unspecified_to_empty)
{
    TagLib_File *file;
    TagLib_Tag *tag;

    if (!is_file_writable(filename)) {
        fprintf(stderr, "%s is not writeable or does not exist\n", filename);
        exit(1);
    }

    taglib_set_strings_unicode(false);

    file = taglib_file_new(filename);
    if(file == NULL)
    {
        fprintf(stderr, "taglib_file_new failed for %s\n", filename);
        exit(1);
    }
    tag = taglib_file_tag(file);

    // Set the new info
    if (i->title) {
        taglib_tag_set_title(tag, i->title); // TODO howto utf8 ??? taglib_set_strings_unicode(FALSE); ?
    }
    else if (set_unspecified_to_empty) {
        taglib_tag_set_title(tag, ""); // TODO howto utf8 ???
    }
    if (i->artist) {
        taglib_tag_set_artist(tag, i->artist);
    }
    else if (set_unspecified_to_empty) {
        taglib_tag_set_artist(tag, "");
    }
    if (i->album) {
        taglib_tag_set_album(tag, i->album);
    }
    else if (set_unspecified_to_empty) {
        taglib_tag_set_album(tag, "");
    }
    if (i->genre) {
        taglib_tag_set_genre(tag, i->genre);
    }
    else if (set_unspecified_to_empty) {
        taglib_tag_set_genre(tag, "");
    }
    if (i->track) {
        taglib_tag_set_track(tag, i->track);
    }
    else if (set_unspecified_to_empty) {
        taglib_tag_set_track(tag, 0);
    }
    if (i->year) {
        taglib_tag_set_year(tag, i->year);
    }
    else if (set_unspecified_to_empty) {
        taglib_tag_set_year(tag, 0);
    }
    if (i->comment) {
        taglib_tag_set_comment(tag, i->comment);
    }
    else if (set_unspecified_to_empty) {
        taglib_tag_set_comment(tag, "");
    }

    // Write the new tag to the file
    taglib_file_save(file);

    taglib_tag_free_strings(); // needed?
    taglib_file_free(file);
}

void remove_all_tags(const char *filename)
{
    // stat file to make sure it exits
    // TODO: figure out how to do this
    //remove_tag(filename);
}

int main(int argc, char *argv[])
{
    struct parg_state ps = {0};
    int c, optend = 0;
    bool print, remove, set_unspecified_to_empty = false;
    struct info i = {0};
    const char *optstring = "hvprut:a:l:g:k:y:c:";

    parg_init(&ps);
    optend = parg_reorder(argc, argv, optstring, NULL);

    while ((c = parg_getopt(&ps, optend, argv, optstring)) != -1) {
        switch (c) {
            case 1:
                // TODO change to use parg_reorder !!!
                printf("SWITCH nonoption '%s'\n", ps.optarg);
                break;
            case 'h':
                printf("Usage: tagmp3 [options] filename\n"
                       "\t[-h]              prints this screen\n"
                       "\t[-v]              prints version information\n"
                       "\t[-p]              prints existing tag information\n"
                       "\t[-r]              remove all existing tag information\n"
                       "\t[-u]              set unspecified tags to empty string\n"
                       "\t[-t title]        sets the title\n"
                       "\t[-a artist]       sets the artist\n"
                       "\t[-l album]        sets the album\n"
                       "\t[-b album-artist] sets the album artist\n"
                       "\t[-g genre]        sets the genre\n"
                       "\t[-k track]        sets the track\n"
                       "\t[-y year]         sets the year\n"
                       "\t[-c comment]      sets the comment\n");
                return EXIT_SUCCESS;
                break;
            case 'v':
                printf("tagmp3 0.0.1\n");
                return EXIT_SUCCESS;
                break;
            case 'p':
                print = true;
                if (verbose) {
                    printf("setting print to: true\n");
                }
                break;
            case 'r':
                remove = true;
                if (verbose) {
                    printf("setting remove to: true\n");
                }
                break;
            case 'u':
                set_unspecified_to_empty = true;
                if (verbose) {
                    printf("setting unspecified fields to empty string: true\n");
                }
                break;
            case 't':
                i.title = (char*)ps.optarg;
                printf("setting title to: '%s'\n", i.title);
                break;
            case 'a':
                i.artist = (char*)ps.optarg;
                printf("setting artist to: '%s'\n", i.artist);
                break;
            case 'l':
                i.album = (char*)ps.optarg;
                printf("setting album to: '%s'\n", i.album);
                break;
            case 'g':
                i.genre = (char*)ps.optarg;
                printf("setting genre to: '%s'\n", i.genre);
                break;
            case 'k':
                i.track = atoi((char*)ps.optarg);
                printf("setting track to: '%d'\n", i.track);
                break;
            case 'y':
                i.year = atoi((char*)ps.optarg);
                printf("setting year to: '%d'\n", i.year);
                break;
            case 'c':
                i.comment = (char*)ps.optarg;
                printf("setting comment to: '%s'\n", i.comment);
                break;
            case '?':
                if (ps.optopt == 't' ||
                    ps.optopt == 'a' ||
                    ps.optopt == 'l' ||
                    ps.optopt == 'b' ||
                    ps.optopt == 'g' ||
                    ps.optopt == 'k' ||
                    ps.optopt == 'y' ||
                    ps.optopt == 'c' ||
                    ps.optopt == 'n' ||
                    ps.optopt == 'o') {
                    printf("option %c requires an argument\n", ps.optopt);
                }
                else {
                    printf("unknown option -%c\n", ps.optopt);
                }
                return EXIT_FAILURE;
                break;
            default:
                printf("error: unhandled option -%c\n", c);
                return EXIT_FAILURE;
                break;
        }
    }

    /*
     * remove tags
     */
    if (remove) {
        for (c = ps.optind; c < argc; ++c) {
            remove_all_tags(argv[c]);
        }
    }

    /*
     * loop through list of files and perform action
     */
    for (c = ps.optind; c < argc; ++c) {
        set_tags(argv[c], &i, set_unspecified_to_empty);
    }

    /*
     * loop through list of files and print
     */
    if (print) {
        for (c = ps.optind; c < argc; ++c) {
            print_all_tags(argv[c]);
        }
    }

    return EXIT_SUCCESS;
}
