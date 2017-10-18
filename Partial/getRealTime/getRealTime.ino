char buf[9];

void setup() {

  Serial.begin(115200);

  //system("date 010112002013"); //sets the date & time to 12:00 1st Jan 2013
}





void loop() {



  system("date '+%H:%M:%S' > /home/root/time.txt");  //get current time in the format- hours:minutes:secs

  //and save in text file time.txt located in /home/root

  FILE *fp;

  fp = fopen("/home/root/time.txt", "r");

  fgets(buf, 9, fp);

  fclose(fp);



  Serial.print("The current time is ");

  Serial.println(buf);

  delay(1000);



}
