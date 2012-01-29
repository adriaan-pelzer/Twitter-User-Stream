#include "includes.h"

enum tweet_element tokenize (char *key) {
    if (!strncmp(key, "place", strlen(key))) { return TWTELM_PLACE; }
    if (!strncmp(key, "geo", strlen(key))) { return TWTELM_GEO; }
    if (!strncmp(key, "retweeted", strlen(key))) { return TWTELM_RETWEETED; }
    if (!strncmp(key, "retweeted_status", strlen(key))) { return TWTELM_RETWEETED_STATUS; }
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
    if (!strncmp(key, "name", strlen(key))) { return TWTELM_NAME; }
    if (!strncmp(key, "screen_name", strlen(key))) { return TWTELM_SCREEN_NAME; }
    if (!strncmp(key, "show_all_inline_media", strlen(key))) { return TWTELM_SHOW_ALL_INLINE_MEDIA; }
    if (!strncmp(key, "profile_text_color", strlen(key))) { return TWTELM_PROFILE_TEXT_COLOR; }
    if (!strncmp(key, "statuses_count", strlen(key))) { return TWTELM_STATUSES_COUNT; }
    if (!strncmp(key, "profile_background_image_url_https", strlen(key))) { return TWTELM_PROFILE_BACKGROUND_IMAGE_URL_HTTPS; }
    if (!strncmp(key, "profile_background_image_url", strlen(key))) { return TWTELM_PROFILE_BACKGROUND_IMAGE_URL; }
    if (!strncmp(key, "listed_count", strlen(key))) { return TWTELM_LISTED_COUNT; }
    if (!strncmp(key, "following", strlen(key))) { return TWTELM_FOLLOWING; }
    if (!strncmp(key, "verified", strlen(key))) { return TWTELM_VERIFIED; }
    if (!strncmp(key, "time_zone", strlen(key))) { return TWTELM_TIME_ZONE; }
    if (!strncmp(key, "profile_link_color", strlen(key))) { return TWTELM_PROFILE_LINK_COLOR; }
    if (!strncmp(key, "profile_image_url_https", strlen(key))) { return TWTELM_PROFILE_IMAGE_URL_HTTPS; }
    if (!strncmp(key, "location", strlen(key))) { return TWTELM_LOCATION; }
    if (!strncmp(key, "is_translator", strlen(key))) { return TWTELM_IS_TRANSLATOR; }
    if (!strncmp(key, "geo_enabled", strlen(key))) { return TWTELM_GEO_ENABLED; }
    if (!strncmp(key, "friends_count", strlen(key))) { return TWTELM_FRIENDS_COUNT; }
    if (!strncmp(key, "description", strlen(key))) { return TWTELM_DESCRIPTION; }
    if (!strncmp(key, "default_profile", strlen(key))) { return TWTELM_DEFAULT_PROFILE; }
    if (!strncmp(key, "profile_background_color", strlen(key))) { return TWTELM_PROFILE_BACKGROUND_COLOR; }
    if (!strncmp(key, "notifications", strlen(key))) { return TWTELM_NOTIFICATIONS; }
    if (!strncmp(key, "profile_background_tile", strlen(key))) { return TWTELM_PROFILE_BACKGROUND_TILE; }
    if (!strncmp(key, "follow_request_sent", strlen(key))) { return TWTELM_FOLLOW_REQUEST_SENT; }
    if (!strncmp(key, "profile_sidebar_fill_color", strlen(key))) { return TWTELM_PROFILE_SIDEBAR_FILL_COLOR; }
    if (!strncmp(key, "protected", strlen(key))) { return TWTELM_PROTECTED; }
    if (!strncmp(key, "default_profile_image", strlen(key))) { return TWTELM_DEFAULT_PROFILE_IMAGE; }
    if (!strncmp(key, "contributors_enabled", strlen(key))) { return TWTELM_CONTRIBUTORS_ENABLED; }
    if (!strncmp(key, "profile_sidebar_border_color", strlen(key))) { return TWTELM_PROFILE_SIDEBAR_BORDER_COLOR; }
    if (!strncmp(key, "followers_count", strlen(key))) { return TWTELM_FOLLOWERS_COUNT; }
    if (!strncmp(key, "profile_image_url", strlen(key))) { return TWTELM_PROFILE_IMAGE_URL; }
    if (!strncmp(key, "favourites_count", strlen(key))) { return TWTELM_FAVOURITES_COUNT; }
    if (!strncmp(key, "lang", strlen(key))) { return TWTELM_LANG; }
    if (!strncmp(key, "profile_use_background_image", strlen(key))) { return TWTELM_PROFILE_USE_BACKGROUND_IMAGE; }
    if (!strncmp(key, "utc_offset", strlen(key))) { return TWTELM_UTC_OFFSET; }
    if (!strncmp(key, "url", strlen(key))) { return TWTELM_URL; }
    return TWTELM_UNDEF;
}

