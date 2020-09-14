/***************
/* testing posets 
/*
/* Nawaf Alharbi
/* Sep 2019
/*
/*
/***************/



#include "poset.h"
#include <iostream>

char getcommand();
void printmenu();
bool processcommand(char cmd, poset &G);

int main()
{
   poset P;

   printmenu();

   char cmd = getcommand();
   while (processcommand(cmd, P)) { 
      cout << endl;
      cmd = getcommand();
   }

}

char getcommand()
{
   //cout << "Enter your command choice (F(ile), A(dd), R(emove), L(ower Ideal), U(pper Ideal), D(ebug Display), H(help), Q(uit))" << endl;
   cout << "Enter your command choice (F(ile), D(ebug Display), H(help), Q(uit))" << endl;
   char cmd;
   cin >> cmd;
   cmd = toupper(cmd);
   switch (cmd) {
      case 'F':
//      case 'A':
//      case 'R':
//      case 'L':
//      case 'U':
      case 'D':
      case 'H':
      case 'Q': return cmd;
      default:  cout << "You have entered an invalid command" << endl;
                return getcommand();
   }
}

void printmenu()
{
   cout << "Enter F to read a DAG (poset) from a file," << endl;
//   cout << "   or A to add a < relation," << endl;
//   cout << "   or R to remove a < relation," << endl;
//   cout << "   or L to list the lower covers of a vertex," << endl;
//   cout << "   or U to list all elements > a given element," << endl;
   cout << "   or D to for debug data display," << endl;
   cout << "   or H for help," << endl;
   cout << "   or Q to quit." << endl;
}

bool processcommand(char cmd, poset &P)
{
   int d; int x;  
   int s, u, v;
   char fn[80];
   switch (cmd) {
      case 'F': cout << "File to read: ";
		   cin >> fn;
		   P.posetRead(fn); 
         break;
/*
      case 'A': cout << "Enter two elements u v (adding u<v): ";
		   cin >> u >> v; 
		   if (u<0 || u>=P.numElements() || v<0 || v>=P.numElements() ) 
			   cout << "Error, out of range.\n";
		   else
			   P.addCover(u,v); 
		      cout << endl;
            break;
      case 'R': cout << "Enter two elements u v (removing u<v): ";
		   cin >> u >> v; 
		   if (u<0 || u>=P.numElements() || v<0 || v>=P.numElements() ) 
			   cout << "Error, out of range.\n";
		   else
			   P.removeCover(u,v); 
		      cout << endl;
            break;
      case 'L': cout << "Element number to list lower covers of: ";
		   cin >> s;
		   if (s<0 || s>=P.numElements()) 
			   cout << "Error, out of range.\n";
		   else
			   //P.listLowerCovers(s); 
		      cout << endl;
            break;
      case 'U': cout << "Element number to list upper ideal of: ";
		   cin >> s;
		   if (s<0 || s>=P.numElements()) 
			   cout << "Error, out of range.\n";
		   else
			   // P.listIdeal(s); 
		      cout << endl;
            break;
*/
      case 'D': P.printPoset(); 
                break;
      case 'H': printmenu(); 
                break;
      default:  return false;
   }
   return true;
}

