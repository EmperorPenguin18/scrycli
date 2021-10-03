build: scry_user.cc
        g++ scry_user.cc -ldl -o scry_user

install: scry_user
        @mkdir -p /usr/bin/
        @mv scry_user /usr/bin/scry_user
