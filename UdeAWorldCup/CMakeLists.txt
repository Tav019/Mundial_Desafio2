cmake_minimum_required(VERSION 3.16)

project(UdeAWorldCup LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(UdeAWorldCup main.cpp
    equipo.h equipo.cpp
    grupo.h grupo.cpp
    recursos.h recursos.cpp
    bombo.h bombo.cpp
    torneo.h torneo.cpp
    fecha.h fecha.cpp
    estadisticajugador.h estadisticajugador.cpp
    confederacion.h confederacion.cpp)

include(GNUInstallDirs)
install(TARGETS UdeAWorldCup
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
