string s = "hola mundo feliz.";
regex r("^hola(\\smundo (\\w+\\.))$");
if (regex_match(s, r))
	cout << "match" << endl;
smatch sm;
if (regex_match(s, sm, r))
	for (auto &m: sm)
		cout << "[" << m << "]" << endl;
/* match
   [hola mundo feliz.]
   [ mundo feliz.]
   [feliz.] */
