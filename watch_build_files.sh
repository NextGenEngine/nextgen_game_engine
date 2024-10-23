#!/usr/bin/env bash

trigger_name=nextgen_game_engine_compile_commands_update
trigger_patterns=('**/BUILD' '**/WORKSPACE' '**/MODULE.bazel')

# Ensure watchman is watching the project root
watchman watch-project .

# Remove existing trigger if it exists
watchman trigger-del . "${trigger_name}"

# Set up a new trigger
watchman --logfile="${PWD}/compile_commands_watchman.log" -- trigger "$PWD" "${trigger_name}" \
	"${trigger_patterns[@]}" -- \
	"$PWD/refresh_compile_commands.sh"

# #!/usr/bin/env bash

# watchman-make -p '**/BUILD' '**/WORKSPACE' '**/MODULE.bazel' \
#   --make='./refresh_compile_commands.sh' \
#   --run