void store_tweet(char *tweet_id, char *user_id, char *retweet_count) {
    printf ("Tweet ID: %s\nUser ID: %s\nRetweet Count: %s\n\n", tweet_id, user_id, retweet_count);
    return;
}

int tweet_create_from_json (char *tweet_json_string) {
    int rc = -1;
    char *key = NULL, *ukey = NULL;
    json_object *tweet = NULL, *value = NULL, *uvalue = NULL;
    struct lh_entry *entry = NULL, *user = NULL;

    char *tweet_id = NULL;
    char *user_id = NULL;
    char *retweet_count = NULL;

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
                    tweet_id = (char *) json_object_get_string(value);
                    break;
                case TWTELM_RETWEET_COUNT:
                    retweet_count = (char *) json_object_get_string (value);
                    break;
                case TWTELM_USER:
                    for (user = json_object_get_object(value)->head; user; user = user->next) {
                        ukey = (char *) user->k;
                        uvalue = (json_object *) user->v;

                        switch (tokenize(ukey)) {
                            case TWTELM_NAME:
                            case TWTELM_SCREEN_NAME:
                            case TWTELM_SHOW_ALL_INLINE_MEDIA:
                            case TWTELM_PROFILE_TEXT_COLOR:
                            case TWTELM_STATUSES_COUNT:
                            case TWTELM_PROFILE_BACKGROUND_IMAGE_URL_HTTPS:
                            case TWTELM_PROFILE_BACKGROUND_IMAGE_URL:
                            case TWTELM_LISTED_COUNT:
                            case TWTELM_FOLLOWING:
                            case TWTELM_VERIFIED:
                            case TWTELM_TIME_ZONE:
                            case TWTELM_PROFILE_LINK_COLOR:
                            case TWTELM_PROFILE_IMAGE_URL_HTTPS:
                            case TWTELM_LOCATION:
                            case TWTELM_IS_TRANSLATOR:
                            case TWTELM_GEO_ENABLED:
                            case TWTELM_FRIENDS_COUNT:
                            case TWTELM_DESCRIPTION:
                            case TWTELM_DEFAULT_PROFILE:
                            case TWTELM_PROFILE_BACKGROUND_COLOR:
                            case TWTELM_NOTIFICATIONS:
                            case TWTELM_PROFILE_BACKGROUND_TILE:
                            case TWTELM_FOLLOW_REQUEST_SENT:
                            case TWTELM_PROFILE_SIDEBAR_FILL_COLOR:
                            case TWTELM_PROTECTED:
                            case TWTELM_DEFAULT_PROFILE_IMAGE:
                            case TWTELM_CONTRIBUTORS_ENABLED:
                            case TWTELM_PROFILE_SIDEBAR_BORDER_COLOR:
                            case TWTELM_FOLLOWERS_COUNT:
                            case TWTELM_PROFILE_IMAGE_URL:
                            case TWTELM_FAVOURITES_COUNT:
                            case TWTELM_LANG:
                            case TWTELM_PROFILE_USE_BACKGROUND_IMAGE:
                            case TWTELM_UTC_OFFSET:
                            case TWTELM_URL:
                            case TWTELM_CREATED_AT:
                            case TWTELM_ID:
                                break;
                            case TWTELM_ID_STR:
                                user_id = (char *) json_object_get_string (uvalue);
                                break;
                            case TWTELM_UNDEF:
                                syslog(P_ERR, "Undefined token found in user object: %s", ukey);
                                break;
                            default:
                                syslog(P_ERR, "Out-of-place token found in user object: %s", ukey);
                        }
                    }
                    break;
                case TWTELM_TEXT:
                case TWTELM_PLACE:
                case TWTELM_GEO:
                case TWTELM_RETWEETED:
                case TWTELM_RETWEETED_STATUS:
                case TWTELM_IN_REPLY_TO_STATUS_ID_STR:
                case TWTELM_IN_REPLY_TO_STATUS_ID:
                case TWTELM_IN_REPLY_TO_USER_ID_STR:
                case TWTELM_TRUNCATED:
                case TWTELM_POSSIBLY_SENSITIVE_EDITABLE:
                case TWTELM_SOURCE:
                case TWTELM_IN_REPLY_TO_USER_ID:
                case TWTELM_CONTRIBUTORS:
                case TWTELM_FAVORITED:
                case TWTELM_CREATED_AT:
                case TWTELM_COORDINATES:
                case TWTELM_POSSIBLY_SENSITIVE:
                case TWTELM_IN_REPLY_TO_SCREEN_NAME:
                case TWTELM_ID:
                case TWTELM_ENTITIES:
                    break;
                case TWTELM_UNDEF:
                    syslog(P_ERR, "Undefined token found: %s", key);
                    break;
                default:
                    syslog(P_ERR, "Out-of-place token found: %s", key);
            }
        }

        if (tweet_id && user_id && retweet_count) {
            store_tweet(tweet_id, user_id, retweet_count);
        }
    }

    rc = 0;
over:
    if (tweet)
        json_object_put(tweet);

    return rc;
}
