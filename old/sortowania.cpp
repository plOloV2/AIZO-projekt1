#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<omp.h>
using namespace std;
vector<int> kop(vector<int> a, int x, int y){
    if(x*2+2!=y && a[x]<a[x*2+2]){
        swap(a[x], a[x*2+2]);
        if((x*2+2)*2+2<y-1) a=kop(a, x*2+2, y);
        else if((x*2+2)*2+1<y-1) a=kop(a, x*2+2, y);
    } 
    if(a[x]<a[x*2+1]){
        swap(a[x], a[x*2+1]);
        if((x*2+1)*2+2<y-1) a=kop(a, x*2+1, y);
        else if((x*2+1)*2+1<y-1) a=kop(a, x*2+1, y);
    }
    return a;
}
vector<int> bombelkowe(vector <int> a){
    int i=0;
    do{
        if(a[i]>a[i+1]){
            swap(a[i], a[i+1]);
            i=0;
        }
        else ++i;
    }
    while(i<a.size()-1);
    return a;
}
vector<int> qs(vector <int> a){
    if(a.size()<=1) return a;
    int x=a[0];
    vector <int> b, c;
    for(int i=1; i<a.size(); i++){
        if(a[i]<x) b.push_back(a[i]);
        else c.push_back(a[i]);
    }
    b=qs(b);
    c=qs(c);
    a.clear();
    for(int i=0; i<b.size(); i++) a.push_back(b[i]);
    a.push_back(x);
    for(int i=0; i<c.size(); i++) a.push_back(c[i]);
    return a;
}
vector<int> wstawianie(vector <int> a){
    vector <int> b;
    while(a.size()>0){
        b.push_back(a[a.size()-1]);
        for(int i=b.size()-1; i>0; i--){
            if(b[i]<b[i-1]) swap(b[i], b[i-1]);
            else break;
        }
        a.pop_back();
    }
    return b;
}
vector<int> wybor(vector <int> a){
    int x;
    for(int i=0; i<a.size()-1; i++){
        x=i;
        for(int j=i+1; j<a.size(); j++){
            if(a[j]<a[x]) x=j;
        }
        swap(a[i], a[x]);
    }
    return a;
}
vector<int> scal(vector <int> a){
    if(a.size()<=1) return a;
    vector <int> b, c;
    int x=a.size()/2;
    for(int i=0; i<x; i++) b.push_back(a[i]);
    for(int i=x; i<a.size(); i++) c.push_back(a[i]);
    b=scal(b);
    c=scal(c);
    a.clear();
    int ci=0, bi=0;
    while(bi<b.size() or ci<c.size()){
    	if(ci==c.size()){
    		for(; bi<b.size(); bi++) a.push_back(b[bi]);
    		break;
		}
		if(bi==b.size()){
    		for(; ci<c.size(); ci++) a.push_back(c[ci]);
    		break;
		}
        if(c[ci]>b[bi]){
            a.push_back(b[bi]);
            bi++;
        } 
        else{
            a.push_back(c[ci]);
            ci++;
        }
    }
    return a;
}
vector<int> stozek(vector <int> a){
    for(int i=a.size()/2-1; i>=0; i--) a=kop(a, i, a.size());
    for(int i=a.size()-1; i>1; i--){
        swap(a[i], a[0]);
        a=kop(a, 0, i);
    }
    swap(a[1], a[0]);
    return a;
}
int main(){
    vector <int> org, s1, s2, s3, s4, s5, s6;
    int a;
    fstream in;
    in.open("dane2.txt", ios::in);
    while(in>>a) org.push_back(a);
    in.close();
    cout<<"ilosc liczb: "<<org.size()<<endl;
    s1=org;
    s2=org;
    s3=org;
    s4=org;
    s5=org;
    s6=org;
    omp_set_num_threads(7);
    #pragma omp parallel
    {
        double cz=omp_get_wtime();
        if(omp_get_thread_num()==0 && org.size()<=10000) {
            s1=bombelkowe(s1);
            cz=omp_get_wtime()-cz;
            #pragma omp critical 
                cout<<"Babelkowe - "<<cz<<endl;
        }
        if(omp_get_thread_num()==1) {
            s2=qs(s2);
            cz=omp_get_wtime()-cz;
            #pragma omp critical 
                cout<<"Quick sort - "<<cz<<endl;
        }
        if(omp_get_thread_num()==2 && org.size()<=100000) {
            s3=wstawianie(s3);
            cz=omp_get_wtime()-cz;
            #pragma omp critical 
                cout<<"Przez wstawianie - "<<cz<<endl;
        }
        if(omp_get_thread_num()==3 && org.size()<=100000) {
            s4=wybor(s4);
            cz=omp_get_wtime()-cz;
            #pragma omp critical 
                cout<<"Przez wybor - "<<cz<<endl;
        }
        if(omp_get_thread_num()==4) {
            s5=scal(s5);
            cz=omp_get_wtime()-cz;
            #pragma omp critical 
                cout<<"Przez scalanie - "<<cz<<endl;
        }
        if(omp_get_thread_num()==5 && org.size()<=10000) {
            s6=stozek(s6);
            cz=omp_get_wtime()-cz;
            #pragma omp critical 
                cout<<"Kopcowe - "<<cz<<endl;
        }
        if(omp_get_thread_num()==6) {
            sort(org.begin(), org.end());
            cz=omp_get_wtime()-cz;
            #pragma omp critical 
                cout<<"Referencyjne - "<<cz<<endl;
        }
    }
    if(org.size()<=1000){
        if(org==s1 && org==s2 && org==s3 && org==s4 && org==s5 && org==s6) cout<<"Udalo sie!\n";
        else cout<<"O nie!\n";
    }
    if(org.size()<=10000 && org.size()>1000){
        if(org==s2 && org==s3 && org==s4 && org==s5 && org==s6) cout<<"Udalo sie!\n";
        else cout<<"O nie!\n";
    }
    if(org.size()>10000 && org.size()<=100000){
        if(org==s2 && org==s3 && org==s4 && org==s5) cout<<"Udalo sie!\n";
        else cout<<"O nie!\n";
    }
	if(org.size()>100000){
		if(org==s2 && org==s5) cout<<"Udalo sie!\n";
        else cout<<"O nie!\n";
	}
    return 0;
}