#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <sstream>
#include <numeric>
#include <map>
#include <cmath>
#include <iomanip>
#include <climits>
#include <unordered_map>
using namespace std;
#define forn(i,n) for(int i=0;i<n;i++)
#define forn1(i,n) for(int i=1;i<=n;i++)
#define mp make_pair
#define pb push_back
#define ins insert
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int n,m;
vector<double>ptsX;
vector<double>ptsY;
vector<int>positions;
vector<int>bestPositions;
vector<double>bestErrors;
vector<double>errors;
bool comp(int x, int y){
	return errors[x]<errors[y];
}
bool comp2(int x,int y){
	return bestErrors[x]<bestErrors[y];
}
int main(){
	srand(time(NULL));
	cin>>n;
	cout<<setprecision(18);
	forn(i,n){
		double x,y;
		cin>>x>>y;
		ptsX.pb(x);
		ptsY.pb(y);
		positions.pb(i);
		errors.pb(0);
		bestPositions.pb(i);
		bestErrors.pb(0);
	}
	// according to lecture slides, we really only need 5 or 6 iterations for 95%, but we have greater confidence with more.
	// with 100 iterations, we are almost completely sure that we picked good data at least once (assuming 30% outliers): only 5.71e-30 probability to pick at least one outlier every time.
	double bestMedian=10e300;
	double median;
	double bestA,bestB;
	forn(i,100){
		int idx=rand()%n;
		int idx2=rand()%n;
		while(idx2==idx)idx2=rand()%n;
		double run=ptsX[idx]-ptsX[idx2];
		if(abs(run)==0.0)run=1e-9;
		double a=(ptsY[idx]-ptsY[idx2])/run;
		double b=ptsY[idx]-a*ptsX[idx];//in form y=ax+b
		forn(j,n){
			double terr=(abs(ptsY[j]-(a*ptsX[j]+b)));
			if(terr<1e-9)terr=0.0;
			errors[j]=terr;
		}
		sort(positions.begin(),positions.end(),comp);
		if(n%2==0){
			double leftMedian=errors[positions[n/2]];
			median=(leftMedian+errors[positions[n/2-1]])/2.0;
		}else{
			median=errors[positions[n/2]];
		}
		if(median<bestMedian){
			bestMedian=median;
			forn(j,n){
				bestPositions[j]=(positions[j]);
				bestErrors[j]=(errors[j]);
			}
		}
	}
	int lastIndexLessThanMedian=n/2-1;//0..lastIndex are used in the regression
	double sumX=0,sumXSq=0,sumXY=0,sumY=0,sum1=lastIndexLessThanMedian+1;
	sort(bestPositions.begin(),bestPositions.end(),comp2);
	forn(i,lastIndexLessThanMedian+1){
		sumX+=ptsX[bestPositions[i]];
		sumXSq+=ptsX[bestPositions[i]]*ptsX[bestPositions[i]];
		sumY+=ptsY[bestPositions[i]];
		sumXY+=ptsX[bestPositions[i]]*ptsY[bestPositions[i]];
	}
	double det=sumXSq*sum1-sumX*sumX;
	double a=(sum1*sumXY-sumX*sumY)/det;//inverting the matrix from online slides
	double b=(-sumX*sumXY+sumXSq*sumY)/det;
	cout<<a<<" "<<b<<endl;
	return 0;
}