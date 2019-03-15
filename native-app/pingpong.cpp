// #include <iostream>
// using namespace std;

// int main() {
//   string input;
//   cin >> input;
//   cout << input;
// }

#include <iostream>
#include <fstream>
#include <json/json.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
  
  string inp = "";
  bool nativeMessaging = false;
  if (argv[1] != NULL) {
    
    unsigned int c, i, t;
    inp = argv[1];
    
    if (inp.find("chrome-extension://") != std::string::npos) {
      nativeMessaging = true;

        // Reset inp
        inp = "";
        t = 0;

        // Sum the first 4 chars from stdin (the length of the message passed).
        for (i = 0; i <= 3; i++) {
          t += getchar();
        }
        
        // Loop getchar to pull in the message until we reach the total
        //  length provided.
        for (i=0; i < t; i++) {
          c = getchar();
          inp += c;
        }
    } 
  } else {
      // get input from cin for debugging purpose
      cin >> inp;
  }

  // Read JSON via jsoncpp
  Json::Reader reader;
  Json::Value obj;
  reader.parse(inp, obj);
  string inputText = obj["text"].asString();

  // Write message sent from extension to log file
  ofstream outfile;
  outfile.open("log.txt", ios::out | ios::app);
  outfile << "JSON: " << inp << endl;
  outfile << "Text: " << inputText << endl;
  outfile << "------------" << endl;
  outfile.close();

  // Define our message
  string message = "{\"text\": \"" + inputText + "\"}";
  // Collect the length of the message
  unsigned int len = message.length();
  // We need to send the 4 bytes of length information
  cout << char(((len>>0) & 0xFF))
            << char(((len>>8) & 0xFF))
            << char(((len>>16) & 0xFF))
            << char(((len>>24) & 0xFF));
  // Now we can output our message
  cout << message;

  // Prevent "Native host has exited." error
  string temp;
  cin >> temp;

  return 0;
}