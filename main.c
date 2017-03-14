#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "id3v2lib.h"
#include "parg.h"

struct info {
    char* title;
    char* artist;
    char* album;
    char* album_artist;
    char* genre;
    char* track;
    char* year;
    char* comment;
    char* disc_number;
    char* composer;
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

void print_all_tags(const char *file)
{
    if (!is_file_writable(file)) {
        fprintf(stderr, "%s is not writeable or does not exist", file);
        exit(EXIT_FAILURE);
    }

    ID3v2_tag* tag = load_tag(file); // Load the full tag from the file
    if (tag == NULL) {
        printf("%s: no tag found", file);
    }
    else {
        ID3v2_frame* f = tag_get_title(tag);
        ID3v2_frame_text_content* tc = parse_text_frame_content(f);
        if (tc != NULL) {
            printf("TITLE: %s\n", tc->data);
        } else {
            printf("failed to parse TITLE\n");
        }

        f = tag_get_artist(tag);
        tc = parse_text_frame_content(f);
        if (tc != NULL) {
            printf("ARTIST: %s\n", tc->data);
        } else {
            printf("failed to parse ARTIST\n");
        }

        f = tag_get_album(tag);
        tc = parse_text_frame_content(f);
        if (tc != NULL) {
            printf("ALBUM: %s\n", tc->data);
        } else {
            printf("failed to parse ALBUM\n");
        }

        f = tag_get_album_artist(tag);
        tc = parse_text_frame_content(f);
        if (tc != NULL) {
            printf("ALBUM ARTIST: %s\n", tc->data);
        } else {
            printf("failed to parse ALBUM ARTIST\n");
        }

        f = tag_get_genre(tag);
        tc = parse_text_frame_content(f);
        if (tc != NULL) {
            printf("GENRE: %s\n", tc->data);
        } else {
            printf("failed to parse GENRE\n");
        }

        f = tag_get_track(tag);
        tc = parse_text_frame_content(f);
        if (tc != NULL) {
            printf("TRACK: %s\n", tc->data);
        } else {
            printf("failed to parse TRACK\n");
        }

        f = tag_get_year(tag);
        tc = parse_text_frame_content(f);
        if (tc != NULL) {
            printf("YEAR: %s\n", tc->data);
        } else {
            printf("failed to parse YEAR\n");
        }

        f = tag_get_comment(tag);
        tc = parse_text_frame_content(f);
        if (tc != NULL) {
            printf("COMMENT: %s\n", tc->data);
        } else {
            printf("failed to parse COMMENT\n");
        }

        f = tag_get_disc_number(tag);
        tc = parse_text_frame_content(f);
        if (tc != NULL) {
            printf("DISC NUMBER: %s\n", tc->data);
        } else {
            printf("failed to parse DISC NUMBER\n");
        }

        f = tag_get_composer(tag);
        tc = parse_text_frame_content(f);
        if (tc != NULL) {
            printf("COMPOSER: %s\n", tc->data);
        } else {
            printf("failed to parse COMPOSER\n");
        }
    }
}

void set_tags(const char *file, struct info* i, bool set_unspecified_to_empty)
{
    if (!is_file_writable(file)) {
        fprintf(stderr, "%s is not writeable or does not exist", file);
        exit(1);
    }

    ID3v2_tag* tag = load_tag(file);
    if(tag == NULL)
    {
        tag = new_tag();
    }

    // Set the new info
    if (i->title) {
        tag_set_title(i->title, 0, tag);
    }
    else if (set_unspecified_to_empty) {
        tag_set_title("", 0, tag);
    }
    if (i->artist) {
        tag_set_artist(i->artist, 0, tag);
    }
    else if (set_unspecified_to_empty) {
        tag_set_artist("", 0, tag);
    }
    if (i->album) {
        tag_set_album(i->album, 0, tag);
    }
    else if (set_unspecified_to_empty) {
        tag_set_album("", 0, tag);
    }
    if (i->album_artist) {
        tag_set_album_artist(i->album_artist, 0, tag);
    }
    else if (set_unspecified_to_empty) {
        tag_set_album_artist("", 0, tag);
    }
    if (i->genre) {
        tag_set_genre(i->genre, 0, tag);
    }
    else if (set_unspecified_to_empty) {
        tag_set_genre("", 0, tag);
    }
    if (i->track) {
        tag_set_track(i->track, 0, tag);
    }
    else if (set_unspecified_to_empty) {
        tag_set_track("", 0, tag);
    }
    if (i->year) {
        tag_set_year(i->year, 0, tag);
    }
    else if (set_unspecified_to_empty) {
        tag_set_year("", 0, tag);
    }
    if (i->comment) {
        tag_set_comment(i->comment, 0, tag);
    }
    else if (set_unspecified_to_empty) {
        tag_set_comment("", 0, tag);
    }
    if (i->disc_number) {
        tag_set_disc_number(i->disc_number, 0, tag);
    }
    else if (set_unspecified_to_empty) {
        tag_set_disc_number("", 0, tag);
    }
    if (i->composer) {
        tag_set_composer(i->composer, 0, tag);
    }
    else if (set_unspecified_to_empty) {
        tag_set_composer("", 0, tag);
    }

    // Write the new tag to the file
    set_tag(file, tag);
}

void remove_all_tags(const char *filename)
{
    // stat file to make sure it exits
    remove_tag(filename);
}

int main(int argc, char *argv[])
{
    struct parg_state ps = {0};
    int c, optend = 0;
    bool print, remove, set_unspecified_to_empty = false;
    struct info i = {0};
    const char *optstring = "hvprut:a:l:b:g:k:y:c:n:o:";

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
                       "\t[-c comment]      sets the comment\n"
                       "\t[-n disc-number]  sets the disc number\n"
                       "\t[-o composer]     sets the composer\n");
                return EXIT_SUCCESS;
                break;
            case 'v':
                printf("tagmp3 0.0.1\n");
                return EXIT_SUCCESS;
                break;
            case 'p':
                print = true;
                printf("setting print to: true\n");
                break;
            case 'r':
                remove = true;
                printf("setting remove to: true\n");
                break;
            case 'u':
                set_unspecified_to_empty = true;
                printf("setting unspecified fields to empty string: true\n");
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
            case 'b':
                i.album_artist = (char*)ps.optarg;
                printf("setting album-artist to: '%s'\n", i.album_artist);
                break;
            case 'g':
                i.genre = (char*)ps.optarg;
                printf("setting genre to: '%s'\n", i.genre);
                break;
            case 'k':
                i.track = (char*)ps.optarg;
                printf("setting track to: '%s'\n", i.track);
                break;
            case 'y':
                i.year = (char*)ps.optarg;
                printf("setting year to: '%s'\n", i.year);
                break;
            case 'c':
                i.comment = (char*)ps.optarg;
                printf("setting comment to: '%s'\n", i.comment);
                break;
            case 'n':
                i.disc_number = (char*)ps.optarg;
                printf("setting disc_number to: '%s'\n", i.disc_number);
                break;
            case 'o':
                i.composer = (char*)ps.optarg;
                printf("setting composer to: '%s'\n", i.composer);
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
