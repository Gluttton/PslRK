macro (determine_coverage_data Sources TestName Artifacts Suffix)
set (CoverageDirectory "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${TestName}.dir")
foreach (File ${Sources})
    string (REGEX MATCH "^${CMAKE_CURRENT_SOURCE_DIR}*" Directory "${File}")
    if    (Directory STREQUAL CMAKE_CURRENT_SOURCE_DIR)
        string (REGEX REPLACE "^${CMAKE_CURRENT_SOURCE_DIR}*" "${CoverageDirectory}" File "${File}")
    else  (Directory STREQUAL CMAKE_CURRENT_SOURCE_DIR)
        string (REGEX REPLACE "/" ";" A "${CMAKE_CURRENT_SOURCE_DIR}")
        string (REGEX REPLACE "/" ";" B "${File}")
        list (LENGTH A DeepDirectory)
        list (LENGTH B DeepFile)
        set (File "${CoverageDirectory}")
        set (I 1)
        while    (I LESS DeepDirectory)
            list (GET A ${I} AI)
            list (GET B ${I} BI)
            if    (AI STREQUAL BI)
                math (EXPR I "${I} + 1")
            else  (AI STREQUAL BI)
                math (EXPR DeepDiff "${DeepFile} - ${I} - 1")
                while    (DeepDiff GREATER 0)
                    set (File "${File}/__")
                    math (EXPR DeepDiff "${DeepDiff} - 1")
                endwhile (DeepDiff GREATER 0)
                while    (I LESS DeepFile)
                    list (GET B ${I} BI)
                    set (File "${File}/${BI}")
                    math (EXPR I "${I} + 1")
                endwhile (I LESS DeepFile)
            endif (AI STREQUAL BI)
        endwhile (I LESS DeepDirectory)
    endif (Directory STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set (${Artifacts} ${${Artifacts}} "${File}${Suffix}")
endforeach (File)
endmacro (determine_coverage_data)
