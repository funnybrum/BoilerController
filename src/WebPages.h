#include "Main.h"

const char CONFIG_PAGE[] PROGMEM = R"=====(
<HTML>
 <HEAD>
   <TITLE>Boiler Controller</TITLE>
 </HEAD>
 <BODY>
  <form action="/settings" method="get">
   %s<br><br>
   %s<br><br>
   %s<br><br>
   <br><br>
   <input type="submit" value="Save" style='width: 150px;'>
   &nbsp;&nbsp;&nbsp;
   <a href="/reboot">
    <button type="button" style='width: 150px;'>Restart</button>
   </a>
  </form>
 </BODY>
</HTML>
)=====";

const char GET_JSON[] PROGMEM = R"=====({
 "heating":%s,
 "buffer_supply_temp": %.1f,
 "buffer_return_temp": %.1f,
 "ufh_supply_temp": %.1f,
 "ufh_return_temp": %.1f,
 "rssi": %d
})=====";
