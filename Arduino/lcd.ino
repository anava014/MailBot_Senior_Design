void draw()
{
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(5, 22, "Brians a");
    u8g.drawStr(24, 35, "FAG!");
}

void backlightOn(){
  digitalWrite(brightness, HIGH);
}

void backlightOff(){
  digitalWrite(brightness, LOW);
}

void drawStraight()
{
    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_unifont);
      u8g.drawStr(5, 22, "Going");
      u8g.drawStr(24, 35, "Straight!");
    }while(u8g.nextPage());
}

void drawString(const char *text)
{
    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_osr29r);
      u8g.drawStr(22, 40, text);
    }while(u8g.nextPage());
}

void drawString(String strText)
{
    const char* text = strText.c_str();
    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_osr29r);
      u8g.drawStr(22, 40, text);
    }while(u8g.nextPage());
}

void drawSmallString(String strText)
{
    const char* text = strText.c_str();
    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_profont10);
      u8g.drawStr(5, 10, text);
    }while(u8g.nextPage());
}



void drawDoubleString(const char *text, const char *secText)
{
    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_unifont);
      u8g.drawStr(5, 22, text);
      u8g.drawStr(5, 35, secText);
    }while(u8g.nextPage());
}

void drawHalt()
{
  u8g.firstPage();
  do{
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(5, 22, "Halting");
  }while(u8g.nextPage());
}
