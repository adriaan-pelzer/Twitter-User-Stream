#include "includes.h"

#ifndef _FT_JSON_H_
#define _FT_JSON_H_

typedef struct Url {
    char *url;
    char *expanded_url;
    char *display_url;
} *Url_p;

typedef struct Media {
    char *type;
    char *url;
    char *media_url;
    char *expanded_url;
    char *display_url;
} *Media_p;

typedef struct Entities {
    Url_p urls;
    size_t url_len;
    Media_p media;
    size_t media_len;
} *Entities_p;

typedef struct User {
    char *id_str;
    char *screen_name;
    char *name;
    char *profile_image_url;
    char *description;
} *User_p;

typedef struct Tweet {
    char *id_str;
    char *created_at;
    char *text;
    User_p user;
    Entities_p entities;
    void *retweeted_status;
    int32_t retweet_count;
    char *error;
} *Tweet_p;

void free_tweet(Tweet_p twt);
int32_t int_from_string_object(json_object *object, const char *key);
char *string_from_object(json_object *object, const char *key);
int tweet_create_from_json(char *tweet);
char send_email(const char *twitter_id, const char *media_url, const char *photo_url, const char *tweet_text);

#endif
