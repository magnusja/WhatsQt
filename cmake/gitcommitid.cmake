find_package(Git)
if(GIT_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} log -1 --date=short "--pretty=%h"
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            RESULT_VARIABLE res_var
            OUTPUT_VARIABLE GIT_COM_ID
    )

    if(NOT ${res_var} EQUAL 0)
        set(GIT_COMMIT_ID "unknown")
        message(WARNING "Git failed (not a repo, or no tags). Build will not contain git revision info.")
    endif()

    string(REPLACE "\n" "" GIT_COMMIT_ID "${GIT_COM_ID}")
else()
    set(GIT_COMMIT_ID "unknown")
endif()