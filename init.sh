#!/bin/bash
if [ -d "build" ]; then
	rm -rf ./build
fi

mkdir ./build
cd ./build
cmake ..

if [ ! -f "make-n-run.sh" ]; then
	touch ./make-n-run.sh
	printf "#!/bin/bash\nmake && ./projek-akhir\n\ncounter=\$(<../build_counter)\n((counter++))\nprintf \"%%s\" \"\$counter\" > ../build_counter" > ./make-n-run.sh
	chmod +x ./make-n-run.sh
fi
