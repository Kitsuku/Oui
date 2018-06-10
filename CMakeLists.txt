cmake_minimum_required(VERSION 3.10)
IF(WIN32)
  project(bomberman)
  include_directories(include include/Menu include/Button include/Graphics include/objects include/Irrlicht json-develop/single_include/nlohmann /user/X11R6/include)
  set (SRC
    src/main.cpp
    src/checkDie.cpp
    src/getObjectAtPosition.cpp
    src/usefullGestionFct.cpp)
  set (MENUSRC
    src/menu/AMenu.cpp
    src/menu/MainMenu.cpp
    src/menu/MultiMenu.cpp
    src/menu/OptionMenu.cpp
    src/menu/PauseMenu.cpp
    src/menu/PlayMenu.cpp
    src/menu/SoloMenu.cpp)
  set (MAPSRC
    src/map/Map.cpp
    src/map/play.cpp)
  set (OBJECTSRC
    src/objects/AObject.cpp
    src/objects/Bomb.cpp
    src/objects/Bonus.cpp
    src/objects/UnbrWall.cpp
    src/objects/Wall.cpp)
  set (BUTTONSRC
    src/button/AButton.cpp
    src/button/BackGroundMultiButton.cpp
    src/button/BackGroundSoloButton.cpp
    src/button/DisplayCommandButton.cpp
    src/button/ExitButton.cpp
    src/button/GroundMultiButton.cpp
    src/button/GroundSoloButton.cpp
    src/button/LoadButton.cpp
    src/button/MultiButton.cpp
    src/button/OptionButton.cpp
    src/button/PauseSoundButton.cpp
    src/button/PlayButton.cpp
    src/button/QuitButton.cpp
    src/button/ResumeButton.cpp
    src/button/ReturnMmButton.cpp
    src/button/RulesButton.cpp
    src/button/SaveButton.cpp
    src/button/SaveGestionButton.cpp
    src/button/SoloButton.cpp
    src/button/SoundButton.cpp
    src/button/StartMultiButton.cpp
    src/button/StartSoloButton.cpp)
  set (GRAPHICSRC
    src/graphics/Graphics.cpp
    src/graphics/MyEvent.cpp
    src/graphics/MyException.cpp)
  set (CHARACSRC
    src/characters/ACharacter.cpp
    src/characters/Player.cpp
    src/characters/IA.cpp)
  set (LDFLAGS gdi32 winspool comdlg32 ole32 oleaut32 uuid odbc32 odbccp32 opengl32 opengl32)
  link_directories(./lib/Win32-visualStudio)
  find_library(LIBIRR NAMES Irrlicht.lib PATHS ./lib/Win32-visualStudio)
  add_executable(bomberman ${SRC} ${MENUSRC} ${BUTTONSRC} ${GRAPHICSRC} ${MAPSRC} ${OBJECTSRC} ${CHARACSRC})
  target_link_libraries(bomberman ${LIBIRR} ${LDFLAGS})
  install(TARGETS bomberman DESTINATION ${bomberman_SOURCE_DIR})
ELSE(WIN32)
  project(bomberman)
  include_directories(include include/Menu include/Button include/Graphics include/objects include/Irrlicht json-develop/single_include/nlohmann /user/X11R6/include)
  set (SRC
    src/main.cpp
    src/checkDie.cpp
    src/getObjectAtPosition.cpp
    src/usefullGestionFct.cpp)
  set (MENUSRC
    src/menu/AMenu.cpp
    src/menu/MainMenu.cpp
    src/menu/MultiMenu.cpp
    src/menu/OptionMenu.cpp
    src/menu/PauseMenu.cpp
    src/menu/PlayMenu.cpp
    src/menu/SoloMenu.cpp)
  set (BUTTONSRC
    src/button/AButton.cpp
    src/button/BackGroundMultiButton.cpp
    src/button/BackGroundSoloButton.cpp
    src/button/DisplayCommandButton.cpp
    src/button/ExitButton.cpp
    src/button/GroundMultiButton.cpp
    src/button/GroundSoloButton.cpp
    src/button/LoadButton.cpp
    src/button/MultiButton.cpp
    src/button/OptionButton.cpp
    src/button/PauseSoundButton.cpp
    src/button/PlayButton.cpp
    src/button/QuitButton.cpp
    src/button/ResumeButton.cpp
    src/button/ReturnMmButton.cpp
    src/button/RulesButton.cpp
    src/button/SaveButton.cpp
    src/button/SaveGestionButton.cpp
    src/button/SoloButton.cpp
    src/button/SoundButton.cpp
    src/button/StartSoloButton.cpp
    src/button/StartMultiButton.cpp)
  set (GRAPHICSRC
    src/graphics/Graphics.cpp
    src/graphics/MyEvent.cpp
    src/graphics/MyException.cpp)
  set (MAPSRC
    src/map/Map.cpp
    src/map/play.cpp)
  set (OBJECTSRC
    src/objects/AObject.cpp
    src/objects/Bomb.cpp
    src/objects/Bonus.cpp
    src/objects/UnbrWall.cpp
    src/objects/Wall.cpp)
  set (CHARACSRC
    src/characters/ACharacter.cpp
    src/characters/Player.cpp
    src/characters/IA.cpp)
  set (LDFLAGS GL Xxf86vm Xext X11 Xcursor)
  find_library(LIBIRR NAMES libIrrlicht.a PATHS ./lib)
  add_executable(bomberman ${SRC} ${MENUSRC} ${BUTTONSRC} ${GRAPHICSRC} ${MAPSRC} ${OBJECTSRC} ${CHARACSRC})
  link_directories(./lib)
  target_link_libraries(bomberman ${LIBIRR} ${LDFLAGS})
  install(TARGETS bomberman DESTINATION ${bomberman_SOURCE_DIR})
ENDIF(WIN32)
