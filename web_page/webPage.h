#ifndef _webPage_h
#define _wePage_h

#define C_QUOTE(q) #q



static const char * WebHomePage = 
#include "index.html"
  ;

static const char * WebJSCodeMy = 
#include "my_code.js"
  ;

#define rawData WebJsCodeJquery
#include "jquery_.cpp"
#undef rawData

#define rawData WebCSS
#include "style_.cpp"
#undef rawData

#undef C_QUOTE


#endif
