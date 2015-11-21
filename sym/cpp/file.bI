// file manipulation

File::File(string V,string M):sym("file",V) {		// create file [Mode="r/w"]
	assert(fh=fopen(V.c_str(),M.c_str()));}
File::~File() { fclose(fh); }						// close file
File *curr_file = NULL;								// current out file for W()
