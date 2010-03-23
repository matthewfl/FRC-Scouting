
if [ ! -e load ]
then
	g++ -Wall load.cpp -o load
fi

./load WebHomePage index.html index_.cpp
./load WebJsCodeJquery jquery.js jquery_.cpp
./load WebJSCodeMy my_code.js my_code_.cpp
./load WebCSS style.css style_.cpp
