#include <windows.h>
#include <stdio.h>
#include <dos.h>


#include <math.h>
#include <time.h>
#include <stdlib.h>


/*! Play Music by BEEEEPS.
 * \param[in]  none.
 * \param[out] none.
 */
void Music(void);

/*! Play Pianino by buttons in keyboard
 * \param[in]  frequency  - int freq;
 * \param[out] none.
 */
int Pianino(int freq);

/*! Hack for first programm.
 * \param[in]  void.
 * \param[out] none.
 */
int Hack_1(void);

/*! Hack for second programm.
 * \param[in]  void.
 * \param[out] none.
 */
int Hack_2(void);

namespace mk5 //IFK namespace44
{
    struct line
    {
        long len = 0;
        char* str = nullptr;
    };
}


/* MAIN FUNCTION */
int main(void) {

  printf("Today is a great day...\n");// I will")
  Sleep(1500);
  printf("And all that's I want to say: beep beep\n");
  Sleep(1600);
  Hack_1();
  Hack_2();

  //Music();

  //Play piano
  while (1)
    if (Pianino(200))
      break;

  printf("PASS_1 and PASS_2 hacked!...\n");
  Sleep(1600);

  return 0;
} /* End of 'main' function */

void Music(void) {
    Beep(196, 200);
    Beep(293, 200);
    Beep(392, 300);

    Beep(196, 200);
    Beep(293, 200);
    Beep(392, 600);

    Beep(100, 200);

    Beep(196, 200);
    Beep(293, 200);
    Beep(392, 500);

    Beep(100, 100);

    Beep(196, 200);
    Beep(293, 200);
    Beep(329, 500);

    //
    Beep(196, 200);
    Beep(293, 200);
    Beep(392, 300);

    Beep(196, 200);
    Beep(293, 200);
    Beep(392, 600);

    Beep(100, 200);

    Beep(196, 200);
    Beep(293, 200);
    Beep(329, 300);

    Beep(100, 100);

    Beep(196, 200);
    Beep(293, 300);
    Beep(329, 800);

    //
    Beep(196, 200);
    Beep(293, 200);
    Beep(392, 300);

    Beep(196, 200);
    Beep(293, 200);
    Beep(392, 600);

    Beep(100, 200);

    Beep(196, 200);
    Beep(293, 200);
    Beep(329, 300);

    Beep(100, 100);

    Beep(196, 200);
    Beep(293, 300);
    Beep(329, 800);

    //
    Beep(196, 200);
    Beep(293, 200);
    Beep(392, 300);

    Beep(196, 200);
    Beep(293, 200);
    Beep(392, 600);

    Beep(100, 200);

    Beep(196, 200);
    Beep(293, 200);
    Beep(329, 300);

    Beep(100, 100);

    Beep(196, 200);
    Beep(293, 300);
    Beep(329, 800);


    // g a b b a g a g a b b b
    // b 246

    Beep(50, 30); //
    Beep(196, 400); //G
    Beep(220, 200); //a
    Beep(246, 400); //B
    Beep(50, 30); //
    Beep(246, 300); //B
    Beep(50, 30); //
    Beep(220, 200); //A
    Beep(196, 200); //G
    Beep(220, 700); //a
    Beep(196, 800); //G
    Beep(50, 30); //
    Beep(196, 200); //G
    Beep(220, 400); //a
    Beep(246, 400); //b
    Beep(50, 30); //
    Beep(246, 1000);


    Beep(50, 30); //
    Beep(196, 400); //G
    Beep(220, 200); //a
    Beep(246, 400); //B
    Beep(50, 30); //
    Beep(246, 300); //B
    Beep(50, 30); //
    Beep(220, 200); //A
    Beep(196, 200); //G
    Beep(220, 700); //a
    Beep(196, 800); //G
    Beep(50, 30); //
    Beep(196, 200); //G

    Beep(50, 30); //
    Beep(196, 500); //G
    Beep(220, 400); //a
    Beep(50, 30); //
    Beep(220, 1000); //a
    Beep(50, 30); //



    Beep(50, 30); //
    Beep(196, 400); //G
    Beep(220, 200); //a
    Beep(246, 400); //B
    Beep(50, 30); //
    Beep(246, 300); //B
    Beep(50, 30); //
    Beep(220, 200); //A
    Beep(196, 200); //G
    Beep(220, 700); //a
    Beep(196, 800); //G
    Beep(50, 30); //
    Beep(196, 200); //G
    Beep(220, 400); //a
    Beep(246, 400); //b
    Beep(50, 30); //
    Beep(246, 1000);


    Beep(50, 30); //
    Beep(196, 400); //G
    Beep(220, 200); //a
    Beep(246, 400); //B
    Beep(50, 30); //
    Beep(246, 300); //B
    Beep(50, 30); //
    Beep(220, 200); //A
    Beep(196, 200); //G
    Beep(220, 700); //a
    Beep(196, 800); //G
    Beep(50, 30); //
    Beep(196, 200); //G

    Beep(50, 30); //
    Beep(196, 500); //G
    Beep(220, 400); //a
    Beep(50, 30); //
    Beep(220, 1000); //a
    Beep(50, 30); //


    Beep(50, 30); //
    Beep(196, 600); //G
    Beep(220, 300); //a
    Beep(50, 30); //
    Beep(220, 300); //a
    Beep(220, 800); //a

    Beep(50, 30); //
    Beep(196, 2000); //G

    Beep(50, 30); //
    Beep(190, 10); //
    Beep(196, 1500); //G

    //--------------------------------------
    // Break down
    Beep(258, 200); //c
    Beep(50, 30); //
    Beep(261, 400);
    Beep(50, 30); //
    Beep(261, 400);
    Beep(50, 30); //
    Beep(261, 400);

    Beep(50, 30); //
    Beep(293, 700); //d

    Beep(329, 500); //e^
    Beep(293, 200);
    Beep(329, 500);

    // Break
    Beep(258, 200); //c
    Beep(50, 30); //
    Beep(261, 400);
    Beep(50, 30); //
    Beep(261, 400);
    Beep(50, 30); //
    Beep(261, 400);

    Beep(50, 30); //
    Beep(293, 700); //d

    Beep(329, 500); //e^
    Beep(293, 200);
    Beep(329, 500);

    //-------------
    Beep(50, 30); //
    Beep(196, 600); //G
    Beep(220, 300); //a
    Beep(50, 30); //
    Beep(220, 300); //a
    Beep(220, 800); //a

    Beep(50, 30); //
    Beep(196, 2000); //G

    Beep(50, 30); //
    Beep(190, 10); //
    Beep(196, 1500); //G
}

