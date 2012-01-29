#include "includes.h"

char *replace_str (char *str, char *orig, char *rep) {
    char *buffer;
    char *p;

    if(!(p = strstr(str, orig)))
        return str;

    if (!(buffer = malloc (strlen (str) - strlen (orig) + strlen (rep) + 1))) {
        syslog (P_ERR, "Cannot allocate memory for new string");
        return NULL;
    }

    strncpy(buffer, str, p-str);
    buffer[p-str] = '\0';

    sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

    free (str);

    return buffer;
}

static size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)data;
    char *p = NULL;
    extern int sig_restart;

    /* Make space for new data from stream, and insert it */

    if (sig_restart == 1) {
        sig_restart = 0;
        return -1;
    }

    if (realsize > 2) {
        syslog (P_DBG, "Add %d bytes of data to scratch memory, for new data from stream", realsize);

        if ((mem->memory = realloc(mem->memory, mem->size + realsize + 1)) == NULL) {
            syslog (P_ERR, "not enough memory (realloc returned NULL)");
            exit(EXIT_FAILURE);
        }

        syslog (P_DBG, "Copy new data into newly allocated space");

        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;

        /* Now find all newlines, and assume they are tweet boundaries */

        while ((p = strchr(mem->memory, '\n'))) {
            char *first = NULL;
            char *last = NULL;
            size_t len = ((size_t) p - (size_t) mem->memory);

            if (!(first = malloc (len + 1))) {
                syslog (P_ERR, "Cannot allocate memory for next tweet JSON");
            }

            if (!(last = malloc (mem->size - len + 1))) {
                syslog (P_ERR, "Cannot allocate memory for remaining JSON text");
            }

            snprintf(first, len + 1, "%s", mem->memory);
            snprintf(last, mem->size - len + 1, "%s", p + 1);

            //syslog (P_DBG, "Found a tweet: %s", first);

            while (strstr (first, "\\u003C")) {
                if (!(first = replace_str(first, "\\u003C", "<"))) {
                    break;
                }
            }

            while (strstr (first, "\\u003E")) {
                if (!(first = replace_str(first, "\\u003E", ">"))) {
                    break;
                }
            }

            while (strstr (first, "\\u007B")) {
                if (!(first = replace_str(first, "\\u007B", "{"))) {
                    break;
                }
            }

            while (strstr (first, "\\u007D")) {
                if (!(first = replace_str(first, "\\u007D", "}"))) {
                    break;
                }
            }

            syslog(P_DBG, "Found tweet JSON: %s\n", first);

            if (tweet_create_from_json(first) != 0) {
                syslog(P_ERR, "Cannot process tweet json text");
            }

            if (first)
                free (first);

            if (mem->memory)
                free (mem->memory);

            mem->memory = last;
            mem->size = strlen (mem->memory);
        }
    }

    return realsize;
}

void freeMemoryStruct(struct MemoryStruct *mem) {
    if (mem) {
        if (mem->curl_handle)
            curl_easy_cleanup(mem->curl_handle);

        if (mem->glob_init) {
            curl_global_cleanup();
            mem->glob_init = 0;
        }

        if(mem->memory)
            free(mem->memory);

        if (mem->req_url)
            free (mem->req_url);
    }

    return;
}

CURLcode curl_connect() { 
    CURLcode cr = CURLE_FAILED_INIT;
    char urlfirst[] = "https://userstream.twitter.com/2/user.json";
    struct MemoryStruct *mem;
    long int http_code = 0;

    /* Allocate & initialise memory struct */
    if ((mem = malloc(sizeof(struct MemoryStruct))) == NULL) {
        syslog(P_ERR, "Cannot alocate memory for main object");
        goto over;
    }

    mem->curl_handle = NULL;
    mem->glob_init = 0;
    mem->req_url = NULL;

    if ((mem->memory = malloc(1)) == NULL) {
        syslog(P_ERR, "Cannot alocate scratch memory inside main object");
        goto over;
    }

    mem->size = 0; 

    /* Sign URL */
    syslog (P_DBG, "Calculate signature for URL: %s", urlfirst);

    if (!(mem->req_url = oauth_sign_url2(urlfirst, NULL, OA_HMAC, NULL, C_KEY, C_SECRET, T_KEY, T_SECRET))) {
        syslog (P_ERR, "Cannot calculate url signature");
        goto over;
    }

    syslog (P_DBG, "Full URL with signature: %s", mem->req_url);

    /* Connect */
    if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
        syslog (P_ERR, "Cannot init curl");
        goto over;
    } else {
        mem->glob_init = 1;
    }

    if (!(mem->curl_handle = curl_easy_init())) {
        syslog (P_ERR, "Cannot get curl handle");
        goto over;
    }

    if (curl_easy_setopt(mem->curl_handle, CURLOPT_URL, mem->req_url) != CURLE_OK) {
        syslog (P_ERR, "Cannot set curl URL");
        goto over;
    }

    if (curl_easy_setopt(mem->curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback) != CURLE_OK) {
        syslog (P_ERR, "Cannot set curl Write Function");
        goto over;
    }

    if (curl_easy_setopt(mem->curl_handle, CURLOPT_WRITEDATA, (void *) mem) != CURLE_OK) {
        syslog (P_ERR, "Cannot set curl Write Data");
        goto over;
    }

    if (curl_easy_setopt(mem->curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0") != CURLE_OK) {
        syslog (P_ERR, "Cannot set curl User Agent");
        goto over;
    }

    if (curl_easy_setopt(mem->curl_handle, CURLOPT_FAILONERROR, 1) != CURLE_OK) {
        syslog (P_ERR, "Cannot set curl FAILONERROR");
        goto over;
    }

    cr = curl_easy_perform(mem->curl_handle);

    if (curl_easy_getinfo(mem->curl_handle, CURLINFO_RESPONSE_CODE, &http_code) != CURLE_OK) {
        syslog (P_ERR, "Cannot extract HTTP code from curl handle");
        goto over;
    }

    syslog (P_DBG, "HTTP code returned: %ld", http_code);
over:
    if (mem)
        freeMemoryStruct(mem);

    return cr;
}
