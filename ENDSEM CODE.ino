
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   
#include <ArduinoJson.h>
#include <HTTPClient.h>


const char* ssid = "desktop";
const char* password = "shraddha";

#define BOTtoken "5826057078:AAHioUtBWLt3ephi_HB_bQMYSKBAuytFSzs"  // your Bot Token (Get from Botfather)

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif
String GOOGLE_SCRIPT_ID = "AKfycbzVP94yG1MobHUnH_FvmH4THX57DLj_V2BOCUgPeHIKR2GpWPIFZPNrY_suGW5C1kgd";
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int bot_Request_Delay_4 = 1000;
unsigned long last_TimeBot_Ran_4;



String chatId_1 ;
String pass_1;
int balance_4;
String assign[3];
int  StringCount = 0;
String y;
int x = Serial.parseInt();
int p = Serial.parseInt();
  int amount_debited_1 = x*100;
int amount_credited_1 = p*100;  
// Handle what happens when you receive new messages
void handle_NewMessages_4(int num_NewMessages) {
  Serial.println("handle_NewMessages_4");
  Serial.println(String(num_NewMessages));

  for (int i=0; i<num_NewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    Serial.println(text);
    String from_name = bot.messages[i].from_name;
    if (text == "/begin") {
      String answer = "welcome,Plz enter /log_in to login in your account";
      bot.sendMessage(chat_id, answer, "");

    }
    if(text =="/log_in"){
        String input = "pls enter your username";
        bot.sendMessage(chat_id, input, "");
        delay(7000);
        num_NewMessages = bot.getUpdates(bot.last_message_received + 1);
        String userName = bot.messages[i].text;
        Serial.println(userName);
        bot.sendMessage(chat_id,"pls enter your password", "");
        delay(7000);
        num_NewMessages = bot.getUpdates(bot.last_message_received + 1);
        String passWord = bot.messages[i].text;//String.toInt()
        Serial.println(passWord);
        if(userName == chatId_1 && passWord == pass_1){
          bot.sendMessage(chat_id,"verified user, plz enter /account_balance to view balance or plz enter /debit_amt if you want to debit money and /credit_amt to credit money", "");
        }
        else{
          bot.sendMessage(chat_id,"User is not there", "");
        }

    }
if(text =="/account_balance"){
  String amt = "Your account has 15000";

      bot.sendMessage(chat_id, amt, "");
      Serial.println(balance_4);
      transaction(balance_4, 0, 0, balance_4);   
      delay(5000);  
      
  }  
if(text =="/debit_amt"){
  
  
  String debitamt = "plz enter value of x";
   

  bot.sendMessage(chat_id, debitamt, ""); 
  delay(5000);
  num_NewMessages = bot.getUpdates(bot.last_message_received + 1);
  String y = bot.messages[i].text;
  int x = y.toInt();
  int amount_debited_1 = x*100;
  Serial.println(x);             
  delay(3000);
  int f = balance_4;
  f = balance_4 - amount_debited_1;
  transaction(balance_4, 0, amount_debited_1, f); 
  if(x <= 30){
     String debission = "Your account balance is "+ String(f)+" and amount debited is"+String(amount_debited_1)+" \n";
     bot.sendMessage(chat_id, debission, "");          
  }
  else{
    String correction = "Your account has insufficient balance";
    bot.sendMessage(chat_id, correction, "");     
  }    
  Serial.println(amount_debited_1);    
  Serial.println(f);     
}

if(text =="/credit_amt"){
  String val = "plz enter value of p"; 
  bot.sendMessage(chat_id, val, "");  
  delay(5000);
  num_NewMessages = bot.getUpdates(bot.last_message_received + 1);
  String z = bot.messages[i].text;
  int p = z.toInt();
  int amount_credited_1 = p*100;
  Serial.println(p);             
  delay(3000);   
  int h = balance_4;   
  h = balance_4 + amount_credited_1;  
  transaction(balance_4 , amount_credited_1, 0, h) ;  
    
  String credission = "Your account balance is "+ String(h)+" and amount credited is"+String(amount_credited_1)+" \n";
  bot.sendMessage(chat_id, credission, "");    
  Serial.println(amount_credited_1);    
  Serial.println(h);  
  
  
}


}
}
void transaction(int t_1, int t_2, int t_3, int t_4){
    if (WiFi.status () == WL_CONNECTED) {
    
    String url_Final = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
    "/exec?"+"prev_balance=" + String (t_1) + "&credit=" + String (t_2)+ "&debit=" + String (t_3) +"&current_balance=" + String (t_4);
    Serial.print ("Show transaction in spreadsheet:");
    Serial.println (url_Final);
    HTTPClient http;
    http.begin (url_Final.c_str () );
    http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
    int http_Code_1 = http.GET () ;
    Serial.print ("HTTP_Status_Code: ");
    Serial.println (http_Code_1);
    http.end () ;  
}
}
void read(){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?read";
    Serial.println("Request made");
    http.begin(url.c_str()); //Specify the URL and certificate
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int http_Code_1 = http.GET();
    String payload;
    
     if (http_Code_1 > 0) { //Check for the returning code
      payload = http.getString();
      Serial.println(http_Code_1);
      Serial.println(payload);
       while(payload.length()>0){
        int index = payload.indexOf(',');
        if (index==-1){
          assign[StringCount++]=payload;
          break;
        }
        else{
           assign[StringCount++]=payload.substring(0,index);
           payload = payload.substring(index+1);
                             
        }
      }  
       
     
      chatId_1= assign[0];
      pass_1 =assign[1];
      balance_4=assign[2].toInt();
      Serial.println(assign[2]);
      Serial.println(assign[1]);
    
   
    }
    else {
      Serial.println("Error_on_HTTP_request");
    }
    http.end();
  }
  delay(1000);
}
  
void setup() {
  Serial.begin(115200);

  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      
    client.setTrustAnchors(&cert); 
  #endif
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Network is being associated..");
  }
  
  Serial.println(WiFi.localIP());
  read() ;
}

void loop() {
  if (millis() > last_TimeBot_Ran_4 + bot_Request_Delay_4)  {
    int num_NewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(num_NewMessages) {
      Serial.println("got response");
      handle_NewMessages_4(num_NewMessages);
      num_NewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    last_TimeBot_Ran_4 = millis();
  }
}

