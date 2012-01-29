Twitter User Stream API C implementation
========================================

This is a short and sweet deamonized (standalone server) C implementation of the [Twitter User Stream API](https://dev.twitter.com/docs/streaming-api/user-streams "Twitter User Stream"). It is meant to be run in a userless, in other words, where you have stored the user's authentication token & secret in a seperate front end with a Twitter Signup user flow.

Installation Dependencies
-------------------------

* [liboauth](http://liboauth.sourceforge.net/ "OAuth C library")
* [json-c](http://oss.metaparadigm.com/json-c/ "JSON C library")
* [libcurl](http://curl.haxx.se/libcurl/ "CURL C Library")

Run *make* in the source directory. It will create a binary called *usbot*. This is the daemon, which could be started up with the *start_bot.sh* script. The script checks if the daemon is already running before starting it, to make it suitable for use in cron, as a "watchdog" script.

Customization
-------------

Most customization to this script can be done in json.c, from within the function *tweet_create_from_json*. At this point, a single API message is available as a json object, and can be processed at will.
