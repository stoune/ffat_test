#include <Arduino.h>

#include "FS.h"
#include "FFat.h"

// You only need to format FFat the first time you run a test
#define FORMAT_FFAT false

void printFileContent(File& file);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  
  
  if(!FFat.begin(false)){
    Serial.println("An Error has occurred while mounting FFat");
    return;
  }

  // To format all space in FFat
  if (FORMAT_FFAT) {
    FFat.format();
  }

  // Get all information of your FFat
  unsigned int totalBytes = FFat.totalBytes();
  unsigned int usedBytes = FFat.usedBytes();
  unsigned int freeBytes = FFat.freeBytes();
  Serial.println("File system info.");
  Serial.print("Total space:      ");
  Serial.print(totalBytes);
  Serial.println("byte");

  Serial.print("Total space used: ");
  Serial.print(usedBytes);
  Serial.println("byte");

  Serial.print("Total space free: ");
  Serial.print(freeBytes);
  Serial.println("byte");


  // Files existence check
  if (FFat.exists( "/temp.txt" ) )
  {
    Serial.println( "temp.txt exists");
  }else
  {
    Serial.println( "temp.txt does not exist");
  }

  if (FFat.exists( "/test.json" ) )
  {
    Serial.println( "test.json exists");
  }
  else
  {
    Serial.println( "test.json does not exist");
  }

  // Files reading examples
  // open file
  File file = FFat.open("/test.json");
  if(!file){ // Don't forget to check if file was opened successfully
    Serial.println("Failed to open test.json file for reading");
    return;
  }

  printFileContent(file);  
  file.close();

  File fileTmp = FFat.open("/temp.txt", "r"); // Open modes compattible with ANSI C98, read, writ and append
  if(!fileTmp){
    Serial.println("Failed to open temp.txt file for reading and writing");
    return;
  }

  printFileContent(fileTmp);  
  fileTmp.close();
  
  Serial.println("End setup!");
}

void printFileContent(File& file)
{
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("In loop!"); 
}