#include "includes.h"

void free_tweet (Tweet_p twt) {
    size_t i = 0;

    if (twt) {
        if (twt->retweeted_status)
            free_tweet (twt->retweeted_status);
        if (twt->user) {
            if (twt->user->id_str)
                free (twt->user->id_str);
            if (twt->user->description)
                free (twt->user->description);
            if (twt->user->profile_image_url)
                free (twt->user->profile_image_url);
            if (twt->user->name)
                free (twt->user->name);
            if (twt->user->screen_name)
                free (twt->user->screen_name);
            free (twt->user);
        }
        if (twt->entities) {
            if (twt->entities->urls) {
                for (i = 0; i < twt->entities->url_len; i++) {
                    if (twt->entities->urls[i].url)
                        free(twt->entities->urls[i].url);
                    if (twt->entities->urls[i].expanded_url)
                        free(twt->entities->urls[i].expanded_url);
                    if (twt->entities->urls[i].display_url)
                        free(twt->entities->urls[i].display_url);
                }

                free(twt->entities->urls);
            }

            if (twt->entities->media) {
                for (i = 0; i < twt->entities->media_len; i++) {
                    if (twt->entities->media[i].url)
                        free(twt->entities->media[i].url);
                    if (twt->entities->media[i].expanded_url)
                        free(twt->entities->media[i].expanded_url);
                    if (twt->entities->media[i].display_url)
                        free(twt->entities->media[i].display_url);
                    if (twt->entities->media[i].media_url)
                        free(twt->entities->media[i].media_url);
                    if (twt->entities->media[i].type)
                        free(twt->entities->media[i].type);
                }

                free(twt->entities->media);
            }

            free (twt->entities);
        }
        if (twt->id_str)
            free (twt->id_str);
        if (twt->created_at)
            free (twt->created_at);
        if (twt->text)
            free (twt->text);
        if (twt->error)
            free (twt->error);
        free (twt);
    }
}

int32_t int_from_string_object (json_object *object, const char *key) {
    json_object *sub_object = NULL;
    char *sub_object_str = NULL;
    int32_t rc = -1;

    if (!(sub_object = json_object_object_get (object, key))) {
        goto over;
    }

    if (!(sub_object_str = (char *) json_object_get_string (sub_object))) {
        goto over;
    }

    if (strncmp (sub_object_str, "100+", 4)) {
        rc = atoi (sub_object_str);
    } else {
        rc = 101;
    }
over:
    return rc;
}

char *string_from_object (json_object *object, const char *key) {
    json_object *sub_object = NULL;
    const char *sub_object_str = NULL;
    char *return_str = NULL;

    if (!(sub_object = json_object_object_get (object, key))) {
        goto over;
    }

    if (!(sub_object_str = json_object_get_string (sub_object))) {
        goto over;
    }

    if (!(return_str = strdup (sub_object_str))) {
        goto over;
    }
over:
    return return_str;
}

