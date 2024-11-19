#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

#define BUILD "./build/"
#define SRC "./src/"
#define DEPS SRC "deps/"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);
    if (!mkdir_if_not_exists("build/")) return 1;
    const char *program = shift(argv, argc);
    Nob_Cmd cmd = {0};

    // clang-format off
    cmd_append(&cmd, "gcc",
               "-Wall", "-Wextra",
               "-I" DEPS "raylib-5.5_win64_mingw-w64/include",
               "-o", BUILD "ezhuti",
               SRC "ezhuti.c",
               "-L" DEPS "raylib-5.5_win64_mingw-w64/lib/", 
               "-l:libraylib.a", "-lgdi32", "-lwinmm",
    );
    // clang-format on

    if (!cmd_run_sync_and_reset(&cmd)) return 1;
    if (argc > 0) {
        const char *comamnd = shift(argv, argc);
        if (strcmp(comamnd, "run") == 0) {
            cmd_append(&cmd, BUILD "ezhuti");
            da_append_many(&cmd, argv, argc);
            if (!cmd_run_sync_and_reset(&cmd)) return 1;
        }
        else {
            nob_log(ERROR, "Unknown command %s", comamnd);
            return 1;
        }
    }
    return 0;
}
