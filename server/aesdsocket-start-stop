#!/bin/sh

DAEMON_NAME="aesdsocket"
DAEMON="/usr/bin/aesdsocket"
DAEMON_ARGS="-d"

case "$1" in
	start)
			echo "Starting ${DAEMON_NAME}"
			start-stop-daemon -S -n aesdsocket --exec "$DAEMON" -- "$DAEMON_ARGS"
			;;
	stop)
			echo "Stopping ${DAEMON_NAME}"
			start-stop-daemon -K -n aesdsocket
			;;
	*)
			echo "Usage: $0 {start|stop}"
			exit 1
esac

exit 0
