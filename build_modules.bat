cd modules

for /D %%i in (*) do (
    cd "%%i/build"
    cmake -DOUTPUT_TYPE=dl -DCMAKE_BUILD_TYPE=Release .. && cmake --build . -j 4 --config Release
    cd "Release/"
    echo D|xcopy /S /Q /Y /F "%%i.glx" "../../../../build/modules/"
    cd ../..
    echo F|xcopy /S /Q /Y /F config.yml "../../build/modules/%%i.yml"
    cd ..
)
