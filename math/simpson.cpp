// Para intervalo [0, 8], polinomio de a lo sumo grado 8, 2700 divisiones alcanzaron
// con error de a lo sumo 10e-5
double integral(double a, double b, int n=10000) {//O(n), n=cantdiv
	double area=0, h=(b-a)/n, fa=f(a), fb;
	forn(i, n){
		fb=f(a+h*(i+1));
		area+=fa+ 4*f(a+h*(i+0.5)) +fb, fa=fb;
	}
	return area*h/6.;}
