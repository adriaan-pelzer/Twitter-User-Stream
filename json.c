#include "includes.h"

char compare(const char *a, const char *b) {
    return ((strlen(a) == strlen(b)) && (!strncmp(a, b, strlen(a))));
}

enum tweet_element tokenize (char *key) {
    if (compare(key, "place")) { return TWTELM_PLACE; }
    if (compare(key, "geo")) { return TWTELM_GEO; }
    if (compare(key, "retweeted")) { return TWTELM_RETWEETED; }
    if (compare(key, "retweeted_status")) { return TWTELM_RETWEETED_STATUS; }
    if (compare(key, "text")) { return TWTELM_TEXT; }
    if (compare(key, "in_reply_to_status_id_str")) { return TWTELM_IN_REPLY_TO_STATUS_ID_STR; }
    if (compare(key, "in_reply_to_status_id")) { return TWTELM_IN_REPLY_TO_STATUS_ID; }
    if (compare(key, "in_reply_to_user_id_str")) { return TWTELM_IN_REPLY_TO_USER_ID_STR; }
    if (compare(key, "in_reply_to_user_id")) { return TWTELM_IN_REPLY_TO_USER_ID; }
    if (compare(key, "in_reply_to_user_id")) { return TWTELM_IN_REPLY_TO_USER_ID; }
    if (compare(key, "truncated")) { return TWTELM_TRUNCATED; }
    if (compare(key, "possibly_sensitive_editable")) { return TWTELM_POSSIBLY_SENSITIVE_EDITABLE; }
    if (compare(key, "source")) { return TWTELM_SOURCE; }
    if (compare(key, "contributors")) { return TWTELM_CONTRIBUTORS; }
    if (compare(key, "retweet_count")) { return TWTELM_RETWEET_COUNT; }
    if (compare(key, "favorited")) { return TWTELM_FAVORITED; }
    if (compare(key, "created_at")) { return TWTELM_CREATED_AT; }
    if (compare(key, "coordinates")) { return TWTELM_COORDINATES; }
    if (compare(key, "possibly_sensitive")) { return TWTELM_POSSIBLY_SENSITIVE; }
    if (compare(key, "id_str")) { return TWTELM_ID_STR; }
    if (compare(key, "user")) { return TWTELM_USER; }
    if (compare(key, "in_reply_to_screen_name")) { return TWTELM_IN_REPLY_TO_SCREEN_NAME; }
    if (compare(key, "id")) { return TWTELM_ID; }
    if (compare(key, "entities")) { return TWTELM_ENTITIES; }
    if (compare(key, "name")) { return TWTELM_NAME; }
    if (compare(key, "screen_name")) { return TWTELM_SCREEN_NAME; }
    if (compare(key, "show_all_inline_media")) { return TWTELM_SHOW_ALL_INLINE_MEDIA; }
    if (compare(key, "profile_text_color")) { return TWTELM_PROFILE_TEXT_COLOR; }
    if (compare(key, "statuses_count")) { return TWTELM_STATUSES_COUNT; }
    if (compare(key, "profile_background_image_url_https")) { return TWTELM_PROFILE_BACKGROUND_IMAGE_URL_HTTPS; }
    if (compare(key, "profile_background_image_url")) { return TWTELM_PROFILE_BACKGROUND_IMAGE_URL; }
    if (compare(key, "listed_count")) { return TWTELM_LISTED_COUNT; }
    if (compare(key, "following")) { return TWTELM_FOLLOWING; }
    if (compare(key, "verified")) { return TWTELM_VERIFIED; }
    if (compare(key, "time_zone")) { return TWTELM_TIME_ZONE; }
    if (compare(key, "profile_link_color")) { return TWTELM_PROFILE_LINK_COLOR; }
    if (compare(key, "profile_image_url_https")) { return TWTELM_PROFILE_IMAGE_URL_HTTPS; }
    if (compare(key, "location")) { return TWTELM_LOCATION; }
    if (compare(key, "is_translator")) { return TWTELM_IS_TRANSLATOR; }
    if (compare(key, "geo_enabled")) { return TWTELM_GEO_ENABLED; }
    if (compare(key, "friends_count")) { return TWTELM_FRIENDS_COUNT; }
    if (compare(key, "description")) { return TWTELM_DESCRIPTION; }
    if (compare(key, "default_profile")) { return TWTELM_DEFAULT_PROFILE; }
    if (compare(key, "profile_background_color")) { return TWTELM_PROFILE_BACKGROUND_COLOR; }
    if (compare(key, "notifications")) { return TWTELM_NOTIFICATIONS; }
    if (compare(key, "profile_background_tile")) { return TWTELM_PROFILE_BACKGROUND_TILE; }
    if (compare(key, "follow_request_sent")) { return TWTELM_FOLLOW_REQUEST_SENT; }
    if (compare(key, "profile_sidebar_fill_color")) { return TWTELM_PROFILE_SIDEBAR_FILL_COLOR; }
    if (compare(key, "protected")) { return TWTELM_PROTECTED; }
    if (compare(key, "default_profile_image")) { return TWTELM_DEFAULT_PROFILE_IMAGE; }
    if (compare(key, "contributors_enabled")) { return TWTELM_CONTRIBUTORS_ENABLED; }
    if (compare(key, "profile_sidebar_border_color")) { return TWTELM_PROFILE_SIDEBAR_BORDER_COLOR; }
    if (compare(key, "followers_count")) { return TWTELM_FOLLOWERS_COUNT; }
    if (compare(key, "profile_image_url")) { return TWTELM_PROFILE_IMAGE_URL; }
    if (compare(key, "favourites_count")) { return TWTELM_FAVOURITES_COUNT; }
    if (compare(key, "lang")) { return TWTELM_LANG; }
    if (compare(key, "profile_use_background_image")) { return TWTELM_PROFILE_USE_BACKGROUND_IMAGE; }
    if (compare(key, "utc_offset")) { return TWTELM_UTC_OFFSET; }
    if (compare(key, "url")) { return TWTELM_URL; }
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
