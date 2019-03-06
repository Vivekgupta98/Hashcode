#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define EB emplace_back
#define MP make_pair
#define all(o) (o).begin(), (o).end()
#define mset(m,v) memset(m,v,sizeof(m))
#define fr(i,n) for(lli i=0;i<(n);++i)
#define rep(i,a,b) for(lli i=a;i<=b;++i)
#define per(i,a,b) for(lli i=a;i>=b;i--)
#define remin(a,b) (a=min((a),(b)))
#define remax(a,b) (a=max((a),(b))) 
#define sz(x) (lli)(x).size()
#define endl '\n'
typedef long long lli;        typedef long double ld;
typedef pair<lli,lli> ii;     typedef vector<lli> vi;
typedef vector<ii> vii;       typedef vector<vi> graph;
long long MOD=1000000007;     long double EPS=1e-9;
#ifndef ONLINE_JUDGE
#define debarr(a,n) cerr<<#a<<" : ";for(int i=0;i<n;i++) cerr<<a[i]<<" "; cerr<<endl;
#define debmat(mat,row,col) cerr<<#mat<<" :\n";for(int i=0;i<row;i++) {for(int j=0;j<col;j++) cerr<<mat[i][j]<<" ";cerr<<endl;}
#define pr(...) dbs(#__VA_ARGS__, __VA_ARGS__)
template <class S, class T>ostream& operator <<(ostream& os, const pair<S, T>& p) {return os << "(" << p.first << ", " << p.second << ")";}
template <class T>ostream& operator <<(ostream& os, const vector<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const unordered_set<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const unordered_map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const set<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const multiset<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T> void dbs(string str, T t) {cerr << str << " : " << t << "\n";}
template <class T, class... S> void dbs(string str, T t, S... s) {int idx = str.find(','); cerr << str.substr(0, idx) << " : " << t << ","; dbs(str.substr(idx + 1), s...);}
template <class T> void prc(T a, T b) {cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n";}
#else
#define pr(...) {}
#define debarr(a,n) {}
#define debmat(mat,row,col) {}
#endif
lli binpow(lli b,lli p,lli mod){lli ans=1;b%=mod;for(;p;p>>=1){if(p&1)ans=ans*b%mod;b=b*b%mod;}return ans;}

void pre(){

}

typedef pair<vector<int>,vector<int>> slide;

vector< pair<char,vector<string>> > photo;
vector<slide> Hor,Ver;
map<string,int> mp;

vector<int> unite(vector<int> &a,vector<int> &b){
    vector<int> v(sz(a)+sz(b));
    auto it=set_union(all(a),all(b),v.begin());                
    v.resize(it-v.begin());
    return v;                 
}

vector<int> diff(vector<int> &a,vector<int> &b){
    vector<int> v(sz(a)+sz(b));
    auto it=set_difference(all(a),all(b),v.begin());                
    v.resize(it-v.begin());
    return v;
}

vector<int> intersect(vector<int> &a,vector<int> &b){
    vector<int> v(sz(a)+sz(b));
    auto it=set_intersection(all(a),all(b),v.begin());                
    v.resize(it-v.begin());
    return v;
}

slide merge(slide a1,slide a2){
    slide a3;
    a3.F.EB(a1.F[0]);
    a3.F.EB(a2.F[0]);
    a3.S=unite(a1.S,a2.S);
    return a3;
}   

lli score(slide a1,slide a2){
    return min({sz(intersect(a1.S,a2.S)),sz(diff(a2.S,a1.S)),sz(diff(a1.S,a2.S))});
}   

void CalculateScore(vector<slide> temp){
    lli Score=0;
    rep(i,1,sz(temp)-1){
        Score+=score(temp[i],temp[i-1]);
    }
    pr(Score);
}

void printOrder(vector<slide> temp){
    cout<<sz(temp)<<endl;
    fr(i,sz(temp)){
        fr(j,sz(temp[i].F)){
            cout<<temp[i].F[j]<<" ";
        }
        cout<<endl;
    }
}

template<class node>
struct SegT{
#define mid ((l+r)>>1)
    int n;
    node *t;
    SegT(int n):n(n){t=new node[4*n+10];}
    void build(int id,int l,int r){
        if(l==r){
            t[id]=1;return;
        }
        build(id<<1,l,mid);
        build(id<<1|1,mid+1,r);
        t[id]=t[id<<1]+t[id<<1|1];
    }
    void update(int id,int l,int r,int pos){
        if(pos<l||pos>r)return;
        if(l==r){
            assert(t[id]==1);
            t[id]=0;return;
        }
        update(id<<1,l,mid,pos);
        update(id<<1|1,mid+1,r,pos);
        t[id]=t[id<<1]+t[id<<1|1];
    }   
    node query(int id,int l,int r,int k){
        if(l==r){
            return l;
        }
        if(k<=t[id<<1])return query(id<<1,l,mid,k);
        else return query(id<<1|1,mid+1,r,k-t[id<<1]);
    }
#undef mid
};


void Ver_stat(){
    random_shuffle(all(Ver));

    int n=sz(Ver);
    if(n==0)return;

    SegT<int> st(n);
    st.build(1,0,n-1);

    for(int i=0;i<n/2;i++){

        int curelem=st.query(1,0,n-1,1);

        int bb=2;
        int scc=-1;

        int lo=2,hi=n-2*i;

        fr(_t,1000){
            int pp=(rand()%(hi-lo+1))+lo;
            pp=st.query(1,0,n-1,pp);
            lli t_t=sz(unite(Ver[pp].S,Ver[curelem].S));
            if(t_t>scc){
                scc=t_t;
                bb=pp;
            }
        }

        Hor.EB(merge(Ver[curelem],Ver[bb]));

        st.update(1,0,n-1,curelem);
        st.update(1,0,n-1,bb);
    }

}


void Hor_stat(){
    random_shuffle(all(Hor));
    int n=sz(Hor);
    vector<slide> temp;
    SegT<int> st(n);
    st.build(1,0,n-1);
    st.update(1,0,n-1,0);

    temp.EB(Hor[0]);
    int last=0;

    for(int i=0;i<n-1;i++){
        int lo=1,hi=n-1-i;

        int bb=1;
        int scc=-1;
        fr(_t,1000){
            int pp=(rand()%(hi-lo+1))+lo;
            pp=st.query(1,0,n-1,pp);
            lli t_t=score(Hor[last],Hor[pp]);
            if(t_t>scc){
                scc=t_t;
                bb=pp;
            }
        }
        temp.EB(Hor[bb]);
        st.update(1,0,n-1,bb);
        last=bb;
    }
    Hor=temp;
}

void solve(){
    lli n;
    cin>>n;
    photo.resize(n);
    fr(i,n){
        cin>>photo[i].F;
        int x;
        cin>>x;
        fr(j,x){
            string taz;
            cin>>taz;
            photo[i].S.EB(taz);
            mp[taz];
        }
    }
    int cc=1;
    for(auto &v:mp){
        v.S=cc++;
    }
    fr(i,n){
        if(photo[i].F=='H'){
            slide tt;
            tt.F.EB(i);
            for(auto xx:photo[i].S){
                tt.S.EB(mp[xx]);
            }
            sort(all(tt.S));Hor.EB(tt);
        }else{
            slide tt;
            tt.F.EB(i);
            for(auto xx:photo[i].S){
                tt.S.EB(mp[xx]);
            }
            sort(all(tt.S));Ver.EB(tt);
        }
    }
    
    vector<slide> sVer=Ver;
    vector<slide> sHor=Hor;

        int seeee=rand();
        pr(seeee);
        srand(seeee);
        Ver_stat();
        Hor_stat();
        CalculateScore(Hor);
    
    printOrder(Hor);
}

signed main(){
    srand(time(0));
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    freopen("b.txt","r",stdin);
    freopen("bout.txt","w",stdout);
    pre();lli t=1;//cin>>t;
    for(lli i=1;i<=t;i++){
        //cout<<"Case #"<<i<<": ";
        solve();
    }
}