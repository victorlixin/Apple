//
//  python-wrapper.c
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <Python/Python.h>

const char * const allowedUsernames[] = {
    "_calendar",
    "_devicemgr",
    "_teamsserver",
    "_xserverdocs"
};

const char* python = "/usr/bin/python2.7";
const char* bin = "/Applications/Server.app/Contents/ServerRoot/Library/CalendarServer/bin";
const char* site = "/Applications/Server.app/Contents/ServerRoot/Library/CalendarServer/lib/python2.7/site-packages";

// Prepend a path to the named environment variable
int prependToPath(const char* name, const char* prepend) {
    const char* old_value = getenv(name);
    char* new_value = NULL;
    if (old_value == NULL) {
        // No existing value - set to the prepend value
        size_t max_length = strlen(prepend) + 1;
        new_value = malloc(max_length);
        strlcpy(new_value, prepend, max_length);
    } else {
        // Existing value - so prepend with a ":" in between
        size_t max_length = strlen(old_value) + strlen(prepend) + 2;
        new_value = malloc(max_length);
        strlcpy(new_value, prepend, max_length);
        strlcat(new_value, ":", max_length);
        strlcat(new_value, old_value, max_length);
    }
    setenv(name, new_value, 1);
    free(new_value);
    return 0;
}

int uidIsAllowed() {
    // Returns 1 if we're root or any of the whitelisted users; 0 otherwise

    int uid = getuid();

    if (uid == 0) {
        // Always allow root
        return 1;

    } else {
        // Check the other whitelisted users
        int i, len;
        struct passwd* passwdInfo;

        len = sizeof(allowedUsernames) / sizeof(allowedUsernames[0]);
        for (i = 0; i < len; i++) {
            passwdInfo = getpwnam(allowedUsernames[i]);
            if (passwdInfo != NULL) {
                if (passwdInfo->pw_uid == uid) {
                    return 1;
                }
            }
        }
    }

    // No match
    return 0;
}


int main(int argc, const char * argv[]) {

    if (uidIsAllowed()) {
        int result;

        // Update PATH and PYTHONPATH
        prependToPath("PATH", bin);
        prependToPath("PYTHONPATH", site);

        Py_Initialize();
        result = Py_Main(argc, (char **)argv);
        Py_Finalize();
        return result;
    } else {
        printf("You are not allowed to run this executable.\n");
        return 1;
    }
}
