qt_add_executable(ghent-data-charts
    dbservice.hpp
    dbservice.cpp
    mainwidget.hpp
    mainwidget.cpp
    main.cpp
    model.hpp
    model.cpp
)

target_link_libraries(ghent-data-charts PRIVATE Qt6::Widgets Qt6::Sql)

set_target_properties(ghent-data-charts PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
