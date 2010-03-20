ecppc jquery.js
ecppc style.css
ecppc my_code.js
ecppc index.html

cat jquery.cpp | grep "* rawData" > jquery_.cpp
cat style.cpp | grep "* rawData" > style_.cpp
cat my_code.cpp | grep "* rawData" > my_code_.cpp
cat index.cpp | grep "* rawData" > index_.cpp


rm jquery.cpp style.cpp my_code.cpp index.cpp
