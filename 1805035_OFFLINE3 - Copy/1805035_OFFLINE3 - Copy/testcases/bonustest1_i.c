int z;
int foo(int a, int b){

	if(a+b <= 5){
		println(z);
		return 7;
	}
	
	int x;
	x=foo(a-2,b-1) + 2*foo(a-1,b-2);
	println(x);
	return x;
}
 
 
int main(){
	int i,j,k;
	i = 7;
	j = 3;
	z=7;
	k = foo(i,j);
	println(k);
 
	return 0;
}
