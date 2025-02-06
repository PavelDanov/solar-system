@echo off

mkdir build
pushd build

cl -Zi ..\src\main.cpp "sfml-graphics-s-d.lib" "sfml-window-s-d.lib" "sfml-system-s-d.lib" "sfml-audio-s-d.lib" "sfml-network-s-d.lib" opengl32.lib freetype.lib winmm.lib gdi32.lib user32.lib Advapi32.lib openal32.lib flac.lib vorbisenc.lib vorbisfile.lib vorbis.lib ogg.lib /I "C:\Users\pid\Code\libs\SFML-2.6.1 - x64\include" -I "..\include" /D SFML_STATIC /MDd /link /LIBPATH:"C:\Users\pid\Code\libs\SFML-2.6.1 - x64\lib" /DEBUG

popd
