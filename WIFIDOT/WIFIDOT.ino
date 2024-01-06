#include <WiFi.h>
#include <WiFiManager.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Turn on debug statements to the serial output
#define  DEBUG  0

#if  DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTX(x) Serial.println(x, HEX)
#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTX(x)
#endif

#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES	8

#define CLK_PIN   18  // or SCK
#define DATA_PIN  23  // or MOSI
#define CS_PIN    21  // or SS

// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// WiFi Server object and parameters
WiFiServer server(80);

// Scrolling parameters
uint8_t frameDelay = 25;  // default frame delay value
textEffect_t  scrollEffect = PA_SCROLL_LEFT;

// Global message buffers shared by Wifi and Scrolling functions
#define BUF_SIZE  512
char curMessage[BUF_SIZE];
char newMessage[BUF_SIZE];
bool newMessageAvailable = false;

const char WebResponse[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";

const char WebPage[] =
  "<!DOCTYPE html>\n"
  "<html>\n"
  "<head>\n"
  "<meta name='viewport' content='width=device-width, initial-scale=1'>\n"
  "<title>Smart Notice Board</title>\n"
  "<script>\n"
  "strLine = '';\n"
  "\n"
  "function SendData() {\n"
  "  nocache = '/&nocache=' + Math.random() * 1000000;\n"
  "  var request = new XMLHttpRequest();\n"
  "  strLine = '&MSG=' + document.getElementById('data_form').Message.value;\n"
  "  strLine = strLine + '/&SD=' + document.getElementById('data_form').ScrollType.value;\n"
  "  strLine = strLine + '/&I=' + document.getElementById('data_form').Invert.value;\n"
  "  strLine = strLine + '/&SP=' + document.getElementById('data_form').Speed.value;\n"
  "  request.open('GET', strLine + nocache, false);\n"
  "  request.send(null);\n"
  "}\n"
  "</script>\n"
  "<style>\n"
  "  body {\n"
  "    font-family: Arial, sans-serif;\n"
  "    margin: 10px;\n"
  "    padding: 10px;\n"
  "  }\n"
  "  \n"
  "  .container {\n"
  "    max-width: 600px;\n"
  "    margin: 0 auto;\n"
  "    text-align: center;\n"
  "  }\n"
  "  \n"
  "  p {\n"
  "    font-size: 30px;\n"
  "    margin-top: 10px;\n"
  "  }\n"
  "  \n"
  "  form {\n"
  "    margin-top: 10px;\n"
  "    display: inline-block;\n"
  "    text-align: left;\n"
  "    width: 60%;\n"
  "  }\n"
  "  \n"
  "  input[type='text'] {\n"
  "    padding: 10px;\n"
  "    font-size: 16px;\n"
  "    width: 100%;\n"
  "    margin-bottom: 20px;\n"
  "    box-sizing: border-box;\n"
  " }\n"

  "  label {\n"
  "    font-size: 16px;\n"
  "   margin-bottom: 10px;\n"
  "    display: block;\n"
  "  }\n"

  "  input[type='radio'] {\n"
  "    margin-right: 10px;\n"
  "  }\n"

  "  input[type='submit'] {\n"
  "    padding: 10px 20px;\n"
  "    font-size: 18px;\n"
  "    background-color: #3F51B5;\n"
  "    color: #fff;\n"
  "    border: 0;\n"
  "    margin-top: 5px;\n"
  "    cursor: pointer;\n"
  "  }\n"

  "  @media only screen and (max-width: 600px) {\n"
  "    form {\n"
  "      width: 100%;\n"
  "    }\n"
  "  }\n"
  "</style>\n"
  "</head>\n"
  "<body>\n"
  "  <div class='container'>\n"
  "    <p><b>Smart Notice Board with ESP8266</b></p>\n"
  "    <h3><b><a href='https://iotprojectsideas.com'>https://iotprojectsideas.com</a></b></h3>\n"
  "  <form id='data_form' name='frmText'>\n"
  " <label>Message:<br><input type='text' name='Message' maxlength='255'></label>\n"
  "  <br><br>\n"
  "  <label>Invert:</label><br>\n"
  "  <input type = 'radio' name = 'Invert' value = '0' checked> Normal \n"
  "  <input type = 'radio' name = 'Invert' value = '1'> Inverse \n"
  "  <br><br>\n"
  "  <label>Scroll Type:</label><br>\n"

  " <input type='radio' name='ScrollType' value='L' checked>Left \n"
  "<input type='radio' name='ScrollType' value='R'>Right \n"
  "<br><br>\n"

  "<label>Speed:</label><br>\n"
  "<div style='display: flex; justify-content: space-between;'>\n"
  "<span style='text-align: left;'>Fast</span>\n"
  "<span style='text-align: right;'>Slow</span>\n"
  "</div>\n"
  "<input type='range' name='Speed' min='10' max='200'>\n"
  "<br><br>\n"

  "<input type='submit' value='Send Data' onclick='SendData()'>\n"
  "</form>\n"
  "<style>\n"
  "body {\n"
  "  font-family: Arial, sans-serif;\n"
  "  text-align: center;\n"
  "}\n"

  "form {\n"
  "  display: inline-block;\n"
  "  text-align: left;\n"
  "  padding: 20px;\n"
  "  background-color: #f2f2f2;\n"
  "  border: 1px solid #ccc;\n"
  "  border-radius: 5px;\n"
  "  box-shadow: 2px 2px 5px #bbb;\n"
  "}\n"

  "label {\n"
  "  display: block;\n"
  "  margin-bottom: 10px;\n"
  "  font-weight: bold;\n"
  "}\n"

  "input[type='text'], input[type='range'] {\n"
  "  width: 100%;\n"
  "  padding: 10px;\n"
  "  margin-bottom: 2px;\n"
  "  box-sizing: border-box;\n"
  "  border: 1px solid #ccc;\n"
  "  border-radius: 5px;\n"
  "  font-size: 16px;\n"
  "}\n"

  "input[type='submit'] {\n"
  "  padding: 10px 20px;\n"
  "  background-color: #4CAF50;\n"
  "  color: white;\n"
  "  border: none;\n"
  "  border-radius: 5px;\n"
  "  font-size: 16px;\n"
  "  cursor: pointer;\n"
  "}\n"

  "input[type='submit']:hover {\n"
  " background-color: #3e8e41;\n"
  "}\n"

  "@media (max-width: 600px) {\n"
  "form {\n"
  "width: 90%;\n"
  "}\n"
  "}\n"
  "</style>\n"
  "</body>\n"
  "</html>\n";

const char *err2Str(wl_status_t code)
{
  switch (code)
  {
    case WL_IDLE_STATUS:    return ("IDLE");           break; // WiFi is in process of changing between statuses
    case WL_NO_SSID_AVAIL:  return ("NO_SSID_AVAIL");  break; // case configured SSID cannot be reached
    case WL_CONNECTED:      return ("CONNECTED");      break; // successful connection is established
    case WL_CONNECT_FAILED: return ("CONNECT_FAILED"); break; // password is incorrect
    case WL_DISCONNECTED:   return ("CONNECT_FAILED"); break; // module is not configured in station mode
    default: return ("??");
  }
}

uint8_t htoi(char c)
{
  c = toupper(c);
  if ((c >= '0') && (c <= '9')) return (c - '0');
  if ((c >= 'A') && (c <= 'F')) return (c - 'A' + 0xa);
  return (0);
}

void getData(char *szMesg, uint16_t len)
// Message may contain data for:
// New text (/&MSG=)
// Scroll direction (/&SD=)
// Invert (/&I=)
// Speed (/&SP=)
{
  char *pStart, *pEnd;      // pointer to start and end of text

  // check text message
  pStart = strstr(szMesg, "/&MSG=");
  if (pStart != NULL)
  {
    char *psz = newMessage;

    pStart += 6;  // skip to start of data
    pEnd = strstr(pStart, "/&");

    if (pEnd != NULL)
    {
      while (pStart != pEnd)
      {
        if ((*pStart == '%') && isxdigit(*(pStart + 1)))
        {
          // replace %xx hex code with the ASCII character
          char c = 0;
          pStart++;
          c += (htoi(*pStart++) << 4);
          c += htoi(*pStart++);
          *psz++ = c;
        }
        else
          *psz++ = *pStart++;
      }

      *psz = '\0'; // terminate the string
      newMessageAvailable = (strlen(newMessage) != 0);
      PRINT("\nNew Msg: ", newMessage);
    }
  }

  // check scroll direction
  pStart = strstr(szMesg, "/&SD=");
  if (pStart != NULL)
  {
    pStart += 5;  // skip to start of data

    PRINT("\nScroll direction: ", *pStart);
    scrollEffect = (*pStart == 'R' ? PA_SCROLL_RIGHT : PA_SCROLL_LEFT);
    P.setTextEffect(scrollEffect, scrollEffect);
    P.displayReset();
  }

  // check invert
  pStart = strstr(szMesg, "/&I=");
  if (pStart != NULL)
  {
    pStart += 4;  // skip to start of data

    PRINT("\nInvert mode: ", *pStart);
    P.setInvert(*pStart == '1');
  }

  // check speed
  pStart = strstr(szMesg, "/&SP=");
  if (pStart != NULL)
  {
    pStart += 5;  // skip to start of data

    int16_t speed = atoi(pStart);
    PRINT("\nSpeed: ", P.getSpeed());
    P.setSpeed(speed);
    frameDelay = speed;
  }
}

void handleWiFi(void)
{
  static enum { S_IDLE, S_WAIT_CONN, S_READ, S_EXTRACT, S_RESPONSE, S_DISCONN } state = S_IDLE;
  static char szBuf[1024];
  static uint16_t idxBuf = 0;
  static WiFiClient client;
  static uint32_t timeStart;

  switch (state)
  {
    case S_IDLE:   // initialise
      PRINTS("\nS_IDLE");
      idxBuf = 0;
      state = S_WAIT_CONN;
      break;

    case S_WAIT_CONN:   // waiting for connection
      {
        client = server.available();
        if (!client) break;
        if (!client.connected()) break;

#if DEBUG
        char szTxt[20];
        sprintf(szTxt, "%03d:%03d:%03d:%03d", client.remoteIP()[0], client.remoteIP()[1], client.remoteIP()[2], client.remoteIP()[3]);
        PRINT("\nNew client @ ", szTxt);
#endif

        timeStart = millis();
        state = S_READ;
      }
      break;

    case S_READ: // get the first line of data
      PRINTS("\nS_READ ");

      while (client.available())
      {
        char c = client.read();

        if ((c == '\r') || (c == '\n'))
        {
          szBuf[idxBuf] = '\0';
          client.flush();
          PRINT("\nRecv: ", szBuf);
          state = S_EXTRACT;
        }
        else
          szBuf[idxBuf++] = (char)c;
      }
      if (millis() - timeStart > 1000)
      {
        PRINTS("\nWait timeout");
        state = S_DISCONN;
      }
      break;

    case S_EXTRACT: // extract data
      PRINTS("\nS_EXTRACT");
      // Extract the string from the message if there is one
      getData(szBuf, BUF_SIZE);
      state = S_RESPONSE;
      break;

    case S_RESPONSE: // send the response to the client
      PRINTS("\nS_RESPONSE");
      // Return the response to the client (web page)
      client.print(WebResponse);
      client.print(WebPage);
      state = S_DISCONN;
      break;

    case S_DISCONN: // disconnect client
      PRINTS("\nS_DISCONN");
      client.flush();
      client.stop();
      state = S_IDLE;
      break;

    default:  state = S_IDLE;
  }
}

void setup()
{
  Serial.begin(115200);
  PRINTS("\n[MD_Parola WiFi Message Display]\nType a message for the scrolling display from your internet browser");

  P.begin();
  P.setIntensity(0);
  P.displayClear();
  P.displaySuspend(false);

  P.displayScroll(curMessage, PA_LEFT, scrollEffect, frameDelay);

  curMessage[0] = newMessage[0] = '\0';

  WiFiManager wifiManager;
  wifiManager.autoConnect("EN2024");

  // Connect to and initialise WiFi network
  PRINT("\nConnecting to ", ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    PRINT("\n", err2Str(WiFi.status()));
    delay(500);
  }
  PRINTS("\nWiFi connected");

  // Start the server
  server.begin();
  PRINTS("\nServer started");

  // Set up first message as the IP address
  sprintf(curMessage, "%03d:%03d:%03d:%03d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  PRINT("\nAssigned IP ", curMessage);
}

void loop()
{
  handleWiFi();

  if (P.displayAnimate())
  {
    if (newMessageAvailable)
    {
      strcpy(curMessage, newMessage);
      newMessageAvailable = false;
    }
    P.displayReset();
  }
}