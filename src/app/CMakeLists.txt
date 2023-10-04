qt_add_executable(ghent-data-charts
    mainwidget.cpp
    main.cpp
)

target_link_libraries(ghent-data-charts PRIVATE Qt6::Widgets)

set_target_properties(ghent-data-charts PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
