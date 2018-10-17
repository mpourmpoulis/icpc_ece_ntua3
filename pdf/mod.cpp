inline int mod_add(int numb1,int numb2,int modulus)
{
	long long int temp=numb1;
	temp=temp+numb2;
	temp=temp%modulus;
	return  temp;
}
 
inline int mod_mul(int numb1,int numb2,int modulus)
{
	long long int temp=numb1;
	temp=temp*numb2;
	temp=temp%modulus;
	return (int) temp;	
}
 
 
inline int mod_exp(int base,int exp,int modulus)
{
	int result=1;
	while(exp>0){
		if(exp%2==1){
			result=mod_mul(result,base,modulus);
		}
		base=mod_mul(base,base,modulus);
		exp>>=1;
	}
	return result;	
}
 

 inline int mod_inv(int numb,int modulus)
{
	numb%=modulus;
	long long int  r[3],t[3],qinv;
	r[0]=modulus;
	r[1]=numb;
	t[0]=0;
	t[1]=1;	
	do{
		r[2]=r[0]%r[1];
		qinv=r[0]/r[1];
		t[2]=t[0]-qinv*t[1];
		r[0]=r[1];
		r[1]=r[2];
		t[0]=t[1];
		t[1]=t[2];		
	} while(r[1]!=0);
	long long int value=t[0];
	if(value>0) return (int) (value%modulus);
	else{
		value=(-1)*value;
		value%=modulus;
		value=modulus-value;
		return (int) value;
	}	
}



inline int gcd(int numb1,int numb2)
{
	while(numb1>0 && numb2>0){
		if(numb1>numb2) numb1=numb1%numb2;
		else numb2=numb2%numb1;
	}
	return numb1+numb2;
}
 

void CRT_compute_coeff(int p, vector<int> &divisor, vector<int> &CRT_coeff)
{
	CRT_coeff.clear(); CRT_coeff.resize(divisor.size());
	int Pr = divisor.size();
	if(Pr==1) CRT_coeff[0]=1;
	for(int i=0;i<Pr;i++){
		int temp=p/divisor[i];
		CRT_coeff[i]=temp*mod_inv(temp,divisor[i]);		
	}	
}
 
inline int Chinese_Remainder_Theorem(vector<int> &divisor,int p)
{
	long long int sum=0,temp; int Pr=divisor.size();
	vector<int> CRT_coeff;
	CRT_compute_coeff(p,divisor,CRT_coeff);
	for(int i=0;i<Pr;i++){
		temp = divisor[i];
		temp *= CRT_coeff[i];
		sum+=temp;
	}
	sum=sum%p;
	return (int) sum;
}



