#include <iostream>

using namespace std;

void parse_string ( const char * s, char words[100][100], int & word )
   {
   word = 0;            // current word number
   int i = -1;          // index into string 's'
   int chr = 0;         // char position in word
   bool inword = false; // in-word or not status

   // start-end of printable ascii
   const int uc[2] = {65,90};
   const int lc[2] = {97,122};

   do
      {
      i++;
      if ((s[i] >= uc[0] && s[i] <= uc[1]) || 
          (s[i] >= lc[0] && s[i] <= lc[1]))
         {
         if (!inword)
            {
            inword = true;
            chr = 0;
            }

         words[word][chr] = s[i];
         }

      else
         {
         if (inword)
            {
            inword = false;
            words[word][chr] = '\0';
            word++;
            }
         }
      chr++;
      }
   while (s[i] != '\0');
   
   }


int main (void)
   {
   const char aString[] = " one two three four    five six ";
   char words[100][100];
   int wordCount = 0;

   parse_string ( aString, words, wordCount );

   for (int i = 0; i < wordCount; ++i)
       {
       cout << "word[" << i << "]:" << words[i] << endl;
       }
   }
