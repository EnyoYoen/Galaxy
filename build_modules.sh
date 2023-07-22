cd modules
for d in *; do
    if [ -d "$d" ]; then
        cd "$d/build"
        cmake -DOUTPUT_TYPE=dl -DCMAKE_BUILD_TYPE=Release .. && cmake --build . -j 4
        cp "$d.glx" ../../../build/modules/
        cd ..
        cp config.yml "../../build/modules/$d.yml"
        cd ..
    fi
done
