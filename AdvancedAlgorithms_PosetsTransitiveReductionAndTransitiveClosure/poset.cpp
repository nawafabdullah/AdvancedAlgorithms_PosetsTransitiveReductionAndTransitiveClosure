/***************************************************************
/*            poset.cpp
/*            by Nawaf Alharbi
/*            Sept 2019
/*
/*            reads a poset in from a file
/*            builds list representations for the 
/*            transitive closure (UpperIdeal and LowerIdeal
/*            and transitive reduction (UpperCover and LowerCover)
/*            provides poset access routines
/*            
/*            
/*********************************************************************/

// #include <queue>  // used in BFS
#include "poset.h"

int NO_VERTEX=-1;

poset::poset(): n(0)
{
   n = 0;
}

poset::poset(int num): n(num)
{
}


int poset::posetRead(char *fn)
{
   ifstream f;
   int v,u;
   
   f.open(fn);
   if (!f) { 
      cerr<<"File not openable. "<<endl; return 0;
      }
   f >> n;   
   LowerIdeal = new vector<int>[n]; // vector of all elements less than
                                    // indexed element, in the poset
   UpperIdeal = new vector<int>[n]; // all elements greater than in poset
   LowerCover= new vector<int>[n];  // all elements covering indexed elt
   UpperCover= new vector<int>[n];  // all elements that cover indexed elt
   Less = new bool* [n];            // Less is nxn array of bool 
   Covers = new bool* [n];

   for (int i=0; i<n; i++) {        // Less[u][v] means u<v in the poset
     Less[i]=new bool[n];           // Construct initial tables within the array 
     Covers[i]=new bool[n];         
     for (int j=0; j<n; j++) {
         Less[i][j]=false;
         Covers[i][j]=false;
      }
   }
   
   cout << "Reading " << n <<  " nodes..." << endl;
   if (n>100000) { cerr<<"n too large: "<<n<<endl; return 0;} // arbitrary

   f >> u;

   while (u<n && f)
   {
     f >> v; 
     while (v <n && f) {
       Less[u][v] = true; //since relation is identified above
       Covers[u][v] = true;
       f >> v;  
     }
     f >> u;
   }

   f.close(); 
 
   
   // transitive closure
   for (int k = 0; k < n; k++)
   {
     // check vertices
     for (int i = 0; i < n; i++)
     {
       for (int j = 0; j < n; j++)
       {
	 if (i==j || i ==k || j == k) continue;    
	 Less[i][j] = Less[i][j] || (Less[i][k] && Less[k][j]);
       }
     }
   }

   // transitive reduction
   for (int k = 0; k < n; k++)
   {
     for (int i = 0; i < n; i++)
     {
       for (int j = 0; j < n; j++)
       {     	     
	 if (i==j || i ==k || j == k) continue;
	 if (Covers[i][j])
	 {
	   if (Less[i][k] && Less[k][j]) 	        
           {             
	     Covers[i][j] = false;
	   }
	 }
       }
     }
   }
    

   // assign values to UpperIdeal, LowerIdeal, UpperCover, LowerCover vectors as per Less array 
   for (int i = 0; i < n; i++) 
   {	 
     for (int j = 0; j < n ; j++)
     {  
       if (Less[i][j] == true)
       { 
		UpperIdeal[i].push_back(j);
		LowerIdeal[j].push_back(i); 
       }
       if (Covers[i][j] == true)
       {
	   	UpperCover[i].push_back(j);
		LowerCover[j].push_back(i); 
       }
     }
   }

   cout << "Read complete." << endl;
   poset::posetWrite(fn);
   return 1;
}


int poset::posetWrite(char *fn)
{
   cout << "Writing transitive closure and transitive reductions..." << endl;
   ofstream o;

   // write transitive closure file
   o.open((string(fn) + ".tclose").c_str());

   o << n << endl;

   for (int u=0; u<n; u++) {
      o << u;

      vector<int>::iterator currneighb = UpperIdeal[u].begin();

      while (currneighb != UpperIdeal[u].end())
      {
         o << " " << *currneighb;
         currneighb ++;
      }

      o << " " << n << endl;
   }

   o << n << endl;

   o.close();

   // write transitive reduction file
   o.open((string(fn) + ".treduc").c_str());

   o << n << endl;

   for (int u=0; u<n; u++) {
     o << u;

     vector<int>::iterator currneighb = UpperCover[u].begin();
     
     while (currneighb != UpperCover[u].end())
       {
         o << " " << *currneighb;
         currneighb ++;
       }

      o << " " << n << endl;
   }

   o << n << endl;

   o.close();

   cout << "Write complete." << endl;

   return 1;
}

poset::~poset()
{

  // free memory reserved for vectord
  for(int i =0; i < n; i++)
  {
    UpperCover[i].clear();
    UpperIdeal[i].clear();
    LowerCover[i].clear();
    LowerIdeal[i].clear();
  }
    delete[] UpperCover;
    delete[] UpperIdeal;
    delete[] LowerCover;
    delete[] LowerIdeal;

    // free memory reserved for arrays
  for(int i = 0; i<n; i++)
  {
    delete [] Less[i]; 
    delete [] Covers[i];
  }
  delete [] Less;
  delete [] Covers;
      
} 



bool poset::lessThan(int u, int v)
{
  if (u<v) 
  {
    return 1;
  }
  return 0;  
}


// call print_node on each node in the poset
void poset::printPoset()
{
   for (int v=0; v<n; v++)
   {
        listLowerIdeal(v);
        cout << endl;
   }
}


void poset::listLowerIdeal(int v)
{
  vector <int>::iterator it = LowerIdeal[v].begin();
  while(it != LowerIdeal[v].end())
  {
    cout << " " << *it;
    it++;
  } 
}





	
