#include "includes.h"

enum tweet_element tokenize (char *key) {
    if (!strncmp(key, "place", strlen(key))) { return TWTELM_PLACE; }
    if (!strncmp(key, "geo", strlen(key))) { return TWTELM_GEO; }
    if (!strncmp(key, "retweeted", strlen(key))) { return TWTELM_RETWEETED; }
    if (!strncmp(key, "text", strlen(key))) { return TWTELM_TEXT; }
    if (!strncmp(key, "in_reply_to_status_id_str", strlen(key))) { return TWTELM_IN_REPLY_TO_STATUS_ID_STR; }
    if (!strncmp(key, "in_reply_to_status_id", strlen(key))) { return TWTELM_IN_REPLY_TO_STATUS_ID; }
    if (!strncmp(key, "in_reply_to_user_id_str", strlen(key))) { return TWTELM_IN_REPLY_TO_USER_ID_STR; }
    if (!strncmp(key, "in_reply_to_user_id", strlen(key))) { return TWTELM_IN_REPLY_TO_USER_ID; }
    if (!strncmp(key, "in_reply_to_user_id", strlen(key))) { return TWTELM_IN_REPLY_TO_USER_ID; }
    if (!strncmp(key, "truncated", strlen(key))) { return TWTELM_TRUNCATED; }
    if (!strncmp(key, "possibly_sensitive_editable", strlen(key))) { return TWTELM_POSSIBLY_SENSITIVE_EDITABLE; }
    if (!strncmp(key, "source", strlen(key))) { return TWTELM_SOURCE; }
    if (!strncmp(key, "contributors", strlen(key))) { return TWTELM_CONTRIBUTORS; }
    if (!strncmp(key, "retweet_count", strlen(key))) { return TWTELM_RETWEET_COUNT; }
    if (!strncmp(key, "favorited", strlen(key))) { return TWTELM_FAVORITED; }
    if (!strncmp(key, "created_at", strlen(key))) { return TWTELM_CREATED_AT; }
    if (!strncmp(key, "coordinates", strlen(key))) { return TWTELM_COORDINATES; }
    if (!strncmp(key, "possibly_sensitive", strlen(key))) { return TWTELM_POSSIBLY_SENSITIVE; }
    if (!strncmp(key, "id_str", strlen(key))) { return TWTELM_ID_STR; }
    if (!strncmp(key, "user", strlen(key))) { return TWTELM_USER; }
    if (!strncmp(key, "in_reply_to_screen_name", strlen(key))) { return TWTELM_IN_REPLY_TO_SCREEN_NAME; }
    if (!strncmp(key, "id", strlen(key))) { return TWTELM_ID; }
    if (!strncmp(key, "entities", strlen(key))) { return TWTELM_ENTITIES; }
    return TWTELM_UNDEF;
}

int tweet_create_from_json (char *tweet_json_string) {
    int rc = -1;
    char *key = NULL;
    json_object *tweet = NULL, *value = NULL;
    struct lh_entry *entry = NULL;

    if (strncmp(tweet_json_string, "\r", 1)) {
        if ((tweet = json_tokener_parse(tweet_json_string)) == NULL) {
            syslog(P_DBG, "Cannot parse tweet json");
            syslog(P_DBG, "%s", tweet_json_string);
            goto over;
        }

        for (entry = json_object_get_object(tweet)->head; entry; entry = entry->next) {
            key = (char *) entry->k;
            value = (json_object *) entry->v;

            switch (tokenize(key)) {
                case TWTELM_ID_STR:
                case TWTELM_TEXT:
                case TWTELM_RETWEET_COUNT:
                    printf ("%s: %s\n", key, json_object_get_string (value));
                    break;
            }
        }
    }

    rc = 0;
over:
    if (tweet)
        json_object_put(tweet);

    return rc;
}
