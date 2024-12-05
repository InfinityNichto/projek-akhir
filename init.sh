if [ -d "build" ]; then
	rm -rf ./build
fi

mkdir ./build
cd ./build
cmake ..

if [ ! -f "make-n-run.sh" ]; then
	touch ./make-n-run.sh
	echo "make && ./projek-akhir" > ./make-n-run.sh
	chmod +x ./make-n-run.sh
fi
