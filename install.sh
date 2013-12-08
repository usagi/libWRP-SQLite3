#!/bin/bash
COMMAND=${COMMAND=install -v}
PREFIX=${PREFIX=/usr/local}
find include -type d -exec ${COMMAND} -d $PREFIX/{} \;
find include -type f -exec ${COMMAND} {} $PREFIX/{} \;
