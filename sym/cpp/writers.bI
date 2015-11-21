// writers

void W(char    c,bool to_file)	{ cout << c ;					// single char
	if (to_file&&curr_file) fprintf(curr_file->fh,"%c",c); }
void W(string  s,bool to_file)	{ cout <<  s;					// string
	if (to_file&&curr_file) fprintf(curr_file->fh,"%s",s.c_str()); }
void W(string *s,bool to_file)	{ cout << *s;					// string ptr
	if (to_file&&curr_file) fprintf(curr_file->fh,"%s",s->c_str()); }
void W(sym    *o,bool to_file)	{ cout << o->dump();			// symb.object
	if (to_file&&curr_file) fprintf(curr_file->fh,"%s",o->dump().c_str()); }
