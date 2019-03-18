cd ./demo
g++ -g -c main.cpp
g++ -g -c plugin.cpp

if [ ! -d "libfoo.so" ]; then
	cp _foo.template foo.cpp
	g++ -Wall -fPIC -c foo.cpp
	g++ -shared foo.o -o libfoo.so
fi

g++ main.o plugin.o -ldl -rdynamic -Wl,-R./ -o main_exe

rm -rf lib*

./main_exe

