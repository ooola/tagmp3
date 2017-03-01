#include <stdio.h>
#include <stdlib.h>

#include "id3v2lib.h"
#include "parg.h"

void print_all_tags(const char *file)
{
    // stat file to make sure it exits

    ID3v2_tag* tag = load_tag(file); // Load the full tag from the file
    if(tag != NULL)
    {
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

void remove_all_tags(const char *filename)
{
    // stat file to make sure it exits
    remove_tag(filename);
}

int main(int argc, char *argv[])
{
    struct parg_state ps;
    int c;

    parg_init(&ps);

    while ((c = parg_getopt(&ps, argc, argv, "hs:vp:r:")) != -1) {
        switch (c) {
            case 1:
                printf("nonoption '%s'\n", ps.optarg);
                break;
            case 'h':
                printf("Usage: tag [-h] [-v] [-p filename] [-s STRING] [-r filename]\n");
                return EXIT_SUCCESS;
                break;
            case 's':
                printf("option -s with argument '%s'\n", ps.optarg);
                break;
            case 'v':
                printf("tag 1.0.0\n");
                return EXIT_SUCCESS;
                break;
            case 'p':
                print_all_tags(ps.optarg);
                return EXIT_SUCCESS;
                break;
            case 'r':
                remove_all_tags(ps.optarg);
                return EXIT_SUCCESS;
                break;
            case '?':
                if (ps.optopt == 's') {
                    printf("option -s requires an argument\n");
                }
                else if (ps.optopt == 'p') {
                    printf("option -p requires an argument\n");
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

    for (c = ps.optind; c < argc; ++c) {
        printf("nonoption '%s'\n", argv[c]);
    }

    return EXIT_SUCCESS;
}
