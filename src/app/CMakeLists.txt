qt_add_executable(ghent-data-charts
    basechartwidget.hpp
    basechartwidget.cpp
    dbservice.hpp
    dbservice.cpp
    districtpopulationdensitychart.hpp
    districtpopulationdensitychart.cpp
    districtpopulationsizechart.hpp
    districtpopulationsizechart.cpp
    mainwidget.hpp
    mainwidget.cpp
    main.cpp
    model.hpp
    model.cpp
    citypopulationchart.hpp citypopulationchart.cpp
)

target_link_libraries(ghent-data-charts PRIVATE Qt6::Widgets Qt6::Sql Qt6::Charts)

set_target_properties(ghent-data-charts PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
