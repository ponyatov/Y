#include "interp.hpp"

sym::sym(string T, string V)	{ tag=T; value=V; 
	if (tag=="int") {
		ostringstream os; os << atoi(value.c_str()); value=os.str();
	}
}

sym::sym(sym* o)				{ tag=o->tag; value=o->value; }

string pad(int n) {
	string S;
	for (int i=0;i<n;i++) S+="\t";
	return S;
}

string sym::dump(int depth)	{ 
	string S = "\n"+pad(depth)+"<"+tag+":"+value+">";
	for ( vector<sym*>::iterator it= nest.begin(); it != nest.end(); it++)
		S += (*it)->dump(depth+1);
	return S;
}

sym* sym::eval()	{
	for ( vector<sym*>::iterator it= nest.begin(); it != nest.end(); it++)
		(*it) = (*it)->eval();
	if (tag=="op") {
		if (nest.size()==1) {
			if (value=="+") return nest[0]->pfxplus();
			if (value=="-") return nest[0]->pfxminus();
		}
		if (nest.size()==2) {
			if (value=="+") return nest[0]->add(nest[1]);
			if (value=="/") return nest[0]->div(nest[1]);
		}
	}
	return this;
}

sym* sym::pfxplus()	{ sym* s = new sym(this);
	if (s->tag!="int")
		s->value = "+"+s->value;
	return s; }

sym* sym::pfxminus()	{ sym* s = new sym(this);
	if (s->tag=="int") {
		ostringstream os; os << -atoi(s->value.c_str()); s->value=os.str();
	} else
		s->value = "-"+s->value;
	return s; }

sym* sym::add(sym* o)	{ sym* s = new sym(this);
	if (s->tag=="sym" && o->tag=="sym") s->value += o->value;
	if (s->tag=="int" && o->tag=="int") {
		ostringstream os; os << atoi(s->value.c_str())+atoi(o->value.c_str());
		s->value=os.str(); 
	}
	return s; }

sym* sym::div(sym* o)	{ sym* s = new sym(this);
	if (s->tag=="sym" && o->tag=="sym") s->value += "/"+o->value;
	if (s->tag=="int" && o->tag=="int") {
		ostringstream os; os << atoi(s->value.c_str())/atoi(o->value.c_str());
		s->value=os.str(); 
	}
	return s; }

void sym::app(sym* o)	{ nest.push_back(o); }

void yyerror(string err) {
	cout << "\n" << err << " # " << yylineno << " : [" << yytext << "]\n\n";
	cerr << "\n" << err << " # " << yylineno << " : [" << yytext << "]\n\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
   cout << "# " << argv[0] << "\n";
   return yyparse();
}

