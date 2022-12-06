

struct init
	{
		char *fname;
		double (*fnct)();
	};
struct init arith_fncts[]={ 
		{"sin", sin},
		{"cos", cos},
		{"tan", tan},
		{"asin", asin},
		{"acos", acos},
		{"atan", atan},
		{"sinh", sinh},
		{"cosh", cosh},
		{"tanh", tanh},
		{"log10", log10},
		{"ln", log},
		{"exp", exp},
		{"sqrt", sqrt},
		{"ceil", ceil},
		{"floor", floor},
		{"fabs", fabs},
		{"pow", pow},
		{"fmod", fmod},
		{0, 0}
	};
