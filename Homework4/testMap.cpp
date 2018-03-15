    #include "Map.h"
    #include <iostream>
    #include <string>
    #include <cassert>

    using namespace std;

    void test()
    {
        Map<int, double> mid;
        Map<string, int> msi;
        assert(msi.empty());
        assert(msi.size() == 0);
        assert(msi.insert("Hello", 10));
        assert(mid.insert(10, 3.5));
        assert(msi.update("Hello", 20));
        assert(mid.update(10, 4.75));
        assert(msi.insertOrUpdate("Goodbye", 30));
        assert(msi.erase("Goodbye"));
        assert(mid.contains(10));
        int k;
        assert(msi.get("Hello", k));
        string s;
        assert(msi.get(0, s, k));
        Map<string, int> msi2(msi);
        msi2.swap(msi);
        msi2 = msi;
        combine(msi,msi2,msi);
        combine(mid,mid,mid);
        subtract(msi,msi2,msi);
        subtract(mid,mid,mid);
    }

    int main()
    {
        test();
        cout << "Passed all tests" << endl;



        int count = 0;
        const int N = 10;
	bool hasCommunicatedWith[N][N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			hasCommunicatedWith[i][j] = i;
	
	int numIntermediaries[N][N];
	for (int i = 0; i < N; i++)
	{
	    numIntermediaries[i][i] = -1;  // the concept of intermediary
				           // makes no sense in this case
	    for (int j = 0; j < i; j++)
	    {

	        if (i == j)
	            continue;
	        numIntermediaries[i][j] = 0;
	        for (int k = 0; k < N; k++)
	        {
	        		        	        count++;

	            if (k == i  ||  k == j)
	                continue;
		    if (hasCommunicatedWith[i][k]  &&  hasCommunicatedWith[k][j])
	        	numIntermediaries[i][j]++;
	        	
	        }
	        numIntermediaries[j][i] = numIntermediaries[i][j];
	    }
	}

	cout << count << endl;

    }
