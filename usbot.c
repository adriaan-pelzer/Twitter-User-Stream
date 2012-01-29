#include "includes.h"

#define DAEMON_NAME "usbot"
#define PID_FILE "/var/run/usbot.pid"

int sig_restart = 0;

void PrintUsage (int argc, char *argv[]) {
    if (argc >=1) {
        printf ("Usage: %s -h -n\n", argv[0]);
        printf ("  Options:\n");
        printf ("      -n\tDon't fork off as a daemon.\n");
        printf ("      -h\tShow this help screen.\n");
        printf ("\n");
    }
}

void signal_handler (int sig) {
    switch (sig) {
        case SIGHUP:
            syslog (LOG_WARNING, "Received SIGHUP signal.");
            sig_restart = 1;
            break;
        case SIGINT:
            syslog (LOG_WARNING, "Received SIGINT signal.");
            exit (EXIT_SUCCESS);
            break;
        case SIGABRT:
            syslog (LOG_WARNING, "Received SIGABRT signal.");
            exit (EXIT_SUCCESS);
            break;
        case SIGTERM:
            syslog (LOG_WARNING, "Received SIGTERM signal.");
            exit (EXIT_SUCCESS);
            break;
        default:
            syslog (LOG_WARNING, "Unhandled signal (%d) %s", sig, strsignal(sig));
            break;
    }
}

int main(int argc, char *argv[]) {
#ifdef DEBUG
    int daemonize = 0;
#else
    int daemonize = 1;
#endif
    int c;
    pid_t pid, sid;
    CURLcode cr = CURLE_WRITE_ERROR; /* Check if this is the best initialization */
    time_t delay = 0;

    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);

    while ((c = getopt(argc, argv, "nh|help")) != -1) {
        switch (c) {
            case 'h':
                PrintUsage (argc, argv);
                exit (EXIT_SUCCESS);
                break;
            case 'n':
                daemonize = 0;
                break;
            default:
                PrintUsage (argc, argv);
                exit (EXIT_SUCCESS);
                break;
        }
    }

#ifdef DEBUG
    setlogmask (LOG_UPTO (LOG_DEBUG));
    openlog (DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
#else
    setlogmask (LOG_UPTO (LOG_INFO));
    openlog (DAEMON_NAME, LOG_CONS, LOG_USER);
#endif

    /* daemon stuff */
    if (daemonize) {
        syslog (P_INF, "%s daemon starting up", DAEMON_NAME);

        if ((pid = fork ()) < 0) {
            syslog (P_ERR, "Could not fork child process: %m");
            exit (EXIT_FAILURE);
        } else if (pid > 0) {
            syslog (P_NTC, "Child process successfully forked");
            exit (EXIT_SUCCESS);
        }

        umask(0);

        sid = setsid();
        if (sid < 0) {
            syslog (P_ERR, "Could not create new session: %m");
            exit (EXIT_FAILURE);
        }

        if ((chdir ("/")) < 0) {
            syslog (P_ERR, "Could not change working dir: %m");
            exit (EXIT_FAILURE);
        }

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
    }

    while ((cr == CURLE_WRITE_ERROR) || (cr == CURLE_OK) || (cr == CURLE_HTTP_RETURNED_ERROR)) {
        time_t uptime = 0, last_tcp_error = time(NULL);

        cr = curl_connect();

        if ((uptime = (time(NULL) - last_tcp_error)) > 240) {
            syslog(P_INF, "UP for more than 4 minutes, resetting delay");
            delay = 0;
        }

        if (cr == CURLE_HTTP_RETURNED_ERROR) {
            if (delay < 10)
                delay = 10;
            else
                delay *= 2;

            if (delay > 240)
                delay = 240;

            syslog(P_INF, "HTTP error - sleeping for %ld seconds", delay);
            sleep(delay);
        } else {
            if (delay < 1)
                delay = 1;
            else
                delay += 1;

            if (delay > 16)
                delay = 16;

            syslog(P_INF, "Connection error (%d) - sleeping for %ld seconds", cr, delay);
            sleep(delay);
        }
    }

    syslog (P_INF, "CURL ERROR: %d\n", cr);
    syslog (P_INF, "%s shutting down", DAEMON_NAME);

    exit (EXIT_SUCCESS);
}

