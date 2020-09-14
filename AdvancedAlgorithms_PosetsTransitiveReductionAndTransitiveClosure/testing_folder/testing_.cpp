

#include "poset.h"

int NO_VERTEX=-1;

poset::poset(): n(0)
{
   n = 0;
}

poset::poset(int num): n(num)
{
}


//bool **Less;Less = new bool* [n];


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
      Less[i]=new bool[n];
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
       // A bunch of stuff you write
       Less[u][v] = true; //since relation is identified above
       Covers[u][v] = true;
       f >> v;  
     }
     f >> u;
   }

   f.close();

  // More stuff you write 
   //   Covers = Less;
  
   //   printf ("\n\n");
   //   printf ("note: you are only seeing these visualaizations if you entered n that is small enough to not disturb readability");
   //  printf ("\n\n");

   // printf ("visualaize Less array \n"); 
   // poset::VISUALIZE_MATRICES(Less); 
   // printf("\n\n"); 
   

   //   printf ("visualaize Covers array \n");
   // poset::VISUALIZE_MATRICES(Covers);
   // printf("\n\n");



     // transitive reduction
     for (int k = 0; k < n; k++)
     {
       for (int i = 0; i < n; i++)
       {
	 if (Covers[i][k])
	 {
	   for (int j = 0; j < n; j++)
	   {
	     if (Covers[k][j])
	     {
	       Covers[i][j] = false;
	     }
	   }
	 }
       }
     }
     //  printf ("visualaize Covers array AFTER TRANSITIVE REDUCTION HAVE BEEN APPLIED \n");
     // poset::VISUALIZE_MATRICES(Covers);
     // printf("\n\n");
     
   
   // transitive closure
   for (int k = 0; k < n; k++)
   {
     // check vertices
     for (int i = 0; i < n; i++)
     {
       for (int j = 0; j < n; j++)
       {
	 Less[i][j] = Less[i][j] || (Less[i][k] && Less[k][j]);
       }
     }
   }

   // printf ("visualaize Less array AFTER TRANSITIVE CLOSURE HAVE BEEN APPLIED  \n");
   // poset::VISUALIZE_MATRICES(Less);
   // printf("\n\n");

     


   // assign values to UpperIdeal
     for (int i = 0; i < n; i++) 
     {
       int j = 0;
       int r = 0; 
       int *a = new int[n];
       while (j < n)
       {	 
	 if (Less[i][j] == true)
	 { 
	   a[r] = j;
	   UpperIdeal[i].push_back(a[r]);
	   r++;
	 }
	 j++;
       }
     }

   
     for (int i = 0; i < n; i++)
     {
       int j = 0;
       int r = 0;
       int *b = new int[n];
       while (j < n)
       {
	 if (Covers[i][j] == true)
	 {
	   b[r] = j;
	   UpperCover[i].push_back(b[r]);
	   r++;
	 }
	 j++;
       }
     }

     for (int i = 0; i < n; i++)
     {
       int j = 0;
       int r = 0;
       int *c = new int[n];
       while (j < n)
       {
	 if (Covers[i][j] == true)
	 {
	   //          a[r] = j;
	   LowerCover[j].push_back(i);
	   r++;
	 }
	 j++;
       }
     }

     for (int i = 0; i < n; i++)
     {
       int j = 0;
       int r = 0;
       int *d = new int[n];
       while (j < n)
       {
	 if (Less[i][j] == true)
	 {
	   d[r] = i;
	   LowerIdeal[j].push_back(d[i]);
	   r++;
	 }
	 j++;
       }
     }

  
   /*
   int** arr = new int*[n];
   for(int i = 0; i < n; i++)
   {
     arr[i] = new int[col];
   }
   
   */

     //        std::cout << "CONTENTS OF UPPER COVER ARE " << endl;
     //  poset::VISUALIZE_VECTORS(UpperCover, n);


     //    std::cout << "CONTENTS OF UPPER IDEAL ARE " << endl;
     // poset::VISUALIZE_VECTORS(UpperIdeal);
       


     //  std::cout << "CONTENTS OF LOWER COVER ARE " << endl;
     // poset::VISUALIZE_VECTORS(LowerCover);

     //          std::cout << "CONTENTS OF LOWER IDEAL ARE " << endl;
     //     poset::VISUALIZE_VECTORS(LowerIdeal);
   

   cout << "Read complete." << endl;
   poset::posetWrite(fn);
   return 1;
}




int main (int argc, char** argv) 
{
  poset obj;
  char fn [80] ;
  cout << "enter a file name" <<endl;
  cin >> fn; 

  obj.poset::posetRead(fn);

  return 1;
}



poset::~poset()
{


}

void poset::VISUALIZE_MATRICES(bool** matrix)
{

  int i,j;
  
  for (i = 0; i < n; i++) //loop through printing elements like a matrix
  {
    for (j = 0; j < n; j++)
    {
      printf ("%i \t", matrix[i][j]);
     
    }
    printf ("\n");
  } 
}

void poset:: VISUALIZE_VECTORS(vector <int> *vec)
{

  for (int i =0; i < n; i++)
  {
    vector<int>::iterator it = vec[i].begin();
    
    while (it != UpperCover[i].end())
    {
      cout <<" " << *it;      
      it++;
    }
    cout << " " << n <<endl;
  }
  cout << n << endl;
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