/*! Read strings from file function.
 * \param[in]  name of file               - char *FileName;
 * \param[in]  buffer of file             - mk5::line *buf;
 * \param[out] count of strokes.
 */
int ReadStrBuf(const char* FileName, mk5::line* buf)
{
    FILE* file = fopen(FileName, "rb");

    if (file == NULL)
    {
        printf("We can't find the file...\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    buf->len = ftell(file);

    rewind(file);

    buf->str = new char[buf->len];
    fread(buf->str, sizeof(char), buf->len - 1, file);

    fclose(file);
    
    return 0;
} /* End of 'ReadStrBuf' function */

/*! Write buffer in the file function.
 * \param[in]  structure of string  - mk5::line str;
 * \param[in]  name of file         - char *FileName;
 * \param[out] none.
 */
void WriteStrBuf(mk5::line str, const char* FileName)
{
    FILE* F = fopen(FileName, "wb");

    if (F == NULL)
    {
        printf("We can't create the file...\n");
        abort();
    }

    fwrite(str.str, str.len, sizeof(char), F);

    fclose(F);
}/* End of 'WriteStrBuf' function */

/*! Play Pianino by buttons in keyboard
 * \param[in]  frequency  - int freq;
 * \param[out] none.
 */
int Pianino(int freq) {
    switch (getchar()) {
    case 'a': 
        system("cls");
        Beep((DWORD)500, freq);
        break;
    case 's':
        system("cls");
        Beep((DWORD)523.25, freq);
        break;
    case 'd': 
        system("cls");
        Beep((DWORD)587.33, freq);
        break;
    case 'f': 
        system("cls");
        Beep((DWORD)659.26, freq);
        break;
    case 'g': 
        system("cls");
        Beep((DWORD)698.46, freq);
        break;
    case 'h': 
        system("cls");
        Beep((DWORD)783.99, freq);
        break;
    case 'j': 
        system("cls");
        Beep((DWORD)880, freq);
        break;
    case 'k': 
        system("cls");
        Beep((DWORD)987.77, freq);
        break;
    case '0':
        return 1;
    }
    return 0;
}

/*! Hack for first programm.
 * \param[in]  void.
 * \param[out] none.
 */
int Hack_1(void) {
    mk5::line buffer = { 0, nullptr };
    ReadStrBuf("S:\\DOC\\T06_HA\\PASS_1.COM", &buffer);
    buffer.str[0x127] = 0x74;
    buffer.str[0x12e] = 0x93;
    buffer.str[0x12f] = 0x02;
    WriteStrBuf(buffer, "S:\\DOC\\T06_HA\\PASS_1.COM");

    delete[] buffer.str;
    return 0;
} /* End of 'Hack_1' function */

/*! Hack for second programm.
 * \param[in]  void.
 * \param[out] none.
 */
int Hack_2(void) {

    mk5::line buffer = { 0, nullptr };
    ReadStrBuf("S:\\DOC\\T06_HA\\PASS_2.COM", &buffer);
    buffer.str[0x127] = 0x75;
    buffer.str[0x13B] = 0x74;
    WriteStrBuf(buffer, "S:\\DOC\\T06_HA\\PASS_2.COM");

    delete[] buffer.str;
    
    return 0;
} /* End of 'Hack_2' function */