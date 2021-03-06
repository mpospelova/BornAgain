MACRO(GLOB_DIRECTORIES result)
    FILE(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()
