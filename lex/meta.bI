meta = next + file @ 'meta.hpp'
meta += 
'#ifndef _H_META
										// ==== metainformation ====
#define _H_META

#define TITLE "'+TITLE+'"
#define ABOUT "'+ABOUT+'"
#define AUTHOR "'+AUTHOR+'"
#define LICENSE "'+LICENSE+'"
#define GITHUB "'+GITHUB+'"
#define AUTOGEN "/***** DO NOT EDIT: this file was autogened by bI *****/"
#define LOGO "'+LOGO+'"
#define COLOR "'+COLOR+'"

#endif // _H_META
'
