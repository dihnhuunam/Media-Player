add_library(lController
    SHARED 
        PlaylistManagementController.cpp
        MediaFileManagementController.cpp
        PlaybackController.cpp
        AppController.cpp
)

target_link_libraries(lController
    PUBLIC
        lModel
)

target_include_directories(lController 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)