Tweet_p tweet_create_from_object (json_object *tweet) {
    Tweet_p twt = NULL, _twt = NULL;
    json_object *tweet_retweeted_status = NULL,
                *tweet_user = NULL,
                *tweet_entities = NULL,
                *tweet_urls = NULL,
                *tweet_url = NULL,
                *tweet_medias = NULL,
                *tweet_media = NULL;
    size_t i = 0;

    if (!(_twt = (Tweet_p) malloc (sizeof (struct Tweet)))) {
        syslog (P_ERR, "Cannot allocate memory for tweet structure");
        goto over;
    }

    _twt->id_str = NULL;
    _twt->created_at = NULL;
    _twt->text = NULL;
    _twt->user = NULL;
    _twt->entities = NULL;
    _twt->retweeted_status = NULL;
    _twt->retweet_count = 0;
    _twt->error = NULL;

    if (!(_twt->user = malloc (sizeof (struct User)))) {
        syslog (P_ERR, "Cannot allocate memory for tweet user\n");
        goto over;
    }

    _twt->user->id_str = NULL;
    _twt->user->screen_name = NULL;
    _twt->user->name = NULL;
    _twt->user->profile_image_url = NULL;
    _twt->user->description = NULL;

    if (!(_twt->entities = malloc (sizeof (struct Entities)))) {
        syslog (P_ERR, "Cannot allocate memory for tweet entities\n");
        goto over;
    }

    _twt->entities->urls = NULL;
    _twt->entities->media = NULL;
    _twt->entities->url_len = 0;
    _twt->entities->media_len = 0;

    if ((tweet_retweeted_status = json_object_object_get (tweet, "retweeted_status"))) {
        if (!(_twt->retweeted_status = tweet_create_from_object (tweet_retweeted_status))) {
            syslog (P_ERR, "Cannot get retweeted status\n");
            goto over;
        }
    }

    if (!(_twt->text = string_from_object (tweet, "text"))) {
        goto over;
    }

    if (!(_twt->id_str = string_from_object (tweet, "id_str"))) {
        syslog (P_ERR, "Cannot retrieve id string");
        goto over;
    }

    if (!(_twt->created_at = string_from_object (tweet, "created_at"))) {
        syslog (P_ERR, "Cannot retrieve created_at string");
        goto over;
    }

    if ((_twt->retweet_count = int_from_string_object (tweet, "retweet_count")) == -1) {
        syslog (P_ERR, "Cannot retrieve retweet_count int");
    }

    if (!(tweet_user = json_object_object_get (tweet, "user"))) {
        syslog (P_ERR, "Cannot retrieve user object");
        goto over;
    }

    if (!(_twt->user->id_str = string_from_object (tweet_user, "id_str"))) {
        syslog (P_ERR, "Cannot retrieve user id_str string");
        goto over;
    }

    if (!(_twt->user->screen_name = string_from_object (tweet_user, "screen_name"))) {
        syslog (P_ERR, "Cannot retrieve user screen_name string");
        goto over;
    }

    if (!(_twt->user->name = string_from_object (tweet_user, "name"))) {
        syslog (P_ERR, "Cannot retrieve user name string");
        goto over;
    }

    _twt->user->description = string_from_object (tweet_user, "description");

    if (!(_twt->user->profile_image_url = string_from_object (tweet_user, "profile_image_url"))) {
        syslog (P_ERR, "Cannot retrieve user profile_image_url string");
        goto over;
    }

    if (!(tweet_entities = json_object_object_get (tweet, "entities"))) {
        syslog (P_ERR, "Cannot retrieve entities object");
        goto over;
    } else {
        if ((tweet_urls = json_object_object_get (tweet_entities, "urls"))) {
            _twt->entities->url_len = json_object_array_length(tweet_urls);

            if (!(_twt->entities->urls = malloc (sizeof(struct Url) * _twt->entities->url_len))) {
                syslog (P_ERR, "Cannot allocate memory for entity URLs");
                goto over;
            }

            for (i = 0; i < _twt->entities->url_len; i++) {
                _twt->entities->urls[i].url = NULL;
                _twt->entities->urls[i].expanded_url = NULL;
                _twt->entities->urls[i].display_url = NULL;

                if (!(tweet_url = json_object_array_get_idx(tweet_urls, i))) {
                    syslog (P_ERR, "Cannot retrieve url number %d from array", i);
                    goto over;
                } else {
                    if (!(_twt->entities->urls[i].url = string_from_object (tweet_url, "url"))) {
                        syslog (P_ERR, "Cannot retrieve url number %d element (url)", i);
                        goto over;
                    }
                    if (!(_twt->entities->urls[i].expanded_url = string_from_object (tweet_url, "expanded_url"))) {
                        syslog (P_ERR, "Cannot retrieve url number %d element (expanded_url)", i);
                        goto over;
                    }
                    if (!(_twt->entities->urls[i].display_url = string_from_object (tweet_url, "display_url"))) {
                        syslog (P_ERR, "Cannot retrieve url number %d element (display_url)", i);
                        goto over;
                    }
                }
            }
        }

        if ((tweet_medias = json_object_object_get (tweet_entities, "media"))) {
            _twt->entities->media_len = json_object_array_length(tweet_medias);

            if (!(_twt->entities->media = malloc (sizeof(struct Media) * _twt->entities->media_len))) {
                syslog (P_ERR, "Cannot allocate memory for entity URLs");
                goto over;
            }

            for (i = 0; i < _twt->entities->media_len; i++) {
                _twt->entities->media[i].url = NULL;
                _twt->entities->media[i].expanded_url = NULL;
                _twt->entities->media[i].display_url = NULL;
                _twt->entities->media[i].media_url = NULL;
                _twt->entities->media[i].type = NULL;

                if (!(tweet_media = json_object_array_get_idx(tweet_medias, i))) {
                    syslog (P_ERR, "Cannot retrieve media number %d from array", i);
                    goto over;
                } else {
                    if (!(_twt->entities->media[i].type = string_from_object (tweet_media, "type"))) {
                        syslog (P_ERR, "Cannot retrieve media number %d element (type)", i);
                        goto over;
                    }
                    if (!(_twt->entities->media[i].url = string_from_object (tweet_media, "url"))) {
                        syslog (P_ERR, "Cannot retrieve media number %d element (url)", i);
                        goto over;
                    }
                    if (!(_twt->entities->media[i].expanded_url = string_from_object (tweet_media, "expanded_url"))) {
                        syslog (P_ERR, "Cannot retrieve media number %d element (expanded_url)", i);
                        goto over;
                    }
                    if (!(_twt->entities->media[i].display_url = string_from_object (tweet_media, "display_url"))) {
                        syslog (P_ERR, "Cannot retrieve media number %d element (display_url)", i);
                        goto over;
                    }
                    if (!(_twt->entities->media[i].media_url = string_from_object (tweet_media, "media_url"))) {
                        syslog (P_ERR, "Cannot retrieve media number %d element (media_url)", i);
                        goto over;
                    }
                }
            }
        }
    }

    twt = _twt;
over:
    if (_twt && (twt == NULL)) {
        free_tweet (_twt);
        _twt = NULL;
    }

    return twt;
}

