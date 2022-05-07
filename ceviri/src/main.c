#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include <string.h>
#include "dllist.h"
#include "jval.h"


 void  Dosyaya_Yazma( Dllist lt ) // dllist output.txt bastıran fonksiyon 
 {
      FILE *dosya;
      dosya=fopen("txt/output.txt","w");
      int i=0;
      Dllist dt;
      dt=lt->flink;
      while (dt!=lt)
      {
          if(i%10==0){fprintf(dosya,"\n");} // 10 satırda bir alt satıra geçme
          fprintf(dosya,"%s " ,dt->val.s);
          dt=dt->flink;
          i++;
     }
   fclose(dosya);
 
 }



int main(int argc, char **argv)
{
  
    if (argc != 4) 
    { 
     fprintf(stderr, "Eksik Parametre \n"); exit(1);
    }
      IS is1;
      IS is2;
      Dllist dl;
      int i;
      int j;
      int taranan=0;
      int kontrol=0;
      int karsilasti=0;
      dl= new_dllist();
      is1=new_inputstruct(argv[2]);
      is2=new_inputstruct(argv[3]);
      if (is1==NULL)
      {
        printf("dosya icerigi boş...");
        exit(1);
      }
      if (is2==NULL)
      {
        printf("Sozluk icerigi bos");
        exit(1);
      } 
 
    if (strcmp(argv[1],"tr")==0 && strcmp(argv[2],"txt/input.txt")==0 && strcmp(argv[3],"txt/sozluk.txt")==0 )
    {
     //buraya tr yi eng cevirme    
         
       while(get_line(is1) >= 0) 
       {
          for (i = 0; i < is1->NF; i++) 
          {  
            is2=new_inputstruct(argv[3]);// getline degerini sıfırlmak için tekrar newledim
            while (get_line(is2)>=0)
             { 
                for(j=0; j< is2->NF; j++)
                {  
                 if (strcmp(is1->fields[i],is2->fields[j])!=0)
                  {
                    //input degeri sozluk txt herhangi bir satırında bulunmadıgında dongünün bir sonrasına geçecek
                   continue;  
                  }
                  else if(strcmp(is1->fields[i],is2->fields[j])==0)
                  {         
                     dll_append(dl,new_jval_s(strdup(is2->fields[j-1]))); // dlliste ekleme
                      taranan++;
                     break; //ekleme işlemi gercekleştiginde döngüyü kıracak
                  }                                               
                }                             
            } 
             if (kontrol==taranan)
             {
                dll_append(dl,new_jval_s(strdup(is1->fields[i]))); // döngüde karşılıgı cıkmazsa bırda input verisini output yazacak              
             } 
               kontrol=taranan;
     
             jettison_inputstruct(is2);
             karsilasti++;                         
          }                              
       }
   

        printf("Karşılaştırılan  Kelime Sayısı : %d\n\n",karsilasti );  
        printf("Çeviri Başarılı Kelime Sayısı : %d\n\n",taranan); 
        printf("Çeviri yapılmamış Kelime sayısı:%d\n\n",karsilasti-taranan); 
        printf("Çıktı Metin Belgesi(output.txt),txt klasörü içindedin...\n");
        
        Dosyaya_Yazma(dl);
        // belleğe iade etme ve değerleri sıfırlama
        jettison_inputstruct(is1);
        free_dllist(dl);
         i=0;
         j=0;
         taranan=0;
         kontrol=0;
         karsilasti=0;

     

    }
     else if (strcmp(argv[1],"eng")==0 && strcmp(argv[2],"txt/input.txt")==0 && strcmp(argv[3],"txt/sozluk.txt")==0)
    {
      // buraya eng yi tr ceviren 

       while(get_line(is1) >= 0) 
       {
          for (i = 0; i < is1->NF; i++) 
          {  
            is2=new_inputstruct(argv[3]);// getline degerini sıfırlmak için tekrar newledim
            while (get_line(is2)>=0)

             { 
                for(j=0; j< is2->NF; j++)
                {  
                 if (strcmp(is1->fields[i],is2->fields[j])!=0)
                  {
                    //printf("degismedi\n");
                   continue;
                         
                  }
                  else if(strcmp(is1->fields[i],is2->fields[j])==0)
                  {    
                                   
                     dll_append(dl,new_jval_s(strdup(is2->fields[j+1])));
                     //printf ("%s \n",is2->fields[j-1]); 
                      taranan++;
                      
                     break;
                  }                
                                
                }
                               
            } 
             if (kontrol==taranan)
             {
                dll_append(dl,new_jval_s(strdup(is1->fields[i])));
               
             } 
               kontrol=taranan;

              
              
             jettison_inputstruct(is2);
             karsilasti++;                         

          }
                                 
       }
   
        printf("Karşılaştırılan  Kelime Sayısı : %d\n\n",karsilasti );  
        printf("Çeviri Başarılı Kelime Sayısı : %d\n\n",taranan); 
        printf("Çeviri yapılmamış Kelime sayısı:%d\n\n",karsilasti-taranan); 
        printf("Çıktı Metin Belgesi(output.txt),txt klasörü içindedin...\n");       
        Dosyaya_Yazma(dl);
         jettison_inputstruct(is1);
        free_dllist(dl);
    }
    else {printf("Lutfen Girdiginiz Parametreleri kontrol ediniz\n"); printf("ornek:bin/ceviri tr txt/input.txt txt/sozluk.txt gibi olmali \n"); }
 
   return 0;
}
