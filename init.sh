if [ -d "build" ]; then
	rm -rf ./build
	mkdir ./build
fi

cd ./build
cmake ..

if [ ! -f "make-n-run.sh" ]; then
	touch ./make-n-run.sh
	echo "make && ./projek-akhir" > ./make-n-run.sh
	chmod +x ./make-n-run.sh
fi