int tweet_create_from_json (char *tweet_json_string) {
    int i = 0, rc = -1;
    json_object *tweet = NULL;
    Tweet_p twt = NULL;
    Ids_p ids = NULL;
    MYSQL *conn = NULL;
    char one_of_our_users = 0;

    if ((conn = db_connect()) == NULL) {
        syslog(P_ERR, "Cannot connect to database");
        goto over;
    }

    if ((ids = get_ids(conn)) == NULL) {
        syslog(P_ERR, "Cannot get id list from database");
        goto over;
    }

    if ((tweet = json_tokener_parse(tweet_json_string)) == NULL) {
        syslog(P_DBG, "Cannot parse tweet json");
        syslog(P_DBG, "%s", tweet_json_string);
        goto over;
    }

    if ((twt = tweet_create_from_object(tweet)) == NULL) {
        syslog(P_DBG, "Cannot turn json object into tweet");
        goto over;
    }

    for (i = 0; i < ids->ids_len; i++) {
        if (!strncmp(ids->ids[i], twt->user->id_str, strlen(ids->ids[i]))) {
            one_of_our_users = 1;
            break;
        }
    }

    if (one_of_our_users) { /* skip mentions */
        if (twt->retweeted_status == NULL) { /* skip retweets */
            if (twt->entities) {
                if (twt->entities->media_len > 0) {
                    for (i = 0; i < twt->entities->media_len; i++) {
                        if (!strncmp (twt->entities->media[i].type, "photo", 5)) {
                            syslog(P_DBG, "Attached MEDIA: %s", twt->entities->media[i].expanded_url);
                            if (send_email(twt->user->id_str, twt->entities->media[i].expanded_url, NULL, twt->text) != 0) {
                                syslog(P_ERR, "All emails failed");
                            }
                            break;
                        }
                    }
                } else if (twt->entities->url_len > 0) {
                    for (i = 0; i < twt->entities->url_len; i++) {
                        syslog(P_DBG, "Attached URL: %s", twt->entities->urls[i].url);
                        syslog(P_DBG, "Attached URL (expanded): %s", twt->entities->urls[i].expanded_url);
                        if (send_email(twt->user->id_str, NULL, twt->entities->urls[i].expanded_url, twt->text) != 0) {
                            syslog(P_ERR, "All emails failed");
                        }
                    }
                } else {
                    syslog(P_DBG, "Photoless tweet");
                }
            }
        }
    }

    rc = 0;
over:
    if (ids) {
        free_ids(ids);
    }

    if (conn) {
        db_disconnect(conn);
    }

    if (twt) {
        free_tweet (twt);
        twt = NULL;
    }

    if (tweet)
        json_object_put(tweet);

    return rc;
}
