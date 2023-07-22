cd modules

for /d %i in (*) do (
    @echo %i%
    cd %i%\build
    cmake -DOUTPUT_TYPE=dl -DCMAKE_BUILD_TYPE=Release .. && cmake --build . -j 4
    xcopy %i%.glx ..\..\..\build\modules\
    cd ..
    xcopy config.yml ..\..\build\modules\%i%.yml
    cd ..
)
