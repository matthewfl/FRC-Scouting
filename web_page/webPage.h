#ifndef _webPage_h
#define _wePage_h

#define C_QUOTE(q) #q



#define rawData WebHomePage 
#include "index_.cpp"
#undef rawData

#define rawData WebJSCodeMy 
#include "my_code_.cpp"
#undef rawData

#define rawData WebJsCodeJquery
#include "jquery_.cpp"
#undef rawData

#define rawData WebCSS
#include "style_.cpp"
#undef rawData

#undef C_QUOTE


#endif
