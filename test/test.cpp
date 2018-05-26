#include<bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
int a[100005];
int mark1[400005],mark2[400005];
struct node{
	int p2,p5,r;
}tree[400005];
struct node2{
	int p2,p5,l;
}lazy2[400005];
int pp2,pp5,t2,t5,n;
void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
struct node merge(struct node l,struct node r,long re)
{
	struct node ans;
	ans.p2 = l.p2 + r.p2;
	ans.p5 = l.p5 + r.p5;
	ans.r = re;
	return ans;
}
struct node3{
	int p2,p5;
}lazy[1000005],an[100005];
void build(int node,int s,int e)
{
	int lc = (node<<1),rc = lc+1;
	if(s == e){
		n = a[s];
		pp2 = pp5 = 0;
		while(n%2 == 0){
			pp2++;
			n = n>>1;
		}
		while(n%5 == 0){
			pp5++;
			n /= 5;
		}
	//	cout << s << " " << pp2 << " " << pp5 << endl;
		tree[node].p2 = pp2;
		tree[node].p5 = pp5;
		tree[node].r = 0;
		return;
	}
	int m = (s+e)>>1;
	build((lc),s,m);
	build(rc,m+1,e);
	tree[node] = merge(tree[(lc)], tree[rc],tree[node].r);
}
void update1(int node,int s,int e,int  l,int  r,int  p2,int  p5)
{
	int lc = (node<<1),rc = lc+1;
/*	if(tree[node].r == 1){
                if(s != e){
                        lazy[lc].p2 = lazy[lc].p5 = lazy[rc].p2 = lazy[rc].p5 = 0;
                       	mark1[lc] = mark1[rc] = 0;
                       	tree[lc].p2 = tree[lc].p5 = tree[(lc)+1].p2 = tree[(lc)+1].p5 = 0;
                        tree[lc].r = 1;
                        tree[rc].r = 1;
                }
                tree[node].r = 0;
               // cout << "q : "<< s << " " << e << " " << pp2 << " " << pp5 << " " << endl;
        }*/
//	cout << s << e;
	if(mark2[node] != 0){
                //mark1[node] = 0;
                tree[node].p2 = (lazy2[node].p2*(e-s+1));
                tree[node].p5 = (lazy2[node].p5*(e-s+1));
                
/*                t2 = 2;
                t5 = 5;
                pp2 = pp5 = 0;
                while(n/t2){
                        pp2 += (n/t2);
                        t2 *= 2;
                }
                while(n/t5){
                        pp5 += (n/t5);
                        t5 *= 5;
                }
                
                t2 = 2;
                t5 = 5;
               // pp2 = pp5 = 0;
                while(n/t2){
                        pp2 -= (n/t2);
                        t2 *= 2;
                }
                while(n/t5){
                        pp5 -= (n/t5);
                        t5 *= 5;
                }*/
		t2 = (e-lazy2[node].l + 1);
		t5 = (s- lazy2[node].l);
		pp2 = an[t2].p2 - an[t5].p2;
		pp5 = an[t2].p5 - an[t5].p5;
                tree[node].p2 += pp2;
                tree[node].p5 += pp5;
//                cout << s << " " << e << " " << tree[node].p2 << " " << tree[node].p5 << " " << endl;
                if(s != e){
                		lazy[lc].p2 = lazy[lc].p5 = lazy[rc].p2 = lazy[rc].p5 = 0;
                       	mark1[lc] = mark1[rc] = 0;
                        lazy2[(lc)].p2 = lazy2[node].p2;
                        lazy2[rc].p5 = lazy2[node].p5;
                        lazy2[(lc)].p5 = lazy2[node].p5;
                        lazy2[rc].p2 = lazy2[node].p2;
                        lazy2[(lc)].l = lazy2[node].l;
                        lazy2[rc].l = lazy2[node].l;
                        mark2[lc] = 1;
                        mark2[(lc)+1] = 1;
         //               mark1[lc] = 0;
           //             mark1[rc] = 0;
		}
				lazy2[node].p2 = lazy2[node].p5 = 0;
                mark2[node] = 0;
        }
	if(mark1[node] != 0){
                tree[node].p2 += (lazy[node].p2*(e-s+1));
                tree[node].p5 += (lazy[node].p5*(e-s+1));
		if(s != e){
			lazy[(lc)].p2 += lazy[node].p2;
			lazy[rc].p5 += lazy[node].p5;
			lazy[(lc)].p5 += lazy[node].p5;
                        lazy[rc].p2 += lazy[node].p2;
			mark1[lc] = 1;
			mark1[rc] = 1;
			
		}
//		cout <<"mark1 : " <<  s << " " << e << " " << pp2 << " " << pp5 << " " << endl;
		lazy[node].p2 = lazy[node].p5 = 0;
		mark1[node] = 0;
	}
	if(s > e || s > r || e < l){
		return;
	}
	if(s >= l && e <= r){
//		cout << "mark b :" << s << " " << e << " " << tree[node].p2 << " " << tree[node].p5 << endl;
		tree[node].p2 += (p2*(e-s+1));
		tree[node].p5 += (p5*(e-s+1));
//		cout << "mark :" << s << " " << e << " " << tree[node].p2 << " " << tree[node].p5 << endl;
		if(s != e){
			lazy[(lc)].p2 += p2;
			lazy[rc].p5 += p5;
			lazy[(lc)].p5 += p5;
                        lazy[rc].p2 += p2;
			mark1[rc] = 1;
			mark1[(lc)] = 1;
		}
		return;
	}
	int m = (s+e)>>1;
	update1((lc),s,m,l,r,p2,p5);
	update1(rc,m+1,e,l,r,p2,p5);
//		update1((lc),s,m,l,r,p2,p5);
//		update1(rc,m+1,e,l,r,p2,p5);
	tree[node] = merge(tree[(lc)],tree[rc],tree[node].r);
}
void update2(int node,int s,int e,int l,int r,int p2,int p5)
{
	int lc = (node<<1),rc = lc+1;
/*	if(tree[node].r == 1){
                if(s != e){
                        lazy[lc].p2 = lazy[lc].p5 = lazy[rc].p2 = lazy[rc].p5 = 0;
                        mark1[lc] = mark1[rc] = 0;
                        tree[lc].p2 = tree[lc].p5 = tree[(lc)+1].p2 = tree[(lc)+1].p5 = 0;
                        tree[lc].r = 1;
                        tree[rc].r = 1;
                }
                tree[node].r = 0;
        }*/
        if(mark2[node] != 0){
//		mark1[node] = 0;
                tree[node].p2 = (lazy2[node].p2*(e-s+1));
                tree[node].p5 = (lazy2[node].p5*(e-s+1));
/*		n = (e-lazy2[node].l + 1);
		t2 = 2;
		t5 = 5;
		pp2 = pp5 = 0;
		while(n/t2){
			pp2 += (n/t2);
			t2 *= 2;
		}
		while(n/t5){
			pp5 += (n/t5);
			t5 *= 5;
		}
		n = (s-lazy2[node].l);
                t2 = 2;
                t5 = 5;
               // pp2 = pp5 = 0;
                while(n/t2){
                        pp2 -= (n/t2);
                        t2 *= 2;
                }
                while(n/t5){
                        pp5 -= (n/t5);
                        t5 *= 5;
                }*/
//		cout << s << " " << e << " " << pp2 << " " << pp5 << " " << endl;
		t2 = (e-lazy2[node].l + 1);
		t5 = (s- lazy2[node].l);
		pp2 = an[t2].p2 - an[t5].p2;
		pp5 = an[t2].p5 - an[t5].p5;		
		tree[node].p2 += pp2;
		tree[node].p5 += pp5;
                if(s != e){
                	lazy[lc].p2 = lazy[lc].p5 = lazy[rc].p2 = lazy[rc].p5 = 0;
                       	mark1[lc] = mark1[rc] = 0;
                        lazy2[(lc)].p2 = lazy2[node].p2;
                        lazy2[rc].p5 = lazy2[node].p5;
                        lazy2[(lc)].p5 = lazy2[node].p5;
                        lazy2[rc].p2 = lazy2[node].p2;
			lazy2[(lc)].l = lazy2[node].l;
			lazy2[rc].l = lazy2[node].l;
                        mark2[lc] = 1;
                        mark2[(lc)+1] = 1;
//			mark1[lc] = 0;
//			mark1[rc] = 0;
                }
                lazy2[node].p2 = lazy2[node].p5 = 0;
                mark2[node] = 0;
        }
	if(mark1[node] != 0){
                tree[node].p2 += (lazy[node].p2*(e-s+1));
                tree[node].p5 += (lazy[node].p5*(e-s+1));
                if(s != e){
                        lazy[(lc)].p2 += lazy[node].p2;
                        lazy[rc].p5 += lazy[node].p5;
                        lazy[(lc)].p5 += lazy[node].p5;
                        lazy[rc].p2 += lazy[node].p2;
                        mark1[lc] = 1;
                        mark1[rc] = 1;
                }
                lazy[node].p2 = lazy[node].p5 = 0;
                mark1[node] = 0;
        }
        if(s > e || s > r || e < l){
                return;
        }
        if(s >= l && e <= r){
		tree[node].p2 = (p2*(e-s+1));
                tree[node].p5 = (p5*(e-s+1));
	/*	n = (e - l + 1);
                t2 = 2;
                t5 = 5;
                pp2 = pp5 = 0;
                while(n/t2){
                        pp2 += (n/t2);
                        t2 *= 2;
                }
                while(n/t5){
                        pp5 += (n/t5);
                        t5 *= 5;
                }
                n = (s - l);
                t2 = 2;
                t5 = 5;
               // pp2 = pp5 = 0;
                while(n/t2){
                        pp2 -= (n/t2);
                        t2 *= 2;
                }
                while(n/t5){
                        pp5 -= (n/t5);
                        t5 *= 5;
                }*/
		t2 = (e - l + 1);
		t5 = (s - l);
		pp2 = an[t2].p2 - an[t5].p2;
		pp5 = an[t2].p5 - an[t5].p5;
                tree[node].p2 += pp2;
                tree[node].p5 += pp5;
                if(s != e){
                	lazy2[(lc)].p2 = p2;
                        lazy2[rc].p5 = p5;
                        lazy2[(lc)].p5 = p5;
                        lazy2[rc].p2 = p2;
                        lazy2[(lc)].l = l;
                        lazy2[rc].l = l;
			lazy[lc].p2 = lazy[lc].p5 = lazy[rc].p2 = lazy[rc].p5 = 0;
			tree[lc].r = 1;
			tree[rc].r = 1;
                        mark2[lc] = 1;
                        mark2[(lc)+1] = 1;
      //                  lazy2[node].p2 = lazy2[node].p5 = 0;
		}
		lazy2[node].p2 = lazy2[node].p5 = 0;
		tree[node].r = 0;
                return;
        }
        int m = (s+e)/2;
        update2((lc),s,m,l,r,p2,p5);
        update2(rc,m+1,e,l,r,p2,p5);
        tree[node] = merge(tree[(lc)],tree[rc],tree[node].r);
}
struct node query(int node,int s,int e,int l,int r)
{
	int lc = (node<<1),rc = lc+1;
/*	if(tree[node].r == 1){
		if(s != e){
			lazy[lc].p2 = lazy[lc].p5 = lazy[rc].p2 = lazy[rc].p5 = 0;
            tree[lc].r = 1;
            tree[lc].p2 = tree[lc].p5 = tree[(lc)+1].p2 = tree[(lc)+1].p5 = 0;
            mark1[lc] = mark1[rc] = 0;
            tree[rc].r = 1;
		}
		tree[node].r = 0;
//		cout << "q : "<< s << " " << e << " " << pp2 << " " << pp5 << " " << endl;
	}*/
	if(s > e || s > r || e < l){
                struct node tm;
                tm.p2 = tm.p5 = tm.r = 0;
                return tm;
        }
	if(mark2[node] != 0){
  //              mark1[node] = 0;
                tree[node].p2 = (lazy2[node].p2*(e-s+1));
                tree[node].p5 = (lazy2[node].p5*(e-s+1));
 /*               n = (e-lazy2[node].l + 1);
                t2 = 2;
                t5 = 5;
                pp2 = pp5 = 0;
                while(n/t2){
                        pp2 += (n/t2);
                        t2 *= 2;
                }
                while(n/t5){
                        pp5 += (n/t5);
                        t5 *= 5;
                }
                n = (s-lazy2[node].l);
                t2 = 2;
                t5 = 5;
               // pp2 = pp5 = 0;
                while(n/t2){
                        pp2 -= (n/t2);
                        t2 *= 2;
                }
                while(n/t5){
                        pp5 -= (n/t5);
                        t5 *= 5;
                }*/
		t2 = (e-lazy2[node].l + 1);
		t5 = (s- lazy2[node].l);
		pp2 = an[t2].p2 - an[t5].p2;
		pp5 = an[t2].p5 - an[t5].p5;
                tree[node].p2 += pp2;
                tree[node].p5 += pp5;
//                cout << "mark q2 :" << s << " " << e << " " << tree[node].p2 << " " << tree[node].p5 << endl;
                if(s != e){
                		lazy[lc].p2 = lazy[lc].p5 = lazy[rc].p2 = lazy[rc].p5 = 0;
                       	mark1[lc] = mark1[rc] = 0;
                        lazy2[(lc)].p2 = lazy2[node].p2;
                        lazy2[rc].p5 = lazy2[node].p5;
                        lazy2[(lc)].p5 = lazy2[node].p5;
                        lazy2[rc].p2 = lazy2[node].p2;
                        lazy2[(lc)].l = lazy2[node].l;
                        lazy2[rc].l = lazy2[node].l;
                        mark2[lc] = 1;
                        mark2[(lc)+1] = 1;
                }
                lazy2[node].p2 = lazy2[node].p5 = 0;
                mark2[node] = 0;
	}
	if(mark1[node] != 0){
//				cout << "q : "<< s << " " << e << " " << pp2 << " " << pp5 << " " << endl;
                tree[node].p2 += (lazy[node].p2*(e-s+1));
                tree[node].p5 += (lazy[node].p5*(e-s+1));
                if(s != e){
                        lazy[(lc)].p2 += lazy[node].p2;
                        lazy[rc].p5 += lazy[node].p5;
                        lazy[(lc)].p5 += lazy[node].p5;
                        lazy[rc].p2 += lazy[node].p2;
                        mark1[lc] = 1;
                        mark1[(lc)+1] = 1;
                }
                lazy[node].p2 = lazy[node].p5 = 0;
                mark1[node] = 0;
        }
	if(l <= s && e <= r){
//		cout << "qqmark :" << s << " " << e << " " << tree[node].p2 << " " << tree[node].p5 << endl;
		return tree[node];
	}
	/*if(s > e || s > r || e < l){
                struct node tm; 
                tm.p2 = tm.p5 = tm.r = 0;
                return tm;
        }*/
	int m = (s+e)>>1;
	if(r <= m)
		return query((lc),s,m,l,r);
	else if(l > m)
		return query(rc,m+1,e,l,r);
	return merge(query((lc),s,m,l,r) , query(rc,m+1,e,l,r),0);
}
int main()
{	int n2,c,t,i,j,v,op,x,y;
	long long sum = 0;
	struct node ans;
	scanint(t);
	for(i = 2;i <= 100001;i++){
		n = i;
		t2 = 2;
                t5 = 5;
                pp2 = pp5 = 0;
                while(n/t2){
                        pp2 += (n/t2);
                        t2 *= 2;
                }
                while(n/t5){
                        pp5 += (n/t5);
                        t5 *= 5;
                }
/*                n = (s-lazy2[node].l);
                t2 = 2;
                t5 = 5;
               // pp2 = pp5 = 0;
                while(n/t2){
                        pp2 -= (n/t2);
                        t2 *= 2;
                }
                while(n/t5){
                        pp5 -= (n/t5);
                        t5 *= 5;
                }*/
		an[i].p2 = pp2;
		an[i].p5 = pp5;
	}
	while(t--){
	//	cout << "t : " << t << endl;
		sum = 0;
		scanint(n2);
		scanint(c);
		for(i = 0;i < 400005 ;i++){
			tree[i].p2 = tree[i].p5 = tree[i].r = 0;
			mark2[i] = mark1[i] = 0;
			lazy[i].p2 = lazy[i].p5 = lazy2[i].p2 = lazy2[i].p5 = lazy2[i].l = 0;
		}
		for(i = 1;i <= n2;i++){
			scanint(a[i]);
		}
		build(1,1,n2);	
		while(c--){
	//		cout <<"c : "  << c << " " << endl;
			scanint(op);
			if(op == 1){
				scanint(i);
				scanint(j);
				scanint(x);
			//	cout << c << endl;
				n = x;
                		pp2 = pp5 = 0;
                		while(n%2 == 0){
                        		pp2++;
                        		n = n>>1;
                		}
                		while(n%5 == 0){
                        		pp5++;
                        		n /= 5;
                		}
//				cout << pp2 << pp5 << endl;
				update1(1,1,n2,i,j,pp2,pp5);
			}
			else if(op == 2){
				scanint(i);
				scanint(j);
				scanint(y);
			//	cout << c << endl;
				n = y;
                                pp2 = pp5 = 0;
                                while(n%2 == 0){
                                        pp2++;
                                        n = n/2;
                                }
                                while(n%5 == 0){
                                        pp5++;
                                        n /= 5;
                                }
                                update2(1,1,n2,i,j,pp2,pp5);
			}
			else{
			//	cout << c << endl;
				scanint(i);
				scanint(j);
				ans = query(1,1,n2,i,j);
	//			cout << ans.p2 << " " <<ans.p5 << endl;
				sum += min(ans.p2,ans.p5);
			}
		}
		printf("%lld\n",sum);
	}
}
